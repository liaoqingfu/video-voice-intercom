#include "SipMessage.h"
#include "MansRtsp.h"
#include "HostDomain.h"

#include "GBStandard.h"
#include "SipMgr.h"
#include <string>

#pragma warning(disable:4101)



bool CheckIpPortAddress(char* str)
{
	//CRegexpT <char> regexp1("((2[0-4]\d|25[0-5]|[01]?\d\d?)\.){3}(2[0-4]\d|25[0-5]|[01]?\d\d?)");
	CRegexpT <char> regexp1("[\\d]{1,3}\\.[\\d]{1,3}\\.[\\d]{1,3}\\.[\\d]{1,3}");
	MatchResult result1 = regexp1.MatchExact(str);
	if (result1.IsMatched() == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//#define _HOSTPORT

HostDomain g_HostMgr;


SipMessage::SipMessage()
{
	m_pMsgBody = NULL;
	memset(&m_sipHeader, 0, sizeof(sipHead));
	m_pMsgBody = new char[BODY_SIZE];
	memset(m_pMsgBody, 0, BODY_SIZE);
	memset(m_appCmdType, 0, sizeof(m_appCmdType));

	m_hCallLeg = NULL;
	m_hTransc = NULL;
	m_hSubs = NULL;
	m_hRegClient = NULL;

	memset(fromHeader, 0, sizeof(fromHeader));
	memset(toHeader, 0, sizeof(toHeader));
	memset(routeHeader, 0, sizeof(routeHeader));
	memset(requestUri, 0, sizeof(requestUri));
	memset(domainFiled, 0, sizeof(domainFiled));


	m_bodySize = 0;
}

SipMessage::SipMessage(const SipMessage& msg)
{
	m_pMsgBody = NULL;
	memset(&m_sipHeader, 0, sizeof(sipHead));
	if (m_pMsgBody == NULL)
	{
		m_pMsgBody = new char[BODY_SIZE];
		memset(m_pMsgBody, 0, BODY_SIZE);
	}

	m_hCallLeg = NULL;
	m_hTransc = NULL;
	m_hSubs = NULL;
	m_hRegClient = NULL;

	memset(fromHeader, 0, sizeof(fromHeader));
	memset(toHeader, 0, sizeof(toHeader));
	memset(routeHeader, 0, sizeof(routeHeader));
	memset(requestUri, 0, sizeof(requestUri));
	memset(domainFiled, 0, sizeof(domainFiled));

	memcpy_s(&m_sipHeader, sizeof(sipHead), &(msg.m_sipHeader), sizeof(sipHead));
	//消息体
	if (m_pMsgBody != NULL && msg.m_pMsgBody != NULL)
	{
		memcpy_s(m_pMsgBody, BODY_SIZE, msg.m_pMsgBody, BODY_SIZE);
		m_bodySize = msg.m_bodySize;
	}

	strcpy(fromHeader, msg.fromHeader);
	strcpy(toHeader, msg.toHeader);
	strcpy(routeHeader, msg.routeHeader);
	strcpy(requestUri, msg.requestUri);
	strcpy(domainFiled, msg.domainFiled);

	m_hCallLeg = msg.m_hCallLeg;
	m_hTransc = msg.m_hTransc;
	m_hSubs = msg.m_hSubs;
	m_hRegClient = msg.m_hRegClient;
}


const SipMessage& SipMessage::operator=(const SipMessage& msg)
{
	if (&msg == this)
		return *this;

	memcpy_s(&m_sipHeader, sizeof(sipHead), &(msg.m_sipHeader), sizeof(sipHead));
	//消息体
	if (m_pMsgBody != NULL && msg.m_pMsgBody != NULL)
	{
		memcpy_s(m_pMsgBody, BODY_SIZE, msg.m_pMsgBody, BODY_SIZE);
		m_bodySize = msg.m_bodySize;
	}

	//sdp消息体
	strcpy(fromHeader, msg.fromHeader);
	strcpy(toHeader, msg.toHeader);
	strcpy(routeHeader, msg.routeHeader);
	strcpy(requestUri, msg.requestUri);
	strcpy(domainFiled, msg.domainFiled);

	m_hCallLeg = msg.m_hCallLeg;
	m_hTransc = msg.m_hTransc;
	m_hSubs = msg.m_hSubs;
	m_hRegClient = msg.m_hRegClient;

	return *this;

}


SipMessage::~SipMessage(void)
{
	if (m_pMsgBody != NULL)
	{
		delete []m_pMsgBody;
		m_pMsgBody = NULL;
	}
}


void SipMessage::zeroSet()
{
	m_hCallLeg = NULL;
	m_hTransc = NULL;
	m_hSubs = NULL;
	m_hRegClient = NULL;

	memset(&m_sipHeader, 0, sizeof(sipHead));
	memset(m_pMsgBody, 0, BODY_SIZE);
	m_bodySize = 0;
}



void SipMessage::setSipMessageBody(const char* pbuf, int Len)
{
	if (Len > BODY_SIZE)
		return ;
	if (pbuf != NULL && m_pMsgBody != NULL)
	{
		memset(m_pMsgBody, 0, BODY_SIZE);
		memcpy_s(m_pMsgBody, BODY_SIZE, pbuf, Len);
		m_bodySize = Len;
	}
}


void SipMessage::setRoute(char* routeUsr, char* routeIp, int routePort)
{
	if (routeUsr == NULL || routeIp == NULL || routePort <= 0)
	{
		return ;
	}

	strcpy(m_sipHeader.route_usr, routeUsr);
	strcpy(m_sipHeader.route_ip, routeIp);
	m_sipHeader.route_port = routePort;

	sprintf_s(routeHeader, sizeof(routeHeader), "<sip:%s@%s:%d>", routeUsr, routeIp, routePort);
}


void SipMessage::setFrom(char* fromUsr, char* fromIp, int fromPort)
{
	if (fromUsr == NULL ||fromIp == NULL)
		return ;

	char buf[64];
	strcpy_s(m_sipHeader.from_user, sizeof(m_sipHeader.from_user), fromUsr);
	strcpy_s(m_sipHeader.from_ip, sizeof(m_sipHeader.from_ip), fromIp);
	m_sipHeader.from_port = fromPort;
  

#ifndef _HOSTPORT
	//std::string filed;
	//g_HostMgr.GetUriDomainFromHost(m_sipHeader.from_ip, m_sipHeader.from_port, filed);
	//sprintf_s(buf, sizeof(buf), "From:<sip:%s@%s>", m_sipHeader.from_user, filed.c_str());

	sprintf_s(buf, sizeof(buf), "From:<sip:%s@%s:%d>", m_sipHeader.from_user, m_sipHeader.from_ip, m_sipHeader.from_port);
#else
	sprintf_s(buf, sizeof(buf), "From:<sip:%s@%s:%d>", m_sipHeader.from_user, m_sipHeader.from_ip, m_sipHeader.from_port);
#endif
	strcpy_s(fromHeader, sizeof(fromHeader), buf);

	setContact(fromUsr, fromIp, fromPort);
}


void  SipMessage::setContact(char* contactUsr, char* contactIp, int contactPort)
{
	char buf[64];
	memset(buf, 0, sizeof(buf));
	sprintf_s(buf, sizeof(buf), "Contact:<sip:%s@%s:%d>", contactUsr, contactIp, contactPort);
	strcpy_s(m_sipHeader.contact, sizeof(m_sipHeader.contact), buf);
}


void SipMessage::setTo(char* toUsr, char* toIp, int toPort)
{
	if (toUsr == NULL ||toIp == NULL )
		return ;

	char buf[64] = { 0 };
	strcpy_s(m_sipHeader.to_user, sizeof(m_sipHeader.to_user), toUsr);
	strcpy_s(m_sipHeader.to_ip, sizeof(m_sipHeader.to_ip), toIp);
	m_sipHeader.to_port = toPort;

#ifndef _HOSTPORT
	//std::string filed;
	//g_HostMgr.GetUriDomainFromHost(m_sipHeader.to_ip, m_sipHeader.to_port, filed);
	//sprintf_s(buf, sizeof(buf), "To:<sip:%s@%s>", m_sipHeader.to_user, filed.c_str());

	sprintf_s(buf, sizeof(buf), "To:<sip:%s@%s:%d>", m_sipHeader.to_user, m_sipHeader.to_ip, m_sipHeader.to_port);
#else
	sprintf_s(buf, sizeof(buf), "To:<sip:%s@%s:%d>", m_sipHeader.to_user, m_sipHeader.to_ip, m_sipHeader.to_port);
#endif
	strcpy_s(toHeader, sizeof(toHeader), buf);

}


void SipMessage::setUri(char* uri_ip, int uri_port)
{
#ifndef _HOSTPORT
	//std::string filed;
	//g_HostMgr.GetUriDomainFromHost(m_sipHeader.to_ip, m_sipHeader.to_port, filed);
	//sprintf_s(requestUri, sizeof(requestUri), "sip:%s@%s", m_sipHeader.to_user, filed.c_str());

	sprintf_s(requestUri, sizeof(requestUri), "sip:%s:%d", uri_ip, uri_port);
#else
	sprintf_s(requestUri, sizeof(requestUri), "sip:%s:%d", uri_ip, uri_port);
#endif
}


void SipMessage::setContentType(char* contentType, int len)
{
	if (contentType != NULL && len <= sizeof(m_sipHeader.content_type))
	{
		strcpy_s(m_sipHeader.content_type, sizeof(m_sipHeader.content_type), contentType);
	}
}

void SipMessage::setAuth_realm(char* realm)
{
	if (realm != NULL)
		strcpy_s(m_sipHeader.auth_realm, sizeof(m_sipHeader.auth_realm), realm);

}

void SipMessage::setAuth_usr(char* usr)
{
	if (usr != NULL)
		strcpy_s(m_sipHeader.auth_usr, sizeof(m_sipHeader.auth_usr), usr);
}

void SipMessage::setAuth_password(char* psw)
{
	if (psw != NULL)
		strcpy_s(m_sipHeader.auth_password, sizeof(m_sipHeader.auth_password), psw);
}

void SipMessage::setEvent(const char* package, const char* id)
{
	if (package != NULL)
		strcpy_s(m_sipHeader.event_package, sizeof(m_sipHeader.event_package), package);

	if (id != NULL)
	{
		strcpy_s(m_sipHeader.event_id, sizeof(m_sipHeader.event_id), id);
	}
}



void SipMessage::setSubject(char* subject)
{
	if (subject != NULL)
		strcpy_s(m_sipHeader.subject, sizeof (m_sipHeader.subject), subject);
}



void SipMessage::sipMsgCallLegParse(RvSipCallLegHandle hCallLeg, RvSipTranscHandle hTransc)
{
	if (hCallLeg == 0)
		return ;
	m_hCallLeg = hCallLeg;
	m_hTransc = hTransc;

	RvStatus rv;
	RvSipMsgHandle hMsg;
	RvSipMethodType MethodType;

	RvSipPartyHeaderHandle PartyHead;
	RvSipAddressHandle AddrHead;
	RvUint actualLen;
	RvSipHeaderListElemHandle listElem;
	RvSipOtherHeaderHandle subjectHeader;

	//via
	RvChar strBuffer[64] = {0,};
	RvSipViaHeaderHandle viaHeader;

	rv = RvSipCallLegGetReceivedMsg(hCallLeg, &hMsg);
	//body
	rv = RvSipMsgGetBody(hMsg, m_pMsgBody, BODY_SIZE, &actualLen);

	//content-type
	rv = RvSipMsgGetContentTypeHeader(hMsg, m_sipHeader.content_type, sizeof(m_sipHeader.content_type), &actualLen);

	//获取方法名
	std::string cmdType;
	MethodType = RvSipMsgGetRequestMethod(hMsg);
	if (MethodType == RVSIP_METHOD_INVITE)
	{
		//如果是invite并且携带sdp信息，则解析sdp
		//获取方法名
		strcpy(m_sipHeader.method, INVITE);

		if (stricmp(m_sipHeader.content_type, "application/sdp") == 0)
		{
			std::string name = INVITE;


			if (strlen(m_pMsgBody) > 0 )
			{
				CGBStandard::GBParseSdpCmdTypeStr(m_pMsgBody, cmdType);
				strcpy(m_appCmdType, cmdType.c_str()); 
			}
			else
			{
				strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), "INVITE");
			}

			//subject
			subjectHeader = (RvSipOtherHeaderHandle)RvSipMsgGetHeaderByName(hMsg, "Subject", RVSIP_FIRST_HEADER, &listElem);
			if (subjectHeader != NULL)
			{
				rv = RvSipOtherHeaderGetValue(subjectHeader, m_sipHeader.subject, 64, &actualLen);
				if (rv != RV_OK)
				{
					throw 1;
				}
			}

			rv = RvSipCallLegTranscCreate(hCallLeg, NULL, &m_hTransc);
		}
		else if (MethodType == RVSIP_METHOD_BYE)
		{
			strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), BYE);
			m_hTransc = hTransc;
		}
		else if (MethodType == RVSIP_METHOD_OTHER)
		{
			//INFO方法
			rv = RvSipMsgGetStrRequestMethod(hMsg, m_sipHeader.method, sizeof(m_sipHeader.method), &actualLen);
			if (strcmp(m_sipHeader.method, INFOR) == 0)
			{
				strcpy(m_sipHeader.method, INFOR);

				CGBStandard::GBParseMansRtspCmdTypeStr(m_pMsgBody, cmdType);
				strcpy(m_appCmdType, cmdType.c_str()); 

			}//MESSAGE通知会话
			else if (strcmp(m_sipHeader.method, MESSAGE) == 0)
			{
				strcpy(m_sipHeader.method, MESSAGE);

				CGBStandard::GBParseAppCmdTypeStr(m_pMsgBody, cmdType);
				strcpy(m_appCmdType, cmdType.c_str()); 
			}
		}

		//解析from和to
		parseFromAndToHead(hMsg);
		//via
		viaHeader = (RvSipViaHeaderHandle)RvSipMsgGetHeaderByType(hMsg, RVSIP_HEADERTYPE_VIA, RVSIP_FIRST_HEADER,&listElem);
		if (viaHeader != NULL)
		{
			RvInt32 rPort = 0;
			RvBool bUse = RV_TRUE;
			rv = RvSipViaHeaderGetReceivedParam(viaHeader, strBuffer, sizeof(strBuffer), &actualLen);
			rv = RvSipViaHeaderGetRportParam(viaHeader, &rPort, &bUse);

			if (strlen(strBuffer) > 0 && strcmp(strBuffer, from_ip()) != 0)
			{
				strcpy(m_sipHeader.from_ip, strBuffer);
				m_sipHeader.from_port = rPort;
			}
		}

		//rv = RvSipCallLegTranscCreate(m_hCallLeg, NULL, &m_hTransc);

	}
}


