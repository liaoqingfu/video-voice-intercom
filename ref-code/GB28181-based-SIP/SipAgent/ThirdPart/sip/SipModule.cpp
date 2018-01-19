#include "SipModule.h"

#include "SipMgr.h"
#include "GBStandard.h"

#include <list>
#include <string>


//define static variable
ServerFunctionStorage CSipClientRegistar::m_RegAppFunStorage;
ServerFunctionStorage CSipInviteCall::m_CallLegAppFunStorage;
ServerFunctionStorage CSipTransaction::m_TransAppFunStorage;
ServerFunctionStorage CSipAuthCall::m_AuthAppFunStorage;
ServerFunctionStorage CSipSubscribe::m_SubscribeAppFunStorage;


CBlockPattern<ClientRequest::ClientData> CSipClientRegistar::m_RegClientRequestBlock;
CBlockPattern<ClientRequest::ClientData> CSipInviteCall::m_CalllegClientRequestBlock;
CBlockPattern<ClientRequest::ClientData> CSipTransaction::m_TransClientRequestBlock;
CBlockPattern<ClientRequest::ClientData> CSipAuthCall::m_AuthClientRequestBlock;
CBlockPattern<ClientRequest::ClientData> CSipSubscribe::m_SubClientRequestBlock;


std::list<RegTransExpires > CSipTransaction::g_RegExpiresList;


#define RETRY_AFTER 90

#define _SIP_PRINT

/////////////////////////////////////
CSipBasicModule::CSipBasicModule(void)
{
}

CSipBasicModule::~CSipBasicModule(void)
{
}


CSipClientRegistar::CSipClientRegistar(void)
{
}

CSipClientRegistar::~CSipClientRegistar(void)
{
}


CSipInviteCall::CSipInviteCall(void)
{
}

CSipInviteCall::~CSipInviteCall(void)
{
}


CSipTransaction::CSipTransaction(void)
{
}

CSipTransaction::~CSipTransaction(void)
{
}



CSipAuthCall::CSipAuthCall(void)
{
}

CSipAuthCall::~CSipAuthCall(void)
{
}


CSipSubscribe::CSipSubscribe(void)
{
}


CSipSubscribe::~CSipSubscribe(void)
{
}


void Utility::SipMsgPrint(RvSipMsgHandle hMsg)
{
	RvStatus   rv;
	HPAGE       hPage;
	RvChar     *msgBuf;
	RvUint32   msgSize;

	/* getting the encoded message on an rpool page.*/
	rv = RvSipMsgEncode(hMsg, CSipMgr::g_appPool, &hPage, &msgSize);
	if (rv != RV_OK)
	{
		_LOG(LOG_LEVEL_DEBUG, "Message encoding failed");
		//RvSipStackDestruct(g_hStackMgr);
		//exit(1);
	}
	/*allocate a consecutive buffer - use UTILS since malloc doesn't work on all OS's */
	msgBuf = (RvChar *)RvSipMidMemAlloc(msgSize+1);

	/* copy the encoded message to an external consecutive buffer*/
	rv = RPOOL_CopyToExternal(CSipMgr::g_appPool,
		hPage,
		0,
		(void*)msgBuf,
		msgSize);
	/*terminate the buffer with null*/
	msgBuf[msgSize] = '\0';
	if(rv != RV_OK)
	{
		_LOG(LOG_LEVEL_DEBUG, "Message encoding failed");
		/*free the page the encode function allocated*/
		RPOOL_FreePage(CSipMgr::g_appPool, hPage);
		RvSipMidMemFree(msgBuf);
		/*
		RvSipStackDestruct(g_hStackMgr);
		exit(1);*/
	}
	_LOG(LOG_LEVEL_DEBUG, "%s",msgBuf);
	/*free the page the encode function allocated*/
	RPOOL_FreePage(CSipMgr::g_appPool, hPage);
	RvSipMidMemFree(msgBuf);
}


void ServerResponse::ServerThreadProc(SipMessage& message, SipMethod method)
{
	int result = 0;
	method(message, result, NULL);
	//sip 回复
	ServerResponse::MakeServerResponse(message, result);
}

void ServerResponse::MakeServerResponse(SipMessage& msg, int iresult)
{
	CSipInviteCall::SipServerResponse(msg, iresult);
	CSipTransaction::SipServerResponse(msg, iresult);
	CSipClientRegistar::SipServerResponse(msg, iresult);
	CSipSubscribe::SipServerResponse(msg, iresult);
}



RvStatus ClientRequest::ClientRecord(RvSipMsgHandle hMsg, void* handle)
{
	RvSipMsgType MsgType;
	RvStatus rv;

	//记录发送的请求的callID，处理其返回
	MsgType = RvSipMsgGetMsgType(hMsg);
	if (MsgType == RVSIP_MSG_REQUEST)
	{
		//设置发送请求的via值
		RvSipViaHeaderHandle  hVia;
		RvSipHeaderListElemHandle hListElemHandle;
		hVia = (RvSipViaHeaderHandle)RvSipMsgGetHeaderByType(hMsg, RVSIP_HEADERTYPE_VIA, RVSIP_FIRST_HEADER,&hListElemHandle);
		if (hVia != NULL)
		{
			SipMessage msg;
			msg.parseFromAndToHead(hMsg);
			rv = RvSipViaHeaderSetRportParam(hVia, (RvInt32)msg.from_port(), RV_TRUE);
			char buf[64] = {0};
			sprintf_s(buf, "%s:%d", msg.from_ip(), msg.from_port());
			rv = RvSipViaHeaderSetHost(hVia, buf);
		}

		RvChar callid[64];
		RvUint actualLen = 0;
		RvSipMethodType MethodType;
		char method[64];
		char* pBuf = new char[BODY_SIZE];
		memset(pBuf, 0, BODY_SIZE);
		TiXmlDocument *xml = NULL;

		do 
		{
			rv = RvSipMsgGetCallIdHeader(hMsg, callid, sizeof(callid), &actualLen);

			rv = RvSipMsgGetBody(hMsg, pBuf, BODY_SIZE, &actualLen);

			//获取方法名
			MethodType = RvSipMsgGetRequestMethod(hMsg);
			if (MethodType == RVSIP_METHOD_OTHER)
			{
				rv = RvSipMsgGetStrRequestMethod(hMsg, method, sizeof(method), &actualLen);
				if (strcmp(method, MESSAGE) == 0)
				{
					ClientRequest::ClientData cl(callid, handle);
					CSipTransaction::m_TransClientRequestBlock.AddBlock(cl);
				}
			}
			else   
			{
				switch(MethodType)
				{
				case RVSIP_METHOD_INVITE:
					{
						ClientRequest::ClientData cl(callid, handle);
						CSipInviteCall::m_CalllegClientRequestBlock.AddBlock(cl);
					}
					break;
				case RVSIP_METHOD_ACK:
					{

					}
					break;
				case RVSIP_METHOD_BYE:
					{

					}
					break;
				case RVSIP_METHOD_REGISTER:
					{
						ClientRequest::ClientData cl(callid, handle);
						CSipClientRegistar::m_RegClientRequestBlock.AddBlock(cl);
					}
					break;
				case RVSIP_METHOD_NOTIFY:
					{
						ClientRequest::ClientData cl(callid, handle);
						CSipTransaction::m_TransClientRequestBlock.AddBlock(cl);
					}
					break;
				case RVSIP_METHOD_CANCEL:
					{

					}
					break;
				case RVSIP_METHOD_SUBSCRIBE:
					{

					}
					break;
				default:
					break;
				}

			}
			//std::string strCmdType;
			//CGBStandard::GBParseAppCmdTypeStr(pBuf, strCmdType);

		} while (0);

		delete []pBuf;
		pBuf = NULL;

	}//end if (MsgType == RVSIP_MSG_REQUEST)

	return RV_OK;
}


RvStatus ClientRequest::ClientResponseRecord(RvSipMsgHandle hMsg, void* handle)
{
	RvStatus rv;
	RvSipMsgType MsgType;
	int iresult = 0;
	MsgType = RvSipMsgGetMsgType(hMsg);
	//如果是发出请求的回复状态则处理
	if (MsgType == RVSIP_MSG_RESPONSE)
	{
		SipMessage msg;
		msg.sipMsgResponseParse(hMsg);
		if (handle != NULL)
			msg.m_hCallLeg = (RvSipCallLegHandle)handle;
		
		if (msg.status_code() == 100)
		{
			return RV_OK;
		}

		ClientNotifyResponse(response_normal, handle, msg);
	}

	return RV_OK;
}


void ClientRequest::ClientNotifyResponse(responseType type, void* handle, SipMessage& msg)
{
	ClientRequest::ClientData cl(msg.m_sipHeader.callid, handle);
	if (type == response_normal)
	{
		cl.restype = response_normal;
		cl.msg = msg;
		CSipClientRegistar::m_RegClientRequestBlock.Resume(cl);
		CSipInviteCall::m_CalllegClientRequestBlock.Resume(cl);
		CSipTransaction::m_TransClientRequestBlock.Resume(cl);
	}
	else if (type == response_timeout)
	{
		cl.restype = response_timeout;
		cl.msg = msg;
		CSipClientRegistar::m_RegClientRequestBlock.Resume(cl);
		CSipInviteCall::m_CalllegClientRequestBlock.Resume(cl);
		CSipTransaction::m_TransClientRequestBlock.Resume(cl);
	}
}


void CSipClientRegistar::SetCallbackFunctions()
{
	RvStatus rv;
	RvSipRegClientEvHandlers appEvHandlers;

	/*Reset the appEvHandlers */
	memset(&appEvHandlers,0,sizeof(RvSipRegClientEvHandlers));

	/*Set application callbacks in the structure*/
	appEvHandlers.pfnStateChangedEvHandler   = RegClientStateChangedEvHandler;
	appEvHandlers.pfnMsgReceivedEvHandler    = RegClientMsgReceivedEvHandler;
	appEvHandlers.pfnMsgToSendEvHandler      = RegClientMsgToSendEvHandler;

	/*Set the structure in the register-client manager*/
	rv = RvSipRegClientMgrSetEvHandlers(CSipMgr::g_hRegClientMgr, &appEvHandlers, sizeof(RvSipRegClientEvHandlers));
	if(rv != RV_OK)
	{
		_LOG(LOG_LEVEL_DEBUG, "sip RegisterClient Set EventCallbackHandle Failed");
	}
}

#if 0
void CSipRegistar::RegisterAppFunc(const char* request, const char* functionCmdType, SipMethod method, void* data)
{
	m_RegAppFunStorage.AddAppFun(request, functionCmdType, method, data);
}
#endif


