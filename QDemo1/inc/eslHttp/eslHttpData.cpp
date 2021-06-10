#include "eslHttpData.h"

CEslHttpData::CEslHttpData()
{
}

CEslHttpData::~CEslHttpData()
{
}

//获取系统配置
bool CEslHttpData::eslGetSysConfig(const QJsonObject &json, QJsonObject &jsonRet)
{
	std::string strUrl = "/api/v1/SystemConfig/getSystemConfig";
		
	std::string strParam;	
	postHttpRequest(strUrl, strParam, json, jsonRet);
	
	if (jsonRet.isEmpty())
	{
		return false;
	}
	
	return true;
}

//获取设备配置
bool CEslHttpData::eslGetDevConfig(const QJsonObject &json, QJsonObject &jsonRet)
{
	std::string strUrl = "/api/v1/upgrade/getdeviceinfo";
	
	std::string strParam;
	postHttpRequest(strUrl, strParam, json, jsonRet);
	
	if (jsonRet.isEmpty())
	{
		return false;
	}
	
	return true;
}

//设置设备配置
void CEslHttpData::eslSetDevConfig(const QJsonObject &json)
{
	std::string strUrl = "/api/v1/upgrade/uploadTerminalInfo";
	
	std::string strParam;
	QJsonObject jsonRet;
	
	postHttpRequest(strUrl, strParam, json, jsonRet);
	
	if (jsonRet.isEmpty())
	{
		return;
	}
	
	if (jsonRet.value("code").toInt() != 0)
	{
		cout << "setDevCOnfig error:" << jsonRet.value("code").toInt();
	}
}

//获取用户配置
bool CEslHttpData::eslGetUserConfig(const QJsonObject &json, QJsonObject &jsonRet)
{
	std::string strUrl = "/api/v1/user/getUserInfo";
	
	std::string strParam;
	postHttpRequest(strUrl, strParam, json, jsonRet);
	
	if (jsonRet.isEmpty())
	{
		return false;
	}
	
	return true;
}

//设置用户配置
void CEslHttpData::eslSetUserConfig(const QJsonObject &json)
{
	std::string strUrl = "/api/v1/user/editUserInfo";
	
	std::string strParam;
	QJsonObject jsonRet;
	
	postHttpRequest(strUrl, strParam, json, jsonRet);
	
	if (jsonRet.isEmpty())
	{
		return;
	}
	
	if (jsonRet.value("code").toInt() != 0)
	{
		cout << "setDevCOnfig error:" << jsonRet.value("code").toInt();
	}
}

//获取快捷通讯录
bool CEslHttpData::eslGetPageData(const QJsonObject &json, QJsonObject &jsonRet)
{
	bool folder = false;
	QJsonObject jsonObject(json);
	
	if (!jsonObject.contains("folder"))
	{
		folder = false;
	}
	else
	{
		if (jsonObject.value("folder").toString() == "0")
		{
			folder = false;
		}
		else
		{
			folder = true;
		}
	}
	
	std::string strUrl;
	jsonObject.remove("folder");
	
	if (folder)
	{
		strUrl = "/api/v1/book/getQuickBook";
	}
	else
	{
		strUrl = "/api/v1/book/getQuickBook_json";
	}
	
	std::string strParam;
	postHttpRequest(strUrl, strParam, json, jsonRet);
	
	if (jsonRet.isEmpty())
	{
		return false;
	}
	
	if (jsonRet.value("code").toInt() != 0)
	{
		cout << "GetPageData error:" << jsonRet.value("code").toInt();
		return false;
	}
	
	return true;
}

//获取共同通讯录
bool CEslHttpData::eslGetPublicContact(const QJsonObject &json, QJsonObject &jsonRet)
{
	bool file = false;
	QJsonObject jsonObject(json);
	
	if (!jsonObject.contains("file"))
	{
		file = false;
	}
	else
	{
		if (jsonObject.value("file").toString() == "0")
		{
			file = false;
		}
		else
		{
			file = true;
		}
	}
	
	std::string strUrl;
	jsonObject.remove("file");
	
	if (file)
	{
		strUrl = "/api/v1/book/getPublicBook";
	}
	else
	{
		strUrl = "/api/v1/book/getPublicBook_json";
	}
	
	std::string strParam;
	postHttpRequest(strUrl, strParam, json, jsonRet);
	
	if (jsonRet.isEmpty())
	{
		return false;
	}
	
	if (jsonRet.value("code").toInt() != 0)
	{
		cout << "GetPublicContact error:" << jsonRet.value("code").toInt();
	}
	
	return true;
}