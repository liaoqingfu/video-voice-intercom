#include "StdAfx.h"
#include <process.h>
#include "GlobalCtrl.h"

#include "Utility/RpcCmd.h"
#include "SipMgr.h"
#include "config/ProxyConfig.h"

#include "AgentServer/BcAdaptor.h"


GlobalCtrl* GlobalCtrl::ms_pInstace = NULL;
GlobalCtrl::Guard GlobalCtrl::Garbo;
bool GlobalCtrl::gSipInit = false;

class GlobalCtrl;

//------------------------------------------
void InitSipDomain()
{
	if (GLOBJ(gConfig) != NULL && GLOBJ(gSipServer) != NULL)
	{
		std::list<AbsDomain>::iterator it;
		for (it = GLOBJ(gConfig)->m_SipDomainList.begin(); it != GLOBJ(gConfig)->m_SipDomainList.end(); it++)
		{
			GLOBJ(gSipServer)->RegisterHostDomain(it->uriHost, it->user, it->uriPort, it->domainName);
		}
	}
}



GlobalCtrl::~GlobalCtrl(void)
{
	delete gConfig;
	gConfig = NULL;

	delete gRpcExcutor;
	gRpcExcutor = NULL;

	delete gSipServer;
	gSipServer = NULL;

	gAdaptor->deinit();
	delete gAdaptor;
	gAdaptor = NULL;

	gThreadPool->stop();
	delete gThreadPool;
	gThreadPool = NULL;
}


GlobalCtrl* GlobalCtrl::instance()
{
	if (ms_pInstace == NULL)
	{
		ms_pInstace = new GlobalCtrl();
	}

	return ms_pInstace;
}


int GlobalCtrl::init()
{
	int ret = 0;

	do 
	{
		//config
		gConfig = new ProxyConfig();
		gConfig->InitCfg();

		//threadpool
		gThreadPool = new base::ThreadPool();
		gThreadPool->start(4);

		//connect to bcenter 
		gRpcExcutor	= new RpcCmd();
		gRpcExcutor->initRpcClient(gConfig->getServerIp(), gConfig->getServerPort());

		//adaptor init
		gAdaptor = new BcAdaptor();
		char url[32] = {0,};
		sprintf(url, "%s://%s:%d@%d", "BC2X",gConfig->getServerIp(), gConfig->getServerPort(),
			3720);
		gAdaptor->init(url, gConfig->getLoginName(), gConfig->getLoginPassword());


		//sipServer
		gSipServer = new CSipMgr();
		if (gConfig->IsReSendDir())
		{
			gSipServer->SetLogOn(true);
		}
		else
		{
			gSipServer->SetLogOn(false);
		}

		unsigned int threadId = 0;
		_beginthreadex(NULL, 0, GlobalCtrl::sipRunProc, this, 0, &threadId);

		while(!GlobalCtrl::gSipInit)
		{
			Sleep(50);
		}

	} while (0);
	
	return ret;

}

unsigned int __stdcall GlobalCtrl::sipRunProc(void* context)
{
	GlobalCtrl* pctrl = (GlobalCtrl*)context;
	if (pctrl == NULL)
	{
		return -1;
	}

	int ret = 0;
	ret = pctrl->gSipServer->initSipStack(pctrl->gConfig->getSiplocalPort());
	if (ret == SIP_INIT_ERROR)
	{
		return -2;
	}

	pctrl->gSipServer->setAuthentication(pctrl->gConfig->getSip_authUser(), pctrl->gConfig->getSip_authPassword(), 
		pctrl->gConfig->getSip_auth_realm(),	pctrl->gConfig->getSip_authnonce(), "",
		pctrl->gConfig->getSip_authopaque(), "", pctrl->gConfig->getSip_authsdomain());

	//sip domain init
	InitSipDomain();
	GlobalCtrl::gSipInit = true;

	_LOG(LOG_LEVEL_DEBUG, "sipÆô¶¯Õý³£");
	pctrl->gSipServer->startupSipServer();

	return 0;
}

