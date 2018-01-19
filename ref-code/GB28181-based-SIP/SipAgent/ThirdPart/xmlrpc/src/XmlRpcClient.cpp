//depot/nvid/xmlrpc/src/XmlRpcClient.cpp#5 - edit change 989 (ktext)

#include "XmlRpcClient.h"

#include "XmlRpcSocket.h"
#include "XmlRpc.h"

#include <stdio.h>
#include <stdlib.h>
#include <sstream>


using namespace XmlRpc;

// Static data
const char XmlRpcClient::REQUEST_BEGIN[] = 
  "<?xml version=\"1.0\"?>\r\n"
  "<methodCall><methodName>";
const char XmlRpcClient::REQUEST_END_METHODNAME[] = "</methodName>\r\n";
const char XmlRpcClient::PARAMS_TAG[] = "<params>";
const char XmlRpcClient::PARAMS_ETAG[] = "</params>";
const char XmlRpcClient::PARAM_TAG[] = "<param>";
const char XmlRpcClient::PARAM_ETAG[] =  "</param>";
const char XmlRpcClient::REQUEST_END[] = "</methodCall>\r\n";
const char XmlRpcClient::METHODRESPONSE_TAG[] = "<methodResponse>";
const char XmlRpcClient::FAULT_TAG[] = "<fault>";



XmlRpcClient::XmlRpcClient(const char* host, int port, const char* uri/*=0*/)
{
  XmlRpcUtil::log(4, "XmlRpcClient new client: host %s, port %d.", host, port);

  _host = host;
  _port = port;
  if (uri)
    _uri = uri;
  else
    _uri = "/RPC2";
  _connectionState = NO_CONNECTION;
  _executing = false;
  _eof = false;
  _waitTimeout = 30;    
  _retries = 0;
  _sessionId = -1;
  _userSpec = 0;
  // Default to keeping the connection open until an explicit close is done
  setKeepOpen();
}
		
XmlRpcClient::~XmlRpcClient()
{
  close();
}

void 
XmlRpcClient::setUserCookie(int sessionId, int userSpec)
{
  _sessionId = sessionId;
  _userSpec = userSpec;
}


// Close the owned fd
void 
XmlRpcClient::close()
{
  XmlRpcUtil::log(4, "XmlRpcClient::close: fd %d.", getfd());
  _connectionState = NO_CONNECTION;

  _disp.removeSource(this);
  XmlRpcSource::close();

  _disp.exit();
}


// Clear the referenced flag even if exceptions or errors occur.
struct ClearFlagOnExit {
  ClearFlagOnExit(bool& flag) : _flag(flag) {}
  ~ClearFlagOnExit() { _flag = false; }
  bool& _flag;
};

// Execute the named procedure on the remote server.
// Params should be an array of the arguments for the method.
// Returns true if the request was sent and a result received (although the result
// might be a fault).
bool 
XmlRpcClient::execute(const char* method, XmlRpcValue const& params, XmlRpcValue& result)
{
  XmlRpcUtil::log(3, "XmlRpcClient::execute: method %s (_connectionState %d).", method, _connectionState);

  // This is not a thread-safe operation, if you want to do multithreading, use separate
  // clients for each thread. If you want to protect yourself from multiple threads
  // accessing the same client, replace this code with a real mutex.
  if (_executing)
    return false;

  _executing = true;
  _retries = 0;
  ClearFlagOnExit cf(_executing);

  _isFault = false;

  if ( ! setupConnection())
    return false;

  result.clear();

  if ( ! generateRequest(method, params))
    return false;

  double msTime = _waitTimeout;   //Specify -1.0 to process until exit is called 
  _disp.work(msTime);

  if (_connectionState != IDLE || ! parseResponse(result)) 
    return false;

  XmlRpcUtil::log(4, "XmlRpcClient::execute: method %s completed.", method);
  _response = "";
  _retries = 0;
  return true;
}

