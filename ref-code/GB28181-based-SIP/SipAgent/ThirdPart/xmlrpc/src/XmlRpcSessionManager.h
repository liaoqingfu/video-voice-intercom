/** $Id: //depot/NVS/v2.1/xmlrpc/src/XmlRpcSessionManager.h#2 $$DateTime: 2008/11/11 16:56:21 $
 *  @file XmlRpcSessionManager.h
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

#ifndef _XMLRPCSESSIONMANAGER_H
#define _XMLRPCSESSIONMANAGER_H
//
// XmlRpc++ Copyright (c) 2006 by Tan Feng
//
#if defined(_MSC_VER)
# pragma warning(disable:4786)    // identifier was truncated in debug info
#endif


#include "XmlRpcUtil.h"

#ifndef MAKEDEPEND
# include <list>
# include <vector>

#if defined(_WINDOWS)
#include <winsock2.h>
#else
#include <pthread.h>
#endif

#endif

namespace XmlRpc {

  struct SessionItem{};

  /*
  struct SessionContext 
  {
      std::string clientAddr;
      unsigned short clientPort;
      std::string serverAddr;
      unsigned short serverPort;
      bool ssl;
      bool authed;
      time_t time;
      time_t timestamp;
      SessionItem* data;
  };
  */

  enum SessionEventType 
  { 
    onSessionOpen,   // 当有客户端连接成功后的事件
    onSessionClose,  // 断开连接
    onSessionLogin,  // 客户端注册session后的事件,指在完成登录后.
    onSessionLogout, // 注销
    onSessionTouch   // 该项已无效,如需开启,需要修改 XmlRpcServerConnection::executeMethod()内的代码
  }; 

  typedef void (* SessionEventHandler)(int id);
   
  class XmlRpcSessionManager {
  public:
    //! Constructor
    XmlRpcSessionManager();
    ~XmlRpcSessionManager();

    // 创建/删除一个的session元素,指定socket fd.
    void open(int fd);
    bool close(int fd);

    // bool touch(int fd);
    // 登录/注销某session
    bool login(int fd, int id, SessionItem* data /* 该参数失效 */); 
    bool logout(int fd, int id); 

    // 通过socket fd获取登录认证后的session id.
    // 如返回-1表示不存在,或者未经过认证.
    int getSessionId(int fd);

		// 通过socket 获取登录认证后的client ip.
		bool getIpByFd(int fd, std::string& ip); // modified_by_cp

		// 通过SessionID 获取登录认证后的client ip.
		bool getIpById(int id, std::string& ip); // modified_by_cp

		// 获得所有session的ip用于发送udp报警信息给客户端
		bool GetAllSessionIP(std::list<std::string> &ip_list); // modified_by_cp

    // 检测某session id 是否已登录认证.
    bool checkSessionId(int id);
      
    // 检测socket fd的对端是否是本地主机.
    bool isLocal(int fd); 
    
    // bool getContext(int id, SessionContext& ctx); 
    void list(std::vector<int>& ls);
    int  id2fd(int id);
    int  fd2id(int fd);

    // 注册某事件的回调
    void catchEvent(SessionEventType event, SessionEventHandler handler);

    // void dump();
    void clear(); 

   private:
    struct Session
    {
      Session():fd(-1),id(0),authed(false),data(NULL){}
      Session(int fd):fd(fd),id(0),authed(false),data(NULL){}
      int fd;             // socket fd
      int id;             // 登录后的session号
      bool authed;        // 是否已完成登录的认证
			std::string ip; // client ip // modified_by_cp
      // time_t time;
      // time_t timestamp;
      SessionItem* data;  // 无用
    };
    struct SessionEvent
    { 
      SessionEvent(SessionEventType e, SessionEventHandler h): event(e), handler(h){}
      SessionEventType event;
      SessionEventHandler handler;
    };

    // A list of sessions to monitor
    typedef std::list< Session* > SessionList; 
    // A list of callback handlers on session close
    typedef std::vector< SessionEvent > EventList; 

    // Sessions being monitored
    SessionList _sessions;

#if defined(_WINDOWS)
    // win平台上锁未实现
    CRITICAL_SECTION _sessionsLock;
    class SessionLock
    {
    public:
      SessionLock(LPCRITICAL_SECTION lpcs ):_lpcs(lpcs) {EnterCriticalSection(_lpcs);}
      ~SessionLock(){LeaveCriticalSection(_lpcs);}
    private:
      LPCRITICAL_SECTION _lpcs;
    };

#else
    pthread_mutex_t _sessionsLock;

    // 锁的自释放封装类
    class SessionLock
    {
    public:
      SessionLock(pthread_mutex_t* mutex) : ml(mutex) { XmlRpcUtil::getLock(ml); }
      ~SessionLock() { XmlRpcUtil::freeLock(ml); }

    private:
      pthread_mutex_t *ml;
    };
#endif



    // Session events being monitored
    EventList _events;

    Session* find(int fd);      // 通过socket fd查找
    Session* findById(int id);  // 通过sessionId查找
    void doEvent(SessionEventType event, int id);


 }; //class SessionManager

} // namespace XmlRpc

#endif  // _XMLRPCSSIONMANAGER_H_
