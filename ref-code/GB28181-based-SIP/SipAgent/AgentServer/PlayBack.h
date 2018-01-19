#ifndef _PLAYBACKMEDIAHANDLE_H
#define _PLAYBACKMEDIAHANDLE_H

#include "SipHandleBase.h"
#include "SipMgr.h"

#include "PlaybackDef.h"
#include "StreamMgr.h"



#define DOCK_TYPE "NVR"
#define VIA "0"

class PlayBack : public SipHandleBase 
{
public:
	PlayBack(CSipMgr* pSipServer);
	~PlayBack(void);

public:
    //sip历史文件检索
	static void SipPlaybackList(SipMessage& msg, int& iresult, void* context);
	//sip历史文件回放
	static void SipPlaybackInvite(SipMessage& msg, int& iresult, void* context);
	//sip回放控制-play
	static void SipPlaybackCtrlInfo_Play(SipMessage& msg, int& iresult, void* context);
	//sip回放控制-pause
	static void SipPlaybackCtrlInfo_Pause(SipMessage& msg, int& iresult, void* context);
	//sip回放控制-teardown
	static void SipPlaybackCtrlInfo_Teardown(SipMessage& msg, int& iresult, void* context);

	//回放结束主动发送message_status
	static void SipPlayback_MediaStatus(SipMessage& msg, int& iresult, void* context);

	static void ParseSubject(std::string& str, std::string& deviceAddr, int& index);

	static void FileListRequest(int index);
	static int SendFileList(char* msgBody, int len, char* fromIp, int fromPort, char* fromUsr);

public:
	static StreamMgr* m_pStreamMgr;

};

#endif

