
#ifndef _XMLRPCSERVER_H_
#define _XMLRPCSERVER_H_
//
// XmlRpc++ Copyright (c) 2002-2003 by Chris Morley
//
#if defined(_MSC_VER)
# pragma warning(disable:4786)    // identifier was truncated in debug info
#endif

#ifndef MAKEDEPEND
# include <map>
# include <string>
#endif

#if defined(_WINDOWS)
#else
# include <unistd.h>
#endif

#include "XmlRpcSessionManager.h"  ///>>>>>BSTAR<<<<<
#include "XmlRpcDispatch.h"
#include "XmlRpcSource.h"

namespace XmlRpc {


  // An abstract class supporting XML RPC methods
  class XmlRpcServerMethod;

  // Class representing session manager 
  class XmlRpcSessionManager;

  // Class representing connections to specific clients
  class XmlRpcServerConnection;

  // Class representing argument and result values
  class XmlRpcValue;

  // Class threads
  class XmlRpcThreads;

  //! A class to handle XML RPC requests
  class XmlRpcServer : public XmlRpcSource {
  public:
    //! Create a server object.
    XmlRpcServer();
    //! Destructor.
    virtual ~XmlRpcServer();

    //! Specify whether introspection is enabled or not. Default is not enabled.
    void enableIntrospection(bool enabled=true);

    //! Add a command to the RPC server
    void addMethod(XmlRpcServerMethod* method);

    //! Remove a command from the RPC server
    void removeMethod(XmlRpcServerMethod* method);

    //! Remove a command from the RPC server by name
    void removeMethod(const std::string& methodName);

    //! Look up a method by name
    XmlRpcServerMethod* findMethod(const std::string& name) const;

    //! Create a socket, bind to the specified port, and
    //! set it in listen mode to make it available for clients.
    bool bindAndListen(int port, int backlog = 5, const char* device = NULL);

    //! Process client requests for the specified time
    void work(double msTime);

    //! Temporarily stop processing client requests and exit the work() method.
    void exit();

    //! Close all connections with clients and the socket file descriptor
    void shutdown();

    //! Introspection support
    void listMethods(XmlRpcValue& result);

    // XmlRpcSource interface implementation

    //! Handle client connection requests
    virtual unsigned handleEvent(unsigned eventType);

    //! Remove a connection from the dispatcher
    virtual void removeConnection(XmlRpcServerConnection*);
    ///>>>>>BSTAR
    //! Run as a daemon
    void daemonize();
    void spawn(int fd);
    //! Session tracking support
    void enableSessionManager(bool enabled = true); 
    bool isSessionManagerEnabled(); 
    XmlRpcSessionManager* getSessionManager(); 
    
    // 使用多进程执行,仅在linux平台下有效.
    void enableSessionSpawn(bool enabled = true); 
    bool isSessionSpawnEnabled(); 
    bool isSessionChild(); 
    void setSessionChild(bool yes = true); 

    // 使用多线程(线程池)执行
    // 此选项如果调用,则enableSessionSpawn()失效.
    void enabledMultiThread(bool enabled, int threadNum);
    bool isMultiThread();
    int pushTaskToThreads(XmlRpcServerConnection* pc);
    ///<<<<<BSTAR

  protected:

    //! Accept a client connection request
    virtual void acceptConnection();

    //! Create a new connection object for processing requests from a specific client.
    virtual XmlRpcServerConnection* createConnection(int socket);

    // Whether the introspection API is supported by this server
    bool _introspectionEnabled;
    bool _isDaemonized;
    bool _isSessionSpawnEnabled;
    bool _isSessionChild;
    bool _isMultiThread;
    XmlRpcThreads* _pt;

    // Event dispatcher
    XmlRpcDispatch _disp;

    XmlRpcSessionManager*  _sessionMgr;    ///>>>>>BSTAR<<<<<

    // Collection of methods. This could be a set keyed on method name if we wanted...
    typedef std::map< std::string, XmlRpcServerMethod* > MethodMap;
    MethodMap _methods;

    // system methods
    XmlRpcServerMethod* _listMethods;
    XmlRpcServerMethod* _methodHelp;

  };
} // namespace XmlRpc

#endif //_XMLRPCSERVER_H_
