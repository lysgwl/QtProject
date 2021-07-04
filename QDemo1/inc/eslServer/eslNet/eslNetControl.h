#ifndef ESL_NET_CONTROL_H
#define ESL_NET_CONTROL_H

#include "eslDataAdapter.h"
#include "eslMeetAdapter.h"
#include "eslStatusAdapter.h"

class CEslNetControl
{
public:
	CEslNetControl();
	virtual ~CEslNetControl();

public:
	//是否开启服务
	bool isEslServer();
	
	//消息请求
    void eslSendMessage(const QJsonObject &json, QByteArray &arSend);
	
	//消息接收
	bool eslRecvMessage(char *pPkgBuf, std::string &strUserNum);
	
private:
    CEslDataAdapter *m_pDataAdapter = Q_NULLPTR;
	CEslMeetAdapter *m_pMeetAdapter = Q_NULLPTR;
	CEslStatusAdapter *m_pStatusAdapter = Q_NULLPTR;	
};

#endif
