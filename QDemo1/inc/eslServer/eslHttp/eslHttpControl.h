#ifndef ELS_HTTP_CONTROL_H
#define ELS_HTTP_CONTROL_H

#include "eslHttpData.h"
#include "eslHttpCall.h"

class CEslHttpControl
{
public:
	CEslHttpControl();
	virtual ~CEslHttpControl();
	
public:
	//esl获取数据
	void eslGetDataFromSrv(std::string &strCallNum, std::string &strToken);
	
	//esl设置数据
	void eslSetSrvData(bool bIsSeat, std::string &strCallNum, std::string &strToken);
	
	//esl设置事件
	void eslSetUserEvent();
	
public:	
	//获取data对象指针
	CEslHttpData *eslGetDataPtr() const;
	
	//获取call对象指针
	CEslHttpCall *eslGetCallPtr() const;
	
protected:
	CEslHttpData *m_pEslHttpData = Q_NULLPTR;
	CEslHttpCall *m_pEslHttpCall = Q_NULLPTR;
};

#endif