#include "eslStatusAdapter.h"

CEslStatusAdapter::CEslStatusAdapter()
{
}

CEslStatusAdapter::~CEslStatusAdapter()
{
}

//Pkg包转换json
bool CEslStatusAdapter::eslBuildJson(int iMsgType, char *pPayload, QJsonObject &jsonRet)
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
	
	if (!eslGetUserStatus(json, jsonRet))
	{
		return false;
	}
	
	return true;
}

//状态通知
bool CEslStatusAdapter::eslGetUserStatus(const QJsonObject &json, QJsonObject &jsonRet)
{
	std::string strType = json["type"].toString().toStdString();
	if (strType == "")
	{
		return false;
	}
	
	if (strType == "call")
	{
		OnEslCallStatus(json, jsonRet);
	}
	else if (strType == "meet")
	{
		OnEslMeetStatus(json, jsonRet);
	}
	else if (strType == "atis")
	{
		OnEslAnnounceStatus(json, jsonRet);
	}
	else
	{
		return false;
	}
	
	jsonRet.insert("businessType", PKG_TYPE_EVENT);
	return true;
}

//通话状态
void CEslStatusAdapter::OnEslCallStatus(const QJsonObject &json, QJsonObject &jsonRet)
{
}

//会议状态
void CEslStatusAdapter::OnEslMeetStatus(const QJsonObject &json, QJsonObject &jsonRet)
{
	std::string strMeetId = json["othernum"].toString().toStdString();
	if (strMeetId == "")
	{
		return;
	}
	
	int iStatus = json["status"].toInt();
	
	QJsonObject jsonData;
	jsonData.insert("meetid", std::stoi(strMeetId));
	jsonData.insert("meetcode", strMeetId.c_str());
	jsonData.insert("usernum", json["lgnum"].toString());
	jsonData.insert("state", iStatus);
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", EVENT_UPDATE_MEETING_MEMB_STATE);
}

//通播状态
void CEslStatusAdapter::OnEslAnnounceStatus(const QJsonObject &json, QJsonObject &jsonRet)
{
	std::string strMeetId = json["othernum"].toString().toStdString();
	if (strMeetId == "")
	{
		return;
	}

	int iStatus = json["status"].toInt();

	QJsonObject jsonData;
	jsonData.insert("meetid", std::stoi(strMeetId));
	jsonData.insert("meetcode", strMeetId.c_str());
	jsonData.insert("usernum", json["lgnum"].toString());
	jsonData.insert("state", iStatus);
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", EVENT_UPDATE_MEETING_MEMB_STATE);
}