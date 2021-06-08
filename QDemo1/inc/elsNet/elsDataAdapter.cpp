#include "elsDataAdapter.h"

CElsDataAdapter::CElsDataAdapter()
{
}

CElsDataAdapter::~CElsDataAdapter()
{
}

//Pkg组包请求
bool CElsDataAdapter::elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType)
{
	bool bResult = false;

	switch (iPkgType)
	{
	case PKG_TYPE_BASIC:
		bResult = buildBaseReqPkg(pstPkg, strJson, iMsgType);
		break;

	case PKG_TYPE_CONFIG:
		bResult = buildBaseReqPkg(pstPkg, strJson, iMsgType);
		break;

	default:
		break;
	}

	return bResult;
}

//Pkg包解析
bool CElsDataAdapter::elsParsePkg(int iPkgType, int iMsgType, char *pPayload, void* pstEvent)
{
	bool bResult = false;
	
	stCfgPkgFormat jstCfgPkgFmt = {0};
	stBasicPkgFormat jstBasicPkgFmt = {0};
	
	if (pPayload == Q_NULLPTR)
	{
		return false;
	}
	
	QJsonObject json = QJsonDocument::fromJson(pPayload).object();
	if (json.isEmpty())
	{
		return false;
	}
	
	stMESSAGE *pstMessage = (stMESSAGE *)pstEvent;
	if (pstMessage == Q_NULLPTR || pstMessage->pvMessage == Q_NULLPTR)
	{
		return false;
	}
	
	pstMessage->ePskType = iPkgType;
	switch (iMsgType)
	{
	case BASIC_MSG_LOGINEXT_RESP:
		pstMessage->ePskType = PKG_TYPE_BASIC;
		OnRespElsLogin(true, &jstBasicPkgFmt, json);
		break;
		
	case BASIC_MSG_HEARTBEAT_ACK:
		pstMessage->ePskType = PKG_TYPE_BASIC;
		OnRespElsHeartBeat(true, &jstBasicPkgFmt, json);
		break;
		
	default:
		break;
	}
	
	if (pstMessage->ePskType == PKG_TYPE_BASIC)
	{
		memcpy(pstMessage->pvMessage, &jstBasicPkgFmt, sizeof(stBasicPkgFormat));
	}
	else if (pstMessage->ePskType == PKG_TYPE_CONFIG)
	{
		memcpy(pstMessage->pvMessage, &jstCfgPkgFmt, sizeof(stCfgPkgFormat));
	}
	else
	{
		return false;
	}
	
	return true;
}

//Pkg包转换json
bool CElsDataAdapter::elsBuildJson(void* pstEvent, QJsonObject &json)
{
	bool bResult = false;
	
	stMESSAGE *pstMessage = (stMESSAGE *)pstEvent;
	if (pstMessage == Q_NULLPTR || pstMessage->pvMessage == Q_NULLPTR)
	{
		return false;
	}
	
	swtich (pMessage->ePskType)
	{
	case PKG_TYPE_BASIC:
		bResult = buildBaseRespPkg(pstMessage->pvMessage, json);
		break;
		
	case PKG_TYPE_CONFIG:
		bResult = buildConfigRespPkg(pstMessage->pvMessage, json);
		break;
		
	default:
		break;
	}
	
	return bResult;
}

//stBasicPkgFormat请求
bool CElsDataAdapter::buildBaseReqPkg(void *pstPkg, std::string &strJson, int &iMsgType)
{
	stBasicPkgFormat *pstBasicMsg = static_cast<stBasicPkgFormat*>(pstPkg);
	if (pstBasicMsg == Q_NULLPTR)
	{
		return false;
	}
	
	switch (pstBasicMsg->iMsgType)
	{
	case BASIC_MSG_LOGINEXT_REQ:
		OnReqElsLogin(pstBasicMsg, strJson, iMsgType);
		break;
		
	case BASIC_MSG_LOGOUT_IND:
		OnReqElsLoginOut(pstBasicMsg, strJson, iMsgType);
		break;
		
	case BASIC_MSG_HEARTBEAT:
		OnReqElsHeartBeat(pstBasicMsg, strJson, iMsgType);
		break;
		
	default:
		break;
	}
	
	return true;
}

