#include "ViewMainHandler.h"

#include "../inc/FrameWork.h"
#include "./MainFrameView.h"
#include "./ToolStatusView.h"

CViewMainHandler::CViewMainHandler()
{
}

void CViewMainHandler::registerObj()
{
     CFrameWork::getObjectMgr()->addObject(View_MainFrame_id, new CMainFrameView);
     CFrameWork::getObjectMgr()->addObject(View_ToolStatus_id, new CToolStatusView);
}
