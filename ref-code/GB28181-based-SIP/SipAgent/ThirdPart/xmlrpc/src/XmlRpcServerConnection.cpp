#include "XmlRpcServerConnection.h"

#include "XmlRpcSocket.h"
#include "XmlRpc.h"
#ifndef MAKEDEPEND
# include <stdio.h>
# include <stdlib.h>
#endif
///BSTAR >>>>>
#if !defined(_WINDOWS)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "XmlRpcSessionManager.h"

#endif
///BSTAR <<<<<

using namespace XmlRpc;

// Static data
const char XmlRpcServerConnection::METHODNAME_TAG[] = "<methodName>";
const char XmlRpcServerConnection::PARAMS_TAG[] = "<params>";
const char XmlRpcServerConnection::PARAMS_ETAG[] = "</params>";
const char XmlRpcServerConnection::PARAM_TAG[] = "<param>";
const char XmlRpcServerConnection::PARAM_ETAG[] = "</param>";

const std::string XmlRpcServerConnection::SYSTEM_MULTICALL = "system.multicall";
const std::string XmlRpcServerConnection::METHODNAME = "methodName";
const std::string XmlRpcServerConnection::PARAMS = "params";

const std::string XmlRpcServerConnection::FAULTCODE = "faultCode";
const std::string XmlRpcServerConnection::FAULTSTRING = "faultString";



// The server delegates handling client requests to a serverConnection object.
XmlRpcServerConnection::XmlRpcServerConnection(int fd, XmlRpcServer* server, bool deleteOnClose /*= false*/) :
  XmlRpcSource(fd, deleteOnClose)
{
  XmlRpcUtil::log(3,"XmlRpcServerConnection: new socket %d.", fd);
  _server = server;
  _connectionState = READ_HEADER;
  _keepAlive = true;
  _threadWorking = false;
  _isDisconnected = false;
  _sessionId = -1;
  _userSpec = 0;
  if(_server->isSessionManagerEnabled())
    _server->getSessionManager()->open(getfd());  
}


XmlRpcServerConnection::~XmlRpcServerConnection()
{
  XmlRpcUtil::log(4,"XmlRpcServerConnection dtor.");
  _server->removeConnection(this);
}
///>>>>>BSTAR
void
XmlRpcServerConnection::close()
{
  // 如果是多线程模式,且当前任务还在线程中执行
  // 则当前不做close()操作,由线程检测退出,见 XmlRpcThreads::execTask()
  if(_server->isMultiThread() && getThreadWorking() ) {
    setDisconnected();
    XmlRpcUtil::log(3, "Can't destroy fd %d directly, another thread is working.", this->getfd());
    return;  
  }

  XmlRpcUtil::log(4,"XmlRpcServerConnection closed: %d, client session:%d, userSpec:%d", 
                  getfd(), _sessionId, _userSpec);
  if(_server->isSessionManagerEnabled())
     _server->getSessionManager()->close(getfd()); 
  if(_server->isSessionSpawnEnabled())
    if(_server->isSessionChild()) {
      _server->shutdown();
      XmlRpcSource::close();
      exit(0);
    }
  XmlRpcSource::close();
}
///<<<<<BSTAR

// Handle input on the server socket by accepting the connection
// and reading the rpc request. Return true to continue to monitor
// the socket for events, false to remove it from the dispatcher.
unsigned
XmlRpcServerConnection::handleEvent(unsigned /*eventType*/)
{
  if(_server->isMultiThread() && getThreadWorking()) {
    XmlRpcUtil::log(3, "A wrong order at the request arrival, fd:%d, session:%d", 
                    getfd(), _sessionId );
    // 正常通讯下,代码执行到这里,_connectionState == READ_HEADER
    // 意味着上一个应答没有结束,但新的请求到达了.
    // 可能是处理的线程尚未执行解锁的代码(概率极低,因此延时后再检测一次),或者是出现错序的通讯.
#if defined(_WINDOWS)
    Sleep(1);//windows  下的sleep函数的参数是以毫秒为单位
#else
    usleep(1000);
#endif
    if(getThreadWorking())
      return handleWrongStatus();
    else
      return XmlRpcDispatch::ReadableEvent;
  }

  if (_connectionState == READ_HEADER)
    if ( ! readHeader()) return 0;

  if (_connectionState == READ_REQUEST)
    if ( ! readRequest()) return 0;

  if (_connectionState == WRITE_RESPONSE)
    if ( ! writeResponse()) return 0;

  return (_connectionState == WRITE_RESPONSE) 
        ? XmlRpcDispatch::WritableEvent : XmlRpcDispatch::ReadableEvent;
}


