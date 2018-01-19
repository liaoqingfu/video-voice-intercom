// SipAgent.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "log4z.h"
#include "GlobalCtrl.h"

#include "AgentServer/SipHeartBeat.h"
#include "AgentServer/SipRegister.h"
#include "AgentServer/Directory.h"
#include "AgentServer/RealPlay.h"
#include "AgentServer/SipPtzCtrl.h"

#include "unittest.h"


//------------------------
static bool g_consoleExit = false;



BOOL CALLBACK ConsoleHandler(DWORD ev)
{
	//注销
	SipRegister reg(GLOBJ(gSipServer));
	reg.Register(0);

	BOOL bRet = FALSE;
	switch (ev)
	{
	case CTRL_CLOSE_EVENT:
		{
			g_consoleExit = true;
			bRet = TRUE;

			//注销
			SipRegister reg(GLOBJ(gSipServer));
			reg.Register(0);
		}
		break;
	default:
		break;
	}
	return bRet;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int ret = -1;

	zsummer::log4z::ILog4zManager::GetInstance()->Start();
	if (GlobalCtrl::instance()->init() != 0)
	{
		return -1;
	}

#if 0
	gService = new ServiceStart();
	gService->Start();

	//监听注销命令
	boost::thread UnRegisterThread(&ListenUnRegister, (void*)NULL);

	//设备操作
	DeviceOperator deviceOpt(&gSipServer);

	//liveStream 现场
	LiveMediaHandle live(&gSipServer);

	//playback回放
	PlayBackMediaHandle playback(&gSipServer);
	//playback.RpcPlaybackFileList(180, 1,0, 0);

	//ptz云台控制
	PtzCtrlHandle ptz(&gSipServer);

	//设备目录
	DirectoryHandle catalog(&gSipServer);

	//alarm报警
	AlarmMgrHandle alarm(&gSipServer);
	alarm.StartAlarmListening();

	gDB.DBInit();

#endif

	SipRegister reg(GLOBJ(gSipServer));
	reg.RegisterServiceStart();

	SipHeartBeat heart(GLOBJ(gSipServer));
	heart.HeartBeatServiceStart();

	Directory dirQuery(GLOBJ(gSipServer));
	dirQuery.autoDirNotify();

	RealPlay real(GLOBJ(gSipServer));
	SipPtzCtrl ptzCtrl(GLOBJ(gSipServer));

  //unitest
	//unittest test;
	//test.start();


	SetConsoleCtrlHandler(ConsoleHandler, TRUE);
	while (!g_consoleExit)
	{
		Sleep(500);
	}
	

	_LOG(LOG_LEVEL_WARN, "###console application exit!");

	return 0;
}

