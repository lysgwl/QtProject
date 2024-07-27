#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <internal.h>

class CFrameWork
{
private:
	stGlobalVariant m_stGlobalVariant;
	CObjectServiceLocator<IMgrService> m_serviceLocator;
	
private:
	CFrameWork();
	~CFrameWork();
	
	// 禁止拷贝构造和赋值
	CFrameWork(const CFrameWork&) = delete;
	CFrameWork& operator=(const CFrameWork&) = delete;
	
public:
    static CFrameWork &GetInstance();
	
protected:
	// 初始化全局环境
	void init_global_env();	
	
	// 初始化服务
	void init_service();
	
public:
	// 初始化
	void init();
	
	// 获取全局变量
    stGlobalVariant* get_global_variant();
};

#endif
