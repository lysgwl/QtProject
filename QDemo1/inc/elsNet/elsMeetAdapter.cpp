#include "elsMeetAdapter.h"

CElsMeetAdapter::CElsMeetAdapter()
{
}

CElsMeetAdapter::~CElsMeetAdapter()
{
}

bool CElsMeetAdapter::elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson)
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

bool CElsMeetAdapter::buildPkg(void *pstPkg, std::string &strJson)
{
	stSchPkgFormat *pstSchPkgMsg = static_cast<stSchPkgFormat*>(pstPkg);
	if (pstSchPkgMsg == Q_NULLPTR)
	{
		return false;
	}
	
	switch (pstSchPkgMsg->iMsgType)
	{
	case SCH_MEETING_CREATE_REQ:
		OnReqElsCreateMeet(pstSchPkgMsg, strJson);
		break;
		
	default:
		break;
	}
	
	return true;
}

void CElsMeetAdapter::OnReqElsCreateMeet(const stSchPkgFormat *pstPkg, std::string &strJson)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
}