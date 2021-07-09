#include "eslHttpBase.h"

#include <iostream>
#include <sstream>

#include "IRztRequestMgr.h"
#include "IRztServerInfoMgr.h"

CEslHttpBase::CEslHttpBase()
{
}

CEslHttpBase::~CEslHttpBase()
{
}

//get request
bool CEslHttpBase::postHttpRequest(const std::string &strUrl, const QJsonObject &json, QJsonObject &jsonResult)
{
	bool bWriteLog = false;
	
	if (strUrl == "")
	{
		return false;
	}
	
	QJsonObject jsonReq(json);
	if(!jsonReq.contains("type"))
	{
		jsonReq.insert("type", 1);
	}
	
	std::string strPostUrl = strUrl;
	httpRequestJson(jsonResult, strPostUrl.c_str(), jsonReq);
	
	if (jsonResult.isEmpty())
	{
		return false;
	}
	
	if (jsonResult.value("code").toInt() != 0)
	{
		std::cout << "setDevCOnfig error:" << jsonResult.value("code").toInt();
		return false;
	}
	
	return true;
}

//post request
bool CEslHttpBase::postHttpRequest(const std::string &strUrl, const std::string &strParam, const QJsonObject &json, QJsonObject &jsonResult)
{
	bool bWriteLog = false;
	
	ObjectPtr<IRztServerInfoMgr> severInfo;
	STSvrInfo svrInfo = severInfo->getCurSvrInfo();
	
	std::string strSvrIp = svrInfo.strIP.toStdString();
	if (strSvrIp == "")
	{
		return false;
	}
	
	int iSvrPort = svrInfo.nHttpPort;
	if (iSvrPort <= 0)
	{
		iSvrPort = 80;
	}
	
	QJsonObject jsonReq(json);
	if(!jsonReq.contains("type"))
	{
		jsonReq.insert("type", 1);
	}
	
	std::ostringstream ostr;
	ostr << "http://" << strSvrIp << ":" << iSvrPort << strUrl << strParam;
	
	std::string strPostUrl = ostr.str();
	httpRequestJson(jsonResult, strPostUrl.c_str(), jsonReq);
	
	if (jsonResult.isEmpty())
	{
		return false;
	}
	
	if (jsonResult.value("code").toInt() != 0)
	{
		std::cout << "setDevCOnfig error:" << jsonResult.value("code").toInt();
		return false;
	}
	
	return true;
}