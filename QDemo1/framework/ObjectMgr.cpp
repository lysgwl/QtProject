#include "ObjectMgr.h"


CObjectMgr::CObjectMgr()
{
}

CObjectMgr::~CObjectMgr()
{
}

void CObjectMgr::init()
{
}

void CObjectMgr::exec()
{
}

QString CObjectMgr::getObjectName(CObject* obj)
{
	ObjectKey key = m_mapData.key(obj);
	return std::get<0>(key)
}

void CObjectMgr::addObject(const ObjectKey& key, CObject* obj)
{
	
}

CObject* CObjectMgr::getObject(const QString& strName, const int& index)
{
	return getObject(ObjectKey(strName, index))
}

CObject* CObjectMgr::getObject(const ObjectKey& key)
{
	return m_mapData.value(key);
}