void SipMessage::sipMsgResponseParse(RvSipMsgHandle hMsg)
{
	if (hMsg == 0)
		return ;
	RvInt16 code;
	RvStatus rv; 
	RvUint actualLen;

	RvSipMethodType MethodType;
	RvSipDateHeaderHandle dateHeader;
	RvSipHeaderListElemHandle listElem;

	try
	{
		//status code
		code = RvSipMsgGetStatusCode(hMsg);
		m_sipHeader.statuscode = code;
    //body 消息体可能有，也可能没有
		rv = RvSipMsgGetBody(hMsg, m_pMsgBody, BODY_SIZE, &actualLen);

    //content-length
		m_sipHeader.content_length = RvSipMsgGetContentLengthHeader(hMsg);

		//CallID
		rv = RvSipMsgGetCallIdHeader(hMsg, m_sipHeader.callid, 64, &actualLen);
		if (rv != RV_OK)
			throw 0;

		//Content-type
		rv = RvSipMsgGetContentTypeHeader(hMsg, m_sipHeader.content_type, 32, &actualLen);

		//dateheader
		dateHeader = (RvSipDateHeaderHandle)RvSipMsgGetHeaderByTypeExt(hMsg, RVSIP_HEADERTYPE_DATE, RVSIP_FIRST_HEADER, RVSIP_MSG_HEADERS_OPTION_ALL, &listElem);
		if (dateHeader != NULL)
		{
			rv = RvSipDateHeaderGetStrBadSyntax(dateHeader, m_sipHeader.datecheck, sizeof(m_sipHeader.datecheck), &actualLen);
		}

	}
	catch (...)
	{

	}

}


