#include "ProxyConfig.h"

#include "../Utility/utility.h"

#define CONFIG_NAME "proxy_config.xml"


ProxyConfig::ProxyConfig(void)
{
	//center server ip
	main_serverIp = "192.168.50.229";
	main_serverPort = 8000;
	main_loginName = "admin";
	main_loginPassword = "admin";
	main_IsReSendDir = 1;

	//live
	live_streamerIp = "192.168.8.169";
	live_streamer_cmd_port = 3721;
	live_streamer_heartbeat_port = 8101;

	//alarm
	alarm_serverIp = "192.168.50.229";
	alarm_serverPort = 5140;
	alarm_localReceivePort = 5140;

	//playback
	playback_ip = "192.168.8.251";
	playback_port = 7021;
	playback_rtsp_addr = "192.168.8.251:7111";

	m_xmlCfg = new XmlParser();

}

ProxyConfig::~ProxyConfig(void)
{
	if (m_xmlCfg != NULL)
	{
		delete m_xmlCfg;
		m_xmlCfg = NULL;
	}

}

//初始化配置文件，创建配置文件
int ProxyConfig::InitCfg()
{
	std::string path = GetAppPath();
	path += CONFIG_NAME;
	if (!IsFileExist(path))//如果不存在，则创建，初始化配置文件
	{
		//int err = ::GetLastError();
		TiXmlElement* node;
		char temp[32] = {0};
		m_xmlCfg->AddRootNode("proxy_cfg");
		node = m_xmlCfg->InsertSubNode("proxy_cfg", "module_directory", ""); //目录推送模块
		//main
		defaultMain();
		//sip
		sipInit();
		defaultSip();
		//sipdomain
		sipDomainInit();
		defaultSipDomain();
		//alarm
		defaultAlarm();
		//live 
		liveInit();
		defaultLive();

		//playback
		defaultPlayback();


		//创建xml配置文件
		int ret = m_xmlCfg->SaveXmlFile((char*)path.c_str());
	}
	else
	{
		LoadCfg();
	}

	return 0;

}


//加载配置文件
int ProxyConfig::LoadCfg()
{
	if (m_xmlCfg->LoadFile(CONFIG_NAME) != 0)
		return -1;

	//解析xml配置文件
	//main
	parseMain();
	//sip
	parseSip();
	//live
	parseLive();
	//alarm
	parseAlarm();
	//playback
	parsePlayback();
	//domain
	parseSipDomain();
	

	return 0;
}

//初始化现场模块
void ProxyConfig::defaultLive()
{
	char str[32] = { 0 };
	TiXmlElement* node = NULL;
	node = m_xmlCfg->InsertSubNode("proxy_cfg", "module_live", "");
	m_xmlCfg->InsertSubNode("module_live", "proxy_streamerIp", (char*)live_streamerIp.c_str());
	sprintf_s(str, sizeof(str), "%d", live_streamer_cmd_port);
	m_xmlCfg->InsertSubNode("module_live","proxy_streamerCmdPort", str);
	memset(str, 0, sizeof(str));
	sprintf_s(str, sizeof(str), "%d", live_streamer_heartbeat_port);
	m_xmlCfg->InsertSubNode("module_live","proxy_streamerHeartBeatPort", str);

}


//初始化主模块
void ProxyConfig::defaultMain()
{
	TiXmlElement* node;
	char temp[32] = {0};
	//main initialize
	node = m_xmlCfg->InsertSubNode("proxy_cfg", "module_main", "");  //主模块
	node = m_xmlCfg->InsertSubNode("module_main", "serverIp", (char*)main_serverIp.c_str());
	sprintf_s(temp, sizeof(temp), "%d", main_serverPort);
	node = m_xmlCfg->InsertSubNode("module_main", "serverPort", temp);
	node = m_xmlCfg->InsertSubNode("module_main", "loginName", (char*)main_loginName.c_str());
	node = m_xmlCfg->InsertSubNode("module_main", "loginPassword", (char*)main_loginPassword.c_str());
	memset(temp, 0, sizeof(temp));
	sprintf_s(temp, sizeof(temp), "%d", main_IsReSendDir);
	node = m_xmlCfg->InsertSubNode("module_main", "IsReSendDir", temp);

}

