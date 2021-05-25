#include "ObjectMgr.h"

ObjectMgr::ObjectMgr()
{
}

void* ObjectMgr::getObject(uint uiId)
{
    return m_mapData.value(uiId);
}

void ObjectMgr::addObject(uint uiId, void *obj)
{
    if (uiId == 0 || obj == nullptr)
    {
        return;
    }

    if (m_mapData.find(uiId) != m_mapData.end())
    {
        return;
    }

    m_mapData[uiId] = obj;
}