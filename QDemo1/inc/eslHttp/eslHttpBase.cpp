#include "eslHttpBase.h"

CEslHttpBase::CEslHttpBase()
{
}

CEslHttpBase::~CEslHttpBase()
{
}

bool CEslHttpBase::postHttpRequest(const std::string &strUrl, const std::string &strParam, const QJsonObject &json, QJsonObject &jsonResult)
{
	ObjectPtr<IRztServerInfoMgr> severInfo;
	STSvrInfo svrInfo = severInfo->getCurSvrInfo();
	
	std::ostringstream ostr;
	ostr << "http://" << svrInfo.strIP << svrInfo.nHttpPort << strUrl << strParam;
	
	std::string strPostUrl = ostr.str();
	httpRequestJson(jsonResult, strPostUrl.c_str(), json);
	
	if (jsonResult.isEmpty())
	{
		return false;
	}
	
	if (jsonResult.value("code").toInt() != 0)
	{
		cout << "setDevCOnfig error:" << jsonResult.value("code").toInt();
		return false;
	}
	
	return true;
}