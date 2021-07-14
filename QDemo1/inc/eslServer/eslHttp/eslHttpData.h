#ifndef ESL_HTTP_DATA_H
#define ESL_HTTP_DATA_H

#include "eslHttpBase.h"

class CEslHttpData : public CEslHttpBase
{
public:
	CEslHttpData();
	~CEslHttpData();
	
public:
	//esl系统配置
	bool eslGetSysConfig(const QJsonObject &json, QJsonObject &jsonValue);

	//esl设备配置
	bool eslSetDevConfig(bool bFlag, const QJsonObject &json);
	
	//esl用户配置
	bool eslSetUserConfig(bool bFlag, const QJsonObject &json);
	
	//esl公共通讯录
	bool eslGetPublicContact(bool bFlag, const QJsonObject &json);

	//esl快捷通讯录
	bool eslSetPageData(int iType, const QJsonObject &json);
	
	//esl席位通讯录
	bool eslSetSeatContact(int iType, const QJsonObject &json);
	
protected:
	//设置系统数据
	void setSysData(const QJsonObject &json, const QJsonObject &jsonData);

	//设置设备数据
	bool setDevData(const QJsonObject &json);
	
	//获取设备数据
	bool getDevData(const QJsonObject &json);
	
	//设置用户数据
	bool setUserData(const QJsonObject &json);
	
	//获取用户数据
	bool getUserData(const QJsonObject &json);

	//设置公共通讯录
	void setPublicContact(const QJsonObject &json);
	
	//获取快捷数据
	bool getPageData(bool isUrl, const QJsonObject &json);
};

#endif