#include "SipMgr.h"

#include "SipModule.h"


//static member initialize
RvSipStackHandle      CSipMgr::g_hStackMgr = NULL;
RvSipTranscMgrHandle CSipMgr::g_hTranscMgr = NULL;
RV_LOG_Handle         CSipMgr::g_hLog = NULL;
HRPOOL                CSipMgr::g_appPool = NULL;
RvSipCallLegMgrHandle CSipMgr::g_hCallLegMgr = NULL;
RvSipSubsMgrHandle CSipMgr::g_hSubsMgr = NULL;
RvSipRegClientMgrHandle CSipMgr::g_hRegClientMgr = NULL;
RvSipAuthenticatorHandle CSipMgr::g_hAuthenticatorMgr;
RvInt32           CSipMgr::g_AuthCounter = 0;
int CSipMgr::g_serverPort = 5060;

base::ThreadPool CSipMgr::g_threadPool;
HostDomain CSipMgr::g_HostMomainResolve;

Authentication CSipMgr::g_Athorization;
bool CSipMgr::g_LogOn = true;


/////
#define MAX_THREAD 4

const int gpoolPageSize = 512;
const int gpoolPageCount = 128;


CSipMgr::CSipMgr()
{
	memset(&g_Athorization, 0, sizeof(Authentication));
}

CSipMgr::~CSipMgr(void)
{
	//RvSipStackDestruct(g_hStackMgr);
}

int CSipMgr::setAuthentication(char* user, char* psw, char* realm, char* nonce, char* qop, 
													 char* opaque, char* algorithm, char* sdomain)
{
	if (user != NULL)
		strcpy_s(g_Athorization.agent_user, sizeof(g_Athorization.agent_user), user);
	if (psw != NULL)
		strcpy_s(g_Athorization.agent_password, sizeof(g_Athorization.agent_password), psw);
	if (realm != NULL)
		strcpy_s(g_Athorization.realm, sizeof(g_Athorization.realm), realm);
	if (nonce != NULL)
		strcpy_s(g_Athorization.nonce, sizeof(g_Athorization.nonce), nonce);
	if (qop != NULL)
		strcpy_s(g_Athorization.qop, sizeof(g_Athorization.qop), qop);
	if (opaque != NULL)
		strcpy_s(g_Athorization.opaque, sizeof(g_Athorization.opaque), opaque);
	if (algorithm != NULL)
		strcpy_s(g_Athorization.algorithm, sizeof(g_Athorization.algorithm), algorithm);
	if (sdomain != NULL)
		strcpy_s(g_Athorization.sdomain, sizeof(g_Athorization.sdomain), sdomain);

	return 0;
}


int CSipMgr::initSipStack(int serverPort)
{
	g_serverPort = serverPort;

	if (!sipStackInitialize())
		return SIP_INIT_ERROR;

	//设置sip消息回调
	CSipClientRegistar::SetCallbackFunctions();
	CSipSubscribe::SetCallbackFunctions();
	CSipTransaction::SetCallbackFunctions();
	CSipInviteCall::SetCallbackFunctions();
	CSipAuthCall::SetCallbackFunctions();

	//g_bInitStack = true;

	//threadpool initialize
	g_threadPool.start(MAX_THREAD);

	return SIP_OK;
}


