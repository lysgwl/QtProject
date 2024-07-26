#ifndef ESL_EVENT_ADAPTER_H
#define ESL_EVENT_ADAPTER_H

#include "eslBaseAdapter.h"

class CEslEventAdapter : public CEslBaseAdapter
{
public:
	CEslEventAdapter();
	~CEslEventAdapter();

public:
	//Pkg包转换json
	bool eslBuildJson(int iMsgType, char *pPayload, QJsonObject &jsonRet);
	
protected:
	//更新席位通讯录
	bool eslGetSeatContactNotify(const QJsonObject &json, QJsonObject &jsonRet);
	
	//更新快捷通讯录
	bool eslGetQuickContactNotify(const QJsonObject &json, QJsonObject &jsonRet);
	
	//更新公共通讯录
	bool eslGetPublicContactNotify(const QJsonObject &json, QJsonObject &jsonRet);
	
	//更新个性化配置
	bool eslGetStyleConfigNotify(const QJsonObject &json, QJsonObject &jsonRet);
	
	//通话转会议通知
	bool eslGetCallToMeetNotify(const QJsonObject &json, QJsonObject &jsonRet);
};

#endif