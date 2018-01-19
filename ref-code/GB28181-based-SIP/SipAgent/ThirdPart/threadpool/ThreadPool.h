#pragma once
#define   WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <list>
#include <vector>

#include "lock.h"


namespace base
{

	typedef int (*fun)(void* context);

	enum ThreadStatus
	{
		kerror = -1,
		knormal = 0,
		krun,
		kblock
	};

	class Thread
	{
	public:
		Thread(fun f, void* context);
		~Thread();

	public:
		void start();
		void stop();

		void resume()
		{
			::ResumeThread(_threadHandle);
			_bActive = true;
		}
		void suspend()
		{
			_bActive = false;
			::SuspendThread(_threadHandle);
		}

		bool active() { return _bActive; }

	  static unsigned int __stdcall threadProc(void* context);
		
	private:
		unsigned int _threadId;
		HANDLE _threadHandle;
		bool _bStop;
		fun _threadFun;
		void* _context;
		bool _bActive;
	};


	class Runable
	{
	public:
		virtual ~Runable(){};

		virtual void run() = 0;
	};



class ThreadPool
{
public:
	ThreadPool(void);
	~ThreadPool(void);

	void start(int threadNum);
	void stop();
	void runInThread(Runable* runobj);

	static int runLoop(void* context);


private: 
	std::list<Runable* > _taskQueue;
	std::vector<Thread> _threads;

	lock_summary::critical_lock _crclLock;
	
};


}