void SipMessage::sipMsgRegParse(RvSipRegClientHandle hRegClient)
{
	RvStatus rv;
	RvSipMsgHandle hMsg;
	RvSipPartyHeaderHandle hFrom;
	RvUint actualLen;
  
	rv = RvSipRegClientGetReceivedMsg(hRegClient, &hMsg);

	//parse From / To
	parseFromAndToHead(hMsg);

	//method
	strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), REGISTER);

 //Authorization:
}

void SipMessage::sipMsgNotifyParse(RvSipMsgHandle hMsg, RvSipSubsHandle hSubs, RvSipNotifyHandle hNotify)
{
	RvStatus rv;
	RvUint actualLen;
	RvSipEventHeaderHandle hEvent;
	RvSipMethodType MethodType;
	RvSipSubscriptionSubstate NotifyState;
	RvSipSubscriptionStateHeaderHandle hSubsState;

	//parse From / To
	parseFromAndToHead(hMsg);

	//Content-type
	rv = RvSipMsgGetContentTypeHeader(hMsg, m_sipHeader.content_type, sizeof(m_sipHeader.content_type), &actualLen);
	//Content-length
	m_sipHeader.content_length = RvSipMsgGetContentLengthHeader(hMsg);

	//event;
	rv = RvSipSubsGetEventHeader(hSubs, &hEvent);
	if (rv == RV_OK)
	{
		//rv = RvSipEventHeaderGetEventParam(hEvent, m_sipHeader.event, sizeof(m_sipHeader.event), &actualLen);
		RvSipEventHeaderGetEventPackage(hEvent, m_sipHeader.event_package, sizeof(m_sipHeader.event_package), &actualLen);
		RvSipEventHeaderGetEventId(hEvent, m_sipHeader.event_id, sizeof(m_sipHeader.event_id), &actualLen);
	}
	//expires
	rv = RvSipSubsGetRequestedExpiresVal(hSubs, &(m_sipHeader.expires));
  //body
	rv = RvSipMsgGetBody(hMsg, m_pMsgBody, BODY_SIZE, &actualLen);
	//state
	if (hNotify != NULL)
	{
		rv = RvSipNotifyGetSubsState(hNotify, &NotifyState);
		if (NotifyState == RVSIP_SUBSCRIPTION_SUBSTATE_ACTIVE)
			sprintf_s(m_sipHeader.subscription_state, sizeof(m_sipHeader.subscription_state), "%s", "active");
    //note
		/*according to RvSipLib, may be never get the params*/

		//rv = RvSipSubscriptionStateHeaderGetStrSubstate(hSubsState, m_sipHeader.subscription_state, 
		//	sizeof(m_sipHeader.subscription_state), &actualLen); 
		//m_sipHeader.expires = RvSipSubscriptionStateHeaderGetExpiresParam(hSubsState);
		//m_sipHeader.subscription_state_retryafter = RvSipSubscriptionStateHeaderGetRetryAfter(hSubsState);
	}
	//method
	//获取方法名
	MethodType = RvSipMsgGetRequestMethod(hMsg);
	if (MethodType == RVSIP_METHOD_NOTIFY)
		strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), NOTIFY);
}



