#include "eslDataAdapter.h"

#include "RztCommonUtils.h"

CEslDataAdapter::CEslDataAdapter()
{
}

CEslDataAdapter::~CEslDataAdapter()
{
}

//////////////////////////////////////////////////////////////////////////
//Pkg组包请求
void CEslDataAdapter::eslBuildPkg(QJsonObject &json, std::string &strJson, int &iPkgType, int &iMsgType)
{
	switch (static_cast<int>(json["msgType"].toInt()))
	{
	case BASIC_MSG_LOGINEXT_REQ:
		iPkgType = ESL_PKG_TYPE_DATA;
		OnReqEslLogin(json, strJson, iMsgType);
		break;
		
	case BASIC_MSG_LOGOUT_IND:
		iPkgType = ESL_PKG_TYPE_DATA;
		OnReqEslLoginOut(json, strJson, iMsgType);
		break;
		
	case BASIC_MSG_HEARTBEAT:
		iPkgType = ESL_PKG_TYPE_DATA;
		OnReqEslHeartBeat(json, strJson, iMsgType);
		break;

	default:
		break;
	}
}

//Pkg包转换json
bool CEslDataAdapter::eslBuildJson(int iMsgType, char *pPayload, QJsonObject &jsonRet)
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
	
	if (iMsgType == ESL_MSG_LOGIN_RESP)
	{
		if (!OnRespEslLogin(json, jsonRet))
		{
			return false;
		}
	}
	else if (iMsgType == ESL_MSG_HEARTBEAT_RESP)
	{
		if (!OnRespEslHeartBeat(json, jsonRet))
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
//登录Req
void CEslDataAdapter::OnReqEslLogin(QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg(json["msg"].toObject());
	if (jsonMsg.isEmpty())
	{
		return;
	}
	
	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgtype", "PC");
	jsonRet.insert("lgnum", jsonMsg["userName"].toString());
	jsonRet.insert("lgpwd", jsonMsg["password"].toString());
	jsonRet.insert("devmask", jsonMsg["hostId"].toString()); //RztCommonUtils::getDeviceId()
	
	iMsgType = ESL_MSG_LOGIN_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//注销Req
void CEslDataAdapter::OnReqEslLoginOut(QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg(json["msg"].toObject());
	if (jsonMsg.isEmpty())
	{
		return;
	}
	
	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("token", jsonMsg["ternimalId"].toInt());
	
    iMsgType = ESL_MSG_LOGOUT_IND;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//心跳Req
void CEslDataAdapter::OnReqEslHeartBeat(QJsonObject &json, std::string &strJson, int &iMsgType)
{
	QJsonObject jsonMsg(json["msg"].toObject());
	if (jsonMsg.isEmpty())
	{
		return;
	}
	
	QJsonObject jsonRet;
	jsonRet.insert("seq", json["requestId"].toInt());
	jsonRet.insert("lgnum", json["connector"].toString());
	jsonRet.insert("token", jsonMsg["ternimalId"].toInt());
	
    iMsgType = ESL_MSG_HEARTBEAT_REQ;
	strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
}

//登录Resp
bool CEslDataAdapter::OnRespEslLogin(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	if (json["result"].toInt() != 0 || json["token"].toString() == "")
	{
		return false;
	}
	
	QJsonObject jsonData;
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("terminalId", json["token"].toString());
	jsonData.insert("terminalType", json["lgtype"].toString());
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", BASIC_MSG_LOGINEXT_RESP);
	
	return true;
}

//心跳Resp
bool CEslDataAdapter::OnRespEslHeartBeat(const QJsonObject &json, QJsonObject &jsonRet)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	QJsonObject jsonData;
	std::string strTime = std::to_string(json["curtime"].toInt());
	
	jsonData.insert("requestId", json["seq"].toInt());
	jsonData.insert("webTime", strTime.c_str());
	jsonData.insert("webMTime", 0);
	
	jsonRet.insert("feedback", jsonData);
	jsonRet.insert("msgType", BASIC_MSG_HEARTBEAT_ACK);
	
	return true;
}
