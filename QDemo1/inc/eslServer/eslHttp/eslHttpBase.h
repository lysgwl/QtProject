#ifndef ESL_HTTP_BASE_H
#define ESL_HTTP_BASE_H

#include <sstream>
#include <string>

#include "STHeader.h"

#include "RztEnvDef.h"
#include "RztCommonUtils.h"
#include "RztDownLoadFile.h"

//登录用户类型
enum ESL_LOGINUSER_TYPE
{
	ESL_LOGIN_USER_TYPE,		//用户登录
	ESL_LOGIN_SEAT_TYPE,		//席位登录
};

//会议状态
enum ESL_MEETMEMB_STATE
{
	MEET_MEMB_STATE_INIT = -1,	//初始状态
	MEET_MEMB_STATE_OFFLINE,	//离线
	MEET_MEMB_STATE_INVITING,	//入会中
	MEET_MEMB_STATE_ANSWER,		//会议中
	MEET_MEMB_STATE_NOANSWER,	//未应答
	MEET_MEMB_STATE_REJECT,		//拒绝
	MEET_MEMB_STATE_EXIT,		//离开
	MEET_MEMB_STATE_KICKOUT,	//踢出
	MEET_MEMB_STATE_SILENCE,	//禁言
	MEET_MEMB_STATE_HOLDING,	//保持
	MEET_MEMB_STATE_SPEECHING,	//演讲
};

enum ESL_ANNCMEMB_STATE
{
	ANNC_MEMB_STATE_INIT = -1,
	ANNC_MEMB_STATE_OFFLINE,	//离线
	ANNC_MEMB_STATE_CALLING,	//呼叫中
	ANNC_MEMB_STATE_CONNECT,	//已连接
	ANNC_MEMB_STATE_SPEAKING,	//正在讲话
	ANNC_MEMB_STATE_NOANSWER,	//未应答
	ANNC_MEMB_STATE_HUNGUP,		//挂断
	ANNC_MEMB_STATE_KICKOUT,	//踢出
	ANNC_MEMB_STATE_REJECT,		//拒接
};

class CEslHttpBase
{
public:
	CEslHttpBase();
	virtual ~CEslHttpBase();
	
public:
	//get request
	bool postHttpRequest(const std::string &strUrl, const QJsonObject &json, QJsonObject &jsonResult);
	
	//post request
	bool postHttpRequest(const std::string &strUrl, const std::string &strParam, const QJsonObject &json, QJsonObject &jsonResult);
};

#endif