//stCfgPkgFormat请求
bool CElsDataAdapter::buildConfigReqPkg(void *pstPkg, std::string &strJson, int &iMsgType)
{
	stCfgPkgFormat *pstCfgMsg = static_cast<stCfgPkgFormat*>(pstPkg);
	if (pstCfgMsg == Q_NULLPTR || pPkgBuf == Q_NULLPTR)
	{
		return false;
	}
	
	return true;
}

//stBasicPkgFormat回复
bool CElsDataAdapter::buildBaseRespPkg(void* pstPkg, QJsonObject &json)
{
	if (pstPkg == Q_NULLPTR)
	{
		return false;
	}
	
	int iMsgType = static_cast<stBasicPkgFormat*>(pstPkg)->iMsgType;
	switch (iMsgType)
	{
	case BASIC_MSG_LOGINEXT_RESP:
		OnRespElsLogin(false, pstPkg, json);
		break;
		
	case BASIC_MSG_HEARTBEAT_ACK:
		OnRespElsHeartBeat(false, pstPkg, json);
		break;
		
	default:
		break;
	}
	
	return true;
}

//stCfgPkgFormat回复
bool CElsDataAdapter::buildConfigRespPkg(void* pstPkg, QJsonObject &json)
{
	if (pstPkg == Q_NULLPTR)
	{
		return false;
	}
	
	int iMsgType = static_cast<stBasicPkgFormat*>(pstPkg)->iMsgType;
	switch (iMsgType)
	{
	default:
		break;
	}
	
	return true;
}

//登录Req
void CElsDataAdapter::OnReqElsLogin(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
	
	QJsonObject json;
	json.insert("seq", pstPkg->iReqId);
	json.insert("lgtype", "PC");
	json.insert("lgnum", pstPkg->acUsrName);
	json.insert("lgpwd", pstPkg->acPwd);
	
	iMsgType = ELS_MSG_LOGIN_REQ;
	strJson = std::string(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

//注销Req
void CElsDataAdapter::OnReqElsLoginOut(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
	
	QJsonObject json;
	json.insert("seq", pstPkg->iReqId);
	json.insert("lgnum", pstPkg->acUsrName);
	
	iMsgType = ELS_MSG_LOGOUT_IND;
	strJson = std::string(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

//心跳Req
void CElsDataAdapter::OnReqElsHeartBeat(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
	
	QJsonObject json;
	json.insert("seq", pstPkg->iReqId);
	json.insert("lgnum", pstPkg->acUsrName);
	
	iMsgType = ELS_MSG_HEARTBEAT_REQ;
	strJson = std::string(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

//登录Resp
void CElsDataAdapter::OnRespElsLogin(bool bFlag, stBasicPkgFormat *pstPkg, QJsonObject &json)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
	
	if (bFlag)
	{
		pstPkg->iMsgType = BASIC_MSG_LOGINEXT_RESP;
		elsParseSegment(json, PKG_TYPE_BASIC, pstPkg);
	}
	else
	{
		json.insert("msgType", pstPkg->iMsgType);
		
		QJsonObject data;
		data.insert("terminalId", pstPkg->iTerminalId);
		data.insert("requestId", pstPkg->iReqId);
		data.insert("terminalType", pstPkg->iTerminalType);
		json.insert("feedback", data);
	}
}

//心跳Resp
void CElsDataAdapter::OnRespElsHeartBeat(bool bFlag, stBasicPkgFormat *pstPkg, QJsonObject &json)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
	
	if (bFlag)
	{
		pstPkg->iMsgType = BASIC_MSG_HEARTBEAT_ACK;
		elsParseSegment(json, PKG_TYPE_BASIC, pstPkg);
	}
	else
	{
		json.insert("msgType", pstPkg->iMsgType);
		
		QJsonObject data;
		data.insert("requestId", pstPkg->iReqId);
		data.insert("webTime", pstPkg->acData);
		data.insert("webMTime", int(stMsg.iRight/1000.0));
		json.insert("feedback", data);
	}
}