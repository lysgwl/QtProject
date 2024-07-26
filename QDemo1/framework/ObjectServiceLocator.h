#ifndef __OBJECT_SERVICE_LOCATOR_H__
#define __OBJECT_SERVICE_LOCATOR_H__

// 对象服务定位器模板类
template <typename T>
class CObjectServiceLocator : public IMgrServiceLocator
{
private:
	 std::map<std::string, T*> m_mapService;
	 
public
	CObjectServiceLocator() {}
	~CObjectServiceLocator() {
		cleanService();
	}
	
protected:
	void cleanService()
	{
		typename std::map<std::string, T*>::iterator iter;
		
		for (iter = m_mapService.begin(); iter != m_mapService.end(); ++iter) {
            delete iter->second; 
        }
		
		m_mapService.clear();
	}
	
public:
	T* getService(const std::string& strServiceName)
	{
		typename std::map<std::string, T*>::iterator iter = m_mapService.find(strServiceName);
		
		if (iter == m_mapService.end())
		{
			return NULL;
		}
		
		return iter->second;
	}
	
	void addService(const std::string& strServiceName, T* service)
	{
		if (m_mapService.find(strServiceName) != m_mapService.end())
		{
			return;
		}
		
		m_mapService[strServiceName] = service;
	}
	
	void removeService(const std::string& strServiceName)
	{
		typename std::map<std::string, T*>::iterator iter = m_mapService.find(strServiceName);
		
		if (iter == m_mapService.end())
		{
			return;
		}
		
		delete iter->second;
		m_mapService.erase(iter);
	}
};


#endif