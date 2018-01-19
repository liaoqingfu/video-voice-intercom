#pragma once

/*
  Ä£¿é£º
	1 Registar
	2 Invite
	3 MessageÀ©Õ¹Ä£¿é
	4 BYE
*/
#include "SipMessage.h"
#include "SipDef.h"
#include <vector>

#include "BlockPattern.h"
#include "ThreadPool.h"


//global define
typedef void (*SipMethod)(SipMessage& sipMsg, int& iresult, void* appData);


enum responseType
{
	response_null = 0,
	response_normal,
	response_timeout
};


struct ServerFunctionStorage
{
	struct Data
	{
		char SipName[16];
		char FuncCmdType[64];
		SipMethod pFun;
		void* context;

		Data(const char* sipcmd, const char* funcmd)
		{
			memset(SipName, 0, sizeof(SipName));
			strcpy(SipName, sipcmd);
			memset(FuncCmdType, 0, sizeof(FuncCmdType));
			strcpy(FuncCmdType, funcmd);

			pFun = NULL;
			context = NULL;
		}

		Data(const char* sipcmd, const char* funcmd, SipMethod method, void* context)
		{
			memset(SipName, 0, sizeof(SipName));
			strcpy(SipName, sipcmd);
			memset(FuncCmdType, 0, sizeof(FuncCmdType));
			strcpy(FuncCmdType, funcmd);

			pFun = method;
			context = context;
		}

		const Data& operator=(const Data& data)
		{
			strcpy(SipName, data.SipName);
			strcpy(FuncCmdType, data.FuncCmdType);
			pFun = data.pFun;
			context = data.context;
		}
	};

	std::list<Data> m_AppFunList;

	void AddAppFun(const char* sipcmd, const char* funcmd, SipMethod method, void* context)
	{
		Data AppData(sipcmd, funcmd, method, context);
		m_AppFunList.push_back(AppData);
	}

	void GetAppFun(Data* AppFun)
	{
		std::list<Data>::iterator it;
		for (it = m_AppFunList.begin(); it != m_AppFunList.end(); it++)
		{
			if (strcmp((*it).SipName, AppFun->SipName) == 0 && strcmp(it->FuncCmdType, AppFun->FuncCmdType) == 0)
			{
				AppFun->context = it->context;
				AppFun->pFun = it->pFun;

				break;
			}
		}
	}

	~ServerFunctionStorage()
	{
		m_AppFunList.clear();
	}


};




namespace ClientRequest
{
	struct ClientData
	{
		responseType restype;
		SipMessage msg;
		char callid[64];
		void* siphandle;
		bool bwait;

		ClientData(const char* calid, void* handle)
		{
			restype = response_null;
			msg.zeroSet();
			siphandle = handle;
			strcpy(callid, calid);
			bwait = true;
		}


		ClientData()
		{
			restype = response_null;
			msg.zeroSet();
			memset(callid, 0, sizeof(callid));
			siphandle = NULL;
			bwait = true;
		}

		const ClientData& operator=(const ClientData& cl)
		{
			restype = cl.restype;
			msg = cl.msg;
			strcpy(callid, cl.callid);
			siphandle = cl.siphandle;
			bwait = cl.bwait;
			return *this;
		}

		bool operator==(const ClientData& cl)
		{
			if (strcmp(callid, cl.callid) == 0 || siphandle == cl.siphandle)
			{
				return true;
			}
			
			return false;
		}
	};

	RvStatus ClientRecord(RvSipMsgHandle hMsg, void* handle);
	RvStatus ClientResponseRecord(RvSipMsgHandle hMsg, void* handle);
	void ClientNotifyResponse(responseType type, void* handle, SipMessage& msg);

}

struct RegTransExpires
{
	void* handle;
	int expires;
};

class ServerResponse : public base::Runable
{
public:
	ServerResponse(SipMessage msg, SipMethod pf)
		:_msg(msg), _pFun(pf)
	{

	}
	virtual void run()
	{
		ServerThreadProc(_msg, _pFun);
	}

	void MakeServerResponse(SipMessage& msg, int iresult);
	void ServerThreadProc(SipMessage& message, SipMethod method);

private:
	SipMessage _msg;
	SipMethod _pFun;
};


namespace Utility
{
	void SipMsgPrint(RvSipMsgHandle hMsg);

}




class CSipBasicModule
{
public:
	CSipBasicModule(void);
	~CSipBasicModule(void);

public:
	static void SetCallbackFunctions() {}

	static void RegisterAppFunc(const char* request, const char* functionCmdType, SipMethod method, void* data){}

public:

};


class CSipClientRegistar : CSipBasicModule
{
public:
	CSipClientRegistar(void);
	~CSipClientRegistar(void);

public:
	static void SetCallbackFunctions();

	//static void RegisterAppFunc(const char* request, const char* functionCmdType, SipMethod method, void* data);

	static void SipServerResponse(SipMessage& msg, int iresult);

	static int SipClientRequest(SipMessage& msg);

	//storage app func
	static ServerFunctionStorage m_RegAppFunStorage;
	static CBlockPattern<ClientRequest::ClientData> m_RegClientRequestBlock;

