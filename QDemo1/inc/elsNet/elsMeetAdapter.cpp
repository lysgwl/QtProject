#include "elsMeetAdapter.h"

CElsMeetAdapter::CElsMeetAdapter()
{
}

CElsMeetAdapter::~CElsMeetAdapter()
{
}

//pkg�������
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

//pkg������
bool CElsMeetAdapter::elsParsePkg(int iMsgType, char *pPayload, void* pstEvent)
{
	stSchPkgFormat jstSchPkgFmt = {0};
	return true;
}

//pkg��ת��json
bool CElsMeetAdapter::elsBuildJson(void* pstEvent, std::string &strJson)
{
	return true;
}

//stSchPkgFormat��
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

//req::createMeet��������
void CElsMeetAdapter::OnReqElsCreateMeet(const stSchPkgFormat *pstPkg, std::string &strJson, int &iMsgType)
{
	if (pstPkg == Q_NULLPTR)
	{
		return;
	}
}