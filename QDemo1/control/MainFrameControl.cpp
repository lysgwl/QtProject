#include "MainFrameControl.h"

#include "../inc/FrameWork.h"
#include "../widget/MainFrameView.h"
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

    //QStackedWidget *pStackedWidget = new QStackedWidget();
    //QVBoxLayout *pLayout = new QVBoxLayout();
    //pLayout->addWidget(pStackedWidget);
    //pLayout->setMargin(0);

    //pMainView->setLayout(pLayout);
    //pMainView->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    //pMainView->setFixedSize();
    pMainView->initUI();

    pMainView->showMaximized();  //showFullScreen
}

QObject* CMainFrameControl::getObject()
{
    return this;
}
