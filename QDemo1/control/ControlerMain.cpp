#include "ControlerMain.h"

#include "../inc/FrameWork.h"
#include "./MainFrameControl.h"
#include "./WorkMainControl.h"
#include "./ToolStatusControl.h"

ControlerMain::ControlerMain()
{
}

void ControlerMain::registerObj()
{
	//CFrameWork::getObjectMgr()->addObject(NULL, this);
	
    CFrameWork::getObjectMgr()->addObject(Controler_MainFrame, new CMainFrameControl);
	
    CFrameWork::getObjectMgr()->addObject(Controler_WorkFrame, new CWorkMainControl);

    CFrameWork::getObjectMgr()->addObject(Controler_ToolStatus, new CToolStatusControl);
}

void ControlerMain::showControlMain()
{
    ObjectPtr<CMainFrameControl> mainFrame(Controler_MainFrame, CFrameWork::getObjectMgr());
    mainFrame->initMainFrame();
    mainFrame->updateMainFrame();
}
