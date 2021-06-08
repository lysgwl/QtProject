#ifndef ELS_DATA_ADAPTER_H
#define ELS_DATA_ADAPTER_H

#include "elsBaseAdapter.h"

class CElsDataAdapter : public CElsBaseAdapter
{
public:
	CElsDataAdapter();
	~CElsDataAdapter();
	
public:	
	//Pkg组包请求
	bool elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType);	
	
	//Pkg包解析
	bool elsParsePkg(int iMsgType, char *pPayload, void* pstEvent);
	
	//Pkg包转换json
	bool elsBuildJson(int iPkgType, void* pstEvent, QJsonObject &json);
	
protected:
	//stBasicPkgFormat请求
	bool buildBaseReqPkg(void *pstPkg, std::string &strJson, int &iMsgType);
	
	//stCfgPkgFormat请求
	bool buildConfigReqPkg(void *pstPkg, std::string &strJson, int &iMsgType);
	
	//stBasicPkgFormat回复
	bool buildBaseRespPkg(bool bFlag, int iMsgType, void* pstEvent, QJsonObject &json);
	
	//stCfgPkgFormat回复
	bool buildConfigRespPkg(bool bFlag, int iMsgType, void* pstEvent, QJsonObject &json);
	
protected:
	//登录Req
	void OnReqElsLogin(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType);
	
	//注销Req
	void OnReqElsLoginOut(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType);
	
	//心跳Req
	void OnReqElsHeartBeat(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType);
	
	//登录Resp
	void OnRespElsLogin(bool bFlag, stBasicPkgFormat *pstPkg, QJsonObject &json);
	
	//心跳Resp
	void OnRespElsHeartBeat(bool bFlag, stBasicPkgFormat *pstPkg, QJsonObject &json);
};

#endif