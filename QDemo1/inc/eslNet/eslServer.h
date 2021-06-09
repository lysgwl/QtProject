#ifndef ESL_SERVER_H
#define ESL_SERVER_H

#include "eslHeader.h"
#include "eslDataAdapter.h"

class CEslServer
{
public:
	CEslServer();
	virtual ~CEslServer();

public:
	//是否支持els服务
	bool isEslServer(const QJsonObject &jsonObject);

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
