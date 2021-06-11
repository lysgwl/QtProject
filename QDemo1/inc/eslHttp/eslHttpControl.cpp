#include "eslHttpControl.h"

CEslHttpControl::CEslHttpControl()
{
	m_pEslHttpData = new CEslHttpData;
}

CEslHttpControl::~CEslHttpControl()
{
	if (m_pEslHttpData)
	{
		delete m_pEslHttpData;
		m_pEslHttpData = Q_NULLPTR;
	}
}

//esl获取数据
void CEslHttpControl::eslGetDataFromSrv()
{
	//获取快捷通讯录
	eslSetPageData(0);
	
	//获取通话记录
	eslSetCallLog();
	
	//获取电台列表
	eslSetRadioList();
	
	//获取用户配置
	eslSetUserConfig();
	
	//获取席位设备列表
	eslSetSeatDevList();
	
	//获取公共通讯录
	eslSetPublicContact();
	
	//获取席位通讯录
	eslSetSeatContact();
	
	//获取模块配置
	eslSetModuleConfig();
}

//esl设置数据
void CEslHttpControl::eslGetSrvData(bool bIsSeat, std::string &strCallNum, std::string &strToken)
{
	if (strCallNum == "" || strToken == "")
	{
		return;
	}
	
	//设备数据
	{
		QJsonObject jsonData;
		jsonData.insert("devuuid", );
		jsonData.insert("seatid", );
		
		jsonData.insert("seatnum", );
		jsonData.insert("terminalip", );
		jsonData.insert("devmac", );
		jsonData.insert("devtype", 1);
		jsonData.insert("version", "");
		jsonData.insert("versionstate", 0);
		
		QJsonObject jsonDev;
		jsonDev.insert("user", strCallNum);
		jsonDev.insert("token", strToken);
		jsonDev.insert("data", jsonData);
		
		m_pEslHttpData->eslSetDevConfig(jsonDev);
	}
	
	//用户数据
	{
		QJsonObject jsonData;
		jsonData.insert("name", );
		jsonData.insert("password", );
		jsonData.insert("transfernumber", );
		jsonData.insert("extend", );
		
		QJsonObject jsonUser;
		jsonUser.insert("user", strCallNum);
		jsonUser.insert("token", strToken);
		
		m_pEslHttpData->eslSetUserConfig(jsonUser);
	}
}

//esl设置快捷通讯录
void CEslHttpControl::eslSetPageData(int iPageType, std::string &strCallNum, std::string &strToken)
{
	if (iPageType == FileHandle_Get)
	{
		eslGetPageData(strCallNum, strToken);
	}
}

//esl设置通话记录
void CEslHttpControl::eslSetCallLog()
{
}

//esl设置系统配置
void CEslHttpControl::eslGetSysConfig(std::string &strCallNum, std::string &strToken)
{
	QJsonObject json;
	json.insert("user", strCallNum);
	json.insert("token", strToken);
	
	QJsonObject jsonRet;
	if (!m_pEslHttpData->eslGetSysConfig(json, jsonRet))
	{
		return;
	}
	
	std::string strRecordIp = jsonRet.value("recordServerIp").toString().toStdString();
	int iRecordPort = jsonRet.value("recordServerPort").toInt();
	
	std::stringstream stream;
	stream << strRecordIp << ":" << iRecordPort;
	std::string strRecordUrl = stream.str();
}

//esl设置设备配置
void CEslHttpControl::eslGetDevConfig(std::string &strCallNum, std::string &strToken)
{
	QJsonObject json;
	json.insert("user", strCallNum);
	json.insert("token", strToken);
	
	QJsonObject jsonRet;
	if (!m_pEslHttpData->eslGetDevConfig(json, jsonRet))
	{
		return;
	}
}

//esl设置用户配置
void CEslHttpControl::eslGetUserConfig(std::string &strCallNum, std::string &strToken)
{
	QJsonObject json;
	json.insert("user", strCallNum);
	json.insert("token", strToken);
	
	QJsonObject jsonRet;
	if (!m_pEslHttpData->eslGetUserConfig(json, jsonRet))
	{
		return;
	}
	
	QJsonObject jsonData = jsonRet["data"].toObject();
	if (jsonData.contains("transfernumber"))
	{//呼叫转移
		std::string strUserNum = jsonData["transfernumber"].toString().toStdString();
		if (jsonData["transferswitch"].toInt() == 0)
		{
			strUserNum = "";
		}

		ObjectPtr<IRztSettingMgr> settingMgr;
		settingMgr->setValue(RztSettingKey::SKey_CallDivert, strUserNum.c_str());
	}
}

//esl设置电台列表
void CEslHttpControl::eslGetRadioList()
{
}

//esl设置席位设备列表
void CEslHttpControl::eslGetSeatDevList()
{
}

//esl设置公共通讯录
void CEslHttpControl::eslGetPublicContact()
{
}

//esl设置席位通讯录
void CEslHttpControl::eslGetSeatContact()
{
}

//esl设置模块配置
void CEslHttpControl::eslGetModuleConfig()
{
}

//获取data对象指针
CEslHttpData* CEslHttpControl::eslGetDataPtr() const
{
	return m_pEslHttpData;
}

void CEslHttpControl::eslGetPageData(std::string &strCallNum, std::string &strToken)
{
	QJsonObject json;
	json.insert("user", strCallNum);
	json.insert("token", strToken);
	json.insert("folder", "0");
	
	QJsonObject jsonRet;
	if (!m_pEslHttpData->eslGetPageData(json, jsonRet))
	{
		return;
	}
	
	std::stringstream stream;
	stream << RztFramework::getGlobalVariantInfo()->strDataPath.toStdString() << "/excel/short.xlsx";
	std::string strDescPath = stream.str();
	
	QJsonObject obj = jsonRet["data"].toObject();
	std::string strUrl = obj["fileUrl"].toString().toStdString();
	
	RztDownLoadFile downFile;
	if (downFile.downLoad(strUrl.c_str(), strDescPath.c_str()))
	{
		return;
	}
	
	ObjectPtr<IRztBasePageMgr> basepageMgr;
    basepageMgr->parseExcel();
}