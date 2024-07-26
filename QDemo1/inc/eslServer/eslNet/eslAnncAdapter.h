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
	
	//手咪对讲Req
	void OnReqEslSpeakDetect(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//手咪对讲Resp
	bool OnRespEslSpeakDetect(int iMsgType, const QJsonObject &json, QJsonObject &jsonRet);
	
	//请求视频查看Req
	void OnReqEslRequestVideo(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//请求视频查看Resp
	bool OnRespEslRequestVideo(int iMsgType, const QJsonObject &json, QJsonObject &jsonRet);

	//请求视频通知
	bool OnNotifyRequestVideo(int iMsgType, const QJsonObject &json, QJsonObject &jsonRet);

	//回复视频确认消息
	void OnReqEslConfirmVideo(const QJsonObject &json, std::string &strJson, int &iMsgType);
};

#endif