#include "eslHttpData.h"

CEslHttpData::CEslHttpData()
{
}

CEslHttpData::~CEslHttpData()
{
}

//////////////////////////////////////////////////////////////////////////
//esl系统配置
bool CEslHttpData::eslGetSysConfig(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	std::string strParam;
	std::string strUrl = "/api/v1/SystemConfig/getSystemConfig";
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, strParam, json, jsonRet))
	{
		return false;
	}
	
	eslSetSysData(jsonRet);
	return true;
}

//esl设备配置
bool CEslHttpData::eslSetDevConfig(bool bFlag, const QJsonObject &json)
{
	bool bResult = false;
	
	if (bFlag)
	{
		bResult = eslSetDevData(json);
	}
	else
	{
		bResult = eslGetDevData(json);
	}
	
	return bResult;
}

//esl用户配置
bool CEslHttpData::eslSetUserConfig(bool bFlag, const QJsonObject &json)
{
	bool bResult = false;
	
	if (bFlag)
	{
		bResult = eslSetUserData(json);
	}
	else
	{
		bResult = eslGetUserData(json);
	}
	
	return bResult;
}

//esl快捷通讯录
bool CEslHttpData::eslSetPageData(int iType, const QJsonObject &json)
{
	bool bResult = false;
	
	if (iType == FileHandle_Get)
	{
		bResult = eslGetPageData(json);
	}
	
	return bResult;
}

//esl公共通讯录
bool CEslHttpData::eslGetPublicContact(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	std::string strUrl;
	QJsonObject jsonPublic(json);
	
	bool file = false;
	if (!jsonPublic.contains("file"))
	{
		file = false;
	}
	else
	{
		if (jsonPublic.value("file").toString() == "0")
		{
			file = false;
		}
		else
		{
			file = true;
		}
	}
	
	if (file)
	{
		strUrl = "/api/v1/book/getPublicBook";
	}
	else
	{
		strUrl = "/api/v1/book/getPublicBook_json";
	}
	
	QJsonObject jsonRet;
	std::string strParam;
	if (!postHttpRequest(strUrl, strParam, jsonPublic, jsonRet))
	{
		return false;
	}
	
	eslSetPublicContact(jsonRet);
	return true;
}

//esl席位通讯录
bool CEslHttpData::eslSetSeatContact(int iType, const QJsonObject &json)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
//设置系统数据
void CEslHttpData::eslSetSysData(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return;
	}
	
	ObjectPtr<IRztSettingMgr> settingMgr;
	
	std::stringstream stream;
	if (json.contains("recordServerIp"))
	{//录播配置
		std::string strRecordIp = json.value("recordServerIp").toString().toStdString();
		int iRecordPort = json.value("recordServerPort").toInt();
		
		stream << strRecordIp << ":" << iRecordPort;
		std::string strRecordUrl = stream.str();
		
		settingMgr->setValue(RztSettingKey::SKey_RecordFileUrl, strRecordUrl.c_str());
	}
	
	if (json.contains("expires"))
	{//sip超时设置
		int iTimeOut = json.value("expires").toInt();
		settingMgr->setValue(RztSettingKey::SKey_SipExpiresTime, iTimeOut);
	}
}

//设置设备数据
bool CEslHttpData::eslSetDevData(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	bool bIsSeat = false;
	if (json.contains("seat"))
	{
		bIsSeat = json.value("seat").toBool();
	}
	
	ObjectPtr<IRztSettingMgr> settingMgr;
	std::string strEthName = settingMgr->toString(RztSettingKey::Skey_EtheName).toStdString();
	std::string strLocalIp = RztComUtilsInLine::readLocalIP(strEthName.c_str()).toStdString();
	
	std::string strUuId = settingMgr->toString(RztSettingKey::Skey_UUID).toStdString();
	std::string strDevAddr = RztCommonUtils::getDeviceId().toStdString();
	std::string strNumber = json.value("user").toString().toStdString();
	
	ObjectPtr<IRztAppStateController> appStateController;
	STPXOInfo pxoInfo = appStateController->pxoInfoEscape();
	std::string strPstnNum = (pxoInfo.strPXO).toStdString();
	
	QJsonObject jsonData;
	jsonData.insert("devuuid", strUuId);
	jsonData.insert("seatid", strUuId);
	
	if (bIsSeat)
	{
		jsonData.insert("seatnum", strNumber);
		jsonData.insert("usernum", "");
	}
	else
	{
		jsonData.insert("seatnum", "");
		jsonData.insert("usernum", strNumber);
	}
	
	jsonData.insert("pstn", strPstnNum);
	jsonData.insert("terminalip", strLocalIp);
	jsonData.insert("devmac", strDevAddr);
	jsonData.insert("devtype", 1);
	jsonData.insert("version", "");
	jsonData.insert("versionstate", 0);
	
	QJsonObject jsonDev(json);
	jsonDev.insert("data", jsonData);
	
	std::string strParam;
	std::string strUrl = "/api/v1/upgrade/uploadTerminalInfo";
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, strParam, jsonDev, jsonRet))
	{
		return false;
	}
	
	return true;
}

