#include "SipPtzCtrl.h"
#include "../Utility/XmlParser.h"
#include "GBStandard.h"
#include "GlobalCtrl.h"

#include "RealPlay.h"
#include "BcAdaptor.h"

struct PtzExchange
{
	char gbPtzCmd;
	char bcPtzCmd;
};

PtzExchange gPtzExchange[] = 
{
	{0x00, PTZ_STOP},
	{0x01, PTZ_RIGHT},
	{0x02, PTZ_LEFT},
	{0x04, PTZ_DOWN},
	{0x08, PTZ_UP},
	{0x10, PTZ_ZOOMOUT},
	{0x20, PTZ_ZOOMIN}
};

//有可能是左上，右上，左下，右下等组合
void getCmd(char gbcmd, char* bcCmd)
{
	*bcCmd = PTZ_STOP;

	for (int i = 0; i < sizeof(gPtzExchange); i++)
	{
		if (gPtzExchange[i].gbPtzCmd == gbcmd)
		{
			*bcCmd = gPtzExchange[i].bcPtzCmd;
			break;
		}
	}

}



SipPtzCtrl::SipPtzCtrl(CSipMgr* pServer)
{
	if (pServer != NULL)
	{
		pServer->Register(MESSAGE, PTZCONTROL, PtzCommandProc, this);
	}
}


SipPtzCtrl::~SipPtzCtrl(void)
{
}


void SipPtzCtrl::PtzCommandProc(SipMessage& msg, int& iresult, void* contex)
{
	iresult = SIP_SUCCESS;

	char* body = msg.sipMessageBody();
	//云台控制
	//解析云台控制参数
	try
	{
		XmlParser xml;
		int ret = xml.ParseDocumentXml((char*)body);
		if (ret != 0)
		{
			throw -1 ;
		}

		TiXmlElement* root = xml.GetRootNode();
		//std::string value;
		//value = (char*)root->Value();

		TiXmlElement* deviceId = NULL;
		TiXmlElement* ptzcmd = NULL;
		deviceId = xml.GetSubNode(root, "DeviceID");
		if (deviceId == NULL)
		{
			throw -2 ;
		}
		int devType = 0;
		int devId = 0;
		GBSysCode::getDevTypeAndId((char*)(deviceId->GetText()), &devType, &devId);

		ptzcmd = xml.GetSubNode(root, "PTZCmd");
		if (ptzcmd == NULL)
		{
			throw -3 ;
		}

		PtzCmd ptz;
		ParsePtzCmd((char*)ptzcmd->GetText(), &ptz);

		HANDLE real = RealPlay::RealStreamGet(devId, devType);
		if (real != NULL)
		{
			char bcCmd = 0;
			getCmd(ptz.cmd, &bcCmd);

			//parse ptz speed
			int speed = 1;
			if (bcCmd == PTZ_LEFT || bcCmd == PTZ_RIGHT)
			{
				speed = ptz.arg1;
			}
			else if (bcCmd == PTZ_UP || bcCmd == PTZ_DOWN)
			{
				speed = ptz.arg2;
			}
			//暂时没有用到云台其他参数
			_LOG(LOG_LEVEL_DEBUG, "###########云台控制参数:%d, speed=%d", bcCmd, speed);
			GLOBJ(gAdaptor)->devPtzControl(real, bcCmd, 1, speed);
		}
	}
	catch (std::exception &e)
	{
			
	}


	msg.emptyMsgBody();

	/*

	#define remote cmd


	enum DomeCmd
	{
	DOME_STOP   = 0, // 停止   
	DOME_PAN    = 1, // 摆动     0:  复位(zero);  1: 左(left)； -1：右(right)
	DOME_TILT   = 2, // 俯仰     0:  复位(zero);  1: 上(up)；   -1：下(down)
	DOME_ZOOM   = 3, // 缩放     0:  自动(auto);  1：大(wide)   -1：小(tele)
	DOME_FOCUS  = 4, // 焦距     0:  自动(auto);  1: 近(near)； -1：远(far)
	DOME_IRIS   = 5, // 光圈     0:  自动(auto);  1: 开(open);  -1: 关闭(close)
	DOME_       = 6, // 未定义
	DOME_SCAN   = 7, // 自动扫描 0-255：区域(zone), 0为全部
	};

	struct DomeCmdMapItem
	{
	int remote_cmd;
	int server_cmd;
	int arg;
	};

	DomeCmdMapItem tagDomeCmdMaps[] =
	{
	{IDC_BTN_DOME_UP,      DOME_TILT,   1},
	{IDC_BTN_DOME_DOWN,    DOME_TILT,  -1},
	{IDC_BTN_DOME_LEFT,    DOME_PAN,    1},
	{IDC_BTN_DOME_RIGHT,   DOME_PAN,   -1},
	{IDC_BTN_DOME_1_PLUS,  DOME_ZOOM,   1},
	{IDC_BTN_DOME_1_MINUS, DOME_ZOOM,  -1},
	{IDC_BTN_DOME_2_PLUS,  DOME_FOCUS,  1},
	{IDC_BTN_DOME_2_MINUS, DOME_FOCUS, -1},
	{IDC_BTN_DOME_3_PLUS,  DOME_IRIS,   1},
	{IDC_BTN_DOME_3_MINUS, DOME_IRIS,  -1}
	};

	CString sCmd = "Video.Live.ptz";
	XmlRpcValue param, result;
	param["camera"] = pVideo->GetCamera();
	param["issuer"] = pVideo->GetIssuer();
	param["cmd"] = iCmd;
	param["arg"] = iArg;
	CString sVia = pVideo->GetVia();
	TransferCmdParamByVia(sCmd, param, sVia);
	return gRpcCmd.ExecuteNonBlock(sCmd, param, result);
	*/
}



void SipPtzCtrl::ParsePtzCmd(const char* cmd, PtzCmd* ptz)
{
	std::string strCmd = cmd;
	int ingHex = 0;
	sscanf(strCmd.substr(0, 2).c_str(), "%x", &ingHex);
	ptz->head = ingHex;
	sscanf(strCmd.substr(2, 2).c_str(), "%x", &ingHex);
	ptz->assemble1 = ingHex;
	sscanf(strCmd.substr(4, 2).c_str(), "%x", &ingHex);
	ptz->addr8L = ingHex;
	sscanf(strCmd.substr(6, 2).c_str(), "%x", &ingHex);
	ptz->cmd = ingHex;
	sscanf(strCmd.substr(8, 2).c_str(), "%x", &ingHex);
	ptz->arg1 = ingHex;
	sscanf(strCmd.substr(10, 2).c_str(), "%x", &ingHex);
	ptz->arg2 = ingHex;
	sscanf(strCmd.substr(12, 2).c_str(), "%x", &ingHex);
	ptz->assemble2 = ingHex;
	sscanf(strCmd.substr(14, 2).c_str(), "%x", &ingHex);
	ptz->checksum = ingHex;
}
