#ifndef ELS_SERVER_H
#define ELS_SERVER_H

#define ELS_PROTOCOL_ID		0x1234abcd

#define ELS_PKG_TYPE_DATA	0x01
#define ELS_PKG_TYPE_MEET	0x02
#define ELS_PKG_TYPE_STATUS	0x03

class CElsServer
{
public:
	CElsServer();
	virtual ~CElsServer();

public:
	bool isElsServer(const QJsonObject &jsonObject);

	bool elsSendMessage(stMESSAGE *pMessage, QByteArray &arSend);
	
	bool elsParsePkg(char *pPkgBuf, int iLen, void *pstEvent);
	
	void elsBuildJson(const stMESSAGE *pMessage, std::string &strJson);

protected:
	void buildPkg(stMESSAGE *pMessage, char *pPkgBuf, int &iLen);
	
	void parsePkg(char *pPkgBuf, stTerminalPkgHeader &stPkgHeader);
	
private:
	CElsDataAdapter *m_pDataAdapter = Q_NULLPTR;
	CElsMeetAdapter *m_pMeetAdapter = Q_NULLPTR;
	CElsStatusAdapter *m_pStatusAdapter = Q_NULLPTR;	
};

#endif