#ifndef __OBJECT_SERVICE_LOCATOR_H__
#define __OBJECT_SERVICE_LOCATOR_H__

#include <IMgrService.h>

// 对象服务定位器模板类
template <typename T>
class CObjectServiceLocator : public IMgrServiceLocator
{
private:
	QMap<QString, QSharedPointer<IService>><T> m_mapService;
	 
public
	CObjectServiceLocator() {}
	~CObjectServiceLocator() 
	{
		cleanService();
	}
	
protected:
	void cleanService()
	{
		m_mapService.clear();
	}
	
public:
	T* getService(const std::string& strServiceName)
	{
		if (!m_mapService.contains(strServiceName))
		{
			return nullptr;
		}
		
		return m_mapService.value(strServiceName).data();
	}
	
	void addService(const std::string& strServiceName, T* service)
	{
		if (!service)
		{
			return;
		}
		
		 m_mapService.insert(strServiceName, QSharedPointer<T>(service));
	}
	
	void removeService(const std::string& strServiceName)
	{
		m_mapService.remove(strServiceName);
	}
};

#endif