void SipMessage::sipMsgSubsParse(RvSipSubsHandle hSubs, RvSipNotifyHandle hNotify)
{
	RvStatus rv;
	RvSipMsgHandle hMsg;
	RvUint actualLen;
	RvSipEventHeaderHandle hEvent;
	RvSipMethodType MethodType;
	RvSipSubscriptionSubstate NotifyState;
	RvSipSubscriptionStateHeaderHandle hSubsState;

	if (hSubs == 0)
		return ;
    m_hSubs = hSubs;

	rv = RvSipSubsGetReceivedMsg(hSubs, &hMsg);

	//parse From / To
	parseFromAndToHead(hMsg);

	//Content-type
	rv = RvSipMsgGetContentTypeHeader(hMsg, m_sipHeader.content_type, sizeof(m_sipHeader.content_type), &actualLen);
	//Content-length
	m_sipHeader.content_length = RvSipMsgGetContentLengthHeader(hMsg);

	//event;
	rv = RvSipSubsGetEventHeader(hSubs, &hEvent);
	if (rv == RV_OK)
	{
		//rv = RvSipEventHeaderGetEventParam(hEvent, m_sipHeader.event, sizeof(m_sipHeader.event), &actualLen);
		RvSipEventHeaderGetEventPackage(hEvent, m_sipHeader.event_package, sizeof(m_sipHeader.event_package), &actualLen);
		RvSipEventHeaderGetEventId(hEvent, m_sipHeader.event_id, sizeof(m_sipHeader.event_id), &actualLen);
	}
	//expires
	rv = RvSipSubsGetRequestedExpiresVal(hSubs, &(m_sipHeader.expires));
  //body
	rv = RvSipMsgGetBody(hMsg, m_pMsgBody, BODY_SIZE, &actualLen);
	//state
	if (hNotify != NULL)
	{
		rv = RvSipNotifyGetSubsState(hNotify, &NotifyState);
		if (NotifyState == RVSIP_SUBSCRIPTION_SUBSTATE_ACTIVE)
			sprintf_s(m_sipHeader.subscription_state, sizeof(m_sipHeader.subscription_state), "%s", "active");
    //note
		/*according to RvSipLib, may be never get the params*/

		//rv = RvSipSubscriptionStateHeaderGetStrSubstate(hSubsState, m_sipHeader.subscription_state, 
		//	sizeof(m_sipHeader.subscription_state), &actualLen); 
		//m_sipHeader.expires = RvSipSubscriptionStateHeaderGetExpiresParam(hSubsState);
		//m_sipHeader.subscription_state_retryafter = RvSipSubscriptionStateHeaderGetRetryAfter(hSubsState);
	}
	//method
	//获取方法名
	MethodType = RvSipMsgGetRequestMethod(hMsg);
	if (MethodType == RVSIP_METHOD_NOTIFY)
		strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), NOTIFY);
	if (MethodType == RVSIP_METHOD_SUBSCRIBE)
		strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), SUBSCRIBE);
}


