#include "Directory.h"

#include "../GlobalCtrl.h"
#include "../Utility/AsynPolicy.h"
#include "SipMgr.h"

#include "GBStandard.h"
#include "../Utility/XmlParser.h"
#include "config/ProxyConfig.h"
#include "BcAdaptor.h"
#include "XmlRpcValue.h"
using namespace XmlRpc;

#include "Utility/Format.h"

#include "Utility/CharacterSet.h"

#include "SipRegister.h"


//--------------------

Directory::Directory(CSipMgr* pServer)
{
	if (pServer != NULL)
	{
		pServer->Register(MESSAGE/*SUBSCRIBE*/, CATALOG, &(Directory::DirectoryQuery), this);
		pServer->Register(SUBSCRIBE, CATALOG, &Directory::CatelogSubscribeCB, this);
	}
}

Directory::~Directory(void)
{
}


void Directory::DirectoryQuery(SipMessage& msg, int& iresult, void* context)
{
	iresult = SIP_SUCCESS;

	AnswerArgs arg;
	strcpy(arg.sourceIp, msg.from_ip());
	strcpy(arg.usr, msg.from_user());
	arg.sourcePort = msg.from_port();
	strcpy(arg.request, msg.sipMessageBody());

	GLOBJ(gThreadPool)->runInThread(new AsynQuery<AnswerArgs>(&arg, &Directory::RpcQueryDir));
	msg.emptyMsgBody();
}


bool hasChild(int type)
{
	if (type == view_video || type == view_district || type == view_site
		|| type == view_nvr || type == view_dvs || type == view_dvr || type == view_encoder)
	{
		return true;
	}

	return false;
}


void Directory::RpcQueryDir(AnswerArgs* args)
{
	assert(args != NULL);
	int nret = 0;

	int buflen = 1024*512;
	const char* via = "0";
	char* dirBuf = new char[buflen];
	memset(dirBuf, 0, buflen);
	int realSize = 0;

	int devId;
	int queryType;
	
	//单独推送行政域根节点
	pushRootDomain(atoi(args->sn), args->usr, args->sourceIp, args->sourcePort);

	//推送本级中心及分控中心区域
	getSubCenterDir(atoi(args->sn), args->usr, args->sourceIp, args->sourcePort);

#if 0
	//推送区域节点，父节点是市
    DirCatalog dis;
    dis.SubNum = 0;
	dis.parentID = 11;
	dis.type = view_root;


	//query to server
	queryType = view_video;
	devId = 0;
	nret = GLOBJ(gAdaptor)->deviceQuery(queryType, devId, via, dirBuf, buflen, &realSize);
	if (nret != 0)
	{
		return ;
	}
	ParseXmlRpcDir(dirBuf, realSize, dis);
	dis.type = view_root;
	pushDevDirectory(dis, atoi(args->sn), args->usr, args->sourceIp, args->sourcePort);

	//
	recurvePushDir(dis, atoi(args->sn), args->usr, args->sourceIp, args->sourcePort);
#endif

#if 0

	do 
	{

		GBDevControlReq::DevControl dirReq;
		GBDevControlReq::DirQueryParse(args->request, &dirReq);
		//如果deviceId是本级中心，则返回bc根节点所有区域,view_video
		if (dirReq.devId.compare(GLOBJ(gConfig)->getSiplocalUser()) == 0)
		{
			devId = 0;
			queryType = view_video;
		}
		else
		{
			GBSysCode::getDevTypeAndId(dirReq.devId.c_str(), &queryType, &devId);
			int bstype = 0;
			exchangeType(&bstype, &queryType);
			queryType = bstype;
		}

#if 1
		//query to server
		nret = GLOBJ(gAdaptor)->deviceQuery(queryType, devId, via, dirBuf, buflen, &realSize);
		if (nret != 0)
		{
			break ;
		}
#else
		nret = GLOBJ(gAdaptor)->devTypedQuery(queryType, dirBuf, &buflen);
		if (nret != 0)
		{
			break ;
		}
#endif

		//construct MANSCP XML
		DirCatalog dirList;
		dirList.SubNum = 0;
		strcpy(dirList.parentId, dirReq.devId.c_str());
		ParseXmlRpcDir(dirBuf, realSize, dirList);


		//将目录分为合理的区块，推送出去
		pushDevDirectory(dirList);

		//test record info
		//memset(dirBuf, 0, buflen);
		//constructRecordFile(dirReq.m_sn, dirBuf, buflen);
		//nret = SendSipDirMsg(dirBuf, args->usr, args->sourceIp, args->sourcePort);

	} while (0);
#endif

	delete []dirBuf;
	dirBuf = NULL;

}


