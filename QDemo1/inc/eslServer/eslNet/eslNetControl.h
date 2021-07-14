#ifndef ESL_NET_CONTROL_H
#define ESL_NET_CONTROL_H

#include "eslDataAdapter.h"
#include "eslMeetAdapter.h"
#include "eslAnncAdapter.h"

#include "eslStatusAdapter.h"
#include "eslEventAdapter.h"

class CEslNetControl
{
public:
	CEslNetControl();
	virtual ~CEslNetControl();

public:
	//是否开启服务
	bool isEslServer();

	//获取会议包类型
	int eslGetMeetPkgType(const QJsonObject &json);
	
	//消息请求
    void eslSendMessage(const QJsonObject &json, QByteArray &arSend);
	
	//消息接收
	bool eslRecvMessage(char *pPkgBuf, std::string &strUserNum);

private:
    CEslDataAdapter *m_pDataAdapter = Q_NULLPTR;
	CEslMeetAdapter *m_pMeetAdapter = Q_NULLPTR;
	CEslAnncAdapter *m_pAnncAdapter = Q_NULLPTR;
	
	CEslStatusAdapter *m_pStatusAdapter = Q_NULLPTR;	
	CEslEventAdapter *m_pEventAdapter = Q_NULLPTR;
};

#endif
