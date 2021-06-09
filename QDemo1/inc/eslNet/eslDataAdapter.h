#ifndef ESL_DATA_ADAPTER_H
#define ESL_DATA_ADAPTER_H

#include "eslBaseAdapter.h"

class CEslDataAdapter : public CEslBaseAdapter
{
public:
	CEslDataAdapter();
	~CEslDataAdapter();
	
public:	
	//Pkg组包请求
	bool eslBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType);	
	
	//Pkg包解析
	bool eslParsePkg(int iMsgType, char *pPayload, void* pstEvent);
	
	//Pkg包转换json
	bool eslBuildJson(int iPkgType, void* pstEvent, QJsonObject &json);
	
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
	void OnReqEslLogin(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType);
	
	//注销Req
	void OnReqEslLoginOut(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType);
	
	//心跳Req
	void OnReqEslHeartBeat(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType);
	
	//登录Resp
	void OnRespEslLogin(bool bFlag, stBasicPkgFormat *pstPkg, QJsonObject &json);
	
	//心跳Resp
	void OnRespEslHeartBeat(bool bFlag, stBasicPkgFormat *pstPkg, QJsonObject &json);
};

#endif