void Directory::pushRootDomain(int sn, const char* usr, const char* ip, const int port)
{
	//首先推送市
	DirCatalog city;
	city.SubNum = 1;
	city.type = view_null;
	city.parentCode = GLOBJ(gConfig)->getSiplocalUser();

	DirectoryNodeInfo nodeInfo;
	std::string name = GLOBJ(gConfig)->getLocalDomainName();
	strcpy_s(nodeInfo.Name, sizeof(nodeInfo.Name), name.c_str());

	nodeInfo.Parental = 1;
	strcpy_s(nodeInfo.ParentID, sizeof(nodeInfo.ParentID), city.parentCode.c_str());

	std::string orga = GLOBJ(gConfig)->getSiplocalUser();
	orga = orga.substr(0, 4);
	strcpy_s(nodeInfo.CivilCode, sizeof(nodeInfo.CivilCode), orga.c_str());

	//Format fm;
	strcpy_s(nodeInfo.DeviceID, sizeof(nodeInfo.DeviceID), orga.c_str());

	nodeInfo.type = view_root;

	city.Sub.push_back(nodeInfo);
	pushDevDirectory(city, sn, usr, ip, port);
}


void Directory::recurvePushDir(DirCatalog& dir, int sn, const char* usr, const char* ip, const int port)
{
	char* dirBuf;
	const int buflen = 32*1024;
	dirBuf = new char[buflen];

	int queryType;
	int nret = 0;
	int realSize = 0;

	DirIter iter;
	Format fm;
	for (iter = dir.Sub.begin() ; iter != dir.Sub.end(); iter++)
	{
		if (hasChild(iter->type))
		{
			queryType = iter->type;
			std::string devId = iter->DeviceID;
			devId = devId.substr(devId.length() - 6, 6);
			int id = atoi(devId.c_str());

			std::string via = dir.via;

			memset(dirBuf, 0, buflen);
			nret = GLOBJ(gAdaptor)->deviceQuery(queryType, id, via.c_str(), dirBuf, buflen, &realSize);
			if (nret != 0)
			{
				break ;
			}

			DirCatalog dirList;
			dirList.parentCode = iter->DeviceID;
			dirList.via = via;
			ParseXmlRpcDir(dirBuf, realSize, dirList);
			pushDevDirectory(dirList, sn, usr, ip, port);
			recurvePushDir(dirList, sn, usr, ip, port);
		}
		else
		{
			break;
		}
	}

	delete []dirBuf;
	dirBuf = NULL;
}

void Directory::pushDevDirectory(DirCatalog& dirList, int sn, const char* usr, const char* ip, const int port)
{
		//将目录分为合理的区块，推送出去
		const int csDivideCount =2;
		int begin = 0;
		int nret = 0;

		char* dirBuf;
		const int buflen = 32*1024;
        dirBuf = new char[buflen];
		//只发送一次
		while (begin < dirList.SubNum)
		{
			memset(dirBuf, 0, buflen);
			int count = (dirList.SubNum - begin) < csDivideCount ? (dirList.SubNum - begin) : csDivideCount; 
			constructMANSCDPXml(dirList, sn, begin, count, dirBuf, (int*)&buflen);
			//DevListNotify(dirList, dirReq.m_sn, begin, count, dirBuf, (int*)&buflen);
			begin += csDivideCount;

			nret = SendSipDirMsg(dirBuf, usr, ip, port);
			if (nret != 0)
			{
				_LOG(LOG_LEVEL_DEBUG, "推送目录失败");
				break;
			}
		}

		delete []dirBuf;
		dirBuf = NULL;
}


