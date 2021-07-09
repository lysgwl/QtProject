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
	
	//esl快捷通讯录
	bool eslSetPageData(int iType, const QJsonObject &json);
	
	//esl公共通讯录
	bool eslSetPublicContact(const QJsonObject &json);
	
	//esl席位通讯录
	bool eslSetSeatContact(int iType, const QJsonObject &json);
	
protected:
	//设置系统数据
	void eslSetSysData(const QJsonObject &json, const QJsonObject &jsonData);

	//设置设备数据
	bool eslSetDevData(const QJsonObject &json);
	
	//获取设备数据
	bool eslGetDevData(const QJsonObject &json);
	
	//设置用户数据
	bool eslSetUserData(const QJsonObject &json);
	
	//获取用户数据
	bool eslGetUserData(const QJsonObject &json);
	
	//获取快捷数据
	bool eslGetPageData(const QJsonObject &json);
	
	//设置公共通讯录
	void GetPublicContact(const QJsonObject &json);
};

#endif