#include "eslNetControl.h"

#include "IRztMessageReceiver.h"

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

//////////////////////////////////////////////////////////////////////////
//是否开启服务
bool CEslNetControl::isEslServer()
{
	return true;
}

//消息请求
void CEslNetControl::eslSendMessage(const QJsonObject &json, QByteArray &arSend)
{
	if (json.isEmpty() || !json.contains("businessType"))
	{
		return;
	}
	
	int iMsgType = 0;
	int iPkgType = 0;
	
	std::string strJson;
	QJsonObject jsonMsg(json);
	
	switch(static_cast<int>(jsonMsg["businessType"].toInt()))
	{
	case PKG_TYPE_BASIC:
	case PKG_TYPE_CONFIG:
		m_pDataAdapter->eslBuildPkg(jsonMsg, strJson, iPkgType, iMsgType);
		break;
		
	case PKG_TYPE_SCHEDULE:
		break;
		
	default:
		break;
	}
	
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

//消息接收
bool CEslNetControl::eslRecvMessage(char *pPkgBuf, std::string &strUserNum)
{
	stProtocolPkgHeader *pstPkgHeader = reinterpret_cast<stProtocolPkgHeader*>(pPkgBuf);
	if (pstPkgHeader == Q_NULLPTR || pstPkgHeader->iBodyLength <= 0)
	{
		return false;
	}
	
	if (pstPkgHeader->iProtocolId != static_cast<int>(htonl(ESL_PROTOCOL_ID)))
	{
		return false;
    }
	
	QJsonObject jsonRet;
	int iPkgType = static_cast<int>(pstPkgHeader->cPkgType);
	
	if (iPkgType == ESL_PKG_TYPE_DATA)
	{
		if (!m_pDataAdapter->eslBuildJson(pstPkgHeader->cMsgType, pstPkgHeader->body, jsonRet))
		{
			return false;
		}
	}
	else if (iPkgType == ESL_PKG_TYPE_MEET)
	{
	}
	else if (iPkgType == ESL_PKG_TYPE_STATUS)
	{
	}
	else
	{
		return false;
	}
	
	std::string strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
	
	ObjectPtr<IRztMessageReceiver> msgReceiver;
	msgReceiver->handleMessage(strJson.c_str(), strUserNum.c_str());
	
	return true;
}