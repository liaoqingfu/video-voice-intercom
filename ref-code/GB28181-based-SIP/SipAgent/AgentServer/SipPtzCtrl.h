#ifndef _PTZCTRLHANDLE_H
#define _PTZCTRLHANDLE_H

#include "SipHandleBase.h"
#include "SipMgr.h"

//---------------------
//云台控制参数定义
struct PtzCmd
{
	char head;
	char assemble1;
	char addr8L;
  char cmd;
	char arg1;
	char arg2;
	char assemble2;
	char checksum;
};

class SipPtzCtrl : SipHandleBase
{
public:
	SipPtzCtrl(CSipMgr* pServer);
	~SipPtzCtrl(void);

public:
	static void PtzCommandProc(SipMessage& msg, int& iresult, void* contex);
  static void ParsePtzCmd(const char* cmd, PtzCmd* ptz);

};

#endif

