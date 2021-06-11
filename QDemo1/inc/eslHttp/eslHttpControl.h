#ifndef ELS_HTTP_CONTROL_H
#define ELS_HTTP_CONTROL_H

#include "eslHttpData.h"

class CEslHttpControl
{
public:
	CEslHttpControl();
	~CEslHttpControl();
	
public:
	//esl获取数据
	void eslGetDataFromSrv();
	
	//esl设置数据
	void eslGetSrvData(bool bIsSeat, std::string &strCallNum, std::string &strToken);
	
public:
	//esl设置快捷通讯录
	void eslSetPageData(int iPageType, std::string &strCallNum, std::string &strToken);	
	
	//esl设置通话记录
	void eslSetCallLog();

public:
	//esl设置系统配置
	void eslGetSysConfig(std::string &strCallNum, std::string &strToken);
	
	//esl设置设备配置
	void eslGetDevConfig(std::string &strCallNum, std::string &strToken);
	
	//esl设置用户配置
	void eslGetUserConfig(std::string &strCallNum, std::string &strToken);
	
	//esl设置电台列表
	void eslGetRadioList();
	
	//esl设置席位设备列表
	void eslGetSeatDevList();
	
	//esl设置公共通讯录
	void eslGetPublicContact();
	
	//esl设置席位通讯录
	void eslGetSeatContact();
	
	//esl设置模块配置
	void eslGetModuleConfig();
	
	//获取data对象指针
	CEslHttpData *eslGetDataPtr() const;
	
protected:
	//获取快捷数据
	void eslGetPageData();
	
protected:
	CEslHttpData *m_pEslHttpData = Q_NULLPTR;	
};

#endif