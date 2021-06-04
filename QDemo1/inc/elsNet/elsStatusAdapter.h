#ifndef ELS_STATUS_ADAPTER_H
#define ELS_STATUS_ADAPTER_H

class CElsStatusAdapter
{
public:
	CElsStatusAdapter();
	~CElsStatusAdapter();

public:
	bool elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson);
	
protected:
	bool buildPkg(void *pstPkg, std::string &strJson);

protected:	
};

#endif