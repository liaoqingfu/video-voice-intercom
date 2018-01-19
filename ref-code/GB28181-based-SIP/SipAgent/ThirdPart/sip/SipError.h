#ifndef _ERROR_H
#define _ERROR_H


enum errorCode
{
	SIP_SUCCESS = 200,
	SIP_NOTIMPLEMENT = 501,    //请求方法不支持
	SIP_NOTAUTHENTICATION = 401, //REGISTER 未鉴权

	//上层业务层执行错误
	SIP_COUNT_LIMIT  = 701,  // 注册上限: 目的联网单元上的可注册单元已达到最大值
	SIP_VALID_PROXY  = 702,  // 未授权的联网单元: 源联网单元注册登记信息不符合系统设置的接入联网条件
	SIP_LACK_INFO    = 713,  // DDCP信息不全: DDCP中的信息不全（必选字段不存在）

	SIP_BADREQUEST   = 400,

	//sip 执行期间的错误返回值定义
	SIP_OK  = 0,                 //执行成功
	SIP_REQUEST_FAILED = -1,     //sip请求执行失败
	SIP_REQUEST_TIMEOUT = -100,  //sip请求超时
	SIP_INIT_ERROR     = -2,     //sip库初始化失败

};


typedef struct _tagSipError
{
	errorCode code;
	char*     explain;
}SipError;


//SipError er[] = 
//{
//};



#endif