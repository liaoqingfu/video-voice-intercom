#include "TaskTimer.h"

#include <process.h>


TaskTimer::TaskTimer(int timeSecond)
{
	m_timeSecond = timeSecond;
	m_bTimerStop = false;

	m_timerFun = NULL;
	m_pFunParam = NULL;

}


TaskTimer::~TaskTimer(void)
{
	stop();
}


void TaskTimer::start()
{
	unsigned int threadId = 0;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, &TaskTimer::timer, this, 0, &threadId);

	CloseHandle(hThread);

}


void TaskTimer::stop()
{
	m_bTimerStop = true;
	//kill thread
}


void TaskTimer::setTimerFun(timerCallBack fun, void* param)
{
	m_timerFun = fun;
	m_pFunParam = param;
}



unsigned int __stdcall TaskTimer::timer(void* context)
{
	TaskTimer* pthis = (TaskTimer*)context;
	if (pthis == NULL)
		return -1;

	unsigned int curTm = 0;
	unsigned int lastTm = 0;

	//执行定时器函数
		if (pthis->m_timerFun != NULL)
		{
			pthis->m_timerFun(pthis->m_pFunParam);
		}

	do{
		curTm = GetTickCount();
		if (lastTm == 0)
		{
			lastTm = curTm;
		}

		if (curTm - lastTm >= pthis->m_timeSecond*1000)
		{
			lastTm = curTm;
		}
		else
		{
			Sleep(1*1000);
			continue;
		}

		//执行定时器函数
		if (pthis->m_timerFun != NULL)
		{
			pthis->m_timerFun(pthis->m_pFunParam);
		}

	}while (!pthis->m_bTimerStop);

	return 0;

}


unsigned long TaskTimer::getTickCount(void)
{
	unsigned long curTime;

#ifdef WIN32
	curTime = GetTickCount();
#else
	struct timeval current;
	gettimeofday(&current, NULL);
	curTime = current.tv_sec * 1000 + current.tv_usec/1000;
#endif

	return curTime;
}
