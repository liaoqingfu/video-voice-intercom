#include "lock.h"
#include <tchar.h>

using namespace lock_summary;


mutex_lock::mutex_lock()
{
	m_mutex = ::CreateMutex(NULL, FALSE, __T("mutex"));
}

mutex_lock::~mutex_lock()
{
	::CloseHandle(m_mutex);
}

void mutex_lock::lock()
{
	unsigned int ret = ::WaitForSingleObject(m_mutex, INFINITE);
}


void mutex_lock::unlock()
{
	::ReleaseMutex(m_mutex);
}

critical_lock::critical_lock()
{
	::InitializeCriticalSection(&m_cs);
}


critical_lock::~critical_lock()
{
	::DeleteCriticalSection(&m_cs);
}


void critical_lock::lock()
{
	::EnterCriticalSection(&m_cs);
}
void critical_lock::unlock()
{
	::LeaveCriticalSection(&m_cs);
}




scope_lock::scope_lock(ILock* plock_entity)
{
	m_pLock = plock_entity;

	lock();

}


scope_lock::~scope_lock(void)
{
	unlock();
}

void scope_lock::lock()
{
	if (m_pLock != NULL)
	{
		m_pLock->lock();
	}
}


void scope_lock::unlock()
{
	if (m_pLock != NULL)
	{
		m_pLock->unlock();
	}
}
