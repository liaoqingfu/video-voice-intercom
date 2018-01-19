#ifndef _XMLRPC_H_
#define _XMLRPC_H_
//
// XmlRpc++ Copyright (c) 2002-2003 by Chris Morley
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
// 

#if defined(_MSC_VER)
# pragma warning(disable:4786)    // identifier was truncated in debug info
#endif

#ifndef MAKEDEPEND
# include <string>
#endif

#include "XmlRpcClient.h"
#include "XmlRpcException.h"
#include "XmlRpcServer.h"
#include "XmlRpcServerMethod.h"
#include "XmlRpcValue.h"
#include "XmlRpcUtil.h"

namespace XmlRpc {


  // 此函数类型是指由外部指定的日志输出函数
  // 用在bc3.0服务器各应用程序中的xmlrpc库的日志和错误输出
  typedef void (*ExtendPrintf)(short level, short type, const char* file, const char* function,
                       int line, const char* fmt, ...);

  //! An interface allowing custom handling of error message reporting.
  class XmlRpcErrorHandler {
  public:
    //! Returns a pointer to the currently installed error handling object.
    static XmlRpcErrorHandler* getErrorHandler() 
    { return _errorHandler; }

    //! Specifies the error handler.
    static void setErrorHandler(XmlRpcErrorHandler* eh)
    { _errorHandler = eh; }

    //! Report an error. Custom error handlers should define this method.
    virtual void error(const char* msg) = 0;

    virtual ~XmlRpcErrorHandler() {};

  protected:
    static XmlRpcErrorHandler* _errorHandler;
  };

  //! An interface allowing custom handling of informational message reporting.
  class XmlRpcLogHandler {
  public:
    //! Returns a pointer to the currently installed message reporting object.
    static XmlRpcLogHandler* getLogHandler() 
    { return _logHandler; }

    //! Specifies the message handler.
    static void setLogHandler(XmlRpcLogHandler* lh)
    { _logHandler = lh; }

    //! Returns the level of verbosity of informational messages. 0 is no output, 5 is very verbose.
    static int getVerbosity() 
    { return _verbosity; }

    //! Specify the level of verbosity of informational messages. 0 is no output, 5 is very verbose.
    static void setVerbosity(int v) 
    { _verbosity = v; }

    //! Returns the outputs of informational messages. 
    static int getMonitor() 
    { return _monitor; }

    //! Specify the outputs of informational messages
    static void setMonitor(int m) 
    { _monitor = m; }

    static ExtendPrintf getExtendPrintf()
    {
      return extendPrintf;
    }

    static void setExtendPrintf(ExtendPrintf pFun)
    {
      extendPrintf = pFun;
    }

    //! Output a message. Custom error handlers should define this method.
    virtual void log(int level, const char* msg) = 0;

    virtual ~XmlRpcLogHandler() {};

  protected:
    static XmlRpcLogHandler* _logHandler;
    static int _verbosity;
    static int _monitor;
    static ExtendPrintf extendPrintf;
  };

  //! Returns log message verbosity. This is short for XmlRpcLogHandler::getVerbosity()
  int getVerbosity();
  //! Sets log message verbosity. This is short for XmlRpcLogHandler::setVerbosity(level)
  void setVerbosity(int level);
  //! Returns log message output. This is short for XmlRpcLogHandler::getMonitor()
  int getMonitor();
  //! Sets log message verbosity. This is short for XmlRpcLogHandler::setMonitor(m)
  void setMonitor(int m);
  

  //! use select or epoll, don't access this directly.
  extern bool _epoll;

  //! Set epoll, use select by default.
  //! if enabled 'child spawn', don't set epoll
  void setUseEpoll();
  bool isUseEpoll();

  ExtendPrintf getExtendPrintf();
  void setExtendPrintf(ExtendPrintf pFun);

  //! Version identifier
  extern const char XMLRPC_VERSION[];

} // namespace XmlRpc

#endif // _XMLRPC_H_
