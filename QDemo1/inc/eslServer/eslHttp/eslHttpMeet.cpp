#include "eslHttpMeet.h"

#include "IRztCallNumberMgr.h"

CEslHttpMeet::CEslHttpMeet()
{
}

CEslHttpMeet::~CEslHttpMeet()
{
}

//////////////////////////////////////////////////////////////////////////
//获取成员列表
bool CEslHttpMeet::eslGetMeetUserList(const QJsonObject &json, QJsonObject &jsonValue)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	ObjectPtr<IRztCallNumberMgr> callNumberMgr;
	std::string strUserNum = callNumberMgr->getActiveNumber().strVsCallNumber.toStdString();
	if (strUserNum == "")
	{
		return false;
	}
	
	int iTerminalId = callNumberMgr->getTerminalId(strUserNum.c_str());
	std::string strUrl = "/api/v1/meeting/getMeetMembers";
	
	std::string strMeetId;
	if (json.contains("meetid"))
	{
		strMeetId = json["meetid"].toString().toStdString();	
	}
	
	QJsonObject jsonMeet;
	jsonMeet.insert("user", strUserNum.c_str());
	jsonMeet.insert("token", iTerminalId);
	jsonMeet.insert("meetingid", strMeetId.c_str());
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonMeet, jsonRet))
	{
		return false;
	}
	
	if (!jsonRet["data"].isArray())
	{
		return false;
	}
	
	QJsonArray jsonArray(jsonRet["data"].toArray());
	if (jsonArray.isEmpty())
	{
		return false;
	}
	
	jsonValue.insert("count", jsonArray.size());
	jsonValue.insert("data", jsonArray);
	
	return true;
}

//获取会议模板
bool CEslHttpMeet::eslGetMeetTemplate(const QJsonObject &json, QJsonObject &jsonValue)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	ObjectPtr<IRztCallNumberMgr> callNumberMgr;
	std::string strUserNum = callNumberMgr->getActiveNumber().strVsCallNumber.toStdString();
	if (strUserNum == "")
	{
		return false;
	}
	
	int iTerminalId = callNumberMgr->getTerminalId(strUserNum.c_str());
	std::string strUrl = "/api/v1/meeting/getMeetTemplate";
	
	std::string strMeetId;
	if (json.contains("meetid"))
	{
		strMeetId = json["meetid"].toString().toStdString();	
	}
	
	std::string strMeetCreater;
	if (json.contains("creator"))
	{
		strMeetCreater = json["creator"].toString().toStdString();
	}
	
	QJsonObject jsonMeet;
	jsonMeet.insert("user", strUserNum.c_str());
	jsonMeet.insert("token", iTerminalId);
	jsonMeet.insert("meetingid", strMeetId.c_str());
	jsonMeet.insert("creator", strMeetCreater.c_str());
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonMeet, jsonRet))
	{
		return false;
	}
	
	if (!jsonRet["data"].isArray())
	{
		return false;
	}
	
	QJsonArray jsonArray(jsonRet["data"].toArray());
	if (jsonArray.isEmpty())
	{
		return false;
	}
	
	jsonValue.insert("count", jsonArray.size());
	jsonValue.insert("data", jsonArray);
	
	return true;
}

//创建会议模板
bool CEslHttpMeet::eslAddMeetTemplate(const QJsonObject &json, const QVector<QString> &vecMember, QJsonObject &jsonValue)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	ObjectPtr<IRztCallNumberMgr> callNumberMgr;
	std::string strUserNum = callNumberMgr->getActiveNumber().strVsCallNumber.toStdString();
	if (strUserNum == "")
	{
		return false;
	}
	
	QJsonArray jsonArray;
	for (auto vec:vecMember)
	{
		jsonArray.append(vec);
	}
	
	int iTerminalId = callNumberMgr->getTerminalId(strUserNum.c_str());
	std::string strUrl = "/api/v1/meeting/addMeetTemplate";
	
	std::string strTitle;
	if (json.contains("theme"))
	{
		strTitle = json["theme"].toString().toStdString();
		if (strTitle == "")
		{
			strTitle = strUserNum;
		}
	}
	else
	{
		strTitle = strUserNum;
	}
	
	QJsonObject jsonMeet;
	jsonMeet.insert("user", strUserNum.c_str());
	jsonMeet.insert("token", iTerminalId);
	jsonMeet.insert("split", 0);
	jsonMeet.insert("imagesize", 0);
	jsonMeet.insert("meetmode", json["mode"].toInt());
	jsonMeet.insert("title", strTitle.c_str());
	jsonMeet.insert("needrecord", 1);
	jsonMeet.insert("members", jsonArray);
	jsonMeet.insert("administrator", strUserNum.c_str());
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonMeet, jsonRet))
	{
		return false;
	}
	
	QJsonObject jsonMsg(jsonRet["data"].toObject());
	if (jsonMsg.isEmpty())
	{
		return false;
	}
	
	jsonValue.insert("title", jsonMsg["title"].toString());
	jsonValue.insert("meetid", jsonMsg["meetingid"].toInt());
	
	return true;
}

//删除会议模板
bool CEslHttpMeet::eslDelMeetTemplate(const QJsonObject &json)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	ObjectPtr<IRztCallNumberMgr> callNumberMgr;
	std::string strUserNum = callNumberMgr->getActiveNumber().strVsCallNumber.toStdString();
	if (strUserNum == "")
	{
		return false;
	}
	
	int iTerminalId = callNumberMgr->getTerminalId(strUserNum.c_str());
	std::string strMeetId = json["meetid"].toString().toStdString();
	std::string strUrl = "/api/v1/meeting/delMeetTemplate";
	
	QJsonObject jsonMeet;
	jsonMeet.insert("user", strUserNum.c_str());
	jsonMeet.insert("token", iTerminalId);
	jsonMeet.insert("meetingid", strMeetId.c_str());

	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonMeet, jsonRet))
	{
		return false;
	}
	
	return true;
}