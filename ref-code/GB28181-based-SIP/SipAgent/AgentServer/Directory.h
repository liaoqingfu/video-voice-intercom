#pragma once

#include "SipMgr.h"
#include "../GlobalCtrl.h"
#include "SipHandleBase.h"
#include "GBStandard.h"
#include "BcAdaptor/adaptorCommon.h"

#include <list>

struct AnswerArgs;

//目录请求处理


//目录信息结构体
struct DirectoryNodeInfo
{
	int type;         //设备类型
	char DeviceID[32];     //id
	char Name[64];        //名字
	char Manufacturer[32]; //设备厂商
	char Model[16];       //设备型号
	char Owner[16];       //设备归属
	char CivilCode[16];   //行政区域
	char Block[16];       //警区--可选
	char Address[16];     //安装地址
	int Parental;         //是否有子设备
	char ParentID[32];    //父设备ID
	int SafetyWay;        //信令安全模式--可选
	int RegisterWay;      //注册方式1： 2： 3：
	char CertNum[16];     //证书序列号--可选
	int Certifiable;      //证书有效标示--可选
	int ErrCode;          //证书无效原因码--可选
	char EndTime[16];     //证书终止有效期--可选
	int Secrecy;          //保密属性
	char IPAddress[24];   //设备系统ip地址--可选
	int Port;             //端口--可选
	char Password[32];    //设备口令--可选
	char Status[4];           //设备状态
	double Longitude;     //经纬度--可选
	double Latitude;      //经纬度--可选


	DirectoryNodeInfo()
	{
		memset(DeviceID, 0, sizeof(DeviceID));
		memset(Name, 0, sizeof(Name));
		strcpy_s(Manufacturer, sizeof(Manufacturer), "BlueSky");
		strcpy_s(Model, sizeof(Model), "bc2.6.x");
		
		strcpy_s(Owner, sizeof(Owner), "BlueSky");
		memset(CivilCode, 0, sizeof(CivilCode));
		strcpy_s(Block, sizeof(Block), "alarm1");
		strcpy_s(Address, sizeof(Address), "bcenter");
		Parental = 1;
		memset(ParentID, 0, sizeof(ParentID));
		SafetyWay = 0;
		RegisterWay = 1;
		Secrecy = 0;
		strcpy(Status, "ON");

	}

	const DirectoryNodeInfo& operator=(const DirectoryNodeInfo& node)
	{
		if (this == &node)
		{
			return *this;
		}

		strcpy_s(DeviceID, sizeof(DeviceID), node.DeviceID);
		strcpy_s(Name, sizeof(Name), node.Name);
		strcpy_s(Manufacturer, sizeof(Manufacturer), node.Manufacturer);
		strcpy_s(Model, sizeof(Model), node.Model);
		strcpy_s(Owner, sizeof(Owner), node.Owner);
		strcpy_s(CivilCode, sizeof(CivilCode), node.CivilCode);
		strcpy_s(Block, sizeof(Block), node.Block);
		strcpy_s(Address, sizeof(Address), node.Address);

		Parental = node.Parental;
		strcpy_s(ParentID, sizeof(ParentID), node.ParentID);
		SafetyWay = node.SafetyWay;
		RegisterWay = node.RegisterWay;
		Secrecy = node.Secrecy;
		strcpy_s(Status, sizeof(Status), node.Status);

		return *this;
	}

};

//ddcp协议关于目录推送结构描述
struct DirCatalog
{
	std::string via;
	std::string parentCode;
	int type;
	int  SubNum;
	std::list<DirectoryNodeInfo> Sub;//[MAX_NODE_NUM];

	DirCatalog()
	{
		via = "0";
		SubNum = 0;
		type = 0;
		parentCode = "130202";
	}
	~DirCatalog()
	{
		Sub.clear();
	}

	void clear()
	{
		via = "0";
		type = 0;
		SubNum  = 0;
		Sub.clear();
		parentCode.clear();
	}
};

typedef std::list<DirectoryNodeInfo>::iterator DirIter;


//--------------------------------


class Directory : SipHandleBase
{
public:
	Directory(CSipMgr* pServer);
	~Directory(void);

public:
	static void DirectoryQuery(SipMessage& msg, int& iresult, void* context);

		//目录订阅
	static void CatelogSubscribeCB(SipMessage& msg, int& iresult, void* appData);

	static void RpcQueryDir(AnswerArgs* args);
private:
	static void pushRootDomain(int sn, const char* usr, const char* ip, const int port);
	static int SendSipDirMsg(const char* sipBody, const char* touser, const char* toip, int toport);
	static void ParseXmlRpcDir(const char* xmlRpcDir, int reqLen, DirCatalog& dirList);
	static void pushDevDirectory(DirCatalog& dir, int sn, const char* usr, const char* ip, const int port);
	static void recurvePushDir(DirCatalog& dir, int sn, const char* usr, const char* ip, const int port);

	//处理分控中心的目录
	static void getSubCenterDir(int sn, const char* usr, const char* ip, const int port);

	static void constructMANSCDPXml(DirCatalog& dirSet, int SN, int begin, int count, char* sendData, int* len);
	static void DevListNotify(DirCatalog& dirSet, int SN, int begin, int count, char* sendData, int* len);

public:
	//
	void autoDirNotify();

public:
	//test record file
	static void constructRecordFile(int SN, char* buf, int len);
};