void CSipClientRegistar::SipServerResponse(SipMessage& msg, int iresult)
{
	RvStatus rv;
	if (strcmp(msg.method(), REGISTER) == 0)
	{
		RegTransExpires exp;
		exp.handle = (void*)msg.m_hTransc;
		exp.expires = msg.expires();
		CSipTransaction::g_RegExpiresList.push_back(exp);
		rv = RvSipTransactionAuthBegin(msg.m_hTransc);
		if(rv != RV_OK)
		{
			_LOG(LOG_LEVEL_DEBUG, "Failed to begin to the authentication");
		}

		if (msg.expires() > 0)
		{
			RegTransExpires exp;
			exp.handle = (void*)msg.m_hTransc;
			exp.expires = msg.expires();
			//g_RegExpiresList.push_back(exp);
			rv = RvSipTransactionAuthBegin(msg.m_hTransc);
			if(rv != RV_OK)
			{
				_LOG(LOG_LEVEL_DEBUG, "Failed to begin to the authentication");
			}
		}
		else
		{
			rv = RvSipTransactionAuthBegin(msg.m_hTransc);
			if(rv != RV_OK)
			{
				_LOG(LOG_LEVEL_DEBUG, "Failed to begin to the authentication");
			}
#if 0
			//unregister
			rv = RvSipTransactionRespond(msg.m_hTransc, SIP_SUCCESS, NULL);
			if(rv != RV_OK)
			{
				_LOG(LOG_LEVEL_DEBUG, "RvSipTransactionRespond fail(transaction %x)\n",(int)msg.m_hTransc);
			}
#endif
		}
	}

}


int CSipClientRegistar::SipClientRequest(SipMessage& msg)
{
	if (strcmp(msg.method(), REGISTER) == 0)
	{
		RvSipRegClientHandle     hRegClient;/*handle to the register-client*/
		RvStatus                rv;
		RvSipExpiresHeaderHandle hExpiresHeader;
		RvSipMsgHandle   hMsg;

		RvSipOtherHeaderHandle hHeader;
		RvSipHeaderListElemHandle hListElem;
		RvSipAuthorizationHeaderHandle* phA;
		RvSipRouteHopHeaderHandle hRouteHeader;
		RvSipAddressHandle hAddrHeader;

		RvInt32                actualSize;

		RvSipAuthorizationHeaderHandle hAuthorHeader;//Authorization:
		//char sAuth[] = "Authorization:Digest username=\"bv\",realm=\"bv\",nonce=\"cc4b7484724b\",uri=\"sip:127.0.0.1:5060\",response=\"938c0e37d\",algorithm=MD5,opaque=\"\"";

		try
		{
			rv = RvSipRegClientMgrCreateRegClient(CSipMgr::g_hRegClientMgr,NULL,&hRegClient);
			if(rv != RV_OK)
				throw SIP_REQUEST_FAILED;
			////////////////////////////////
			rv = RvSipRegClientGetNewExpiresHeaderHandle(hRegClient, &hExpiresHeader);
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;
			std::string str;
			str += "Expires:";
			char s[32] = {0};
			sprintf(s, "%d", msg.expires());
			str += s;
			rv = RvSipExpiresHeaderParse(hExpiresHeader, (RvChar*)str.c_str());
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;
			rv = RvSipRegClientSetExpiresHeader(hRegClient, hExpiresHeader);
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;
			rv = RvSipRegClientResetOutboundMsg(hRegClient);
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;

			rv = RvSipRegClientGetOutboundMsg(hRegClient, &hMsg);
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;

#if ROUTE_HEADER
			rv = RvSipRouteHopHeaderConstructInMsg(hMsg, RV_FALSE, &hRouteHeader);
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;
			rv = RvSipAddrConstructInRouteHopHeader(hRouteHeader, RVSIP_ADDRTYPE_URL, &hAddrHeader);

			rv = RvSipAddrUrlSetUser(hAddrHeader, msg.route_usr());
			rv = RvSipAddrUrlSetHost(hAddrHeader, msg.route_ip());
			rv = RvSipAddrUrlSetPortNum(hAddrHeader, msg.route_port());
			rv = RvSipAddrUrlSetLrParam(hAddrHeader, RV_TRUE);
			rv = RvSipRouteHopHeaderSetAddrSpec(hRouteHeader, hAddrHeader);
#endif
#if 0
			rv = RvSipOtherHeaderConstructInMsg(hMsg,RV_FALSE,&hHeader);
			rv = RvSipOtherHeaderSetName(hHeader,"Authorization");
			rv = RvSipOtherHeaderSetValue(hHeader,"Digest username=\"bv\",realm=\"bv\",nonce=\"cc4b7484724b\",
				uri=\"sip:127.0.0.1:5060\",response=\"938c0e37d\",algorithm=MD5,opaque=\"\"");
#endif
			//rv = RvSipAuthorizationHeaderConstructInMsg(hMsg, RV_FALSE, &hAuthorHeader);
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;
			//rv = RvSipAuthorizationHeaderParseValue(hAuthorHeader, sAuth);
			//rv = RvSipAuthorizationHeaderParse(hAuthorHeader, sAuth);
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;
			//RVSIP_HEADERTYPE_AUTHORIZATION
			//rv = RvSipMsgSetBody(hMsg, "this is a Register body");
			//if (rv != RV_OK)
			//	throw SIP_REQUEST_FAILED;
			//RVSIP_NEXT_HEADER
			//	void* RvSipMsgGetHeaderByType(
			//phA = (RvSipAuthorizationHeaderHandle*)RvSipMsgGetHeaderByType(hOutMsg, RVSIP_HEADERTYPE_AUTHORIZATION,
			//	RVSIP_FIRST_ELEMENT, &hListElem);

			//rv = RvSipMsgConstructHeaderInMsgByType(hOutMsg, RVSIP_HEADERTYPE_AUTHORIZATION, RV_FALSE, &phA);
			//rv = RvSipAuthorizationHeaderParseValue(phA, sAuth);
			////////////////////////////

			//rv = RvSipRegClientAuthenticate(hRegClient);
			msg.m_hRegClient = hRegClient;
			/*
			char str[32] = { 0 };
			sprintf_s(str, sizeof(str), "%s:%d", msg.uri(), msg.to_port());*/

			rv = RvSipRegClientMake(hRegClient, msg.from(), msg.to(), msg.uri(),msg.contact());
			//rv = RvSipRegClientRegister(hRegClient);
			if(rv != RV_OK)
				throw SIP_REQUEST_FAILED;
		}
		catch (...)
		{
			return SIP_REQUEST_FAILED;
		}

		if (hRegClient != NULL)
		{
			//阻塞否
			ClientRequest::ClientData cl("", (void*)hRegClient);
			m_RegClientRequestBlock.Suspend(cl);

			msg = cl.msg;
		}

	}

	return SIP_OK;
}


//register
void _stdcall CSipClientRegistar::RegClientStateChangedEvHandler(
	RvSipRegClientHandle            hRegClient,
	RvSipAppRegClientHandle         hAppRegClient,
	RvSipRegClientState             eState,
	RvSipRegClientStateChangeReason eReason)
{
	RvStatus rv;
	RvSipMsgHandle hMsg;
	RvSipAuthorizationHeaderHandle hAuth;

	RvChar pstrCallId[64];
	RvInt32 actualSize;

	switch(eState)
	{
	case RVSIP_REG_CLIENT_STATE_FAILED:
		{
			//if (eReason == RVSIP_REG_CLIENT_REASON_TRANSACTION_TIMEOUT)
			{
				SipMessage msg;
				msg.m_sipHeader.statuscode = SIP_BADREQUEST;
				ClientRequest::ClientNotifyResponse(response_timeout, (void*)hRegClient, msg);
			}

			rv = RvSipRegClientTerminate(hRegClient);
		}
		break;
	case RVSIP_REG_CLIENT_STATE_REGISTERING:
		break;
	case RVSIP_REG_CLIENT_STATE_REGISTERED:
		{
			//PLOG("REGISTER", "注册成功");
		}
		break;
	case RVSIP_REG_CLIENT_STATE_UNAUTHENTICATED:
		{
/*
			if (!m_bAuth)
			{
				m_bAuth = true;*/

				rv = RvSipRegClientAuthenticate(hRegClient);
				if(rv != RV_OK)
				{
					//LOG("SIP", "Failed to authenticate the call");
				}
		//	}
		}
		break;
	case RVSIP_REG_CLIENT_STATE_UNDEFINED:
	case RVSIP_REG_CLIENT_STATE_MSG_SEND_FAILURE:
	case RVSIP_REG_CLIENT_STATE_TERMINATED:
		{
			rv = RvSipRegClientTerminate(hRegClient);
			if(rv != RV_OK)
			{
			}
		}
		break;
	default:
		break;
	}

	RV_UNUSED_ARG(hAppRegClient);
	RV_UNUSED_ARG(eReason);
}



RvStatus _stdcall CSipClientRegistar::RegClientMsgReceivedEvHandler(
	RvSipRegClientHandle          hRegClient,
	RvSipAppRegClientHandle       hAppRegClient,
	RvSipMsgHandle                hMsg)
{
	if (CSipMgr::g_LogOn)
		Utility::SipMsgPrint(hMsg);

	RvInt16 code;
	//status code
	code = RvSipMsgGetStatusCode(hMsg);
	if (code != 200)
		return RV_OK;

	return ClientRequest::ClientResponseRecord(hMsg, (void*)hRegClient);
}



RvStatus _stdcall CSipClientRegistar::RegClientMsgToSendEvHandler(
	RvSipRegClientHandle          hRegClient,
	RvSipAppRegClientHandle       hAppRegClient,
	RvSipMsgHandle                hMsg)
{
	if (CSipMgr::g_LogOn)
		Utility::SipMsgPrint(hMsg);

	return ClientRequest::ClientRecord(hMsg, (void*)hRegClient);
}


void CSipInviteCall::SetCallbackFunctions()
{
	RvStatus rv;
	RvSipCallLegEvHandlers appEvHandlers;

	/*Reset the appEvHandlers since not all callbacks are set by this
	application*/
	memset(&appEvHandlers,0,sizeof(RvSipCallLegEvHandlers));

	/*Set application callbacks in the structure*/
	appEvHandlers.pfnStateChangedEvHandler   = CallLegStateChangedEvHandler;
	appEvHandlers.pfnMsgReceivedEvHandler    = CallLegMsgReceivedEvHandler;
	appEvHandlers.pfnTranscCreatedEvHandler  = CallLegTranscCreatedEvHandler;
	appEvHandlers.pfnTranscStateChangedEvHandler  = CallLegTranscStateChangedEvHandler;
	appEvHandlers.pfnMsgToSendEvHandler  = CallLegMsgToSendEvHandler;
	appEvHandlers.pfnByeCreatedEvHandler = CallLegByeCreatedEvHandler;
	appEvHandlers.pfnByeStateChangedEvHandler = CallLegByeStateChangedEvHandler;
	/*Set the structure in the call-leg manager*/
	rv = RvSipCallLegMgrSetEvHandlers(CSipMgr::g_hCallLegMgr,
		&appEvHandlers,
		sizeof(RvSipCallLegEvHandlers));
	if(rv != RV_OK)
	{
		_LOG(LOG_LEVEL_DEBUG, "sip CallLeg Set EventCallbackHandle Failed");
	}
}


void CSipInviteCall::RegisterAppFunc(const char* request, const char* functionCmdType, SipMethod method, void* data)
{
	m_CallLegAppFunStorage.AddAppFun(request, functionCmdType, method, data);
}


