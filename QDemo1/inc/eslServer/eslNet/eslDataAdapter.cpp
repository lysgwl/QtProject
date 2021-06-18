#include "eslDataAdapter.h"

#include "RztCommonUtils.h"

CEslDataAdapter::CEslDataAdapter()
{
}

CEslDataAdapter::~CEslDataAdapter()
{
}

//Pkg组包请求
bool CEslDataAdapter::eslBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType)
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
bool CEslDataAdapter::eslParsePkg(int iMsgType, char *pPayload, void* pstEvent)
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
	
    bool bResult = false;

	switch (iMsgType)
	{
    case ESL_MSG_LOGIN_RESP:
		bResult = buildBaseRespPkg(true, BASIC_MSG_LOGINEXT_RESP, pstEvent, json);
		break;

    case ESL_MSG_HEARTBEAT_RESP:
		bResult = buildBaseRespPkg(true, BASIC_MSG_HEARTBEAT_ACK, pstEvent, json);
		break;	
	
	default:
		break;
	}

    return bResult;
}

//Pkg包转换json
bool CEslDataAdapter::eslBuildJson(int iPkgType, void* pstEvent, QJsonObject &json)
{
	bool bResult = false;
	
    switch (iPkgType)
	{
	case PKG_TYPE_BASIC:
		bResult = buildBaseRespPkg(false, -1, pstEvent, json);
		break;
		
	case PKG_TYPE_CONFIG:
		bResult = buildConfigRespPkg(false, -1, pstEvent, json);
		break;
		
	default:
		break;
	}
	
	return bResult;
}

//stBasicPkgFormat请求
bool CEslDataAdapter::buildBaseReqPkg(void *pstPkg, std::string &strJson, int &iMsgType)
{
	stBasicPkgFormat *pstBasicMsg = static_cast<stBasicPkgFormat*>(pstPkg);
	if (pstBasicMsg == Q_NULLPTR)
	{
		return false;
	}
	
	switch (pstBasicMsg->iMsgType)
	{
	case BASIC_MSG_LOGINEXT_REQ:
		OnReqEslLogin(pstBasicMsg, strJson, iMsgType);
		break;
		
	case BASIC_MSG_LOGOUT_IND:
		OnReqEslLoginOut(pstBasicMsg, strJson, iMsgType);
		break;
		
	case BASIC_MSG_HEARTBEAT:
		OnReqEslHeartBeat(pstBasicMsg, strJson, iMsgType);
		break;
		
	default:
		break;
	}
	
	return true;
}

//stCfgPkgFormat请求
bool CEslDataAdapter::buildConfigReqPkg(void *pstPkg, std::string &strJson, int &iMsgType)
{
	stCfgPkgFormat *pstCfgMsg = static_cast<stCfgPkgFormat*>(pstPkg);
    if (pstCfgMsg == Q_NULLPTR)
	{
		return false;
	}
	
    std::cout << strJson << iMsgType << std::endl;
	return true;
}

//stBasicPkgFormat回复
bool CEslDataAdapter::buildBaseRespPkg(bool bFlag, int iMsgType, void* pstEvent, QJsonObject &json)
{
    stBasicPkgFormat jstBasicPkgFmt;
	stBasicPkgFormat *pstBasicPkgFmt = Q_NULLPTR;

    stMESSAGE *pstMsg = static_cast<stMESSAGE*>(pstEvent);
	if (pstMsg == Q_NULLPTR || pstMsg->pvMessage == Q_NULLPTR)
	{
		return false;
	}

	if (bFlag == true)
	{
        memset(&jstBasicPkgFmt, 0x0, sizeof(stBasicPkgFormat));
		pstBasicPkgFmt = &jstBasicPkgFmt;
        pstMsg->ePskType = PKG_TYPE_BASIC;
	}
	else
	{
		pstBasicPkgFmt = static_cast<stBasicPkgFormat*>(pstMsg->pvMessage);
		iMsgType = pstBasicPkgFmt->iMsgType;
	}

	switch (iMsgType)
	{
	case BASIC_MSG_LOGINEXT_RESP:
		OnRespEslLogin(bFlag, pstBasicPkgFmt, json);
		break;

	case BASIC_MSG_HEARTBEAT_ACK:
		OnRespEslHeartBeat(bFlag, pstBasicPkgFmt, json);
		break;	
	
	default:
		break;
	}

	if (bFlag == true)
	{
		memcpy(pstMsg->pvMessage, pstBasicPkgFmt, sizeof(stBasicPkgFormat));
	}

	return true;
}

//stCfgPkgFormat回复
bool CEslDataAdapter::buildConfigRespPkg(bool bFlag, int iMsgType, void* pstEvent, QJsonObject &json)
{
    stCfgPkgFormat jstCfgPkgFmt;
	stCfgPkgFormat *pstCfgPkgFmt = Q_NULLPTR;

    stMESSAGE *pstMsg = static_cast<stMESSAGE*>(pstEvent);
	if (pstMsg == Q_NULLPTR || pstMsg->pvMessage == Q_NULLPTR)
	{
		return false;
	}

	if (bFlag == true)
	{
        memset(&jstCfgPkgFmt, 0x0, sizeof(stCfgPkgFormat));
		pstCfgPkgFmt = &jstCfgPkgFmt;
	}
	else
	{
		pstCfgPkgFmt = static_cast<stCfgPkgFormat*>(pstMsg->pvMessage);
		iMsgType = pstCfgPkgFmt->iMsgType;
	}

	switch (iMsgType)
	{
	default:
		break;
	}

	if (bFlag == true)
	{
		memcpy(pstMsg->pvMessage, pstCfgPkgFmt, sizeof(stCfgPkgFormat));
	}

	return true;
}

//登录Req
void CEslDataAdapter::OnReqEslLogin(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType)
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
	json.insert("devmask", RztCommonUtils::getDeviceId());
	
    iMsgType = ESL_MSG_LOGIN_REQ;
	strJson = std::string(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

//注销Req
void CEslDataAdapter::OnReqEslLoginOut(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
	
	QJsonObject json;
	json.insert("seq", pstPkg->iReqId);
	json.insert("lgnum", pstPkg->acUsrName);
	
    iMsgType = ESL_MSG_LOGOUT_IND;
	strJson = std::string(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

//心跳Req
void CEslDataAdapter::OnReqEslHeartBeat(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
	
	QJsonObject json;
	json.insert("seq", pstPkg->iReqId);
	json.insert("lgnum", pstPkg->acUsrName);
	
    iMsgType = ESL_MSG_HEARTBEAT_REQ;
	strJson = std::string(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

//登录Resp
void CEslDataAdapter::OnRespEslLogin(bool bFlag, stBasicPkgFormat *pstPkg, QJsonObject &json)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
	
	if (bFlag)
	{
		pstPkg->iMsgType = BASIC_MSG_LOGINEXT_RESP;
        eslParseSegment(json, PKG_TYPE_BASIC, pstPkg);
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
void CEslDataAdapter::OnRespEslHeartBeat(bool bFlag, stBasicPkgFormat *pstPkg, QJsonObject &json)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
	
	if (bFlag)
	{
		pstPkg->iMsgType = BASIC_MSG_HEARTBEAT_ACK;
        eslParseSegment(json, PKG_TYPE_BASIC, pstPkg);
	}
	else
	{
		json.insert("msgType", pstPkg->iMsgType);
		
		QJsonObject data;
		data.insert("requestId", pstPkg->iReqId);
		data.insert("webTime", pstPkg->acData);
        //data.insert("webMTime", int(stMsg.iRight/1000.0));
        //json.insert("feedback", data);
	}
}
