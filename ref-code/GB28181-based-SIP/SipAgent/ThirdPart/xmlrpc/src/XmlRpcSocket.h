#ifndef _XMLRPCSOCKET_H_
#define _XMLRPCSOCKET_H_
//
// XmlRpc++ Copyright (c) 2002-2003 by Chris Morley
//
#if defined(_MSC_VER)
# pragma warning(disable:4786)    // identifier was truncated in debug info
#endif


#ifndef MAKEDEPEND
# include <string>
#if defined(_WINDOWS)
# include <stdio.h>
# include <winsock2.h>
# include <errno.h>
//# pragma lib(WS2_32.lib)

# define EINPROGRESS	WSAEINPROGRESS
# define EWOULDBLOCK	WSAEWOULDBLOCK
# define ETIMEDOUT	    WSAETIMEDOUT
#else
extern "C" {
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <errno.h>
# include <fcntl.h>
#include <arpa/inet.h>
}
#endif  // _WINDOWS

#endif // MAKEDEPEND


namespace XmlRpc {

  //! A platform-independent socket API.
  class XmlRpcSocket {
  public:

    //! Creates a stream (TCP) socket. Returns -1 on failure.
    static int socket();

    //! Closes a socket.
    static void close(int socket);


    //! Sets a stream (TCP) socket to perform non-blocking IO. Returns false on failure.
    static bool setNonBlocking(int socket);

    //! Read text from the specified socket. Returns false on error.
    static bool nbRead(int socket, std::string& s, bool *eof);

    //! Write text to the specified socket. Returns false on error.
    //! ms是阻塞最大等待的时间毫秒,0表示如需阻塞直接返回
    //! -1表示永久阻塞
    static bool nbWrite(int socket, std::string& s, int *bytesSoFar, int ms=0);


    // The next four methods are appropriate for servers.

    //! Allow the port the specified socket is bound to to be re-bound immediately so 
    //! server re-starts are not delayed. Returns false on failure.
    static bool setReuseAddr(int socket);

    //! Winsock  initializer
    static void initSock();

    //! Winsock  finalizer
    static void finiSock();

    //! Check if the file discriptor is valid
    static bool examine(int socket);  

    //! Cleanup receival buffer 
    static void flush(int socket);  

    //! server Bind to specified device
    static bool setBindDevice(int socket, const char* device);  

    //! recv timeout
    static bool setReadTimeout(int socket, int timeout);  

    //! send timeout
    static bool setWriteTimeout(int socket, int timeout);  

    //! server heart-beating
    static bool setKeepAlive(int socket);

    //! Bind to a specified port
    static bool bind(int socket, int port);

    //! Set socket in listen mode
    static bool listen(int socket, int backlog);

    //! Accept a client connection request
    static int accept(int socket);


    //! Connect a socket to a server (from a client)
    static bool connect(int socket, std::string& host, int port);

    //! Connect a socket to a server (from a client) with timeout
    static bool connect(int socket, std::string& host, int port, int timeout);

    //! Returns last errno
    static int getError();

    //! Returns message corresponding to last error
    static std::string getErrorMsg();

    //! Returns message corresponding to error
    static std::string getErrorMsg(int error);
  };

} // namespace XmlRpc

#endif
