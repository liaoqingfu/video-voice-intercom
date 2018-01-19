// utility.cpp
//

#include "utility.h"
#include <windows.h>

#include <fstream>
#include <string>

std::string
GetAppPath()
{
	std::string str;
	char buffer[MAX_PATH] = {0};
	unsigned int dw = ::GetModuleFileName(NULL, buffer, MAX_PATH);
	if(dw != 0)
	{
		str = buffer;
		str = str.substr(0, str.find_last_of("\\"));
	}

	return str + "\\";
}

bool
IsFileExist(std::string strFilePath)
{
	std::fstream file;
	file.open(strFilePath.c_str(), std::ios::in);
	if (!file)
	{
		return false;
	}

	return true;
}

bool
UTF82Unicode(const char *input_utf8, wchar_t **p_output_unicode, unsigned long *length)
{
	if (input_utf8 == NULL)
		return false;

	const char* p_current_char = input_utf8;
	unsigned long unicode_length = 0;
	char current_char;
	// calculate the size to locate
	do
	{
		// get the begining char
		current_char = *p_current_char;

		if ((current_char  & 0x80) == 0)
		{
			// 0xxxxxxx
			p_current_char++;
		}
		else if ((current_char  & 0xe0) == 0xc0)
		{
			// < 110x-xxxx 10xx-xxxx
			p_current_char += 2;
		} 
		else if ((current_char  & 0xf0) == 0xe0)
		{
			// < 1110-xxxx 10xx-xxxx 10xx-xxxx
			p_current_char += 3;
		} 
		else if ((current_char  & 0xf8) == 0xf0)
		{
			// < 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx
			p_current_char += 4;
		}
		else if ((current_char & 0xfc) == 0xf8)
		{
			// 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			p_current_char += 5;
		}
		else
		{
			// if((current_char & 0xfe) == 0xfc)
			// 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			p_current_char += 6;
		}
		unicode_length++;

	}while (current_char != 0);

	wchar_t* des = new wchar_t[unicode_length];
	unsigned long unicode_index = 0;
	p_current_char = input_utf8;

	do
	{
		current_char = *p_current_char;

		if ((current_char & 0x80) == 0)
		{
			des[unicode_index] = p_current_char[0];
			p_current_char++;
		}
		else if ((current_char & 0xE0) == 0xC0)
		{
			// < 110x-xxxx 10xx-xxxx
			wchar_t &wide_char = des[unicode_index];
			wide_char  = (p_current_char[0] & 0x3F) << 6;
			wide_char |= (p_current_char[1] & 0x3F);
			p_current_char += 2;
		}
		else if ((current_char & 0xF0) == 0xE0)
		{
			// < 1110-xxxx 10xx-xxxx 10xx-xxxx
			wchar_t &wide_char = des[unicode_index];
			wide_char  = (p_current_char[0] & 0x1F) << 12;
			wide_char |= (p_current_char[1] & 0x3F) << 6;
			wide_char |= (p_current_char[2] & 0x3F);
			p_current_char += 3;
		}
		else if ((current_char & 0xF8) == 0xF0)
		{
			// < 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx
			wchar_t &wide_char = des[unicode_index];
			wide_char  = (p_current_char[0] & 0x0F) << 18;
			wide_char |= (p_current_char[1] & 0x3F) << 12;
			wide_char |= (p_current_char[2] & 0x3F) << 6;
			wide_char |= (p_current_char[3] & 0x3F);
			p_current_char += 4;
		}
		else if ((current_char & 0xfc) == 0xf8)
		{
			// 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
			wchar_t &wide_char = des[unicode_index];
			wide_char = (p_current_char[0] & 0x07) << 24;
			wide_char |= (p_current_char[1] & 0x3F) << 18;
			wide_char |= (p_current_char[2] & 0x3F) << 12;
			wide_char |= (p_current_char[3] & 0x3F) << 6;
			wide_char |= (p_current_char[4] & 0x3F);
			p_current_char += 5;
		}
		else
		{
			wchar_t &wide_char = des[unicode_index];
			wide_char = (p_current_char[0] & 0x03) << 30;
			wide_char |= (p_current_char[1] & 0x3F) << 24;
			wide_char |= (p_current_char[2] & 0x3F) << 18;
			wide_char |= (p_current_char[3] & 0x3F) << 12;
			wide_char |= (p_current_char[4] & 0x3F) << 6;
			wide_char |= (p_current_char[5] & 0x3F);
			p_current_char += 6;
		}
		unicode_index++;

	} while (current_char != 0);

	*p_output_unicode =  des;
	*length = unicode_length - 1; // ignore the last 

	return true;
}

