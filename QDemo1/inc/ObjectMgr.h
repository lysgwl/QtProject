#ifndef __OBJECT_MGR_H__
#define __OBJECT_MGR_H__

#include <QMap>
#include <QHash>

class CObjectMgr
{
public:
	CObjectMgr();
	
public:
	void*		getObject(uint uId);
	
	void		addObject(uint uId, void *obj);
	
private:	
	QHash<uint, void*> m_mapData;
};

#endif
