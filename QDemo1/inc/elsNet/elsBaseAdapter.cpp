#include "elsBaseAdapter.h"

CElsBaseAdapter::CElsBaseAdapter()
{
}

CElsBaseAdapter::~CElsBaseAdapter()
{
}

bool CElsBaseAdapter::elsParseSegment(const QJsonObject &json, int iPkgType, void *pstPkgEvent)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	std::vector<std::tuple<std::string, std::string>> vecstr;
	
	int iSize = json.size();
	for (int iIndex=0; iIndex<iSize; iIndex++)
	{
		if (json.contains("seq"))
		{
			std::string seq = std::to_string(json.value("seq").toInt());
			vecstr.push_back(std::make_tuple("seq", seq));
		}
		else if (json.contains("result"))
		{
			std::string result = json.value("result").toString().toStdString();
			vecstr.push_back(std::make_tuple("result", result));
		}
		else if (json.contains("lgtype"))
		{
			std::string lgtype = json.value("lgtype").toString().toStdString();
			vecstr.push_back(std::make_tuple("lgtype", lgtype));
		}
		else if (json.contains("lgnum"))
		{
			std::string lgnum = json.value("lgnum").toString().toStdString();
			vecstr.push_back(std::make_tuple("lgnum", lgnum));
		}
		else if (json.contains("lgpwd"))
		{
			std::string lgpwd = json.value("lgpwd").toString().toStdString();
			vecstr.push_back(std::make_tuple("lgpwd", lgpwd));
		}
		else if (json.contains("token"))
		{
			std::string token = json.value("token").toString().toStdString();
			vecstr.push_back(std::make_tuple("token", token));
		}
		else if (json.contains("meetid"))
		{
			std::string meetid = json.value("meetid").toString().toStdString();
			vecstr.push_back(std::make_tuple("meetid", token));
		}
	}
	
	if (parseSegment(iPkgType, pstPkgEvent, vecstr) == false)
	{
		return false;
	}
	
	return true;
}

bool CElsBaseAdapter::parseSegment(int iPkgType, void *pstPkgEvent, std::vector<std::tuple<std::string, std::string>> &vecTuple)
{
	if (pstPkgEvent == NULL)
	{
		return false;
	}
	
	stCfgPkgFormat *pstCfgPkgFmt = Q_NULLPTR;
	stBasicPkgFormat *pstBasePkgFmt = Q_NULLPTR;
	
	stSchPkgFormat *pstSchPkgFmt = Q_NULLPTR;
	stEventPkgFormat *pstEventPkgFmt = Q_NULLPTR;
	
	for (auto iter=vecTuple.cbegin(); iter != vecTuple.cend(); iter++)
	{
		std::string strKey = std::get<0>(*iter);
		std::string strValue = std::get<1>(*iter);
		
		if (iPkgType == PKG_TYPE_BASIC)
		{
			pstCfgPkgFmt = static_cast<stCfgPkgFormat*>(pstPkgEvent);
			
			if (strKey == "seq")
			{
				pstCfgPkgFmt->iReqId = std::stoi(strValue);
			}
			else if (strKey == "result")
			{
				pstCfgPkgFmt->iResult = std::stoi(strValue);
			}
			else if (strKey == "usrnum")
			{
			}
		}
		else if (iPkgType == PKG_TYPE_CONFIG)
		{
			pstBasePkgFmt = static_cast<stBasicPkgFormat*>(pstPkgEvent);
			if (strKey == "seq")
			{
				pstBasePkgFmt->iReqId = std::stoi(strValue);
			}
			else if (strKey == "result")
			{
				pstBasePkgFmt->iResult = std::stoi(strValue);
			}
			else if (strKey == "usrnum")
			{
			}
		}
		else if (iPkgType == PKG_TYPE_SCHEDULE)
		{
			pstSchPkgFmt = static_cast<stSchPkgFormat*>(pstPkgEvent);
			if (strKey == "seq")
			{
				pstSchPkgFmt->iReqId = std::stoi(strValue);
			}
			else if (strKey == "result")
			{
				pstSchPkgFmt->iResult = std::stoi(strValue);
			}
			else if (strKey == "usrnum")
			{
			}
		}
		else if (iPkgType == PKG_TYPE_EVENT)
		{
			pstEventPkgFmt = static_cast<stEventPkgFormat*>(pstPkgEvent);
			if (strKey == "seq")
			{
				pstEventPkgFmt->iReqId = std::stoi(strValue);
			}
			else if (strKey == "result")
			{
				pstEventPkgFmt->iResult = std::stoi(strValue);
			}
			else if (strKey == "usrnum")
			{
			}
		}
	}
	
	return true;
}