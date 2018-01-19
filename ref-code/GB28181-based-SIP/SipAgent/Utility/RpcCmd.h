 /** $Id$ $DateTime$
 *  @file  RpcCmd.h
 *  @brief XmlRpcClient的上层封装
 *  @version 0.0.1
 *  @since 0.0.1
 *  @author qinyf<qinyf@bstar.com.cn>
 *  @date 2011-11-29    Created it
 */
/******************************************************************************
*@note
    Copyright 2007, BeiJing Bluestar Corporation, bsrExplorer
                        ALL RIGHTS RESERVED
 Permission is hereby granted to licensees of BeiJing Bluestar, Inc. products
 to use or abstract this computer program for the sole purpose of implementing
 a product based on BeiJing Bluestar, Inc. products. No other rights to
 reproduce, use, or disseminate this computer program,whether in part or  in
 whole, are granted. BeiJing Bluestar, Inc. makes no representation or
 warranties with respect to the performance of this computer program, and
 specifically disclaims any responsibility for any damages, special or
 consequential, connected with the use of this program.
 For details, see http://www.bstar.com.cn/
******************************************************************************/
#ifndef _RPCCMD_H
#define _RPCCMD_H

#include "common.h"

#include <string>
using namespace std;
//include 
#include "XmlRpc.h"
using namespace XmlRpc;


//class define
#define ERR_EXPLORER 38000
#define RPC_ERR_101 101

enum LoginType
{
	LT_NULL   = 0x0,
	LT_LOCAL  = 0x1,
	LT_CENTER = 0x2,
	LT_DOOR   = 0x4,
};




class RpcCmd
{
public:
	RpcCmd(void);
	~RpcCmd(void);

public:
	//初始化一个xmlRpcClient
	int initRpcClient(const char* strAddr, int port);

	void resetRpc(int sessionId);

	//rpc执行体
	bool excute(const char* strCmd, XmlRpcValue& param, XmlRpcValue& result, int& ireport);

	//login
	bool login(const char* strUser, const char* strPassword, XmlRpcValue& result, int ext);

	//get client session
	int getSession();

private:
	int m_iSession;

	static int g_usrCount;

	XmlRpcClient* m_pRpcExcutor;

	string m_strAddr;
	int m_iport;

	string m_strUser;
	string m_strPassword;

	int m_iUsrIndex;

	


};


#endif
