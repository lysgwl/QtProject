#include "ControlerMain.h"

#include <internal.h>

#include "./HomePageControl.h"
#include "./MainFrameControl.h"
#include "./WorkMainControl.h"
#include "./ToolStatusControl.h"

ControlerMain::ControlerMain()
{
}

void ControlerMain::registerObj()
{
    ObjectMgr *pObjectMgr = CFrameWork::getFrameWork().getObjectMgr();
	if (pObjectMgr == Q_NULLPTR)
	{
		return;
	}
	
	//pObjectMgr->addObject(NULL, this);

    pObjectMgr->addObject(Controler_HomePage, new CHomePageControl);
	
    pObjectMgr->addObject(Controler_MainFrame, new CMainFrameControl);
	
    pObjectMgr->addObject(Controler_WorkFrame, new CWorkMainControl);

    pObjectMgr->addObject(Controler_ToolStatus, new CToolStatusControl);
}

void ControlerMain::showControlMain()
{
    ObjectMgr *pObjectMgr = CFrameWork::getFrameWork().getObjectMgr();
	if (pObjectMgr == Q_NULLPTR)
	{
		return;
	}
	
    ObjectPtr<CMainFrameControl> mainFrame(Controler_MainFrame, pObjectMgr);
    mainFrame->initMainFrame();
    mainFrame->updateMainFrame();
}
