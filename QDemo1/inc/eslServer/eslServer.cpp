#include "eslServer.h"

#include "ISDKUtils.h"
#include "IRztSettingMgr.h"

#include "IRztVsNet.h"
#include "IRztConnector.h"
#include "IRztConnectorMgr.h"

CEslServer::CEslServer()
{
	m_pHttpCtrl = new CEslHttpControl;
}

CEslServer::~CEslServer()
{
	if (m_pHttpCtrl)
	{
		delete m_pHttpCtrl;
		m_pHttpCtrl = Q_NULLPTR;
	}
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
	
	if (strUserNum == "" || strPasswd == "")
	{
		qRztInfo() << "login info is err!" << strUserNum.c_str() << strPasswd.c_str();
		return false;
	}
	
	int iSvrVsPort = 20000;
	int iSvrHttpPort = settingMgr->toInt(RztSettingKey::SKey_SvrPrimaryHttpPort);
	std::string strSvrIp = settingMgr->toString(RztSettingKey::SKey_SvrPrimaryIP).toStdString();
	
	QJsonObject jsonData;
	jsonData.insert("timeout", 3000);
	jsonData.insert("usernum", strUserNum.c_str());
	
	jsonData.insert("svrport", iSvrVsPort);
	jsonData.insert("svrip", strSvrIp.c_str());
	
	if (!connectSvr(jsonData))
	{
		qRztInfo() << "connector is failed";	
		addLastErr("连接服务器失败!");
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
		return false;
	}
	
	QJsonObject json;
	json.insert("user", strUserNum.c_str());
	json.insert("passwd", strPasswd.c_str());
	json.insert("token", jsonLogin["terminalId"].toInt());
	
	json.insert("seat", true);
	json.insert("vsport", iSvrVsPort);
	json.insert("httpport", iSvrHttpPort);
	json.insert("hostip", strSvrIp.c_str());
	
	CEslHttpData *pEslHttpData = m_pHttpCtrl->eslGetDataPtr();
	if (pEslHttpData != Q_NULLPTR)
	{
		//获取系统配置
		pEslHttpData->eslGetSysConfig(json);
	}
	
	//设置服务器数据
	m_pHttpCtrl->eslSetSrvData(json);
	
	//获取服务器数据
	m_pHttpCtrl->eslGetDataFromSrv(json);
	
	//设置运行事件
	m_pHttpCtrl->eslSetUserEvent(json);
	
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
	
	if (strSvrIp == "" || strUserNum == "")
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