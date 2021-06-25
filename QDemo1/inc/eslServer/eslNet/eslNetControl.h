#ifndef ESL_NET_CONTROL_H
#define ESL_NET_CONTROL_H

#include "eslDataAdapter.h"

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
	CElsMeetAdapter *m_pMeetAdapter = Q_NULLPTR;
	//CElsStatusAdapter *m_pStatusAdapter = Q_NULLPTR;	
};

#endif
