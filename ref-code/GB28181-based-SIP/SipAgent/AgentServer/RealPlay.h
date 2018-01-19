#pragma once


#include "SipHandleBase.h"
#include <string>

#include "SipMgr.h"

#include <list>
#include "lock.h"


class RealPlay : public SipHandleBase
{
public:
	RealPlay(CSipMgr* sipServer);
	~RealPlay(void);


	struct RealMedia
	{
		int devId;
		int devType;
		HANDLE hReal;
	};


public:
	//INVITE «Î«ÛµƒœÏ”¶
	static void SipLiveStreamOpen(SipMessage& msg, int& iresult, void* context);
	static void SipLiveStreamClose(SipMessage& msg, int& iresult, void* context);

	static void ParseSubject(std::string& str, std::string& deviceAddr, int& index);

public:
	static void RealStreamAdd(RealPlay::RealMedia* stream);
	static void RealStreamDel(int devId, int devType);
	static HANDLE RealStreamGet(int devid, int devType);

	//
	static void sendhik(char* ip, int port, int bindPort);

public:

	static std::list<RealMedia> ms_RealStreamMgr;
	static lock_summary::critical_lock ms_crtlLock;
};
