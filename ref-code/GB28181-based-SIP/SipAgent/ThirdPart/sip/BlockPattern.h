#pragma once

/*
  ×èÈûÄ£ÐÍ
*/

#include <list>
#include "lock.h"
#include <algorithm>


template<typename T>
class CBlockPattern
{
public:
	CBlockPattern(void);
	~CBlockPattern(void);

public:
	//add block obj
	void AddBlock(T& t);
	//del block obj
	void DelBlock(T& t);
	//×èÈû
	int Suspend(T& t);
	//»½ÐÑ
	int Resume(T& t);

public:
	std::list<T> m_BlockQueue;
	lock_summary::critical_lock m_crtlLock;
};



template<typename T>
CBlockPattern<T>::CBlockPattern(void)
{
}


template<typename T>
CBlockPattern<T>::~CBlockPattern(void)
{
	m_BlockQueue.clear();
}



template<typename T>
void CBlockPattern<T>::AddBlock(T& t)
{
	lock_summary::scope_lock lock(&m_crtlLock);
	m_BlockQueue.push_back(t);
}


//del block obj
template<typename T>
void CBlockPattern<T>::DelBlock(T& t)
{
	lock_summary::scope_lock lock(&m_crtlLock);

	std::list<T>::iterator it;
	it = std::find(m_BlockQueue.begin(), m_BlockQueue.end(), t);
	if (it != m_BlockQueue.end())
	{
		m_BlockQueue.erase(it);
	}
}

//×èÈû
template<typename T>
int CBlockPattern<T>::Suspend(T& t)
{

	do 
	{
		std::list<T>::iterator it;

		{
			lock_summary::scope_lock lock(&m_crtlLock);
			it = std::find(m_BlockQueue.begin(), m_BlockQueue.end(), t);
			if (it != m_BlockQueue.end() && !(it->bwait))
			{
				t = *it;
				m_BlockQueue.erase(it);
				break;
			}
	    }
		
		//timeout
    Sleep(10);
	} while (true);
	

	//×èÈû

	return 0;
}

//»½ÐÑ
template<typename T>
int CBlockPattern<T>::Resume(T& t)
{
	if (m_BlockQueue.size() <= 0)
	{
		return -1;
	}

	std::list<T>::iterator it;		
	lock_summary::scope_lock lock(&m_crtlLock);
	it = std::find(m_BlockQueue.begin(), m_BlockQueue.end(), t);
	if (it != m_BlockQueue.end())
	{

		*it = t;
		it->bwait = false;
	}

	return 0;
}
