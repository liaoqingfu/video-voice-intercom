
#include "XmlRpcSocket.h"
#include "XmlRpcUtil.h"

#include <string.h>

#if !defined(_WINDOWS)
#include <sys/epoll.h>
#include "XmlRpc.h"
#endif


using namespace XmlRpc;

// These errors are not considered fatal for an IO operation; the operation will be re-tried.
static inline bool
nonFatalError()
{
  int err = XmlRpcSocket::getError();
  return (err == EINPROGRESS || err == EAGAIN || err == EWOULDBLOCK || err == EINTR);
}




void 
XmlRpcSocket::initSock()
{
#if defined(_WINDOWS)
    WORD wVersionRequested = MAKEWORD( 2, 2 );
    WSADATA wsaData;
    WSAStartup(wVersionRequested, &wsaData);
#endif
}

void 
XmlRpcSocket::finiSock()
{
#if defined(_WINDOWS)
    WSACleanup();
#endif
}


int
XmlRpcSocket::socket()
{
  return (int) ::socket(AF_INET, SOCK_STREAM, 0);
}


void
XmlRpcSocket::close(int fd)
{
  XmlRpcUtil::log(4, "XmlRpcSocket::close: fd %d.", fd);
#if defined(_WINDOWS)
  WSACancelBlockingCall();
  closesocket(fd);
#else
  ::close(fd);
#endif // _WINDOWS
}




bool
XmlRpcSocket::setNonBlocking(int fd)
{
#if defined(_WINDOWS)
  unsigned long flag = 1;
  return (ioctlsocket((SOCKET)fd, FIONBIO, &flag) == 0);
#else
  return (fcntl(fd, F_SETFL, O_NONBLOCK) == 0);
#endif // _WINDOWS
}


bool
XmlRpcSocket::setReuseAddr(int fd)
{
  // Allow this port to be re-bound immediately so server re-starts are not delayed
  int sflag = 1;
  return (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&sflag, sizeof(sflag)) == 0);
}
///>>>>>BSTAR
//Test if the socket is valid
bool
XmlRpcSocket::examine(int fd)
{
//fd Validity test
    int optval = 1;
#if defined(_WINDOWS)
    int optlen = sizeof(int);	
#else
    socklen_t optlen = sizeof(int);	
#endif
    int ret = getsockopt(fd, SOL_SOCKET, SO_ERROR, (char*)&optval, &optlen); 
   
    XmlRpcUtil::log(5, "XmlRpcSocket::examine getsockopt ret %d", ret);
    if( !ret ) return false;


    /*
    如果win平台,使终使用select,
    linux平台则检测设置项isUseEpoll()
    */
#if defined(_WINDOWS)
    if(1)
    {
#else
    if(isUseEpoll())
    {
      int epollHandle;
      epollHandle = ::epoll_create(1);

      struct epoll_event ev;
      ev.data.fd = fd;
      ev.events = EPOLLOUT;
      if(::epoll_ctl(epollHandle, EPOLL_CTL_ADD, fd, &ev) == -1)
        XmlRpcUtil::log(2, "Use epoll_ctl monitor fd %d failed, error:%s", fd, strerror(errno));

      epoll_event epollEvents[1];
      int status = ::epoll_wait(epollHandle, epollEvents, 1, 0);
      ::close(epollHandle);
      return (status > 0);
    }
    else
    {

#endif

      // Further test, we assume all socket should always be writable
      struct timeval tv = { 0, 0 };

      fd_set fdset; 
      FD_ZERO(&fdset); 
      FD_SET(fd, &fdset); 
      int status = select(fd+1, NULL, &fdset, NULL, &tv);  
      XmlRpcUtil::log(5, "XmlRpcSocket::flush: select writing %d", status);
      return (status > 0);
    }
}

//Cleanup dirty data in read buffer 
void
XmlRpcSocket::flush(int fd)
{
  int status;

  /*
  如果win平台,使终使用select,
  linux平台则检测设置项isUseEpoll()
  */
#if defined(_WINDOWS)
  if(1)
  {
#else
  if(isUseEpoll())
  {
    // Epoll
    int epollHandle;
    epollHandle = ::epoll_create(1);

    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(::epoll_ctl(epollHandle, EPOLL_CTL_ADD, fd, &ev) == -1)
      XmlRpcUtil::log(2, "Use epoll_ctl monitor fd %d failed, error:%s", fd, strerror(errno));

    epoll_event epollEvents[1];
    status = ::epoll_wait(epollHandle, epollEvents, 1, 0);
    ::close(epollHandle);
    if(status <=0) return;

  }
  else
  {
#endif

    // Select
    struct timeval tv = { 0, 0 };

    fd_set fdset; 
    FD_ZERO(&fdset); 
    FD_SET(fd, &fdset); 
    status = select(fd+1, &fdset, NULL, NULL, &tv);  
    XmlRpcUtil::log(5, "XmlRpcSocket::flush: select reading %d", status);
    if (status <= 0) return; 

  }
    
    XmlRpcUtil::log(5, "XmlRpcSocket::flush: exhausting dirty data in socket %d", fd);
    const int READ_SIZE = 4096;   
    char readBuf[READ_SIZE];
#if defined(_WINDOWS)
    while((recv(fd, readBuf, READ_SIZE-1, 0)) > 0 );
#else
    while((read(fd, readBuf, READ_SIZE-1)) > 0 );
#endif
}

bool
XmlRpcSocket::setBindDevice(int fd, const char* device)
{
#if defined(_WINDOWS)
  return true;
#else
  return (setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, device, strlen(device)) == 0);
#endif
}

bool
XmlRpcSocket::setReadTimeout(int fd, int timeout)
{

#if defined(_WINDOWS)
  int val = timeout;

  return (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&val, sizeof(val)) == 0);
#else
  struct timeval tv;
  
  tv.tv_sec = timeout;
  tv.tv_usec = 0;
  return (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == 0);
#endif
}

