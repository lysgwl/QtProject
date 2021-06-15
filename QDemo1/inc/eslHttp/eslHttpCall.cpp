#include "eslHttpCall.h"

CEslHttpCall::CEslHttpCall()
{
}

CEslHttpCall::~CEslHttpCall()
{
}

//////////////////////////////////////////////////////////////////////////
//设置呼叫记录
bool CEslHttpCall::eslSetCallLog(bool bIsUpload, const QJsonObject &json)
{
	bool bResult = false;
	
	if (bIsUpload)
	{
		bResult = eslUploadCallLog(json);
	}
	else
	{
		bResult = eslGetCallLog(json);
	}
	
	return bResult;
}

//获取电台列表
bool CEslHttpCall::eslGetRadioList(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	return true;
}

//////////////////////////////////////////////////////////////////////////
//获取呼叫记录
bool CEslHttpCall::eslGetCallLog(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	std::string strParam;
	std::string strUrl = "/api/v1/call/getClientCall";
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, strParam, json, jsonRet))
	{
		return false;
	}
	
	return true;
}

//上传呼叫记录
bool CEslHttpCall::eslUploadCallLog(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	std::string strParam;
	std::string strUrl = "/api/v1/call/uploadClientCall";
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, strParam, json, jsonRet))
	{
		return false;
	}
	
	return true;
}