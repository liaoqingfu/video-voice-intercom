#include "AsynPolicy.h"

//static 
int AsynPolicy::m_gIndex  = 0;
map<int, AnswerArgs> AsynPolicy::m_Args;

AsynPolicy::AsynPolicy(void)
{
}

AsynPolicy::~AsynPolicy(void)
{
}


void AsynPolicy::StorePolicyInfo(int index, AnswerArgs* arg)
{
	if (arg == NULL)
	{
		return ;
	}

	//m_asynPolicyLock.lock();
	m_Args[index] = *arg;
	//m_asynPolicyLock.unlock();
}


void AsynPolicy::ErasePolicyInfo(int portKey)
{
	m_Args.erase(portKey);
}


int AsynPolicy::GetPort()
{
	int ntemp = 0;
	//m_asynPolicyLock.lock();
	ntemp = ++m_gIndex;
	//m_asynPolicyLock.unlock();

	return ntemp;
}


AnswerArgs& AsynPolicy::GetPortAnswerArgs(int portKey)
{
	return m_Args[portKey];
}

