#ifndef ESL_HTTP_BASE_H
#define ESL_HTTP_BASE_H

class CEslHttpBase
{
public:
	CEslHttpBase();
	virtual ~CEslHttpBase();
	
public:
	bool postHttpRequest(const std::string &strUrl, const std::string &strParam, const QJsonObject &json, QJsonObject &jsonResult);
};

#endif