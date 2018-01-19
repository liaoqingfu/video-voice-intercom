#ifndef _SIPDEF_H
#define _SIPDEF_H
#include <string.h>

#pragma warning(disable:4996)

//解析sdp失败，抛出异常的问题
//#define RV_SDP_CHECK_BAD_SYNTAX

//error
#define SIP_OK    0
#define SIP_ERRER -1

/************************************************************************/
/* 方法定义规则：
   server:
   1 SIP标准方法
	    1 同一方法没有附加不同功能的，处理请求的方法注册按原方法名 INVITE
      2 同一方法附加不同功能的， 处理请求的方法注册按 NOTIFY_AlarmNotify
			  标准名+_+功能名
	 2 自定义扩展方法
	    处理请求的方法注册按 DO_KeepAlive 扩展方法名+_+功能名
	 client发送端：


	 */
/************************************************************************/
//sip request

#define INVITE         "INVITE"
#define REGISTER       "REGISTER"
#define MESSAGE             "MESSAGE"
#define INFOR               "INFO"
#define BYE						 "BYE"
#define SUBSCRIBE			"SUBSCRIBE"
#define ACK						 "ACK"
#define CANCEL         "CANCEL"
#define NOTIFY         "NOTIFY"

//app method
#define PLAY    "Play"
#define AUTHSUCCESS		"AuthSuccess"

#define HEARTBEAT  "Keepalive"
#define ALARM      "Alarm"
#define CATALOG    "Catalog"
#define SUBSCRIBECATALOG "SUBSCRIBE_Catalog"
#define NOTIFYCATALOG    "NOTIFY_Catalog"
#define MESSAGEBROADCAST   "MESSAGE_Broadcast"
#define MEDIASTATUS "MediaStatus"
#define	DEVICEINFO		"DeviceInfo"
#define DEVICESTATUS	"DeviceStatus"
#define DEVICECONTROL	"DeviceControl"

#define RECORD  "DeviceControl_Record"
#define STOPRECORD  "DeviceControl_StopRecord"
#define SETGUARD    "DeviceControl_SetGuard"
#define RESETGUARD  "DeviceControl_ResetGuard"
#define RESETALARM  "DeviceControl_ResetAlarm"

//ÎÞÓ¦´ð
#define PTZCONTROL   "DeviceControl_PTZCmd"
#define BOOT        "DeviceControl_TeleBoot"

#define RECORDINFO "RecordInfo"
#define PLAYBACK   "Playback"
#define DOWNLOAD   "Download"
#define PAUSE         "PAUSE"
#define TEARDOWN      "TEARDOWN"

// Do方法：获得预置位列表信息
#define DOPRESETLIST   "DO_PresetList"


//¼øÈ¨²ÎÊý
#define AGENT_LEN 32
#define REALM_LEN 64
#define NONCE_LEN 64
#define OPAQUE_LEN 64
#define QOP_LEN 16
#define ALGORITHM_LEN 8

#define BODY_SIZE 64*1024

#define SIP_SENDRECEIVE_SIZE 1024*16

//sip 协议栈连接数目设置
#define MAX_SIP_HANDLE_NUM 64
#define MAX_SIP_CONNECT_NUM 256
//sip timeout
#define SIP_TIMEOUT 90000
#define SIP_MAX_SESSIONEXPIRES 1800

///////////////////////////

enum sdpMediaType
{
	sdpMediaType_unkonwn = -1,
	sdpMediaType_notset,
	sdpMediaType_Video,
	sdpMediaType_Audio,
	sdpMediaType_nas,
	sdpMediaType_app,
	sdpMediaType_data,
	sdpMediaType_image,
	sdpMediaType_control
};

enum sdpProtocolType
{
	sdpProtocolType_notset,
	sdpProtocolType_tcp,
	sdpProtocolType_udp,
	sdpProtocolType_rtpavp,
	sdpProtocolType_atmavp,
	sdpProtocolType_local,

};


typedef struct _tagAuthentication
{
	char agent_user[AGENT_LEN];
	char agent_password[AGENT_LEN];
	char algorithm[ALGORITHM_LEN];
	char qop[QOP_LEN];
	char realm[REALM_LEN];
	char nonce[NONCE_LEN];
	char opaque[OPAQUE_LEN];
	char sdomain[AGENT_LEN];
}Authentication;


//sdp o
struct Origin
{
	char usr[33];
	char vision[8];
	char sid[8];
	char nettype[8];
	char addrtype[8];
	char addr[32];
	const Origin& operator=(const Origin& o)
	{
		strcpy(usr, o.usr);
		strcpy(vision, o.vision);
		strcpy(sid, o.sid);
		strcpy(nettype, o.nettype);
		strcpy(addrtype, o.addrtype);
		strcpy(addr, o.addr);

		return *this;
	}
};



//m
struct mediaDescr
{
	struct des
	{
		sdpMediaType mtype;
		int mport;
		sdpProtocolType protocol;
		char formats[8][8];

		const des& operator=(const des& m)
		{
			mtype = m.mtype;
			mport = m.mport;
			protocol = m.protocol;

			for (int i = 0; i < 8; i++)
			{
				strcpy(formats[i], m.formats[i]);
			}

			return *this;
		}
	};

	int count;
	des mediades[4];

	const mediaDescr& operator=(const mediaDescr& m)
	{
		for (int i = 0; i < sizeof(mediades)/sizeof(des); i++)
		{
			mediades[i] = m.mediades[i];
			count = m.count;
		}
		return *this;
	}

};

//m
struct attribute
{
	char name[16];
	char value[32];

	const attribute& operator=(const attribute& a)
	{
		strcpy(name, a.name);
		strcpy(value, a.value);

		return *this;
	}
};

//c
struct cconnect
{
	char netType[8];
	char addrType[8];
	char addr[24];

	const cconnect& operator=(const cconnect& c)
	{
		strcpy(netType, c.netType);
		strcpy(addrType, c.addrType);
		strcpy(addr, c.addr);

		return *this;
	}
};


#endif