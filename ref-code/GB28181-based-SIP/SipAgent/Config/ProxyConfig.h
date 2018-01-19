#ifndef _PROXYCONFIG_H
#define _PROXYCONFIG_H

#include "../Utility/XmlParser.h"

#include "HostDomain.h"

#include <list>

/*
1 生成配置文件 proxy_config.xml
2 读取各个模块全局配置项，存储到内存中
3 对各个模块提供 读 写配置项接口
*/
/*
<proxy_cfg>
  <module_alarm>
	 <option>bAccept</option>
	</module_alarm>
	<module_sip>
	</module_sip>
</proxy_cfg>
*/

class ProxyConfig
{
public:
	ProxyConfig(void);
	~ProxyConfig(void);

public:
	//初始化配置文件，创建配置文件
	int InitCfg();

	//加载配置文件
	int LoadCfg();

public:
	XmlParser* m_xmlCfg;

	//模块
	//main
	//center server ip
	std::string main_serverIp;
	//center server port
	int  main_serverPort;
	//登陆 server 的user name
	std::string main_loginName;
	//登陆 server 的password
	std::string main_loginPassword;
	//启动的时候是否重启目录推送
	int main_IsReSendDir;

	//域名称配置
	std::string domain_name;

	//live 现场各厂家媒体信息配置
	//live streamer 的ip 和端口
	std::string live_streamerIp;
	int live_streamer_cmd_port;
	int live_streamer_heartbeat_port;

	//sip config
	//本地sip接收和发送端口
	int  sip_localPort;     //本地sip ip和端口
	std::string sip_localIp;
	int  sip_remotePort;  //远程sip端的ip和端口
	std::string sip_remoteIp;
	std::string sip_localUser;  //本地user
	std::string sip_remoteUser;  //远程user
	//鉴权
	std::string sip_auth_User;    //鉴权 用户名、密码
	std::string sip_auth_Password;
	std::string sip_auth_realm; 
	std::string sip_auth_nonce;
	std::string sip_auth_sdomain;
	std::string sip_auth_opaque;
	//注册的时间和心跳时间间隔
	int sip_heartbeat;
	int sip_RegExpires;

  //sip 域名
	std::list<AbsDomain> m_SipDomainList;

	//alarm
	std::string alarm_serverIp;
	int alarm_serverPort;
	int alarm_localReceivePort;

	//playback
	std::string playback_ip;
	int playback_port;
	std::string playback_rtsp_addr;//回放模块的rtsp ip和port，组织成url




public:
	inline char* getServerIp() {return (char*)main_serverIp.c_str(); }
	inline int   getServerPort() {return main_serverPort; }
	inline char* getLoginName() {return (char*)main_loginName.c_str(); }
	inline char* getLoginPassword() {return (char*)main_loginPassword.c_str(); }
	inline bool  IsReSendDir()
	{
		bool bsend = (main_IsReSendDir == 0 ? false : true);
		return bsend;
	}

	//live 
	inline char* getStreamerIp() { return (char*)live_streamerIp.c_str(); }
	inline int   getStreamerCmdPort() { return live_streamer_cmd_port; }
	inline int   getStreamerHeartBeatPort() { return live_streamer_heartbeat_port; }
	//inline int   getStreamerHeartBeatPort() { return ;}

	//sip
	inline int   getSiplocalPort() {return sip_localPort; }
	inline char* getSiplocalIp() { return (char*)sip_localIp.c_str(); }
	inline char* getSipremoteIp() { return (char*)sip_remoteIp.c_str(); }
	inline int   getSipremotePort() { return sip_remotePort; }
	inline char* getSiplocalUser() { return (char*)sip_localUser.c_str(); }
	inline char* getSipremoteUser() { return (char*)sip_remoteUser.c_str(); }
	inline char* getSip_authUser() { return (char*)sip_auth_User.c_str(); }
	inline char* getSip_authPassword() { return (char*)sip_auth_Password.c_str(); }
	inline char* getSip_auth_realm() { return (char*)sip_auth_realm.c_str(); } 
	inline char* getSip_authnonce() { return (char*)sip_auth_nonce.c_str(); }
	inline char* getSip_authsdomain() { return (char*)sip_auth_sdomain.c_str(); }
	inline char* getSip_authopaque() { return (char*)sip_auth_opaque.c_str(); }

	inline char* getLocalDomainName() {return (char*)domain_name.c_str(); }

	inline int   getSip_heartBeatTm() { return sip_heartbeat; }
	inline int   getSip_regExpiresTm() { return sip_RegExpires; }

	//alarm
	inline char* getAlarmServerIp() { return (char*)alarm_serverIp.c_str(); }
	inline int getAlarmLocalPort() { return alarm_localReceivePort; }
	inline int getAlarmServerPort() { return alarm_serverPort; }

	//playback
	inline char* getPlaybackip() { return (char*)playback_ip.c_str(); }
	inline int   getPlaybackPort() { return playback_port; }
	inline char* getPlaybackRtspAddr() { return (char*)playback_rtsp_addr.c_str(); }

public:
	//初始化主模块
	void defaultMain();
	void parseMain();
	//初始化现场模块
	void defaultLive();
	void parseLive();
	void liveInit();
	//sip
	void defaultSip();
	void parseSip();
	void sipInit();
	//sip_domain
	void defaultSipDomain();
	void parseSipDomain();
	void sipDomainInit();
	//alarm
	void defaultAlarm();
	void parseAlarm();

	//playback
	void defaultPlayback();
	void parsePlayback();

};


#endif

