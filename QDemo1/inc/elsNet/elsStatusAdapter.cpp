#include "elsStatusAdapter.h"

CElsStatusAdapter::CElsStatusAdapter()
{
}

CElsStatusAdapter::~CElsStatusAdapter()
{
}

//pkg�������
bool CElsStatusAdapter::elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType)
{
	bool bResult = false;
	
	switch (iPkgType)
	{
	case PKG_TYPE_EVENT:
		break;
		
	default:
		break;
	}
	
	return bResult;
}

//pkg������
bool CElsStatusAdapter::elsParsePkg(int iMsgType, char *pPayload, void* pstEvent)
{
	stEventPkgFormat jstEventPkgFmt = {0};
	return true;
}

//pkg��ת��json
bool CElsStatusAdapter::elsBuildJson(void* pstEvent, std::string &strJson)
{
	return true;
}

//stEventPkgFormat��
bool CElsStatusAdapter::buildPkg(void *pstPkg, std::string &strJson, int &iMsgType)
{
	return true;
}