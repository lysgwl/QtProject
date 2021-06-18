#include "eslHttpControl.h"

#include "RztCommonUtils.h"
#include "RztEventHeader.h"

#include "IRztSettingMgr.h"
#include "IRztServerInfoMgr.h"
#include "IRztIpcController.h"
#include "IRztFaceDistinguishController.h"

CEslHttpControl::CEslHttpControl()
{
	//data对象指针
	m_pEslHttpData = new CEslHttpData;
	
	//call对象指针
	m_pEslHttpCall = new CEslHttpCall;
}

CEslHttpControl::~CEslHttpControl()
{
	if (m_pEslHttpData)
	{
		delete m_pEslHttpData;
		m_pEslHttpData = Q_NULLPTR;
	}
	
	if (m_pEslHttpCall)
	{
		delete m_pEslHttpCall;
		m_pEslHttpCall = Q_NULLPTR;
	}
}

//esl获取数据
void CEslHttpControl::eslGetDataFromSrv(QJsonObject &json)
{
	if (json.isEmpty())
	{
		return;
	}
	
	//获取设备配置
	m_pEslHttpData->eslSetDevConfig(false, json);
	
	//获取用户配置
	m_pEslHttpData->eslSetUserConfig(false, json);
	
	//获取快捷通讯录
	//m_pEslHttpData->eslSetPageData(FileHandle_Get, json);
	
	//获取公共通讯录
	//m_pEslHttpData->eslSetPublicContact(json);
	
	//获取席位通讯录
	//m_pEslHttpData->eslSetSeatContact(0, json);
}

//esl设置数据
void CEslHttpControl::eslSetSrvData(QJsonObject &json)
{
	if (json.isEmpty())
	{
		return;
	}
	
	//设置设备配置
	m_pEslHttpData->eslSetDevConfig(true, json);
	
	//设置用户配置
	m_pEslHttpData->eslSetUserConfig(true, json);
}

//esl设置事件
void CEslHttpControl::eslSetUserEvent(QJsonObject &json)
{
	ObjectPtr<IRztServerInfoMgr> severInfo;
	STSvrInfo svrInfo = severInfo->getCurSvrInfo();
	
	std::string strSvrIp = svrInfo.strIP.toStdString();
	if  (strSvrIp == "")
	{
		return;
	}
	
	//ntp 对时
	RztCommonUtils::ntpToServer(strSvrIp.c_str());
	
	//人脸sdk初始化
	std::thread([=](){
		safeCallInterface(IRztFaceDistinguishController, initFacePlugin());
	}).detach();
	
	//emit sglLoginStateChanged(true);//切到主界面
    qRztEmitEvent(RztEventKey::event_login_loginChange, true);
	
	//通知monitor
	QJsonObject jsonSeatLogin;
	jsonSeatLogin.insert("seatNumber", json["user"].toString());
	
	ObjectPtr<IRztIpcController> ipcController;
	ipcController->sendIpcMsg(MsgType_SeatNumberLogined, true, 2000, jsonSeatLogin);
	
	//推荐通道 voip
	ObjectPtr<IRztSettingMgr> settingMgr;
    settingMgr->setValue(RztSettingKey::SKey_PreferredChannel, VC_Voip);
	settingMgr->flush();
}

//获取data对象指针
CEslHttpData* CEslHttpControl::eslGetDataPtr() const
{
	return m_pEslHttpData;
}

//获取call对象指针
CEslHttpCall* CEslHttpControl::eslGetCallPtr() const
{
	return m_pEslHttpCall;
}