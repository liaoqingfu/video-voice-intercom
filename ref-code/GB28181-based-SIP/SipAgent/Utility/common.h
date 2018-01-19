#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>

#include <string>
#include <list>
using namespace std;


typedef union _ularge_int
{
	struct 
	{
		unsigned long wlowint;
		unsigned long whighint;
	};
	__int64 quadpart;

}ularge_int;



//common 
#define RET_IF_NULL(p, n) if (p == NULL) return n; 

#define SAFE_DEL(p) if (p != NULL) delete p;\
	                                 p = NULL;

#define VERIFY(exp) if (exp == -1) return -1;

//function
//18位对象地址编码
struct AddrCode
{
	unsigned long province;
	unsigned long city;
	unsigned long county;
	unsigned long town;
	char  deviceCode[32];
	char  objCode[8];
	char  accessCode[4];  //接入类型
	int   parentType;     //父节点类型
};

//static function

//组织成ddcp描述的18位地址编码
void ConstructAddrCode(AddrCode& code, std::string& addr);

//根据设备id（6位）和父节点类型，组合出一个6个长度的字符串
void CombineAddress(std::string addr, int parentType, std::string& outPutAddr); 

unsigned long getTickCount(void);

//从18位地址编码获得deviceId
int FromDeviceAddrToDevId(const char* address);


/*
时间字符串转换time_t
 时间字符串形如：2005-11-10T13:20:50
*/
time_t StrTimeToTime_t(const char* strTime);
void Time_tToStrTime(time_t t, std::string& strTime);


//
#if 0
SYSTEMTIME Time_tToSystemTime(time_t t);
time_t SystemTimeToTime_t(SYSTEMTIME& sysTm);
__int64 SystemTimeToTime_t2(SYSTEMTIME& sysTm);
#endif


//切割字符串
int SegString(string strInput, std::list<string>& strList, string sep);

#endif