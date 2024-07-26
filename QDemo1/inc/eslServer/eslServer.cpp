#include "eslServer.h"

#include "ISDKUtils.h"
#include "IRztSettingMgr.h"

#include "IRztVsNet.h"
#include "IRztConnector.h"
#include "IRztConnectorMgr.h"

#include "ISDKMeeting.h"
#include "IRztServerInfoMgr.h"
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
	return settingMgr->toBool(RztSettingKey::SKey_EslOpen);
}

//登录用户
bool CEslServer::loginUser(const QJsonObject &json)
{
	bool bResult = false;

	if (json.isEmpty())
	{
		return false;
	}
	
	switch (json["type"].toInt())
	{
	case ESL_LOGIN_USER_TYPE:
		bResult = loginUserNumber(json);
		break;
		
	case ESL_LOGIN_SEAT_TYPE:
		bResult = loginSeatNumber(json);
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
	CEslHttpAnnc *pEslHttpAnnc = m_pHttpCtrl->eslGetAnncPtr();

	if (pEslHttpMeet == Q_NULLPTR || pEslHttpAnnc == Q_NULLPTR)
	{
		return false;
	}

	QJsonObject jsonMeet;
	jsonMeet.insert("mode", detailInfo.nMode);
	jsonMeet.insert("type", detailInfo.nType);
	jsonMeet.insert("theme", detailInfo.strTheme);
	jsonMeet.insert("voice", detailInfo.strVoice);
	jsonMeet.insert("endmode", detailInfo.nEndMode);
	
	QJsonObject jsonRet;
	int iType = detailInfo.nType;
	
	if (iType == 2)
	{//通播
		if (!pEslHttpAnnc->eslAddAnncTemplate(jsonMeet, vecMember, jsonRet))
		{
			addLastErr("通播模板创建失败,请检查!");
			return false;
		}
	}
	else
	{//会议
		if (!pEslHttpMeet->eslAddMeetTemplate(jsonMeet, vecMember, jsonRet))
		{
			addLastErr("会议模板创建失败,请检查!");
			return false;
		}
	}
	
	detailInfo.nMeetingId = jsonRet["meetid"].toInt();

	ObjectPtr<ISDKMeeting> sdkMeeting;
	int iRet = sdkMeeting->createMeeting(detailInfo, vecMember);
	if (iRet <= 0 || iRet == INVALID_ID)
	{
		addLastErr("会议创建失败!");
		closeMeeting(iType, detailInfo.nMeetingId);
		return false;
	}

	if (iType == 2)
	{
		ObjectPtr<IRztCreateMeetingCondition> AnnounceCreate;

		AnnounceCreate->setMeetingDetailInfo(detailInfo);
		AnnounceCreate->setMeetingId(jsonRet["meetid"].toInt());
	}
	else
	{
		ObjectPtr<IRztCreateMeetingCondition> meetingCreate;

		meetingCreate->setMeetingDetailInfo(detailInfo);
		meetingCreate->setMeetingId(jsonRet["meetid"].toInt());
	}

	return true;
}

//关闭会议
void CEslServer::closeMeeting(int iType, int iMeetId)
{
	CEslHttpMeet *pEslHttpMeet = m_pHttpCtrl->eslGetMeetPtr();
	CEslHttpAnnc *pEslHttpAnnc = m_pHttpCtrl->eslGetAnncPtr();

	if (iMeetId <= 0 || pEslHttpMeet == Q_NULLPTR || pEslHttpAnnc == Q_NULLPTR)
	{
		return;
	}
	
	QJsonObject jsonMeet;
	jsonMeet.insert("meetid", std::to_string(iMeetId).c_str());
	
	if (iType == 2)
	{//通播
		if (!pEslHttpAnnc->eslDelAnncTemplate(jsonMeet))
		{
			addLastErr("会议模板删除失败!");
		}
	}
	else
	{//会议
		if (!pEslHttpMeet->eslDelMeetTemplate(jsonMeet))
		{
			addLastErr("会议模板删除失败!");
		}
	}
}

//获取会议信息
bool CEslServer::getMeetingInfo(int iType, int iMeetId, QJsonObject &jsonValue)
{
	CEslHttpMeet *pEslHttpMeet = m_pHttpCtrl->eslGetMeetPtr();
	CEslHttpAnnc *pEslHttpAnnc = m_pHttpCtrl->eslGetAnncPtr();

	if (iMeetId <= 0 || pEslHttpMeet == Q_NULLPTR || pEslHttpAnnc == Q_NULLPTR)
	{
		return false;
	}
	
	QJsonObject jsonMeet;
	jsonMeet.insert("meetid", std::to_string(iMeetId).c_str());
	
	QJsonObject jsonRet;
	if (iType == 2)
	{
		if (!pEslHttpAnnc->eslGetAnncTemplate(jsonMeet, jsonRet))
		{
			addLastErr("获取通播模板失败!");
			return false;
		}
	}
	else
	{
		if (!pEslHttpMeet->eslGetMeetTemplate(jsonMeet, jsonRet))
		{
			addLastErr("获取会议模板失败!");
			return false;
		}
	}
	
	int iCount = jsonRet["count"].toInt();
	QJsonArray array = jsonRet["data"].toArray();
	if (iCount <= 0 || array.isEmpty())
	{
		addLastErr("模板数据发生错误!");
		return false;
	}
	
	jsonValue = array.at(0).toObject();
	return true;
}

//获取会议成员
bool CEslServer::getMeetingUserList(int iType, int iMeetId, QVector<STMeetingMemberVs> &vecMember)
{
	CEslHttpMeet *pEslHttpMeet = m_pHttpCtrl->eslGetMeetPtr();
	CEslHttpAnnc *pEslHttpAnnc = m_pHttpCtrl->eslGetAnncPtr();

	if (iMeetId <= 0 || pEslHttpMeet == Q_NULLPTR || pEslHttpAnnc == Q_NULLPTR)
	{
		return false;
	}
	
	QJsonObject jsonMeet;
	jsonMeet.insert("meetid", std::to_string(iMeetId).c_str());
	
	QJsonObject jsonRet;
	if (iType == 2)
	{
		if (!pEslHttpAnnc->eslGetAnncUserList(jsonMeet, jsonRet))
		{
			addLastErr("获取会议成员失败!");
			return false;
		}
	}
	else
	{
		if (!pEslHttpMeet->eslGetMeetUserList(jsonMeet, jsonRet))
		{
			addLastErr("获取会议成员失败!");
			return false;
		}
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
		
		int iState = getMeetStatusFromEsl(object["state"].toInt());
		
		STMeetingMemberVs stItemData;
		stItemData.strCaller = std::to_string(iMeetId).c_str();
		stItemData.strNickName = object["nickname"].toString();
		stItemData.strNumber = object["memberid"].toString();
		stItemData.memberState = static_cast<MeetingMemberState>(iState);
		
		vecMember.append(stItemData);
	}
	
	return true;
}

//获取会议状态
int CEslServer::getMeetStatusFromEsl(int iStatus)
{
	int iMmsState = MMS_OFFLINE;
	switch (iStatus)
	{
	case MEET_MEMB_STATE_INIT:
		iMmsState = static_cast<int>(MMS_INIT);
		break;
		
	case MEET_MEMB_STATE_OFFLINE:
		iMmsState = static_cast<int>(MMS_OFFLINE);
		break;
		
	case MEET_MEMB_STATE_INVITING:
		iMmsState = static_cast<int>(MMS_INVITING);
		break;
		
	case MEET_MEMB_STATE_ANSWER:
		iMmsState = static_cast<int>(MMS_JOINED);
		break;
		
	case MEET_MEMB_STATE_NOANSWER:
		iMmsState = static_cast<int>(MMS_NO_ANSWER);
		break;
		
	case MEET_MEMB_STATE_REJECT:
		iMmsState = static_cast<int>(MMS_REJECT);
		break;
		
	case MEET_MEMB_STATE_EXIT:
		iMmsState = static_cast<int>(MMS_EXIT);
		break;
		
	case MEET_MEMB_STATE_KICKOUT:
		iMmsState = static_cast<int>(MMS_EXIT);	//MMS_KICKOUTED
		break;
		
	case MEET_MEMB_STATE_SILENCE:
		iMmsState = static_cast<int>(MMS_MUTED);
		break;
		
	case MEET_MEMB_STATE_HOLDING:
		iMmsState = static_cast<int>(MMS_NON_TALK);
		break;
		
	case MEET_MEMB_STATE_SPEECHING:
		iMmsState = static_cast<int>(MMS_TALK);
		break;
		
	default:
		break;
	}
	
	return iMmsState;
}

//获取通播状态
int CEslServer::getAnncStatusFromEsl(int iStatus)
{
	int iMmsState = MMS_OFFLINE;
	switch (iStatus)
	{
	case ANNC_MEMB_STATE_INIT:
		iMmsState = static_cast<int>(MMS_INIT);
		break;

	case ANNC_MEMB_STATE_OFFLINE:
		iMmsState = static_cast<int>(MMS_OFFLINE);
		break;

	case ANNC_MEMB_STATE_CALLING:
		iMmsState = static_cast<int>(MMS_INVITING);
		break;

	case ANNC_MEMB_STATE_CONNECT:
		iMmsState = static_cast<int>(MMS_JOINED);
		break;

	case ANNC_MEMB_STATE_SPEAKING:
		iMmsState = static_cast<int>(MMS_TALK);
		break;

	case ANNC_MEMB_STATE_NOSPEAKING:
		iMmsState = static_cast<int>(MMS_NON_TALK);
		break;	

	case ANNC_MEMB_STATE_NOANSWER:
		iMmsState = static_cast<int>(MMS_NO_ANSWER);
		break;

	case ANNC_MEMB_STATE_HUNGUP:
		iMmsState = static_cast<int>(MMS_EXIT);
		break;

	case ANNC_MEMB_STATE_KICKOUT:
		iMmsState = static_cast<int>(MMS_EXIT);	//MMS_KICKOUTED
		break;

	case ANNC_MEMB_STATE_REJECT:
		iMmsState = static_cast<int>(MMS_REJECT);
		break;

	default:
		break;
	}
	
	return iMmsState;
}

//////////////////////////////////////////////////////////////////////////
//登录席位号码
bool CEslServer::loginSeatNumber(const QJsonObject &json)
{
	bool bRet = false;
	bool bLogined = false;

	ObjectPtr<ISDKUtils> sdkUtils;
	
	CEslHttpData *pEslHttpData = m_pHttpCtrl->eslGetDataPtr();
	if (pEslHttpData == Q_NULLPTR)
	{
		addLastErr("软件内部发生错误!");
		return false;
	}

	std::string strUserNum = json["usernum"].toString().toStdString();
	std::string strPasswd = json["userpasswd"].toString().toStdString();
	if (strUserNum == "" || strPasswd == "")
	{
		addLastErr("用户密码不能为空!");
		return false;
	}
	
	do
	{	
		int iSvrVsPort = 20000;
		int iSvrHttpPort = json["httpport"].toInt();
		std::string strSvrIp = json["hostip"].toString().toStdString();

		std::string strUid = json["uid"].toString().toStdString();
		std::string strUidPasswd = json["uidpasswd"].toString().toStdString();
		
		QJsonObject jsonSystem;
		jsonSystem.insert("uid", strUid.c_str());
		jsonSystem.insert("httpport", iSvrHttpPort);
		jsonSystem.insert("hostip", strSvrIp.c_str());
		
		//获取系统配置
		QJsonObject jsonRet;
		if (!pEslHttpData->eslGetSysConfig(jsonSystem, jsonRet))
		{
			addLastErr("获取系统配置参数失败!");
			break;
		}
		else
		{
			iSvrVsPort = jsonRet["tcp_port"].toInt();
			
			QJsonObject jsonConnect;
			jsonConnect.insert("timeout", 3000);
			jsonConnect.insert("svrport", iSvrVsPort);
			jsonConnect.insert("svrip", strSvrIp.c_str());
			jsonConnect.insert("usernum", strUserNum.c_str());
			
			if (!connectSvr(jsonConnect))
			{
				addLastErr("连接服务器失败!");
				break;
			}
		}
		
		QJsonObject jsonLogin;
		if (!sdkUtils->loginVs(jsonLogin, strUserNum.c_str(), strPasswd.c_str()))
		{
			addLastErr("登录服务器失败!");
			break;
		}
		else
		{
			bLogined = true;
		
			QJsonObject jsonParam;
			jsonParam.insert("user", strUserNum.c_str());
			jsonParam.insert("passwd", strPasswd.c_str());
			jsonParam.insert("uid", strUid.c_str());
			jsonParam.insert("uidpasswd", strUidPasswd.c_str());
			jsonParam.insert("devuid", strUid.c_str());
			jsonParam.insert("token", jsonLogin["terminalId"].toString());
			
			jsonParam.insert("seat", true);
			jsonParam.insert("vsport", iSvrVsPort);
			jsonParam.insert("httpport", iSvrHttpPort);
			jsonParam.insert("hostip", strSvrIp.c_str());
			
			//设置服务器数据
			if (!m_pHttpCtrl->eslSetSrvData(jsonParam))
			{
				addLastErr("设置服务器数据失败!");
				break;
			}
			
			//获取服务器数据
			if (!m_pHttpCtrl->eslGetDataFromSrv(jsonParam))
			{
				addLastErr("获取服务器数据失败!");
				break;
			}
			
			//设置运行事件
			m_pHttpCtrl->eslSetUserEvent(jsonParam);
		}
		
		bRet = true;
	} while (false);

	if (!bRet)
	{
		if (bLogined)
		{
			sdkUtils->logoutVs(strUserNum.c_str());
		}

		ObjectPtr<IRztConnectorMgr> connectorMgr;
		if (connectorMgr->getConnector(strUserNum.c_str()) != Q_NULLPTR)
		{
			connectorMgr->releaseConnector(strUserNum.c_str());
		}
	}
	
	return bRet;
}

//登录用户号码
bool CEslServer::loginUserNumber(const QJsonObject &json)
{
	bool bRet = false;
	bool bLogined = false;

	ObjectPtr<ISDKUtils> sdkUtils;

	CEslHttpData *pEslHttpData = m_pHttpCtrl->eslGetDataPtr();
	if (pEslHttpData == Q_NULLPTR)
	{
		addLastErr("软件内部发生错误!");
		return false;
	}

	std::string strUserNum = json["usernum"].toString().toStdString();
	std::string strPasswd = json["userpasswd"].toString().toStdString();
	if (strUserNum == "" || strPasswd == "")
	{
		addLastErr("用户密码不能为空!");
		return false;
	}

	do
	{
		ObjectPtr<IRztServerInfoMgr> severInfo;
		STSvrInfo svrInfo = severInfo->getCurSvrInfo();

		int iSvrPort = svrInfo.nVsPort;
		int iHttpPort = svrInfo.nHttpPort;
		std::string strSvrIp = svrInfo.strIP.toStdString();

		std::string strUid = json["uid"].toString().toStdString();
		std::string strUidPasswd = json["uidpasswd"].toString().toStdString();

		std::string strDevUid = json["devuid"].toString().toStdString();

		QJsonObject jsonConnect;
		jsonConnect.insert("timeout", 3000);
		jsonConnect.insert("svrport", iSvrPort);
		jsonConnect.insert("svrip", strSvrIp.c_str());
		jsonConnect.insert("usernum", strUserNum.c_str());
		if (!connectSvr(jsonConnect))
		{
			addLastErr("连接服务器失败!");
			break;
		}

		QJsonObject jsonLogin;
		if (!sdkUtils->loginVs(jsonLogin, strUserNum.c_str(), strPasswd.c_str()))
		{
			addLastErr("登录服务器失败!");
			break;
		}
		else
		{
			bLogined = true;

			QJsonObject jsonParam;
			jsonParam.insert("user", strUserNum.c_str());
			jsonParam.insert("passwd", strPasswd.c_str());
			jsonParam.insert("uid", strUid.c_str());
			jsonParam.insert("uidpasswd", strUidPasswd.c_str());
			jsonParam.insert("devuid", strDevUid.c_str());
			jsonParam.insert("token", jsonLogin["terminalId"].toString());

			jsonParam.insert("seat", false);
			jsonParam.insert("vsport", iSvrPort);
			jsonParam.insert("httpport", iHttpPort);
			jsonParam.insert("hostip", strSvrIp.c_str());

			//设置服务器数据
			if (!m_pHttpCtrl->eslSetSrvData(jsonParam))
			{
				addLastErr("设置服务器数据失败!");
				break;
			}

			//获取服务器数据
			if (!m_pHttpCtrl->eslGetDataFromSrv(jsonParam))
			{
				addLastErr("获取服务器数据失败!");
				break;
			}

			//设置运行事件
			//m_pHttpCtrl->eslSetUserEvent(jsonParam);
		}

		bRet = true;
	} while (false);

	if (!bRet)
	{
		if (bLogined)
		{
			sdkUtils->logoutVs(strUserNum.c_str());
		}

		ObjectPtr<IRztConnectorMgr> connectorMgr;
		if (connectorMgr->getConnector(strUserNum.c_str()) != Q_NULLPTR)
		{
			connectorMgr->releaseConnector(strUserNum.c_str());
		}
	}
	
	return bRet;
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

	//connnect vs
	ObjectPtr<IRztConnectorMgr> connectorMgr;
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