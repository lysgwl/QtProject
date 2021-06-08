#ifndef ELS_STATUS_ADAPTER_H
#define ELS_STATUS_ADAPTER_H

class CElsStatusAdapter : public CElsBaseAdapter
{
public:
	CElsStatusAdapter();
	~CElsStatusAdapter();

public:
	//pkg请求组包
	bool elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType);
	
	//pkg包解析
	bool elsParsePkg(int iMsgType, char *pPayload, void* pstEvent);
	
	//pkg包转换json
	bool elsBuildJson(void* pstEvent, std::string &strJson);
	
protected:
	//stEventPkgFormat包
	bool buildEventPkg(void *pstPkg, std::string &strJson, int &iMsgType);

protected:
};

#endif