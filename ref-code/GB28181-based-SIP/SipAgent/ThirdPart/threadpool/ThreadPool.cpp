#include "ThreadPool.h"

#include <process.h>
#include <assert.h>

using namespace base;


Thread::Thread(fun f, void* context):
_threadFun(f),_context(context),
_bActive(true),_bStop(false)
{

}


Thread::~Thread()
{

}

void Thread::start()
{
	_threadHandle = (HANDLE)_beginthreadex(NULL, 0, threadProc, this, 0, &_threadId);

}

void Thread::stop()
{
	_bStop = true;

	resume();
	int ret;
	ret = ::WaitForSingleObject(_threadHandle,100);
	if (WAIT_OBJECT_0 != ret)
	{
		DWORD dwExitCode;
		GetExitCodeThread(_threadHandle,&dwExitCode);
		if (STILL_ACTIVE ==dwExitCode)
		{
			//TRACE("STILL_ACTIVE ==dwExitCode\n");
			TerminateThread(_threadHandle,dwExitCode);
			::CloseHandle(_threadHandle);
		}
	}	

	_threadHandle = NULL;
}


unsigned int __stdcall Thread::threadProc(void* context)
{
	Thread* pthis = (Thread*)context;
	if (pthis == NULL)
	{
		return -1;
	}

	int runStatus = 0;
	while (!pthis->_bStop)
	{
		try
		{
			runStatus = pthis->_threadFun(pthis->_context);
			if (runStatus == kblock)
			{
				pthis->suspend();
			}
		}
		catch (std::exception& exc)
		{

		}

	}

	return 0;
}



ThreadPool::ThreadPool(void)
{
}

ThreadPool::~ThreadPool(void)
{
}


void ThreadPool::start(int threadNum)
{
	assert(threadNum > 0);

	_threads.reserve(threadNum);
	for (int i = 0; i < threadNum; i++)
	{
		_threads.push_back(Thread(&ThreadPool::runLoop, (void*)this));
		_threads[i].start();
	}

}


//1 stop all thread
//2 destroy all resource
void ThreadPool::stop()
{
	for (int i = 0; i < _threads.size(); i++)
	{
		_threads[i].stop();
	}

	{
		lock_summary::scope_lock lock(&_crclLock);
		std::list<Runable*>::iterator it;
		for (it = _taskQueue.begin(); it != _taskQueue.end(); )
		{
			delete (*it);
			*it = NULL;

			it = _taskQueue.erase(it);
		}
	}

}


void ThreadPool::runInThread(Runable* runobj)
{
	assert(runobj != NULL);
	{
		lock_summary::scope_lock lock(&_crclLock);
		_taskQueue.push_back(runobj);

		for (int i = 0; i < _threads.size(); i++)
		{
			if (!_threads[i].active())
			{
				_threads[i].resume();
				break;
			}
		}
	}


}

//1 many threads call this fun,lock
//2 if taskqueue is empty:suspend current thread
//
int ThreadPool::runLoop(void* context)
{
	ThreadPool* pthis = (ThreadPool*)context;
	if (pthis == NULL)
	{
		return kerror;
	}

	if (pthis->_taskQueue.empty())
		return kblock;

  //run
	Runable* runobj = NULL;
	{
		lock_summary::scope_lock lock(&pthis->_crclLock);
		runobj = pthis->_taskQueue.front();
		pthis->_taskQueue.pop_front();
	}

	runobj->run();
	delete runobj;
	runobj = NULL;

	return knormal;
}
