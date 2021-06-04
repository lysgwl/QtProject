#include "elsDataAdapter.h"

CElsDataAdapter::CElsDataAdapter()
{
}

CElsDataAdapter::~CElsDataAdapter()
{
}

bool CElsDataAdapter::elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson)
{
	bool bResult = false;

	switch (iPkgType)
	{
	case PKG_TYPE_BASIC:
		bResult = buildBasePkg(pstPkg, strJson);
		break;

	case PKG_TYPE_CONFIG:
		bResult = buildConfigPkg(pstPkg, strJson);
		break;

	default:
		break;
	}

	return bResult;
}

bool CElsDataAdapter::buildBasePkg(void *pstPkg, std::string &strJson)
{
	stBasicPkgFormat *pstBasicMsg = static_cast<stBasicPkgFormat*>(pstPkg);
	if (pstBasicMsg == Q_NULLPTR)
	{
		return false;
	}
	
	switch (pstBasicMsg->iMsgType)
	{
	case BASIC_MSG_LOGINEXT_REQ:
		OnReqElsLogin(pstBasicMsg, strJson);
		break;
		
	case BASIC_MSG_LOGOUT_IND:
		OnReqElsLoginOut(pstBasicMsg, strJson);
		break;
		
	case BASIC_MSG_HEARTBEAT:
		OnReqElsHeartBeat(pstBasicMsg, strJson);
		break;
		
	default:
		break;
	}
	
	return true;
}

bool CElsDataAdapter::buildConfigPkg(void *pstPkg, std::string &strJson)
{
	stCfgPkgFormat *pstCfgMsg = static_cast<stCfgPkgFormat*>(pstPkg);
	if (pstCfgMsg == Q_NULLPTR || pPkgBuf == Q_NULLPTR)
	{
		return false;
	}
	
	return true;
}

void CElsDataAdapter::OnReqElsLogin(const stBasicPkgFormat *pstPkg, std::string &strJson)
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
	
	strJson = std::string(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

void CElsDataAdapter::OnReqElsLoginOut(const stBasicPkgFormat *pstPkg, std::string &strJson)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
	
	QJsonObject json;
}

void CElsDataAdapter::OnReqElsHeartBeat(const stBasicPkgFormat *pstPkg, std::string &strJson)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
	
	QJsonObject json;
}