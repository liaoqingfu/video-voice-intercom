#include "BcAdaptor.h"
#include "log4z.h"

#define TimeOut_Adaptor 1000

BcAdaptor::BcAdaptor(void)
:m_hAdaptor(NULL)
{
}

BcAdaptor::~BcAdaptor(void)
{
}

int BcAdaptor::init(const char* loginUrl, const char* usr, const char* psw)
{
	int nret = 0;
	adaptor_init(TimeOut_Adaptor);

	m_hAdaptor = adaptor_login(loginUrl, usr, psw);
	if (m_hAdaptor != NULL)
	{
		_LOG(LOG_LEVEL_DEBUG, "初始化adaptor成功,url=%s, usr=%s, psw=%s", loginUrl, usr, psw);
	} 
	else
	{
		nret = -1;
		_LOG(LOG_LEVEL_DEBUG, "初始化adaptor失败,url=%s, usr=%s, psw=%s", loginUrl, usr, psw);
	}

	nret = adaptor_hello( m_hAdaptor );

	return nret;
}


void BcAdaptor::deinit()
{
	adaptor_logout(m_hAdaptor);
	adaptor_uninit();
}


int BcAdaptor::deviceQuery(int type, int parentId,
								const char *pVia, char *pDirBuf,
								int bufSize, int *pRealSize )
{
	return adaptor_deviceQuery(m_hAdaptor, type, parentId, pVia, pDirBuf, bufSize, pRealSize);

}


HANDLE BcAdaptor::realTranslate( int cameraId, const char* pVia, 
							 const char *dstIP, unsigned short dstPort, int *pError, 
							 unsigned int* bindAddr, unsigned short* bindPort )
{
	return adaptor_realTranslate( m_hAdaptor, cameraId, pVia, dstIP, dstPort, pError, bindAddr, bindPort );
}


void BcAdaptor::realClose( HANDLE hReal )
{
	adaptor_realClose(hReal);
}


int BcAdaptor::devTypedQuery(int devType, char* resBuf, int* resBufLen)
{
	return adaptor_deviceTypedQuery(m_hAdaptor, devType, resBuf, resBufLen);
}


int BcAdaptor::devPtzControl(HANDLE hReal, int ptzCmd, int arg, int res)
{
	return adaptor_realPtzControl( hReal, ptzCmd, arg, res);
}