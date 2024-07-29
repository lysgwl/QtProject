#ifndef __OBJECT_SERVICE_LOCATOR_H__
#define __OBJECT_SERVICE_LOCATOR_H__

#include <IMgrService.h>

// 对象服务定位器模板类
template <typename T>
class CObjectServiceLocator : public IMgrServiceLocator
{
private:
    QMap<QString, QSharedPointer<T>> m_mapService;
	 
public:
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
    T* getService(const QString& strServiceName)
	{
        if (!m_mapService.contains(strServiceName))
		{
			return nullptr;
		}
		
        return m_mapService.value(strServiceName).data();
	}
	
    void addService(const QString& strServiceName, IMgrService* service)
	{
		if (!service)
		{
			return;
		}
		
        m_mapService.insert(strServiceName, QSharedPointer<T>(service));
	}
	
    void removeService(const QString& strServiceName)
	{
        m_mapService.remove(strServiceName);
	}
};

#endif
