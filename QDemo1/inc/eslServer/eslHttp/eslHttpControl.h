#ifndef ELS_HTTP_CONTROL_H
#define ELS_HTTP_CONTROL_H

#include "eslHttpData.h"
#include "eslHttpCall.h"
#include "eslHttpMeet.h"
#include "eslHttpAnnc.h"

class CEslHttpControl
{
public:
	CEslHttpControl();
	virtual ~CEslHttpControl();
	
public:
	//esl获取数据
	bool eslGetDataFromSrv(const QJsonObject &json);
	
	//esl设置数据
	bool eslSetSrvData(const QJsonObject &json);
	
	//esl设置事件
	void eslSetUserEvent(const QJsonObject &json);
	
public:	
	//获取data对象指针
	CEslHttpData *eslGetDataPtr() const;
	
	//获取call对象指针
	CEslHttpCall *eslGetCallPtr() const;
	
	//获取meet对象指针
	CEslHttpMeet *eslGetMeetPtr() const;
	
	//获取annc对象指针
	CEslHttpAnnc *eslGetAnncPtr() const;
	
protected:
	CEslHttpData *m_pEslHttpData = Q_NULLPTR;
	CEslHttpCall *m_pEslHttpCall = Q_NULLPTR;
	CEslHttpMeet *m_pEslHttpMeet = Q_NULLPTR;
	CEslHttpAnnc *m_pEslHttpAnnc = Q_NULLPTR;
};

#endif