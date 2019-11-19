#include "ControlerMainHandler.h"

#include "../inc/FrameWork.h"
#include "./MainFrameControl.h"

CControlerMainHandler::CControlerMainHandler()
{
}

void CControlerMainHandler::registerObj()
{
    CFrameWork::getObjectMgr()->addObject(Controler_MainFrame_Id, new CMainFrameControl);
}
