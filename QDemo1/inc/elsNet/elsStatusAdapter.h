#ifndef ELS_STATUS_ADAPTER_H
#define ELS_STATUS_ADAPTER_H

class CElsStatusAdapter : public CElsBaseAdapter
{
public:
	CElsStatusAdapter();
	~CElsStatusAdapter();

public:
	//pkg�������
	bool elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType);
	
	//pkg������
	bool elsParsePkg(int iMsgType, char *pPayload, void* pstEvent);
	
	//pkg��ת��json
	bool elsBuildJson(void* pstEvent, std::string &strJson);
	
protected:
	//stEventPkgFormat��
	bool buildEventPkg(void *pstPkg, std::string &strJson, int &iMsgType);

protected:
};

#endif