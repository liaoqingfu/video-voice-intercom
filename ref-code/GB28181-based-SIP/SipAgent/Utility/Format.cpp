#include "Format.h"
#include <string.h>

Format::Format(void)
{
	memset(_formatStr, 0 , _maxSize);
	memset(_tempBuf, 0 , _maxInput);
}

Format::~Format(void)
{
}

void Format::append(const char* data)
{
	int len = strlen(data);
	if (len <= 0)
	{
		return ;
	}
	
	int leftSize = _maxSize - strlen(_formatStr);
	if (leftSize - 1 < len)
	{
		return ;
	}
	
	strcat_s(_formatStr, leftSize - 1, data);

}


//--------------------------------------------
void format_unitest()
{
	Format format;
	format<<10<<"abc"<<'c'<<3.1415926;
	const char* p = (format<<10<<"abc"<<'c'<<3.1415926).data();
	format<<(void*)p;

	p = format.data();
}