#include "elsServer.h"

CElsServer::CElsServer()
{
	m_pDataAdapter = new CElsDataAdapter();
	m_pMeetAdapter = new CElsMeetAdapter();
	m_pStatusAdapter = new CElsStatusAdapter();
}

CElsServer::~CElsServer()
{
	if (m_pDataAdapter)
	{
		delete m_pDataAdapter;
		m_pDataAdapter = Q_NULLPTR;
	}
	
	if (m_pMeetAdapter)
	{
		delete m_pMeetAdapter;
		m_pMeetAdapter = Q_NULLPTR;
	}
	
	if (m_pStatusAdapter)
	{
		delete m_pStatusAdapter;
		m_pStatusAdapter = Q_NULLPTR;
	}
}

bool CElsServer::isElsServer(const QJsonObject &jsonObject)
{
	if (jsonObject.isEmpty() || jsonObject.isNullObject())
	{
		return false;
	}
	
	if (!jsonObject.contains("protocol"))
	{
		return false;
	}
	
	uint uPkgId = jsonObject.value("protocol").toInt();
	if (uPkgId != htonl(ELS_PROTOCOL_ID))
	{
		return false;
	}
	
	return true;
}

bool CElsServer::elsSendMessage(stMESSAGE *pMessage, QByteArray &arSend)
{
	bool bResult = false;
	std::string strJson;

	if (pMessage == Q_NULLPTR)
	{
		return false;
	}
	
	switch(pMessage->ePskType)
	{
	case PKG_TYPE_BASIC:
	case PKG_TYPE_CONFIG:
		bResult = m_pDataAdapter->elsBuildPkg(pMessage->ePskType, pMessage->pvMessage, strJson);
		break;
		
	case PKG_TYPE_SCHEDULE:
		bResult = m_pMeetAdapter->elsBuildPkg(pMessage->ePskType, pMessage->pvMessage, strJson);
		break;
	
	default:
		break;
	}
	
	if (bResult)
	{
		arSend = QByteArray(strJson.c_str(), strJson.len());
	}
	
	return bResult;
}

bool CElsServer::elsParsePkg(char *pPkgBuf, int iLen, void *pstEvent)
{
	stTerminalPkgHeader stPkgHeader = {0};
	
	if (parsePkg(pPkgBuf, stPkgHeader) == false)
	{
		return false;
	}
	
	switch (stPkgHeader->cPkgType)
	{
	case ELS_PKG_TYPE_DATA:
		break;
		
	case ELS_PKG_TYPE_MEET:
		break;
		
	case ELS_PKG_TYPE_STATUS:
		break;
		
	default:
		break;
	}
	
	return true;
}

void CElsServer::elsBuildJson(const stMESSAGE *pMessage, std::string &strJson)
{
}

void CElsServer::buildPkg(stMESSAGE *pMessage, char *pPkgBuf, int &iLen)
{
}

void CElsServer::parsePkg(char *pPkgBuf, stTerminalPkgHeader &stPkgHeader)
{
}