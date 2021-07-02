#ifndef ELS_HTTP_CONTROL_H
#define ELS_HTTP_CONTROL_H

#include "eslHttpData.h"
#include "eslHttpCall.h"
#include "eslHttpMeet.h"

class CEslHttpControl
{
public:
	CEslHttpControl();
	virtual ~CEslHttpControl();
	
public:
	//esl获取数据
	bool eslGetDataFromSrv(QJsonObject &json);
	
	//esl设置数据
	bool eslSetSrvData(QJsonObject &json);
	
	//esl设置事件
	void eslSetUserEvent(QJsonObject &json);
	
public:	
	//获取data对象指针
	CEslHttpData *eslGetDataPtr() const;
	
	//获取call对象指针
	CEslHttpCall *eslGetCallPtr() const;
	
	//获取meet对象指针
	CEslHttpMeet *eslGetMeetPtr() const;
	
protected:
	CEslHttpData *m_pEslHttpData = Q_NULLPTR;
	CEslHttpCall *m_pEslHttpCall = Q_NULLPTR;
	CEslHttpMeet *m_pEslHttpMeet = Q_NULLPTR;
};

#endif