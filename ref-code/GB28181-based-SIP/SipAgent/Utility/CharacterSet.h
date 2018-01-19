// CharacterSet.h: interface for the CCharacterSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARACTERSET_H__70762936_27D7_4632_9606_ECE5A03647F0__INCLUDED_)
#define AFX_CHARACTERSET_H__70762936_27D7_4632_9606_ECE5A03647F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<string>
using namespace std;

class CCharacterSet  
{
public:
	CCharacterSet();
	virtual ~CCharacterSet();

	static int UTF_8ToGB2312(string& pOut,const char *pText, int pLen);
	static int GB2312ToUTF_8(string& pOut,const char *pText, int pLen);

protected:
	// Unicode 转换成UTF-8
	static int UnicodeToUTF_8(char* pOut,const short* pText);
	// GB2312 转换成　Unicode
	static int Gb2312ToUnicode(short* pOut,const char *gbBuffer);
	// 把Unicode 转换成 GB2312
	static int UnicodeToGB2312(char* pOut,unsigned short uData);
	// 把UTF-8转换成Unicode
	static int UTF_8ToUnicode(short* pOut,const char* pText);
	static int WIN_UTF_8ToGB2312(string& pOut,const char *pText, int pLen);
	static int WIN_GB2312ToUTF_8(string& pOut,const char *pText, int pLen);

};

#endif // !defined(AFX_CHARACTERSET_H__70762936_27D7_4632_9606_ECE5A03647F0__INCLUDED_)
