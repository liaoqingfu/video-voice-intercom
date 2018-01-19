#include "RvSdp.h"
#include <string>

#define SDP_BUFFER_SIZE 1024*16

RvSdp::RvSdp(void)
{
	memset(attributeLines, 0, sizeof(attribute) * ATTRIBUTESIZE);
	memset(&mNameAndAddr, 0, sizeof(mediaDescr));
	memset(&osIdentifier, 0, sizeof(Origin));

	memset(sName, 0, sizeof(sName));
	memset(t, 0, sizeof(t));
	memset(vision, 0, sizeof(vision));

	m_pContent = new char[SDP_BUFFER_SIZE];
	memset(m_pContent, 0, SDP_BUFFER_SIZE);

	memset(uri, 0, sizeof(uri));
	memset(&otherfield, 0, sizeof(otherfield));

	RvStatus rv;
	rv = RvSdpMgrConstruct();

	m_sdpPool = RPOOL_Construct(1024,10, NULL,RV_FALSE,"RvSdpPool");
}


RvSdp::~RvSdp(void)
{
	if (m_pContent != NULL)
	{
		delete []m_pContent;
		m_pContent = NULL;
	}

	RPOOL_Destruct(m_sdpPool);

	RvSdpMgrDestruct();
	
}


void RvSdp::getO(Origin* o)
{
	if (o != NULL)
	{
		strcpy(o->usr, osIdentifier.usr);
		strcpy(o->vision, osIdentifier.vision);
		strcpy(o->sid, osIdentifier.sid);
		strcpy(o->nettype, osIdentifier.nettype);
		strcpy(o->addrtype, osIdentifier.addrtype);
		strcpy(o->addr, osIdentifier.addr);
	}
}


void RvSdp::getM(mediaDescr* m)
{
	if (m != NULL)
	{
		*m = mNameAndAddr;
	}
}


void RvSdp::getA(attribute** a)
{
	if (a != NULL && *a != NULL)
	{
		for (int i = 0; i < ATTRIBUTESIZE; i++)
		{
			if (strlen(attributeLines[i].name) > 0)
			{
				strcpy((*a)[i].name, attributeLines[i].name);
				strcpy((*a)[i].value, attributeLines[i].value);
			}
		}
	}
}

void RvSdp::getC(cconnect* c)
{
	if (c != NULL)
	{
		strcpy(c->netType, cInfo.netType);
		strcpy(c->addrType, cInfo.addrType);
		strcpy(c->addr, cInfo.addr);
	}
}


int RvSdp::ParseSdpInfo(char* sdpBuffer, int len)
{
	strcpy(m_pContent, sdpBuffer);

	int mediaSize = 0;
	RvSdpMsg pMsg;
	RvSdpOrigin *origin = NULL;
	RvSdpMediaDescr *media = NULL;
	RvSdpConnection* connect= NULL;
	RvSdpAttribute* attr = NULL;
	RvStatus rv;
	rv = CreateSdpMsgFromEncodedBuffer(m_pContent, &len, &pMsg);
	if (rv == RV_OK)
	{
		m_pSdpMsg = pMsg;

		char* tempStr = NULL;
		RvSdpMsg* pSdp = &pMsg;
		//o
		 origin = rvSdpMsgGetOrigin(pSdp);
		 if (origin != NULL)
		 {
			 tempStr = (char*)rvSdpOriginGetUsername(origin);
			 strcpy(osIdentifier.usr, tempStr);
			 tempStr = (char*)rvSdpOriginGetVersion(origin);
			 strcpy(osIdentifier.vision, tempStr);
			 tempStr = (char*)rvSdpOriginGetSessionId(origin);
			 strcpy(osIdentifier.sid, tempStr);
			 tempStr = (char*)rvSdpOriginGetNetTypeStr(origin);
			 strcpy(osIdentifier.nettype, tempStr);
			 tempStr = (char*)rvSdpOriginGetAddressTypeStr(origin);
			 strcpy(osIdentifier.addrtype, tempStr);
			 tempStr = (char*)rvSdpOriginGetAddress(origin);
			 strcpy(osIdentifier.addr, tempStr);
		 }
		 //s
		 char* s = NULL;
		 s = (char*)rvSdpMsgGetSessionName(pSdp);
		 if (s != NULL)
		 {
			 strcpy(sName, s);
		 }
		 //uri
		 tempStr = (char*)rvSdpMsgGetURI(pSdp);
		 if (tempStr != NULL)
			 strcpy(uri, tempStr);
		 //m
		 mediaSize = rvSdpMsgGetNumOfMediaDescr(&pMsg);
		 mNameAndAddr.count = mediaSize;
		 for (int index=0;index< mediaSize; ++index)
		 {
			 media=rvSdpMsgGetMediaDescr(&pMsg, index);
			 RvSdpMediaType type = rvSdpMediaDescrGetMediaType(media);
			 mNameAndAddr.mediades[index].mtype = TransferMediaType(type);
			 mNameAndAddr.mediades[index].mport = rvSdpMediaDescrGetPort(media);
			 RvSdpProtocol protocol = rvSdpMediaDescrGetProtocol(media);
			 mNameAndAddr.mediades[index].protocol = TransferProtocolType(protocol);
			 size_t size = rvSdpMediaDescrGetNumOfFormats(media);
			 for (int i = 0; i < size; i++)
			 {
				 tempStr = (char*)rvSdpMediaDescrGetFormat(media, i);
				 strcpy(mNameAndAddr.mediades[index].formats[i], tempStr);
			 }
			 
			 // Do something with media
		 }

		 //c
		 connect = rvSdpMsgGetConnection(&pMsg);
		 if (connect != NULL)
		 {
			 tempStr = (char*)rvSdpConnectionGetNetTypeStr(connect);
			 strcpy(cInfo.netType, tempStr);
			 tempStr = (char*)rvSdpConnectionGetAddrTypeStr(connect);
			 strcpy(cInfo.addrType, tempStr);
			 tempStr = (char*)rvSdpConnectionGetAddress(connect);
			 strcpy(cInfo.addr, tempStr);
		 }

		 //a
		 size_t size = 0; 
		 size = rvSdpMsgGetNumOfAttr(&pMsg);
		 int alen = 0;
		 for (alen = 0; alen < size; alen++)
		 {
			 attr = rvSdpMsgGetAttribute(&pMsg, alen);
       tempStr = (char*)rvSdpAttributeGetName(attr);
			 strcpy(attributeLines[alen].name, tempStr);
			 tempStr = (char*)rvSdpAttributeGetValue(attr);
			 strcpy(attributeLines[alen].value, tempStr);
		 }

		 //attr rtpmap
		 RvSdpRtpMap* rtpmap = NULL;
		 size = rvSdpMsgGetNumOfRtpMap(&pMsg);
		 char str_a[16] = {0,};
		 for (int i = 0; i < size; i++)
		 {
			 rtpmap = rvSdpMsgGetRtpMap(&pMsg, i);
			 if (rtpmap != NULL)
			 {
				 int payload = rvSdpRtpMapGetPayload(rtpmap);
				 char * encode = (char*)rvSdpRtpMapGetEncodingName(rtpmap);
				 memset(str_a, 0, sizeof(str_a));
				 sprintf(str_a, "%d", payload);
				 strcpy(attributeLines[alen].name, encode);
				 strcpy(attributeLines[alen].value, str_a);
				 alen++;
			 }
		 }

	}

	return 0;
}


