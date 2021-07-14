#include "eslAnncAdapter.h"

#include "RztCommonUtils.h"

CEslAnncAdapter::CEslAnncAdapter()
{
}

CEslAnncAdapter::~CEslAnncAdapter()
{
}

//////////////////////////////////////////////////////////////////////////
//Pkg请求包
void CEslAnncAdapter::eslBuildPkg(const QJsonObject &json, std::string &strJson, int &iPkgType, int &iMsgType)
{
	iPkgType = ESL_PKG_TYPE_ANNC;
	switch (static_cast<int>(json["msgType"].toInt()))
	{
	case SCH_MEETING_CREATE_REQ:
		OnReqEslCreateAnnc(json, strJson, iMsgType);
		break;
		
	case SCH_MEETING_OVER_CMD:
		OnReqEslCloseAnnc(json, strJson, iMsgType);
		break;
		
	case SCH_MEETING_MEMB_ADD_REQ:
		OnReqEslAddAnncMemb(json, strJson, iMsgType);
		break;
		
	case SCH_MEETING_MEMB_KICKOUT_REQ:
		OnReqEslDelAnncMemb(json, strJson, iMsgType);
		break;
		
	default:
		break;	
	}
}

//Pkg包转换json
bool CEslAnncAdapter::eslBuildJson(int iMsgType, char *pPayload, QJsonObject &jsonRet)
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
	case ESL_MSG_CREATEANNC_RESP:
		bRet = OnRespEslCreateAnnc(json, jsonRet);
		break;
		
	case ESL_MSG_CLOSEANNC_RESP:
		bRet = OnRespEslCloseAnnc(json, jsonRet);
		break;
		
	case ESL_MSG_ADDANNCMEMB_RESP:
		bRet = OnRespEslAddAnncMemb(json, jsonRet);
		break;
		
	case ESL_MSG_DELANNCMEMB_RESP:
		bRet = OnRespEslDelAnncMemb(json, jsonRet);
		break;
		
	default:
		break;
	}
	
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
//创建通播Req
void CEslAnncAdapter::OnReqEslCreateAnnc(const QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg	= json.value("msg").toObject();
	if (jsonMsg.isEmpty())
	{
		return;
	}

	std::string strMeetId = std::to_string(jsonMsg["meetid"].toInt());
	std::string strTernimalId = std::to_string(jsonMsg["ternimalId"].toInt());
	if (strMeetId == "" || strTernimalId == "")
	{
		return;
	}

	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("atisid", strMeetId.c_str());
	jsonRet.insert("token", strTernimalId.c_str());

	iMsgType = ESL_MSG_CREATEANNC_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//创建通播Resp
bool CEslAnncAdapter::OnRespEslCreateAnnc(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["atisid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}

	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("result", json["result"].toInt());
	jsonData.insert("meetid", std::stoi(strMeetId));
	jsonData.insert("usernum", json["lgnum"].toString());
	jsonData.insert("token", json["token"].toString());

	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", SCH_MEETING_CREATE_REQ);
	jsonRet.insert("businessType", PKG_TYPE_SCHEDULE);

	return true;
}

//关闭通播Req
void CEslAnncAdapter::OnReqEslCloseAnnc(const QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg = json.value("msg").toObject();
	if (jsonMsg.isEmpty())
	{
		return;
	}

	std::string strMeetId = std::to_string(jsonMsg["meetid"].toInt());
	std::string strTernimalId = std::to_string(jsonMsg["ternimalId"].toInt());
	if (strMeetId == "" || strTernimalId == "")
	{
		return;
	}

	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("atisid", strMeetId.c_str());
	jsonRet.insert("token", strTernimalId.c_str());

	iMsgType = ESL_MSG_CLOSEANNC_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//关闭通播Resp
bool CEslAnncAdapter::OnRespEslCloseAnnc(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["atisid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}

	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("meetid", std::stoi(strMeetId));

	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", "");
	jsonRet.insert("businessType", PKG_TYPE_SCHEDULE);

	return true;
}

//增加通播成员Req
void CEslAnncAdapter::OnReqEslAddAnncMemb(const QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg = json.value("msg").toObject();
	if (jsonMsg.isEmpty())
	{
		return;
	}

	QJsonArray array = jsonMsg["members"].toArray();
	if (array.isEmpty())
	{
		return;
	}

	std::string strMeetId = std::to_string(jsonMsg["meetid"].toInt());
	std::string strTernimalId = std::to_string(jsonMsg["ternimalId"].toInt());
	if (strMeetId == "" || strTernimalId == "")
	{
		return;
	}
	
	QJsonArray jsonArray;
	if (jsonMsg.contains("members"))
	{
		if (!jsonMsg["members"].toArray().isEmpty())
		{
			int iIndex = 0;
			QJsonArray array = jsonMsg["members"].toArray();
			
			for (QJsonArray::Iterator iter = array.begin(); iter != array.end(); iter++)
			{
				QJsonObject object = iter[0].toObject();
				if (object.isEmpty())
				{
					continue;
				}
				
				jsonArray.insert(iIndex++, object["num"].toString());
			}
		}
	}

	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("atisid", strMeetId.c_str());
	jsonRet.insert("token", strTernimalId.c_str());
	jsonRet.insert("memlist", jsonArray);
	
	iMsgType = ESL_MSG_ADDANNCMEMB_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//增加通播成员Resp
bool CEslAnncAdapter::OnRespEslAddAnncMemb(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["atisid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}

	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("result", json["result"].toInt());
	jsonData.insert("meetid", std::stoi(strMeetId));
	jsonData.insert("usernum", json["lgnum"].toString());
	jsonData.insert("token", json["token"].toString());

	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", SCH_MEETING_MEMB_ADD_RESP);
	jsonRet.insert("businessType", PKG_TYPE_SCHEDULE);

	return true;
}

//删除通播成员Req
void CEslAnncAdapter::OnReqEslDelAnncMemb(const QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg = json.value("msg").toObject();
	if (jsonMsg.isEmpty())
	{
		return;
	}
	
	std::string strMeetId = std::to_string(jsonMsg["meetid"].toInt());
	std::string strTernimalId = std::to_string(jsonMsg["ternimalId"].toInt());
	if (strMeetId == "" || strTernimalId == "")
	{
		return;
	}
	
	QJsonArray jsonArray;
	if (jsonMsg.contains("members"))
	{
		if (!jsonMsg["members"].toArray().isEmpty())
		{
			int iIndex = 0;
			QJsonArray array = jsonMsg["members"].toArray();
			
			for (QJsonArray::Iterator iter = array.begin(); iter != array.end(); iter++)
			{
				QJsonObject object = iter[0].toObject();
				if (object.isEmpty())
				{
					continue;
				}
				
				jsonArray.insert(iIndex++, object["num"].toString());
			}
		}
	}

	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("atisid", strMeetId.c_str());
	jsonRet.insert("token", strTernimalId.c_str());
	jsonRet.insert("memlist", jsonArray);

	iMsgType = ESL_MSG_DELANNCMEMB_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//删除通播成员Resp
bool CEslAnncAdapter::OnRespEslDelAnncMemb(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["atisid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}

	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("meetid", std::stoi(strMeetId));
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", SCH_MEETING_MEMB_KICKOUT_RESP);
	jsonRet.insert("businessType", PKG_TYPE_SCHEDULE);

	return true;
}

//开启手咪对讲Req
void CEslAnncAdapter::OnReqEslStartSpeak(const QJsonObject &json, std::string &strJson, int &iMsgType)
{
	
}

//开启手咪对讲Resp
bool CEslAnncAdapter::OnRespEslStartSpeak(const QJsonObject &json, QJsonObject &jsonRet)
{
	return true;
}

//关闭手咪对讲Req
void CEslAnncAdapter::OnReqEslStopSpeak(const QJsonObject &json, std::string &strJson, int &iMsgType)
{
}

//关闭手咪对讲Resp
bool CEslAnncAdapter::OnRespEslStopSpeak(const QJsonObject &json, QJsonObject &jsonRet)
{
	return true;
}

//开启视频查看Req
void CEslAnncAdapter::OnReqEslStartVideo(const QJsonObject &json, std::string &strJson, int &iMsgType)
{
}

//开启视频查看Resp
bool CEslAnncAdapter::OnRespEslStartVideo(const QJsonObject &json, QJsonObject &jsonRet)
{
	return true;
}

//关闭视频查看Req
void CEslAnncAdapter::OnReqEslStopVideo(const QJsonObject &json, std::string &strJson, int &iMsgType)
{
}

//关闭视频查看Resp
bool CEslAnncAdapter::OnRespEslStopVideo(const QJsonObject &json, QJsonObject &jsonRet)
{
	return true;
}