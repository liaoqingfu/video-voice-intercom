#include "PlayBack.h"
#include "../Utility/XmlParser.h"

//static variable

StreamMgr* PlayBack::m_pStreamMgr = NULL;

PlayBack::PlayBack(CSipMgr* pSipServer)
{
	if (pSipServer != NULL)
	{
		pSipServer->Register(MESSAGE, RECORDINFO, &(PlayBack::SipPlaybackList), this);
		pSipServer->Register(INVITE, PLAYBACK, &(PlayBack::SipPlaybackInvite), this);
		pSipServer->Register(INFOR, PLAY, &(PlayBack::SipPlaybackCtrlInfo_Play), this);
		pSipServer->Register(INFOR, PAUSE, &(PlayBack::SipPlaybackCtrlInfo_Pause), this);
		pSipServer->Register(INFOR, TEARDOWN, &(PlayBack::SipPlaybackCtrlInfo_Teardown), this);
		pSipServer->Register(INVITE, DOWNLOAD, &(PlayBack::SipPlaybackInvite), this);
		pSipServer->Register(MESSAGE, MEDIASTATUS, &(PlayBack::SipPlayback_MediaStatus), this);
	}

	m_pStreamMgr = new StreamMgr();

}


PlayBack::~PlayBack(void)
{
	delete m_pStreamMgr;
	m_pStreamMgr = NULL;
}


//回放文件检索
void PlayBack::SipPlaybackList(SipMessage& msg, int& iresult, void* context)
{

	iresult = SIP_SUCCESS;
	msg.emptyMsgBody();

#if 0
	AnswerArgs arg;
	strcpy(arg.sourceIp, msg.from_ip());
	strcpy(arg.usr, msg.from_user());
	arg.sourcePort = msg.from_port();
	strcpy(arg.request, msg.sipMessageBody());

	//int index = m_PlaybackMsg.GetPort();
	//m_PlaybackMsg.StorePolicyInfo(index, &arg);

	//TaskPool::_taskPool()->g_threadPool.schedule(boost::bind(&FileListRequest, index));

#endif

}



void PlayBack::FileListRequest(int index)
{
#if 0
	AnswerArgs arg = m_PlaybackMsg.GetPortAnswerArgs(index);
	char* resultBuf;
	resultBuf = new char[BODY_SIZE];
	memset(resultBuf, 0, BODY_SIZE);
	do 
	{
		//if (gXmlRpcConnect.PlaybackFileList(arg.request, resultBuf) == 0)
		{
			if (SendFileList(resultBuf, strlen(resultBuf), arg.sourceIp, arg.sourcePort, arg.usr) == 0)
			{
				break;
			}
		}
		else
		{
			break;
		}


	} while (0);

	m_PlaybackMsg.ErasePolicyInfo(index);

	delete []resultBuf;
	resultBuf = NULL;
#endif

}

int PlayBack::SendFileList(char* msgBody, int len, char* fromIp, int fromPort, char* fromUsr)
{
#if 0
	SipMessage msg;
	msg.setFrom(gConfig->getSiplocalUser(), gConfig->getSiplocalIp(), gConfig->getSiplocalPort());
	msg.setTo(fromUsr, fromIp, fromPort);
	msg.setUri(fromIp, fromPort);
	msg.setSipMessageBody(msgBody, len);

	int ret = 0;
	ret = CSipMgr::doSipRequest(MESSAGE, msg);
	if (ret == SIP_OK)
	{
		if (msg.status_code() == SIP_SUCCESS)
		{
		}
		else
		{
			//重发处理
		}
	}
	else
	{
	}
	//发送目录超时处理
	if (ret == SIP_REQUEST_TIMEOUT)
	{
		//ret = directoryReSend(msgBody, len);
		//ret = SIP_REQUEST_TIMEOUT;
	}

#endif

	return 0;
}


//sip历史文件回放
void PlayBack::SipPlaybackInvite(SipMessage& msg, int& iresult, void* context)
{
	iresult = SIP_SUCCESS;

#if 0
	StreamInfo info;
	std::string subject = msg.GetSubject();
	//解析subject的 deviceaddr和流序号
	std::string deviceAddr;
	int index;
	ParseSubject(subject, deviceAddr, index);
	strcpy(info.addrCode, msg.to_user());
#if 0
	Origin o;
	msg.getSdpO(&o);
	strcpy(info.addrCode, o.usr);
  //
	strcpy(info.addrCode, msg.to_user());
#endif
	RvSdp parser;
	if (parser.ParseSdpInfo(msg.sipMessageBody(), strlen(msg.sipMessageBody())) == 0)
	{
		std::string u = parser.getU();
		int pos = u.find(":", 0);
		std::string id = u.substr(0, pos);
		strcpy(info.addrCode, id.c_str());
	}
	else
	{
		_LOG(LOG_LEVEL_DEBUG, "解析sdp失败");
	}

	info.streamIndex = index;
	info.sessionHandle = (void*)(msg.m_hCallLeg);
	//流管理
	if (m_pStreamMgr != NULL)
	{
		m_pStreamMgr->OpenStream(&info);
	}

	//发送xmlrpc请求
	char* pBuf;
  pBuf = new char[1024*8];
	memset(pBuf, 0, 8*1024);
	if (gXmlRpcConnect.PlaybackPlayRpc(info.addrCode, info.streamIndex, msg.sipMessageBody(), pBuf, (char*)subject.c_str()) == 0)
	{
		msg.setSipMessageBody(pBuf, strlen(pBuf));
		iresult = SIP_SUCCESS;
	}
	else
	{
		iresult = SIP_BADREQUEST;
	}

	msg.setFrom(gConfig->getSiplocalUser(), gConfig->getSiplocalIp(), gConfig->getSiplocalPort());


	delete []pBuf;
	pBuf = NULL;

#endif
}


