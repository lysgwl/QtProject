#ifndef ESL_SERVER_H
#define ESL_SERVER_H

#include "STHeader.h"
#include "./eslHttp/eslHttpControl.h"

class CEslServer
{
public:
	CEslServer();
	~CEslServer();

	static CEslServer &Instance();

public:
	//是否开启服务
	bool isEslServer();
	
	//登录用户
	bool loginUser(int iType);

protected:
	//登录席位号码
	bool loginSeatNumber();

	//登录用户号码
	bool loginUserNumber();	
	
	//连接服务器
	bool connectSvr(const QJsonObject &json);
	
protected:
	CEslHttpControl *m_pHttpCtrl = Q_NULLPTR;	
};

#endif