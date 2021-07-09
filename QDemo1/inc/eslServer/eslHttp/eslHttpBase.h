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

enum ESL_MEETMEMB_STATE
{
	ESL_MEMB_STATE_INIT = -1,	//初始状态
	ESL_MEMB_STATE_OFFLINE,		//离线
	ESL_MEMB_STATE_INVITING,	//入会中
	ESL_MEMB_STATE_ANSWER,		//会议中
	ESL_MEMB_STATE_NOANSWER,	//未应答
	ESL_MEMB_STATE_REJECT,		//拒绝
	ESL_MEMB_STATE_EXIT,		//离开
	ESL_MEMB_STATE_SILENCE,		//禁言
	ESL_MEMB_STATE_HOLDING,		//保持
	ESL_MEMB_STATE_SPEECHING,	//演讲
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