bool
XmlRpcSocket::setWriteTimeout(int fd, int timeout)
{
#if defined(_WINDOWS)
  int val = timeout;

  return (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&val, sizeof(val)) == 0);
#else
  struct timeval tv;
  
  tv.tv_sec = timeout;
  tv.tv_usec = 0;
  return (setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) == 0);
#endif
}

bool
XmlRpcSocket::setKeepAlive(int fd)
{
  int sflag = 1;
  return (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (const char *)&sflag, sizeof(sflag)) == 0);

}
///<<<<<BSTAR

// Bind to a specified port
bool 
XmlRpcSocket::bind(int fd, int port)
{
  struct sockaddr_in saddr;
  memset(&saddr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);
  saddr.sin_port = htons((u_short) port);
  return (::bind(fd, (struct sockaddr *)&saddr, sizeof(saddr)) == 0);
}


// Set socket in listen mode
bool 
XmlRpcSocket::listen(int fd, int backlog)
{
  return (::listen(fd, backlog) == 0);
}


int
XmlRpcSocket::accept(int fd)
{
  struct sockaddr_in addr;
#if defined(_WINDOWS)
  int
#else
  socklen_t
#endif
    addrlen = sizeof(addr);

 return ::accept(fd, (struct sockaddr*)&addr, &addrlen);
  
}


    
// Connect a socket to a server (from a client)
bool
XmlRpcSocket::connect(int fd, std::string& host, int port)
{
  struct sockaddr_in saddr;
  memset(&saddr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;

#if defined(_WINDOWS)
  struct hostent *hp = gethostbyname(host.c_str());
  if (hp == 0) return false;
#else  	
  char buf[8192];
  struct hostent hostinfo;
  struct hostent *hp = NULL;
  int herrno;

  if(gethostbyname_r(host.c_str(), &hostinfo, buf, 8192, &hp, &herrno))
    return false;
  if (hp == NULL) 
    return false;
#endif  

  saddr.sin_family = hp->h_addrtype;
  memcpy(&saddr.sin_addr, hp->h_addr, hp->h_length);
  saddr.sin_port = htons((u_short) port);

  // For asynch operation, this will return EWOULDBLOCK (windows) or
  // EINPROGRESS (linux) and we just need to wait for the socket to be writable...
  int result = ::connect(fd, (struct sockaddr *)&saddr, sizeof(saddr));
  return result == 0 || nonFatalError();
}

///>>>>>BSTAR
// Connect a socket to a server (from a client) with timeout
bool
XmlRpcSocket::connect(int fd, std::string& host, int port, int timeout)
{
  struct sockaddr_in saddr;
  memset(&saddr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;

#if defined(_WINDOWS)
  struct hostent *hp = gethostbyname(host.c_str());
  if (hp == 0) return false;
#else  	
  char buf[8192];
  struct hostent hostinfo;
  struct hostent *hp = NULL;
  int herrno;

  if(gethostbyname_r(host.c_str(), &hostinfo, buf, 8192, &hp, &herrno))
    return false;
  if (hp == NULL) 
    return false;
#endif    
    
  saddr.sin_family = hp->h_addrtype;
  memcpy(&saddr.sin_addr, hp->h_addr, hp->h_length);
  saddr.sin_port = htons((u_short) port);

  //Set non-blocking 
#if defined(_WINDOWS)
  unsigned long oldflag = 0;  //??? I dont know how to get current flag on Windows
  unsigned long newflag = 1;
  ioctlsocket((SOCKET)fd, FIONBIO, &newflag);
#else
  int oldflag = fcntl(fd, F_GETFL, NULL); 
  int newflag = oldflag | O_NONBLOCK; 
  fcntl(fd, F_SETFL, newflag); 
#endif

  bool result = false;
  do {
    // For asynch operation, this will return EWOULDBLOCK (windows) or
    // EINPROGRESS (linux) and we just need to wait for the socket to be writable...
    int status = ::connect(fd, (struct sockaddr *)&saddr, sizeof(saddr));

    //Connection established OK
    if ( !status ) {
       result = true;
       break;
    }

    //Test if the socket is readable 
#if defined(_WINDOWS)
    if (WSAGetLastError() != EWOULDBLOCK) break; 
#else
    if (errno != EINPROGRESS) break; 
#endif


    /*
    如果win平台,使终使用select,
    linux平台则检测设置项isUseEpoll()
    */
#if defined(_WINDOWS)
    if(1)
    {
#else
    if(isUseEpoll())
    {
      // Epoll
      int epollHandle;
      epollHandle = ::epoll_create(1);

      struct epoll_event ev;
      ev.data.fd = fd;
      ev.events = EPOLLOUT;
      if(::epoll_ctl(epollHandle, EPOLL_CTL_ADD, fd, &ev) == -1)
        XmlRpcUtil::log(2, "Use epoll_ctl monitor fd %d failed, error:%s", fd, strerror(errno));

      epoll_event epollEvents[1];
      int waitms = timeout*1000;
      int status = ::epoll_wait(epollHandle, epollEvents, 1, waitms);
      ::close(epollHandle);
      if (status <= 0) break;
      if (fd == epollEvents[0].data.fd) {
        result = true;
        XmlRpcUtil::log(5, "XmlRpcSocket::connect: epoll writing ready");
        break;
      }
    }
    else
    {

#endif

      // Select
      struct timeval tv;
      tv.tv_sec = timeout; 
      tv.tv_usec = 0; 
      fd_set fdset; 

      FD_ZERO(&fdset); 
      FD_SET(fd, &fdset); 
      status = select(fd+1, NULL, &fdset, NULL, &tv);  
      XmlRpcUtil::log(5, "XmlRpcSocket::connect: select writing %d", status);
      if (status <= 0) break;
      if (FD_ISSET(fd, &fdset)) {
        result = true;
        XmlRpcUtil::log(5, "XmlRpcSocket::connect: select writing ready");
        break;
      }

    }

    int optval = 1;
#if defined(_WINDOWS)
    int optlen = sizeof(int);	
#else
    socklen_t optlen = sizeof(int);	
#endif
    setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char*)&optval, optlen);
    //if (WSAGetLastError() == EINPROGRESS) break; 
    optval = 0;
    optlen = sizeof(int);
    getsockopt(fd, SOL_SOCKET, SO_ERROR, (char*)&optval, &optlen); 
    if(optval) break;

    result = true;
  } while (false);

  //Restore fd's old flag 
#if defined(_WINDOWS)
#else
  fcntl(fd, F_SETFL, oldflag); 
#endif

  return result;
}
///<<<<<BSTAR


// Read available text from the specified socket. Returns false on error.
bool 
XmlRpcSocket::nbRead(int fd, std::string& s, bool *eof)
{
  const int READ_SIZE = 4096;   // Number of bytes to attempt to read at a time
  char readBuf[READ_SIZE];

  bool wouldBlock = false;
  *eof = false;

  while ( ! wouldBlock && ! *eof) {
#if defined(_WINDOWS)
    int n = recv(fd, readBuf, READ_SIZE-1, 0);
#else
    int n = read(fd, readBuf, READ_SIZE-1);
#endif
    XmlRpcUtil::log(8, "XmlRpcSocket::nbRead: read/recv returned %d.", n);

    if (n > 0) {
      readBuf[n] = 0;
      s.append(readBuf, n);
    } else if (n == 0) {
      *eof = true;
    } else if (nonFatalError()) {
      wouldBlock = true;
    } else {
      XmlRpcUtil::error("XmlRpcSocket::nbRead: %s", getErrorMsg().c_str());
      *eof = true;
      return false;   // Error
    }
  }
  return true;
}


// Write text to the specified socket. Returns false on error.
bool 
XmlRpcSocket::nbWrite(int fd, std::string& s, int *bytesSoFar, int ms)
{
  int nToWrite = int(s.length()) - *bytesSoFar;
  char *sp = const_cast<char*>(s.c_str()) + *bytesSoFar;
  bool wouldBlock = false;

#if !defined(_WINDOWS)
  // use select only.
  struct timeval tv;
  if(ms > 0)
  {
    tv.tv_sec = ms/1000;
    tv.tv_usec = (ms%1000)*1000;
  }
#endif

  while ( nToWrite > 0 && ! wouldBlock ) {
#if defined(_WINDOWS)
    int n = send(fd, sp, nToWrite, 0);
#else
    int n = write(fd, sp, nToWrite);
#endif
    XmlRpcUtil::log(8, "XmlRpcSocket::nbWrite: send/write returned %d.", n);

    if (n > 0) {
      sp += n;
      *bytesSoFar += n;
      nToWrite -= n;
    } else if (nonFatalError()) {
      wouldBlock = true;

#if !defined(_WINDOWS)
      if(isUseEpoll())
      {
        // 等待10ms重试一下
        // epoll没有使用同select的超时方式,是因为epoll不是递减时间值.
        ms -= 10;
        if(ms <= 0)
        {
          *bytesSoFar = 0;
          return false;
        }

        // Epoll
        int epollHandle;
        epollHandle = ::epoll_create(1);

        struct epoll_event ev;
        ev.data.fd = fd;
        ev.events = EPOLLOUT;
        if(::epoll_ctl(epollHandle, EPOLL_CTL_ADD, fd, &ev) == -1)
          XmlRpcUtil::log(2, "Use epoll_ctl monitor fd %d failed, error:%s", fd, strerror(errno));

        epoll_event epollEvents[1];
        int status = ::epoll_wait(epollHandle, epollEvents, 1, 10 /* 10 ms*/);
        ::close(epollHandle);
        if (status < 0 ) {
          *bytesSoFar = 0;
          return false;
        }

        wouldBlock = false;
      }
      else
      {
        // socket需要阻塞,等待可写事件发生.
        if(ms > 0) {
          fd_set outFd;
          FD_ZERO(&outFd);
          FD_SET(fd, &outFd);
          int rs = select(fd+1, NULL, &outFd, NULL, &tv);
          if(rs <= 0) {
            *bytesSoFar = 0;
            return false;
          }
          wouldBlock = false;
        }
      }
#endif

    } else {
      XmlRpcUtil::error("XmlRpcSocket::nbWrite: %s", getErrorMsg().c_str()); 
      *bytesSoFar = 0; 
      return false;   // Error
    }
  }
  return true;
}


// Returns last errno
int 
XmlRpcSocket::getError()
{
#if defined(_WINDOWS)
  return WSAGetLastError();
#else
  return errno;
#endif
}


// Returns message corresponding to last errno
std::string 
XmlRpcSocket::getErrorMsg()
{
  return getErrorMsg(getError());
}

// Returns message corresponding to errno... well, it should anyway
std::string 
XmlRpcSocket::getErrorMsg(int error)
{
  char err[60];
#if defined(_WINDOWS)
  snprintf(err,sizeof(err),"error %d", error);
#else
  snprintf(err,sizeof(err),"error %d: %s", error, strerror(error));
#endif
  return std::string(err);
}