void ProxyConfig::defaultSip()
{
	if (m_xmlCfg == NULL)
		return ;
	char str[32] = { 0 };
	TiXmlElement* node = NULL;
	node = m_xmlCfg->InsertSubNode("proxy_cfg", "module_sip", "");
	sprintf_s(str, sizeof(str), "%d", sip_localPort);
	m_xmlCfg->InsertSubNode("module_sip", "sip_localPort", str);
	m_xmlCfg->InsertSubNode("module_sip","sip_localIp", (char*)sip_localIp.c_str());
	memset(str, 0, sizeof(str));
	sprintf_s(str, sizeof(str), "%d", sip_remotePort);
	m_xmlCfg->InsertSubNode("module_sip", "sip_remotePort", str);
	m_xmlCfg->InsertSubNode("module_sip","sip_remoteIp", (char*)sip_remoteIp.c_str());

	m_xmlCfg->InsertSubNode("module_sip","sip_localUser", (char*)sip_localUser.c_str());
	m_xmlCfg->InsertSubNode("module_sip","sip_remoteUser", (char*)sip_remoteUser.c_str());

	m_xmlCfg->InsertSubNode("module_sip","domain_name", (char*)domain_name.c_str());

	m_xmlCfg->InsertSubNode("module_sip","sip_auth_User", (char*)sip_auth_User.c_str());
	m_xmlCfg->InsertSubNode("module_sip","sip_auth_Password", (char*)sip_auth_Password.c_str());
	m_xmlCfg->InsertSubNode("module_sip","sip_auth_realm", (char*)sip_auth_realm.c_str());
	m_xmlCfg->InsertSubNode("module_sip","sip_auth_nonce", (char*)sip_auth_nonce.c_str());
	m_xmlCfg->InsertSubNode("module_sip","sip_auth_sdomain", (char*)sip_auth_sdomain.c_str());
	m_xmlCfg->InsertSubNode("module_sip","sip_auth_opaque", (char*)sip_auth_opaque.c_str());

	memset(str, 0, sizeof(str));
	sprintf_s(str, sizeof(str), "%d", sip_heartbeat);
	m_xmlCfg->InsertSubNode("module_sip","sip_HeartBeatTime", str);
	memset(str, 0, sizeof(str));
	sprintf_s(str, sizeof(str), "%d", sip_RegExpires);
	m_xmlCfg->InsertSubNode("module_sip","sip_RegExpiresTime", str);

}


void ProxyConfig::parseSip()
{
	if (m_xmlCfg == NULL)
		return ;

	TiXmlElement* node;
	TiXmlElement* temp;
	std::string str;
	node = m_xmlCfg->GetSubNode(NULL, "module_sip");

	temp = m_xmlCfg->GetSubNode(node, "sip_localPort");
	m_xmlCfg->ParseNode(temp, str);
	sip_localPort = atoi(str.c_str());
	temp = m_xmlCfg->GetSubNode(node, "sip_localIp");
	m_xmlCfg->ParseNode(temp, sip_localIp);
	temp = m_xmlCfg->GetSubNode(node, "sip_remotePort");
	m_xmlCfg->ParseNode(temp, str);
	sip_remotePort = atoi(str.c_str());
	temp = m_xmlCfg->GetSubNode(node, "sip_remoteIp");
	m_xmlCfg->ParseNode(temp, sip_remoteIp);
	temp = m_xmlCfg->GetSubNode(node, "sip_localUser");
	m_xmlCfg->ParseNode(temp, sip_localUser);
	temp = m_xmlCfg->GetSubNode(node, "sip_remoteUser");
	m_xmlCfg->ParseNode(temp, sip_remoteUser);

	temp = m_xmlCfg->GetSubNode(node, "domain_name");
	m_xmlCfg->ParseNode(temp, domain_name);
	

	temp = m_xmlCfg->GetSubNode(node, "sip_auth_User");
	m_xmlCfg->ParseNode(temp, sip_auth_User);
	temp = m_xmlCfg->GetSubNode(node, "sip_auth_Password");
	m_xmlCfg->ParseNode(temp, sip_auth_Password);
	temp = m_xmlCfg->GetSubNode(node, "sip_auth_realm");
	m_xmlCfg->ParseNode(temp, sip_auth_realm);
	temp = m_xmlCfg->GetSubNode(node, "sip_auth_nonce");
	m_xmlCfg->ParseNode(temp, sip_auth_nonce);
	temp = m_xmlCfg->GetSubNode(node, "sip_auth_sdomain");
	m_xmlCfg->ParseNode(temp, sip_auth_sdomain);
	temp = m_xmlCfg->GetSubNode(node, "sip_auth_opaque");
	m_xmlCfg->ParseNode(temp, sip_auth_opaque);

	temp = m_xmlCfg->GetSubNode(node, "sip_HeartBeatTime");
	m_xmlCfg->ParseNode(temp, str);
	sip_heartbeat = atoi(str.c_str());
	temp = m_xmlCfg->GetSubNode(node, "sip_RegExpiresTime");
	m_xmlCfg->ParseNode(temp, str);
	sip_RegExpires = atoi(str.c_str());
}


