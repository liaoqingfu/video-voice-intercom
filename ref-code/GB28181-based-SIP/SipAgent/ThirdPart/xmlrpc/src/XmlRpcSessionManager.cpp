/** $Id: //depot/NVS/v2.1/xmlrpc/src/XmlRpcSessionManager.cpp#2 $$DateTime: 2008/11/11 16:56:21 $
 *  @file XmlRpcSessionManager.cpp
 *  @brief A TCP connection status tracking manager for login/logout
 *  @version 0.5
 *  @author Tyhoon<tanf@bstar.com.cn> 
 *  @date 2006-06-22    Create it
 */
/************************************************************
 *  @note
    Copyright 2005, BeiJing Bluestar Corporation, Limited	
 			ALL RIGHTS RESERVED			
 Permission is hereby granted to licensees of BeiJing Bluestar, Inc.	 products to use or abstract this computer program for the sole	 purpose of implementing a product based on BeiJing Bluestar, Inc. products. No other rights to reproduce, use, or disseminate this computer program,whether in part or in whole, are granted. BeiJing Bluestar, Inc. makes no representation or warranties with respect to the performance of this computer program, and specifically disclaims any responsibility for any damages, special or consequential, connected with the use of this program.
 For details, see http://www.bstar.com.cn/ 
***********************************************************/

#include "XmlRpcSessionManager.h"
#include <sys/types.h>
#include <time.h>
#if defined(_WINDOWS)

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

using namespace XmlRpc;
   
XmlRpcSessionManager::XmlRpcSessionManager()
{
#if defined(_WINDOWS)
  InitializeCriticalSection(&_sessionsLock);
#else
  pthread_mutex_init(&_sessionsLock, NULL);
#endif
}

XmlRpcSessionManager::~XmlRpcSessionManager()
{
#if defined(_WINDOWS)
  
  DeleteCriticalSection(&_sessionsLock);
#else
  pthread_mutex_destroy(&_sessionsLock);
#endif
}

XmlRpcSessionManager::Session*
XmlRpcSessionManager::find(int fd)
{
  for (SessionList::iterator it=_sessions.begin(); it!=_sessions.end(); ++it)
    if ((*it)->fd  == fd)
    {
      return (*it);
    }
  return NULL;
}


XmlRpcSessionManager::Session*
XmlRpcSessionManager::findById(int id)
{
  for (SessionList::iterator it=_sessions.begin(); it!=_sessions.end(); ++it)
    if ((*it)->id  == id)
    {
      return (*it);
    }
  return NULL;
}

int
XmlRpcSessionManager::fd2id(int fd)
{
  SessionLock sl(&_sessionsLock);
  Session* s = find(fd);
  if (s) return s->id; 
  
  return -1;
}

int
XmlRpcSessionManager::id2fd(int id)
{
  Session* s = findById(id);
  if (s) return s->fd; 
  
  return -1;
}

void 
XmlRpcSessionManager::open(int fd)
{
  XmlRpcUtil::log(5, "XmlRpcSessionManager::open: Creating %d/%d", fd, _sessions.size());
  Session* s = new Session(fd);
  
  s->id = fd<1 ? 1 : -1;  // sessionÄ¬ÈÏÈ¡-1
  s->authed = false;
  // s->time =  time(NULL);
  // s->timestamp = s->time;
  s->data = NULL;
  SessionLock sl(&_sessionsLock);
  _sessions.push_back(s);
  doEvent(onSessionOpen, s->id);
}

bool 
XmlRpcSessionManager::close(int fd)
{
  XmlRpcUtil::log(5, "XmlRpcSessionManager::close: Removing %d/%d", fd, _sessions.size());

  SessionLock sl(&_sessionsLock);
  for (SessionList::iterator it=_sessions.begin(); it!=_sessions.end(); ++it)
    if ((*it)->fd  == fd) {
      Session* pTmp = *it;
      doEvent(onSessionClose, pTmp->id);
      if(pTmp->data) delete pTmp->data;
      delete pTmp;
      _sessions.erase(it);
      return true;
    }
    return false;
}

/*
bool 
XmlRpcSessionManager::touch(int fd)
{
  Session* s = find(fd);
  if (s) {
    // s->timestamp = time(NULL);
    doEvent(onSessionTouch, s->id);
    return true;
   }
  return false;
}
*/

bool 
XmlRpcSessionManager::login(int fd, int id, SessionItem* data)
{
  if (id < 1)
	{
    XmlRpcUtil::log(2, "XmlRpcSessionManager::login: Invalid session id %d\n", id);
    return false;
  }
  
  SessionLock sl(&_sessionsLock);
  Session* s = find(fd);
  if (s && (!s->authed))
	{
		char client_ip[100]={0}; // modified_by_cp
		sockaddr_in addr;
#ifdef _WINDOWS
		int size = sizeof(addr);
#else
		socklen_t len = sizeof(addr);
#endif
		::getpeername(fd, (PSOCKADDR)&addr, &size);
		sprintf(client_ip, "%d.%d.%d.%d",
		(unsigned char)addr.sin_addr.S_un.S_un_b.s_b1,
		(unsigned char)addr.sin_addr.S_un.S_un_b.s_b2,
		(unsigned char)addr.sin_addr.S_un.S_un_b.s_b3,
		(unsigned char)addr.sin_addr.S_un.S_un_b.s_b4);

		s->ip = client_ip;
    s->id = id;
    s->authed = true;
    s->data = data;
    doEvent(onSessionLogin, id);
    return true;
  }
  return false;
} 

