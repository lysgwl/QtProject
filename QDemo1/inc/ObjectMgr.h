#ifndef OBJECT_MGR_H
#define OBJECT_MGR_H

#include <stHeader.h>

class ObjectMgr
{
public:
	ObjectMgr();
	
public:
	void* getObject(uint uiId);
	
	void addObject(uint uiId, void *obj);
	
private:	
	QHash<uint, void*> m_mapData;
};

template <typename T>
class ObjectPtr
{
public:
    ObjectPtr(const int& iIndex, ObjectMgr *objMgr)
	{
        t = getPointer(iIndex, objMgr);
	}
	
	~ObjectPtr()
	{
	}
	
	T* operator ->()
	{
		return t;
	}
	
	operator bool ()
	{
		return t != Q_NULLPTR;
	}
	
public:
	static T* getPointer(const int& iIndex, ObjectMgr *objMgr)
	{
        if (iIndex <= 0 || objMgr == Q_NULLPTR)
		{
			return Q_NULLPTR;
		}

       return static_cast<T*>(objMgr->getObject(iIndex));
	}
	
private:
	ObjectPtr(const ObjectPtr &) = delete;
	ObjectPtr &operator=(ObjectPtr &) = delete;
	
	bool operator == (const ObjectPtr &ptr) = delete;
	bool operator != (const ObjectPtr &ptr) = delete;
		
private:
	T* t = Q_NULLPTR;	
};

#endif
