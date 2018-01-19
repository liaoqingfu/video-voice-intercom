#pragma once

//管理sip心跳keepalive、主动发起sip心跳请求到第三方系统

#include "SipMgr.h"
#include "SipHandleBase.h"

class TaskTimer;

class SipHeartBeat : SipHandleBase
{
public:
	SipHeartBeat(CSipMgr* pServer);
	~SipHeartBeat(void);

public:
	//启动服务
	void HeartBeatServiceStart();
	//处理心跳请求
	static void SipHeartBeatServiceMgr(SipMessage& msg, int& iresult, void* context);
	static void CheckAllUacHeartBeat(void* lpVoid);

	//主动发送心跳请求
	static void HeartBeatProc(void* param);
public:
	//心跳检查定时器
	TaskTimer* m_pCheckUacStateTimer;
	//主动发送心跳定时器
	TaskTimer* m_pHearBeatTimer;

	//
	static int m_HeartBeatFailedNum;
	//
	static int m_SNIndex;
};
