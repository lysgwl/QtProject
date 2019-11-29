#include "MainFrameControl.h"

#include "../inc/FrameWork.h"
#include "../widget/MainFrameView.h"
#include "../widget/ToolStatusView.h"
#include "../widget/ViewMainHandler.h"

CMainFrameControl::CMainFrameControl(QObject *parent) 
		: QObject(parent)
{
}

void CMainFrameControl::initMainFrame()
{
    CMainFrameView *pMainView = (CMainFrameView*)CFrameWork::getObjectPointer(View_MainFrame_id);
    if (pMainView == nullptr)
        return;

    pMainView->initUI();
    pMainView->showMain();
}

QObject* CMainFrameControl::getObject()
{
    return this;
}