void CSipInviteCall::SipServerResponse(SipMessage& msg, int iresult)
{
	//回复sip消息
	RvStatus rv;
	if (strcmp(msg.method(), INVITE) == 0)
	{
		RvSipMsgHandle hMsg;
		RvSipOtherHeaderHandle hHeader;
		RvSipHeaderListElemHandle hListElem;
		RvSipAuthorizationHeaderHandle hAuth;
		RvSipContactHeaderHandle hContact;
		RvSipAddressHandle hAddr;

		RvSipHeaderType HeaderType;
		RvSipHeaderListElemHandle ls;

		rv = RvSipCallLegGetOutboundMsg(msg.m_hCallLeg, &hMsg);

		rv = RvSipOtherHeaderConstructInMsg(hMsg, RV_FALSE, &hHeader);
		rv = RvSipOtherHeaderSetName(hHeader,"Content-type");
		rv = RvSipOtherHeaderSetValue(hHeader, msg.content_type());

		//RvSipAddrUrlSetUser(hAddr, msg.from_user());
		rv = RvSipCallLegGetLocalContactAddress(msg.m_hCallLeg, &hAddr);
		char contiP[24] = {0,};
		char contPort[16] = {0,};
		char contUsr[32] = {0,};
		msg.parseContact(msg.contact(), contUsr, contiP, contPort);
		//RvSipAddrUrlSetUser(hAddr, msg.from_user());
		RvSipAddrUrlSetHost(hAddr, contiP);
		RvSipAddrUrlSetPortNum(hAddr, atoi(contPort));
		/*		//rv = RvSipCallLegGetReceivedMsg(msg.m_hCallLeg, &hMsg);
		//rv = RvSipContactHeaderConstructInMsg(hMsg, RV_FALSE, &hContact);
		oth = RvSipMsgGetHeaderByName(hMsg, "Contact", RVSIP_FIRST_HEADER, &ls);
		hContact = (RvSipContactHeaderHandle)RvSipMsgGetHeaderByType(hMsg, RVSIP_HEADERTYPE_CONTACT, RVSIP_FIRST_HEADER, &ls);
		//rv = RvSipAddrConstructInContactHeader(hContact, RVSIP_ADDRTYPE_URL, &hAddr);
		hAddr = RvSipContactHeaderGetAddrSpec(hContact);
		rv = RvSipAddrUrlSetUser(hAddr, msg.from_user());
		rv = RvSipAddrUrlSetHost(hAddr, msg.from_ip());
		rv = RvSipAddrUrlSetPortNum(hAddr, msg.from_port());*/

		rv = RvSipMsgSetBody(hMsg, msg.sipMessageBody());
		//
		if (iresult == SIP_SUCCESS)
		{
			rv = RvSipCallLegAccept(msg.m_hCallLeg);
			if (rv != RV_OK)
			{
				_LOG(LOG_LEVEL_DEBUG, "SIP INVITE 通信失败");
			}
		}
		else
		{
			rv = RvSipCallLegReject(msg.m_hCallLeg, iresult);
			if (rv != RV_OK)
			{
				_LOG(LOG_LEVEL_DEBUG, "SIP INVITE 通信失败");
			}
		}
	}
	else if (strcmp(msg.method(), INFOR) == 0)
	{
		rv = RvSipCallLegTranscResponse(msg.m_hCallLeg, msg.m_hTransc, iresult);
	}
	else if (strcmp(msg.method(), BYE) == 0)
	{
		rv = RvSipCallLegByeAccept(msg.m_hCallLeg, msg.m_hTransc);
		if (rv != RV_OK)
		{
			_LOG(LOG_LEVEL_DEBUG, "SIP BYE 通信失败");
		}
	}
	
}


int CSipInviteCall::SipClientRequest(SipMessage& msg)
{
	int iresult = 0;
	RvSipCallLegHandle      hCallLeg; /*handle to the call-leg*/
	RvStatus               rv;
	RvSipMsgHandle          hMsg;
	RvInt32                actualSize;
	RvSipOtherHeaderHandle hSubject;
	RvSipBodyHandle         hBody;

	if (strcmp(msg.method(), INVITE) == 0 )
	{
		try
		{
			rv = RvSipCallLegMgrCreateCallLeg(CSipMgr::g_hCallLegMgr,NULL,&hCallLeg);
			if(rv != RV_OK)
				throw SIP_REQUEST_FAILED;

			rv = RvSipCallLegGetOutboundMsg(hCallLeg, &hMsg);
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;
			//body
			if (strlen(msg.sipMessageBody()) != 0)
			{
				rv = RvSipMsgSetBody(hMsg, msg.sipMessageBody());
				if (rv != RV_OK)
					throw SIP_REQUEST_FAILED;
			}
			//content-type
			if (strlen(msg.content_type()) > 0)
				rv = RvSipMsgSetContentTypeHeader(hMsg, msg.content_type());
			//subject
			if (strlen(msg.GetSubject()) > 0)
			{
				RvSipOtherHeaderConstructInMsg(hMsg, RV_TRUE, &hSubject);
				/*Set the other header fields.*/
				RvSipOtherHeaderSetName(hSubject,"Subject");
				RvSipOtherHeaderSetValue(hSubject, msg.GetSubject());
			}
			msg.m_hCallLeg = hCallLeg;


			//tcp
			std::string uri = msg.uri();
			//转换tcp传输
			if (msg.transport == 1)
			{
				//tcp remote address
				uri += ";transport=TCP";

				RvSipAddressHandle hRemoteContact;
				rv = RvSipCallLegGetNewAddressHandle(hCallLeg,RVSIP_ADDRTYPE_URL,&hRemoteContact);
				if(rv != RV_OK)
				{
					_LOG(LOG_LEVEL_DEBUG, "Failed to create new address object for remote contact");
					throw SIP_REQUEST_FAILED;
				}
				rv = RvSipAddrParse(hRemoteContact,const_cast<char*>(uri.c_str()));
				if(rv != RV_OK)
				{
					_LOG(LOG_LEVEL_DEBUG, "Failed to parse remote contact");
					throw SIP_REQUEST_FAILED;
				}
				rv = RvSipCallLegSetRemoteContactAddress(hCallLeg,hRemoteContact);
				if(rv != RV_OK)
				{
					_LOG(LOG_LEVEL_DEBUG, "Failed to set remote contact");
					throw SIP_REQUEST_FAILED;
				}
			}

			rv = RvSipCallLegMake(hCallLeg, msg.from(), msg.to());
			if (rv == RV_OK)
			{
				_LOG(LOG_LEVEL_DEBUG, "发送INVITE成功");
			}
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;
		}
		catch (...)
		{
			return SIP_REQUEST_FAILED;
		}
	}
	else if (strcmp(msg.method(), INFOR) == 0)
	{
		RvSipTranscHandle hTransc = NULL;
		rv = RvSipCallLegTranscCreate(msg.m_hCallLeg,NULL,&hTransc);
		if (rv != RV_OK)
		{
			return rv;
		}
		rv = RvSipTransactionGetOutboundMsg(hTransc, &hMsg);

		rv = RvSipBodyConstructInMsg(hMsg, &hBody);
		rv = RvSipBodySetBodyStr(hBody, msg.sipMessageBody(), msg.m_bodySize);
		//content type
		if (strlen(msg.content_type()) > 0)
		{
			rv = RvSipMsgSetContentTypeHeader(hMsg, msg.content_type());
		}
		rv = RvSipCallLegTranscRequest(msg.m_hCallLeg, INFOR, &hTransc);
		if(rv == RV_OK)
		{
		}

	}
	else if (strcmp(msg.method(), BYE) == 0)
	{
		//INVITE 的BYE消息
		rv = RvSipCallLegDisconnect(msg.m_hCallLeg);
		if (rv == RV_OK)
		{
			iresult = SIP_OK;
		}
		else
		{
			iresult = SIP_REQUEST_FAILED;
		}

	}
	else if (strcmp(msg.method(), ACK) == 0)
	{
		rv = RvSipCallLegGetOutboundAckMsg(msg.m_hCallLeg, &hMsg);
		//rv = RvSipCallLegGetOutboundMsg(msg.m_hCallLeg, &hMsg);
		//setbody
		if (hMsg == NULL)
		{
			return SIP_REQUEST_FAILED;
		}
		rv = RvSipBodyConstructInMsg(hMsg, &hBody);
		if (hBody == NULL)
		{
			return SIP_REQUEST_FAILED;
		}
		rv = RvSipBodySetBodyStr(hBody, msg.sipMessageBody(), strlen(msg.sipMessageBody()));
		rv = RvSipCallLegAck(msg.m_hCallLeg);

		return (int)rv;  //直接返回
	}

	if (hCallLeg != NULL)
	{
		//阻塞否
		ClientRequest::ClientData cl("", (void*)hCallLeg);
		m_CalllegClientRequestBlock.Suspend(cl);

		//continue
		msg = cl.msg;
	}

	return SIP_OK;
}


//callleg
void _stdcall CSipInviteCall::CallLegStateChangedEvHandler(
	RvSipCallLegHandle            hCallLeg,
	RvSipAppCallLegHandle         hAppCallLeg,
	RvSipCallLegState             eState,
	RvSipCallLegStateChangeReason eReason)
{
	RvStatus rv;
	RvSipCallLegDirection eDirection;
	RvSipCallLegGetDirection(hCallLeg,&eDirection);

	switch(eState)
	{
		/*
	case RVSIP_CALL_LEG_TRANSC_STATE_CLIENT_GEN_PROCEEDING:
		{
			break;
		}
		*/
	case RVSIP_CALL_LEG_STATE_INVITING:
		break;
	case RVSIP_CALL_LEG_STATE_CONNECTED:
		if(eDirection == RVSIP_CALL_LEG_DIRECTION_INCOMING)
		{
#if 0		
			SipMessage msg;
			msg.sipMsgCallLegParse(hCallLeg, 0);

			PLOG("-----transAction:", msg.method());

			map<string, handleMethod>::iterator iter;
			iter = g_handleRequestFuncs.find(msg.method());
			if (iter != g_handleRequestFuncs.end())
			{
				g_pool.schedule(boost::bind(CSipMgr::threadProc, msg, iter->second));
			}

			rv = RvSipCallLegDisconnect(hCallLeg);
			if(rv != RV_OK)
			{
				LOG("SIP", "Failed to disconnect the call");
			}
#endif
		}
		break;
	case RVSIP_CALL_LEG_STATE_MSG_SEND_FAILURE:
	case RVSIP_CALL_LEG_STATE_TERMINATED:
		_LOG(LOG_LEVEL_DEBUG, "终止一个call回话, state = %d, %x", eState, hCallLeg);
		RvSipCallLegTerminate(hCallLeg);
		break;
	case RVSIP_CALL_LEG_STATE_OFFERING:
		{
			SipMessage msg;
			msg.sipMsgCallLegParse(hCallLeg, 0);

			if (strcmp(msg.method(), INVITE) != 0)
			{
				break;
			}

			ServerFunctionStorage::Data appfun(msg.method(), msg.m_appCmdType);
			m_CallLegAppFunStorage.GetAppFun(&appfun);
			if (appfun.pFun != NULL)
			{
				CSipMgr::g_threadPool.runInThread(new ServerResponse(msg, appfun.pFun));
			}
	
		}
		break;
	case RVSIP_CALL_LEG_STATE_PROCEEDING_TIMEOUT:
		_LOG(LOG_LEVEL_DEBUG, "处理超时，终止一个call回话, state = %d", eState);
		//RvSipCallLegTerminate(hCallLeg);
		break;
	case RVSIP_CALL_LEG_STATE_ACCEPTED:
		break;
	case RVSIP_CALL_LEG_STATE_REMOTE_ACCEPTED:
		//rv = RvSipCallLegAck(hCallLeg);
		//PLOG("ACK", "应该回应ACK");
		break;
	case RVSIP_CALL_LEG_STATE_DISCONNECTED:
		{
			//if (eReason == RVSIP_CALL_LEG_REASON_LOCAL_TIME_OUT)
			{
				SipMessage msg;
				ClientRequest::ClientNotifyResponse(response_timeout, (void*)hCallLeg, msg);
			}
		}
		break;
	default:
		break;
	}

	RV_UNUSED_ARG(hAppCallLeg);
	RV_UNUSED_ARG(eReason);
}


