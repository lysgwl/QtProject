#ifndef __OBJECT_MGR_H__
#define __OBJECT_MGR_H__

#include <IMgrObject.h>
#include <IMgrService.h>

class CObjectMgr : public IMgrObject, public IMgrService
{
private:
	QMap<QString, CObject*> m_mapData;
	
public:
    CObjectMgr();
    ~CObjectMgr();
	
public:
	// 初始化服务
    void init() override;

	// 执行服务
    void exec() override;

public:
	// 获取对象
	CObject* getObject(const QString& strName) override;
	
	// 注册对象
	void addObject(const QString& strName, CObject* obj) override;
	
	// 清空对象
	void cleanObject();
};

DECLARE_OBJ(CObjectMgr, "org.CObjectMgr.service")

#endif
