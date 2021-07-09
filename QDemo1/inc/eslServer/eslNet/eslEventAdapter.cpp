#include "eslEventAdapter.h"

CEslEventAdapter::CEslEventAdapter()
{
}

CEslEventAdapter::~CEslEventAdapter()
{
}

//Pkg包转换json
bool CEslEventAdapter::eslBuildJson(int iMsgType, char *pPayload, QJsonObject &jsonRet)
{
	if (pPayload == Q_NULLPTR)
	{
		return false;
	}
	
	QJsonObject json = QJsonDocument::fromJson(pPayload).object();
	if (json.isEmpty())
	{
		return false;
	}
	
	bool bRet = false;
	switch (iMsgType)
	{
	case ESL_NOTIFY_SEATCONTACT:
		bRet = eslGetSeatContactNotify(json, jsonRet);
		break;
		
	case ESL_NOTIFY_QUICKCONTACT:
		bRet = eslGetQuickContactNotify(json, jsonRet);
		break;
		
	case ESL_NOTIFY_PUBLICCONTACT:
		bRet = eslGetPublicContactNotify(json, jsonRet);
		break;
		
	case ESL_NOTIFY_STYLECONFIG:
		bRet = eslGetStyleConfigNotify(json, jsonRet);
		break;
		
	case ESL_NOTIFY_CALLTOMEET:
		bRet = eslGetCallToMeetNotify(json, jsonRet);
		break;
		
	default:
		break;
	}
	
	return bRet;
}

//更新席位通讯录
bool CEslEventAdapter::eslGetSeatContactNotify(const QJsonObject &json, QJsonObject &jsonRet)
{
	return true;
}

//更新快捷通讯录
bool CEslEventAdapter::eslGetQuickContactNotify(const QJsonObject &json, QJsonObject &jsonRet)
{
	return true;
}

//更新公共通讯录
bool CEslEventAdapter::eslGetPublicContactNotify(const QJsonObject &json, QJsonObject &jsonRet)
{
	return true;
}

//更新个性化配置
bool CEslEventAdapter::eslGetStyleConfigNotify(const QJsonObject &json, QJsonObject &jsonRet)
{
	return true;
}

//通话转会议通知
bool CEslEventAdapter::eslGetCallToMeetNotify(const QJsonObject &json, QJsonObject &jsonRet)
{
	std::string strMeetId = json["meetid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}
	
	QJsonObject jsonData;
	jsonData.insert("meetid", std::stoi(strMeetId));
	jsonData.insert("meetcode", strMeetId.c_str());
	jsonData.insert("usernum", json["lgnum"].toString());
	jsonData.insert("caller", json["caller"].toString());
	jsonData.insert("callee", json["callee"].toString());
	jsonData.insert("mediatype", json["mediatype"].toInt());
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", EVENT_P2P_CHANGE_MEETING);
	jsonRet.insert("businessType", PKG_TYPE_EVENT);
	
	return true;
}