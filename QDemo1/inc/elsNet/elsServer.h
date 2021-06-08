#ifndef ELS_SERVER_H
#define ELS_SERVER_H

#include "elsHeader.h"
#include "elsDataAdapter.h"

class CElsServer
{
public:
	CElsServer();
	virtual ~CElsServer();

public:
	//是否支持els服务
	bool isElsServer(const QJsonObject &jsonObject);

	//消息请求
    bool elsSendMessage(const stMESSAGE *pstMsg, QByteArray &arSend);
	
	//pkg包解析
    bool elsParsePkg(char *pPkgBuf, void *pstEvent);
	
	//消息转换json
	void elsBuildJson(const stMESSAGE *pstMsg, std::string &strJson);

protected:
	//pkg包头解析
	bool parsePkg(char *pPkgBuf, stTerminalPkgHeader **pstPkgHeader);
	
private:
	CElsDataAdapter *m_pDataAdapter = Q_NULLPTR;
	//CElsMeetAdapter *m_pMeetAdapter = Q_NULLPTR;
	//CElsStatusAdapter *m_pStatusAdapter = Q_NULLPTR;	
};

#endif
