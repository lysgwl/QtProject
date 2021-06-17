#ifndef ESL_HTTP_CALL_H
#define ESL_HTTP_CALL_H

class CEslHttpCall : public CEslHttpBase
{
public:
	CEslHttpCall();
	virtual ~CEslHttpCall();

public:
	//设置呼叫记录
	bool eslSetCallLog(bool bIsUpload, const QJsonObject &json);
	
	//获取电台列表
	bool eslGetRadioList(const QJsonObject &json);
	
protected:
	//获取呼叫记录
	bool eslGetCallLog(const QJsonObject &json);	
	
	//上传呼叫记录
	bool eslUploadCallLog(const QJsonObject &json);
};

#endif