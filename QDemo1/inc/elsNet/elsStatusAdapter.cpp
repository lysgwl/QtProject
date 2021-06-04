#include "elsStatusAdapter.h"

CElsStatusAdapter::CElsStatusAdapter()
{
}

CElsStatusAdapter::~CElsStatusAdapter()
{
}

bool CElsStatusAdapter::elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson)
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

bool CElsStatusAdapter::buildPkg(void *pstPkg, std::string &strJson)
{
	return true;
}