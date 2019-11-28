#include "ControlerMainHandler.h"

#include "../inc/FrameWork.h"
#include "./MainFrameControl.h"
#include "./ToolStatusControl.h"

CControlerMainHandler::CControlerMainHandler()
{
}

void CControlerMainHandler::registerObj()
{
    CFrameWork::getObjectMgr()->addObject(Controler_MainFrame_Id, new CMainFrameControl);
    CFrameWork::getObjectMgr()->addObject(Controler_ToolStatus_Id, new CToolStatusControl);
}
