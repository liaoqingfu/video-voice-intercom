
#include "XmlRpcServer.h"
#include "XmlRpcServerConnection.h"
#include "XmlRpcServerMethod.h"
#include "XmlRpcSocket.h"
#include "XmlRpcUtil.h"
#include "XmlRpcException.h"
#include "XmlRpcThreads.h"
#include <sys/types.h>


using namespace XmlRpc;


XmlRpcServer::XmlRpcServer()
{
  _introspectionEnabled = false;
  _isDaemonized = false;
  _listMethods = 0;
  _methodHelp = 0;
  _sessionMgr = NULL;  ///>>>>>BSTAR<<<<<
  _isSessionSpawnEnabled = false;
  _isSessionChild = false;
  _isMultiThread = false;
  _pt = NULL;
}


XmlRpcServer::~XmlRpcServer()
{
  this->shutdown();
  _methods.clear();
  delete _listMethods;
  delete _methodHelp;
  delete _sessionMgr;  ///>>>>>BSTAR<<<<<
  delete _pt;
}



// Add a command to the RPC server
void 
XmlRpcServer::addMethod(XmlRpcServerMethod* method)
{
  _methods[method->name()] = method;
}

// Remove a command from the RPC server
void 
XmlRpcServer::removeMethod(XmlRpcServerMethod* method)
{
  MethodMap::iterator i = _methods.find(method->name());
  if (i != _methods.end())
    _methods.erase(i);
}

// Remove a command from the RPC server by name
void 
XmlRpcServer::removeMethod(const std::string& methodName)
{
  MethodMap::iterator i = _methods.find(methodName);
  if (i != _methods.end())
    _methods.erase(i);
}


// Look up a method by name
XmlRpcServerMethod* 
XmlRpcServer::findMethod(const std::string& name) const
{
  MethodMap::const_iterator i = _methods.find(name);
  if (i == _methods.end())
    return 0;
  return i->second;
}


