#ifndef ESL_HTTP_ANNC_H
#define ESL_HTTP_ANNC_H

#include "eslHttpBase.h"

class CEslHttpAnnc : public CEslHttpBase
{
public:
	CEslHttpAnnc();
	virtual ~CEslHttpAnnc();

public:
	//获取成员列表
	bool eslGetAnncUserList(const QJsonObject &json, QJsonObject &jsonValue);

	//获取通播模板
	bool eslGetAnncTemplate(const QJsonObject &json, QJsonObject &jsonValue);

	//创建通播模板
	bool eslAddAnncTemplate(const QJsonObject &json, const QVector<QString> &vecMember, QJsonObject &jsonValue);

	//删除通播模板	
	bool eslDelAnncTemplate(const QJsonObject &json);
};

#endif