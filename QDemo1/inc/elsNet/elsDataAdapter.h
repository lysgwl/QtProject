#ifndef ELS_DATA_ADAPTER_H
#define ELS_DATA_ADAPTER_H

class CElsDataAdapter
{
public:
	CElsDataAdapter();
	~CElsDataAdapter();
	
public:	
	bool elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson);	
	
protected:
	bool buildBasePkg(void *pstPkg, std::string &strJson);
	bool buildConfigPkg(void *pstPkg, std::string &strJson);
	
protected:
	void OnReqElsLogin(const stBasicPkgFormat *pstPkg, std::string &strJson);
	void OnReqElsLoginOut(const stBasicPkgFormat *pstPkg, std::string &strJson);
	void OnReqElsHeartBeat(const stBasicPkgFormat *pstPkg, std::string &strJson);
};

#endif