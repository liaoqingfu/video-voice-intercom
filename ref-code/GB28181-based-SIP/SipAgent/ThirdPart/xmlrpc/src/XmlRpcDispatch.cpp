
#include "XmlRpcDispatch.h"
#include "XmlRpcSocket.h"
#include "XmlRpcSource.h"
#include "XmlRpcUtil.h"

#include <math.h>
#include <sys/timeb.h>

#if !defined(_WINDOWS)
#include <sys/epoll.h>
#include "XmlRpc.h"
#endif


#if defined(_WINDOWS)
# include <winsock2.h>

# define USE_FTIME
# if defined(_MSC_VER)
#  define timeb _timeb
#  define ftime _ftime
# endif
#else
# include <sys/time.h>
# include <signal.h>
#endif  // _WINDOWS


using namespace XmlRpc;


XmlRpcDispatch::XmlRpcDispatch()
{
  _endTime = -1.0;
  _doClear = false;
  _inWork = false;
}


XmlRpcDispatch::~XmlRpcDispatch()
{
}

// Monitor this source for the specified events and call its event handler
// when the event occurs
void
XmlRpcDispatch::addSource(XmlRpcSource* source, unsigned mask)
{
  _sources.push_back(MonitoredSource(source, mask));
}

// Stop monitoring this source. Does not close the source.
void
XmlRpcDispatch::removeSource(XmlRpcSource* source)
{
  for (SourceList::iterator it=_sources.begin(); it!=_sources.end(); it++)
    if (it->getSource() == source)
    {
      it->setErasable(true);
      break;
    }
}


// Modify the types of events to watch for on this source
void 
XmlRpcDispatch::setSourceEvents(XmlRpcSource* source, unsigned eventMask)
{
  for (SourceList::iterator it=_sources.begin(); it!=_sources.end(); ++it)
    if (it->getSource() == source)
    {
      it->setMask(eventMask);
      break;
    }
}


bool 
XmlRpcDispatch::canErase( const MonitoredSource&  ms)
{  
   return ms.getErasable();
}

// Watch current set of sources and process events
void
XmlRpcDispatch::work(double timeout)
{  
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
    // 在多进程模式下,开启epoll模式会存在问题,
    // 因为epoll本身的句柄在fork后会被继承.
    return workByEpoll(timeout);
  }
  else
  {
#endif

    // Select
    return workBySelect(timeout);
  }


}


void
XmlRpcDispatch::workBySelect(double timeout)
{
  // Compute end time
  _endTime = (timeout < 0.0) ? -1.0 : (getTime() + timeout);
  _doClear = false;
  _inWork = true;
  SourceList::iterator it;


  // Only work while there is something to monitor
  while (_sources.size() > 0) {

    // Do sanity check, erase sources marked insane
    _sources.remove_if(canErase);
    if(_sources.size() < 1) break;

    // Construct the sets of descriptors we are interested in
    fd_set inFd, outFd, excFd;
    FD_ZERO(&inFd);
    FD_ZERO(&outFd);
    FD_ZERO(&excFd);

    int maxFd = -1;     // Not used on windows
    for (it=_sources.begin(); it!=_sources.end(); it++) {
      int fd = it->getSource()->getfd();
      if (it->getMask() & ReadableEvent) FD_SET(fd, &inFd);
      if (it->getMask() & WritableEvent) FD_SET(fd, &outFd);
      if (it->getMask() & Exception)     FD_SET(fd, &excFd);
      if (it->getMask() && fd > maxFd)   maxFd = fd;
    }
    //Empty set of fds 
    if ( maxFd < 0 ) break;

    // Check for events
    int nEvents;

#if defined(_WINDOWS)
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    nEvents = select(maxFd+1, &inFd, &outFd, &excFd, &tv);
#else
    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 0;
    sigset_t sigmask;
    sigfillset(&sigmask);
    nEvents = pselect(maxFd+1, &inFd, &outFd, &excFd, &ts, &sigmask);
#endif

    // Check whether end time has passed
    if (0 <= _endTime && getTime() > _endTime) break;

    //Error happened, check if any sources are invalid  
    if (nEvents < 0)
    {
      XmlRpcUtil::error("Error in XmlRpcDispatch::work: error in select (%d) :%s", nEvents, XmlRpcSocket::getErrorMsg().c_str());
      for (it=_sources.begin(); it!=_sources.end(); it++) {
        XmlRpcSource *src = it->getSource();
        if( ! src->examine()) src->close();
      }
      //Invalid fds will be cleanup in next loop
      continue;
    } 

    // 无事件返回,不处理
    if(nEvents == 0)
      continue;

    // Process events
    for (it=_sources.begin(); it != _sources.end(); it++)
    {
      SourceList::iterator thisIt = it;
      XmlRpcSource* src = thisIt->getSource();
      int fd = src->getfd();
      // XmlRpcUtil::log(3, "aaaaaaaaaaaa getKeepOpen %d", src->getKeepOpen());
      unsigned newMask = (unsigned) -1;
      if (fd <= maxFd) {
        // If you select on multiple event types this could be ambiguous
        if (FD_ISSET(fd, &inFd))
          newMask &= src->handleEvent(ReadableEvent);
        if (FD_ISSET(fd, &outFd))
          newMask &= src->handleEvent(WritableEvent);
        if (FD_ISSET(fd, &excFd))
          newMask &= src->handleEvent(Exception);

        if ( ! newMask) {
          thisIt->setErasable(true);  // Stop monitoring this one
          // XmlRpcUtil::log(3, "getKeepOpen %d", src->getKeepOpen());
          if ( ! src->getKeepOpen()) src->close();
        } else if (newMask != (unsigned) -1) 
          thisIt->setMask(newMask);

      }
    }//for

    // Check whether to clear all sources
    if (_doClear)
    {
      clearAll();
      _doClear = false;
      break;
    }

  }//while

  _inWork = false;

}


