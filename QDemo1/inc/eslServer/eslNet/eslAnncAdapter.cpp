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

	case SCH_PHONE_HANDLE_UPDATE_STATE_CMD:
		OnReqEslSpeakDetect(json, strJson, iMsgType);
		break;	

	case SCH_MEETING_GET_SPEC_PICTURE_REQ:
		OnReqEslRequestVideo(json, strJson, iMsgType);
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

	case ESL_MSG_STARTSPEAK_RESP:
	case ESL_MSG_STOPSPEAK_RESP:
		bRet = OnRespEslSpeakDetect(iMsgType, json, jsonRet);
		break;	

	case ESL_MSG_STARTVIDEO_REQ:	//视频查看对方处理消息
	case ESL_MSG_STOPVIDEO_REQ:
		bRet = OnNotifyRequestVideo(iMsgType, json, jsonRet);
		break;

	case ESL_MSG_STARTVIDEO_RESP:	//视频查看申请方处理消息
	case ESL_MSG_STOPVIDEO_RESP:
		bRet = OnRespEslRequestVideo(iMsgType, json, jsonRet);
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

//手咪对讲Req
void CEslAnncAdapter::OnReqEslSpeakDetect(const QJsonObject &json, std::string &strJson, int &iMsgType)
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

	int iState = jsonMsg["state"].toInt();
	if (iState == MMS_TALK)
	{
		iMsgType = ESL_MSG_STARTSPEAK_REQ;
		strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
	}
	else if (iState == MMS_NON_TALK)
	{
		iMsgType = ESL_MSG_STOPSPEAK_REQ;
		strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
	}
}

//开启手咪对讲Resp
bool CEslAnncAdapter::OnRespEslSpeakDetect(int iMsgType, const QJsonObject &json, QJsonObject &jsonRet)
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
	jsonRet.insert("businessType", PKG_TYPE_SCHEDULE);
	
	return true;
}

//请求视频查看Req
void CEslAnncAdapter::OnReqEslRequestVideo(const QJsonObject &json, std::string &strJson, int &iMsgType)
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

	std::string strUserNum = jsonMsg["targetnum"].toString().toStdString();
	if (strUserNum == "")
	{
		return;
	}

	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("atisid", strMeetId.c_str());
	jsonRet.insert("mem", strUserNum.c_str());
	jsonRet.insert("token", strTernimalId.c_str());

	int iViewState = jsonMsg["viewstate"].toInt();
	if (iViewState == ARVC_RequesterOpen)
	{
		iMsgType = ESL_MSG_STARTVIDEO_REQ;
		strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
	}
	else
	{
		if (iViewState == ARVC_RequesterCancel)
		{
			iMsgType = ESL_MSG_STOPVIDEO_REQ;
			strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
		}
	}
}

//请求视频查看Resp
bool CEslAnncAdapter::OnRespEslRequestVideo(int iMsgType, const QJsonObject &json, QJsonObject &jsonRet)
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
	jsonRet.insert("businessType", PKG_TYPE_SCHEDULE);
	
	return true;
}

//请求视频通知
bool CEslAnncAdapter::OnNotifyRequestVideo(int iMsgType, const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}

	std::string strMeetId = json["atisid"].toString().toStdString();
	std::string strTernimalId = json["token"].toString().toStdString();
	if (strMeetId == "" || strTernimalId == "")
	{
		return false;
	}

	std::string strReqNum = json["lgnum"].toString().toStdString();
	std::string strRecvNum = json["mem"].toString().toStdString();
	if (strReqNum == "" || strRecvNum == "")
	{
		return false;
	}

	int iViewState = ARVC_RequesterCancel;
	if (iMsgType == ESL_MSG_STARTVIDEO_REQ)
	{
		iViewState = ARVC_RequesterOpen;
	}
	else 
	{
		if (iMsgType == ESL_MSG_STOPVIDEO_REQ)
		{
			iViewState = ARVC_RequesterCancel;
		}
	}

	QJsonObject jsonData;
	jsonData.insert("preresult", AVE_SUCCESS);
	jsonData.insert("prereqid", json["seq"].toInt());
	jsonData.insert("preternimalid", std::stoi(strTernimalId));
	jsonData.insert("pretransactionid", std::stoi(strMeetId));

	jsonData.insert("uicfg", iViewState);	//请求查看视频
	jsonData.insert("videosender", json["lgnum"].toString());
	jsonData.insert("videoreceiver", json["mem"].toString());

	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", SCH_MEETING_GET_SPEC_PICTURE_RESP);
	jsonRet.insert("businessType", PKG_TYPE_SCHEDULE);

	return true;
}

//回复视频确认消息
void CEslAnncAdapter::OnReqEslConfirmVideo(const QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg = json.value("msg").toObject();
	if (jsonMsg.isEmpty())
	{
		return;
	}

	std::string strMeetId = std::to_string(jsonMsg["pretransactionid"].toInt());
	std::string strTernimalId = std::to_string(jsonMsg["preternimalid"].toInt());
	if (strMeetId == "" || strTernimalId == "")
	{
		return;
	}

	int iResult = -1;
	std::string strReqNum;
	std::string strRecvNum;

	int iViewState = jsonMsg["viewstate"].toInt();
	if (iViewState == ARVC_AnswerAgreen)
	{
		iResult = 0;
		strReqNum = jsonMsg["selfnum"].toString().toStdString();
		strRecvNum = jsonMsg["targetnum"].toString().toStdString();
	}
	else 
	{
		if (iViewState == ARVC_AnswerReject)
		{
			iResult = -1;
			strReqNum = jsonMsg["targetnum"].toString().toStdString();
			strRecvNum = jsonMsg["selfnum"].toString().toStdString();
		}
		else
		{
			return;
		}
	}

	QJsonObject jsonRet;
	jsonRet.insert("seq", jsonMsg["prereqid"].toInt());
	jsonRet.insert("result", iResult);
	jsonRet.insert("atisid", strMeetId.c_str());
	jsonRet.insert("token", strTernimalId.c_str());

	jsonRet.insert("lgnum", strReqNum.c_str());
	jsonRet.insert("mem", strRecvNum.c_str());

	iMsgType = ESL_MSG_STARTVIDEO_RESP;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}