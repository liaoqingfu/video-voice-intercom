#ifndef _TASKTIMER_H
#define _TASKTIMER_H

#include <iostream>


#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <netinet/in.h>
#endif  

typedef void (*timerCallBack)(void* param);

class TaskTimer
{
public:
	TaskTimer(int timeSecond);
	~TaskTimer(void);

public:
	void start();
	void stop();

	void setTimerFun(timerCallBack fun, void* param);

	static unsigned int __stdcall timer(void* context);

public:
	timerCallBack m_timerFun;
	void* m_pFunParam;

public:
	int m_timeSecond;
	bool m_bTimerStop;

	static unsigned long getTickCount(void);

};


#endif

