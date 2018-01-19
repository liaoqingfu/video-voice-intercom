// CharacterSet.cpp: implementation of the CCharacterSet class.
//
//////////////////////////////////////////////////////////////////////
#include "CharacterSet.h"
#ifdef WIN32
#include "Windows.h"
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCharacterSet::CCharacterSet()
{
}

CCharacterSet::~CCharacterSet()
{
}


int CCharacterSet::UTF_8ToUnicode(short* pOut,const char *pText)
{
	char* uchar = (char *)pOut;
	uchar[1] = ((pText[0] & 0x0F) << 4) + ((pText[1] >> 2) & 0x0F);
	uchar[0] = ((pText[1] & 0x03) << 6) + (pText[2] & 0x3F);
	return 0;
}

int CCharacterSet::UnicodeToGB2312(char* pOut,unsigned short uData)
{
#ifdef WIN32
	return WideCharToMultiByte(CP_ACP,NULL,(LPCWSTR)&uData,1,pOut,sizeof(WCHAR),NULL,NULL);
#endif
	return -1;
}

int CCharacterSet::Gb2312ToUnicode(short* pOut,const char *gbBuffer)
{
#ifdef WIN32
	::MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,gbBuffer,2,(WCHAR*)pOut,1);
#endif
	return -1;
}

int CCharacterSet::UnicodeToUTF_8(char* pOut,const short* pText)
{
	// 注意 WCHAR高低字的顺序,低字节在前，高字节在后
	char* pchar = (char *)pText;

	pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
	pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
	pOut[2] = (0x80 | (pchar[0] & 0x3F));
	
	return 0;
}

int CCharacterSet::WIN_GB2312ToUTF_8(string& pOut,const char *pText, int pLen)
{
	char buf[4];
	char* rst = new char[1+2*pLen];
	
	memset(buf,0,4);
	memset(rst,0,1+2*pLen);
	
	int i = 0;
	int j = 0;	
	while(i < pLen)
	{
		//如果是英文直接复制就可以
		if( *(pText + i) >= 0)
		{
			rst[j++] = pText[i++];
		}
		else
		{
			short pbuffer;
			Gb2312ToUnicode(&pbuffer,pText+i);
			
			UnicodeToUTF_8(buf,&pbuffer);
			
			unsigned short int tmp = 0;
			tmp = rst[j] = buf[0];
			tmp = rst[j+1] = buf[1];
			tmp = rst[j+2] = buf[2];
			
			
			j += 3;
			i += 2;
		}
	}
	rst[j] = '\0';

	//返回结果
	pOut = rst;		
	delete []rst;	
	
	return 0;
}

int CCharacterSet::WIN_UTF_8ToGB2312(string &pOut, const char *pText, int pLen)
{
	 char * newBuf = new char[pLen+1];
	 char Ctemp[4];
	 memset(Ctemp,0,4);

	 int i =0;
	 int j = 0;
	 
	 while(i < pLen)
	 {
	 	if(pText[i] > 0)
		{
			newBuf[j++] = pText[i++];			
		}
		else                 
		{
			short Wtemp;
			UTF_8ToUnicode(&Wtemp,pText + i);
		
			UnicodeToGB2312(Ctemp,Wtemp);
		    
			newBuf[j] = Ctemp[0];
			newBuf[j + 1] = Ctemp[1];

			i += 3;    
			j += 2;   
		}
	 }
	 newBuf[j] = '\0';
	 
	 pOut = newBuf;
	 delete []newBuf;
	 
	 return 0; 
}


int CCharacterSet::UTF_8ToGB2312(string& pOut,const char *pText, int pLen)
{
#ifdef WIN32
	return WIN_UTF_8ToGB2312(pOut,pText,pLen);
#else
#endif
}

int CCharacterSet::GB2312ToUTF_8(string& pOut,const char *pText, int pLen)
{
#ifdef WIN32
	return WIN_GB2312ToUTF_8(pOut,pText,pLen);
#else
#endif
}
