#include "elsBaseAdapter.h"

CElsBaseAdapter::CElsBaseAdapter()
{
}

CElsBaseAdapter::~CElsBaseAdapter()
{
}

//解析json数据段
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
            //vecstr.push_back(std::make_tuple("meetid", token));
		}
	}
	
	if (parseSegment(iPkgType, pstPkgEvent, vecstr) == false)
	{
		return false;
	}
	
	return true;
}

//解析消息数据
bool CElsBaseAdapter::parseSegment(int iPkgType, void *pstPkgEvent, std::vector<std::tuple<std::string, std::string>> &vecTuple)
{
    if (pstPkgEvent == Q_NULLPTR)
	{
		return false;
	}
	
	for (auto iter=vecTuple.cbegin(); iter != vecTuple.cend(); iter++)
	{
		std::string strKey = std::get<0>(*iter);
		std::string strValue = std::get<1>(*iter);
		
		if (iPkgType == PKG_TYPE_BASIC)
		{
            setBasicPkgData(strKey, strValue, pstPkgEvent);
		}
		else if (iPkgType == PKG_TYPE_CONFIG)
		{
            setConfigPkgData(strKey, strValue, pstPkgEvent);
		}
		else if (iPkgType == PKG_TYPE_SCHEDULE)
		{
            setSchPkgData(strKey, strValue, pstPkgEvent);
		}
		else if (iPkgType == PKG_TYPE_EVENT)
		{
            setEventPkgData(strKey, strValue, pstPkgEvent);
		}
	}
	
	return true;
}

//设置Basic数据
void CElsBaseAdapter::setBasicPkgData(std::string &strKey, std::string &strValue, void *pstPkg)
{
    stBasicPkgFormat *pstBasePkgFmt = static_cast<stBasicPkgFormat*>(pstPkg);
    if (pstBasePkgFmt == Q_NULLPTR)
    {
        return;
    }

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
        pstBasePkgFmt->
    }
}

//设置Config数据
void CElsBaseAdapter::setConfigPkgData(std::string &strKey, std::string &strValue, void *pstPkg)
{

}

//设置Schedule数据
void CElsBaseAdapter::setSchPkgData(std::string &strKey, std::string &strValue, void *pstPkg)
{

}

//设置Event数据
void CElsBaseAdapter::setEventPkgData(std::string &strKey, std::string &strValue, void *pstPkg)
{

}
