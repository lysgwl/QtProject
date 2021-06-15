#include "eslHttpControl.h"

CEslHttpControl::CEslHttpControl()
{
	//data对象指针
	m_pEslHttpData = new CEslHttpData;
	
	//call对象指针
	m_pEslHttpCall = new CEslHttpCall;
}

CEslHttpControl::~CEslHttpControl()
{
	if (m_pEslHttpData)
	{
		delete m_pEslHttpData;
		m_pEslHttpData = Q_NULLPTR;
	}
	
	if (m_pEslHttpCall)
	{
		delete m_pEslHttpCall;
		m_pEslHttpCall = Q_NULLPTR;
	}
}

//esl获取数据
void CEslHttpControl::eslGetDataFromSrv(std::string &strCallNum, std::string &strToken)
{
	if (strCallNum == "" || strToken == "")
	{
		return;
	}
	
	QJsonObject json;
	json.insert("user", strCallNum);
	json.insert("token", strToken);
	
	//获取系统配置
	m_pEslHttpData->eslGetSysConfig(json);
	
	//获取设备配置
	m_pEslHttpData->eslSetDevConfig(false, json);
	
	//获取用户配置
	m_pEslHttpData->eslSetUserConfig(false, json);
	
	//获取快捷通讯录
	m_pEslHttpData->eslSetPageData(FileHandle_Get, json);
	
	//获取公共通讯录
	m_pEslHttpData->eslSetPublicContact(json);
	
	//获取席位通讯录
	m_pEslHttpData->eslSetSeatContact(json);
	
	//获取通话记录
	m_pEslHttpCall->eslSetCallLog(false, json);
	
	//获取电台列表
	m_pEslHttpCall->eslSetRadioList(json);
}

//esl设置数据
void CEslHttpControl::eslSetSrvData(bool bIsSeat, std::string &strCallNum, std::string &strToken)
{
	if (strCallNum == "" || strToken == "")
	{
		return;
	}
	
	QJsonObject json;
	json.insert("user", strCallNum);
	json.insert("token", strToken);
	json.insert("seat", bIsSeat);
	
	//设置设备配置
	m_pEslHttpData->eslSetDevConfig(true, json);
	
	//设置用户配置
	m_pEslHttpData->eslSetUserConfig(true, json);
}

//esl设置事件
void CEslHttpControl::eslSetUserEvent()
{
	ObjectPtr<IRztServerInfoMgr> severInfo;
	STSvrInfo svrInfo = severInfo->getCurSvrInfo();
	
	//ntp 对时
	RztCommonUtils::ntpToServer(svrInfo.strIP);
}

//获取data对象指针
CEslHttpData* CEslHttpControl::eslGetDataPtr() const
{
	return m_pEslHttpData;
}

//获取call对象指针
CEslHttpCall* CEslHttpControl::eslGetCallPtr() const
{
	return m_pEslHttpCall;
}