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
    bool eslSendMessage(const stMESSAGE *pstMsg, QByteArray &arSend);
	
	//pkg包解析
    bool eslParsePkg(char *pPkgBuf, void *pstEvent);
	
	//消息转换json
    void eslBuildJson(stMESSAGE *pstMsg, std::string &strJson);

protected:
	//pkg包头解析
	bool parsePkg(char *pPkgBuf, stTerminalPkgHeader **pstPkgHeader);
	
private:
    CEslDataAdapter *m_pDataAdapter = Q_NULLPTR;
	//CElsMeetAdapter *m_pMeetAdapter = Q_NULLPTR;
	//CElsStatusAdapter *m_pStatusAdapter = Q_NULLPTR;	
};

#endif
