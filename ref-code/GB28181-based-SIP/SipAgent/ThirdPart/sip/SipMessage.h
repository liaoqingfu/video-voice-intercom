#ifndef _SIPMESSAGE_H
#define _SIPMESSAGE_H

#include <stdio.h>
#include <stdlib.h>

#include "SipError.h"
#include "SipDef.h"
#include "deelx.h"


//============include RVSIP header=============
#include "RV_SIP_DEF.h"
#include <stdarg.h>
#include "RvSipStackTypes.h"
#include "RvSipStack.h"

#include "RvSipTransactionTypes.h"
#include "RvSipTransaction.h"

#include "RvSipAddress.h"
#include "RvSipMid.h"

#include "RvSipOtherHeader.h"

#include "RvSipCallLegTypes.h"
#include "RvSipCallLeg.h"

#include "RvSipSubscriptionTypes.h"
#include "RvSipSubscription.h"
#include "RvSipSubscriptionStateHeader.h"

#include "RvSipRegClientTypes.h"
#include "RvSipRegClient.h"
#include "RvSipContactHeader.h"
#include "RvSipAuthorizationHeader.h"

#include "RvSipExpiresHeader.h"

#include "RvSipCSeqHeader.h"
#include "RvSipViaHeader.h"
#include "RvSipEventHeader.h"

#include "RvSipRouteHopHeader.h"
#include "RvSipDateHeader.h"
#include "RvSipTransmitter.h"

#include "RvSipTransport.h"

#include "RvSipBody.h"

#include "HostDomain.h"

#include <string>
#include"..\tinyxml\tinyxml.h"
#include "..\log\log4z.h"
#include "RvSdp.h"


//判断是否合法ip地址
bool CheckIpPortAddress(char* str);


//extern
extern HostDomain g_HostMgr;

class SipMessage
{
public:
	SipMessage(const SipMessage& msg);
	SipMessage();
	~SipMessage(void);

	const SipMessage& operator=(const SipMessage& msg);

public:
	//sipmsg 的解析
	void sipMsgCallLegParse(RvSipCallLegHandle hCallLeg, RvSipTranscHandle hTransc);
	void sipMsgTransaParse(RvSipTranscHandle& hTransc);
	void sipMsgSubsParse(RvSipSubsHandle hSubs, RvSipNotifyHandle hNotify);
	void sipMsgRegParse(RvSipRegClientHandle hRegClient);
	void sipMsgResponseParse(RvSipMsgHandle hMsg);
	void sipMsgNotifyParse(RvSipMsgHandle hMsg, RvSipSubsHandle hSubs, RvSipNotifyHandle hNotify);

	//parse contact field
	void parseContact(const char* contact, char* contactUsr, char* contactIp, char* contactPort);

	//property
	inline char* sipMessageBody() { return m_pMsgBody; }
	inline char* from_user() { return m_sipHeader.from_user; }
	inline char* from_ip(){ return m_sipHeader.from_ip; }
	inline int   from_port() {return m_sipHeader.from_port; }
	inline char* to_user() { return m_sipHeader.to_user; }
	inline char* to_ip() { return m_sipHeader.to_ip; }
	inline int   to_port() { return m_sipHeader.to_port; }
	inline char* from()    {return fromHeader; }
	inline char* to()     {return toHeader; }
	inline char* method() { return m_sipHeader.method; }
	inline char* via() { return m_sipHeader.via; }
	inline char* contact() {return m_sipHeader.contact; }
	inline int cseq() {return m_sipHeader.cseq; }
	inline char* content_type() { return m_sipHeader.content_type; }
	inline int content_length() { return m_sipHeader.content_length; }
	inline int expires() { return m_sipHeader.expires; }
	inline char* uri() { return requestUri; }
	inline int status_code() { return m_sipHeader.statuscode; }
	//inline char* event() { return m_sipHeader.event; }
	inline char* subscription_state() { return m_sipHeader.subscription_state; }
	inline int subscription_state_retryafter() { return m_sipHeader.subscription_state_retryafter; }
	inline char* route_usr() { return m_sipHeader.route_usr; }
	inline char* route_ip() { return m_sipHeader.route_ip; }
	inline int route_port() { return m_sipHeader.route_port; }
	inline char* route() { return routeHeader; }
	//Authenticate
	inline bool  isAuth() {return m_sipHeader.bAuth; }
	inline char* auth_realm() {return m_sipHeader.auth_realm; }
	inline char* auth_usr() {return m_sipHeader.auth_usr; }
	inline char* auth_password() {return m_sipHeader.auth_password; }
	inline char* get_checkdate() { return m_sipHeader.datecheck; }

