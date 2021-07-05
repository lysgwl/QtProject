#include "eslServer.h"

#include "ISDKUtils.h"
#include "IRztSettingMgr.h"

#include "IRztVsNet.h"
#include "IRztConnector.h"
#include "IRztConnectorMgr.h"

#include "ISDKMeeting.h"
#include "IRztCreateMeetingCondition.h"

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
	ObjectPtr<IRztSettingMgr> settingMgr;
	
	bool bFlag = settingMgr->toBool(RztSettingKey::SKey_EslOpen);
	if (!bFlag)
	{
		return false;
	}
	
	return true;
}

//登录用户
bool CEslServer::loginUser(int iType)
{
	bool bResult = false;
	
	switch (iType)
	{
	case ESL_LOGIN_USER_TYPE:
		bResult = loginUserNumber();
		break;
		
	case ESL_LOGIN_SEAT_TYPE:
		bResult = loginSeatNumber();
		break;
		
	default:
		addLastErr("登录类型传输错误!");
		break;
	}

	return bResult;
}

//创建会议
bool CEslServer::createMeeting(STMeetingDetailInfo &detailInfo, const QVector<QString> &vecMember)
{
	CEslHttpMeet *pEslHttpMeet = m_pHttpCtrl->eslGetMeetPtr();
	if (pEslHttpMeet == Q_NULLPTR)
	{
		return false;
	}
	
	ObjectPtr<IRztCreateMeetingCondition> meetingCreate;
	if (!meetingCreate->canCreate())
    {
        addLastErr("会议操作太频繁，请稍侯!");
        return false;
    }
	
	QJsonObject jsonInfo;
	jsonInfo.insert("mode", detailInfo.nMode);
	jsonInfo.insert("type", detailInfo.nType);
	jsonInfo.insert("theme", detailInfo.strTheme);
	jsonInfo.insert("voice", detailInfo.strVoice);
	jsonInfo.insert("endmode", detailInfo.nEndMode);
	
	QJsonObject jsonRet;
	if (!pEslHttpMeet->eslAddMeetTemplate(jsonInfo, vecMember, jsonRet))
	{
		addLastErr("会议模板创建失败，请检查!");
		return false;
	}
	
	detailInfo.nMeetingId = jsonRet["meetingid"].toInt();
	if (detailInfo.nMeetingId <= 0)
	{
		addLastErr("会议号发生错误, 请检查!");
		return false;
	}
	
	ObjectPtr<ISDKMeeting> sdkMeeting;
	if (sdkMeeting->createMeeting(detailInfo, vecMember) == INVALID_ID)
	{
		QJsonObject json;
		json.insert("meetId", std::to_string(detailInfo.nMeetingId).c_str());
		
		pEslHttpMeet->eslDelMeetTemplate(json);
		addLastErr("会议创建失败!");
		return false;
	}
	
	meetingCreate->setMeetingDetailInfo(detailInfo);
	meetingCreate->setMeetingId(jsonRet["meetingid"].toInt());
	
	return true;
}

//关闭会议
void CEslServer::closeMeeting(int iMeetId)
{
	CEslHttpMeet *pEslHttpMeet = m_pHttpCtrl->eslGetMeetPtr();
	if (pEslHttpMeet == Q_NULLPTR || iMeetId <= 0)
	{
		return;
	}
	
	QJsonObject jsonInfo;
	jsonInfo.insert("meetId", std::to_string(iMeetId).c_str());
	
	if (!pEslHttpMeet->eslDelMeetTemplate(jsonInfo))
	{
		addLastErr("会议模板删除失败!");
		return;
	}
	
	ObjectPtr<ISDKMeeting> sdkMeeting;
	sdkMeeting->vsDeleteMeeting(iMeetId, "");
}

