#ifndef __I_MGR_SERVICE_H__
#define __I_MGR_SERVICE_H__

// 服务接口声明
class IMgrService
{
public:
	virtual void init() = 0;
	virtual void exec() = 0;	
};
 
// 服务定位器接口声明
class IMgrServiceLocator
{
public:
	// 获取服务实例
	virtual IMgrService* getService(const std::string& strServiceName) = 0;
	
	// 注册服务
	virtual void addService(const std::string& strServiceName, IMgrService* service) = 0;
	
	// 移除服务
	virtual void removeService(const std::string& strServiceName) = 0;
};

#endif