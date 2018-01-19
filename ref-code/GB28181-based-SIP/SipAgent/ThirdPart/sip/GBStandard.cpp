#include "GBStandard.h"

#include "RvSdp.h"
#include "MansRtsp.h"

#include "Utility/XmlParser.h"

#include "Utility/Format.h"
#include "GlobalCtrl.h"
#include "config/ProxyConfig.h"

#include "BcAdaptor/adaptorCommon.h"

using namespace GBSysCode;
using namespace GBDevControlReq;


CGBStandard::CGBStandard(void)
{
}

CGBStandard::~CGBStandard(void)
{
}


TiXmlElement* CGBStandard::NodeFind(char* value, TiXmlElement* node)
{
	TiXmlElement* findNode;
	if (node == NULL)
		return NULL;

	while(node != NULL)
	{
		char* name = (char*)node->Value();
		if (strcmp(name, value) == 0)
			return node;

		TiXmlElement* child = node->FirstChildElement();

		findNode = NodeFind(value, child);
		if (findNode != NULL)
			return findNode;

		node = node->NextSiblingElement();
	}

	return NULL;
}


void CGBStandard::GBParseAppCmdTypeStr(const char* msg, std::string& strCmd)
{
	std::string strValue;
	TiXmlElement* findNode;
	TiXmlDocument *xml = new TiXmlDocument();
	do 
	{
		if (xml != NULL)
		{
			if (xml->Parse(msg) == NULL)
			{
				//PLOG("SIP", "SipMessageBody can't find the method name");
				//break;
			}
			//解析出SIP方法的消息体中附带的功能串
			TiXmlElement* rootElement = xml->RootElement();
			//查找指定字段的值
			findNode = NodeFind("CmdType", rootElement);
			if (findNode != NULL)
			{
				strValue = (char*)findNode->GetText();

				//判断是否有子命令RecordCmd、PTZCmd,SetGuard/ResetGuard ,result
				findNode = NodeFind("Result", rootElement);
				if (findNode != NULL)
				{
					break;
				}

				findNode = NodeFind("RecordCmd", rootElement);
				if (findNode != NULL)
				{
					strValue += "_";
					strValue += (char*)findNode->GetText();
					break;
				}

				findNode = NodeFind("PTZCmd", rootElement);
				if (findNode != NULL)
				{
					strValue += "_";
					strValue += "PTZCmd";
					break;
				}

				findNode = NodeFind("GuardCmd", rootElement);
				if (findNode != NULL)
				{
					strValue += "_";
					strValue += (char*)findNode->GetText();
					break;
				}

				findNode = NodeFind("AlarmCmd", rootElement);
				if (findNode != NULL)
				{
					strValue += "_";
					strValue += (char*)findNode->GetText();
					break;
				}

				findNode = NodeFind("TeleBoot", rootElement);
				if (findNode != NULL)
				{
					strValue += "_";
					strValue += "TeleBoot";
					break;
				}

			}
			else
				break;
		}
	} while (0);

	delete xml;
	xml = NULL;

	strCmd = strValue;
}


//-------------------------------------------------------

struct ExchangeType
{
	view_id bsType;
	DevTypeCode gbType;
};


static ExchangeType gTransferMap[] = 
{
	{view_video, VideoServer_Code},
	{view_root, CenterServer_Code},
	{view_district, District_Code},
	{view_site, Site_Code},
	{view_district, District_Code},
	{view_dvr, Dvr_Code},
	{view_encoder, Encoder_Code},
	{view_decoder, Decoder_Code},
	{view_nvr, NVR_Code},
	{view_camera, Camera_Code},
	{view_ipcamera, Ipc_Code}
};


void exchangeType(int* bsType, int* gbType)
{
	if (*bsType != 0)
	{
		for (int i = 0; i < sizeof(gTransferMap); i++)
		{
			if (gTransferMap[i].bsType == *bsType)
			{
				*gbType = gTransferMap[i].gbType;
				break;
			}
		}
	}
	else 
	{
		for (int i = 0; i < sizeof(gTransferMap); i++)
		{
			if (gTransferMap[i].gbType == *gbType)
			{
				*bsType = gTransferMap[i].bsType;
				break;
			}
		}
	}
}




void CGBStandard::GBParseSdpCmdTypeStr(const char* msg, std::string& strCmd)
{
	//解析sdp
	int actualLen = 0;
	RvSdp* parser = new RvSdp();
	if (parser->ParseSdpInfo((char*)msg, actualLen) == 0)
	{
		strCmd = parser->getS();
	}

	delete parser;
	parser = NULL;
}



void CGBStandard::GBParseMansRtspCmdTypeStr(const char* msg, std::string& strCmd)
{
	MansRtsp rtsp;
	rtsp.ParseMansRtsp(msg);
	strCmd = rtsp.method;
}

//------------------------------
using namespace GBSysCode;
#include <string>


std::string  GBSysCode::gb28181Code(std::string& civilcode, int nodeType, int nodeId)
{
	std::string code;
	if (nodeType == view_null)
	{
		code = GLOBJ(gConfig)->getSiplocalUser();
		return code;
	}

	if (nodeType == view_root && nodeType == view_video)
	{
		std::string orga = GLOBJ(gConfig)->getSiplocalUser();
		orga = orga.substr(0, 4);
		code = orga;

		return code;
	}

	int gbType = 0;
	exchangeType(&nodeType, &gbType);

	std::string orga = civilcode;
	orga = orga.substr(0, 10);

	Format fm;
	char idStr[9] = {0};
	//hik 平台对接
	//5:公安网
	sprintf(idStr, "5%06d", nodeId);
	const char* business = "00";
	GBSysCode::constructSysCode(code, orga.c_str(), business, (fm<<gbType).data(), idStr);

	return code;
}

void GBSysCode::constructSysCode(std::string& code, const char* orga, const char* business, const char* type, const char* id)
{
	//福州马尾区，暂定
	//std::string orga1 = GLOBJ(gConfig)->getSiplocalUser();
	//orga1 = orga1.substr(0, 10);

	code = orga;//orga1
	//code += business;
	code += type;
	code += id;

}


void GBSysCode::getDevTypeAndId(const char* code, int* type, int* id)
{
	std::string strCode = code;
	if (strCode.length() <= 0)
	{
		return ;
	}

	std::string tmp = strCode.substr(8+2, 3);
	*type = atoi(tmp.c_str());
	tmp.clear();
	tmp = strCode.substr(8+2+3+1+1, 5);
	*id = atoi(tmp.c_str());
}

//------------------
using namespace GBDevControlReq;

int GBDevControlReq::DirQueryParse(const char* req, DevControl* ctrl)
{
	assert(req != NULL && ctrl != NULL);

	XmlParser xml;
	int ret = xml.ParseDocumentXml((char*)req);
	if (ret != 0)
	{
		return -1;
	}

	TiXmlElement* root = xml.GetRootNode();
	std::string value;
	value = (char*)root->Value();

	xml.ParseNode("CmdType", ctrl->m_controlCmd);
	std::string tmp;
	xml.ParseNode("SN", tmp);
	ctrl->m_sn = atoi(tmp.c_str());
	xml.ParseNode("DeviceID", ctrl->devId);

	return 0;
}