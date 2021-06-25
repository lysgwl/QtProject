#include "elsMeetAdapter.h"

CEslMeetAdapter::CEslMeetAdapter()
{
}

CEslMeetAdapter::~CEslMeetAdapter()
{
}

//////////////////////////////////////////////////////////////////////////
//Pkg请求包
void CEslMeetAdapter::eslBuildPkg(QJsonObject &json, std::string &strJson, int &iPkgType, int &iMsgType)
{
	iPkgType = ESL_PKG_TYPE_MEET;
	switch (static_cast<int>(json["msgType"].toInt()))
	{
	case SCH_MEETING_CREATE_REQ:	//创建会议
		OnReqEslCreateMeet(json, strJson, iMsgType);
		break;
		
	case SCH_MEETING_MEMB_ADD_REQ:	//添加会议成员
		OnReqEslAddMeetMemb(json, strJson, iMsgType);
		break;
		
	case SCH_MEETING_MEMB_KICKOUT_REQ:	//删除会议成员
		OnReqEslDelMeetMemb(json, strJson, iMsgType);
		break;
		
	case SCH_MEETING_MEMB_MUTE_REQ:		//会议成员禁言
		OnReqEslSilenceMeetMemb(json, strJson, iMsgType);
		break;
		
	case SCH_MEETING_SPLIT_SCREEN_SET_REQ:	//视频会议分屏
		OnReqEslSplitScrMeet(json, strJson, iMsgType);
		break;
		
	case SCH_MEETING_VIDEO_SPEECH_SET_REQ:	//会议成员演讲
		OnReqEslSpeechMeetMemb(json, strJson, iMsgType);
		break;
		
	case SCH_MEETING_OVER_CMD:			//关闭会议
		OnReqEslCloseMeet(json, strJson, iMsgType);
		break;
		
	default:
		break;
	}
}