void _stdcall CSipInviteCall::CallLegByeStateChangedEvHandler(
	RvSipCallLegHandle                hCallLeg,
	RvSipAppCallLegHandle             hAppCallLeg,
	RvSipTranscHandle                 hTransc,
	RvSipAppTranscHandle              hAppTransc,
	RvSipCallLegByeState              eByeState,
	RvSipTransactionStateChangeReason eReason)
{
	switch (eByeState)
	{
	case RVSIP_CALL_LEG_BYE_STATE_REQUEST_RCVD:
		//
		{
			SipMessage msg;
			msg.sipMsgCallLegParse(hCallLeg, hTransc);

			_LOG(LOG_LEVEL_DEBUG, "收到bye消息, callHandle = %x", hCallLeg);

			ServerFunctionStorage::Data appfun(msg.method(), msg.m_appCmdType);
			m_CallLegAppFunStorage.GetAppFun(&appfun);
			if (appfun.pFun != NULL)
			{
				CSipMgr::g_threadPool.runInThread(new ServerResponse(msg, appfun.pFun));

			}

		}
		break;
	case RVSIP_CALL_LEG_BYE_STATE_TERMINATED:
		{
			_LOG(LOG_LEVEL_DEBUG, "终止一个invite回话, %x", hCallLeg);
			RvSipCallLegTerminate(hCallLeg);
		}
		break;
	case RVSIP_CALL_LEG_BYE_STATE_DETACHED:
		{
			ClientRequest::ClientData cl("", (void*)hCallLeg);
			cl.restype = response_normal;
			CSipInviteCall::m_CalllegClientRequestBlock.Resume(cl);
			/*
			list<ClientRequest>::iterator iter;
						for (iter = g_handleResponseFuncs.begin(); iter != g_handleResponseFuncs.end(); iter++)
						{
							if (iter->handle == hCallLeg)//对应的CallID
							{
								iter->bresponse = true;
								g_conditionAll.notify_all();
								break;
							}
						}*/
			
		}
		break;
	default:
		break;
	}

	RV_UNUSED_ARG(hAppCallLeg);
	RV_UNUSED_ARG(eReason);
}

void _stdcall CSipInviteCall::CallLegTranscStateChangedEvHandler(
	RvSipCallLegHandle                hCallLeg,
	RvSipAppCallLegHandle             hAppCallLeg,
	RvSipTranscHandle                 hTransc,
	RvSipAppTranscHandle              hAppTransc,
	RvSipCallLegTranscState           eTranscState,
	RvSipTransactionStateChangeReason eReason)
{
	switch(eTranscState)
	{
	case RVSIP_CALL_LEG_TRANSC_STATE_SERVER_GEN_REQUEST_RCVD:
		{
			//PLOG("CallLegTranscStateChangedEvHandler", "Call-leg %x Received INFO request. responding with 200\n",
			//(int)hCallLeg);
			SipMessage msg;
			msg.sipMsgCallLegParse(hCallLeg, hTransc);
			if (strcmp(msg.method(), INVITE) == 0)
			{
				break;
			}
			
			ServerFunctionStorage::Data appfun(msg.method(), msg.m_appCmdType);
			m_CallLegAppFunStorage.GetAppFun(&appfun);
			if (appfun.pFun != NULL)
			{
				CSipMgr::g_threadPool.runInThread(new ServerResponse(msg, appfun.pFun));

			}
		}
		break;
	case RVSIP_CALL_LEG_TRANSC_STATE_SERVER_GEN_FINAL_RESPONSE_SENT:
		{
			RvUint16 responseCode;
			//RvSipTransactionGetResponseCode(hTransc,&responseCode);
			//PLOG("CallLegTranscStateChangedEvHandler", "Call-leg %x Received %d response to the INFO request\n",
			//	(int)hCallLeg,responseCode);
		}
		break;
	case RVSIP_CALL_LEG_TRANSC_STATE_CLIENT_MSG_SEND_FAILURE:
	case RVSIP_CALL_LEG_TRANSC_STATE_TERMINATED:
		{
			_LOG(LOG_LEVEL_DEBUG, "终止一个 Transc invite回话, eTranstate = %d, callleg = %x", eTranscState, hCallLeg);
			//RvSipCallLegTerminate(hCallLeg);
			RvSipTransactionTerminate(hTransc);
		}
		break;
	default:
		break;
	}
	RV_UNUSED_ARG(hAppCallLeg);
	RV_UNUSED_ARG(hAppTransc);
	RV_UNUSED_ARG(eReason);
}


void _stdcall CSipInviteCall::CallLegTranscCreatedEvHandler(
	RvSipCallLegHandle            hCallLeg,
	RvSipAppCallLegHandle         hAppCallLeg,
	RvSipTranscHandle             hTransc,
	RvSipAppTranscHandle          *hAppTransc,
	RvBool                       *bAppHandleTransc)
{
#if 0
	RvChar method[50];

	RvSipTransactionGetMethodStr(hTransc,50,method);

	/*handle only INFO requests. leave the rest of the requests for the
	stack to handle*/
	if(strcmp(method,"INFO")==0)
	{
		*bAppHandleTransc = RV_TRUE;
	}
	else
	{
		*bAppHandleTransc = RV_FALSE;
	}
#endif

	*bAppHandleTransc = RV_TRUE;

	RV_UNUSED_ARG(hCallLeg);
	RV_UNUSED_ARG(hAppCallLeg);
	RV_UNUSED_ARG(hAppTransc);
}


void _stdcall CSipInviteCall::CallLegByeCreatedEvHandler(
	RvSipCallLegHandle            hCallLeg,
	RvSipAppCallLegHandle         hAppCallLeg,
	RvSipTranscHandle             hTransc,
	RvSipAppTranscHandle          *hAppTransc,
	RvBool                       *bAppHandleTransc)
{
	*hAppTransc = NULL;  /*the application handle is set to NULL*/
	*bAppHandleTransc = RV_TRUE; /*the application wishes to handle the transaction*/
}


RvStatus _stdcall CSipInviteCall::CallLegMsgReceivedEvHandler(
	RvSipCallLegHandle            hCallLeg,
	RvSipAppCallLegHandle         hAppCallLeg,
	RvSipMsgHandle                hMsg)
{
	//log
	if (CSipMgr::g_LogOn)
		Utility::SipMsgPrint(hMsg);

	return ClientRequest::ClientResponseRecord(hMsg, (void*)hCallLeg);
}



RvStatus _stdcall CSipInviteCall::CallLegMsgToSendEvHandler(
	RvSipCallLegHandle            hCallLeg, 
	RvSipAppCallLegHandle         hAppCallLeg,
	RvSipMsgHandle                hMsg)
{
	//log
	if (CSipMgr::g_LogOn)
		Utility::SipMsgPrint(hMsg);

	return ClientRequest::ClientRecord(hMsg, (void*)hCallLeg);
}




void CSipTransaction::SetCallbackFunctions()
{
	RvStatus rv;
	RvSipTransactionEvHandlers     appEvHandlers;
	//Reset the appEvHandlers
	memset(&appEvHandlers,0,sizeof(RvSipTransactionEvHandlers));
	appEvHandlers.pfnEvTransactionCreated = TranscCreatedEvHandler;
	appEvHandlers.pfnEvMsgReceived        = TranscMsgReceivedEvHandler;
	appEvHandlers.pfnEvStateChanged       = TranscStateChangedEvHandler;
	appEvHandlers.pfnEvMsgToSend          = TranscMsgToSendEvHandler;
	appEvHandlers.pfnEvAuthCompleted      = TranscAuthCompletedEv;
	appEvHandlers.pfnEvAuthCredentialsFound = TranscAuthCredentialsFoundEv;

	/*Set the structure in the call-leg manager*/
	rv = RvSipTransactionMgrSetEvHandlers(CSipMgr::g_hTranscMgr,
		NULL,
		&appEvHandlers,
		sizeof(RvSipTransactionEvHandlers));
	if(rv != RV_OK)
	{
		_LOG(LOG_LEVEL_DEBUG, "sip Transaction Set EventCallbackHandle Failed");
	}
}


void CSipTransaction::RegisterAppFunc(const char* request, const char* functionCmdType, SipMethod method, void* data)
{
	m_TransAppFunStorage.AddAppFun(request, functionCmdType, method, data);
}


void CSipTransaction::SipServerResponse(SipMessage& msg, int iresult)
{
	RvStatus rv;
	RvSipMsgHandle hMsg;
	if (strcmp(msg.method(), MESSAGE) == 0)
	{
		rv = RvSipTransactionGetOutboundMsg(msg.m_hTransc, &hMsg);
		rv = RvSipMsgSetBody(hMsg, msg.sipMessageBody());
		if (iresult < 100)
			iresult = SIP_NOTIMPLEMENT;
		rv = RvSipTransactionRespond(msg.m_hTransc,iresult,NULL);
	}
}