void SipMessage::sipMsgTransaParse(RvSipTranscHandle& hTransc)
{
	if (hTransc == 0)
		return ;

	m_hTransc = hTransc;

	RvStatus rv; 
	RvSipMsgHandle hMsg;

	RvChar strBuffer[64] = {0,};
	RvUint actualLen;
	RvUint length;
	RvUint32 bodylength;

  //Cseq
	RvSipCSeqHeaderHandle CSeqHead;

	//via
	RvSipViaHeaderHandle viaHeader;
	RvSipHeaderListElemHandle listElem;

	RvSipOtherHeaderHandle OtherHead;

	try
	{
		rv = RvSipTransactionGetReceivedMsg(hTransc, &hMsg);
		if (rv != RV_OK)
			throw 0;

		//parse method name
		parseMethodAndBody(hMsg);
		
		//CallID
		rv = RvSipMsgGetCallIdHeader(hMsg, m_sipHeader.callid, sizeof(m_sipHeader.callid), &actualLen);
		if (rv != RV_OK)
			throw 0;

    //parse From / To
		parseFromAndToHead(hMsg);

		//cseq
		CSeqHead =  RvSipMsgGetCSeqHeader(hMsg);
		m_sipHeader.cseq = RvSipCSeqHeaderGetStep(CSeqHead);
		//Contact

		//via
		viaHeader = (RvSipViaHeaderHandle)RvSipMsgGetHeaderByType(hMsg, RVSIP_HEADERTYPE_VIA, RVSIP_FIRST_HEADER,&listElem);
		if (viaHeader != NULL)
		{
			RvInt32 rPort = 0;
			RvBool bUse = RV_TRUE;
			memset(strBuffer, 0, sizeof(strBuffer));
			rv = RvSipViaHeaderGetReceivedParam(viaHeader, strBuffer, sizeof(strBuffer), &actualLen);
			rv = RvSipViaHeaderGetRportParam(viaHeader, &rPort, &bUse);

			if (strlen(strBuffer) > 0 && strcmp(strBuffer, from_ip()) != 0)
			{
				strcpy(m_sipHeader.from_ip, strBuffer);
				m_sipHeader.from_port = rPort;
			}
		}

		//Expires
		RvSipExpiresHeaderHandle ExpiresHandle;
		RvSipHeaderListElemHandle ListElem;
		ExpiresHandle =	(RvSipExpiresHeaderHandle)RvSipMsgGetHeaderByType(hMsg, RVSIP_HEADERTYPE_EXPIRES, RVSIP_FIRST_HEADER, &ListElem);
		if (ExpiresHandle != NULL)
		{
			RvUint32 detailSecond;
			RvSipExpiresHeaderGetDeltaSeconds(ExpiresHandle, (RvUint32*)&detailSecond);
			setExpires(detailSecond);
		}

		//Content-length
		m_sipHeader.content_length = RvSipMsgGetContentLengthHeader(hMsg);

		//Content-type
		rv = RvSipMsgGetContentTypeHeader(hMsg, m_sipHeader.content_type, sizeof(m_sipHeader.content_type), &actualLen);

	}
	catch (...)
	{
		
	}

}


