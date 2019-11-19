#include "FrameWork.h"

CFrameWork::CFrameWork()
{
}

CObjectMgr* CFrameWork::getObjectMgr()
{
	static CObjectMgr objectMgr;
	return &objectMgr;
}

void* CFrameWork::getObjectPointer(uint uObjectId)
{
   return CFrameWork::getObjectMgr()->getObject(uObjectId);
}
