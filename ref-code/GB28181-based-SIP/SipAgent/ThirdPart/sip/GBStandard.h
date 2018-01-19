#pragma once

/*
  遵循GB28181标准，详见
	GB T 28181--2011安全防范视频监控联网系统 信息传输、交换、控制技术要求.pdf
*/

#include"..\tinyxml\tinyxml.h"

#include <string>

class CGBStandard
{
public:
	CGBStandard(void);
	~CGBStandard(void);

public:
	static TiXmlElement* NodeFind(char* value, TiXmlElement* node);
	static void GBParseAppCmdTypeStr(const char* msg, std::string& strCmd);

	static void GBParseSdpCmdTypeStr(const char* msg, std::string& strCmd);
	static void GBParseMansRtspCmdTypeStr(const char* msg, std::string& strCmd);
};



void exchangeType(int* bsType, int* gbType);

//
//编码规则：系统编码=中心编码+行业编码+类型编码+序号
//中心编码8位：34000001
//行业编码2位：00
//类型编码3位：118
//序号编码7位：0000001

//类型编码枚举
enum DevTypeCode
{
	Dvr_Code = 111, //DVR
	VideoServer_Code = 112, //视频服务器
	Encoder_Code = 113, //encoder
	Decoder_Code = 114, //decoder
	AlarmDev_Code = 117, //报警主机
	NVR_Code = 118, //nvr

	Camera_Code = 131, //camera
	Ipc_Code = 132, //ipc
	VGA_Code = 133, //vga
	AlarmInput_Code = 134, //alarm input
	AlarmOutput_Code = 135, //alarm output

	CenterServer_Code = 200, //中心信令控制服务器编码
	//
	District_Code = 202,
	Site_Code = 203
};



namespace GBSysCode
{
	void constructSysCode(std::string& code, const char* orga, const char* business, const char* type, const char* id);
	void getDevTypeAndId(const char* code, int* type, int* id);

	std::string gb28181Code(std::string& civilcode, int nodeType, int nodeId);
}



//GB28181 
//device control cmd request parse
namespace GBDevControlReq
{
  //information
	struct DevControl
	{
		std::string devId;
		int m_sn;
		std::string m_controlCmd;
		std::string m_controlType;
	};

	int DirQueryParse(const char* req, DevControl* ctrl);


}

//GB28181 
//device control cmd responce parse
class GBDevControlResp
{

};