void SipMessage::parseFromAndToHead(RvSipMsgHandle& hMsg)
{
	RvStatus rv; 
	RvUint actualLen;
	RvUint length;
	RvSipPartyHeaderHandle PartyHead;
	RvSipAddressHandle AddrHead;

	//From
	PartyHead = RvSipMsgGetFromHeader(hMsg);
	AddrHead = RvSipPartyHeaderGetAddrSpec(PartyHead);
	length = RvSipAddrGetStringLength(AddrHead, RVSIP_ADDRESS_HOST);
	//获取from的user
	rv = RvSipAddrUrlGetUser(AddrHead, m_sipHeader.from_user, sizeof(m_sipHeader.from_user), &actualLen);

	char filedFrom[64] = {0};
	rv = RvSipAddrUrlGetHost(AddrHead, filedFrom, sizeof(filedFrom), &length);
	//判断是否包含域名
	if (CheckIpPortAddress(filedFrom))
	{
		strcpy(m_sipHeader.from_ip, filedFrom);
		m_sipHeader.from_port = RvSipAddrUrlGetPortNum(AddrHead);
	}
	else
	{
		//domain
		std::string FromIp;
		CSipMgr::g_HostMomainResolve.GetHostFromDomain(filedFrom, m_sipHeader.from_user, FromIp, &m_sipHeader.from_port);
		strcpy(m_sipHeader.from_ip, FromIp.c_str());
	}


	//To
	PartyHead = RvSipMsgGetToHeader(hMsg);
	AddrHead = RvSipPartyHeaderGetAddrSpec(PartyHead);
	length = RvSipAddrGetStringLength(AddrHead, RVSIP_ADDRESS_HOST);
	//获取to的user
	rv = RvSipAddrUrlGetUser(AddrHead, m_sipHeader.to_user, sizeof(m_sipHeader.to_user), &actualLen);
	char filedTo[64] = {0};
	rv = RvSipAddrUrlGetHost(AddrHead, filedTo, sizeof(filedTo), &length);
	if (CheckIpPortAddress(filedTo))
	{
		strcpy(m_sipHeader.to_ip, filedTo);
		m_sipHeader.to_port = RvSipAddrUrlGetPortNum(AddrHead);
	}
	else
	{
		//domain
		std::string FromIp;
		CSipMgr::g_HostMomainResolve.GetHostFromDomain(filedTo, m_sipHeader.to_user, FromIp, &m_sipHeader.to_port);
		strcpy(m_sipHeader.to_ip, FromIp.c_str());
	}

}


