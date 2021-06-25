#ifndef ESL_DATA_ADAPTER_H
#define ESL_DATA_ADAPTER_H

#include "eslBaseAdapter.h"

class CEslDataAdapter : public CEslBaseAdapter
{
public:
	CEslDataAdapter();
	~CEslDataAdapter();
	
public:	
	//Pkg请求包
	void eslBuildPkg(QJsonObject &json, std::string &strJson, int &iPkgType, int &iMsgType);	
	
	//Pkg包转换json
	bool eslBuildJson(int iMsgType, char *pPayload, QJsonObject &jsonRet);
	
protected:
	//登录Req
	void OnReqEslLogin(QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//登录Resp
	bool OnRespEslLogin(const QJsonObject &json, QJsonObject &jsonRet);
	
	//注销Req
	void OnReqEslLoginOut(QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//心跳Req
	void OnReqEslHeartBeat(QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//心跳Resp
	bool OnRespEslHeartBeat(const QJsonObject &json, QJsonObject &jsonRet);
};

#endif