// XmlRpcSource interface implementation
// Handle server responses. Called by the event dispatcher during execute.
unsigned
XmlRpcClient::handleEvent(unsigned eventType)
{
  if(_retries > 3) return  XmlRpcDispatch::Exception;

  if (eventType == XmlRpcDispatch::Exception)
  {
    if (_connectionState == WRITE_REQUEST && _bytesWritten == 0)
      XmlRpcUtil::error("Error in XmlRpcClient::handleEvent: could not connect to server (%s).", 
                       XmlRpcSocket::getErrorMsg().c_str());
    else
      XmlRpcUtil::error("Error in XmlRpcClient::handleEvent (state %d): %s.", 
                        _connectionState, XmlRpcSocket::getErrorMsg().c_str());
    return 0;
  }

  if (_connectionState == WRITE_REQUEST)
    if ( ! writeRequest()) return 0;

  if (_connectionState == READ_HEADER)
    if ( ! readHeader()) return 0;

  if (_connectionState == READ_RESPONSE)
    if ( ! readResponse()) return 0;

  // This should probably always ask for Exception events too
  return (_connectionState == WRITE_REQUEST) 
        ? XmlRpcDispatch::WritableEvent : XmlRpcDispatch::ReadableEvent;
}

// Create the socket connection to the server if necessary
bool 
XmlRpcClient::setupConnection()
{
    
  if (_connectionState == IDLE || _connectionState == READ_HEADER )
  {
    flush();
    _eof = false;
    _connectionState = IDLE;
  };
  // If an error occurred last time through, or if the server closed the connection, close our end
  if ((_connectionState != NO_CONNECTION && _connectionState != IDLE) || _eof)
    close();

  if (_connectionState == NO_CONNECTION)
  {
    if (! doConnect())
	{
		return false;
	}
  }

  _eof = false;

  // Prepare to write the request
  _connectionState = WRITE_REQUEST;
  _bytesWritten = 0;

  // Notify the dispatcher to listen on this source (calls handleEvent when the socket is writable)
  _disp.removeSource(this);       // Make sure nothing is left over
  _disp.addSource(this, XmlRpcDispatch::WritableEvent | XmlRpcDispatch::Exception);

  return true;
}


