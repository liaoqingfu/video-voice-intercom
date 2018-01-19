#pragma once

//主动发起注册请求、管理下级向本级发起的注册请求
#include "SipMgr.h"
#include "SipHandleBase.h"


class TaskTimer;

class SipRegister : SipHandleBase
{
public:
	SipRegister(CSipMgr* pServer);
	~SipRegister(void);

public:
	//管理注册服务
	static void RegisterServiceMgr(SipMessage& msg, int& iresult, void* context);
	static void RegisterServiceSuccess(SipMessage& msg, int& iresult, void* context);

	int RegisterServiceStart();
	static void RegisterProc(void* param);

	//向下提供注册
	int Register(int expires);

public:
	TaskTimer* m_RegTimer;

	char m_SysCheckDateTm[64];

	//是否已经注册
	static bool g_bRegisted;
	//注册的handle
	static RvSipRegClientHandle g_hRegClient;
};
