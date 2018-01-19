/************************************************************************

  用于测试的xmlrpc client端


  g++ -o testmcc testmcc.cpp ../libXmlRpc.a -lpthread

************************************************************************/

#include <iostream>
#if defined(_MSC_VER)

#include "XmlRpcClient.h"
#include "XmlRpcValue.h"
#include <windows.h>
#include <process.h>

#define sleep Sleep

#else

#include "XmlRpc.h"
#include <unistd.h>
#include <pthread.h>
#include <string>
#endif

#define THREADNUM 1

using namespace XmlRpc;

#if defined(_MSC_VER)
DWORD WINAPI threadEntry(LPVOID pArgs)
#else
void* threadEntry(void* pArgs)
#endif
{

  XmlRpcClient c("192.168.8.232", 10000);
  
  for(int i=0; i<4  ; i++)
  { 
		//XmlRpcClient c("192.168.8.232", 10000);

    XmlRpcValue params;
    XmlRpcValue result; 


    if(i >= 2)
    {
      c.setUserCookie(102030, 9090);  // 设置当前连接使用的sessionId和用户特定参数
      std::string cmdstr = "AUTHED";
      params["mess"] = "thread client          1   you can do better!!!  ";

      std::cout << "   1    count: " << i  <<  "  cmd:" << cmdstr << "; params:" << params << std::endl;
      if (c.execute(cmdstr.c_str(), params, result))
      {
        std::cout << "Send successed.\n\n" << result << std::endl;
      }
      else
        std::cout << "Send failed.\n\n";

    }
    else
    {
      std::string cmdstr = "SIMECHO";
      params["mess"] = "hello,world.";

      std::cout << "cmd:" << cmdstr << "; params:" << params << std::endl;
      if (c.execute(cmdstr.c_str(), params, result))
      {
        std::cout << "Send successed.\n\n" << result << std::endl;
      }
      else
        std::cout << "Send failed.\n\n";

      // sleep(2);
      // break;
    }
    
    
    //usleep(10000);
  }

  sleep(111);

#if defined(_MSC_VER)
	return 0;
#else
  return NULL;
#endif
}





#if defined(_MSC_VER)
DWORD WINAPI threadEntry2(LPVOID pArgs)
#else
void* threadEntry2(void* pArgs)
#endif
{
  XmlRpcClient c("192.168.8.232", 10000); 

  for(int i=0; i<3 ; i++)
  {
    XmlRpcClient c("192.168.8.232", 10000); 
    XmlRpcValue params;
    XmlRpcValue result; 


    //usleep(10000);
    if(i >= 1)
    {
      c.setUserCookie(102030, 9090);
    }

    std::string cmdstr = "AUTHED";
    params["mess"] = "thread client           2   hello,world.";


    std::cout << "count: " << i  <<  "  cmd:" << cmdstr << "; params:" << params << std::endl;
    if (c.execute(cmdstr.c_str(), params, result))
    {
      std::cout << "Send successed.\n\n" << result << std::endl;
    }
    else
      std::cout << "Send failed.\n\n";
  
    // sleep(1);
  }

#if defined(_MSC_VER)
  return 0;
#else
  return NULL;
#endif
}


#if defined(_MSC_VER)
DWORD WINAPI threadEntry3(LPVOID pArgs)
#else
void* threadEntry3(void* pArgs)
#endif
{

  XmlRpcClient c("192.168.8.237", 10000);
  
 
  //XmlRpcClient c("192.168.8.232", 10000);

  XmlRpcValue params;
  XmlRpcValue result; 


  c.setUserCookie(102030, 9090);  // 设置当前连接使用的sessionId和用户特定参数
  /*std::string cmdstr = "AUTHED";
  params["mess"] = "thread client          3   you can do better!!!  ";

  std::cout << "   1    count: " << i  <<  "  cmd:" << cmdstr << "; params:" << params << std::endl;
  if (c.execute(cmdstr.c_str(), params, result))
  {
    std::cout << "Send successed.\n\n" << result << std::endl;
  }
  else
    std::cout << "Send failed.\n\n";*/
  int i=0;
  while (i++ < 1)
  {
    std::string cmdstr = "SIMECHO";
    params["mess"] = "hello,world.";

    std::cout << "Thread: " << GetCurrentThreadId() << ": cmd:" << cmdstr << "; params:" << params << std::endl;
    if (c.execute(cmdstr.c_str(), params, result))
    {
    std::cout << "Thread: " << GetCurrentThreadId() << ": Send successed.\n\n" << result << std::endl;
    }
    else
    std::cout << "Thread: " << GetCurrentThreadId() << ": Send failed.\n\n";
  }
  
  std::cout << "Thread: " << GetCurrentThreadId() << ": exit";

#if defined(_MSC_VER)
  return 0;
#else
  return NULL;
#endif
}

int main(int argc, char* argv[])
{
#if defined(_MSC_VER)
  HANDLE threadHandle[THREADNUM];
  for (int i = 0;i < THREADNUM;++i)
  {
  threadHandle[i] = CreateThread(NULL,1024*1024*5,threadEntry3,NULL,0,NULL);
  CloseHandle(threadHandle[i]);
  }
  sleep(2000);
  for (int i = 0;i < THREADNUM;++i)
  {
    ::WaitForMultipleObjects(THREADNUM,threadHandle,true,INFINITE);
    //TerminateThread(threadHandle[i],0);
  }
  /*Sleep(3);
  threadHandle = CreateThread(NULL,1024*1024*5,threadEntry2,NULL,0,NULL);
  CloseHandle(threadHandle);*/
#else

  pthread_attr_t threadAttr;
  pthread_attr_init(&threadAttr);
  pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
  
  pthread_t threadId;
  pthread_create(&threadId, &threadAttr, (void*(*)(void*))threadEntry, NULL);

  sleep(3);
  pthread_create(&threadId, &threadAttr, (void*(*)(void*))threadEntry2, NULL);

#endif

  sleep(1000);
  std::cout << "main thread exit" << std::endl;
  return 0;
}


