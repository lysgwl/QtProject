#ifndef ESL_HTTP_DATA_H
#define ESL_HTTP_DATA_H

class CEslHttpData : public CEslHttpBase
{
public:
	CEslHttpData();
	~CEslHttpData();

public:
	//获取系统配置
	bool eslGetSysConfig(const QJsonObject &json, QJsonObject &jsonRet);
	
	//获取设备配置
	bool eslGetDevConfig(const QJsonObject &json, QJsonObject &jsonRet);
	
	//设置设备配置
	void eslSetDevConfig(const QJsonObject &json);
	
	//获取用户配置
	bool eslGetUserConfig(const QJsonObject &json, QJsonObject &jsonRet);
	
	//设置用户配置
	void eslSetUserConfig(const QJsonObject &json);
	
	//获取快捷通讯录
	bool eslGetPageData(const QJsonObject &json, QJsonObject &jsonRet);
	
	//获取共同通讯录
	bool eslGetPublicContact(const QJsonObject &json, QJsonObject &jsonRet);
};

#endif