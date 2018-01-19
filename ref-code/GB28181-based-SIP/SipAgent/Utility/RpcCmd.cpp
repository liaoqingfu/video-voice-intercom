 /** $Id$ $DateTime$
 *  @file  RpcCmd.cpp
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
#include "rpcCmd.h"
#include "log4z.h"

int RpcCmd::g_usrCount = 0;

RpcCmd::RpcCmd(void)
{
	m_iSession = 0;

	m_iUsrIndex = 0;

	m_pRpcExcutor = NULL;
}


RpcCmd::~RpcCmd(void)
{
	delete m_pRpcExcutor;
	m_pRpcExcutor = NULL;
}


/**
 * @fn initRpcClient
 * @brief   初始化一个xmlRpcClient   
 * @param[in] strAddr:ip
 * @param[in] port : 端口
 * @retval  0: 成功
 * @retval  -1: 没实现
 * @retval  其它: 错误码
 */
int RpcCmd::initRpcClient(const char* strAddr, int port)
{
	if (m_pRpcExcutor != NULL)
	{
		delete m_pRpcExcutor;
		m_pRpcExcutor = NULL;
	}
	
	m_pRpcExcutor = new XmlRpcClient(strAddr, port);
	m_pRpcExcutor->setWaitTimeout(30);

	m_iUsrIndex = g_usrCount;
	g_usrCount++;

	m_strAddr = strAddr;
	m_iport = port;

	return 0;

}

//setUserCookie

void RpcCmd::resetRpc(int sessionId)
{
	m_iSession = sessionId;
	m_pRpcExcutor->setUserCookie(m_iSession, m_iUsrIndex);
}


/**
 * @fn excute
 * @brief  xmlRpc命令的执行体    
 * @param[in] strCmd:命令名  
 * @param[in] param xmlrpc参数
 * @param[out] result:执行返回值
 * @param[out] ireport:错误值报告
 * @retval  true：成功 false 失败
 */
bool RpcCmd::excute(const char* strCmd, XmlRpcValue& param, XmlRpcValue& result, int& ireport)
{
	RET_IF_NULL(m_pRpcExcutor, false);

	bool bresult = false;
	ireport = 0;

	if (m_pRpcExcutor->execute(strCmd, param, result)) //执行方法体
	{
		if (m_pRpcExcutor->isFault())
		{
			ireport = (int)result["faultCode"];
			if (ireport == RPC_ERR_101)
			{
				XmlRpcValue p, r;
				p["name"]     = m_strUser;
				p["password"] = m_strPassword;
				p["actor"]    = 0x01;
				p["session"]  = m_iSession;
				p["serverAddr"] = m_strAddr;
				if (m_pRpcExcutor->execute("Security.Session.login", p, r))
				{
					if (m_pRpcExcutor->isFault())
					{
						ireport = (int)r["faultCode"];
					}
					else
					{
						m_iSession = (int)r["session"];
						ireport = 0;
						bresult = true;
					}
				}
			}
			else
			{
				_LOG(LOG_LEVEL_DEBUG, "XmlRpc执行失败，请检查参数设置");
			}
		}
		else
		{
			ireport = 0;
			bresult = true;
		}
	}
	else if (!m_pRpcExcutor->isConnected()) //断开
	{
		ireport = ERR_EXPLORER + 3;
		result["faultCode"] = ireport;
	}

	return bresult;
}


/**
 * @fn login
 * @brief   登陆   
 * @param[in] strUser:用户名 
 * @param[in] strPassword:密码  
 * @param[in] result:执行结果 
 * @param[out] 
 * @return int
 * @retval  0: 成功
 * @retval  -1: 没实现
 * @retval  其它: 错误码
 */
//login
bool RpcCmd::login(const char* strUser, const char* strPassword, XmlRpcValue& result, int ext)
{
	bool bResult = false;
	XmlRpcValue param;
	LoginType actor = LT_LOCAL;
	if (strUser != NULL)
	{
		string strCmd      = "Security.Session.login";
		param["name"]       = strUser;
		param["password"]   = strPassword;
		param["actor"]      = actor;
		param["serverAddr"] = m_strAddr;
		bResult = excute(strCmd.c_str(), param, result, ext);
		if (bResult)
		{
		  m_strUser	    = strUser;
			m_strPassword = strPassword;
			m_iSession    = (int)result["session"];
		}
		else
		{
			_LOG(LOG_LEVEL_DEBUG, "login failed !");
		}
	}

	return bResult;
}



//get client session
int RpcCmd::getSession()
{
	return m_iSession;
}
