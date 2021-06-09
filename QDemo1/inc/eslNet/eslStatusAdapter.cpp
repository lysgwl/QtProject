#include "elsStatusAdapter.h"

CEslStatusAdapter::CEslStatusAdapter()
{
}

CEslStatusAdapter::~CEslStatusAdapter()
{
}

//pkg请求组包
bool CEslStatusAdapter::eslBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType)
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
bool CEslStatusAdapter::eslParsePkg(int iMsgType, char *pPayload, void* pstEvent)
{
	stEventPkgFormat jstEventPkgFmt = {0};
	return true;
}

//pkg包转换json
bool CEslStatusAdapter::eslBuildJson(void* pstEvent, std::string &strJson)
{
	return true;
}

//stEventPkgFormat包
bool CEslStatusAdapter::buildPkg(void *pstPkg, std::string &strJson, int &iMsgType)
{
	return true;
}