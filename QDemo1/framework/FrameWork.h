#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <internal.h>

class CFrameWork
{
private:
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
	// 初始化服务
	void init_service();
	
	// 初始化对象
	void init_object();
	
public:
	// 初始化
	void init();
};

#endif
