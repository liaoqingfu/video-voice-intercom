#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//#pragma warning(disable:4996)

/**
  Mark:
	1 仅在单线程中调用
	2 禁用拷贝构造，等号赋值操作
	3 字符串有大小限制(1024)
*/

class Format;

#define FORMAT \
	Format fm; fm


class Format
{
public:
	Format(void);
	~Format(void);

	const char* data()
	{
		return (const char*)_formatStr;
	}
	void clear()
	{
		memset(_formatStr, 0, _maxSize);
	}

public:
	Format& operator<<(int arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%d", arg);
		append(_tempBuf);

		return *this;
	}

	Format& operator<<(unsigned int arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%u", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(short arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%hd", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(unsigned short arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%hu", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(char arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%c", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(unsigned char arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%hhd", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(long arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%ld", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(unsigned long arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%ld", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(long long arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%lld", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(unsigned long long arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%lld", arg);
		append(_tempBuf);

		return *this;
	}

	Format& operator<<(double arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%lf", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(float arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%f", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(const char* arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%s", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(char* arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%s", arg);
		append(_tempBuf);

		return *this;
	}
	Format& operator<<(void* arg)
	{
		memset(_tempBuf, 0, _maxInput);
		sprintf(_tempBuf, "%0xp", arg);
		append(_tempBuf);

		return *this;
	}

private:
	Format(const Format& format);
	const Format& operator=(const Format& format);
private:
	void append(const char* data);

private:
	static const int _maxSize = 1024;
	static const int _maxInput = 64;
	char _formatStr[_maxSize];
	char _tempBuf[_maxInput];
};



void format_unitest();