#include "eslServer.h"

CEslServer::CEslServer()
{
    m_pDataAdapter = new CEslDataAdapter;
	//m_pMeetAdapter = new CElsMeetAdapter;
	//m_pStatusAdapter = new CElsStatusAdapter;
}

CEslServer::~CEslServer()
{
	if (m_pDataAdapter)
	{
		delete m_pDataAdapter;
		m_pDataAdapter = Q_NULLPTR;
	}
		
	/*if (m_pMeetAdapter)
	{
		delete m_pMeetAdapter;
		m_pMeetAdapter = Q_NULLPTR;
	}
	
	if (m_pStatusAdapter)
	{
		delete m_pStatusAdapter;
		m_pStatusAdapter = Q_NULLPTR;
	}*/
}

//是否支持els服务
bool CEslServer::isEslServer(const QJsonObject &jsonObject)
{
    if (jsonObject.isEmpty())
	{
		return false;
	}
	
	if (!jsonObject.contains("protocol"))
	{
		return false;
	}
	
    uint uiPkgId = static_cast<uint>(jsonObject.value("protocol").toInt());
    if (uiPkgId != htonl(ESL_PROTOCOL_ID))
	{
		return false;
    }
	
	return true;
}

//消息请求
bool CEslServer::eslSendMessage(const stMESSAGE *pstMsg, QByteArray &arSend)
{
	bool bResult = false;
	
	if (pstMsg == Q_NULLPTR)
	{
		return false;
	}

    int iPkgType = 0;
    int iMsgType = 0;
	
    std::string strJson;
	switch(pstMsg->ePskType)
	{
	case PKG_TYPE_BASIC:
	case PKG_TYPE_CONFIG:
        bResult = m_pDataAdapter->eslBuildPkg(pstMsg->ePskType, pstMsg->pvMessage, strJson, iMsgType);
        iPkgType = ESL_PKG_TYPE_DATA;
		break;
		
	case PKG_TYPE_SCHEDULE:
		//bResult = m_pMeetAdapter->elsBuildPkg(pstMsg->ePskType, pstMsg->pvMessage, strJson, iMsgType);
        iPkgType = ESL_PKG_TYPE_MEET;
		break;
	
	default:
		break;
	}
	
	if (bResult)
	{
        char acBuffer[AC_MAX_PROTOCOL_PKG_LEN];
        stTerminalPkgHeader *pstPkgHeader = reinterpret_cast<stTerminalPkgHeader*>(acBuffer);

        pstPkgHeader->iProtocolId = static_cast<int>(htonl(ESL_PROTOCOL_ID));
        pstPkgHeader->cPkgType = static_cast<char>(iPkgType);
        pstPkgHeader->cMsgType = static_cast<char>(iMsgType);
		
        int iLen = static_cast<int>(strJson.length());
        pstPkgHeader->iBodyLength = static_cast<int>(iLen);

        strncpy(pstPkgHeader->body, strJson.c_str(), strJson.length());
        arSend = QByteArray(acBuffer, iLen);
	}
	
	return bResult;
}

//Pkg包解析
bool CEslServer::eslParsePkg(char *pPkgBuf, void *pstEvent)
{
	bool bResult = false;
	
	stTerminalPkgHeader *pstPkgHeader = Q_NULLPTR;
	if (parsePkg(pPkgBuf, &pstPkgHeader) == false)
	{
		return false;
	}
	
	switch (pstPkgHeader->cPkgType)
	{
	case ESL_PKG_TYPE_DATA:
		bResult = m_pDataAdapter->eslParsePkg(pstPkgHeader->cMsgType, pstPkgHeader->body, pstEvent);
		break;
		
	case ESL_PKG_TYPE_MEET:
		//bResult = m_pMeetAdapter->eslParsePkg(pstPkgHeader->cMsgType, pstPkgHeader->body, pstEvent);
		break;
		
	case ESL_PKG_TYPE_STATUS:
		//bResult = m_pStatusAdapter->eslParsePkg(pstPkgHeader->cMsgType, pstPkgHeader->body, pstEvent);
		break;
		
	default:
		break;
	}
	
	return bResult;
}

//消息转换json
void CEslServer::eslBuildJson(stMESSAGE *pstMsg, std::string &strJson)
{
    if (pstMsg == Q_NULLPTR)
	{
		return;
	}
	
    QJsonObject json;
    int iPkgType = pstMsg->ePskType;

    switch (iPkgType)
	{
	case PKG_TYPE_BASIC:
    case PKG_TYPE_CONFIG:
        m_pDataAdapter->eslBuildJson(iPkgType, pstMsg, json);
		break;
	
	case PKG_TYPE_SCHEDULE:
		//m_pMeetAdapter->eslBuildJson(iPkgType, pstMsg, json);
		break;
	
	case PKG_TYPE_EVENT:
		//m_pStatusAdapter->eslBuildJson(iPkgType, pstMsg, json);
		break;
		
    default:
		break;
	}

    strJson = std::string(QJsonDocument(json).toJson(QJsonDocument::Compact));
}

//Pkg包头解析
bool CEslServer::parsePkg(char *pPkgBuf, stTerminalPkgHeader **pstPkgHeader)
{
    *pstPkgHeader = reinterpret_cast<stTerminalPkgHeader*>(pPkgBuf);
	if ((*pstPkgHeader) == Q_NULLPTR)
	{
		return false;
    }

    if ((*pstPkgHeader)->iProtocolId != static_cast<int>(htonl(ESL_PROTOCOL_ID)))
	{
		return false;
    }
	
	char cPkgType = (*pstPkgHeader)->cPkgType;
	if (cPkgType != ESL_PKG_TYPE_DATA && 
		cPkgType != ESL_PKG_TYPE_MEET && 
		cPkgType != ESL_PKG_TYPE_STATUS)
	{
		return false;
	}
	
	if ((*pstPkgHeader)->iBodyLength <= 0)
	{
		return false;
	}
	
	return true;
}
