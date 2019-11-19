#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#include "./ObjectMgr.h"

class CFrameWork
{
public:
	CFrameWork();
	
public:
	static CObjectMgr*		getObjectMgr();
	
    static void*            getObjectPointer(uint uObjectId);
};

#endif
