#ifndef ELS_SERVER_H
#define ELS_SERVER_H

class CElsServer
{
public:
	CElsServer();
	virtual ~CElsServer();

public:
	//�Ƿ�֧��els����
	bool isElsServer(const QJsonObject &jsonObject);

	//��Ϣ����
	bool elsSendMessage(stMESSAGE *pstMsg, QByteArray &arSend);
	
	//pkg������
	bool elsParsePkg(char *pPkgBuf, int iLen, void *pstEvent);
	
	//��Ϣת��json
	void elsBuildJson(const stMESSAGE *pMessage, std::string &strJson);

protected:
	//pkg��ͷ����
	bool parsePkg(char *pPkgBuf, stTerminalPkgHeader **pstPkgHeader);
	
private:
	CElsDataAdapter *m_pDataAdapter = Q_NULLPTR;
	CElsMeetAdapter *m_pMeetAdapter = Q_NULLPTR;
	CElsStatusAdapter *m_pStatusAdapter = Q_NULLPTR;	
};

#endif