int CSipTransaction::SipClientRequest(SipMessage& msg)
{
	if (strcmp(msg.method(), MESSAGE) == 0 ||
		strcmp(msg.method(), NOTIFY) == 0)
	{
		RvSipTranscHandle       hTransc; 
		RvStatus               rv;
		RvSipMsgHandle         hMsg;
		RvInt32                 actualLen;

		RvSipExpiresHeaderHandle hExpires;
		RvSipBodyHandle         hBody;
		RvSipAddressHandle     hAddr;
		RvSipPartyHeaderHandle hPartyHead;
		try
		{
			rv = RvSipTranscMgrCreateTransaction(CSipMgr::g_hTranscMgr,NULL,&hTransc);
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;

			rv = RvSipTransactionGetOutboundMsg(hTransc, &hMsg);
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;

			/*	//Expires
			if (msg.expires() >= 0)
			{
			rv = RvSipExpiresHeaderConstructInMsg(hMsg, RV_TRUE, &hExpires);
			char expires[16];
			sprintf_s(expires, 16, "Expires:%d", msg.expires());
			rv = RvSipExpiresHeaderParse(hExpires, expires);
			if (rv != RV_OK)
			throw SIP_REQUEST_FAILED;
			}*/
			//body
			if (strlen(msg.sipMessageBody()) > 0)
			{
				//RvSipBodySetBodyStr()
				rv = RvSipBodyConstructInMsg(hMsg, &hBody);
				rv = RvSipBodySetBodyStr(hBody, msg.sipMessageBody(), msg.m_bodySize);
				if (rv!= RV_OK)
					throw SIP_REQUEST_FAILED;
			}
			//content type
			if (strlen(msg.sipMessageBody()) > 0 && strlen(msg.content_type()) > 0)
			{
				rv = RvSipMsgSetContentTypeHeader(hMsg, msg.content_type());
			}

			//do method  去掉功能标示部分
			std::string method = msg.method();
			size_t pos = method.find("_");
			if (pos != std::string::npos)
			{
				method.erase(method.begin() + pos, method.end());
				strcpy_s(msg.m_sipHeader.method, sizeof(msg.m_sipHeader.method), method.c_str());
			}
			//send
			msg.m_hTransc = hTransc;

			std::string uri = msg.uri();
			//是否tcp传输
			if (msg.transport == 1)
			{
				//tcp
				uri += ";transport=TCP";
			}

			rv = RvSipTransactionMake(hTransc, msg.from(), msg.to(), (RvChar*)uri.c_str()/*msg.uri()*/, msg.cseq() + 1,msg.method());
			if (rv != RV_OK)
			{
				throw SIP_REQUEST_FAILED;
			}

		}
		catch (...)
		{
			_LOG(LOG_LEVEL_DEBUG, "SIP请求-%s-发送失败", msg.method());
			return SIP_REQUEST_FAILED;
		}

		if (hTransc != NULL)
		{
			//阻塞否
			ClientRequest::ClientData cl("", (void*)hTransc);
			m_TransClientRequestBlock.Suspend(cl);

			//continue
			msg = cl.msg;
		}

	}

	return SIP_OK;
}


//transaction 
void _stdcall CSipTransaction::TranscCreatedEvHandler(
	RvSipTranscHandle            hTransc,
	void                         *context,
	RvSipTranscOwnerHandle       *phAppTransc,
	RvBool                      *b_handleTransc)
{
	*phAppTransc = NULL;  /*the application handle is set to NULL*/
	*b_handleTransc = RV_TRUE; /*the application wishes to handle the transaction*/
	RV_UNUSED_ARG(context);

}


RvStatus _stdcall CSipTransaction::TranscMsgReceivedEvHandler(
	RvSipTranscHandle            hTransc,
	RvSipTranscOwnerHandle       hAppTransc,
	RvSipMsgHandle               hMsg)
{
	//log
	if (CSipMgr::g_LogOn)
		Utility::SipMsgPrint(hMsg);

	RvSipAddressHandle addr;
	RvSipTransport trans;
	addr = RvSipMsgGetRequestUri(hMsg);
	trans = RvSipAddrUrlGetTransport(addr);
	if (RVSIP_TRANSPORT_TCP == trans)
	{
		_LOG(LOG_LEVEL_DEBUG, "New Connection TCP Accepted");
	}


	return ClientRequest::ClientResponseRecord(hMsg, (void*)hTransc);
}



RvStatus _stdcall CSipTransaction::TranscMsgToSendEvHandler(
	RvSipTranscHandle            hTransc,
	RvSipTranscOwnerHandle       hAppTransc,
	RvSipMsgHandle               hMsg)
{
	//log
	if (CSipMgr::g_LogOn)
		Utility::SipMsgPrint(hMsg);

	ClientRequest::ClientRecord(hMsg, (void*)hTransc);

	return RV_OK;
}



void _stdcall CSipTransaction::TranscStateChangedEvHandler(
	RvSipTranscHandle                 hTransc,
	RvSipTranscOwnerHandle            hAppTransc,
	RvSipTransactionState             eState,
	RvSipTransactionStateChangeReason eReason)
{
	RvStatus             rv;
	RvSipMsgHandle       hMsg;
	RvSipMethodType MethodType;

	switch(eState)
	{
	case RVSIP_TRANSC_STATE_SERVER_GEN_REQUEST_RCVD:
		{
			SipMessage msg;
			msg.sipMsgTransaParse(hTransc);

			_LOG(LOG_LEVEL_DEBUG, "收到sip方法：%s", msg.method());

			ServerFunctionStorage::Data appfun(msg.method(), msg.m_appCmdType);
			m_TransAppFunStorage.GetAppFun(&appfun);
			if (appfun.pFun != NULL)
			{
				CSipMgr::g_threadPool.runInThread(new ServerResponse(msg, appfun.pFun));
			}
			else  //default response
			{
				rv = RvSipTransactionRespond(hTransc, SIP_NOTIMPLEMENT, NULL);
			}

		}
		break;
	case RVSIP_TRANSC_STATE_SERVER_GEN_FINAL_RESPONSE_SENT:  //server
	case RVSIP_TRANSC_STATE_CLIENT_GEN_FINAL_RESPONSE_RCVD:  //client
	case RVSIP_TRANSC_STATE_CLIENT_MSG_SEND_FAILURE:         //client
	case RVSIP_TRANSC_STATE_TERMINATED:                      //terminate
		{
			//超时
			//if (eReason == RVSIP_TRANSC_REASON_TIME_OUT)
			{
				SipMessage msg;
				msg.m_sipHeader.statuscode = SIP_BADREQUEST;
				ClientRequest::ClientNotifyResponse(response_timeout, (void*)hTransc, msg);

			}
			RvSipTransactionTerminate(hTransc);
		}
		break;
	default:
		break;
	}

	RV_UNUSED_ARG(hAppTransc);
	RV_UNUSED_ARG(eReason);
}



void _stdcall CSipTransaction::TranscAuthCompletedEv(
	RvSipTranscHandle        hTransc,
	RvSipTranscOwnerHandle   hAppTransc,
	RvBool                   bAuthSucceed)
{
	RvStatus rv;

	if(bAuthSucceed == RV_TRUE)
	{
		//PLOG("SIP", "\nAuthentication completed successfully (transaction %x)\n\n",(int)hTransc);
		int result; 
		SipMessage msg;

		RvStatus rv; 
		RvUint actualLen;
		RvUint length;
		RvSipPartyHeaderHandle PartyHead;
		RvSipAddressHandle AddrHead;
		RvSipExpiresHeaderHandle ExpiresHandle;

		//From
		rv = RvSipTransactionGetFromHeader(hTransc, &PartyHead);
		AddrHead = RvSipPartyHeaderGetAddrSpec(PartyHead);
		length = RvSipAddrGetStringLength(AddrHead, RVSIP_ADDRESS_HOST);
		//获取from的user
		rv = RvSipAddrUrlGetUser(AddrHead, msg.m_sipHeader.from_user, sizeof(msg.m_sipHeader.from_user), &actualLen);
		char filedFrom[64] = {0};
		rv = RvSipAddrUrlGetHost(AddrHead, filedFrom, sizeof(filedFrom), &length);
		if (CheckIpPortAddress(filedFrom))
		{
			strcpy(msg.m_sipHeader.from_ip, filedFrom);
			msg.m_sipHeader.from_port = RvSipAddrUrlGetPortNum(AddrHead);
		}
		else
		{
			//domain
			std::string FromIp;
			CSipMgr::g_HostMomainResolve.GetHostFromDomain(filedFrom, msg.m_sipHeader.from_user, FromIp, &msg.m_sipHeader.from_port);
			strcpy(msg.m_sipHeader.from_ip, FromIp.c_str());
		}

		//To
		rv = RvSipTransactionGetToHeader(hTransc, &PartyHead);
		AddrHead = RvSipPartyHeaderGetAddrSpec(PartyHead);
		length = RvSipAddrGetStringLength(AddrHead, RVSIP_ADDRESS_HOST);
		//获取from的user
		rv = RvSipAddrUrlGetUser(AddrHead, msg.m_sipHeader.to_user, sizeof(msg.m_sipHeader.to_user), &actualLen);

		char filedTo[64] = {0};
		rv = RvSipAddrUrlGetHost(AddrHead, filedTo, sizeof(filedTo), &length);
		if (CheckIpPortAddress(filedTo))
		{
			strcpy(msg.m_sipHeader.from_ip, filedTo);
			msg.m_sipHeader.from_port = RvSipAddrUrlGetPortNum(AddrHead);
		}
		else
		{
			//domain
			std::string FromIp;
			CSipMgr::g_HostMomainResolve.GetHostFromDomain(filedTo, msg.m_sipHeader.to_user, FromIp, &msg.m_sipHeader.from_port);
			strcpy(msg.m_sipHeader.from_ip, FromIp.c_str());
		}

		std::list<RegTransExpires>::iterator it;
		for (it = g_RegExpiresList.begin(); it != g_RegExpiresList.end(); it++)
		{
			if (it->handle == hTransc)
			{
				msg.setExpires(it->expires);
				break;
			}
		}

		RvSipMsgHandle hMsg;
		rv = RvSipTransactionGetOutboundMsg(hTransc, &hMsg);
		/*
		RvSipHeaderListElemHandle listHead;
		ExpiresHandle =	(RvSipExpiresHeaderHandle)RvSipMsgGetHeaderByType(hMsg, RVSIP_HEADERTYPE_EXPIRES, RVSIP_FIRST_HEADER, &listHead);
		if (ExpiresHandle != NULL)
		{
		int detailSecond;
		RvSipExpiresHeaderGetDeltaSeconds(ExpiresHandle, (RvUint32*)&detailSecond);
		msg.setExpires(detailSecond);
		}*/


		ServerFunctionStorage::Data appfun(REGISTER, "AuthSuccess");
		CSipTransaction::m_TransAppFunStorage.GetAppFun(&appfun);
		if (appfun.pFun != NULL)
		{
			appfun.pFun(msg, result, NULL);

			//date header
			RvSipOtherHeaderHandle dateHeader;
			RvSipHeaderListElemHandle listElem;
			rv = RvSipOtherHeaderConstructInMsg(hMsg, RV_FALSE, &dateHeader);
			RvUint actLen = 0;
			rv = RvSipOtherHeaderSetName(dateHeader, "Date");
			rv = RvSipOtherHeaderSetValue(dateHeader, msg.m_sipHeader.datecheck);
		}
		else  //default response
		{
			rv = RvSipTransactionRespond(hTransc, SIP_NOTIMPLEMENT, NULL);
		}

		rv = RvSipTransactionRespond(hTransc, SIP_SUCCESS, NULL);
		if(rv != RV_OK)
		{
			_LOG(LOG_LEVEL_DEBUG, "RvSipTransactionRespond fail(transaction %x)\n",(int)hTransc);
		}
	}
	else
	{
		//LOG("SIP", "\nAuthentication completed with failure!!! (transaction %x)\n\n",(int)hTransc);
		RvChar* sdomain;
		if (strlen(CSipMgr::g_Athorization.sdomain) == 0)
			sdomain = NULL;  //标示忽略
		else
			sdomain = CSipMgr::g_Athorization.sdomain;
		rv = RvSipTransactionRespondUnauthenticatedDigest(
			hTransc, SIP_NOTAUTHENTICATION, NULL, CSipMgr::g_Athorization.realm,
			sdomain, CSipMgr::g_Athorization.nonce, CSipMgr::g_Athorization.opaque, RV_TRUE,
			RVSIP_AUTH_ALGORITHM_MD5, NULL,
			RVSIP_AUTH_QOP_AUTH_ONLY, NULL);
		if(rv != RV_OK)
		{
			//LOG("SIP", "RvSipTransactionRespondUnauthenticatedDigest fail(transaction %x)\n",(int)hTransc);
		}
	}
	RV_UNUSED_ARG(hAppTransc);
}



