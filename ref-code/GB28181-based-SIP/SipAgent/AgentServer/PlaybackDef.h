#ifndef _PLAYBACKDEF_H
#define _PLAYBACKDEF_H

#include <list>


// file type定义在DB33-3-A.1
// 0表示全部类型, 1表示定时录像, 2表示移动侦测录像, 3表示报警录像, 4表示手动录像, 5-9备用
enum PlaybackFileType
{
	recordtype_all = 0,
	recordtype_time = 1,
	recordtype_move = 2,
	recordtype_alarm = 3,
	recordtype_manual = 4,
  //5-9 extend
};

//回放的设备信息
typedef struct 
{
	int deviceId;
	int nChannel;
	int disk;
	char vendor[32];
	int filetype;
	char devAddr[32];
	char proxyAddr[32];
	int cmdPort;
	int dataPort;
	int devCmdPort;
	char devUsr[32];
	char devPassword[32];
}DeviceInfo;


//统一回放文件属性
typedef struct tagPLAYBACK_RECORDFILE_INFO
{
	unsigned int ch; //通道号
	char filename[256]; //文件名
	unsigned int size; //文件大小
	__int64 starttime;  //文件起始时间
	__int64 endtime;    //文件结束时间
	unsigned char nfiletype;  //文件类型
	unsigned char ncluster;   //磁盘

	tagPLAYBACK_RECORDFILE_INFO& operator=(const tagPLAYBACK_RECORDFILE_INFO& info)
	{
		if (&info == this)
		{
			return *this;
		}
		ch = info.ch;
		size = info.size;
		starttime = info.starttime;
		endtime = info.endtime;
		nfiletype = info.nfiletype;
		ncluster = info.ncluster;
		strcpy_s(filename, sizeof(filename), info.filename);

		return *this;
	}

}PLAYBACK_RECORDFILE_INFO, *LPPLAYBACK_RECORDFILE_INFO;


//文件列表
struct playback_filelist
{
	unsigned int num; //文件总数目
	std::list<PLAYBACK_RECORDFILE_INFO> filelist;

};


//回放历史文件检索结构体
struct DevFileSearchInfo
{
	int deviceId;  //设备地址
	char privilege[8];//权限功能码
	int fileType; //文件类型
	int fromIndex; //起始索引
	int toIndex;//终止索引
	__int64 beginTm; //起始时间
	__int64 endTm;  //终止时间
};

struct FileVodUrlRequestInfo
{
	char privilege[8];//权限功能码

};

#endif