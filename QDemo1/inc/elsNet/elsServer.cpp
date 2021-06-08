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

//�Ƿ�֧��els����
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

//��Ϣ����
bool CElsServer::elsSendMessage(stMESSAGE *pstMsg, QByteArray &arSend)
{
	bool bResult = false;
	
	int iPkgType = 0;
	int iMsgType = 0;

	std::string strJson;
	char acBuffer[AC_MAX_PROTOCOL_PKG_LEN] = {0};

	if (pstMsg == Q_NULLPTR)
	{
		return false;
	}
	
	switch(pstMsg->ePskType)
	{
	case PKG_TYPE_BASIC:
	case PKG_TYPE_CONFIG:
		bResult = m_pDataAdapter->elsBuildPkg(pstMsg->ePskType, pstMsg->pvMessage, strJson, iMsgType);
		iPkgType = ELS_PKG_TYPE_DATA;
		break;
		
	case PKG_TYPE_SCHEDULE:
		bResult = m_pMeetAdapter->elsBuildPkg(pstMsg->ePskType, pstMsg->pvMessage, strJson, iMsgType);
		iPkgType = ELS_PKG_TYPE_MEET;
		break;
	
	default:
		break;
	}
	
	if (bResult)
	{
		stProtocolPkgHeader *pstPkgHeader = (stProtocolPkgHeader *)acBuffer;
		pstPkgHeader->iProtocolId = htonl(ELS_PROTOCOL_ID);
		pstPkgHeader->cPkgType = iPkgType;
		pstPkgHeader->cMsgType = iMsgType;
		
		pstPkgHeader->iBodyLength = htonl(strJson.size());
		strncpy(pstPkgHeader->body, strJson.c_str(), strJson.size());
		
		arSend = QByteArray(acBuffer, strJson.size());
	}
	
	return bResult;
}

//Pkg������
bool CElsServer::elsParsePkg(char *pPkgBuf, int iLen, void *pstEvent)
{
	bool bResult = false;
	
	stTerminalPkgHeader *pstPkgHeader = Q_NULLPTR;
	if (parsePkg(pPkgBuf, &pstPkgHeader) == false)
	{
		return false;
	}
	
	switch (pstPkgHeader->cPkgType)
	{
	case ELS_PKG_TYPE_DATA:
		bResult = m_pDataAdapter->elsParsePkg(pstPkgHeader->cMsgType, pstPkgHeader->body, pstEvent);
		break;
		
	case ELS_PKG_TYPE_MEET:
		bResult = m_pMeetAdapter->elsParsePkg(pstPkgHeader->cMsgType, pstPkgHeader->body, pstEvent);
		break;
		
	case ELS_PKG_TYPE_STATUS:
		bResult = m_pStatusAdapter->elsParsePkg(pstPkgHeader->cMsgType, pstPkgHeader->body, pstEvent);
		break;
		
	default:
		break;
	}
	
	return bResult;
}

//��Ϣת��json
void CElsServer::elsBuildJson(const stMESSAGE *pMessage, std::string &strJson)
{
	if (pMessage == NULL)
	{
		return;
	}
	
	QJsonObject json;
	
	swtich (pMessage->ePskType)
	{
	case PKG_TYPE_BASIC:
	case PKG_TYPE_CONFIG:
		m_pDataAdapter->elsBuildJson(pMessage, json);
		break;
	
	case PKG_TYPE_SCHEDULE:
		m_pMeetAdapter->elsBuildJson(pMessage, json);
		break;
	
	case PKG_TYPE_EVENT:
		m_pStatusAdapter->elsBuildJson(pMessage, json);
		break;
		
	default
		break;
	}
}

//Pkg��ͷ����
bool CElsServer::parsePkg(char *pPkgBuf, stTerminalPkgHeader **pstPkgHeader)
{
	*pstPkgHeader = (stTerminalPkgHeader*)pPkgBuf;
	if ((*pstPkgHeader) == Q_NULLPTR)
	{
		return false;
	}
	
	if ((*pstPkgHeader)->iProtocolId != htonl(ELS_PROTOCOL_ID))
	{
		return false;
	}
	
	char cPkgType = (*pstPkgHeader)->cPkgType;
	if (cPkgType != ELS_PKG_TYPE_DATA && 
		cPkgType != ELS_PKG_TYPE_MEET && 
		cPkgType != ELS_PKG_TYPE_STATUS)
	{
		return false;
	}
	
	if ((*pstPkgHeader)->iBodyLength <= 0)
	{
		return false;
	}
	
	return true;
}