bool 
XmlRpcSessionManager::logout(int fd, int id)
{
  SessionLock sl(&_sessionsLock);
  Session* s = find(fd);
  if (s) {
    s->id = 0;
    s->authed = false;
    if (s->data) { 
      delete s->data;
      s->data = NULL;
    }
    doEvent(onSessionLogout, id);
    return true;
  }
  return false;
} 

int
XmlRpcSessionManager::getSessionId(int fd)
{
  SessionLock sl(&_sessionsLock);
  Session* s = find(fd);
  if (s && s->authed) 
    return s->id;
  return -1;
}

bool
XmlRpcSessionManager::getIpByFd(int fd, std::string& ip)
{
	SessionLock sl(&_sessionsLock);
	Session* s = find(fd);
	if (s && s->authed)
	{
		ip = s->ip;
		return true;
	}
	else
		return false;
}

bool
XmlRpcSessionManager::getIpById(int id, std::string& ip)
{
	SessionLock sl(&_sessionsLock);
	Session* s = findById(id);
	if (s && s->authed)
	{
		ip = s->ip;
		return true;
	}
	else
		return false;
}

bool
XmlRpcSessionManager::GetAllSessionIP(std::list<std::string> &ip_list)
{
	SessionLock sl(&_sessionsLock);
	for (SessionList::iterator it=_sessions.begin(); it!=_sessions.end(); ++it)
	{
		ip_list.push_back((*it)->ip);
	}

	return true;
}

bool 
XmlRpcSessionManager::checkSessionId(int id)
{
  SessionLock sl(&_sessionsLock);
  Session* s = findById(id);
  if(s && s->authed)
    return true;
  else
    return false;
}

#if defined(_WINDOWS)
int  inet_netof(struct in_addr in)
{
  struct Dots { 
    union { unsigned char b1, b2, b3, b4; } bytes;
    unsigned int addr;
  };
  struct Dots x = { 0 };     

	
  x.addr = in.s_addr;    

  if ((x.addr & 0x80) == 0)
    return (x.bytes.b1);

  if ((x.addr & 0x40) == 0)
    return (x.bytes.b1*256 + x.bytes.b2);

  return (x.bytes.b1*256*256 + x.bytes.b2*256 + x.bytes.b3);
}
#endif

bool 
XmlRpcSessionManager::isLocal(int fd)
{
  struct sockaddr_in saddr;
#if defined(_WINDOWS)
  int len = sizeof(saddr);
#else
  socklen_t len = sizeof(saddr);
#endif
  getpeername(fd,(struct sockaddr*)&saddr, &len);
  
  return inet_netof(saddr.sin_addr) == 127;
}

/*
bool
XmlRpcSessionManager::getContext(int id, SessionContext& ctx)
{ 
  //Stored Session variables
  Session* s = findById(id);
  if ( !s )  
    return false;

  ctx.authed = s->authed;
  ctx.time = s->time;
  ctx.timestamp = s->timestamp;
  ctx.data = s->data;

  //Calculated Connection tupple
  struct sockaddr_in saddr;
  int fd = s->fd;
#if defined(_WINDOWS)
  int len = sizeof(saddr);
#else
  socklen_t len = sizeof(saddr);
#endif
  getsockname(fd,(struct sockaddr*)&saddr, &len);
  ctx.serverAddr = inet_ntoa(saddr.sin_addr);
  ctx.serverPort = ntohs(saddr.sin_port);
	
  getpeername(fd,(struct sockaddr*)&saddr, &len);
  ctx.clientAddr = inet_ntoa(saddr.sin_addr);
  ctx.clientPort = ntohs(saddr.sin_port);

  ctx.ssl = false;
  
  return true;
  
} 
*/

void
XmlRpcSessionManager::list(std::vector<int>& ls)
{
  for (SessionList::iterator it=_sessions.begin(); it!=_sessions.end(); ++it)
  {
    ls.push_back((*it)->id);
  }
}

/*
void 
XmlRpcSessionManager::dump()
{
  for (SessionList::iterator it=_sessions.begin(); it!=_sessions.end(); ++it)
  {
    XmlRpcUtil::log(5, "XmlRpcSessionManager::dump: %d\n", (*it)->id);
  }
}
*/

void 
XmlRpcSessionManager::clear()
{
  SessionLock sl(&_sessionsLock);
  _sessions.clear(); 
}


void 
XmlRpcSessionManager::catchEvent(SessionEventType event, SessionEventHandler handler)
{
  _events.push_back(SessionEvent(event, handler));
}


void 
XmlRpcSessionManager::doEvent(SessionEventType event, int id)
{
  
  for (EventList::reverse_iterator it=_events.rbegin(); it!=_events.rend(); ++it)
  {
    if(event == (*it).event) 
    {
      XmlRpcUtil::log(5, "XmlRpcSessionManager::doEvent: id=%d event=%d handler=%p", id, (*it).event, (*it).handler);
      (*it).handler( id );
    }
  }
}