//Pkg包转换json
bool CEslMeetAdapter::eslBuildJson(int iMsgType, char *pPayload, QJsonObject &jsonRet)
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
	case ESL_MSG_CREATEMEET_RESP:
		bRet = OnRespEslCreateMeet(json, jsonRet);
		break;
		
	case ESL_MSG_ADDMEETMEMB_RESP:
		bRet = OnRespEslAddMeetMemb(json, jsonRet);
		break;
		
	case ESL_MSG_DELMEETMEMB_RESP:
		bRet = OnRespEslDelMeetMemb(json, jsonRet);
		break;
		
	case ESL_MSG_MUTEMEETMEMB_RESP:
		bRet = OnRespEslMuteMeetMemb(json, jsonRet);
		break;
		
	case ESL_MSG_SILENCEMEETMEMB_RESP:
		bRet = OnRespEslSilenceMeetMemb(json, jsonRet);
		break;
		
	case ESL_MSG_SPLITSCREENMEET_RESP:
		bRet = OnRespEslSplitScrMeet(json, jsonRet);
		break;
		
	case ESL_MSG_SPEECHMEETMEMB_RESP:
		bRet = OnRespEslSpeechMeetMemb(json, jsonRet);
		break;
		
	case ESL_MSG_CLOSEMEET_RESP:
		bRet = OnRespEslCloseMeet(json, jsonRet);
		break;
		
	default:
		break;
	}
	
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
//创建会议Req
void CEslMeetAdapter::OnReqEslCreateMeet(QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg(json["msg"].toObject());
	if (jsonMsg.isEmpty())
	{
		return;
	}
	
	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("meetid", jsonMsg["meetid"].toInt());
	jsonRet.insert("token", jsonMsg["ternimalId"].toInt());
	
	iMsgType = ESL_MSG_CREATEMEET_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//创建会议Resp
bool CEslMeetAdapter::OnRespEslCreateMeet(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["meetid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}
	
	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("meetid", std::stoi(strMeetId));
	jsonData.insert("meetcode", strMeetId.c_str());
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", SCH_MEETING_CREATE_RESP);
	
	return true;
}

//增加会议成员Req
void CEslMeetAdapter::OnReqEslAddMeetMemb(QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg(json["msg"].toObject());
	if (jsonMsg.isEmpty())
	{
		return;
	}
	
	if (!jsonMsg.contains("members"))
	{
		return;
	}
	
	if (jsonMsg["members"].toArray().isEmpty())
	{
		return;
	}
	
	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("meetid", jsonMsg["meetid"].toInt());
	jsonRet.insert("token", jsonMsg["ternimalId"].toString());
	jsonRet.insert("memlist", jsonMsg["members"].toArray());
	
	iMsgType = ESL_MSG_ADDMEETMEMB_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//增加会议成员Resp
bool CEslMeetAdapter::OnRespEslAddMeetMemb(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["meetid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}
	
	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("meetid", std::stoi(strMeetId));
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", SCH_MEETING_MEMB_ADD_RESP);
	
	return true;
}

//删除会议成员Req
void CEslMeetAdapter::OnReqEslDelMeetMemb(QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg(json["msg"].toObject());
	if (jsonMsg.isEmpty())
	{
		return;
	}
	
	if (!jsonMsg.contains("members"))
	{
		return;
	}
	
	if (jsonMsg["members"].toArray().isEmpty())
	{
		return;
	}
	
	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("meetid", jsonMsg["meetid"].toInt());
	jsonRet.insert("token", jsonMsg["ternimalId"].toString());
	jsonRet.insert("memlist", jsonMsg["members"].toArray());
	
	iMsgType = ESL_MSG_DELMEETMEMB_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//删除会议成员Resp
bool CEslMeetAdapter::OnRespEslDelMeetMemb(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["meetid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}
	
	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("meetid", std::stoi(strMeetId));
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", SCH_MEETING_MEMB_KICKOUT_RESP);
	
	return true;
}

//静音会议成员Req
void CEslMeetAdapter::OnReqEslMuteMeetMemb(QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg(json["msg"].toObject());
	if (jsonMsg.isEmpty())
	{
		return;
	}
}

//静音会议成员Resp
bool CEslMeetAdapter::OnRespEslMuteMeetMemb(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["meetid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}

	return true;
}

//禁言会议成员Req
void CEslMeetAdapter::OnReqEslSilenceMeetMemb(QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg(json["msg"].toObject());
	if (jsonMsg.isEmpty())
	{
		return;
	}
	
	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("meetid", jsonMsg["meetid"].toInt());
	jsonRet.insert("token", jsonMsg["ternimalId"].toString());
	
	iMsgType = ESL_MSG_SILENCEMEETMEMB_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//禁言会议成员Resp
bool CEslMeetAdapter::OnRespEslSilenceMeetMemb(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["meetid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}
	
	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("meetid", std::stoi(strMeetId));
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", SCH_MEETING_MEMB_MUTE_RESP);
	
	return true;
}

//视频会议分屏Req
void CEslMeetAdapter::OnReqEslSplitScrMeet(QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg(json["msg"].toObject());
	if (jsonMsg.isEmpty())
	{
		return;
	}
	
	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("meetid", jsonMsg["meetid"].toInt());
	jsonRet.insert("splitscreen", jsonMsg["splitnum"].toInt());
	jsonRet.insert("token", jsonMsg["ternimalId"].toString());
	
	iMsgType = ESL_MSG_SPLITSCREENMEET_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//视频会议分屏Resp
bool CEslMeetAdapter::OnRespEslSplitScrMeet(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["meetid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}
	
	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("meetid", std::stoi(strMeetId));
	jsonData.insert("meetcode", strMeetId.c_str());
	jsonData.insert("splitnum", "");
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", SCH_MEETING_SPLIT_SCREEN_SET_RESP);
	
	return true;
}

//演讲会议成员Req
void CEslMeetAdapter::OnReqEslSpeechMeetMemb(QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg(json["msg"].toObject());
	if (jsonMsg.isEmpty())
	{
		return;
	}
	
	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("meetid", jsonMsg["meetid"].toInt());
	jsonRet.insert("speecher", jsonMsg[""].toString());
	jsonRet.insert("token", jsonMsg["ternimalId"].toString());
	
	iMsgType = ESL_MSG_SPLITSCREENMEET_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//演讲会议成员Resp
bool CEslMeetAdapter::OnRespEslSpeechMeetMemb(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["meetid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}
	
	std::string strMeetId = json["meetid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}
	
	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("meetid", std::stoi(strMeetId));
	jsonData.insert("meetcode", strMeetId.c_str());
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", SCH_MEETING_VIDEO_SPEECH_SET_RESP);
	
	return true;
}

//关闭会议Req
void CEslMeetAdapter::OnReqEslCloseMeet(QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg(json["msg"].toObject());
	if (jsonMsg.isEmpty())
	{
		return;
	}
	
	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("meetid", jsonMsg["meetid"].toInt());
	jsonRet.insert("token", jsonMsg["ternimalId"].toString());
	
	iMsgType = ESL_MSG_SPLITSCREENMEET_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//关闭会议Resp
bool CEslMeetAdapter::OnRespEslCloseMeet(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	std::string strMeetId = json["meetid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}
	
	std::string strMeetId = json["meetid"].toString().toStdString();
	if (strMeetId == "")
	{
		return false;
	}
	
	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("meetid", std::stoi(strMeetId));
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", "");
	
	return true;
}