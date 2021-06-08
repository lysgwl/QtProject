#ifndef ELS_MEET_ADAPTER_H
#define ELS_MEET_ADAPTER_H

class CElsMeetAdapter : CElsBaseAdapter
{
public:
	CElsMeetAdapter();
	~CElsMeetAdapter();

public:
	//pkg�������
	bool elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType);
	
	//pkg������
	bool elsParsePkg(int iMsgType, char *pPayload, void* pstEvent);
	
	//pkg��ת��json
	bool elsBuildJson(void* pstEvent, std::string &strJson);

protected:
	//stSchPkgFormat��
	bool buildPkg(void *pstPkg, std::string &strJson, int &iMsgType);

protected:
	//req::createMeet��������
	void OnReqElsCreateMeet(const stSchPkgFormat *pstPkg, std::string &strJson, int &iMsgType);	
};

#endif