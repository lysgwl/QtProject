#ifndef ESL_HTTP_MEET_H
#define ESL_HTTP_MEET_H

#include "eslHttpBase.h"

class CEslHttpMeet : public CEslHttpBase
{
public:
	CEslHttpMeet();
	virtual ~CEslHttpMeet();

public:
	//获取成员列表
	bool eslGetMeetUserList(const QJsonObject &json, QJsonObject &jsonValue);
	
	//获取会议模板
	bool eslGetMeetTemplate(const QJsonObject &json, QJsonObject &jsonValue);

	//创建会议模板
	bool eslAddMeetTemplate(const QJsonObject &json, const QVector<QString> &vecMember, QJsonObject &jsonValue);

	//删除会议模板
	bool eslDelMeetTemplate(const QJsonObject &json);
};

#endif