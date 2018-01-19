#pragma once

#pragma warning(disable:4996)

#include <map>
using namespace std;

#include "ThreadPool.h"

struct AnswerArgs
{
	char usr[32];
	char sourceIp[24];
	int sourcePort;
	char request[1024*16];
	char sn[16];

	AnswerArgs()
	{
		memset(usr, 0, sizeof(usr));
		memset(sourceIp, 0, sizeof(sourceIp));
		sourcePort = 0;
    memset(request, 0, sizeof(request));
		memset(sn, 0, sizeof(sn));

	}

	const AnswerArgs& operator=(const AnswerArgs& a)
	{
		strcpy(usr, a.usr);
		strcpy(sourceIp, a.sourceIp);
		sourcePort = a.sourcePort;
		strcpy(request, a.request);
    strcpy(sn, a.sn);
		return *this;
	}
};

//
template<typename T>
class AsynQuery : public base::Runable
{
public:

	typedef void (*pf)(T* );

	AsynQuery(T* args, pf pfun):
			m_pfun(pfun)
	{
		m_args = *args;
	}

	void run()
	{
		if (m_pfun != NULL)
			m_pfun(&m_args);
	}

private:
	T m_args;
	pf m_pfun;
};




class AsynPolicy
{
public:
	AsynPolicy(void);
	~AsynPolicy(void);

public:
	void StorePolicyInfo(int index, AnswerArgs* arg);
	void ErasePolicyInfo(int portKey);
	int GetPort();
	AnswerArgs& GetPortAnswerArgs(int portKey);

public:
	static int m_gIndex;
	static map<int, AnswerArgs> m_Args;
	//lock_summary::critical_lock m_asynPolicyLock;
};
