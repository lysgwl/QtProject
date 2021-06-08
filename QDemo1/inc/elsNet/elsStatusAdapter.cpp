#include "elsStatusAdapter.h"

CElsStatusAdapter::CElsStatusAdapter()
{
}

CElsStatusAdapter::~CElsStatusAdapter()
{
}

//pkg请求组包
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

//pkg包解析
bool CElsStatusAdapter::elsParsePkg(int iMsgType, char *pPayload, void* pstEvent)
{
	stEventPkgFormat jstEventPkgFmt = {0};
	return true;
}

//pkg包转换json
bool CElsStatusAdapter::elsBuildJson(void* pstEvent, std::string &strJson)
{
	return true;
}

//stEventPkgFormat包
bool CElsStatusAdapter::buildPkg(void *pstPkg, std::string &strJson, int &iMsgType)
{
	return true;
}