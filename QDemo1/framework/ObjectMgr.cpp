#include "ObjectMgr.h"

CObjectMgr::CObjectMgr()
{}

CObjectMgr::~CObjectMgr()
{
	cleanObject();
}

// 初始化服务
void CObjectMgr::init()
{
}

// 执行服务
void CObjectMgr::exec()
{
}

// 获取对象
CObject* CObjectMgr::getObject(const QString& strName)
{
	if (!m_mapData.contains(strName))
	{
		return nullptr;
	}
	
    return m_mapData[strName];
}

// 注册对象
void CObjectMgr::addObject(const QString& strName, CObject* obj)
{
	if (!obj)
	{
		return;
	}
	
    m_mapData.insert(strName, obj);
}

// 清空对象
void CObjectMgr::cleanObject()
{
	m_mapData.clear();
}
