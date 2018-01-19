#include "common.h"

//#include "..\directory\DirectoryDef.h"


#define ASC2_BASE_VALUE 32


void ConstructAddrCode(AddrCode& code, std::string& addr)
{
	char str[16] = {0};
	sprintf_s(str, 16, "%d", g_provinceAddr/*code.province*/);
	addr += str;

	memset(str, 0, 16);
	sprintf_s(str, 16, "%d", g_cityAddr/*code.city*/);
	addr += str;

	memset(str, 0, 16);
	sprintf_s(str, 16, "%d", g_countyAddr/*code.county*/);
	addr += str;

	memset(str, 0, 16);
	sprintf_s(str, 16, "%d", g_townAddr/*code.town*/);
	addr += str;

	addr += ACCESS_CODE/*code.accessCode*/;
	std::string tempStr;
	CombineAddress(code.deviceCode, code.parentType, tempStr);
	addr += tempStr;
	addr += code.objCode;

}

/**
 * @fn CombineAddress
 * @brief  这是一个算法
 *         把6位的地址码和父节点类型，组合成一个6位的字符串   
 * @param  addr
 * @param  parentType
 * @param  outPutAddr
 * @return
 * @retval  
 */
void CombineAddress(std::string addr, int parentType, std::string& outPutAddr)
{
	char first = addr[0];
	char temp[4] = {0};
	sprintf(temp, "%d%c", parentType, first);
	int num = atoi(temp);

	char asc2 = num + ASC2_BASE_VALUE;

	addr[0] = asc2;

	outPutAddr = addr;

}

unsigned long getTickCount(void)
{
	unsigned long curTime;

#ifdef WIN32
	curTime = GetTickCount();
#else
	struct timeval current;
	gettimeofday(&current, NULL);
	curTime = current.tv_sec * 1000 + current.tv_usec/1000;
#endif

	return curTime;
}

//
#if 0
SYSTEMTIME Time_tToSystemTime(time_t t)
{
	tm temptm = *localtime(&t);
	SYSTEMTIME st = {1900 + temptm.tm_year, 
		1 + temptm.tm_mon, 
		temptm.tm_wday, 
		temptm.tm_mday, 
		temptm.tm_hour, 
		temptm.tm_min, 
		temptm.tm_sec, 
		0};
	return st;
}

time_t SystemTimeToTime_t(SYSTEMTIME& sysTm)
{
	time_t rtm;

	FILETIME ft;
	SystemTimeToFileTime(&sysTm, &ft);

	__int64 ll;

	ularge_int ui;
	ui.wlowint = ft.dwLowDateTime;
	ui.whighint = ft.dwHighDateTime;

	ll = (ft.dwHighDateTime<<32) + ft.dwLowDateTime;
	rtm = ((__int64)(ui.quadpart - 116444736000000000) / 10000000);
	rtm -= 8 * 3600;

	return rtm;
}


__int64 SystemTimeToTime_t2(SYSTEMTIME& sysTm)
{
	struct tm gm = {sysTm.wSecond, sysTm.wMinute, sysTm.wHour, sysTm.wDay, sysTm.wMonth-1, sysTm.wYear-1900, sysTm.wDayOfWeek, 0, 0};
	__int64 rtm = mktime(&gm);
	//rtm -= 28800;
	//SYSTEMTIME tim = Time_tToSystemTime(rtm);

	return rtm;
}
#endif


/**
 * @fn FromDeviceAddrToDevId
 * @brief  从18位地址码中解析出6位设备ID
 *         
 * @param  address
 * @return
 * @retval  
 */
int FromDeviceAddrToDevId(const char* address)
{
	//取18位地址编码102030405011111104中间11-16位6位值
	std::string addr = address;
	int id;
	std::string subIdStr = addr.substr(10, 6).c_str();
	int num = subIdStr[0];
	num -= ASC2_BASE_VALUE;
	char strnum[4] = {0};
	itoa(num, strnum, 10);
	std::string str = strnum;
	subIdStr[0] = subIdStr[1];
	id = atoi(subIdStr.c_str());
	return id;
}




/*
时间字符串形如：20051110T132050Z
             2005.11.10 13:20:50
*/
time_t StrTimeToTime_t(const char* strTime)
{
	SYSTEMTIME sysTm;
	time_t retTime = 0;
	memset(&sysTm, 0, sizeof(sysTm));
	std::string ctm = strTime;

	sysTm.wYear = atoi(ctm.substr(0, 4).c_str());
	sysTm.wMonth = atoi(ctm.substr(5, 2).c_str());
	sysTm.wDay = atoi(ctm.substr(8, 2).c_str());
	sysTm.wHour = atoi(ctm.substr(12, 2).c_str());
	sysTm.wMinute = atoi(ctm.substr(14, 2).c_str());
	sysTm.wSecond = atoi(ctm.substr(17, 2).c_str());

	retTime = SystemTimeToTime_t(sysTm);

	return retTime;

}

//time_t到自定义时间字符串的转换  
//2005.11.10 13:20:50  ---> 20051110T132050Z
void Time_tToStrTime(time_t t, std::string& strTime)
{
	char ltm[64] = {0};
	SYSTEMTIME sysTm = Time_tToSystemTime(t);
	sprintf_s(ltm, sizeof(ltm), "%d-%02d-%02dT%02d:%02d:%02d", sysTm.wYear, 
		sysTm.wMonth, sysTm.wDay, sysTm.wHour, sysTm.wMinute, sysTm.wSecond);
	strTime = ltm;
	
}


int SegString(string strInput, std::list<string>& strList, string sep)
{
	char* szStr = _strdup(strInput.c_str());

	if (!szStr)
		return 0;

	char* pStart = szStr;
	char *token = NULL;
	char *next_token = NULL;

	token = strtok_s(szStr, sep.c_str(), &next_token);

	while( token != NULL )
	{
		int nLen = strlen(token);

		char* pWord = (char*)malloc((nLen+1)*sizeof(char));

		if (pWord)
		{
			strncpy_s(pWord, nLen+1, token, nLen);

			pWord[nLen] = 0;

			strList.push_back(pWord);
		}

		// Get next token: 
		token = strtok_s(NULL, sep.c_str(), &next_token);
	}

	free(szStr);

	int nSize = strList.size();

	return nSize;
}

