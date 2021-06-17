#include "eslServer.h"

CEslServer::CEslServer()
{
}

CEslServer::~CEslServer()
{
}

CEslServer& CEslServer::Instance()
{
	static CEslServer inst;
	return inst;
}

//////////////////////////////////////////////////////////////////////////
//是否开启服务
bool CEslServer::isEslServer()
{
	return true;
}

//登录用户
bool CEslServer::loginUser(int iType)
{
	bool bResult = false;
	
	if (iType == 0)
	{
		bResult = loginSeatNumber();
	}
	else
	{
		bResult = loginUserNumber();
	}
	
	return bResult;
}

//登录席位号码
bool CEslServer::loginSeatNumber()
{
	ObjectPtr<IRztSettingMgr> settingMgr;
	std::string strUserNum = settingMgr->toString(RztSettingKey::Skey_SeatNumber).toStdString();
	std::string strPasswd = settingMgr->toString(RztSettingKey::Skey_SeatPwd).toStdString();
	
	std::string strSvrIp = settingMgr->toString(RztSettingKey::SKey_SvrPrimaryIP);
	int iSvrPort = settingMgr->toInt(RztSettingKey::SKey_SvrPrimaryHttpPort);
	
	if (strUserNum.isEmpty() || strPasswd.isEmpty())
	{
		qRztInfo() << "login info is err!" << strUserNum.c_str() << strPasswd.c_str();
		
		stateSleep(3000);
		return false;
	}
	
	QJsonObject jsonData;
	jsonData.insert("timeout", 3000);
	jsonData.insert("usernum", strUserNum.c_str());
	
	jsonData.insert("svrport", iSvrPort);
	jsonData.insert("svrip", strSvrIp.c_str());
	
	if (!connectSvr(jsonData))
	{
		qRztInfo() << "connector is failed";	
		addLastErr("连接服务器失败!");
		
		stateSleep(3000);
		return false;
	}
	
	ObjectPtr<ISDKUtils> sdkUtils;
	ObjectPtr<IRztConnectorMgr> connectorMgr;
	
	QJsonObject jsonLogin;
	if (!sdkUtils->loginVs(jsonLogin, strUserNum.c_str(), strPasswd.c_str()))
	{
		qRztInfo() << "login is failed";
		addLastErr("登录服务器失败！");
		
		connectorMgr->releaseConnector(strUserNum.c_str());
		stateSleep(2000);
		return false;
	}
	
	return true;
}

//登录用户号码
bool CEslServer::loginUserNumber()
{
	return true;
}

//连接服务器
bool CEslServer::connectSvr(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	int iTimeout = json["timeout"].toInt();
	int iSvrPort = json["svrport"].toInt();
	std::string strSvrIp = json["svrip"].toString().toStdString();
	std::string strUserNum = json["usernum"].toString().toStdString();
	
	if (strSvr.IsEmpty() || strUserNum.IsEmpty())
	{
		return false;
	}
	
	ObjectPtr<IRztConnectorMgr> connectorMgr;
	
	//connnect vs
	IRztConnector* connector = connectorMgr->getConnector(strUserNum.c_str());
	if (connector == Q_NULLPTR)
	{
		ObjectPtr<IRztVsNet> vsNet;
		
		connector = vsNet->createConnector(strSvrIp.c_str(), iSvrPort);
		connector->setVsCallNum(strUserNum.c_str());
	}
	
	if (connector == Q_NULLPTR)
	{
		qRztInfo() << "malloc is failed";
        return false;
	}
	
	if (!connector->connectSvr(iTimeout))
	{
		delete connector;
		qRztInfo() << "connector is failed";
        return false;
	}
	
	connectorMgr->addConnector(strUserNum.c_str(), connector);
    return true;
}