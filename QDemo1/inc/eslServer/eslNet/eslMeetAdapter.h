#ifndef ESL_MEET_ADAPTER_H
#define ESL_MEET_ADAPTER_H

#include "eslBaseAdapter.h"

class CEslMeetAdapter : public CEslBaseAdapter
{
public:
	CEslMeetAdapter();
	~CEslMeetAdapter();

public:
	//Pkg请求包
	void eslBuildPkg(const QJsonObject &json, std::string &strJson, int &iPkgType, int &iMsgType);
	
	//Pkg包转换json
	bool eslBuildJson(int iMsgType, char *pPayload, QJsonObject &jsonRet);

protected:
	//创建会议Req
	void OnReqEslCreateMeet(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//创建会议Resp
	bool OnRespEslCreateMeet(const QJsonObject &json, QJsonObject &jsonRet);
	
	//关闭会议Req
	void OnReqEslCloseMeet(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//关闭会议Resp
	bool OnRespEslCloseMeet(const QJsonObject &json, QJsonObject &jsonRet);
	
	//增加会议成员Req
	void OnReqEslAddMeetMemb(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//增加会议成员Resp
	bool OnRespEslAddMeetMemb(const QJsonObject &json, QJsonObject &jsonRet);
	
	//删除会议成员Req
	void OnReqEslDelMeetMemb(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//删除会议成员Resp
	bool OnRespEslDelMeetMemb(const QJsonObject &json, QJsonObject &jsonRet);
	
	//静音会议成员Req
	void OnReqEslMuteMeetMemb(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//静音会议成员Resp
	bool OnRespEslMuteMeetMemb(const QJsonObject &json, QJsonObject &jsonRet);
	
	//禁言会议成员Req
	void OnReqEslSilenceMeetMemb(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//禁言会议成员Resp
	bool OnRespEslSilenceMeetMemb(const QJsonObject &json, QJsonObject &jsonRet);
	
	//视频会议分屏Req
	void OnReqEslSplitScrMeet(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//视频会议分屏Resp
	bool OnRespEslSplitScrMeet(const QJsonObject &json, QJsonObject &jsonRet);
	
	//演讲会议成员Req
	void OnReqEslSpeechMeetMemb(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//演讲会议成员Resp
	bool OnRespEslSpeechMeetMemb(const QJsonObject &json, QJsonObject &jsonRet);
	
	//通话转会议Req
	void OnReqEslCallToMeet(const QJsonObject &json, std::string &strJson, int &iMsgType);
	
	//通话转会议Resp
	bool OnRespEslCallToMeet(const QJsonObject &json, QJsonObject &jsonRet);
};

#endif