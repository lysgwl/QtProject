#include "FrameWork.h"

CFrameWork::CFrameWork()
{
}

ObjectMgr* CFrameWork::getObjectMgr()
{
	static ObjectMgr objectMgr;
	return &objectMgr;
}

void* CFrameWork::getObjectPointer(uint uiId)
{
   return CFrameWork::getObjectMgr()->getObject(uiId);
}