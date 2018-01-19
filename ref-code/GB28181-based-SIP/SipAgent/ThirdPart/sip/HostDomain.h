#pragma once

#include <list>
#include <string>

/*
uri的绝对域名管理
*/

struct AbsDomain
{
	char domainName[64];
	char uriHost[24];
	char user[32];
	int uriPort;

	AbsDomain()
	{
		memset(domainName, 0, sizeof(domainName));
		memset(uriHost, 0, sizeof(uriHost));
		memset(user, 0, sizeof(user));
		uriPort = 0;
	}

	const AbsDomain& operator=(const AbsDomain& filed)
	{
		strcpy(domainName, filed.domainName);
		strcpy(uriHost, filed.uriHost);
		strcpy(user, filed.user);
		uriPort = filed.uriPort;

		return *this;
	}

};


class HostDomain
{
public:
	HostDomain(void);
	~HostDomain(void);

public:
	void AppendOneUriDomain(char* domainName, char* user, char* host, int port);
  void GetUriDomainFromHost(char* host, int port, char* user, std::string& filed);
	void GetHostFromDomain(char* filed, char* user, std::string& host, int* port);

public:

	std::list<AbsDomain > m_FiledList;

};