void _stdcall CSipTransaction::TranscAuthCredentialsFoundEv(
	RvSipTranscHandle               hTransc,
	RvSipTranscOwnerHandle          hAppTransc,
	RvSipAuthorizationHeaderHandle  hAuthorization,
	RvBool                         bCredentialsSupported)
{
	RvStatus rv;
	RvChar strName[64], strRealm[REALM_LEN], strNonce[NONCE_LEN], strPW[32];
	RvUint32 actualLen1 = 0, actualLen2 = 0, actualLen3 = 0;
	RvBool toSkip = RV_FALSE;

	memset(strName, 0, sizeof strName);
	memset(strRealm, 0, sizeof strRealm);
	memset(strNonce, 0, sizeof strNonce);
	memset(strPW, 0, sizeof strPW);

	//g_AuthCounter += 1;
	/*
	PLOG("SIP", "\nAuthentication credentials num %d found(transaction %x)\n",
	g_AuthCounter, (int)hTransc);*/


	if(bCredentialsSupported == RV_TRUE)
	{
		rv = RvSipAuthorizationHeaderGetCredentialIdentifier(hAuthorization,
			strRealm, REALM_LEN,
			strName, 64,
			strNonce, NONCE_LEN,
			(RvUint*)&actualLen1,
			(RvUint*)&actualLen2,
			(RvUint*)&actualLen3);

		if(rv != RV_OK)
		{
			//LOG("SIP", "Couldn't get credentical Identifiers from authorization header \n");
		}

		//鉴权的上层处理
		int result; 
		SipMessage msg;

		RvStatus rv; 
		RvUint actualLen;
		RvUint length;
		RvSipPartyHeaderHandle PartyHead;
		RvSipAddressHandle AddrHead;

		//From
		rv = RvSipTransactionGetFromHeader(hTransc, &PartyHead);
		AddrHead = RvSipPartyHeaderGetAddrSpec(PartyHead);
		length = RvSipAddrGetStringLength(AddrHead, RVSIP_ADDRESS_HOST);
		//获取from的user
		rv = RvSipAddrUrlGetUser(AddrHead, msg.m_sipHeader.from_user, sizeof(msg.m_sipHeader.from_user), &actualLen);
		char filedFrom[64] = {0};
		rv = RvSipAddrUrlGetHost(AddrHead, filedFrom, sizeof(filedFrom), &length);
		//判断是否包含域名
		if (CheckIpPortAddress(filedFrom))
		{
			strcpy(msg.m_sipHeader.from_ip, filedFrom);
			msg.m_sipHeader.from_port = RvSipAddrUrlGetPortNum(AddrHead);
		}
		else
		{
			//domain
			std::string FromIp;
			CSipMgr::g_HostMomainResolve.GetHostFromDomain(filedFrom, msg.m_sipHeader.from_user, FromIp, &msg.m_sipHeader.from_port);
			strcpy(msg.m_sipHeader.from_ip, FromIp.c_str());
		}

		//To
		rv = RvSipTransactionGetToHeader(hTransc, &PartyHead);
		AddrHead = RvSipPartyHeaderGetAddrSpec(PartyHead);
		length = RvSipAddrGetStringLength(AddrHead, RVSIP_ADDRESS_HOST);
		//获取from的user
		rv = RvSipAddrUrlGetUser(AddrHead, msg.m_sipHeader.to_user, sizeof(msg.m_sipHeader.to_user), &actualLen);

		char filedTo[64] = {0};
		rv = RvSipAddrUrlGetHost(AddrHead, filedTo, sizeof(filedTo), &length);
		if (CheckIpPortAddress(filedTo))
		{
			strcpy(msg.m_sipHeader.from_ip, filedTo);
			msg.m_sipHeader.from_port = RvSipAddrUrlGetPortNum(AddrHead);
		}
		else
		{
			//domain
			std::string FromIp;
			CSipMgr::g_HostMomainResolve.GetHostFromDomain(filedTo, msg.m_sipHeader.to_user, FromIp, &msg.m_sipHeader.from_port);
			strcpy(msg.m_sipHeader.from_ip, FromIp.c_str());
		}

		msg.setAuth_realm(strRealm);
		msg.setAuth_usr(strName);

		ServerFunctionStorage::Data appfun(REGISTER, "");
		CSipTransaction::m_TransAppFunStorage.GetAppFun(&appfun);
		if (appfun.pFun != NULL)
		{
			appfun.pFun(msg, result, NULL);
			if (result != SIP_SUCCESS)
				rv = RvSipTransactionRespond(hTransc,result,NULL);

		}
		else  //default response
		{
			rv = RvSipTransactionRespond(hTransc, SIP_NOTIMPLEMENT, NULL);
		}

#if 0
		if(strcmp(strRealm, REALM)!=0)
		{
			LOG("SIP", "unknown realm %s. continue with loop \n", strRealm);
			toSkip = RV_TRUE;
		}

		if(CheckUserInDB(strName, strPW) == RV_OK)
		{
			LOG("SIP", "username %s was found. using it's pw \n", strName);
			toSkip = RV_FALSE;
		}
		else
		{
			LOG("SIP", "unknown username %s. continue with loop \n", strName);
			toSkip = RV_TRUE;
		}
#endif

		if(toSkip == RV_FALSE)
		{
			rv = RvSipTransactionAuthProceed(hTransc,
				RVSIP_TRANSC_AUTH_ACTION_USE_PASSWORD,
				hAuthorization,
				msg.auth_password());
		}
		else
		{
			rv = RvSipTransactionAuthProceed(hTransc,
				RVSIP_TRANSC_AUTH_ACTION_SKIP,
				NULL,
				NULL);
		}

		while(rv != RV_OK)
		{
			rv = RvSipTransactionAuthProceed(hTransc,
				RVSIP_TRANSC_AUTH_ACTION_SKIP,
				NULL,
				NULL);
		}

	}
	else
	{
		_LOG(LOG_LEVEL_DEBUG, "Algorithm is not supported \n");
		rv = RvSipTransactionAuthProceed(hTransc,
			RVSIP_TRANSC_AUTH_ACTION_SKIP,
			NULL,
			NULL);
	}
	RV_UNUSED_ARG(hAppTransc);
}


void CSipAuthCall::SetCallbackFunctions()
{
	RvStatus rv;
	RvSipAuthenticatorEvHandlers authEvHandlers;

	/* Reset the authEvHandlers since not all callbacks
	are set by this application */
	memset(&authEvHandlers,0,sizeof(RvSipAuthenticatorEvHandlers));

	/*Set application callbacks in the structure*/
	authEvHandlers.pfnMD5AuthenticationHandler = serverAuthenticationMD5Ev;
	authEvHandlers.pfnMD5AuthenticationExHandler           = AuthenticationMD5Ev;
	authEvHandlers.pfnGetSharedSecretAuthenticationHandler = AuthenticationGetSharedSecretEv;

	/*Set the structure in the authenticator */
	rv = RvSipAuthenticatorSetEvHandlers(CSipMgr::g_hAuthenticatorMgr,
		&authEvHandlers,
		sizeof(RvSipAuthenticatorEvHandlers));
	if(rv != RV_OK)
	{
		_LOG(LOG_LEVEL_DEBUG, "Failed to set application callbacks for authentication");
	}
}


void CSipAuthCall::RegisterAppFunc(const char* request, const char* functionCmdType, SipMethod method, void* data)
{
	m_AuthAppFunStorage.AddAppFun(request, functionCmdType, method, data);
}



void _stdcall CSipAuthCall::serverAuthenticationMD5Ev(RPOOL_Ptr *pRpoolMD5Input,
																						 RvUint32 length,
																						 RPOOL_Ptr *pRpoolMD5Output)
{
	RvChar strDigest[1024];
	RvChar strResponse[33];
	RvUint8 digest[20];

	/* The string for the md5 is on a page. first we copy it to
	a consecutive buffer.*/
	RPOOL_CopyToExternal(pRpoolMD5Input->hPool,
		pRpoolMD5Input->hPage,
		pRpoolMD5Input->offset,
		(void*)strDigest,
		length);

	/* implementation of the MD5 algorithm - we give the string to the MD5*/

	MDString((char*)strDigest, strResponse);

	/*after we have a result we must copy it back to the page*/
	RPOOL_AppendFromExternalToPage(pRpoolMD5Output->hPool,
		pRpoolMD5Output->hPage,
		(void*)strResponse,
		strlen(strResponse) + 1,
		&(pRpoolMD5Output->offset));

}


void _stdcall CSipAuthCall::AuthenticationMD5Ev(RvSipAuthenticatorHandle hAuthenticator,
																			 RvSipAppAuthenticatorHandle    hAppAuthenticator,
																			 RPOOL_Ptr                     *pRpoolMD5Input,
																			 RvUint32                     length,
																			 RPOOL_Ptr                     *pRpoolMD5Output)
{
	RvChar strDigest[1024];
	RvChar strResponse[33];
	RvUint8 digest[20];
	MD5_CTX mdc;

	/* The string for the md5 is on a page. first we copy it to
	a consecutive buffer.*/
	RPOOL_CopyToExternal(pRpoolMD5Input->hPool,
		pRpoolMD5Input->hPage,
		pRpoolMD5Input->offset,
		(void*)strDigest,
		length);

	/* implementation of the MD5 algorithm - we give the string to the MD5*/
	memset(strResponse, 0, sizeof(strResponse));

	MDString((char*)strDigest, strResponse);

	/*after we have a result we must copy it back to the page*/
	RPOOL_AppendFromExternalToPage(pRpoolMD5Output->hPool,
		pRpoolMD5Output->hPage,
		(void*)strResponse,
		strlen(strResponse) + 1,
		&(pRpoolMD5Output->offset));
	RV_UNUSED_ARG(hAuthenticator);
	RV_UNUSED_ARG(hAppAuthenticator);

}


