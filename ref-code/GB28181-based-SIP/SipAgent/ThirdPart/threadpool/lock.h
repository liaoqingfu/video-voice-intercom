#pragma once

#include <windows.h>


namespace lock_summary
{
	class ILock
	{
	public:
		ILock(){}
		virtual ~ILock(){}

	public:
		virtual void lock() = 0;
		virtual void unlock() = 0;
	};

	class mutex_lock : public ILock
	{
	public:
		mutex_lock();
		~mutex_lock();

	public:
		void lock();
		void unlock();

	public:
		HANDLE m_mutex;
	};

	class critical_lock : public ILock
	{
	public:
		critical_lock();
		~critical_lock();

	public:
		void lock();
		void unlock();

	public:
		CRITICAL_SECTION m_cs;
	};


	class scope_lock
	{
	public:
		scope_lock(ILock* plock_entity);
		~scope_lock(void);

	public:
		void lock();
		void unlock();

	private:
		ILock* m_pLock;
	};
}


