#pragma once

class RpcCmd;
class CSipMgr;
class ProxyConfig;
class BcAdaptor;


#include "ThreadPool.h"
//
class GlobalCtrl;
#define GLOBJ(obj) GlobalCtrl::instance()->obj

class GlobalCtrl
{
public:
	static GlobalCtrl* instance();
  
	//初始化全局对象
	int init();

	//启动sip-server
	static unsigned int __stdcall sipRunProc(void* context);
	static bool gSipInit;
public:
	//xmlrpc 命令对象
	RpcCmd* gRpcExcutor;
	//sip上层应用管理
	CSipMgr* gSipServer;
	//配置文件
	ProxyConfig* gConfig;
	//thread pool
	base::ThreadPool* gThreadPool;

	//adaptor
	BcAdaptor* gAdaptor;


private:
	GlobalCtrl(void){}
	~GlobalCtrl(void);
	GlobalCtrl(const GlobalCtrl& global);
	const GlobalCtrl& operator=(const GlobalCtrl& global);

private:
	static GlobalCtrl* ms_pInstace;


	class Guard //
	{
	public:
		~Guard()
		{
			delete GlobalCtrl::ms_pInstace;
			GlobalCtrl::ms_pInstace = NULL;
		}
	};

	static Guard Garbo; 

};