unsigned
XmlRpcServerConnection::handleWrongStatus()
{
  // 如果当前连接正在线程执行中,如何处理?
  // 目前的处理方式是读取请求但丢弃掉.
  // 但如果出错,或对端关闭,返回false

  XmlRpcUtil::log(3, "XmlRpcServerConnection::handleWrongStatus: error on execute status at fd %d", 
                  this->getfd());     

  std::string tmpStr;
  bool tmpEof;
  bool rs = XmlRpcSocket::nbRead(this->getfd(), tmpStr, &tmpEof);

  if(rs)
  {
    // 对端正常关闭socket
    if(tmpStr.empty())
      return 0;
  }
  else
  {
    return 0;
  }

  return XmlRpcDispatch::ReadableEvent;
}


bool
XmlRpcServerConnection::readHeader()
{

  // Read available data
  bool eof;
  if ( ! XmlRpcSocket::nbRead(this->getfd(), _header, &eof)) {
    // Its only an error if we already have read some data
    if (_header.length() > 0)
      XmlRpcUtil::error("XmlRpcServerConnection::readHeader: error while reading header (%s).",XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }

  XmlRpcUtil::log(4, "XmlRpcServerConnection::readHeader: read %d bytes.", _header.length());
  char *hp = (char*)_header.c_str();  // Start of header
  char *ep = hp + _header.length();   // End of string
  char *bp = 0;                       // Start of body
  char *ckp =0;                       // Start of cookie
  char *lp = 0;                       // Start of content-length value
  char *kp = 0;                       // Start of connection value
  char *rpb = 0;                       // Start of referer 
  char *rpe = 0;                       // End of referer 


  for (char *cp = hp; (bp == 0) && (cp < ep); ++cp) {
	if ((ep - cp > 16) && (strncasecmp(cp, "Content-length: ", 16) == 0))
	  lp = cp + 16;
  else if ((ep - cp > 8) && (strncasecmp(cp, "Cookie: ", 8) == 0))
    ckp = cp + 8;
	else if ((ep - cp > 12) && (strncasecmp(cp, "Connection: ", 12) == 0))
	  kp = cp + 12;
	else if ((ep - cp > 9) && (strncasecmp(cp, "Referer: ", 9) == 0))
	  rpb = cp + 9;
	else if ((ep - cp > 4) && (strncmp(cp, "\r\n\r\n", 4) == 0))
	  bp = cp + 4;
	else if ((ep - cp > 2) && (strncmp(cp, "\n\n", 2) == 0))
	  bp = cp + 2;
  }

  // 如果没有设置过session,且当前连接中有cookie值
  if(_sessionId == -1 && ckp != 0) {
    setUserCookie(ckp);
  }

  // If we haven't gotten the entire header yet, return (keep reading)
  if (bp == 0) {
    // EOF in the middle of a request is an error, otherwise its ok
    if (eof) {
      XmlRpcUtil::log(4, "XmlRpcServerConnection::readHeader: EOF");
      if (_header.length() > 0)
        XmlRpcUtil::error("XmlRpcServerConnection::readHeader: EOF while reading header");
      return false;   // Either way we close the connection
    }
    
    return true;  // Keep reading
  }
  //Decode referer
  _referer = "";
  if (rpb != 0) {
     rpe = strstr(rpb, "\r\n");
     if(rpe) 
       _referer = std::string(rpb, rpe-rpb);
   }
  XmlRpcUtil::log(4, "XmlRpcServerConnection::readHeader: referer is %s.", _referer.c_str());
  // Decode content length
  if (lp == 0) {
    XmlRpcUtil::error("XmlRpcServerConnection::readHeader: No Content-length specified");
    return false;   // We could try to figure it out by parsing as we read, but for now...
  }

  _contentLength = atoi(lp);
  if (_contentLength <= 0) {
    XmlRpcUtil::error("XmlRpcServerConnection::readHeader: Invalid Content-length specified (%d).", _contentLength);
    return false;
  }
  	
  XmlRpcUtil::log(4, "XmlRpcServerConnection::readHeader: specified content length is %d.", _contentLength);

  // Otherwise copy non-header data to request buffer and set state to read request.
  _request = bp;

  // Parse out any interesting bits from the header (HTTP version, connection)
  _keepAlive = true;
  if (_header.find("HTTP/1.0") != std::string::npos) {
    if (kp == 0 || strncasecmp(kp, "keep-alive", 10) != 0)
      _keepAlive = false;           // Default for HTTP 1.0 is to close the connection
  } else {
    if (kp != 0 && strncasecmp(kp, "close", 5) == 0)
      _keepAlive = false;
  }
  // XmlRpcUtil::log(4, "KeepAlive: %d", _keepAlive);


  _header = ""; 
  _connectionState = READ_REQUEST;
  return true;    // Continue monitoring this source
}

bool
XmlRpcServerConnection::readRequest()
{
  // If we dont have the entire request yet, read available data
  if (int(_request.length()) < _contentLength) {
    bool eof;
    if ( ! XmlRpcSocket::nbRead(this->getfd(), _request, &eof)) {
      XmlRpcUtil::error("XmlRpcServerConnection::readRequest: read error (%s).",XmlRpcSocket::getErrorMsg().c_str());
      return false;
    }

    // If we haven't gotten the entire request yet, return (keep reading)
    if (int(_request.length()) < _contentLength) {
      if (eof) {
        XmlRpcUtil::error("XmlRpcServerConnection::readRequest: EOF while reading request");
        return false;   // Either way we close the connection
      }
      return true;
    }
  }

  // Otherwise, parse and dispatch the request
  XmlRpcUtil::log(5, "XmlRpcServerConnection::readRequest read %d bytes.", _request.length());
  XmlRpcUtil::log(7, "XmlRpcServerConnection::readRequest:\n%s\n", _request.c_str());

  _connectionState = WRITE_RESPONSE;

  return true;    // Continue monitoring this source
}


bool
XmlRpcServerConnection::writeResponse()
{

  if(_server->isMultiThread()) {
    // 置状态为线程处理中
    setThreadWorking(true);

    // 提交待处理的连接到线程池,如提交失败(没有想到任何原因会导致它),
    // 则由自身线程处理.
    if( _server->pushTaskToThreads(this) == -1) {
      setThreadWorking(false);
      XmlRpcUtil::log(3, "XmlRpcServerConnection::writeResponse can't execute method via thread.");
      return writeResponseThread();
    }

    // 改变状态为读头
    _connectionState = READ_HEADER;

    return true;
  }
  else
  {
    return writeResponseThread();
  }

}


bool
XmlRpcServerConnection::writeResponseThread()
{
  if (_response.length() == 0) {
    executeRequest();
    _bytesWritten = 0;
    if (_response.length() == 0) {
      XmlRpcUtil::error("XmlRpcServerConnection::writeResponse: empty response.");
      return false;
    }
  }

  int timeOutMS = 0;
  // 如果是在线程中执行写,则最多阻塞一分钟,如一分钟内没写完,nbWrite() 返回失败
  if( getThreadWorking())
    timeOutMS = 60*1000;
  
  // Try to write the response
  if ( ! XmlRpcSocket::nbWrite(this->getfd(), _response, &_bytesWritten, timeOutMS)) {
    XmlRpcUtil::error("XmlRpcServerConnection::writeResponse: write error (%s).",XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }
  // XmlRpcUtil::log(5, "XmlRpcServerConnection::writeResponse: wrote %d of %d bytes.", _bytesWritten, _response.length());

  // Prepare to read the next request
  if (_bytesWritten == int(_response.length())) {
    _header = "";
    _request = "";
    _response = "";
    _connectionState = READ_HEADER;
  }

  return _keepAlive;    // Continue monitoring this source if true
}



// Run the method, generate _response string
void
XmlRpcServerConnection::executeRequest()
{
  XmlRpcValue params, resultValue;
  std::string methodName = parseRequest(params);
  XmlRpcUtil::log(3, "XmlRpcServerConnection::executeRequest: server calling method '%s', client session:%d, userSpec:%d", 
                    methodName.c_str(), _sessionId, _userSpec);

  try {

    if ( ! executeMethod(methodName, params, resultValue) &&
         ! executeMulticall(methodName, params, resultValue))
      generateFaultResponse(methodName + ": unknown method name");
    else
      generateResponse(resultValue.toXml());

  } catch (const XmlRpcException& fault) {
    XmlRpcUtil::log(2, "XmlRpcServerConnection::executeRequest: fault <%d>:%s.",
                    fault.getCode(), fault.getMessage().c_str()); 
    generateFaultResponse(fault.getMessage(), fault.getCode());
  }
}

// Parse the method name and the argument values from the request.
std::string
XmlRpcServerConnection::parseRequest(XmlRpcValue& params)
{
  int offset = 0;   // Number of chars parsed from the request

  std::string methodName = XmlRpcUtil::parseTag(METHODNAME_TAG, _request, &offset);

  if (methodName.size() > 0 && XmlRpcUtil::findTag(PARAMS_TAG, _request, &offset))
  {
    int nArgs = 0;
    while (XmlRpcUtil::nextTagIs(PARAM_TAG, _request, &offset)) {
      params[nArgs++] = XmlRpcValue(_request, &offset);
      (void) XmlRpcUtil::nextTagIs(PARAM_ETAG, _request, &offset);
    }

    (void) XmlRpcUtil::nextTagIs(PARAMS_ETAG, _request, &offset);
  }

  return methodName;
}

///>>>>>BSTAR
// Added context info to params[0]
void 
XmlRpcServerConnection::generateContext(XmlRpcValue& params)
{
  try {
    int fd = getfd();
    // int sid = _server->getSessionManager()->fd2id(fd); 
    params[0]["_fd"] = fd;              // 用户连接的句柄
    params[0]["_session"] = _sessionId; // 用户session
    params[0]["_userSpec"] = _userSpec;  // 用户指定的参数
    // XmlRpcUtil::log(4, "XmlRpcServerConnection::generateContext: Injected session id %d", _sessionId);
    } catch (XmlRpcException) {
      XmlRpcUtil::log(3, "XmlRpcServerConnection::generateContext:  When sessionManager enabled,params[0] can only be empty or a struct!");
    }
}

// Execute a named method with the specified params.
bool
XmlRpcServerConnection::executeMethod(const std::string& methodName, 
                                      XmlRpcValue& params, XmlRpcValue& result)
{
  XmlRpcServerMethod* method = _server->findMethod(methodName);

  if ( ! method) return false;

	int fd = getfd();

  if(_server->isSessionManagerEnabled())
  { 
    XmlRpcSessionManager* mgr = _server->getSessionManager();
    
    // XmlRpcUtil::log(5, "XmlRpcServerConnection::executeMethod: Checking authorization: needAuth=%d isAuthed=%d isLocal=%d",
    //                method->needAuth(), mgr->isAuthed(fd), mgr->isLocal(fd));

    // 访问的方法需要登录的认证,且当前连接的session不合法
    if( method->needAuth() && _sessionId == -1 && methodName != "Security.Session.login")
    {
      // 获取当前连接的session,返回值非-1,则表示session合法 
      _sessionId = mgr->getSessionId(fd);

      // 如果验证session失败,本地访问也需要认证.
      if(_sessionId == -1 /* && (!mgr->isLocal(fd))*/ )
        throw XmlRpcException("Access denied, authentication required!", XMLRPC_FAULTCODE_101);
    }

    // 原意是当客户端执行方法时,可以先执行一个预先注册的回调.
    // 目前没有使用,且浪费效率
    // mgr->touch(fd);
  }

  XmlRpcUtil::log(5, "XmlRpcServerConnection::executeMethod: Executing method");

  // 生成预置的参数
  generateContext(params);
  params[0]["_thisMethodName"] = methodName;  // 方法名称
  
  method->execute(params, result);

  // Ensure a valid result value
  if ( ! result.valid())
    result = std::string();

  return true;
}
///<<<<<BSTAR

// Execute multiple calls and return the results in an array.
bool
XmlRpcServerConnection::executeMulticall(const std::string& methodName, 
                                         XmlRpcValue& params, XmlRpcValue& result)
{
  if (methodName != SYSTEM_MULTICALL) return false;

  // There ought to be 1 parameter, an array of structs
  if (params.size() != 1 || params[0].getType() != XmlRpcValue::TypeArray)
    throw XmlRpcException(SYSTEM_MULTICALL + ": Invalid argument (expected an array)");

  int nc = params[0].size();
  result.setSize(nc);

  for (int i=0; i<nc; ++i) {

    if ( ! params[0][i].hasMember(METHODNAME) ||
         ! params[0][i].hasMember(PARAMS)) {
      result[i][FAULTCODE] = -1;
      result[i][FAULTSTRING] = SYSTEM_MULTICALL +
              ": Invalid argument (expected a struct with members methodName and params)";
      continue;
    }

    const std::string& methodName = params[0][i][METHODNAME];
    XmlRpcValue& methodParams = params[0][i][PARAMS];

    XmlRpcValue resultValue;
    resultValue.setSize(1);
    try {
      if ( ! executeMethod(methodName, methodParams, resultValue[0]) &&
           ! executeMulticall(methodName, params, resultValue[0]))
      {
        result[i][FAULTCODE] = -1;
        result[i][FAULTSTRING] = methodName + ": unknown method name";
      }
      else
        result[i] = resultValue;

    } catch (const XmlRpcException& fault) {
        result[i][FAULTCODE] = fault.getCode();
        result[i][FAULTSTRING] = fault.getMessage();
    }
  }

  return true;
}


// Create a response from results xml
void
XmlRpcServerConnection::generateResponse(std::string const& resultXml)
{
  const char RESPONSE_1[] = 
    "<?xml version=\"1.0\"?>\r\n"
    "<methodResponse><params><param>\r\n\t";
  const char RESPONSE_2[] =
    "\r\n</param></params></methodResponse>\r\n";

  std::string body = RESPONSE_1 + resultXml + RESPONSE_2;
  std::string header = generateHeader(body);

  _response = header + body;
  XmlRpcUtil::log(7, "XmlRpcServerConnection::generateResponse:\n%s\n", _response.c_str()); 
}

// Prepend http headers
std::string
XmlRpcServerConnection::generateHeader(std::string const& body)
{
  std::string header = 
    "HTTP/1.1 200 OK\r\n"
    "Server: ";
  header += XMLRPC_VERSION;
  header += "\r\n";
  header += "Referer: " + _referer + "\r\n"
    "Content-Type: text/xml\r\n"
    "Content-length: ";

  char buffLen[40];
  sprintf(buffLen,"%d\r\n\r\n", body.size());

  return header + buffLen;
}


void
XmlRpcServerConnection::generateFaultResponse(std::string const& errorMsg, int errorCode)
{
  const char RESPONSE_1[] = 
    "<?xml version=\"1.0\"?>\r\n"
    "<methodResponse><fault>\r\n\t";
  const char RESPONSE_2[] =
    "\r\n</fault></methodResponse>\r\n";

  XmlRpcValue faultStruct;
  faultStruct[FAULTCODE] = errorCode;
  faultStruct[FAULTSTRING] = errorMsg;
  std::string body = RESPONSE_1 + faultStruct.toXml() + RESPONSE_2;
  std::string header = generateHeader(body);

  _response = header + body;
}


void
XmlRpcServerConnection::setUserCookie(const char* pBuff)
{
  /*
    pBuff 格式如下:
    session=818188188; userSpec=9090\r\n...
  */

  const char *pSes = NULL;
  pSes = strstr(pBuff, "session=");
  if(pSes == NULL)
    return;

  pSes += 8;
  char tmpSesStr[16] = "\0";
  for(unsigned int i=0; i<sizeof(tmpSesStr)-1; i++)
  {
    if(pSes[i] < 48 || pSes[i] > 57)  // 非数字字符
      break;
    
    tmpSesStr[i] = pSes[i];
  }
  this->_sessionId = atoi(tmpSesStr);

  // 验证该_sessionId是否已登录
  if( ! _server->getSessionManager()->checkSessionId(this->_sessionId) )
  {
    this->_sessionId = -1;
    return;
  }

  const char *pUser = NULL;
  pUser = strstr(pBuff, "userSpec=");
  if(pUser == NULL)
    return;

  pUser += 9;
  char tmpUserStr[16] = "\0";
  for(unsigned int i=0; i<sizeof(tmpUserStr)-1; i++)
  {
    if(pUser[i] < 48 || pUser[i] > 57)  // 非数字字符
      break;

    tmpUserStr[i] = pUser[i];
  }
  this->_userSpec = atoi(tmpUserStr);

  return;
}