//获取设备数据
bool CEslHttpData::eslGetDevData(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	std::string strParam;
	std::string strUrl = "/api/v1/upgrade/getdeviceinfo";
	
	QJsonObject jsonDev(json);
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, strParam, jsonDev, jsonRet))
	{
		return false;
	}
	
	return true;
}

//设置用户数据
bool CEslHttpData::eslSetUserData(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	QJsonObject jsonUser(json);
	if (jsonUser.contains("name"))
	{
		if (jsonUser.value("name").toString().isEmpty())
		{
			jsonUser.remove("name");
		}
	}
	
	if (jsonUser.contains("password"))
	{
		if (jsonUser.value("password").toString().isEmpty())
		{
			jsonUser.remove("password");
		}
	}
	
	if (jsonUser.contains("transfernumber"))
	{
		if (jsonUser.value("transfernumber").toString().isEmpty())
		{
			jsonUser.remove("transfernumber");
		}
	}
	
	jsonUser.insert("extend", "");
	
	std::string strParam;
	std::string strUrl = "/api/v1/user/editUserInfo";
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, strParam, jsonUser, jsonRet))
	{
		return false;
	}
	
	return true;
}

//获取用户数据
bool CEslHttpData::eslGetUserData(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	std::string strParam;
	std::string strUrl = "/api/v1/user/getUserInfo";
	
	QJsonObject jsonUser(json);
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, strParam, jsonDev, jsonRet))
	{
		return false;
	}
	
	if (jsonRet.contains("transfernumber"))
	{//呼叫转移
		std::string strUserNum = jsonRet["transfernumber"].toString().toStdString();
		if (jsonRet["transferswitch"].toInt() == 0)
		{
			strUserNum = "";
		}
		
		ObjectPtr<IRztSettingMgr> settingMgr;
		settingMgr->setValue(RztSettingKey::SKey_CallDivert, strUserNum.c_str());
	}
	
	return true;
}

//获取快捷数据
bool CEslHttpData::eslGetPageData(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	std::string strUrl;
	QJsonObject jsonPage(json);
	
	bool folder = false;
	if (!jsonPage.contains("folder"))
	{
		folder = false;
	}
	else
	{
		if (jsonPage.value("folder").toString() == "0")
		{
			folder = false;
		}
		else
		{
			folder = true;
		}
	}
	
	if (folder)
	{
		strUrl = "/api/v1/book/getQuickBook";
	}
	else
	{
		strUrl = "/api/v1/book/getQuickBook_json";
	}
	
	QJsonObject jsonRet;
	std::string strParam;
	if (!postHttpRequest(strUrl, strParam, jsonPage, jsonRet))
	{
		return false;
	}
	
	QJsonObject objData = jsonRet["data"].toObject();
	if (objData.contains("fileUrl"))
	{
		std::stringstream stream;
		stream << RztFramework::getGlobalVariantInfo()->strDataPath.toStdString() << "/excel/short.xlsx";
		
		std::string strPath = stream.str();
		std::string strUrl = objData["fileUrl"].toString().toStdString();
		
		RztDownLoadFile downFile;
		if (downFile.downLoad(strUrl.c_str(), strPath.c_str()))
		{
			return;
		}
		
		ObjectPtr<IRztBasePageMgr> basepageMgr;
		basepageMgr->parseExcel();
	}
	
	return true;
}

//设置公共通讯录
void CEslHttpData::eslSetPublicContact(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return;
	}
	
	QJsonObject objData = json["data"].toObject();
	if (objData.contains("fileUrl"))
	{//下载公共通讯录
		std::string strDir = RztFramework::getGlobalVariantInfo()->strConfigPath.toStdString();
		
		std::stringstream stream;
		stream << strDir << ENV_PUBLICCONTACT.toStdString();
		
		std::string strPath = stream.str();
		std::string strUrl = objData["fileUrl"].toString().toStdString();
		
		ObjectPtr<IRztSettingMgr> settingMgr;
		settingMgr->setValue(RztSettingKey::SKey_PublicContactUrl, strUrl.c_str());
		
		RztDownLoadFile downFile;
		if (downFile.downLoad(strUrl.c_str(), strPath.c_str()))
		{
			return;
		}
		
		//QWriteLocker locker(&m_lockPublicContact);//文件锁定
		QJsonObject objContact = RztCommonUtils::readJsonFromFile(strPath.c_str());
		
		ObjectPtr<IRztPublicContactMgr> publicContactMgr;
		publicContactMgr->loadData(objContact);
	}
}