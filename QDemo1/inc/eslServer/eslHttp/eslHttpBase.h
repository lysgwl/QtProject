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
	ESL_LOGIN_USER_EMPTY = 0,
	ESL_LOGIN_USER_TYPE,
	ESL_LOGIN_SEAT_TYPE,
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