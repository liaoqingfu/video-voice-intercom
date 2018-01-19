
#include "XmlRpcUtil.h"
#include "XmlRpcThreads.h"

#include "XmlRpcServerConnection.h"
#include <errno.h>

namespace XmlRpc {

#if defined(_WINDOWS)
XmlRpcThreads::XmlRpcThreads()
{
   InitializeCriticalSection(&_mcs);
   _mSem = CreateSemaphore(NULL,0,100,NULL);

}

XmlRpcThreads::~XmlRpcThreads()
{
  DeleteCriticalSection(&_mcs);
}


int 
XmlRpcThreads::initThreads(int num)
{
  if(num <= 0)
    return -1;
	HANDLE threadHandle;
  for (int i=0; i<num; i++) {
    
    if ((threadHandle = CreateThread(NULL,1024*1024*5,_threadWork,(LPVOID )this,0,NULL)) == NULL)
      return -1; 
    CloseHandle(threadHandle);
  }
  
  return 0;
}


DWORD WINAPI  
XmlRpcThreads::_threadWork(LPVOID pArgs)
{
  XmlRpcThreads* pThis = (XmlRpcThreads*)pArgs;
  pThis->execTask();

  return 0;
}


int 
XmlRpcThreads::pushTask(XmlRpcServerConnection* connTask)
{

  EnterCriticalSection(&_mcs);
  _mConnection.push_back(connTask);
  LeaveCriticalSection(&_mcs);

  // 唤醒一个线程
	ReleaseSemaphore(_mSem,1,NULL);

  return 0;
}

int 
XmlRpcThreads::execTask()
{
  while(1) {
    // 所有线程阻塞中,等待唤醒
    WaitForSingleObject(_mSem,INFINITE);

    XmlRpcServerConnection* p = NULL;

    EnterCriticalSection(&_mcs);
    p = _mConnection.front();
    _mConnection.pop_front();
    //XmlRpcUtil::log(5, "Wait process tasks is %d", _mConnection.size());
    LeaveCriticalSection(&_mcs);

    if(p) {
      XmlRpcUtil::log(5, "Executing wirteResponse in thread %x", GetCurrentThreadId());
      p->writeResponseThread();
      p->setThreadWorking(false);
      if(p->checkDisconnected()) { 
         // XmlRpcUtil::log(3, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!   executed via thread %x");
         p->close();
      }
      
      XmlRpcUtil::log(5, "Executed wirteResponse in thread %x", GetCurrentThreadId());
    }

  }

  return 0;
}

#else


XmlRpcThreads::XmlRpcThreads()
{
  pthread_mutex_init(&_mConnectionLock, NULL);
  sem_init(&_mSem,0,0);

}

XmlRpcThreads::~XmlRpcThreads()
{
  pthread_mutex_destroy(&_mConnectionLock);
  sem_destroy(&_mSem);
}



int 
XmlRpcThreads::initThreads(int num)
{
  if(num <= 0)
    return -1;

  for (int i=0; i<num; i++) {
    pthread_t tid;
    pthread_attr_t threadAttr;
    pthread_attr_init(&threadAttr);
    pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setstacksize(&threadAttr, 1024*1024*5);  // 设置线程栈大小
    
    if(pthread_create(&tid, &threadAttr, XmlRpcThreads::_threadWork, (void *)this) != 0)
      return -1;
  }
  
  return 0;
}


void* 
XmlRpcThreads::_threadWork(void* pArgs)
{
  XmlRpcThreads* pThis = (XmlRpcThreads*)pArgs;
  pThis->execTask();

  return NULL;
}


int 
XmlRpcThreads::pushTask(XmlRpcServerConnection* connTask)
{
  int rs = XmlRpcUtil::getLock(&_mConnectionLock);
  if (rs == 0) {
    _mConnection.push_back(connTask);
     XmlRpcUtil::freeLock(&_mConnectionLock);

    // 唤醒一个线程
    sem_post(&_mSem);
  }

  return rs;
}

int 
XmlRpcThreads::execTask()
{
  while(1) {
    // 所有线程阻塞中,等待唤醒
    int ret;
    do{
      ret = sem_wait(&_mSem);
    }while(ret == -1 && errno == EINTR);

    XmlRpcServerConnection* p = NULL;
    int rs = XmlRpcUtil::getLock(&_mConnectionLock);
    if(rs == 0) {
      if (_mConnection.size() > 0)
      {
        p = _mConnection.front();
        _mConnection.pop_front();
      }

      XmlRpcUtil::freeLock(&_mConnectionLock);
    }

    if(p) {
      XmlRpcUtil::log(5, "Executing wirteResponse in thread %x", pthread_self());
      p->writeResponseThread();
      p->setThreadWorking(false);
      XmlRpcUtil::log(5, "Finished wirteResponse in thread %x", pthread_self());
      if(p->checkDisconnected()) { 
         // 此时该连接可能对端已关闭,但本地的资源并未释放
         XmlRpcUtil::log(3, "Destroy fd %d after thread work.", p->getfd());
         p->close();
      }
      
      // XmlRpcUtil::log(5, "Executed wirteResponse in thread %x", pthread_self());
    }

  }

  return 0;
}



#endif


}









// End

