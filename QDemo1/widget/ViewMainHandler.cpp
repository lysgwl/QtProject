#include "ViewMainHandler.h"

#include "../inc/FrameWork.h"
#include "./MainFrameView.h"

CViewMainHandler::CViewMainHandler()
{
}

void CViewMainHandler::registerObj()
{
     CFrameWork::getObjectMgr()->addObject(View_MainFrame_id, new CMainFrameView);
}
