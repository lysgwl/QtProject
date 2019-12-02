#include "MainFrameControl.h"

#include "../inc/FrameWork.h"
#include "../widget/MainFrameView.h"
#include "../widget/ToolStatusView.h"
#include "../widget/ViewMainHandler.h"

#include "../widget/ScreenShotView.h"

CMainFrameControl::CMainFrameControl(QObject *parent) 
		: QObject(parent)
{
}

void CMainFrameControl::initMainFrame()
{
    CMainFrameView *pMainView = (CMainFrameView*)CFrameWork::getObjectPointer(View_MainFrame_id);
    if (pMainView == nullptr)
        return;

    //pMainView->initUI();
    //pMainView->showMain();

    CScreenShotView *pScreenShot = new CScreenShotView;
    pScreenShot->initUI();
}

QObject* CMainFrameControl::getObject()
{
    return this;
}