// Create a socket, bind to the specified port, and
// set it in listen mode to make it available for clients.
bool 
XmlRpcServer::bindAndListen(int port, int backlog /*= 5*/, const char* device /*=NULL*/)
{
  int fd = XmlRpcSocket::socket();
  if (fd < 0)
  {
    XmlRpcUtil::error("XmlRpcServer::bindAndListen: Could not create socket (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }

  this->setfd(fd);

  // Don't block on reads/writes
  if ( ! XmlRpcSocket::setNonBlocking(fd))
  {
    this->close();
    XmlRpcUtil::error("XmlRpcServer::bindAndListen: Could not set socket to non-blocking input mode (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }

  // Allow this port to be re-bound immediately so server re-starts are not delayed
  if ( ! XmlRpcSocket::setReuseAddr(fd))
  {
    this->close();
    XmlRpcUtil::error("XmlRpcServer::bindAndListen: Could not set SO_REUSEADDR socket option (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }

  ///>>>>>BSTAR
  // Bind to the specified interface 
  if( device )
  if ( ! XmlRpcSocket::setBindDevice(fd, device))
  {
    this->close();
    XmlRpcUtil::error("XmlRpcServer::bindAndListen: Could not bind to specified interface (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }
  if ( ! XmlRpcSocket::setKeepAlive(fd))
  {
    this->close();
    XmlRpcUtil::error("XmlRpcServer::bindAndListen: Could not set SO_KEEPALIVE socket option (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }
  ///<<<<<BSTAR

  // Bind to the specified port on the default interface
  if ( ! XmlRpcSocket::bind(fd, port))
  {
    this->close();
    XmlRpcUtil::error("XmlRpcServer::bindAndListen: Could not bind to specified port (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }

  // Set in listening mode
  if ( ! XmlRpcSocket::listen(fd, backlog))
  {
    this->close();
    XmlRpcUtil::error("XmlRpcServer::bindAndListen: Could not set socket in listening mode (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }

  XmlRpcUtil::log(2, "XmlRpcServer::bindAndListen: server listening on port %d fd %d", port, fd);

  // Notify the dispatcher to listen on this source when we are in work()
  _disp.addSource(this, XmlRpcDispatch::ReadableEvent);

  return true;
}


// Process client requests for the specified time
void 
XmlRpcServer::work(double msTime)
{
  XmlRpcUtil::log(2, "XmlRpcServer::work: waiting for a connection");
  _disp.work(msTime);
}



// Handle input on the server socket by accepting the connection
// and reading the rpc request.
unsigned
XmlRpcServer::handleEvent(unsigned mask)
{
  acceptConnection();
  return XmlRpcDispatch::ReadableEvent;		// Continue to monitor this fd
}


// Accept a client connection request and create a connection to
// handle method calls from the client.
void
XmlRpcServer::acceptConnection()
{
  int s = XmlRpcSocket::accept(this->getfd());
  XmlRpcUtil::log(3, "XmlRpcServer::acceptConnection: socket %d", s);
  if (s < 0)
  {
    //this->close();
    XmlRpcUtil::error("XmlRpcServer::acceptConnection: Could not accept connection (%s).", XmlRpcSocket::getErrorMsg().c_str());
  }
  else if ( ! XmlRpcSocket::setNonBlocking(s))
  {
    XmlRpcSocket::close(s);
    XmlRpcUtil::error("XmlRpcServer::acceptConnection: Could not set socket to non-blocking input mode (%s).", XmlRpcSocket::getErrorMsg().c_str());
  }
  else  // Notify the dispatcher to listen for input on this source when we are in work()
  {
    XmlRpcUtil::log(4, "XmlRpcServer::acceptConnection: creating a connection");
    //Fork a new process if spawning enabled
    if (!isSessionSpawnEnabled()) 
      _disp.addSource(this->createConnection(s), XmlRpcDispatch::ReadableEvent);
    else
      spawn(s);
  }
}

// Create a new connection object for processing requests from a specific client.
XmlRpcServerConnection*
XmlRpcServer::createConnection(int s)
{
  // Specify that the connection object be deleted when it is closed
  return new XmlRpcServerConnection(s, this, true);
}


void 
XmlRpcServer::removeConnection(XmlRpcServerConnection* sc)
{
  _disp.removeSource(sc);
}


// Stop processing client requests
void 
XmlRpcServer::exit()
{
  _disp.exit();
}


// Close the server socket file descriptor and stop monitoring connections
void 
XmlRpcServer::shutdown()
{
  // This closes and destroys all connections as well as closing this socket
  _disp.clear();
}


// Introspection support
static const std::string LIST_METHODS("System.listMethods");
static const std::string METHOD_HELP("System.methodHelp");
static const std::string MULTICALL("System.multicall");


// List all methods available on a server
class ListMethods : public XmlRpcServerMethod
{
public:
  ListMethods(XmlRpcServer* s) : XmlRpcServerMethod(LIST_METHODS, s, false) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    _server->listMethods(result);
  }

  std::string help() { return std::string("List all methods available on a server as an array of strings"); }
};


// Retrieve the help string for a named method
class MethodHelp : public XmlRpcServerMethod
{
public:
  MethodHelp(XmlRpcServer* s) : XmlRpcServerMethod(METHOD_HELP, s, false) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    if (params[0].getType() != XmlRpcValue::TypeString)
      throw XmlRpcException(METHOD_HELP + ": Invalid argument type");

    XmlRpcServerMethod* m = _server->findMethod(params[0]);
    if ( ! m)
      throw XmlRpcException(METHOD_HELP + ": Unknown method name");

    result = m->help();
  }

  std::string help() { return std::string("Retrieve the help string for a named method"); }
};

///>>>>>BSTAR
//Detatch the control tty and run the server as a daemon
void 
XmlRpcServer::daemonize()
{
#if defined(_WINDOWS)
#else
    daemon(1, 0);
    setsid(); 
    //for (int i=getdtablesize(); i>=0; --i)
    //   ::close(i);
#endif
}


int 
XmlRpcServer::pushTaskToThreads(XmlRpcServerConnection* pc)
{

  return _pt->pushTask(pc);

} 

void 
XmlRpcServer::spawn(int fd)
{
#if defined(_WINDOWS)
#else
  pid_t pid;
  if ((pid = fork()) < 0 ) 
  {
    XmlRpcUtil::log(2, "XmlRpcServer::spawn: Failure to fork");
    return;
  }

  //child process
  if(pid == 0) 
  {
      enableSessionSpawn(false);
      setSessionChild();
      _disp.addSource(this->createConnection(fd), XmlRpcDispatch::ReadableEvent);
      _disp.removeSource(this);
      this->close();
  } 
 //parent process
  else  
  {
      XmlRpcUtil::log(3, "XmlRpcServer::spawn: Created child pid=%d for fd=%d", pid, fd);
      XmlRpcSocket::close(fd);
  }
#endif
}

void 
XmlRpcServer::enableSessionManager(bool enabled)
{
  if(enabled) 
  {
    XmlRpcUtil::log(5, "XmlRpcServer::Session Manager enabled!");
    if(!_sessionMgr) _sessionMgr = new XmlRpcSessionManager();
  }
  else
  {
    XmlRpcUtil::log(5, "XmlRpcServer::Session Manager disabled!");
    if(_sessionMgr) delete _sessionMgr; 
    _sessionMgr = NULL;
  }

}

bool 
XmlRpcServer::isSessionManagerEnabled()
{
  return _sessionMgr != NULL;
}
///<<<<<BSTAR
XmlRpcSessionManager* 
XmlRpcServer::getSessionManager()
{
  return _sessionMgr;
}

void 
XmlRpcServer::enableSessionSpawn(bool enabled) 
{
  // 如果开启了多线程选项,则忽略此次调用
  if( _isMultiThread )
    return;
  
  _isSessionSpawnEnabled = enabled;
}

bool 
XmlRpcServer::isSessionSpawnEnabled() 
{
  return _isSessionSpawnEnabled;
}

bool 
XmlRpcServer::isSessionChild() 
{
  return _isSessionChild;
}

void 
XmlRpcServer::setSessionChild( bool yes ) 
{
  _isSessionChild = yes;
}

void 
XmlRpcServer::enabledMultiThread(bool enabled, int threadNum)
{

  if(enabled)
  {
    _isSessionSpawnEnabled = false; // 关掉该特性

    // 开启线程
    this->_pt = new XmlRpcThreads();
    this->_pt->initThreads(threadNum);
  }

  _isMultiThread = enabled;

}

bool
XmlRpcServer::isMultiThread()
{
  return _isMultiThread;
}
///<<<<<BSTAR
    
// Specify whether introspection is enabled or not. Default is enabled.
void 
XmlRpcServer::enableIntrospection(bool enabled)
{
  if (_introspectionEnabled == enabled)
    return;

  _introspectionEnabled = enabled;

  if (enabled)
  {
    if ( ! _listMethods)
    {
      _listMethods = new ListMethods(this);
      _methodHelp = new MethodHelp(this);
    } else {
      addMethod(_listMethods);
      addMethod(_methodHelp);
    }
  }
  else
  {
    removeMethod(LIST_METHODS);
    removeMethod(METHOD_HELP);
  }
}


void
XmlRpcServer::listMethods(XmlRpcValue& result)
{
  int i = 0;
  result.setSize(_methods.size()+1);
  for (MethodMap::iterator it=_methods.begin(); it != _methods.end(); ++it)
    result[i++] = it->first;

  // Multicall support is built into XmlRpcServerConnection
  result[i] = MULTICALL;
}