#if !defined(_WINDOWS)
void
XmlRpcDispatch::workByEpoll(double timeout)
{
  // Compute end time
  _endTime = (timeout < 0.0) ? -1.0 : (getTime() + timeout);
  _doClear = false;
  _inWork = true;
  SourceList::iterator it;

  int epollHandle;
  epollHandle = ::epoll_create(5);
  XmlRpcUtil::log(3, "Use epoll fd %d to start work", epollHandle);
  if(epollHandle == -1)
  {
    return;
  }

  int ers;
  // Only work while there is something to monitor
  while (_sources.size() > 0) {

    // Do sanity check, erase sources marked insane
    _sources.remove_if(canErase);
    if(_sources.size() < 1) break;

    bool emptyFds = true;
    for (it=_sources.begin(); it!=_sources.end(); it++) {
      int fd = it->getSource()->getfd();
      if(fd < 0) continue;

      struct epoll_event ev;
      ev.data.fd = fd;
      ev.events = 0;
      if (it->getMask() & ReadableEvent) ev.events |= EPOLLIN;
      if (it->getMask() & WritableEvent) ev.events |= EPOLLOUT;
      if (it->getMask() & Exception)     ev.events |= EPOLLERR;

      // epoll不同select(每次循环需再次FD_SET),
      // epoll只需更改即可,但如果是新的句柄,则更改失败.
      // 另,epoll无须EPOLL_CTL_DEL,因为所监听的fd关闭后,会自动从epoll中移除
      if((ers = ::epoll_ctl(epollHandle, EPOLL_CTL_MOD, fd, &ev)) == -1)
      {
        if(errno == ENOENT)
          ers = ::epoll_ctl(epollHandle, EPOLL_CTL_ADD, fd, &ev);
      }

      if(ers == -1)
        XmlRpcUtil::log(2, "Use epoll_ctl monitor fd %d failed, error:%s", fd, strerror(errno));
      else
        emptyFds = false;

      // XmlRpcUtil::log(3, "+ fd %d", fd);
    }

    //Empty set of fds 
    if ( emptyFds ) break;

    // Check for events
    epoll_event epollEvents[1];
    int waitms = 1000;
    int status = ::epoll_wait(epollHandle, epollEvents, 1, waitms);
    // Check whether end time has passed
    if (0 <= _endTime && getTime() > _endTime) break;

    //Error happened, check if any sources are invalid  
    if (status < 0 && errno != EINTR)
    {
      XmlRpcUtil::error("Error in XmlRpcDispatch::work: error in epoll (%d) :%s", status, XmlRpcSocket::getErrorMsg().c_str());
      for (it=_sources.begin(); it!=_sources.end(); it++) {
        XmlRpcSource *src = it->getSource();
        if( ! src->examine()) src->close();
      }
      //Invalid fds will be cleanup in next loop
      continue;
    }

    if(status > 0)
    {
      // Process events
      for (it=_sources.begin(); it != _sources.end(); it++)
      {
        SourceList::iterator thisIt = it;
        XmlRpcSource* src = thisIt->getSource();
        int fd = src->getfd();
        unsigned newMask = (unsigned) -1;
        if (fd == epollEvents[0].data.fd) {
          // If you select on multiple event types this could be ambiguous
          if (epollEvents[0].events & EPOLLIN)
            newMask &= src->handleEvent(ReadableEvent);
          if (epollEvents[0].events & EPOLLOUT)
            newMask &= src->handleEvent(WritableEvent);
          if (epollEvents[0].events & EPOLLERR)
            newMask &= src->handleEvent(Exception);

          if ( ! newMask) {
            thisIt->setErasable(true);  // Stop monitoring this one
            if ( ! src->getKeepOpen()) {
              src->close();
              // src->close()在线程未处理完的情况下并不会真正关闭fd,
              // 所以需要手动从epoll中移除
              ::epoll_ctl(epollHandle, EPOLL_CTL_DEL, fd, NULL);
            }
          } else if (newMask != (unsigned) -1) 
            thisIt->setMask(newMask);

        }
      }//for
    }

    // Check whether to clear all sources
    if (_doClear)
    {
      clearAll();
      _doClear = false;
      break;
    }

  }//while

  ::close(epollHandle);
  _inWork = false;
}
#endif

// Exit from work routine. Presumably this will be called from
// one of the source event handlers.
void
XmlRpcDispatch::exit()
{
  _endTime = 0.0;   // Return from work asap
}

// Clear all sources from the monitored sources list
void
XmlRpcDispatch::clearAll()
{
  for (SourceList::iterator it=_sources.begin(); it!=_sources.end(); ++it)
      it->getSource()->close();
  _sources.clear();
}
// Clear all sources from the monitored sources list
void
XmlRpcDispatch::clear()
{
  if (_inWork)
    _doClear = true;  // Finish reporting current events before clearing
  else
    clearAll();
}

double
XmlRpcDispatch::getTime()
{
#ifdef USE_FTIME
  struct timeb	tbuff;

  ftime(&tbuff);
  return ((double) tbuff.time + ((double)tbuff.millitm / 1000.0) +
	  ((double) tbuff.timezone * 60));
#else
  struct timeval	tv;
  struct timezone	tz;

  gettimeofday(&tv, &tz);
  return (tv.tv_sec + tv.tv_usec / 1000000.0);
#endif /* USE_FTIME */
}