void Directory::constructMANSCDPXml(DirCatalog& dirSet, int SN, int begin, int count, char* sendData, int* len)
{
	//tiny xml---construct a xml document
	XmlParser parse;
	char tempStr[32] = {0};
	TiXmlElement* itemNode = NULL;

	TiXmlElement* rootNode = parse.AddRootNode("Response");
	parse.InsertSubNode(rootNode, "CmdType", "Catalog");
	sprintf(tempStr, "%d", SN);
	parse.InsertSubNode(rootNode, "SN", tempStr);

	parse.InsertSubNode(rootNode, "DeviceID", dirSet.parentCode.c_str());

	char textValue[32] = {0};
	sprintf_s(textValue, sizeof(textValue),"%d", dirSet.SubNum);
	parse.InsertSubNode(rootNode, "SumNum", textValue);

	itemNode = parse.InsertSubNode(rootNode, "DeviceList", "");
	memset(tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%d", count);
	parse.SetNodeAttributes(itemNode, "Num",tempStr);

	DirIter iter;
	int index = 0;
	int itemcount = 0;
	Format fm;
	for (iter = dirSet.Sub.begin() ; iter != dirSet.Sub.end(); iter++)
	{
		if (index < begin)
		{
			index++;
			continue;
		}

		//左闭右开
		if (itemcount >= count)
		{
			break;
		}
		itemcount++;


		TiXmlElement* node = parse.InsertSubNode(itemNode, "Item", "");

		parse.InsertSubNode(node, "Name", iter->Name);
		parse.InsertSubNode(node, "DeviceID", iter->DeviceID);

		parse.InsertSubNode(node, "Manufacturer", iter->Manufacturer);
		parse.InsertSubNode(node, "Model", iter->Model);
		parse.InsertSubNode(node, "Owner", iter->Owner);
		parse.InsertSubNode(node, "CivilCode", iter->CivilCode);
		parse.InsertSubNode(node, "Block", iter->Block);
		parse.InsertSubNode(node, "Address", iter->Address);
		fm.clear();
		parse.InsertSubNode(node, "Parental", (fm<<iter->Parental).data());
		parse.InsertSubNode(node, "ParentID", iter->ParentID);
		fm.clear();
		parse.InsertSubNode(node, "SafetyWay", (fm<<iter->SafetyWay).data());
		fm.clear();
		parse.InsertSubNode(node, "RegisterWay", (fm<<iter->RegisterWay).data());
		fm.clear();
		parse.InsertSubNode(node, "Secrecy", (fm<<iter->Secrecy).data());
		parse.InsertSubNode(node, "Status", iter->Status);

	}

	//获取xml串
	parse.SetXmlTile(XMLTITLE);
	parse.getWholeXml(sendData, BODY_SIZE, len);

}


//
void Directory::getSubCenterDir(int sn, const char* usr, const char* ip, const int port)
{
	int nret = 0;
	int buflen = 1024*512;
	const char* via = "0";
	char* dirBuf = new char[buflen];
	memset(dirBuf, 0, buflen);
	int realSize = 0;

	int devId;
	int queryType;

	//获取分控及本级中心节点
	queryType = view_root;
	devId = 0;
	nret = GLOBJ(gAdaptor)->deviceQuery(queryType, devId, via, dirBuf, buflen, &realSize);
	if (nret != 0)
	{
		return ;
	}
	
	XmlRpcValue result;
	int offset = 0;
	result.fromXml(dirBuf, &offset);

	int iCount = result["count"];
	for (int i = 0; i < iCount; i++)
	{
		std::string via = result["rows"][i]["via"].toString();
		std::string name = result["rows"][i]["name"].toString();

		//获取本级和分控中心所有区域
		memset(dirBuf, 0, buflen);
		realSize = 0;
		queryType = view_video;
		devId = 0;
		nret = GLOBJ(gAdaptor)->deviceQuery(queryType, devId, via.c_str(), dirBuf, buflen, &realSize);
		if (nret != 0)
		{
			continue ;
		}

		DirCatalog dis;
		ParseXmlRpcDir(dirBuf, realSize, dis);
		//dis.type = view_root;
    pushDevDirectory(dis, sn, usr, ip, port);

		if (!dis.Sub.empty())
			recurvePushDir(dis, sn, usr, ip, port);
	}



}


void Directory::DevListNotify(DirCatalog& dirSet, int SN, int begin, int count, char* sendData, int* len)
{
	//tiny xml---construct a xml document
	XmlParser parse;
	char tempStr[32] = {0};
	TiXmlElement* itemNode = NULL;

	TiXmlElement* rootNode = parse.AddRootNode("Notify");
	parse.InsertSubNode(rootNode, "CmdType", "Catalog");
	sprintf(tempStr, "%d", SN);
	parse.InsertSubNode(rootNode, "SN", tempStr);
	//parse.InsertSubNode(rootNode, "DeviceID", dirSet.parentID);

	char textValue[32] = {0};
	sprintf_s(textValue, sizeof(textValue),"%d", dirSet.SubNum);
	parse.InsertSubNode(rootNode, "SumNum", textValue);

	itemNode = parse.InsertSubNode(rootNode, "DeviceList", "");
	memset(tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%d", count);
	parse.SetNodeAttributes(itemNode, "Num",tempStr);

	DirIter iter;
	int index = 0;
	int itemcount = 0;
	Format fm;
	for (iter = dirSet.Sub.begin() ; iter != dirSet.Sub.end(); iter++)
	{
		if (index < begin)
		{
			index++;
			continue;
		}

		//左闭右开
		if (itemcount >= count)
		{
			break;
		}
		itemcount++;


		TiXmlElement* node = parse.InsertSubNode(itemNode, "Item", "");
		parse.InsertSubNode(node, "DeviceID", iter->DeviceID);
		parse.InsertSubNode(node, "Event", "ON");

	}

	//获取xml串
	parse.SetXmlTile(XMLTITLE);
	parse.getWholeXml(sendData, BODY_SIZE, len);
}



void Directory::ParseXmlRpcDir(const char* xmlRpcDir, int reqLen, DirCatalog& dirList)
{

#if 1
	XmlRpcValue result;
	int offset = 0;
	result.fromXml(xmlRpcDir, &offset);

	int iCount = result["count"];
	//dirList.SubNum = iCount;

	int i = 0;
	for (;i < iCount; i++)
	{
		DirectoryNodeInfo nodeInfo;
		std::string name = result["rows"][i]["name"].toString();
		strcpy_s(nodeInfo.Name, sizeof(nodeInfo.Name), name.c_str());
		nodeInfo.Parental = 1;
		nodeInfo.type = (int)result["rows"][i]["subtype"];

		std::string code = result["rows"][i]["code"].toString();
		if (code.size() < 6 && nodeInfo.type == view_district)
		{
			continue;
		}

		//所有区域以下节点的行政编码=区域编码(前6位)
		std::string orga;
		if (nodeInfo.type == view_district)
		{
			orga = code;
		}
		else
		{
			orga = dirList.parentCode;
		}
		//统一10位编码
		if (orga.length() < 10)
		{
			int va = 10 - orga.length();
			for (int i = 0; i < va; i++)
			{
				orga += "0";
			}
		}
		std::string civilCode = orga.substr(0, 8);
		strcpy_s(nodeInfo.CivilCode, sizeof(nodeInfo.CivilCode), civilCode.c_str());

		//id
		int id = (int)result["rows"][i]["id"];
		std::string devCode = GBSysCode::gb28181Code(orga, nodeInfo.type, id);
		strcpy_s(nodeInfo.DeviceID, sizeof(nodeInfo.DeviceID), devCode.c_str());

		//parentID
		int paId = result["rows"][i]["dockId"];
		int patype = (int)result["parentType"];
		std::string parentId = GBSysCode::gb28181Code(orga, patype, paId);
		strcpy_s(nodeInfo.ParentID, sizeof(nodeInfo.ParentID), parentId.c_str());

		dirList.parentCode = nodeInfo.ParentID;
		dirList.via = result["rows"][i]["via"];

		dirList.Sub.push_back(nodeInfo);
	}
	dirList.SubNum = i;
#else
	XmlParser xml;
	int ret = xml.ParseDocumentXml((char*)xmlRpcDir);
	if (ret != 0)
	{
		return ;
	}

	TiXmlElement* root = xml.GetRootNode();
	std::string value;
	value = (char*)root->Value();

	TiXmlElement* nvrNode = NULL;
	TiXmlElement* cameraNode = NULL;
	const std::string stype = "nvr";
	nvrNode = xml.GetSubNode(root, stype.c_str());
	if (nvrNode == NULL)
	{
		return ;
	}

	const char* business = "00";
	//dirList.SubNum = 0;
	//获取所有NVR设备
	while (nvrNode != NULL)
	{ 
		std::string name;
		TiXmlElement* nameNode = xml.GetSubNode(nvrNode, "name");
		xml.ParseNode(nameNode, name);
		CCharacterSet::UTF_8ToGB2312(name, name.c_str(), name.length());

		TiXmlElement* idNode = xml.GetSubNode(nvrNode, "id");
		std::string cid ;
		xml.ParseNode(idNode, cid);
		int id = atoi(cid.c_str());

		DirectoryNodeInfo nodeInfo;

		strcpy_s(nodeInfo.Name, sizeof(nodeInfo.Name), name.c_str());
		strcpy_s(nodeInfo.ParentID, sizeof(nodeInfo.ParentID), dirList.DeviceID);
		int devType = view_nvr;
		int gbType = 0;
		exchangeType(&devType, &gbType);

		std::string code;
		std::string orga = GLOBJ(gConfig)->getSiplocalUser();
		orga = orga.substr(0, 8);

		Format fm;
		char idStr[8] = {0};
		//hik 平台对接
		sprintf(idStr, "25%05d", id);
		GBSysCode::constructSysCode(code, orga.c_str(), business, (fm<<gbType).data(), idStr);
		strcpy_s(nodeInfo.DeviceID, sizeof(nodeInfo.DeviceID), code.c_str());
		strcpy_s(nodeInfo.CivilCode, sizeof(nodeInfo.CivilCode), orga.c_str());

		dirList.Sub.push_back(nodeInfo);

		//获取NVR下所有摄像头
		cameraNode = xml.GetSubNode(nvrNode, "camera");
		while (cameraNode != NULL)
		{
			std::string name;
			TiXmlElement* nameNode = xml.GetSubNode(cameraNode, "name");
			xml.ParseNode(nameNode, name);
			CCharacterSet::UTF_8ToGB2312(name, name.c_str(), name.length());

			TiXmlElement* idNode = xml.GetSubNode(cameraNode, "id");
			std::string cid ;
			xml.ParseNode(idNode, cid);
			int id = atoi(cid.c_str());

			DirectoryNodeInfo nodeInfo;
			nodeInfo.Parental = 1;
			strcpy_s(nodeInfo.Name, sizeof(nodeInfo.Name), name.c_str());
			strcpy_s(nodeInfo.ParentID, sizeof(nodeInfo.ParentID), code.c_str());
			int devType = view_camera;
			int gbType = 0;
			exchangeType(&devType, &gbType);

			std::string code;
			std::string orga = GLOBJ(gConfig)->getSiplocalUser();
			orga = orga.substr(0, 8);

			Format fm;
			char idStr[32] = {0};
			//hik 平台对接
			sprintf(idStr, "25%05d", id);
			GBSysCode::constructSysCode(code, orga.c_str(), business, (fm<<gbType).data(), idStr);
			strcpy_s(nodeInfo.DeviceID, sizeof(nodeInfo.DeviceID), code.c_str());
			strcpy_s(nodeInfo.CivilCode, sizeof(nodeInfo.CivilCode), orga.c_str());

			dirList.Sub.push_back(nodeInfo);

			cameraNode = xml.GetNextSiblingNode(cameraNode, "camera");
			dirList.SubNum++;
		}


		nvrNode = xml.GetNextSiblingNode(nvrNode, stype.c_str());
		dirList.SubNum++;
	}

#endif

}


int Directory::SendSipDirMsg(const char* sipBody, const char* touser, const char* toip, int toport)
{
	SipMessage msg;
	msg.setFrom(GLOBJ(gConfig)->getSiplocalUser(), GLOBJ(gConfig)->getSiplocalIp(), GLOBJ(gConfig)->getSiplocalPort());
	msg.setTo((char*)touser, (char*)toip, toport);
	msg.setUri((char*)toip, toport);
	std::string contentType = "Application/MANSCDP+xml";
	msg.setContentType((char*)contentType.c_str(), contentType.length());

	msg.setSipMessageBody(sipBody, strlen(sipBody));

	int ret = 0;
	ret = CSipMgr::doSipRequest(/*NOTIFY*/MESSAGE, msg);
	if (ret == SIP_OK)
	{
		if (msg.status_code() == SIP_SUCCESS)
		{
			_LOG(LOG_LEVEL_DEBUG, "设备目录推送成功");
		}
		else
		{
			//重发处理
			//ret = directoryReSend(msgBody, len);
		}
	}
	else
	{
		_LOG(LOG_LEVEL_DEBUG, "设备目录推送失败");
		//directoryReSend(msgBody, len);
	}

	return 0;
}


//for test
void Directory::constructRecordFile(int SN, char* buf, int len)
{
	XmlParser parse;
	char tempStr[32] = {0};
	TiXmlElement* itemNode = NULL;

	parse.AddRootNode("Response");
	parse.InsertSubNode("Response", "CmdType", "RecordInfo");
	sprintf(tempStr, "%d", SN);
	parse.InsertSubNode("Response", "SN", tempStr);
	parse.InsertSubNode("Response", "DeviceID", "35010500001312500031");
	parse.InsertSubNode("Response", "Name", "Camera1");

	char textValue[32] = {0};
	sprintf_s(textValue, sizeof(textValue),"%d", 1);
	parse.InsertSubNode("Response", "SumNum", textValue);

	itemNode = parse.InsertSubNode("Response", "RecordList", "");
	memset(tempStr, 0, sizeof(tempStr));
	sprintf(tempStr, "%d", 1);
	parse.SetNodeAttributes(itemNode, "Num",tempStr);


	TiXmlElement* node = parse.InsertSubNode(itemNode, "Item", "");

	parse.InsertSubNode(node, "Name", "Camera1");
	parse.InsertSubNode(node, "DeviceID", "35010500001312500031");
	parse.InsertSubNode(node, "FilePath", "/record/record1-20150716");
	parse.InsertSubNode(node, "Address", "Address1");
	parse.InsertSubNode(node, "StartTime", "2015-01-01T10:10:10");
	parse.InsertSubNode(node, "EndTime", "2015-12-01T10:10:10");
	parse.InsertSubNode(node, "Secrecy", "0");
	parse.InsertSubNode(node, "Type", "time");
	parse.InsertSubNode(node, "RecorderID", "35010002552459000001");


	//获取xml串
	parse.SetXmlTile(XMLTITLE);
	parse.getWholeXml(buf, BODY_SIZE, &len);
}


void Directory::autoDirNotify()
{
	while (!SipRegister::g_bRegisted)
	{
		Sleep(500);
	}

	SipMessage msg;
	msg.setFrom(GLOBJ(gConfig)->getSipremoteUser(), GLOBJ(gConfig)->getSipremoteIp(), GLOBJ(gConfig)->getSipremotePort());
	msg.setTo((char*)GLOBJ(gConfig)->getSiplocalUser(), (char*)GLOBJ(gConfig)->getSiplocalIp(), GLOBJ(gConfig)->getSiplocalPort());
	msg.setUri((char*)GLOBJ(gConfig)->getSiplocalIp(), GLOBJ(gConfig)->getSiplocalPort());
	std::string contentType = "Application/MANSCDP+xml";
	msg.setContentType((char*)contentType.c_str(), contentType.length());

	int nerr = 0;
	static int g_SNIndex = 600;
	char buf[32] = {0};
	sprintf(buf, "%d", g_SNIndex);

	void* context = NULL;
	std::string dir = "<?xml version=\"1.0\"?>";
		dir +=  "<Query>\r\n";
		dir += "<CmdType>Catalog</CmdType>\r\n";
		dir += "<SN>";
		dir += buf;
		dir += "</SN>\r\n";
		dir += "<DeviceID>";
		dir += GLOBJ(gConfig)->getSiplocalUser();
		dir += "</DeviceID> \r\n";
		dir += "</Query>";
	msg.setSipMessageBody(dir.c_str(), dir.length());
	Directory::DirectoryQuery(msg, nerr, context);

    g_SNIndex++;

	return ;

	//-------------------------------------------------------

	int nret = 0;

	const int buflen = 1024*64;
	const char* via = "0";
	char* dirBuf = new char[buflen];
	memset(dirBuf, 0, buflen);
	int realSize = 0;

	int devId;
	int queryType;


	devId = 0;
	queryType = view_video;
	nret = GLOBJ(gAdaptor)->deviceQuery(queryType, devId, via, dirBuf, buflen, &realSize);
	if (nret != 0)
	{

	}

	memset(dirBuf, 0, buflen);
	devId = 1;
	queryType = view_district;
	nret = GLOBJ(gAdaptor)->deviceQuery(queryType, devId, via, dirBuf, buflen, &realSize);
	if (nret != 0)
	{

	}


	delete[] dirBuf;
	dirBuf = NULL;

}


//目录订阅
void Directory::CatelogSubscribeCB(SipMessage& msg, int& iresult, void* appData)
{
	iresult = SIP_SUCCESS;

	//取消订阅
	if (msg.expires() <= 0)
	{
		//m_subsc.erase(msg.from_user());
		msg.emptyMsgBody();
		return ;
	}

	msg.emptyMsgBody();

}