#include "eslBaseAdapter.h"

CEslBaseAdapter::CEslBaseAdapter()
{
}

CEslBaseAdapter::~CEslBaseAdapter()
{
}

//解析json数据段
bool CEslBaseAdapter::eslParseSegment(const QJsonObject &json, int iPkgType, void *pstPkgEvent)
{
	if (json.isEmpty())
	{
		return false;
	}
	
	std::vector<std::tuple<std::string, std::string>> vecstr;

    //seq
    if (json.contains("seq"))
    {
        std::string seq = std::to_string(json.value("seq").toInt());
        vecstr.push_back(std::make_tuple("seq", seq));
    }

    //result
    if (json.contains("result"))
    {
        std::string result = std::to_string(json.value("result").toInt());
        vecstr.push_back(std::make_tuple("result", result));
    }

    //lgtype
    if (json.contains("lgtype"))
    {
        std::string lgtype = json.value("lgtype").toString().toStdString();
        vecstr.push_back(std::make_tuple("lgtype", lgtype));
    }

    //lgnum
    if (json.contains("lgnum"))
    {
        std::string lgnum = json.value("lgnum").toString().toStdString();
        vecstr.push_back(std::make_tuple("lgnum", lgnum));
    }

    //lgpwd
    if (json.contains("lgpwd"))
    {
        std::string lgpwd = json.value("lgpwd").toString().toStdString();
        vecstr.push_back(std::make_tuple("lgpwd", lgpwd));
    }

    //token
    if (json.contains("token"))
    {
        std::string token = json.value("token").toString().toStdString();
        vecstr.push_back(std::make_tuple("token", token));
    }

    //meetid
    if (json.contains("meetid"))
    {
        std::string meetid = json.value("meetid").toString().toStdString();
        vecstr.push_back(std::make_tuple("meetid", meetid));
    }
	
	if (parseSegment(iPkgType, pstPkgEvent, vecstr) == false)
	{
		return false;
	}
	
	return true;
}

//解析消息数据
bool CEslBaseAdapter::parseSegment(int iPkgType, void *pstPkgEvent, std::vector<std::tuple<std::string, std::string>> &vecTuple)
{
    if (pstPkgEvent == Q_NULLPTR)
	{
		return false;
	}
	
    for (auto iter=vecTuple.cbegin(); iter != vecTuple.cend(); ++iter)
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
void CEslBaseAdapter::setBasicPkgData(std::string &strKey, std::string &strValue, void *pstPkg)
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
    else if (strKey == "lgnum")
    {
        snprintf(pstBasePkgFmt->acUsrName, STR_LEN_32, "%s", strValue.c_str());
    }
    else if (strKey == "token")
    {
        pstBasePkgFmt->iTerminalId = std::stoi(strValue);
    }
}

//设置Config数据
void CEslBaseAdapter::setConfigPkgData(std::string &strKey, std::string &strValue, void *pstPkg)
{
    stCfgPkgFormat *pstCfgPkgFmt = static_cast<stCfgPkgFormat*>(pstPkg);
    if (pstCfgPkgFmt == Q_NULLPTR)
    {
        return;
    }

    if (strKey == "seq")
    {
        pstCfgPkgFmt->uiRequestID = std::stoul(strValue);
    }
    else if (strKey == "result")
    {
        pstCfgPkgFmt->uiResult = std::stoul(strValue);
    }
    else if (strKey == "lgnum")
    {
        snprintf(pstCfgPkgFmt->acNumber, STR_LEN_64, "%s", strValue.c_str());
    }
}

//设置Schedule数据
void CEslBaseAdapter::setSchPkgData(std::string &strKey, std::string &strValue, void *pstPkg)
{
    stSchPkgFormat *pstSchPkgFmt = static_cast<stSchPkgFormat*>(pstPkg);
    if (pstSchPkgFmt == Q_NULLPTR)
    {
        return;
    }

    if (strKey == "seq")
    {
        pstSchPkgFmt->iReqId = std::stoul(strValue);
    }
    else if (strKey == "result")
    {
        pstSchPkgFmt->iResult = std::stoul(strValue);
    }
    else if (strKey == "lgnum")
    {
        snprintf(pstSchPkgFmt->acNumber, STR_LEN_64, "%s", strValue.c_str());
    }
}

//设置Event数据
void CEslBaseAdapter::setEventPkgData(std::string &strKey, std::string &strValue, void *pstPkg)
{
    stEventPkgFormat *pstEventPkgFmt = static_cast<stEventPkgFormat*>(pstPkg);
    if (pstEventPkgFmt == Q_NULLPTR)
    {
        return;
    }

    if (strKey == "seq")
    {
        std::cout << strValue << std::endl;
    }
    else if (strKey == "result")
    {
        std::cout << strValue << std::endl;
    }
    else if (strKey == "lgnum")
    {
        std::cout << strValue << std::endl;
    }
}