	//register
	static void _stdcall RegClientStateChangedEvHandler(
		RvSipRegClientHandle            hRegClient,
		RvSipAppRegClientHandle         hAppRegClient,
		RvSipRegClientState             eState,
		RvSipRegClientStateChangeReason eReason);

	static RvStatus _stdcall RegClientMsgReceivedEvHandler(
		RvSipRegClientHandle          hRegClient,
		RvSipAppRegClientHandle       hAppRegClient,
		RvSipMsgHandle                hMsg);

	static RvStatus _stdcall RegClientMsgToSendEvHandler(
		RvSipRegClientHandle          hRegClient,
		RvSipAppRegClientHandle       hAppRegClient,
		RvSipMsgHandle                hMsg);
};



class CSipInviteCall : CSipBasicModule
{
public:
	CSipInviteCall(void);
	~CSipInviteCall(void);

public:
	static void SetCallbackFunctions();

	static void RegisterAppFunc(const char* request, const char* functionCmdType, SipMethod method, void* data);
	static void SipServerResponse(SipMessage& msg, int iresult);

	static int SipClientRequest(SipMessage& msg);
	//storage app func
	static ServerFunctionStorage m_CallLegAppFunStorage;

	//client
	static CBlockPattern<ClientRequest::ClientData> m_CalllegClientRequestBlock;

	//callleg
	static void _stdcall CallLegStateChangedEvHandler(
		RvSipCallLegHandle            hCallLeg,
		RvSipAppCallLegHandle         hAppCallLeg,
		RvSipCallLegState             eState,
		RvSipCallLegStateChangeReason eReason);
	static RvStatus _stdcall CallLegMsgReceivedEvHandler(
		RvSipCallLegHandle            hCallLeg,
		RvSipAppCallLegHandle         hAppCallLeg,
		RvSipMsgHandle                hMsg);
	static RvStatus _stdcall CallLegMsgToSendEvHandler(
		RvSipCallLegHandle            hCallLeg, 
		RvSipAppCallLegHandle         hAppCallLeg,
		RvSipMsgHandle                hMsg);
	static void _stdcall CallLegByeStateChangedEvHandler(
		RvSipCallLegHandle                hCallLeg,
		RvSipAppCallLegHandle             hAppCallLeg,
		RvSipTranscHandle                 hTransc,
		RvSipAppTranscHandle              hAppTransc,
		RvSipCallLegByeState              eByeState,
		RvSipTransactionStateChangeReason eReason);
	static void _stdcall CallLegByeCreatedEvHandler(
		RvSipCallLegHandle            hCallLeg,
		RvSipAppCallLegHandle         hAppCallLeg,
		RvSipTranscHandle             hTransc,
		RvSipAppTranscHandle          *hAppTransc,
		RvBool                       *bAppHandleTransc);
	static void _stdcall CallLegTranscStateChangedEvHandler(
		RvSipCallLegHandle                hCallLeg,
		RvSipAppCallLegHandle             hAppCallLeg,
		RvSipTranscHandle                 hTransc,
		RvSipAppTranscHandle              hAppTransc,
		RvSipCallLegTranscState           eTranscState,
		RvSipTransactionStateChangeReason eReason);
	static void _stdcall CallLegTranscCreatedEvHandler(
		RvSipCallLegHandle            hCallLeg,
		RvSipAppCallLegHandle         hAppCallLeg,
		RvSipTranscHandle             hTransc,
		RvSipAppTranscHandle          *hAppTransc,
		RvBool                       *bAppHandleTransc);
};



class CSipTransaction : CSipBasicModule
{
public:
	CSipTransaction(void);
	~CSipTransaction(void);

public:
	static void SetCallbackFunctions();

	static void RegisterAppFunc(const char* request, const char* functionCmdType, SipMethod method, void* data);

	static void SipServerResponse(SipMessage& msg, int iresult);

	static int SipClientRequest(SipMessage& msg);

	//storage app func
	static ServerFunctionStorage m_TransAppFunStorage;
	static CBlockPattern<ClientRequest::ClientData> m_TransClientRequestBlock;

	static std::list<RegTransExpires > g_RegExpiresList;

	//transaction
	static void _stdcall TranscCreatedEvHandler(
		RvSipTranscHandle            hTransc,
		void                         *context,
		RvSipTranscOwnerHandle       *phAppTransc,
		RvBool                      *b_handleTransc);
	static RvStatus _stdcall TranscMsgReceivedEvHandler(
		RvSipTranscHandle            hTransc,
		RvSipTranscOwnerHandle       hAppTransc,
		RvSipMsgHandle               hMsg);
	static RvStatus _stdcall TranscMsgToSendEvHandler(
		RvSipTranscHandle            hTransc,
		RvSipTranscOwnerHandle       hAppTransc,
		RvSipMsgHandle               hMsg);
	static void _stdcall TranscStateChangedEvHandler(
		RvSipTranscHandle                 hTransc,
		RvSipTranscOwnerHandle            hAppTransc,
		RvSipTransactionState             eState,
		RvSipTransactionStateChangeReason eReason);

