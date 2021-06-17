#ifndef ESL_MEET_ADAPTER_H
#define ESL_MEET_ADAPTER_H

#include "eslBaseAdapter.h"

class CEslMeetAdapter : public CEslBaseAdapter
{
public:
	CEslMeetAdapter();
	~CEslMeetAdapter();

public:
	//pkg请求组包
	bool eslBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType);
	
	//pkg包解析
	bool eslParsePkg(int iMsgType, char *pPayload, void* pstEvent);
	
	//pkg包转换json
	bool eslBuildJson(void* pstEvent, std::string &strJson);

protected:
	//stSchPkgFormat包
	bool buildPkg(void *pstPkg, std::string &strJson, int &iMsgType);

protected:
	//req::createMeet创建会议
	void OnReqEslCreateMeet(const stSchPkgFormat *pstPkg, std::string &strJson, int &iMsgType);	
};

#endif