#ifndef __I_MGR_SERVICE_H__
#define __I_MGR_SERVICE_H__

#include <internal.h>

// 服务接口声明
class IMgrService
{
public:
	virtual ~IService() = default; 
	
	// 初始化服务
	virtual void init() = 0;
	
	// 执行服务
	virtual void exec() = 0;	
};
 
// 服务定位器接口声明
class IMgrServiceLocator
{
public:
	virtual ~IMgrServiceLocator() = default;
	
	// 获取服务实例
	virtual IMgrService* getService(const QString& strServiceName) = 0;
	
	// 注册服务
	virtual void addService(const QString& strServiceName, IMgrService* service) = 0;
	
	// 移除服务
	virtual void removeService(const QString& strServiceName) = 0;
};

#endif