	static void _stdcall TranscAuthCompletedEv(
		RvSipTranscHandle        hTransc,
		RvSipTranscOwnerHandle   hAppTransc,
		RvBool                   bAuthSucceed);

	static void _stdcall TranscAuthCredentialsFoundEv(
		RvSipTranscHandle               hTransc,
		RvSipTranscOwnerHandle          hAppTransc,
		RvSipAuthorizationHeaderHandle  hAuthorization,
		RvBool                         bCredentialsSupported);

};


class CSipSubscribe : CSipBasicModule
{
public:
	CSipSubscribe(void);
	~CSipSubscribe(void);

public:
	static void SetCallbackFunctions();

	static void RegisterAppFunc(const char* request, const char* functionCmdType, SipMethod method, void* data);

	static int sendSubscribeNotify(RvSipSubsHandle hSubs, RvSipSubscriptionSubstate eSubstate, int expires, SipMessage& msg);
	static void SipServerResponse(SipMessage& msg, int iresult);

	static int SipClientRequest(SipMessage& msg);

	//storage app func
	static ServerFunctionStorage m_SubscribeAppFunStorage;
	static CBlockPattern<ClientRequest::ClientData> m_SubClientRequestBlock;
	//
	static void _stdcall SubsStateChangedEvHandler(
		RvSipSubsHandle            hSubs,
		RvSipAppSubsHandle         hAppSubs,
		RvSipSubsState             eState,
		RvSipSubsStateChangeReason eReason);

	static void _stdcall SubsNotifyEvHandler( RvSipSubsHandle    hSubs,
		RvSipAppSubsHandle hAppSubs,
		RvSipNotifyHandle  hNotification,
		RvSipAppNotifyHandle  hAppNotification,
		RvSipSubsNotifyStatus eNotifyStatus,
		RvSipSubsNotifyReason eNotifyReason,
		RvSipMsgHandle     hNotifyMsg);

	static RvStatus _stdcall SubsMsgReceivedEvHandler(
		RvSipSubsHandle      hSubs,
		RvSipAppSubsHandle   hAppSubs,
		RvSipNotifyHandle    hNotify,
		RvSipAppNotifyHandle hAppNotify,
		RvSipMsgHandle       hMsg);

	static void _stdcall SubsSubscriptionExpiredEvHandler(
		RvSipSubsHandle            hSubs,
		RvSipAppSubsHandle         hAppSubs);

	static void _stdcall SubsExpirationAlertEvHandler(
		RvSipSubsHandle            hSubs,
		RvSipAppSubsHandle         hAppSubs);

	static RvStatus _stdcall SubsMsgToSendEvHandler(
		RvSipSubsHandle      hSubs,
		RvSipAppSubsHandle   hAppSubs,
		RvSipNotifyHandle    hNotify,
		RvSipAppNotifyHandle hAppNotify,
		RvSipMsgHandle       hMsg);


	static void _stdcall AppSubsReferNotifyReadyEv(
		RvSipSubsHandle                  hSubs,
		RvSipAppSubsHandle               hAppSubs,
		RvSipSubsReferNotifyReadyReason  eReason,
		RvInt16                         responseCode,
		RvSipMsgHandle                   hResponseMsg);
	static void AppSubsSendReferNotify(RvSipSubsHandle hSubs,
		RvInt16                   statusCode,
		RvSipSubscriptionSubstate  eSubsState,
		RvSipSubscriptionReason    eReason,
		RvInt32                   expiresParamVal);

};



class CSipAuthCall : CSipBasicModule
{
public:
	CSipAuthCall(void);
	~CSipAuthCall(void);

public:
	static void SetCallbackFunctions();

	static void RegisterAppFunc(const char* request, const char* functionCmdType, SipMethod method, void* data);

	static int SipClientRequest(SipMessage& msg){}

	//storage app func
	static ServerFunctionStorage m_AuthAppFunStorage;
	static CBlockPattern<ClientRequest::ClientData> m_AuthClientRequestBlock;

	//auth
	static void _stdcall serverAuthenticationMD5Ev(RPOOL_Ptr *pRpoolMD5Input,
		RvUint32 length,
		RPOOL_Ptr *pRpoolMD5Output);
	
	static void _stdcall AuthenticationMD5Ev(RvSipAuthenticatorHandle hAuthenticator,
		RvSipAppAuthenticatorHandle    hAppAuthenticator,
		RPOOL_Ptr                     *pRpoolMD5Input,
		RvUint32                     length,
		RPOOL_Ptr                     *pRpoolMD5Output);

	static void _stdcall AuthenticationGetSharedSecretEv(
		RvSipAuthenticatorHandle       hAuthenticator,
		RvSipAppAuthenticatorHandle    hAppAuthenticator,
		void*                          hObject,
		void*                          peObjectType,
		RPOOL_Ptr                     *pRpoolRealm,
		RPOOL_Ptr                     *pRpoolUserName,
		RPOOL_Ptr                     *pRpoolPassword);
};


