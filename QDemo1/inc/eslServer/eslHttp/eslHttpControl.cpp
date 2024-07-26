#include "eslHttpControl.h"

#include "ISDKUtils.h"
#include "RztCommonUtils.h"
#include "RztEventHeader.h"

#include "IRztDevice.h"
#include "IRztSettingMgr.h"
#include "IRztRegisterNumber.h"
#include "IRztServerInfoMgr.h"
#include "IRztIpcController.h"
#include "IRztFaceDistinguishController.h"

CEslHttpControl::CEslHttpControl()
{
	//data对象指针
	m_pEslHttpData = new CEslHttpData;
	
	//call对象指针
	m_pEslHttpCall = new CEslHttpCall;
	
	//meet对象指针
	m_pEslHttpMeet = new CEslHttpMeet;
	
	//annc对象指针
	m_pEslHttpAnnc = new CEslHttpAnnc;
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
	
	if (m_pEslHttpMeet)
	{
		delete m_pEslHttpMeet;
		m_pEslHttpMeet = Q_NULLPTR;
	}
	
	if (m_pEslHttpAnnc)
	{
		delete m_pEslHttpAnnc;
		m_pEslHttpAnnc = Q_NULLPTR;
	}
}

//esl获取数据
bool CEslHttpControl::eslGetDataFromSrv(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	//获取设备配置
	if (!m_pEslHttpData->eslSetDevConfig(false, json))
	{
		return false;
	}
	
	//获取用户配置
	if (!m_pEslHttpData->eslSetUserConfig(false, json))
	{
		return false;
	}
	
	//获取公共通讯录
	//m_pEslHttpData->eslGetPublicContact(json);

	//获取快捷通讯录
	m_pEslHttpData->eslSetPageData(FileHandle_Get, json);
	
	//获取席位通讯录
	//m_pEslHttpData->eslSetSeatContact(0, json);
	
	return true;
}

//esl设置数据
bool CEslHttpControl::eslSetSrvData(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	//设置设备配置
	if (!m_pEslHttpData->eslSetDevConfig(true, json))
	{
		return false;
	}
	
	//设置用户配置
	if (!m_pEslHttpData->eslSetUserConfig(true, json))
	{
		return false;
	}
	
	return true;
}

//esl设置事件
void CEslHttpControl::eslSetUserEvent(const QJsonObject &json)
{
	bool bIsSeat = false;
	if (json.contains("seat"))
	{
		bIsSeat = json.value("seat").toBool();
	}

	std::string strUid = json["uid"].toString().toStdString();
	std::string strUserNum = json["user"].toString().toStdString();
	std::string strSvrIp = json["hostip"].toString().toStdString();
	
	ObjectPtr<ISDKUtils> sdkUtils;
	sdkUtils->sendHeartBeat(strUserNum.c_str());

	ObjectPtr<IRztSettingMgr> settingMgr;
	ObjectPtr<IRztIpcController> ipcController;
	
	if (bIsSeat)
	{
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
		jsonSeatLogin.insert("seatNumber", strUserNum.c_str());
		ipcController->sendIpcMsg(MsgType_SeatNumberLogined, true, 2000, jsonSeatLogin);

		//推荐通道 voip
		settingMgr->setValue(RztSettingKey::SKey_PreferredChannel, VC_Voip);
		settingMgr->flush();

		//
		ObjectPtr<IRztDevice> device;
		if (sdkUtils->initMediaModule(false))
		{
			STDeviceInfo info = device->getDeviceInfo();
			sdkUtils->setSoundCardInfo(info.lstTotalSoundCardCap, info.lstTotalSoundCardPlay);
		}

		//bindMgr
		ObjectPtr<IRztRegisterNumber> registerNumber;
		registerNumber->clearNumber();

		//register p2p, sip;
		sdkUtils->registerNumbersIP(strUserNum.c_str());

		//注册完号，要重新设置Media env
		sdkUtils->setMediaEnv();
	}
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

//获取meet对象指针
CEslHttpMeet* CEslHttpControl::eslGetMeetPtr() const
{
	return m_pEslHttpMeet;
}

//获取annc对象指针
CEslHttpAnnc* CEslHttpControl::eslGetAnncPtr() const
{
	return m_pEslHttpAnnc;
}