//获取会议信息
bool CEslServer::getMeetingInfo(int iMeetId, QJsonObject &jsonValue)
{
	CEslHttpMeet *pEslHttpMeet = m_pHttpCtrl->eslGetMeetPtr();
	if (pEslHttpMeet == Q_NULLPTR || iMeetId <= 0)
	{
		return false;
	}
	
	QJsonObject jsonInfo;
	jsonInfo.insert("meetId", std::to_string(iMeetId).c_str());
	
	QJsonObject jsonRet;
	if (!pEslHttpMeet->eslGetMeetTemplate(jsonInfo, jsonRet))
	{
		addLastErr("获取会议模板失败!");
		return false;
	}
	
	int iCount = jsonRet["count"].toInt();
	QJsonArray array = jsonRet["data"].toArray();
	if (iCount <= 0 || array.isEmpty())
	{
		addLastErr("会议模板数据发生错误!");
		return false;
	}
	
	jsonValue = array.at(0).toObject();
	
	return true;
}

//获取会议成员
bool CEslServer::getMeetingUserList(int iMeetId, QVector<STMeetingMemberVs> &vecMember)
{
	CEslHttpMeet *pEslHttpMeet = m_pHttpCtrl->eslGetMeetPtr();
	if (pEslHttpMeet == Q_NULLPTR || iMeetId <= 0)
	{
		return false;
	}
	
	QJsonObject jsonInfo;
	jsonInfo.insert("meetId", std::to_string(iMeetId).c_str());
	
	QJsonObject jsonRet;
	if (!pEslHttpMeet->eslGetMeetUserList(jsonInfo, jsonRet))
	{
		addLastErr("获取会议成员失败!");
		return false;
	}
	
	int iCount = jsonRet["count"].toInt();
	QJsonArray array = jsonRet["data"].toArray();
	if (iCount <= 0 || array.isEmpty())
	{
		addLastErr("会议模板数据发生错误!");
		return false;
	}
	
	for (int iIndex=0; iIndex<array.size(); iIndex++)
	{
		QJsonObject object = array.at(iIndex).toObject();
		if (object.isEmpty())
		{
			continue;
		}
		
		int iState = MMS_JOINED;//getMeetMembState(object["state"].toInt());
		
		STMeetingMemberVs stItemData;
		stItemData.strCaller = std::to_string(iMeetId).c_str();
		stItemData.strNickName = object["nickname"].toString();
		stItemData.strNumber = object["memberid"].toString();
		stItemData.memberState = static_cast<MeetingMemberState>(iState);
		
		vecMember.append(stItemData);
	}
	
	return true;
}

//////////////////////////////////////////////////////////////////////////
//登录席位号码
bool CEslServer::loginSeatNumber()
{
	ObjectPtr<IRztSettingMgr> settingMgr;
	std::string strUserNum = settingMgr->toString(RztSettingKey::Skey_SeatNumber).toStdString();
	std::string strPasswd = settingMgr->toString(RztSettingKey::Skey_SeatPwd).toStdString();
	
	if (strUserNum == "" || strPasswd == "")
	{
		addLastErr("席位用户密码不能为空!");
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
		addLastErr("连接服务器失败!");
		return false;
	}
	
	ObjectPtr<ISDKUtils> sdkUtils;
	ObjectPtr<IRztConnectorMgr> connectorMgr;
	
	QJsonObject jsonLogin;
	if (!sdkUtils->loginVs(jsonLogin, strUserNum.c_str(), strPasswd.c_str()))
	{
		addLastErr("登录服务器失败!");
		connectorMgr->releaseConnector(strUserNum.c_str());
		return false;
	}
	
	QJsonObject json;
	json.insert("user", strUserNum.c_str());
	json.insert("passwd", strPasswd.c_str());
	json.insert("token", jsonLogin["terminalId"].toString());
	
	json.insert("seat", true);
	json.insert("vsport", iSvrVsPort);
	json.insert("httpport", iSvrHttpPort);
	json.insert("hostip", strSvrIp.c_str());
	
	CEslHttpData *pEslHttpData = m_pHttpCtrl->eslGetDataPtr();
	if (pEslHttpData != Q_NULLPTR)
	{
		//获取系统配置
		if (!pEslHttpData->eslGetSysConfig(json))
		{
			addLastErr("获取系统配置参数失败!");
			return false;
		}
	}
	
	//设置服务器数据
	if (!m_pHttpCtrl->eslSetSrvData(json))
	{
		addLastErr("设置服务器数据失败!");
		return false;
	}
	
	//获取服务器数据
	if (!m_pHttpCtrl->eslGetDataFromSrv(json))
	{
		addLastErr("获取服务器数据失败!");
		return false;
	}
	
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