//sip stack initialize
bool CSipMgr::sipStackInitialize()
{
	bool bresult = false;
	RvStatus rv;
	RvSipStackCfg stackCfg;

	do 
	{
		//Initialize the configuration structure with default values
		RvSipStackInitCfg(sizeof(stackCfg),&stackCfg);

		stackCfg.maxCallLegs = MAX_SIP_HANDLE_NUM * 2;
		stackCfg.manualAckOn2xx = RV_TRUE;
		stackCfg.maxTransactions = MAX_SIP_CONNECT_NUM;
		stackCfg.maxRegClients = MAX_SIP_HANDLE_NUM;
		stackCfg.maxSubscriptions = MAX_SIP_HANDLE_NUM;
		stackCfg.maxTransmitters = MAX_SIP_HANDLE_NUM;
		stackCfg.subsAutoRefresh = RV_FALSE;
		stackCfg.tcpEnabled = RV_TRUE;
		stackCfg.maxConnections = MAX_SIP_CONNECT_NUM;
		stackCfg.sendReceiveBufferSize = SIP_SENDRECEIVE_SIZE;

		stackCfg.enableServerAuth = RV_TRUE;

		stackCfg.localUdpPort = g_serverPort;
		stackCfg.localTcpPort = g_serverPort;

		stackCfg.enableInviteProceedingTimeoutState = RV_TRUE;

		stackCfg.manualSessionTimer = RV_TRUE;
		stackCfg.generalRequestTimeoutTimer = SIP_TIMEOUT;
		stackCfg.sessionExpires = SIP_TIMEOUT;

		stackCfg.pfnPrintLogEntryEvHandler = CSipMgr::print2screen;


		rv = RvSipStackConstruct(sizeof(stackCfg),&stackCfg,&CSipMgr::g_hStackMgr);
		if (rv != RV_OK)
		{
			RvSipStackDestruct(CSipMgr::g_hStackMgr);
			_LOG(LOG_LEVEL_DEBUG, "initialize SipStack failed, error code = %d", rv);
			break;
		}
		//得到TransactionMgrHandle
		rv = RvSipStackGetTransactionMgrHandle(CSipMgr::g_hStackMgr,&CSipMgr::g_hTranscMgr);
		if (rv != RV_OK)
			break;
		//得到CallLegMgrhandle
		rv = RvSipStackGetCallLegMgrHandle(CSipMgr::g_hStackMgr,&CSipMgr::g_hCallLegMgr);
		if (rv != RV_OK)
			break;
		//得到SubsMgrHandle
		rv = RvSipStackGetSubsMgrHandle(CSipMgr::g_hStackMgr, &CSipMgr::g_hSubsMgr);
		if (rv != RV_OK)
			break;

		rv = RvSipStackGetRegClientMgrHandle(CSipMgr::g_hStackMgr, &CSipMgr::g_hRegClientMgr);
		if (rv != RV_OK)
			break;
		//鉴权
		rv = RvSipStackGetAuthenticatorHandle(g_hStackMgr, &g_hAuthenticatorMgr);
		if (rv != RV_OK)
			break;

		rv = RvSipStackGetLogHandle(CSipMgr::g_hStackMgr,&CSipMgr::g_hLog);
		if (rv != RV_OK)
			break;
		//Construct a pool of memory for the application
		CSipMgr::g_appPool = RPOOL_Construct(gpoolPageSize,gpoolPageCount,g_hLog,RV_FALSE,"ApplicationPool");

		bresult = true;

	} while (0);

	return bresult;

}


int CSipMgr::startupSipServer()
{
	//do process loop
	RvSipStackProcessEvents();

	return SIP_OK;
}


void _stdcall CSipMgr::print2screen(void* context,
																RvSipLogFilters filter,
																const RvChar* formattedText)
{
	static RvInt lineNum = 0;

	/* Write the message to the screen*/
	//OSPrintf("line %d:",++lineNum);
	//OSPrintf("%s\n", formattedText);
}


int CSipMgr::Register(const char* request, const char* functionCmdType, SipMethod method, void* data)
{
	if (strcmp(request, INVITE) == 0 ||
		strcmp(request, BYE) == 0)
	{
		CSipInviteCall::RegisterAppFunc(request, functionCmdType, method, data);
	}
	else if (strcmp(request, MESSAGE) == 0)
	{
		CSipTransaction::RegisterAppFunc(request, functionCmdType, method, data);
	}
	else if (strcmp(request, REGISTER) == 0)
	{
		CSipTransaction::RegisterAppFunc(request, functionCmdType, method, data);
	}
	else if (strcmp(request, SUBSCRIBE) == 0)
	{
		CSipSubscribe::RegisterAppFunc(request, functionCmdType, method, data);
	}

	return 0;
}


int CSipMgr::doSipRequest(const char* request, SipMessage& msg)
{
	int ret = -1;
	strcpy(msg.method(), request);
	if (strcmp(request, INVITE) == 0 ||
		strcmp(request, ACK) == 0 ||
		strcmp(request, BYE) == 0 ||
		strcmp(request, INFOR) == 0)
	{
		ret = CSipInviteCall::SipClientRequest(msg);
	}
	else if (strcmp(request, MESSAGE) == 0)
	{
		ret = CSipTransaction::SipClientRequest(msg);
	}
	else if (strcmp(request, REGISTER) == 0)
	{
		ret = CSipClientRegistar::SipClientRequest(msg);
	}
	else if (strcmp(request, SUBSCRIBE) == 0)
	{
		ret = CSipSubscribe::SipClientRequest(msg);
	}
	else if (strcmp(request, NOTIFY) == 0)
	{
		ret = CSipSubscribe::sendSubscribeNotify(msg.m_hSubs, RVSIP_SUBSCRIPTION_SUBSTATE_ACTIVE, msg.expires(), msg);
	}
	

	return ret;
}



void CSipMgr::RegisterHostDomain(char* host, char* user, int port, char* domain)
{
	g_HostMomainResolve.AppendOneUriDomain(domain, user, host, port);
}