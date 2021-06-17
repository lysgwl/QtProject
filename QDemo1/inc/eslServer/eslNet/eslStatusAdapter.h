#ifndef ESL_STATUS_ADAPTER_H
#define ESL_STATUS_ADAPTER_H

#include "eslBaseAdapter.h"

class CEslStatusAdapter : public CEslBaseAdapter
{
public:
	CEslStatusAdapter();
	~CEslStatusAdapter();

public:
	//pkg请求组包
	bool eslBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType);
	
	//pkg包解析
	bool eslParsePkg(int iMsgType, char *pPayload, void* pstEvent);
	
	//pkg包转换json
	bool eslBuildJson(void* pstEvent, std::string &strJson);
	
protected:
	//stEventPkgFormat包
	bool buildEventPkg(void *pstPkg, std::string &strJson, int &iMsgType);

protected:
};

#endif