void _stdcall CSipAuthCall::AuthenticationGetSharedSecretEv(
	RvSipAuthenticatorHandle       hAuthenticator,
	RvSipAppAuthenticatorHandle    hAppAuthenticator,
	void*                          hObject,
	void*                          peObjectType,
	RPOOL_Ptr                     *pRpoolRealm,
	RPOOL_Ptr                     *pRpoolUserName,
	RPOOL_Ptr                     *pRpoolPassword)
{

	/*copy the username + '\0' to the given page*/
	RPOOL_AppendFromExternalToPage(pRpoolUserName->hPool,
		pRpoolUserName->hPage,
		(void*)CSipMgr::g_Athorization.agent_user,
		strlen(CSipMgr::g_Athorization.agent_user) + 1,
		&(pRpoolUserName->offset));

	/*copy the password + '\0' to the given page*/
	RPOOL_AppendFromExternalToPage(pRpoolPassword->hPool,
		pRpoolPassword->hPage,
		(void*)CSipMgr::g_Athorization.agent_password,
		strlen(CSipMgr::g_Athorization.agent_password) + 1,
		&(pRpoolPassword->offset));
	RV_UNUSED_ARG(hAppAuthenticator);
	RV_UNUSED_ARG(hAuthenticator);
	RV_UNUSED_ARG(hObject);
	RV_UNUSED_ARG(peObjectType);
	RV_UNUSED_ARG(pRpoolRealm);
}



void CSipSubscribe::SetCallbackFunctions()
{
	RvStatus rv;
	RvSipSubsEvHandlers appEvHandlers;

	/*Reset the appEvHandlers since not all callbacks are set by this sample*/
	memset(&appEvHandlers,0,sizeof(RvSipSubsEvHandlers));

	/*Set application callbacks in the structure*/
	appEvHandlers.pfnStateChangedEvHandler = SubsStateChangedEvHandler;
	appEvHandlers.pfnMsgReceivedEvHandler  = SubsMsgReceivedEvHandler;
	appEvHandlers.pfnSubsExpiredEvHandler  = SubsSubscriptionExpiredEvHandler;
	appEvHandlers.pfnNotifyEvHandler       = SubsNotifyEvHandler;
	appEvHandlers.pfnExpirationAlertEvHandler = SubsExpirationAlertEvHandler;
	appEvHandlers.pfnMsgToSendEvHandler    = SubsMsgToSendEvHandler;
	appEvHandlers.pfnReferNotifyReadyEvHandler = AppSubsReferNotifyReadyEv;

	/*Set the structure in the subscription manager*/
	rv = RvSipSubsMgrSetEvHandlers(CSipMgr::g_hSubsMgr, &appEvHandlers, sizeof(RvSipSubsEvHandlers));
	if(rv != RV_OK)
	{
		_LOG(LOG_LEVEL_DEBUG, "sip Subscribe Set EventCallbackHandle Failed");
	}
}


void CSipSubscribe::RegisterAppFunc(const char* request, const char* functionCmdType, SipMethod method, void* data)
{
	m_SubscribeAppFunStorage.AddAppFun(request, functionCmdType, method, data);
}


int CSipSubscribe::sendSubscribeNotify(RvSipSubsHandle hSubs, RvSipSubscriptionSubstate eSubstate, int expires, SipMessage& msg)
{

	RvSipNotifyHandle hNotify;
	RvSipMsgHandle    hMsg;
	RvSipBodyHandle         hBody;
	RvSipSubscriptionSubstate hSubState;
	RvSipSubscriptionStateHeaderHandle hSubsStateHeader;
	RvStatus         rv;

	RvSipSubscriptionType type;
	RvSipSubsGetSubsType(hSubs, &type);

	rv = RvSipSubsCreateNotify(hSubs, NULL, &hNotify);
	if(rv != RV_OK)
	{
		_LOG(LOG_LEVEL_DEBUG, "###RvSipSubsCreateNotify failed,hSubs=0x%x", hSubs);
		return -1;
	}
	rv = RvSipNotifyGetOutboundMsg(hNotify, &hMsg);
	if(rv != RV_OK)
	{
		return -1;
	}

	if (strlen(msg.sipMessageBody()) > 0)
	{
		rv = RvSipBodyConstructInMsg(hMsg, &hBody);
		rv = RvSipBodySetBodyStr(hBody, msg.sipMessageBody(), msg.m_bodySize);
		//content type
		if (strlen(msg.content_type()) > 0)
		{
			rv = RvSipMsgSetContentTypeHeader(hMsg, msg.content_type());
		}
	}

	//NOTIFY,event package and id
	if (strlen(msg.getEventPackage()) > 0 || strlen(msg.getEventId()) > 0)
	{
		RvSipEventHeaderHandle eventHeader;
		RvSipEventHeaderConstructInMsg(hMsg, RV_FALSE, &eventHeader);

		RvSipEventHeaderSetEventPackage(eventHeader, (RvChar*)msg.getEventPackage());
		RvSipEventHeaderSetEventId(eventHeader, (RvChar*)msg.getEventId());
	}

	if (strlen(msg.subscription_state()) > 0)
	{
		//TODO
		RvSipSubscriptionStateHeaderHandle substateHandle;
		rv = RvSipSubscriptionStateHeaderConstructInMsg(hMsg, RV_FALSE, &substateHandle);

		rv = RvSipSubscriptionStateHeaderSetSubstate(substateHandle, eSubstate, NULL);  //(RvChar*)(msg.subscription_state())
	}

#if 0
	//RvSipNotifySetSubscriptionStateParams(hNotify, )
	rv = RvSipSubscriptionStateHeaderSetSubstate(hSubsStateHeader, eSubstate, NULL);
	rv = RvSipSubscriptionStateHeaderSetExpiresParam(hSubsStateHeader, expires);
	rv = RvSipSubscriptionStateHeaderSetRetryAfter(hSubsStateHeader, RETRY_AFTER);
#endif

	rv = RvSipNotifySend(hNotify);
	if(rv != RV_OK)
	{
		return rv;
	}

	hMsg = NULL;

	return SIP_OK;
}


void CSipSubscribe::SipServerResponse(SipMessage& msg, int iresult)
{
	//回复sip消息
	RvStatus rv;
	if (strcmp(msg.method(), SUBSCRIBE) == 0)
	{
		RvSipMsgHandle hMsg;
		RvSipOtherHeaderHandle hHeader;
		RvSipHeaderListElemHandle hListElem;
		RvSipAuthorizationHeaderHandle hAuth;
		RvSipContactHeaderHandle hContact;
		RvSipAddressHandle hAddr;

		RvSipHeaderType HeaderType;
		RvSipHeaderListElemHandle ls;

		rv = RvSipSubsGetOutboundMsg(msg.m_hSubs, &hMsg);
		rv = RvSipMsgSetBody(hMsg, msg.sipMessageBody());
		//
		if (iresult == SIP_SUCCESS)
		{
			rv = RvSipSubsRespondAccept(msg.m_hSubs, 5/*UNDEFINED*/);
			//send notify       //    RVSIP_SUBSCRIPTION_SUBSTATE_PENDING / RVSIP_SUBSCRIPTION_SUBSTATE_TERMINATED,
			//sendSubscribeNotify(msg.m_hSubs, RVSIP_SUBSCRIPTION_SUBSTATE_ACTIVE, msg.expires());
		}
		else
		{
			RvSipSubsRespondReject(msg.m_hSubs, iresult, NULL);
		}
	}


}


int CSipSubscribe::SipClientRequest(SipMessage& msg)
{
	if (strcmp(msg.method(), SUBSCRIBE) == 0)
	{
		RvStatus rv;
		RvSipMsgHandle hMsg;
		RvSipSubsHandle         hSubs;
		RvUint                actualLen;

		//creating a new subscription
		try
		{
			rv = RvSipSubsMgrCreateSubscription(CSipMgr::g_hSubsMgr, NULL, NULL, &hSubs);
			if(rv != RV_OK)
				throw SIP_REQUEST_FAILED;
			/*------------------------------------------------------------
			Call the init function with the To and From addresses, event
			and expires values, in order to init and send the subscription.
			-------------------------------------------------------------*/
			//去掉From: 和 To: 头
			std::string strFrom = msg.from();
			std::string strTo = msg.to();

			size_t pos = strFrom.find(":");
			if (pos != std::string::npos)
			{
				strFrom.erase(0, pos + 1);
				strcpy_s(msg.from(), sizeof(msg.fromHeader), strFrom.c_str());
			}

			pos = strTo.find(":");
			if (pos != std::string::npos)
			{
				strTo.erase(0, pos + 1);
				strcpy_s(msg.to(), sizeof(msg.toHeader), strTo.c_str());
			}

			if (strlen(msg.getEventPackage()) > 0 && strlen(msg.getEventId()) > 0)
			{
				char event[64] = {0};
				sprintf(event, "%s;id=%s", msg.getEventPackage(), msg.getEventId());
				rv = RvSipSubsInitStr(hSubs, msg.from(), msg.to(), msg.expires(), event);
				if(rv != RV_OK)
					throw SIP_REQUEST_FAILED;
			}

			rv = RvSipSubsGetOutboundMsg(hSubs, &hMsg);
			if (rv != RV_OK)
				throw SIP_REQUEST_FAILED;

			//body
			if (strlen(msg.sipMessageBody()) != 0)
			{
				rv = RvSipMsgSetBody(hMsg, msg.sipMessageBody());
				if (rv != RV_OK)
					throw SIP_REQUEST_FAILED;
			}

			//Expires
			if (msg.expires() > 0)
			{
				RvSipSubsSetExpiresVal(hSubs, msg.expires());
			}

			msg.m_hSubs = hSubs;

			rv = RvSipSubsSubscribe(hSubs);
			if(rv != RV_OK)
				throw SIP_REQUEST_FAILED;
		}
		catch (...)
		{
			return SIP_REQUEST_FAILED;
		}

		if (hSubs != NULL)
		{
			//阻塞否
			ClientRequest::ClientData cl("", (void*)hSubs);
			m_SubClientRequestBlock.Suspend(cl);

			//continue
			msg = cl.msg;
		}

	}	

	return SIP_OK;
}


