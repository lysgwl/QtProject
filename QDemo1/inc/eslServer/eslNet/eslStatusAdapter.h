#ifndef ESL_STATUS_ADAPTER_H
#define ESL_STATUS_ADAPTER_H

#include "eslBaseAdapter.h"

class CEslStatusAdapter : public CEslBaseAdapter
{
public:
	CEslStatusAdapter();
	~CEslStatusAdapter();

public:
	//Pkg包转换json
	bool eslBuildJson(int iMsgType, char *pPayload, QJsonObject &jsonRet);
	
protected:
	//状态通知
	bool eslGetUserStatus(const QJsonObject &json, QJsonObject &jsonRet);
	
	//通话状态
	void OnEslCallStatus(const QJsonObject &json, QJsonObject &jsonRet);
	
	//会议状态
	void OnEslMeetStatus(const QJsonObject &json, QJsonObject &jsonRet);
	
	//通播状态
	void OnEslAnnounceStatus(const QJsonObject &json, QJsonObject &jsonRet);
};

#endif