void SipMessage::parseMethodAndBody(RvSipMsgHandle& hMsg)
{
	RvStatus rv;
	RvChar strBuffer[16];
	RvUint actualLen;
	RvSipMethodType MethodType;

	//获取方法名
	MethodType = RvSipMsgGetRequestMethod(hMsg);

	rv = RvSipMsgGetBody(hMsg, m_pMsgBody, BODY_SIZE, &actualLen);
	//如果是DO方法
	if (MethodType == RVSIP_METHOD_OTHER)
	{
		rv = RvSipMsgGetStrRequestMethod(hMsg, m_sipHeader.method, sizeof(m_sipHeader.method), &actualLen);
		if (strcmp(m_sipHeader.method, MESSAGE) != 0)
			return ;
	}
	else
	{
		switch(MethodType)
		{
		case RVSIP_METHOD_INVITE:
			strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), INVITE);
			break;
		case RVSIP_METHOD_ACK:
			strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), ACK);
			break;
		case RVSIP_METHOD_BYE:
			strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), BYE);
			break;
		case RVSIP_METHOD_REGISTER:
			strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), REGISTER);
			break;
		case RVSIP_METHOD_NOTIFY:
			strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), NOTIFY);
			break;
		case RVSIP_METHOD_CANCEL:
			strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), CANCEL);
			break;
		case RVSIP_METHOD_SUBSCRIBE:
			strcpy_s(m_sipHeader.method, sizeof(m_sipHeader.method), SUBSCRIBE);
			break;
		default:
			break;
		}
		if (strlen(m_pMsgBody) == 0)
			return ;
	}

	//解析出sip方法的功能类型串
	std::string strCmdType;
	CGBStandard::GBParseAppCmdTypeStr(m_pMsgBody, strCmdType);
	strcpy(m_appCmdType, strCmdType.c_str());

}


void SipMessage::setDateCheck(char* date)
{
	if (date == NULL)
	{
		return ;
	}

	memset(m_sipHeader.datecheck, 0, sizeof(m_sipHeader.datecheck));
	strcpy(m_sipHeader.datecheck, date);
}


//Contact:<sip:34010000001310000028@192.168.100.145:5060>
void SipMessage::parseContact(const char* contact, char* contactUsr, char* contactIp, char* contactPort)
{
	assert(contact != NULL || contactUsr != NULL || contactIp != NULL || contactPort != NULL);

	std::string cont = contact;
	int pos = cont.find_first_of(':', 0);
	pos = cont.find_first_of(':', pos + 1);
	int pos2 = cont.find_first_of('@', pos);
	std::string usr = cont.substr(pos + 1, pos2 - pos - 1);

	int pos3 = cont.find_last_of(':');
	std::string port = cont.substr(pos3 + 1, cont.length() - pos3 - 1 - 1);
	std::string ip = cont.substr(pos2 + 1,  pos3 - pos2 - 1);
	//unsafe 
	strcpy(contactUsr, usr.c_str());
	strcpy(contactIp, ip.c_str());
	strcpy(contactPort, port.c_str());

}