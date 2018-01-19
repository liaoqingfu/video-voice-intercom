#pragma once

#include <windows.h>
#include "../BcAdaptor/Adaptor.h"

#pragma comment(lib, "BcAdaptor/Adaptor.lib")

class BcAdaptor
{
public:
	BcAdaptor(void);
	~BcAdaptor(void);

public:
	int init(const char* loginUrl, const char* usr, const char* psw);
	void deinit();

	HANDLE getAdaptorHandle()
	{ return m_hAdaptor; }


public:
	//directory query
int deviceQuery(int type, int parentId,
				const char *pVia, char *pDirBuf,
				int bufSize, int *pRealSize );

int devTypedQuery(int devType, char* resBuf, int* resBufLen);
int devPtzControl(HANDLE hReal, int ptzCmd, int arg, int res);

//real video
HANDLE realTranslate(int cameraId, const char* pVia, 
							 const char *dstIP, unsigned short dstPort, int *pError, 
							 unsigned int *bindAddr, unsigned short* bindPort );
void realClose( HANDLE hReal );



private:
	HANDLE m_hAdaptor;

};
