/**
*  @file XmlRpcThreads.h
*  @brief A simple thread pool manager
*  @version 0.1
*  @author yulichun<yulc@bstar.com.cn> 
*  @date 2009-12-17    Create it
*/
/************************************************************
*  @note
Copyright 2005, BeiJing Bluestar Corporation, Limited	
ALL RIGHTS RESERVED			
Permission is hereby granted to licensees of BeiJing Bluestar, Inc.	 products to use or abstract this computer program for the sole	 purpose of implementing a product based on BeiJing Bluestar, Inc. products. No other rights to reproduce, use, or disseminate this computer program,whether in part or in whole, are granted. BeiJing Bluestar, Inc. makes no representation or warranties with respect to the performance of this computer program, and specifically disclaims any responsibility for any damages, special or consequential, connected with the use of this program.
For details, see http://www.bstar.com.cn/ 
***********************************************************/

#ifndef _XMLRPCTHREADS_H
#define _XMLRPCTHREADS_H
//


#if defined(_MSC_VER)
# pragma warning(disable:4786)    // identifier was truncated in debug info
#endif


#ifndef MAKEDEPEND
#include <list>

#if defined(_WINDOWS)
#include <windows.h>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

using namespace std;

#endif


namespace XmlRpc {

  class XmlRpcServerConnection;
  class XmlRpcServer;

  class XmlRpcThreads {



  public:
    int initThreads(int num);
    
    int pushTask(XmlRpcServerConnection*);
    int execTask();


  private:
#if defined(_WINDOWS)
    static DWORD WINAPI _threadWork(LPVOID pArgs);
#else
    static void* _threadWork(void* pArgs);
#endif
    
    // 禁止拷贝和复制
    XmlRpcThreads(const XmlRpcThreads&);
    XmlRpcThreads& operator=(const XmlRpcThreads&);

    // 禁止声明对象,除了friend
    XmlRpcThreads();
    ~XmlRpcThreads();
    friend class XmlRpcServer;

    // 待处理的连接队列
    list<XmlRpcServerConnection*> _mConnection;

#if defined(_WINDOWS)
    HANDLE _mSem;
    CRITICAL_SECTION _mcs;
#else
    sem_t _mSem;                    // 唤醒线程的信号量

    // 连接队列锁
    pthread_mutex_t _mConnectionLock;


#endif

  };


}





#endif

