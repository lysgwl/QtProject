#include "eslHttpData.h"

#include <sstream>
#include <string>

#include "RztEnvDef.h"
#include "RztCommonUtils.h"
#include "RztDownLoadFile.h"

#include "IRztSettingMgr.h"
#include "RztComUtilsInLine.h"

#include "IRztBasePageMgr.h"
#include "IRztCallNumberMgr.h"
#include "IRztServerInfoMgr.h"
#include "IRztPublicContactMgr.h"
#include "IRztAppStateController.h"

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
	
	int iVsPort = json["vsport"].toInt();
	int iHttpPort = json["httpport"].toInt();
	
	std::string strHostIp = json["hostip"].toString().toStdString();
	if (strHostIp == "")
	{
		return false;
	}
	
	QJsonObject jsonConfig(json);
	jsonConfig.insert("type", 0);
	
	std::ostringstream ostr;
	std::string strUrl = "/api/v1/SystemConfig/getSystemConfig";

	ostr << "http://" << strHostIp << ":" << iHttpPort << strUrl;
	std::string strPostUrl = ostr.str();
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strPostUrl, jsonConfig, jsonRet))
	{
		return false;
	}
	
	QJsonObject jsonData(jsonRet["data"].toObject());
	if (jsonData.isEmpty())
	{
		return false;
	}
	
	if (!jsonData.contains("hostip"))
	{
		jsonData.insert("hostip", strHostIp.c_str());
	}
	
	if (!jsonData.contains("vsport"))
	{
		jsonData.insert("vsport", iVsPort);
	}
	
	if (!jsonData.contains("httpport"))
	{
		jsonData.insert("httpport", iHttpPort);
	}
	
	eslSetSysData(jsonData);
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
bool CEslHttpData::eslSetPublicContact(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	std::string strUrl;
	QJsonObject jsonPublic(json);
	jsonPublic.insert("type", 0);
	
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
	if (!postHttpRequest(strUrl, "", jsonPublic, jsonRet))
	{
		return false;
	}
	
	GetPublicContact(jsonRet);
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
	
	std::stringstream stream;
	ObjectPtr<IRztSettingMgr> settingMgr;
	
	if (json.contains("hostip"))
	{//服务器配置
		QJsonObject localSvr;
		localSvr.insert("ip", json["hostip"].toString());
		localSvr.insert("vsPort", std::to_string(json["vsport"].toInt()).c_str());
		localSvr.insert("httpPort", std::to_string(json["httpport"].toInt()).c_str());
		localSvr.insert("sipPort", std::to_string(json["sipPort"].toInt()).c_str());
		
		localSvr.insert("sbcIp", json["sbcip"].toString());
		localSvr.insert("sbcPort", std::to_string(json["sbcPort"].toInt()).c_str());
		localSvr.insert("sbcMediaPort", std::to_string(json["sbcmediaport"].toInt()).c_str());
	
		QJsonObject jsonSvr;
		jsonSvr.insert("localServer", localSvr);
		
		QJsonArray jsonArray;
		jsonSvr.insert("standbyServer", jsonArray);
		
		ObjectPtr<IRztServerInfoMgr> severInfoMgr;
		severInfoMgr->loadServerInfo(jsonSvr);
		
		STSvrInfo svrInfo = severInfoMgr->getCurSvrInfo();
		settingMgr->setValue(RztSettingKey::SKey_GJB4908SvrPort, svrInfo.n4908SvrPort);
		settingMgr->setValue(RztSettingKey::SKey_GJB4908SvrIP, svrInfo.str4908IP);
		settingMgr->setValue(RztSettingKey::SKey_GJB4908LocalPort, svrInfo.n4908LocalPort);
		settingMgr->setValue(RztSettingKey::SKey_SvrPowerOnUDPPort, svrInfo.nPoweronPort);
		settingMgr->setValue(RztSettingKey::SKey_Enable28, svrInfo.bEnable28);
		settingMgr->flush();
	}
	
	if (json.contains("recordServerIp"))
	{//录播配置
		if (json["recordServerIp"].toString() != "")
		{
			int iRecordPort = json.value("recordServerPort").toInt();
			std::string strRecordIp = json.value("recordServerIp").toString().toStdString();
			if (strRecordIp == "localhost")
			{
				strRecordIp = "127.0.0.1";
			}
			
			stream << strRecordIp << ":" << iRecordPort;
			std::string strRecordUrl = stream.str();
		
			settingMgr->setValue(RztSettingKey::SKey_RecordFileUrl, strRecordUrl.c_str());
		}
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
	jsonData.insert("devuuid", strUuId.c_str());
	jsonData.insert("seatid", strUuId.c_str());
	
	if (bIsSeat)
	{
		jsonData.insert("seatnum", strNumber.c_str());
		jsonData.insert("usernum", "");
	}
	else
	{
		jsonData.insert("seatnum", "");
		jsonData.insert("usernum", strNumber.c_str());
	}
	
	jsonData.insert("pstn", strPstnNum.c_str());
	jsonData.insert("terminalip", strLocalIp.c_str());
	jsonData.insert("devmac", strDevAddr.c_str());
	jsonData.insert("devtype", 1);
	jsonData.insert("version", "");
	jsonData.insert("versionstate", 0);
	
	QJsonObject jsonDev(json);
	jsonDev.insert("type", 0);
	jsonDev.insert("data", jsonData);
	
	std::string strUrl = "/api/v1/upgrade/uploadTerminalInfo";
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonDev, jsonRet))
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
	
	QJsonObject jsonDev(json);
	jsonDev.insert("type", 0);
	std::string strUrl = "/api/v1/upgrade/getdeviceinfo";
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonDev, jsonRet))
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
	
	jsonUser.insert("type", 0);
	jsonUser.insert("extend", "");

	std::string strUrl = "/api/v1/user/editUserInfo";
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonUser, jsonRet))
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
	
	QJsonObject jsonUser(json);
	jsonUser.insert("type", 0);
	std::string strUrl = "/api/v1/user/getUserInfo";
	
	bool bIsSeat = false;
	if (jsonUser.contains("seat"))
	{
		bIsSeat = jsonUser.value("seat").toBool();
	}
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonUser, jsonRet))
	{
		return false;
	}
	
	QJsonObject jsonData(jsonRet["data"].toObject());
	if (jsonData.isEmpty())
	{
		return false;
	}
	
	if (jsonData.contains("transfernumber"))
	{//呼叫转移
		std::string strUserNum = jsonData["transfernumber"].toString().toStdString();
		if (jsonData["transferswitch"].toInt() == 0)
		{
			strUserNum = "";
		}
		
		ObjectPtr<IRztSettingMgr> settingMgr;
		settingMgr->setValue(RztSettingKey::SKey_CallDivert, strUserNum.c_str());
	}
	
	if (jsonData.contains("name"))
	{//用户昵称
		STNumber numberNew;
		numberNew.type = bIsSeat ? NT_Seat : NT_Staff;
		numberNew.gma = bIsSeat ? GMA_SeatNumber : GMA_UserNumber;
		numberNew.strUID = jsonData["devuuid"].toString();
		numberNew.strUIDPwd = jsonUser["passwd"].toString();
		numberNew.strVsCallNumber = jsonUser["user"].toString();
		numberNew.strVsPassword = jsonUser["passwd"].toString();
		
		QJsonObject jsonLogin;
		jsonLogin.insert("DispatcherName", jsonData["name"].toString());
		jsonLogin.insert("DispatcherNameAlias", jsonData["name"].toString());
		jsonLogin.insert("DispatcherUserAlias", jsonData["name"].toString());
		
		QJsonObject jsonNum;
		jsonNum.insert("terminalId", jsonUser["token"].toInt());
		jsonNum.insert("LoginId", jsonLogin);
		
		ObjectPtr<IRztCallNumberMgr> callNumberMgr;
		callNumberMgr->addNumber(numberNew, jsonNum);
		callNumberMgr->setActiveNumber(jsonUser["user"].toString());
	}
	
	ObjectPtr<IRztSettingMgr> settingMgr;
	settingMgr->setValue(RztSettingKey::SKey_ConvergeOpen, jsonData["sbcswitch"].toInt());
	
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
	jsonPage.insert("type", 0);
	
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
	if (!postHttpRequest(strUrl, "", jsonPage, jsonRet))
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
			return false;
		}
		
		ObjectPtr<IRztBasePageMgr> basepageMgr;
		basepageMgr->parseExcel();
	}
	
	return true;
}

//设置公共通讯录
void CEslHttpData::GetPublicContact(const QJsonObject &json)
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