// Connect to the xmlrpc server
bool 
XmlRpcClient::doConnect()
{
  int fd = XmlRpcSocket::socket();
  if (fd < 0)
  {
    XmlRpcUtil::error("Error in XmlRpcClient::doConnect: Could not create socket (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }

  XmlRpcUtil::log(3, "XmlRpcClient::doConnect: fd %d.", fd);
  this->setfd(fd);

  // Don't block on connect/reads/writes
  if ( ! XmlRpcSocket::setNonBlocking(fd))
  {
    this->close();
    XmlRpcUtil::error("Error in XmlRpcClient::doConnect: Could not set socket to non-blocking IO mode (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }

 // We use connect() with timeout instead >>>>>BSTAR<<<<<
//if ( ! XmlRpcSocket::connect(fd, _host, _port))
  if ( ! XmlRpcSocket::connect(fd, _host, _port, _waitTimeout))
  {
    this->close();
    XmlRpcUtil::error("Error in XmlRpcClient::doConnect: Could not connect to server (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }
 /*
 // Apply self-detection of reachibility to avoid deadlock 
  if ( !verify())
  {
    this->close();
    XmlRpcUtil::error("Error in XmlRpcClient::doConnect: Could not verify the connection to server (%s).", XmlRpcSocket::getErrorMsg().c_str());
    return false;
  }
 */

  return true;
}

// Encode the request to call the specified method with the specified parameters into xml
bool 
XmlRpcClient::generateRequest(const char* methodName, XmlRpcValue const& params)
{

  std::string body = REQUEST_BEGIN;
  body += methodName;
  body += REQUEST_END_METHODNAME;

  // If params is an array, each element is a separate parameter
  if (params.valid()) {
    body += PARAMS_TAG;
    if (params.getType() == XmlRpcValue::TypeArray)
    {
      for (int i=0; i<params.size(); ++i) {
        body += PARAM_TAG;
        body += params[i].toXml();
        body += PARAM_ETAG;
      }
    }
    else
    {
      body += PARAM_TAG;
      body += params.toXml();
      body += PARAM_ETAG;
    }
      
    body += PARAMS_ETAG;
  }
  body += REQUEST_END;

  std::string header = generateHeader(methodName, body);
  XmlRpcUtil::log(4, "XmlRpcClient::generateRequest: header is %d bytes, content-length is %d.", 
                  header.length(), body.length());

  _request = header + body;
  return true;
}
//Cumulative sequence number for each request which will be sent back in it's response 
//by the server untouched,
//the client later may use it to verfy if the reply is exactly right for the request 
std::string
XmlRpcClient::generateSequence()
// Prepend http headers
{
  static size_t sequence = 1;
  std::ostringstream ss;
  ss << sequence++;
  return ss.str(); 
}
std::string
XmlRpcClient::generateHeader(const char* method, std::string const& body)
{
  std::string header = 
    "POST " + _uri + " HTTP/1.1\r\n"
    "User-Agent: ";
  header += XMLRPC_VERSION;
  header += "\r\nHost: ";
  header += _host;

  char buff[128];
  sprintf(buff,":%d\r\n", _port);
  header += buff;

  //>>>>>BSTAR
  if( getKeepOpen() )
     header += "Connection: Keep-Alive\r\n";
  else
     header += "Connection: Close\r\n";
  _refererClient =  std::string(method) + "/" + generateSequence();
  header += "Referer: " + _refererClient + "\r\n";

  if(_sessionId != -1)
  {
    sprintf(buff, "Cookie: session=%d; userSpec=%d\r\n", _sessionId, _userSpec);
    header += buff;
  }

  //<<<<<BSTAR

  header += "Content-Type: text/xml\r\nContent-length: ";
  sprintf(buff,"%d\r\n\r\n", body.size());


  return header + buff;
}

bool 
XmlRpcClient::writeRequest()
{
  if (_bytesWritten == 0)
    XmlRpcUtil::log(8, "XmlRpcClient::writeRequest :\n%s\n",  _request.c_str());

  // Try to write the request
  if ( ! XmlRpcSocket::nbWrite(this->getfd(), _request, &_bytesWritten)) {
    XmlRpcUtil::error("Error in XmlRpcClient::writeRequest: write error (%s).",XmlRpcSocket::getErrorMsg().c_str());
  XmlRpcSource::close();
  _connectionState = NO_CONNECTION;
  return false;
  }
    
  XmlRpcUtil::log(3, "XmlRpcClient::writeRequest: wrote %d of %d bytes.", _bytesWritten, _request.length());

  // Wait for the result
  if (_bytesWritten == int(_request.length())) {
    _header = "";
    _response = "";
    _connectionState = READ_HEADER;
  }
  return true;
}


// Read the header from the response
bool 
XmlRpcClient::readHeader()
{
  // Read available data
  if ( ! XmlRpcSocket::nbRead(this->getfd(), _header, &_eof) ||
       (_eof && _header.length() == 0)) {
    XmlRpcUtil::error("Error in XmlRpcClient::readHeader: error while reading header (%s) on fd %d.", XmlRpcSocket::getErrorMsg().c_str(), getfd());
    // If we haven't read any data yet and this is a keep-alive connection, the server may
    // have timed out, so we try one more time.
    // Check if the connection is healthy
    if ( !examine() || (getKeepOpen() && _header.length() == 0 )) {
      XmlRpcUtil::log(4, "XmlRpcClient::readHeader: re-trying connection");
      XmlRpcSource::close();
      _connectionState = NO_CONNECTION;
      _eof = false;
      _retries++;
      return setupConnection();
    }
    return false;
  }

  XmlRpcUtil::log(4, "XmlRpcClient::readHeader: client has read %d bytes", _header.length());
  XmlRpcUtil::log(8, "XmlRpcClient::readHeader: response header:\n%s\n", _header.c_str());

  char *hp = (char*)_header.c_str();  // Start of header
  char *ep = hp + _header.length();   // End of string
  char *bp = 0;                       // Start of body
  char *lp = 0;                       // Start of content-length value
  char *rpb = 0;                       // Start of referer 
  char *rpe = 0;                       // End of referer 

  for (char *cp = hp; (bp == 0) && (cp < ep); ++cp) {
    if ((ep - cp > 16) && (strncasecmp(cp, "Content-length: ", 16) == 0))
      lp = cp + 16;
    else if ((ep - cp > 9) && (strncasecmp(cp, "Referer: ", 9) == 0))
	  rpb = cp + 9;
    else if ((ep - cp > 4) && (strncmp(cp, "\r\n\r\n", 4) == 0))
      bp = cp + 4;
    else if ((ep - cp > 2) && (strncmp(cp, "\n\n", 2) == 0))
      bp = cp + 2;
  }

  // If we haven't gotten the entire header yet, return (keep reading)
  if (bp == 0) {
    if (_eof)          // EOF in the middle of a response is an error
    {
      XmlRpcUtil::error("Error in XmlRpcClient::readHeader: EOF while reading header");
      return false;   // Close the connection
    }
    
    return true;  // Keep reading
  }

  //Decode referer
  _refererServer = "";
  if (rpb != 0) {
     rpe = strstr(rpb, "\r\n");
     if(rpe) 
       _refererServer = std::string(rpb, rpe-rpb);
   }
  XmlRpcUtil::log(4, "XmlRpcClient::readHeader: referer is %s.", _refererServer.c_str());
  // Decode content length
  if (lp == 0) {
    XmlRpcUtil::error("Error XmlRpcClient::readHeader: No Content-length specified");
    return false;   // We could try to figure it out by parsing as we read, but for now...
  }

  _contentLength = atoi(lp);
  if (_contentLength <= 0) {
    XmlRpcUtil::error("Error in XmlRpcClient::readHeader: Invalid Content-length specified (%d).", _contentLength);
    return false;
  }
  	
  XmlRpcUtil::log(4, "client read content length: %d", _contentLength);

  // Otherwise copy non-header data to response buffer and set state to read response.
  _response = bp;
  _header = "";   // should parse out any interesting bits from the header (connection, etc)...
  _connectionState = READ_RESPONSE;
  return true;    // Continue monitoring this source
}

    
bool 
XmlRpcClient::readResponse()
{
  // If we dont have the entire response yet, read available data
  if (int(_response.length()) < _contentLength) {
    if ( ! XmlRpcSocket::nbRead(this->getfd(), _response, &_eof)) {
      XmlRpcUtil::error("Error in XmlRpcClient::readResponse: read error (%s).",XmlRpcSocket::getErrorMsg().c_str());
      return false;
    }

    // If we haven't gotten the entire _response yet, return (keep reading)
    if (int(_response.length()) < _contentLength) {
      if (_eof) {
        XmlRpcUtil::error("Error in XmlRpcClient::readResponse: EOF while reading response");
        return false;
      }
      return true;
    }
  }

  // Otherwise, parse and return the result
  XmlRpcUtil::log(3, "XmlRpcClient::readResponse (read %d bytes)", _response.length());

  _connectionState = IDLE;

  return false;    // Stop monitoring this source (causes return from work)
}


// Convert the response xml into a result value
bool 
XmlRpcClient::parseResponse(XmlRpcValue& result)
{
  // Check if the response matches the request
  if(_refererServer != "" && _refererServer != _refererClient) return false;

  // Parse response xml into result
  int offset = 0;
  if ( ! XmlRpcUtil::findTag(METHODRESPONSE_TAG,_response,&offset)) {
    XmlRpcUtil::error("Error in XmlRpcClient::parseResponse: Invalid response - no methodResponse. Response:\n%s", _response.c_str());
    return false;
  }

  // Expect either <params><param>... or <fault>...
  if ((XmlRpcUtil::nextTagIs(PARAMS_TAG,_response,&offset) &&
       XmlRpcUtil::nextTagIs(PARAM_TAG,_response,&offset)) ||
      XmlRpcUtil::nextTagIs(FAULT_TAG,_response,&offset) && (_isFault = true))
  {
    if ( ! result.fromXml(_response, &offset)) {
      XmlRpcUtil::error("Error in XmlRpcClient::parseResponse: Invalid response value. Response:\n%s", _response.c_str());
      _response = "";
      return false;
    }
  } else {
    XmlRpcUtil::error("Error in XmlRpcClient::parseResponse: Invalid response - no param or fault tag. Response:\n%s", _response.c_str());
    _response = "";
    return false;
  }
      
  _response = "";
  return result.valid();
}

///>>>>>BSTAR
//Set wait timeout
void 
XmlRpcClient::setWaitTimeout(int timeout)
{
  _waitTimeout = timeout; 
}