//subscrib
void _stdcall CSipSubscribe::SubsStateChangedEvHandler(
	RvSipSubsHandle            hSubs,
	RvSipAppSubsHandle         hAppSubs,
	RvSipSubsState             eState,
	RvSipSubsStateChangeReason eReason)
{
	RvStatus             rv;
	RvSipMsgHandle       hMsg;


	RvSipSubscriptionType type;
	RvSipSubsGetSubsType(hSubs, &type);
	_LOG(LOG_LEVEL_DEBUG, "###subs=0x%x, type=%d", hSubs, type);


	switch(eState)
	{
		/*-------------------------------------------------------------------
		Accept incoming subscription and send a notify (active) immediately
		-------------------------------------------------------------------*/
	case RVSIP_SUBS_STATE_SUBS_RCVD:
		{
			SipMessage msg;
			msg.sipMsgSubsParse(hSubs, NULL);

			//for NOTIFY,如果不是notifier,则此subscribe不能调用notify
			RvSipSubscriptionType type;
			RvSipSubsGetSubsType(hSubs, &type);
			if (type == RVSIP_SUBS_TYPE_NOTIFIER)
			{
				ServerFunctionStorage::Data appfun(msg.method(), msg.m_appCmdType);
				m_SubscribeAppFunStorage.GetAppFun(&appfun);
				if (appfun.pFun != NULL)
				{
					CSipMgr::g_threadPool.runInThread(new ServerResponse(msg, appfun.pFun));
				}
			}

			rv = RvSipSubsRespondAccept(hSubs, UNDEFINED);
			if(rv != RV_OK)
			{
				assert(0);
				break;
			}

			msg.setSubscState("active");
			sendSubscribeNotify(hSubs, RVSIP_SUBSCRIPTION_SUBSTATE_ACTIVE, msg.expires(), msg);

			//RvSipSubsAutoRefresh(hSubs, RV_TRUE);
			//RvSipSubsSetNoNotifyTimer(hSubs, 600000);
		}
		break;

	case RVSIP_SUBS_STATE_REFRESH_RCVD:
		{
			/*-------------------------------------------------------------------
			Accept refresh and send a notify (active) immediately
			-------------------------------------------------------------------*/
			rv = RvSipSubsRespondAccept(hSubs, UNDEFINED);
			if(rv != RV_OK)
			{
			}

			SipMessage msg;
			msg.sipMsgSubsParse(hSubs, NULL);
			msg.setSubscState("active");
			sendSubscribeNotify(hSubs, RVSIP_SUBSCRIPTION_SUBSTATE_ACTIVE, msg.expires(), msg);
		}
		break;

	case RVSIP_SUBS_STATE_REFRESHING:
	case RVSIP_SUBS_STATE_ACTIVE:
		/*-------------------------------------------------------------------
		set bSendUnsubscribe to true, so next request will be an unsubscribe.
		-------------------------------------------------------------------*/
		//bSendUnsubscribe = RV_TRUE;
		break;

	case RVSIP_SUBS_STATE_UNSUBSCRIBE_RCVD:
		{
			/*-------------------------------------------------------------------
			Accept unsubscribe and send a notify (terminated) immediately
			-------------------------------------------------------------------*/
			rv = RvSipSubsRespondAccept(hSubs, UNDEFINED);
			if(rv != RV_OK)
			{
			}
			SipMessage msg;
			msg.setSubscState("terminated");
			sendSubscribeNotify(hSubs, RVSIP_SUBSCRIPTION_SUBSTATE_TERMINATED, 0, msg);
		}
		break;
	case RVSIP_SUBS_STATE_MSG_SEND_FAILURE:
	case RVSIP_SUBS_STATE_TERMINATED:
		RvSipSubsTerminate(hSubs);
		break;
	default:
		break;
	}
	RV_UNUSED_ARG(hAppSubs);
	RV_UNUSED_ARG(eReason);
}


void _stdcall CSipSubscribe::SubsNotifyEvHandler( RvSipSubsHandle    hSubs,
																			 RvSipAppSubsHandle hAppSubs,
																			 RvSipNotifyHandle  hNotification,
																			 RvSipAppNotifyHandle  hAppNotification,
																			 RvSipSubsNotifyStatus eNotifyStatus,
																			 RvSipSubsNotifyReason eNotifyReason,
																			 RvSipMsgHandle     hNotifyMsg)
{
	RvStatus rv;
	int iresult = 0;

	switch (eNotifyStatus)
	{
	case RVSIP_SUBS_NOTIFY_STATUS_REQUEST_RCVD:
		{
			SipMessage msg;
			msg.sipMsgNotifyParse(hNotifyMsg, hSubs, hNotification);

			ServerFunctionStorage::Data appfun(msg.method(), msg.m_appCmdType);
			m_SubscribeAppFunStorage.GetAppFun(&appfun);
			if (appfun.pFun != NULL)
			{
				CSipMgr::g_threadPool.runInThread(new ServerResponse(msg, appfun.pFun));
			}

			rv = RvSipNotifyAccept(hNotification);
			//if(rv != RV_OK)
		}
		break;
	case RVSIP_SUBS_NOTIFY_STATUS_2XX_RCVD:
		break;
	case RVSIP_SUBS_NOTIFY_STATUS_REJECT_RCVD:
	case RVSIP_SUBS_NOTIFY_STATUS_REDIRECTED:
	case RVSIP_SUBS_NOTIFY_STATUS_UNAUTHENTICATED:
		break;
	case RVSIP_SUBS_NOTIFY_STATUS_TERMINATED:
		RvSipSubsTerminate(hSubs);
		break;
	default:
		break;
	}
	RV_UNUSED_ARG(hSubs);
	RV_UNUSED_ARG(hAppSubs);
	RV_UNUSED_ARG(hAppNotification);
	RV_UNUSED_ARG(eNotifyReason);
	RV_UNUSED_ARG(hNotifyMsg);
}

RvStatus _stdcall CSipSubscribe::SubsMsgReceivedEvHandler(
	RvSipSubsHandle      hSubs,
	RvSipAppSubsHandle   hAppSubs,
	RvSipNotifyHandle    hNotify,
	RvSipAppNotifyHandle hAppNotify,
	RvSipMsgHandle       hMsg)
{
	//log
	if (CSipMgr::g_LogOn)
		Utility::SipMsgPrint(hMsg);

	return ClientRequest::ClientResponseRecord(hMsg, (void*)hSubs);
}


void _stdcall CSipSubscribe::SubsSubscriptionExpiredEvHandler(
	RvSipSubsHandle            hSubs,
	RvSipAppSubsHandle         hAppSubs)
{

}

void _stdcall CSipSubscribe::SubsExpirationAlertEvHandler(
	RvSipSubsHandle            hSubs,
	RvSipAppSubsHandle         hAppSubs)
{

}

RvStatus _stdcall CSipSubscribe::SubsMsgToSendEvHandler(
	RvSipSubsHandle      hSubs,
	RvSipAppSubsHandle   hAppSubs,
	RvSipNotifyHandle    hNotify,
	RvSipAppNotifyHandle hAppNotify,
	RvSipMsgHandle       hMsg)
{
	//log
	if (CSipMgr::g_LogOn)
		Utility::SipMsgPrint(hMsg);

	return ClientRequest::ClientRecord(hMsg, (void*)hSubs);
}


/***************************************************************************
 * RvSipSubsReferNotifyReadyEv
 * ------------------------------------------------------------------------
 * General: Indicates that a refer notifier subscription is ready to
 *          send a notify request.
 *          This callback is called after accepting a REFER request, and for
 *          every incoming provisional or final response for the related
 *          object establishment attempt.
 *          When RvSipSubsReferNotifyReadyEv() is called, application should
 *          create and send a new notify request, with status of the establish
 *          attempt of the refer related object.
 *          The response code parameter indicates the response code that should
 *          be set in the body of the NOTIFY message.
 *          The function also provides the incoming response message of the
 *          establishment attempt. (note that the message not always exists.
 *          in case of timeout termination, for example, this parameter will
 *          be NULL).
 * Return Value: (-)
 * ------------------------------------------------------------------------
 * Arguments:
 * Input:   hSubs         - The sip stack subscription handle
 *          hAppSubs      - The application handle for this subscription.
 *          eReason       - The reason for a NOTIFY request to be sent
 *          responseCode  - The response code that should be set in the
 *                          NOTIFY message body.
 *          hResponseMsg  - The message that was received on the refer related
 *                          object (provisional or final response).
 ***************************************************************************/
void _stdcall CSipSubscribe::AppSubsReferNotifyReadyEv(
                           RvSipSubsHandle                  hSubs,
                           RvSipAppSubsHandle               hAppSubs,
                           RvSipSubsReferNotifyReadyReason  eReason,
                           RvInt16                         responseCode,
                           RvSipMsgHandle                   hResponseMsg)
{
    RvInt16  notifyResponseCode; /* the response code that will be set in
                                     the outgoing NOTIFY request body */
    /* Subscription-State header parameters */
    RvSipSubscriptionSubstate   eSubsState = RVSIP_SUBSCRIPTION_SUBSTATE_TERMINATED;
    RvSipSubscriptionReason     eNotifyReason = RVSIP_SUBSCRIPTION_REASON_UNDEFINED;
    RvInt32                    expires = UNDEFINED;

    /* if the reason is final response, or termination, notify request should
    be sent with header " Subscription-State:terminated;reason=noresource".
    if the reason is provisional response or initial notify, notify request should
    be sent with header " Subscription-State:active;expires=xxx". */
    switch (eReason)
    {
    case RVSIP_SUBS_REFER_NOTIFY_READY_REASON_1XX_RESPONSE_MSG_RCVD:
    case RVSIP_SUBS_REFER_NOTIFY_READY_REASON_INITIAL_NOTIFY:
        eSubsState = RVSIP_SUBSCRIPTION_SUBSTATE_ACTIVE;
        notifyResponseCode = responseCode;
        expires = 50;
        break;
    case RVSIP_SUBS_REFER_NOTIFY_READY_REASON_FINAL_RESPONSE_MSG_RCVD:
        notifyResponseCode = responseCode;
        eNotifyReason = RVSIP_SUBSCRIPTION_REASON_NORESOURCE;
        break;
    case RVSIP_SUBS_REFER_NOTIFY_READY_REASON_TIMEOUT:
    case RVSIP_SUBS_REFER_NOTIFY_READY_REASON_ERROR_TERMINATION:
        notifyResponseCode = 503;
        eNotifyReason = RVSIP_SUBSCRIPTION_REASON_NORESOURCE;
        break;
    case RVSIP_SUBS_REFER_NOTIFY_READY_REASON_UNDEFINED:
    default:
        return;
    }

    AppSubsSendReferNotify(hSubs, notifyResponseCode, eSubsState,
                           eNotifyReason, expires);

    RV_UNUSED_ARG(hAppSubs);
    RV_UNUSED_ARG(hResponseMsg);

}


/***************************************************************************
 * AppSubsSendReferNotify
 * ------------------------------------------------------------------------
 * General: Send a NOTIFY request on a refer subscription.
 *          1. create a notification object.
 *          2. set the notify parameters.
 *          3. set the refer notify body.
 *          4. send the NOTIFY request.
 ***************************************************************************/
void CSipSubscribe::AppSubsSendReferNotify(RvSipSubsHandle            hSubs,
                                  RvInt16                   statusCode,
                                  RvSipSubscriptionSubstate  eSubsState,
                                  RvSipSubscriptionReason    eReason,
                                  RvInt32                   expiresParamVal)
{
    RvStatus   rv          = RV_OK;
    RvSipNotifyHandle hNotify;

    rv = RvSipSubsCreateNotify(hSubs, NULL, &hNotify);
    if (RV_OK != rv)
    {
        _LOG(LOG_LEVEL_DEBUG, "RvSipSubsCreateNotify failed!");
    }
    rv = RvSipNotifySetSubscriptionStateParams(hNotify,eSubsState, eReason, expiresParamVal);
    if (RV_OK != rv)
    {
        _LOG(LOG_LEVEL_DEBUG, "RvSipNotifySetSubscriptionStateParams failed");
    }
    rv = RvSipNotifySetReferNotifyBody(hNotify, statusCode);
    if (RV_OK != rv)
    {
        _LOG(LOG_LEVEL_DEBUG, "RvSipNotifySetReferNotifyBody failed");
    }

    rv = RvSipNotifySend(hNotify);
    if (RV_OK != rv)
    {
        _LOG(LOG_LEVEL_DEBUG, "RvSipNotifySend failed");
    }

}
