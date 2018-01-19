/************************************************************************

  用于测试的xmlrpc server端


  g++ -o testmc testmc.cpp -I../../bsrDirectory/common/ -I./ ../libXmlRpc.a ../../bsrDirectory/common/MOBase.o -lpthread

************************************************************************/
#if defined(_WINDOWS)
#include <windows.h>
#endif


#include "MOBase.hpp"

#include <iostream>

using namespace std;

class XS : public MOBase
{
public:
  XS(XmlRpcServer* s);
  ~XS(){}

  static void simecho(XmlRpcValue& params, XmlRpcValue& result);
  static void authed(XmlRpcValue& params, XmlRpcValue& result);

private:

};

XmlRpcServer svrXmlrpc;


XS::XS(XmlRpcServer* s)
{
  registerRPC(s, "SIMECHO",  XS::simecho, false );
  registerRPC(s, "AUTHED",  XS::authed );


}


void XS::simecho(XmlRpcValue& params, XmlRpcValue& result)
{
  cout << "In XS::simecho()" << endl;
  cout << params << endl;

  result = params;

  svrXmlrpc.getSessionManager()->login((int)params["_fd"], 102030, NULL);

  //Sleep(5000);
}

void XS::authed(XmlRpcValue& params, XmlRpcValue& result)
{
  cout << "In XS::authed()" << endl;
  cout << params << endl;
  //usleep(5000);
  for(int i=0; i<10; i++)
    result[i]["msg"] = "you are the best! ";
  //sleep(5);
}




int main()
{

  XmlRpc::setVerbosity(7);

  svrXmlrpc.bindAndListen(10000, 5);      // 监听10000端口
  svrXmlrpc.enableSessionManager(true);   // 开启session管理器
  svrXmlrpc.enableIntrospection(false);   // 关闭方法列表功能,该特性默认为关闭.
  // svrXmlrpc.enableSessionSpawn(true);  // 启用多进程模式.
  svrXmlrpc.enabledMultiThread(true, 10); // 启用多线程模式,预分配30个线程执行.

  XS xs(&svrXmlrpc);
  svrXmlrpc.work(-1.0);

  return 0;
}


// End

