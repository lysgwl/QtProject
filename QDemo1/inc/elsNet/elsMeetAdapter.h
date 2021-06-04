#ifndef ELS_MEET_ADAPTER_H
#define ELS_MEET_ADAPTER_H

class CElsMeetAdapter
{
public:
	CElsMeetAdapter();
	~CElsMeetAdapter();

public:
	bool elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson);

protected:
	bool buildPkg(void *pstPkg, std::string &strJson);

protected:
	void OnReqElsCreateMeet(const stSchPkgFormat *pstPkg, std::string &strJson);	
};

#endif