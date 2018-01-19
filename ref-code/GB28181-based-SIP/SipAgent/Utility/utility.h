// utility.h
//

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <string>
#include <list>
#include <locale.h>

#ifdef _WINDOWS

#else
#include <unistd.h>
#include <sys/time.h>
#include <netinet/in.h>
#endif  


#pragma warning(disable: 4996)


typedef std::list<std::string> strList;

std::string GetAppPath();

bool IsFileExist(std::string strFilePath);

bool UTF82Unicode(const char *input_utf8, wchar_t **p_output_unicode, unsigned long *length);

bool Unicode2UTF8(const wchar_t *input_unicode, char **p_output_utf8,unsigned long *length);

std::string wstr2str(const std::wstring& wstr);

std::wstring str2wstr(const std::string& str);

void UTF82String(const char *input_utf8, std::string& strDes);

void String2UTF8(std::string strGb, std::string& strDes);

int RegexGetString(std::string strRegex, std::string strSource, strList& retList);


std::string i2str(int iInput);

bool GetSubStr(std::string strSrc, std::string strBegin, std::string strEnd, std::string& strOut);

#endif // _UTILITY_H_