const RvSdp& RvSdp::operator=(const RvSdp& sdp)
{
	if (this == &sdp)
	{
		return *this;
	}

	strcpy(vision, sdp.vision);
	strcpy(sName, sdp.sName);
	strcpy(t, sdp.t);

	osIdentifier = sdp.osIdentifier;
	cInfo = sdp.cInfo;

	mNameAndAddr = mNameAndAddr;
	
	for (int i = 0; i < 8; i++)
	{
		attributeLines[i] = sdp.attributeLines[i];
	}

	strcpy(m_pContent, sdp.m_pContent);
	int len = strlen(sdp.m_pContent);

	//m_pSdpMsg = CreateSdpMsgFromEncodedBuffer(m_pContent, &len);

	strcpy(uri, sdp.uri);

	memcpy(&otherfield, &(sdp.otherfield), sizeof(otherfield));

	return *this;
}


//设置媒体流接收端的ip和端口
void RvSdp::SetNetAddressAndPort(char* netAddr, int port)
{
	int mediaSize = 0;
	RvStatus rv;
	RvSdpOrigin *origin = NULL;
	RvSdpMediaDescr *media = NULL;
	RvSdpConnection* connect= NULL;

	RvSdpMsg* pSdp = &m_pSdpMsg;
	//o
	origin = rvSdpMsgGetOrigin(pSdp);
	rv = rvSdpOriginSetAddress(origin, netAddr);
	//c
	connect = rvSdpMsgGetConnection(&m_pSdpMsg);
  rv = rvSdpConnectionSetAddress(connect, netAddr);
	//m
	mediaSize = rvSdpMsgGetNumOfMediaDescr(&m_pSdpMsg);
	for (int index=0;index< mediaSize; ++index)
	{
		media=rvSdpMsgGetMediaDescr(&m_pSdpMsg, index);
		rvSdpMediaDescrSetPort(media, port);
	}


}

void RvSdp::GetSdpMsgBuf(char* pBuf, int len)
{
  RvStatus rv;
  rv = EncodeSdpMsgToBuffer(&m_pSdpMsg, len, pBuf);

}


void RvSdp::GetSdpMsgHandle(RvSdpMsg* sdp)
{
	int len = strlen(m_pContent);
	RvStatus rv = CreateSdpMsgFromEncodedBuffer(m_pContent, &len, sdp);

}


