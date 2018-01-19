#pragma once

#include <list>

#include <windows.h>

template<typename T>
class CAsynNotifyNode
{
public:
	CAsynNotifyNode(void);
	~CAsynNotifyNode(void);

public:
	int Create();

	int WaitForComplete();
	int GetWaitData(int id, T& data);

	int Complete(T data);


private:
	std::list<T> m_CacheList;

	void* m_SemaphoreShare;

};

template<typename T>
CAsynNotifyNode<T>::CAsynNotifyNode()
{
}

template<typename T>
CAsynNotifyNode<T>::~CAsynNotifyNode()
{
}

template<typename T>
int CAsynNotifyNode<T>::Create()
{
	LPSECURITY_ATTRIBUTES pattri;
	m_SemaphoreShare = CreateSemaphore(NULL, 0, 1, "Notify");
	if (m_SemaphoreShare == NULL)
	{
		return -1;
	}

	return 0;
}

template<typename T>
int CAsynNotifyNode<T>::WaitForComplete()
{
	if (m_SemaphoreShare != NULL)
		WaitForSingleObject(m_SemaphoreShare, INFINITE);

	return 0;
}

template<typename T>
int CAsynNotifyNode<T>::GetWaitData(int id, T& data)
{
	std::list<T>::iterator it;
	for (it = m_CacheList.begin(); it != m_CacheList.end(); it++)
	{
		if (id == it->id)
		{
			data = *it;
			m_CacheList.erase(it);
			return 0;
		}
	}

	return -1;

}

template<typename T>
int CAsynNotifyNode<T>::Complete(T data)
{
	m_CacheList.push_back(data);

	ReleaseSemaphore(m_SemaphoreShare, 1, NULL);

	return 0;
	
}