void ProxyConfig::defaultAlarm()
{
	if (m_xmlCfg == NULL)
		return ;
	char str[32] = { 0 };
	TiXmlElement* node = NULL;
	node = m_xmlCfg->InsertSubNode("proxy_cfg", "module_alarm", "");
	sprintf_s(str, sizeof(str), "%d", alarm_serverPort);
	m_xmlCfg->InsertSubNode("module_alarm", "alarm_serverPort", str);
	m_xmlCfg->InsertSubNode("module_alarm","alarm_serverIp", (char*)alarm_serverIp.c_str());

	memset(str, 0, sizeof(str));
	sprintf_s(str, sizeof(str), "%d", alarm_localReceivePort);
	m_xmlCfg->InsertSubNode("module_alarm", "alarm_localReceivePort", str);
  
}


void ProxyConfig::parseAlarm()
{
	if (m_xmlCfg == NULL)
		return ;

	TiXmlElement* node;
	TiXmlElement* temp;
	std::string str;
	node = m_xmlCfg->GetSubNode(NULL, "module_alarm");

	temp = m_xmlCfg->GetSubNode(node, "alarm_serverPort");
	m_xmlCfg->ParseNode(temp, str);
	alarm_serverPort = atoi(str.c_str());
	temp = m_xmlCfg->GetSubNode(node, "alarm_serverIp");
	m_xmlCfg->ParseNode(temp, alarm_serverIp);
	temp = m_xmlCfg->GetSubNode(node, "alarm_localReceivePort");
	m_xmlCfg->ParseNode(temp, str);
	alarm_localReceivePort = atoi(str.c_str());
}


//playback
void ProxyConfig::defaultPlayback()
{
	if (m_xmlCfg == NULL)
		return ;
	char str[32] = { 0 };
	TiXmlElement* node = NULL;
	node = m_xmlCfg->InsertSubNode("proxy_cfg", "module_playback", "");
	sprintf_s(str, sizeof(str), "%d", playback_port);
	m_xmlCfg->InsertSubNode(node, "playback_port", str);
	m_xmlCfg->InsertSubNode(node,"playback_ip", (char*)playback_ip.c_str());
	m_xmlCfg->InsertSubNode(node, "playback_rtsp_addr", (char*)playback_rtsp_addr.c_str());
}


void ProxyConfig::parsePlayback()
{
	if (m_xmlCfg == NULL)
		return ;

	TiXmlElement* node;
	TiXmlElement* temp;
	std::string str;
	node = m_xmlCfg->GetSubNode(NULL, "module_playback");
	temp = m_xmlCfg->GetSubNode(node, "playback_port");
	m_xmlCfg->ParseNode(temp, str);
	playback_port = atoi(str.c_str());
	temp = m_xmlCfg->GetSubNode(node, "playback_ip");
	m_xmlCfg->ParseNode(temp, playback_ip);
	temp = m_xmlCfg->GetSubNode(node, "playback_rtsp_addr");
	m_xmlCfg->ParseNode(temp, playback_rtsp_addr);
}


void ProxyConfig::sipInit()
{
	sip_localPort = 5060;     //本地sip ip和端口
	sip_localIp = "192.168.8.251";
	sip_remotePort = 5060;  //远程sip端的ip和端口
	sip_remoteIp = "192.168.8.195";
	sip_localUser = "sip_proxy";  //本地user
	sip_remoteUser = "sip_server";  //远程user

	domain_name = "domain_name";
	//鉴权
	sip_auth_User = "admin";    //鉴权 用户名、密码
	sip_auth_Password = "12345";
	sip_auth_realm = "SimpleRealm"; 
	sip_auth_nonce = "1234567890";
	sip_auth_sdomain = "sip:SimpleDomain@192.168.8.251";
	sip_auth_opaque = "SimpleOpaque";

	sip_heartbeat = 60;
	sip_RegExpires = 3600;
}



