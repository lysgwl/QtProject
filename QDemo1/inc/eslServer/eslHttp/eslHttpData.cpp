#include "eslHttpData.h"

#include "IRztDBMgr.h"
#include "IRztSettingMgr.h"
#include "RztComUtilsInLine.h"

#include "IRztBasePageMgr.h"
#include "IRztCallNumberMgr.h"
#include "IRztServerInfoMgr.h"
#include "IRztPublicContactMgr.h"
#include "IRztSystemSnapShotMgr.h"
#include "IRztAppStateController.h"

CEslHttpData::CEslHttpData()
{
}

CEslHttpData::~CEslHttpData()
{
}

//////////////////////////////////////////////////////////////////////////
//esl系统配置
bool CEslHttpData::eslGetSysConfig(const QJsonObject &json, QJsonObject &jsonValue)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	int iHttpPort = json["httpport"].toInt();
	std::string strHostIp = json["hostip"].toString().toStdString();
	if (strHostIp == "")
	{
		return false;
	}
	
	std::string strUrl = "/api/v1/SystemConfig/getSystemConfig";

	std::ostringstream ostr;
	ostr << "http://" << strHostIp << ":" << iHttpPort << strUrl;
	std::string strPostUrl = ostr.str();

	QJsonObject jsonConfig;
	jsonConfig.insert("uid", json["uid"].toString());
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strPostUrl, jsonConfig, jsonRet))
	{
		return false;
	}
	
	jsonValue = jsonRet["data"].toObject();
	if (jsonValue.isEmpty())
	{
		return false;
	}
	
	eslSetSysData(json, jsonValue);
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
	
	bool file = false;
	if (!json.contains("file"))
	{
		file = false;
	}
	else
	{
		if (json.value("file").toInt() == 0)
		{
			file = false;
		}
		else
		{
			file = true;
		}
	}
	
	std::string strUrl;
	if (file)
	{
		strUrl = "/api/v1/book/getPublicBook";
	}
	else
	{
		strUrl = "/api/v1/book/getPublicBook_json";
	}

	QJsonObject jsonPublic;
	jsonPublic.insert("user", json["user"].toString());
	jsonPublic.insert("token", json["token"].toString());
	
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
void CEslHttpData::eslSetSysData(const QJsonObject &json, const QJsonObject &jsonData)
{
	std::stringstream stream;
	ObjectPtr<IRztSettingMgr> settingMgr;

	if (json.contains("hostip"))
	{//服务器配置
		QJsonObject localSvr;
		localSvr.insert("ip", json["hostip"].toString());
		localSvr.insert("httpPort", std::to_string(json["httpport"].toInt()).c_str());
		localSvr.insert("vsPort", std::to_string(jsonData["tcp_port"].toInt()).c_str());
		localSvr.insert("sipPort", std::to_string(jsonData["sipPort"].toInt()).c_str());
		
		localSvr.insert("sbcIp", jsonData["sbcip"].toString());
		localSvr.insert("sbcPort", std::to_string(jsonData["sbcPort"].toInt()).c_str());
		localSvr.insert("sbcMediaPort", std::to_string(jsonData["sbcmediaport"].toInt()).c_str());
		
		QJsonObject jsonSvr;
		jsonSvr.insert("localServer", localSvr);
		
		QJsonArray jsonArray;
		jsonSvr.insert("standbyServer", jsonArray);
		
		ObjectPtr<IRztServerInfoMgr> severInfoMgr;
		severInfoMgr->loadServerInfo(jsonSvr);
		
		//getParamFromServer
		STSvrInfo svrInfo = severInfoMgr->getCurSvrInfo();
		settingMgr->setValue(RztSettingKey::SKey_GJB4908SvrPort, svrInfo.n4908SvrPort);
		settingMgr->setValue(RztSettingKey::SKey_GJB4908SvrIP, svrInfo.str4908IP);
		settingMgr->setValue(RztSettingKey::SKey_GJB4908LocalPort, svrInfo.n4908LocalPort);
		settingMgr->setValue(RztSettingKey::SKey_SvrPowerOnUDPPort, svrInfo.nPoweronPort);
		settingMgr->setValue(RztSettingKey::SKey_Enable28, svrInfo.bEnable28);
	}
	
	if (jsonData.contains("recordServerIp"))
	{//录播配置
		if (jsonData["recordServerIp"].toString() != "")
		{
			int iRecordPort = jsonData.value("recordServerPort").toInt();
			std::string strRecordIp = jsonData.value("recordServerIp").toString().toStdString();
			if (strRecordIp == "localhost")
			{
				strRecordIp = "127.0.0.1";
			}
			
			stream << strRecordIp << ":" << iRecordPort;
			std::string strRecordUrl = stream.str();
			
			settingMgr->setValue(RztSettingKey::SKey_RecordFileUrl, strRecordUrl.c_str());
		}
	}
	
	if (jsonData.contains("expires"))
	{//sip超时设置
		int iTimeOut = jsonData.value("expires").toInt();
		
		settingMgr->setValue(RztSettingKey::SKey_SipExpiresTime, iTimeOut);
	}
	
	//号码范围
	{
		//getCallNumberAlgorithm
		QJsonObject jsonValue;
		jsonValue.insert("fixedNum", jsonData["numberRange"].toString()); //固定电话号码范围
		jsonValue.insert("scheduleUserNum", ""); //调度电话号码范围
		jsonValue.insert("staticNum", jsonData["meetingNumRange"].toString()); //私人会议号码范围
		jsonValue.insert("talkBackAccessNum", ""); //移动对讲组号码范围
		jsonValue.insert("radioNum", jsonData["atisNumRange"].toString()); //通播号码范围
		jsonValue.insert("cameraMonitorNum", ""); //视频监控号码范围
		jsonValue.insert("manyRadioUserNum", ""); //电台号码范围
		
		ObjectPtr<IRztCallNumberMgr> callNumMgr;
		callNumMgr->setAlgorithm(jsonValue);
		
		ObjectPtr<IRztDBMgr> dbMgr;
		dbMgr->writeGlobalInfo(GlobalInfoType_CallAlgorithm, jsonData);
	}
	
	settingMgr->flush();
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

	QJsonObject jsonData;
	
	ObjectPtr<IRztSettingMgr> settingMgr;
	std::string strEthName = settingMgr->toString(RztSettingKey::Skey_EtheName).toStdString();
	std::string strLocalIp = RztComUtilsInLine::readLocalIP(strEthName.c_str()).toStdString();
	std::string strDevAddr = RztCommonUtils::getDeviceId().toStdString();

	std::string strUuId = json.value("devuid").toString().toStdString();
	std::string strNumber = json.value("user").toString().toStdString();
	if (strNumber != "")
	{
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
	}
	
	ObjectPtr<IRztAppStateController> appStateController;
	STPXOInfo pxoInfo = appStateController->pxoInfoEscape();
	std::string strPstnNum = (pxoInfo.strPXO).toStdString();
	if (strPstnNum != "")
	{
		jsonData.insert("pstn", strPstnNum.c_str());
	}
	
	jsonData.insert("devuuid", strUuId.c_str());
	jsonData.insert("seatid", strUuId.c_str());
	
	jsonData.insert("terminalip", strLocalIp.c_str());
	jsonData.insert("devmac", strDevAddr.c_str());
	jsonData.insert("devtype", 1);

	jsonData.insert("version", "");
	jsonData.insert("versionstate", 0);
	
	QJsonObject jsonDev;
	jsonDev.insert("user", json["user"].toString());
	jsonDev.insert("token", json["token"].toString());
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
	
	QJsonObject jsonDev;
	jsonDev.insert("user", json["user"].toString());
	jsonDev.insert("token", json["token"].toString());
	jsonDev.insert("devuuid", json["devuid"].toString());

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
	
	QJsonObject jsonUser;
	jsonUser.insert("user", json["user"].toString());
	jsonUser.insert("token", json["token"].toString());
	jsonUser.insert("extend", "");
	
	if (json.contains("name"))
	{
		if (json.value("name").toString().isEmpty())
		{
			jsonUser.insert("name", json["name"].toString());
		}
	}
	
	if (json.contains("password"))
	{
		if (json.value("password").toString().isEmpty())
		{
			jsonUser.insert("password", json["password"].toString());
		}
	}
	
	if (json.contains("transfernumber"))
	{
		if (json.value("transfernumber").toString().isEmpty())
		{
			jsonUser.insert("transfernumber", json["transfernumber"].toString());
		}
	}
	
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
	
	bool bIsSeat = false;
	if (json.contains("seat"))
	{
		bIsSeat = json.value("seat").toBool();
	}

	std::string strUserNum = json["user"].toString().toStdString();
	std::string strPasswd = json["passwd"].toString().toStdString();

	std::string strUid = json["uid"].toString().toStdString();
	std::string strUidPasswd = json["uidpasswd"].toString().toStdString();
	std::string strToken = json["token"].toString().toStdString();
	
	QJsonObject jsonUser;
	jsonUser.insert("user", strUserNum.c_str());
	jsonUser.insert("token", strToken.c_str());

	std::string strUrl = "/api/v1/user/getUserInfo";

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
	
	ObjectPtr<IRztSettingMgr> settingMgr;
	if (jsonData.contains("transfernumber"))
	{//呼叫转移
		std::string strUserNum = jsonData["transfernumber"].toString().toStdString();
		if (jsonData["transferswitch"].toInt() == 0)
		{
			strUserNum = "";
		}
		
		settingMgr->setValue(RztSettingKey::SKey_CallDivert, strUserNum.c_str());
	}
	
	if (jsonData.contains("name"))
	{//用户昵称
		std::string strUserName = jsonData["name"].toString().toStdString();
	
		STNumber numberNew;
		numberNew.type = bIsSeat ? NT_Seat : NT_Staff;
		numberNew.gma = bIsSeat ? GMA_SeatNumber : GMA_UserNumber;
		numberNew.strUID = strUid.c_str();
		numberNew.strUIDPwd = strUidPasswd.c_str();
		numberNew.strVsCallNumber = strUserNum.c_str();
		numberNew.strVsPassword = strPasswd.c_str();
		
		if (strUserName == "")
		{
			strUserName = strUserNum;
		}
		
		QJsonObject jsonLogin;
		jsonLogin.insert("DispatcherName", strUserName.c_str());
		jsonLogin.insert("DispatcherNameAlias", strUserName.c_str());
		jsonLogin.insert("DispatcherUserAlias", strUserName.c_str());
		
		QJsonObject jsonNum;
		jsonNum.insert("terminalId", std::stoi(strToken));
		jsonNum.insert("LoginId", jsonLogin);
		
		ObjectPtr<IRztCallNumberMgr> callNumberMgr;
		callNumberMgr->addNumber(numberNew, jsonNum);
		callNumberMgr->setActiveNumber(strUserNum.c_str());

		if (!bIsSeat)
		{
			ObjectPtr<IRztSystemSnapShotMgr> systemSnapShot;
			systemSnapShot->setUserNumber(numberNew);
		}
	}
	
	if (bIsSeat)
	{
		settingMgr->setValue(RztSettingKey::SKey_ConvergeOpen, jsonData["sbcswitch"].toInt());
	}
	else
	{
		settingMgr->setValue(RztSettingKey::SKey_UserNumber, strUserNum.c_str());
		settingMgr->setValue(RztSettingKey::SKey_UserPassword, strPasswd.c_str());

		settingMgr->setValue(RztSettingKey::Skey_UserNumberUUID, strUid.c_str());
		settingMgr->setValue(RztSettingKey::Skey_UserNumberUUIDPwd, strUidPasswd.c_str());
	}
	
	settingMgr->flush();
	return true;
}

//获取快捷数据
bool CEslHttpData::eslGetPageData(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	bool folder = false;
	if (!json.contains("folder"))
	{
		folder = false;
	}
	else
	{
		if (json.value("folder").toString() == "0")
		{
			folder = false;
		}
		else
		{
			folder = true;
		}
	}
	
	std::string strUrl;
	if (folder)
	{
		strUrl = "/api/v1/book/getQuickBook";
	}
	else
	{
		strUrl = "/api/v1/book/getQuickBook_json";
	}

	QJsonObject jsonPage;
	jsonPage.insert("user", json["user"].toString());
	jsonPage.insert("token", json["token"].toString());
	
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
		if (!downFile.downLoad(strUrl.c_str(), strPath.c_str()))
		{
			return;
		}
		
		//QWriteLocker locker(&m_lockPublicContact);//文件锁定
		QJsonObject objContact = RztCommonUtils::readJsonFromFile(strPath.c_str());
		
		ObjectPtr<IRztPublicContactMgr> publicContactMgr;
		publicContactMgr->loadData(objContact);
	}
}