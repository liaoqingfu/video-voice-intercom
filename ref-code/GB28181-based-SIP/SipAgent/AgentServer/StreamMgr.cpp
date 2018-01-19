#include "StreamMgr.h"

lock_summary::critical_lock StreamMgr::ms_crtlLock;

StreamMgr::StreamMgr(void)
{
}

StreamMgr::~StreamMgr(void)
{
}


void StreamMgr::OpenStream(StreamInfo* stream)
{
	if (stream == NULL)
	{
		return ;
	}

	lock_summary::scope_lock lock(&ms_crtlLock);
	StreamInfo info;
	info = *stream;

	m_StreamList.push_back(info);

}


void StreamMgr::CloseStream(void* handle, StreamInfo* stream)
{

	lock_summary::scope_lock lock(&ms_crtlLock);

	std::list<StreamInfo>::iterator it;
	for (it = m_StreamList.begin(); it != m_StreamList.end(); it++)
	{
		if (it->sessionHandle == handle)
		{
			*stream = *it;
      m_StreamList.erase(it);
			break;
		}
	}

}


int StreamMgr::GetStreamInfo(void* handle, StreamInfo* stream)
{
	std::list<StreamInfo>::iterator it;
	for (it = m_StreamList.begin(); it != m_StreamList.end(); it++)
	{
		if (it->sessionHandle == handle)
		{
			*stream = *it;
			return 0;
		}
	}

	return -1;

}