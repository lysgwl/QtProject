#include "eslHttpAnnc.h"

#include "IRztCallNumberMgr.h"

CEslHttpAnnc::CEslHttpAnnc()
{
}

CEslHttpAnnc::~CEslHttpAnnc()
{

}

//////////////////////////////////////////////////////////////////////////
//获取成员列表
bool CEslHttpAnnc::eslGetAnncUserList(const QJsonObject &json, QJsonObject &jsonValue)
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
	std::string strUrl = "/api/v1/satis/getSatisMembers";

	std::string strMeetId;
	if (json.contains("meetid"))
	{
		strMeetId = json["meetid"].toString().toStdString();	
	}

	QJsonObject jsonAnnc;
	jsonAnnc.insert("user", strUserNum.c_str());
	jsonAnnc.insert("token", iTerminalId);
	jsonAnnc.insert("atisid", strMeetId.c_str());

	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonAnnc, jsonRet))
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

//获取通播模板
bool CEslHttpAnnc::eslGetAnncTemplate(const QJsonObject &json, QJsonObject &jsonValue)
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
	std::string strUrl = "/api/v1/satis/getSatisTemplateList";

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

	QJsonObject jsonAnnc;
	jsonAnnc.insert("user", strUserNum.c_str());
	jsonAnnc.insert("token", iTerminalId);
	jsonAnnc.insert("atisid", strMeetId.c_str());
	jsonAnnc.insert("creator", strMeetCreater.c_str());
	
	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonAnnc, jsonRet))
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

//创建通播模板
bool CEslHttpAnnc::eslAddAnncTemplate(const QJsonObject &json, const QVector<QString> &vecMember, QJsonObject &jsonValue)
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
	std::string strUrl = "/api/v1/satis/addSatisTemplate";

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

	QJsonObject jsonAnnc;
	jsonAnnc.insert("user", strUserNum.c_str());
	jsonAnnc.insert("token", iTerminalId);
	jsonAnnc.insert("title", strTitle.c_str());
	jsonAnnc.insert("needrecord", 1);
	jsonAnnc.insert("members", jsonArray);
	jsonAnnc.insert("administrator", strUserNum.c_str());

	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonAnnc, jsonRet))
	{
		return false;
	}
	
	QJsonObject jsonMsg(jsonRet["data"].toObject());
	if (jsonMsg.isEmpty())
	{
		return false;
	}

	jsonValue.insert("title", jsonMsg["title"].toString());
	jsonValue.insert("meetid", jsonMsg["atisid"].toInt());

	return true;
}

//删除通播模板	
bool CEslHttpAnnc::eslDelAnncTemplate(const QJsonObject &json)
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
	std::string strUrl = "/api/v1/satis/delSatisTemplate";

	QJsonObject jsonAnnc;
	jsonAnnc.insert("user", strUserNum.c_str());
	jsonAnnc.insert("token", iTerminalId);
	jsonAnnc.insert("atisid", strMeetId.c_str());

	QJsonObject jsonRet;
	if (!postHttpRequest(strUrl, "", jsonAnnc, jsonRet))
	{
		return false;
	}

	return true;
}