bool
Unicode2UTF8(const wchar_t *input_unicode, char **p_output_utf8,unsigned long *length)
{
	if (input_unicode == NULL) 
		return false;

	int size_d = 8;
	int buffer_size = 0;

	const wchar_t* p_unicode = input_unicode;
	// count for the space need to allocate
	wchar_t w_char;
	do
	{
		w_char = *p_unicode;
		if (w_char < 0x80)
		{
			// utf char size is 1
			buffer_size += 1;
		}
		else if (w_char < 0x800) 
		{
			// utf char size is 2
			buffer_size += 2;
		}
		else if (w_char < 0x10000)
		{
			// utf char size is 3
			buffer_size += 3;
		}
		else if (w_char < 0x200000)
		{
			// utf char size is 4
			buffer_size += 4;
		}
		else if (w_char < 0x4000000)
		{
			// utf char size is 5
			buffer_size += 5;
		}
		else
		{
			// utf char size is 6
			buffer_size += 6;
		}
		p_unicode++;

	}while (w_char != static_cast<char>(0));
	
	// allocate the memory
	char* utf8 = new char[buffer_size];

	p_unicode = input_unicode;
	int index_buffer = 0;
	// do the conversion
	do
	{
		w_char = *input_unicode;  // the unicode char current being converted
		input_unicode++;

		if (w_char < 0x80)
		{
			// length = 1;
			utf8[index_buffer++] = static_cast<char>(w_char);
		}
		else if (w_char < 0x800)
		{
			// length = 2;
			utf8[index_buffer++] = 0xc0 | (w_char >> 6);
			utf8[index_buffer++] = 0x80 | (w_char & 0x3f);
		}
		else if (w_char < 0x10000)
		{
			// length = 3;
			utf8[index_buffer++] = 0xe0 | (w_char >> 12);
			utf8[index_buffer++] = 0x80 | ((w_char >> 6) & 0x3f);
			utf8[index_buffer++] = 0x80 | (w_char & 0x3f);
		}
		else if (w_char < 0x200000) 
		{
			// length = 4;
			utf8[index_buffer++] = 0xf0 | (static_cast<int>(w_char) >> 18);
			utf8[index_buffer++] = 0x80 | ((w_char >> 12) & 0x3f);
			utf8[index_buffer++] = 0x80 | ((w_char >> 6) & 0x3f);
			utf8[index_buffer++] = 0x80 | (w_char & 0x3f);
		}
		else if (w_char < 0x4000000) 
		{
			// length = 5
			utf8[index_buffer++] = 0xf8| (static_cast<int>(w_char) >> 24);
			utf8[index_buffer++] = 0x80 | ((static_cast<int>(w_char) >> 18) & 0x3f);
			utf8[index_buffer++] = 0x80 | ((w_char >> 12) & 0x3f);
			utf8[index_buffer++] = 0x80 | ((w_char >> 6) & 0x3f);
			utf8[index_buffer++] = 0x80 | (w_char & 0x3f);
		}
		else
		{  // if(wchar >= 0x4000000)
			// all other cases length = 6
			utf8[index_buffer++] = 0xfc | (static_cast<int>(w_char) >> 30);
			utf8[index_buffer++] = 0x80 | ((static_cast<int>(w_char) >> 24) & 0x3f);
			utf8[index_buffer++] = 0x80 | ((static_cast<int>(w_char) >> 18) & 0x3f);
			utf8[index_buffer++] = 0x80 | ((w_char >> 12) & 0x3f);
			utf8[index_buffer++] = 0x80 | ((w_char >> 6) & 0x3f);
			utf8[index_buffer++] = 0x80 | (w_char & 0x3f);
		}

	}while (w_char !=  static_cast<char>(0));

	// set the output length
	*length = buffer_size - 1;  // ignore last 

	// set the output charset
	*p_output_utf8 = utf8;

	return true;
}

std::string
wstr2str(const std::wstring& wstr)
{
	std::string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs"); 
	const wchar_t* _Source = wstr.c_str();
	size_t _Dsize = 2 * wstr.size() + 1;

	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	std::string result = _Dest;

	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());

	return result;
}

std::wstring
str2wstr(const std::string& str)
{
	std::string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs"); 
	const char* _Source = str.c_str();
	size_t _Dsize = str.size() + 1;

	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest;

	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());

	return result;
}

void
UTF82String(const char *input_utf8, std::string& strDes)
{
	wchar_t* wbuf;
	unsigned long ul;
	std::wstring wstr;

	UTF82Unicode(input_utf8, &wbuf, &ul);

	wstr = wbuf;

	delete[] wbuf;
	wbuf = NULL;

	strDes = wstr2str(wstr);
}

void
String2UTF8(std::string strGb, std::string& strDes)
{
	std::wstring wstr = str2wstr(strGb);

	char* buf = NULL;
	unsigned long ul = 0;
	Unicode2UTF8(wstr.c_str(), &buf, &ul);

	strDes = buf;

	delete[] buf;
	buf = NULL;
}

int
RegexGetString(std::string strRegex, std::string strSource, strList& retList)
{
	/*std::string strRet;
	boost::regex reg(strRegex);
	boost::tmatch what;

	if(boost::regex_match(strSource.c_str(), what, reg))
	{
		for(unsigned int i=0; i<what.size(); i++)
		{
			strRet =  what[i].first;
			retList.push_back(strRet);
		}
	}

	return what.size();*/

	return 0;
}


std::string
i2str(int iInput)
{
	std::string s ;//= boost::lexical_cast <std::string>(iInput);

	return s;
}

bool GetSubStr(std::string strSrc, std::string strBegin, std::string strEnd, std::string& strOut)
{
	int iPos1 = -1, iPos2 = -1;

	iPos1 = strSrc.find(strBegin);
	iPos2 = strSrc.find(strEnd, iPos1+1);

	if(iPos1 < 0 || iPos2 < 0 || iPos2 < iPos1)
	{
		return false;
	}

	strOut = strSrc.substr(iPos1 + strBegin.length(), iPos2 - iPos1 - strBegin.length());

	return true;
}