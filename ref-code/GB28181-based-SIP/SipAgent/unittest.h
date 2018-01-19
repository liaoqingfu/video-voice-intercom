#pragma once


class unittest
{
public:
	unittest(void);
	~unittest(void);

	void start();

public:
	static unsigned int __stdcall testProc(void* context); 


public:
	void adaptor_QueryDir();
	
};
