#ifndef ELS_MEET_ADAPTER_H
#define ELS_MEET_ADAPTER_H

class CElsMeetAdapter : CElsBaseAdapter
{
public:
	CElsMeetAdapter();
	~CElsMeetAdapter();

public:
	//pkg请求组包
	bool elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType);
	
	//pkg包解析
	bool elsParsePkg(int iMsgType, char *pPayload, void* pstEvent);
	
	//pkg包转换json
	bool elsBuildJson(void* pstEvent, std::string &strJson);

protected:
	//stSchPkgFormat包
	bool buildPkg(void *pstPkg, std::string &strJson, int &iMsgType);

protected:
	//req::createMeet创建会议
	void OnReqElsCreateMeet(const stSchPkgFormat *pstPkg, std::string &strJson, int &iMsgType);	
};

#endif