void ProxyConfig::defaultSipDomain()
{
	if (m_xmlCfg == NULL)
		return ;

	char str[32] = { 0 };
	TiXmlElement* node = NULL;
	node = m_xmlCfg->InsertSubNode("proxy_cfg", "sip_domain", "");

	std::list<AbsDomain>::iterator it;
	for (it = m_SipDomainList.begin(); it != m_SipDomainList.end(); it++)
	{
		TiXmlElement* tempNode;
		tempNode = m_xmlCfg->InsertSubNode(node, "item", "");
		m_xmlCfg->InsertSubNode(tempNode,"domain_name", it->domainName);
		m_xmlCfg->InsertSubNode(tempNode,"sip_user", it->user);
		m_xmlCfg->InsertSubNode(tempNode,"sip_host", it->uriHost);
		memset(str, 0, sizeof(str));
		sprintf_s(str, sizeof(str), "%d", it->uriPort);
		m_xmlCfg->InsertSubNode(tempNode,"sip_port", str);
	}
}

void ProxyConfig::parseSipDomain()
{
	if (m_xmlCfg == NULL)
		return ;

	TiXmlElement* node;
	TiXmlElement* itemNode;
	std::string str;
	node = m_xmlCfg->GetSubNode(NULL, "sip_domain");
	itemNode = m_xmlCfg->GetSubNode(node, "item");
	while (itemNode != NULL)
	{
		TiXmlElement* subNode = m_xmlCfg->GetSubNode(itemNode, "domain_name");
		m_xmlCfg->ParseNode(subNode, str);
		AbsDomain domain;
		strcpy(domain.domainName, str.c_str());

		subNode = m_xmlCfg->GetSubNode(itemNode, "sip_user");
		m_xmlCfg->ParseNode(subNode, str);
		strcpy(domain.user, str.c_str());

		subNode = m_xmlCfg->GetSubNode(itemNode, "sip_host");
		m_xmlCfg->ParseNode(subNode, str);
		strcpy(domain.uriHost, str.c_str());

		subNode = m_xmlCfg->GetSubNode(itemNode, "sip_port");
		m_xmlCfg->ParseNode(subNode, str);
		domain.uriPort = atoi(str.c_str());

		m_SipDomainList.push_back(domain);

		itemNode = m_xmlCfg->GetNextSiblingNode(itemNode, "item");
	}


}

void ProxyConfig::sipDomainInit()
{
	AbsDomain domain;
	strcpy(domain.domainName, "3401000000");
	strcpy(domain.uriHost, "192.168.8.251");
	strcpy(domain.user, "34010000002000000001");
	domain.uriPort = 5060;
	m_SipDomainList.push_back(domain);
}


void ProxyConfig::parseMain()
{
	//main
	std::string serverPort, sipPort;
	std::string isReSend;
	m_xmlCfg->ParseNode("serverIp", main_serverIp);
	m_xmlCfg->ParseNode("serverPort", serverPort);
	main_serverPort = atoi(serverPort.c_str());
	m_xmlCfg->ParseNode("loginName", main_loginName);
	m_xmlCfg->ParseNode("loginPassword", main_loginPassword);
	m_xmlCfg->ParseNode("IsReSendDir", isReSend);
	main_IsReSendDir = atoi(isReSend.c_str());
}


void ProxyConfig::parseLive()
{
	if (m_xmlCfg == NULL)
		return ;
	TiXmlElement* node;
	TiXmlElement* temp;
	std::string txt;
	node = m_xmlCfg->GetSubNode(NULL, "module_live");
	temp = m_xmlCfg->GetSubNode(node, "proxy_streamerIp");
	m_xmlCfg->ParseNode(temp, live_streamerIp);
	temp = m_xmlCfg->GetSubNode(node, "proxy_streamerCmdPort");
	m_xmlCfg->ParseNode(temp, txt);
	live_streamer_cmd_port = atoi(txt.c_str());
	temp = m_xmlCfg->GetSubNode(node, "proxy_streamerHeartBeatPort");
  m_xmlCfg->ParseNode(temp, txt);
	live_streamer_heartbeat_port = atoi(txt.c_str());

	node = m_xmlCfg->GetSubNode(node, "item");

}


#if 0
int ProxyConfig::searchStreamInfo(std::string& vendor, StreamInfoOfVendor& info)
{
	int ret = -1;

	return ret;
}
#endif 



void ProxyConfig::liveInit()
{

}
