#include "eslNetControl.h"

#include "IRztSettingMgr.h"
#include "IRztMessageReceiver.h"

CEslNetControl::CEslNetControl()
{
    m_pDataAdapter = new CEslDataAdapter;
	m_pMeetAdapter = new CEslMeetAdapter;
	m_pAnncAdapter = new CEslAnncAdapter;

	m_pStatusAdapter = new CEslStatusAdapter;
	m_pEventAdapter = new CEslEventAdapter;
}

CEslNetControl::~CEslNetControl()
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
	
	if (m_pAnncAdapter)
	{
		delete m_pAnncAdapter;
		m_pAnncAdapter = Q_NULLPTR;
	}

	if (m_pStatusAdapter)
	{
		delete m_pStatusAdapter;
		m_pStatusAdapter = Q_NULLPTR;
	}
	
	if (m_pEventAdapter)
	{
		delete m_pEventAdapter;
		m_pEventAdapter = Q_NULLPTR;
	}
}

//////////////////////////////////////////////////////////////////////////
//是否开启服务
bool CEslNetControl::isEslServer()
{
	ObjectPtr<IRztSettingMgr> settingMgr;
	return settingMgr->toBool(RztSettingKey::SKey_EslOpen);
}

//获取会议包类型
int CEslNetControl::eslGetMeetPkgType(const QJsonObject &json)
{
	int iMeetPkgType = ESL_PKG_TYPE_MEET;
	QJsonObject jsonMsg(json["msg"].toObject());

	if (jsonMsg.contains("type"))
	{
		int type = jsonMsg["type"].toInt();
		if (type == 0 || type == 5 || type == 6)
		{
			iMeetPkgType = ESL_PKG_TYPE_MEET;
		}
		else if (type == 2)
		{
			iMeetPkgType = ESL_PKG_TYPE_ANNC;
		}
	}
	else if (jsonMsg.contains("meetcode"))
	{
		QString strMeetCode = jsonMsg["meetcode"].toString();

		QRegExp rx("(.*)[h|H]$");
		if (strMeetCode.indexOf(rx) == 0)
		{
			iMeetPkgType = ESL_PKG_TYPE_MEET;
		}
		else
		{
			iMeetPkgType = ESL_PKG_TYPE_ANNC;
		}
	}
	else
	{
		if (json["msgType"].toInt() == SCH_P2P_CHANGE_TO_MEETING_REQ)
		{
			iMeetPkgType = ESL_PKG_TYPE_MEET;
		}
	}

	return iMeetPkgType;
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
	QJsonObject jsonValue(json);
	
	switch(static_cast<int>(jsonValue["businessType"].toInt()))
	{
	case PKG_TYPE_BASIC:
	case PKG_TYPE_CONFIG:
		m_pDataAdapter->eslBuildPkg(jsonValue, strJson, iPkgType, iMsgType);
		break;
		
	case PKG_TYPE_SCHEDULE:
		{
			if (eslGetMeetPkgType(jsonValue) == ESL_PKG_TYPE_MEET)
			{
				m_pMeetAdapter->eslBuildPkg(jsonValue, strJson, iPkgType, iMsgType);
			}
			else
			{
				m_pAnncAdapter->eslBuildPkg(jsonValue, strJson, iPkgType, iMsgType);
			}
		}
		break;
		
	default:
		break;
	}
	
	if (strJson != "")
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
	
	bool bRet = false;
	switch (static_cast<int>(pstPkgHeader->cPkgType))
	{
	case ESL_PKG_TYPE_DATA:
		bRet = m_pDataAdapter->eslBuildJson(pstPkgHeader->cMsgType, pstPkgHeader->body, jsonRet);
		break;
		
	case ESL_PKG_TYPE_MEET:
		bRet = m_pMeetAdapter->eslBuildJson(pstPkgHeader->cMsgType, pstPkgHeader->body, jsonRet);
		break;
		
	case ESL_PKG_TYPE_ANNC:
		bRet = m_pAnncAdapter->eslBuildJson(pstPkgHeader->cMsgType, pstPkgHeader->body, jsonRet);
		break;
		
	case ESL_PKG_TYPE_STATUS:
		bRet = m_pStatusAdapter->eslBuildJson(pstPkgHeader->cMsgType, pstPkgHeader->body, jsonRet);
		break;
		
	case ESL_PKG_TYPE_NOTIFY:
		bRet = m_pEventAdapter->eslBuildJson(pstPkgHeader->cMsgType, pstPkgHeader->body, jsonRet);
		break;
		
	default:
		break;
	}
	
	if (bRet)
	{
		std::string strJson = std::string(QJsonDocument(jsonRet).toJson(QJsonDocument::Compact));
		
		ObjectPtr<IRztMessageReceiver> msgReceiver;
		msgReceiver->handleMessage(strJson.c_str(), strUserNum.c_str());
	}
	
	return bRet;
}