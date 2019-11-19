#include "ObjectMgr.h"

CObjectMgr::CObjectMgr()
{
}

void* CObjectMgr::getObject(uint uId)
{
    return m_mapData.value(uId);
}

void CObjectMgr::addObject(uint uId, void *obj)
{
    if (uId == 0 || obj == nullptr)
    {
        return;
    }

    if (m_mapData.find(uId) != m_mapData.end())
    {
        return;
    }

    m_mapData[uId] = obj;
}
