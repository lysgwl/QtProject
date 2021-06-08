#include "elsMeetAdapter.h"

CElsMeetAdapter::CElsMeetAdapter()
{
}

CElsMeetAdapter::~CElsMeetAdapter()
{
}

//pkg请求组包
bool CElsMeetAdapter::elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType)
{
	bool bResult = false;
	
	switch (iPkgType)
	{
	case PKG_TYPE_SCHEDULE:
		bResult = buildPkg(pstPkg, strJson);
		break;
		
	default:
		break;
	}
	
	return bResult;
}

//pkg包解析
bool CElsMeetAdapter::elsParsePkg(int iMsgType, char *pPayload, void* pstEvent)
{
	stSchPkgFormat jstSchPkgFmt = {0};
	return true;
}

//pkg包转换json
bool CElsMeetAdapter::elsBuildJson(void* pstEvent, std::string &strJson)
{
	return true;
}

//stSchPkgFormat包
bool CElsMeetAdapter::buildPkg(void *pstPkg, std::string &strJson, int &iMsgType)
{
	stSchPkgFormat *pstSchPkgMsg = static_cast<stSchPkgFormat*>(pstPkg);
	if (pstSchPkgMsg == Q_NULLPTR)
	{
		return false;
	}
	
	switch (pstSchPkgMsg->iMsgType)
	{
	case SCH_MEETING_CREATE_REQ:
		OnReqElsCreateMeet(pstSchPkgMsg, strJson, iMsgType);
		break;
		
	default:
		break;
	}
	
	return true;
}

//req::createMeet创建会议
void CElsMeetAdapter::OnReqElsCreateMeet(const stSchPkgFormat *pstPkg, std::string &strJson, int &iMsgType)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
}