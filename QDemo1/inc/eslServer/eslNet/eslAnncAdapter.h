#ifndef ESL_ANNC_ADAPTER_H
#define ESL_ANNC_ADAPTER_H

#include "eslBaseAdapter.h"

class CEslAnncAdapter : public CEslBaseAdapter
{
public:
	CEslAnncAdapter();
	~CEslAnncAdapter();
	
public:
	//Pkg请求包
	void eslBuildPkg(const QJsonObject &json, std::string &strJson, int &iPkgType, int &iMsgType);
	
	//Pkg包转换json
	bool eslBuildJson(int iMsgType, char *pPayload, QJsonObject &jsonRet);

protected:
	//创建通播Req
	void OnReqEslCreateAnnc(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//创建通播Resp
	bool OnRespEslCreateAnnc(const QJsonObject &json, QJsonObject &jsonRet);
	
	//关闭通播Req
	void OnReqEslCloseAnnc(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//关闭通播Resp
	bool OnRespEslCloseAnnc(const QJsonObject &json, QJsonObject &jsonRet);
	
	//增加通播成员Req
	void OnReqEslAddAnncMemb(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//增加通播成员Resp
	bool OnRespEslAddAnncMemb(const QJsonObject &json, QJsonObject &jsonRet);
	
	//删除通播成员Req
	void OnReqEslDelAnncMemb(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//删除通播成员Resp
	bool OnRespEslDelAnncMemb(const QJsonObject &json, QJsonObject &jsonRet);
	
	//开启手咪对讲Req
	void OnReqEslStartSpeak(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//开启手咪对讲Resp
	bool OnRespEslStartSpeak(const QJsonObject &json, QJsonObject &jsonRet);
	
	//关闭手咪对讲Req
	void OnReqEslStopSpeak(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//关闭手咪对讲Resp
	bool OnRespEslStopSpeak(const QJsonObject &json, QJsonObject &jsonRet);
	
	//开启视频查看Req
	void OnReqEslStartVideo(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//开启视频查看Resp
	bool OnRespEslStartVideo(const QJsonObject &json, QJsonObject &jsonRet);
	
	//关闭视频查看Req
	void OnReqEslStopVideo(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//关闭视频查看Resp
	bool OnRespEslStopVideo(const QJsonObject &json, QJsonObject &jsonRet);
};

#endif