RvStatus RvSdp::EncodeSdpMsgToBuffer(RvSdpMsg *pMsg,
															int bufLen,
															char *encodedBuf)
{
	RvSdpStatus eStatus;
	rvSdpMsgEncodeToBuf(pMsg,encodedBuf,bufLen,&eStatus);
	if (eStatus != RV_SDPSTATUS_OK)
	{
		/* Error in rvSdpMsgEncodeToBuf function */
	}
	return eStatus;
}


RvStatus RvSdp::CreateSdpMsgFromEncodedBuffer(char *pBuffer, int *pBufSize, RvSdpMsg* pMsg)
{
	//
	//ObtainUnregularHead(pBuffer);

	/* Create a SDP message from encoded buffer*/

	RvStatus rv;

	RvSdpParseStatus eStat;
	/* Pass the encoded buffer */
	RvAlloc sdpAllocator;
	if (m_sdpPool != NULL)
		rv = RvSdpAllocConstruct(m_sdpPool, &sdpAllocator);
	int len = strlen(pBuffer);
	//rvSdpMsgConstructParseA(pMsg,pBuffer, &len,&eStat, &sdpAllocator);
	rvSdpMsgConstructParse(pMsg,pBuffer, &len, &eStat);
	if (eStat == RV_SDPPARSER_STOP_ERROR || pMsg == NULL)
	{
		return RV_ERROR_BADPARAM;
	}

	return RV_OK;
}


void RvSdp::setO_user(char* user)
{
	if (user == NULL)
	{
		return ;
	}
	RvStatus rv;
	RvSdpOrigin *origin = NULL;
	RvSdpMsg* pSdp = &m_pSdpMsg;
	//o
	origin = rvSdpMsgGetOrigin(pSdp);
	rv = rvSdpOriginSetUsername(origin, user);
}


sdpMediaType RvSdp::TransferMediaType(RvSdpMediaType ty)
{
	sdpMediaType mtype;
	switch (ty)
	{
	case RV_SDPMEDIATYPE_AUDIO:
		mtype = sdpMediaType_Audio;
		break;
	case RV_SDPMEDIATYPE_NAS:
		mtype = sdpMediaType_nas;
		break;
	case RV_SDPMEDIATYPE_VIDEO:
		mtype = sdpMediaType_Video;
		break;
	case RV_SDPMEDIATYPE_CONTROL:
		mtype = sdpMediaType_control;
		break;
	case RV_SDPMEDIATYPE_APP:
		mtype = sdpMediaType_app;
		break;
	case RV_SDPMEDIATYPE_DATA:
		mtype = sdpMediaType_data;
		break;
	case RV_SDPMEDIATYPE_IMAGE:
		mtype = sdpMediaType_image;
		break;
	case RV_SDPMEDIATYPE_UNKNOWN:
		mtype = sdpMediaType_unkonwn;
		break;
	default:
		mtype = sdpMediaType_notset;
		break;
	}

	return mtype;
}

sdpProtocolType RvSdp::TransferProtocolType(RvSdpProtocol ty)
{
	sdpProtocolType ptype;
	switch (ty)
	{
	case RV_SDPPROTOCOL_NOTSET:
		ptype = sdpProtocolType_notset;
		break;
	case RV_SDPPROTOCOL_RTP:
		ptype = sdpProtocolType_rtpavp;
		break;
	case RV_SDPPROTOCOL_LOCAL:
		ptype = sdpProtocolType_local;
		break;
	case RV_SDPPROTOCOL_ATM:
		ptype = sdpProtocolType_atmavp;
		break;
	case RV_SDPPROTOCOL_UDP:
		ptype = sdpProtocolType_udp;
		break;
	case RV_SDPPROTOCOL_TCP:
		ptype = sdpProtocolType_tcp;
		break;
	default:
		ptype = sdpProtocolType_notset;
		break;
	}

	return ptype;
}


/*
v=0
o=34020000001180000002 0 0 IN IP4 192.168.8.196
s=Playback
c=IN IP4 192.168.8.196
u=34020000001340000001:1
t=1351137600 1351141200
m=video 7280 RTP/AVP 96 98 97
a=recvonly
a=rtpmap:96 PS/90000
a=rtpmap:98 H264/90000
a=rtpmap:97 MPEG4/90000
*/
void RvSdp::ObtainUnregularHead(char* pMsg)
{
#if 0
	if (pMsg == NULL)
	{
		return ;
	}

	std::string uri = pMsg;
/*	std::list<string> strList;
  SegString(uri, strList, "\\r\\n");
  uri.replace()
*/
	int upos = 0;
	upos = uri.find("u=");
	if (upos <= 0)
	{
		return;
	}
	int linetoend = uri.find("=", upos + 2);
	std::string u;
	if (linetoend <= 0)
	{
		u = uri.substr(upos, uri.length() - upos);
	}
	else
	{
		u = uri.substr(upos, linetoend - upos - 2);
	}

	std::string u2 = uri.substr(upos, linetoend  - upos - 1);
	strcpy(uri, u2.c_str());
	 
	uri.erase(upos, linetoend  - upos - 1);


	memset(pMsg, 0, strlen(pMsg));
	strcpy(pMsg, uri.c_str());

#endif

}
