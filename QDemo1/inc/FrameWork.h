#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "./ObjectMgr.h"

class CFrameWork
{
public:
	CFrameWork();
	
public:
	static ObjectMgr* getObjectMgr();
	
    static void* getObjectPointer(uint uiId);
};

#endif