	inline char* GetSubject() { return m_sipHeader.subject; }

	inline char* GetUriFiled() { return domainFiled; }
	inline void setTransport(int trans) { transport = trans; }

	inline const char* getEventPackage() { return m_sipHeader.event_package; }
	inline const char* getEventId() { return m_sipHeader.event_id; }
	inline void setSubscState(const char* state)
	{
		strcpy_s(m_sipHeader.subscription_state, sizeof(m_sipHeader.subscription_state), state);
	}

  //set
	void setSipMessageBody(const char* pbuf, int Len);
	void setFrom(char* fromUsr, char* fromIp, int fromPort);
	void setTo(char* toUsr, char* toIp, int toPort);
	void setContentType(char* contentType, int len);
	void setExpires(int expires) { m_sipHeader.expires = expires; }
	void setEvent(const char* package, const char* id);
	void setAuth_realm(char* realm);
	void setAuth_usr(char* usr);
	void setAuth_password(char* psw);

	//route
	void setRoute(char* routeUsr, char* routeIp, int routePort);
	//uri
	void setUri(char* uri_ip, int uri_port);
	//date
	void setDateCheck(char* date);
	//subject
  void setSubject(char* subject);
	//filed
	void setUriFiled(char* filed) { if (filed != NULL) strcpy(domainFiled, filed); }
	//contact
	void setContact(char* contactUsr, char* contactIp, int contactPort);

	//初始化message
	void zeroSet();
	void emptyMsgBody() { memset(m_pMsgBody, 0, BODY_SIZE); }

public:
	struct sipHead
	{
		char method[64];  //INVITE BYE...
		int  statuscode;
		char via[32];     //Via
		int max_forwards; //Max-Forwards
		char from_user[32]; //from
		char from_ip[32];
		int  from_port;
		char to_user[32];   //to
		char to_ip[32];
		int  to_port;
		char callid[64];       //CallId
		int cseq;    //CSeq
		char contact[64]; //Contact
		char route_usr[32];  //route
		char route_ip[24];
		int route_port;
		char event_package[16];  //subscribe
		char event_id[16];  //subscribe
		int expires;      //Expires
		char content_type[32]; //Content-Type
		int content_length; //Content-Length
    bool bAuth;
		char auth_realm[32];  //Authorization
		char auth_usr[32];
		char auth_password[32];
		char subscription_state[16];
		int  subscription_state_retryafter;
		char datecheck[64];    //register-校时用()
		char subject[64];   
	};

public:
	void* getCallLegHandle() { return (void*)m_hCallLeg; }
	void  setCallLegHandle(void* handle) { m_hCallLeg = (RvSipCallLegHandle)handle; }

public:
	//SIP 消息头域
	sipHead m_sipHeader;
	//消息体
	int     m_bodySize;
	char*   m_pMsgBody;
	//app cmd type
	char    m_appCmdType[64];

	char    fromHeader[64];
	char    toHeader[64];
	char    routeHeader[64];
	char    requestUri[64];
	//domain filed
	char    domainFiled[64];
	int     transport; //default:0=udp,1=tcp

	RvSipCallLegHandle m_hCallLeg;
	RvSipTranscHandle m_hTransc;
	RvSipSubsHandle   m_hSubs;
	RvSipRegClientHandle m_hRegClient;

public:
	void parseMethodAndBody(RvSipMsgHandle& hMsg);
  //parse from and to header
	void parseFromAndToHead(RvSipMsgHandle& hMsg);


};

#endif

