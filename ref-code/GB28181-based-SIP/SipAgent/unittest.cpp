#include "StdAfx.h"

#include <process.h>
#include "unittest.h"
#include "GlobalCtrl.h"
#include "BcAdaptor/adaptorCommon.h"
#include "AgentServer/BcAdaptor.h"
#include "AgentServer/Directory.h"


#include "log4z.h"

#include "Utility/Format.h"

unittest::unittest(void)
{
}

unittest::~unittest(void)
{
}


void unittest::start()
{
	unsigned int threadId = 0;
	_beginthreadex(NULL, 0, &unittest::testProc, this, 0, &threadId);
}


unsigned int __stdcall unittest::testProc(void* context)
{
	Sleep(100);

	unittest* pthis = (unittest*)context;
	if (pthis == NULL)
	{
		return -1;
	}

	format_unitest();

	//device directory
	pthis->adaptor_QueryDir();


	return 0;
}


void unittest::adaptor_QueryDir()
{

    SipMessage msg;
	int nerr = 0;
	void* context = NULL;
	std::string dir = "<?xml version=\"1.0\"?>"
		 "<Query>"
		"<CmdType>Catalog</CmdType>"
		"<SN>248</SN>"
		"<DeviceID>35010002552459000001</DeviceID>"
		"</Query>";
	msg.setSipMessageBody(dir.c_str(), dir.length());
	Directory::DirectoryQuery(msg, nerr, context);


	return ;

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