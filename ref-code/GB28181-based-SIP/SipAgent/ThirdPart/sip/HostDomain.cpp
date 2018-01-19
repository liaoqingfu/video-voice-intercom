#include "HostDomain.h"

HostDomain::HostDomain(void)
{
}

HostDomain::~HostDomain(void)
{
	m_FiledList.clear();
}

void HostDomain::AppendOneUriDomain(char* domainName, char* user, char* host, int port)
{
	AbsDomain filed;
	strcpy(filed.domainName, domainName);
	strcpy(filed.uriHost, host);
	strcpy(filed.user, user);
	filed.uriPort = port;

  m_FiledList.push_back(filed);
}


void HostDomain::GetUriDomainFromHost(char* host, int port, char* user, std::string& filed)
{
	std::list<AbsDomain >::iterator it;
	for (it = m_FiledList.begin(); it != m_FiledList.end(); it++)
	{
		if (strcmp(it->uriHost, host) == 0 && (it->uriPort == port) && strcmp(it->user, user) == 0)
		{
			filed = it->domainName;
			break;
		}
	}

}


void HostDomain::GetHostFromDomain(char* filed, char* user, std::string& host, int* port)
{
	std::list<AbsDomain >::iterator it;
	for (it = m_FiledList.begin(); it != m_FiledList.end(); it++)
	{
		if (strcmp(it->domainName, filed) == 0 && strcmp(it->user, user) == 0)
		{
			host = it->uriHost;
			*port = it->uriPort;
			break;
		}
	}

}
