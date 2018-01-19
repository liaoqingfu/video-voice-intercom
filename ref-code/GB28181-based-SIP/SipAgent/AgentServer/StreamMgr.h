#pragma once

#include "lock.h"
#include <list>
/*
实时视频流的管理
*/

//流信息
struct StreamInfo
{
	int streamIndex;    //流编号
	char addrCode[24];   //sip设备地址编码
	void* sessionHandle;  //sip会话句柄

	StreamInfo()
	{
		streamIndex = 0;
		memset(addrCode, 0, sizeof(addrCode));
		sessionHandle = NULL;
	}

	StreamInfo& operator=(const StreamInfo& info)
	{
		streamIndex = info.streamIndex;
		strcpy(addrCode, info.addrCode);
		sessionHandle = info.sessionHandle;

		return *this;
	}

};


class StreamMgr
{
public:
	StreamMgr(void);
	~StreamMgr(void);


public:
	void OpenStream(StreamInfo* stream);
	void CloseStream(void* handle, StreamInfo* stream); 

	int GetStreamInfo(void* handle, StreamInfo* stream);

public:
	std::list<StreamInfo> m_StreamList;

	static lock_summary::critical_lock ms_crtlLock;

};
