#include "eslNetControl.h"

CEslNetControl::CEslNetControl()
{
    m_pDataAdapter = new CEslDataAdapter;
	//m_pMeetAdapter = new CElsMeetAdapter;
	//m_pStatusAdapter = new CElsStatusAdapter;
}

CEslNetControl::~CEslNetControl()
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

//是否开启服务
bool CEslNetControl::isEslServer()
{
	return true;
}

//消息请求
bool CEslNetControl::eslSendMessage(const stMESSAGE *pstMsg, QByteArray &arSend)
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
		memset(acBuffer, 0x0, AC_MAX_PROTOCOL_PKG_LEN);
        stProtocolPkgHeader *pstPkgHeader = reinterpret_cast<stProtocolPkgHeader*>(acBuffer);

        pstPkgHeader->iProtocolId = static_cast<int>(htonl(ESL_PROTOCOL_ID));
        pstPkgHeader->cPkgType = static_cast<char>(iPkgType);
        pstPkgHeader->cMsgType = static_cast<char>(iMsgType);
		
		size_t len = strJson.length();
        pstPkgHeader->iBodyLength = static_cast<int>(htonl(len));
        strncpy(pstPkgHeader->body, strJson.c_str(), len);
		
		len += sizeof(stProtocolPkgHeader);
        arSend = QByteArray(acBuffer, len);
	}
	
	return bResult;
}

//Pkg包解析
bool CEslNetControl::eslParsePkg(char *pPkgBuf, void *pstEvent)
{
	bool bResult = false;
	
	stProtocolPkgHeader *pstPkgHeader = Q_NULLPTR;
	if (!parsePkg(pPkgBuf, &pstPkgHeader))
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
void CEslNetControl::eslBuildJson(stMESSAGE *pstMsg, std::string &strJson)
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
bool CEslNetControl::parsePkg(char *pPkgBuf, stProtocolPkgHeader **pstPkgHeader)
{
    *pstPkgHeader = reinterpret_cast<stProtocolPkgHeader*>(pPkgBuf);
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
