#ifndef ELS_HTTP_CONTROL_H
#define ELS_HTTP_CONTROL_H

class CEslHttpControl
{
public:
	CEslHttpControl();
	~CEslHttpControl();

public:
	//esl获取配置
	bool eslHttpGetDataFromSrv();
};

#endif