//sip回放控制-play
void PlayBack::SipPlaybackCtrlInfo_Play(SipMessage& msg, int& iresult, void* context)
{
	iresult = SIP_SUCCESS;

#if 0
	StreamInfo info;
	int ret = 0;
	if (m_pStreamMgr != NULL)
	{
		ret = m_pStreamMgr->GetStreamInfo((void*)msg.m_hCallLeg, &info);
	}

	char* pBuf;
	pBuf = new char[1024*8];
	memset(pBuf, 0, 8*1024);
	if (gXmlRpcConnect.PlaybackResetPlayRpc(info.addrCode, info.streamIndex, msg.sipMessageBody(), pBuf) == 0)
	{
		msg.setSipMessageBody(pBuf, strlen(pBuf));
		iresult = SIP_SUCCESS;
	}
	else
	{
		iresult = SIP_BADREQUEST;
	}

	delete []pBuf;
	pBuf = NULL;
#endif

}

//sip回放控制-pause
void PlayBack::SipPlaybackCtrlInfo_Pause(SipMessage& msg, int& iresult, void* context)
{
	iresult = SIP_SUCCESS;

#if 0
	StreamInfo info;
	if (m_pStreamMgr != NULL)
	{
		int ret = m_pStreamMgr->GetStreamInfo((void*)msg.m_hCallLeg, &info);
	}

	char* pBuf;
	pBuf = new char[1024*8];
	memset(pBuf, 0, 8*1024);
	if (gXmlRpcConnect.PlaybackPauseRpc(info.addrCode, info.streamIndex, msg.sipMessageBody(), pBuf) == 0)
	{
		msg.setSipMessageBody(pBuf, strlen(pBuf));
		iresult = SIP_SUCCESS;
	}
	else
	{
		iresult = SIP_BADREQUEST;
	}

	delete []pBuf;
	pBuf = NULL;
#endif
}


//sip回放控制-teardown
void PlayBack::SipPlaybackCtrlInfo_Teardown(SipMessage& msg, int& iresult, void* context)
{
	iresult = SIP_SUCCESS;

#if 0
	StreamInfo info;
	if (m_pStreamMgr != NULL)
	{
		m_pStreamMgr->GetStreamInfo((void*)msg.m_hCallLeg, &info);	
	}

	char* pBuf;
	pBuf = new char[1024*8];
	memset(pBuf, 0, 8*1024);
	if (gXmlRpcConnect.PlaybackStopRpc(0, info.addrCode, info.streamIndex, msg.sipMessageBody(), pBuf) == 0)
	{
		msg.setSipMessageBody(pBuf, strlen(pBuf));
		iresult = SIP_SUCCESS;
	}
	else
	{
		iresult = SIP_BADREQUEST;
	}

	delete []pBuf;
	pBuf = NULL;
#endif
}


void PlayBack::SipPlayback_MediaStatus(SipMessage& msg, int& iresult, void* context)
{
	iresult = SIP_SUCCESS;

#if 0

	SipMessage mediaMsg;
	mediaMsg.setFrom(gConfig->getSiplocalUser(), gConfig->getSiplocalIp(), gConfig->getSiplocalPort());
	mediaMsg.setTo(gConfig->getSipremoteUser(), gConfig->getSipremoteIp(), gConfig->getSipremotePort());
	mediaMsg.setUri(gConfig->getSipremoteIp(), gConfig->getSipremotePort());
	mediaMsg.setSipMessageBody(msg.sipMessageBody(), strlen(msg.sipMessageBody()));
// 	std::string cty = "Application/MANSCDP+xml";
// 	mediaMsg.setContentType((char*)cty.c_str(), cty.length());
	
	msg.emptyMsgBody();

	int ret = 0;
	ret = CSipMgr::doSipRequest(MESSAGE, mediaMsg);
	if (ret == SIP_OK)
	{
		if (mediaMsg.status_code() == SIP_SUCCESS)
		{

		}
	}
	else
	{

	}

#endif
}


void PlayBack::ParseSubject(std::string& str, std::string& deviceAddr, int& index)
{
	std::string buf = str;
	size_t pos = buf.find_first_of(':', 0);
	//摄像头的Address ID
	std::string addr = buf.substr(0, pos);
	size_t pos2 = buf.find_first_of(':', pos + 1);
	std::string indexStr = buf.substr(pos2 + 1);

	deviceAddr = addr;
	index = atoi(indexStr.c_str());

}

