#ifndef ESL_HTTP_BASE_H
#define ESL_HTTP_BASE_H

#include "STHeader.h"

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