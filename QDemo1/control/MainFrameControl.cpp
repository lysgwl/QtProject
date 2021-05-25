#include "MainFrameControl.h"

#include "../inc/FrameWork.h"
#include "ControlerMain.h"
#include "WorkMainControl.h"

CMainFrameControl::CMainFrameControl(QObject *parent) 
		: QObject(parent)
{
}

QObject* CMainFrameControl::getObject()
{
    return this;
}

QWidget* CMainFrameControl::getWidget()
{
    return m_pMainView;
}

void CMainFrameControl::initMainFrame()
{
    if (m_pMainView == Q_NULLPTR)
    {
        m_pMainView = new CMainFrameView();
        m_pMainView->initUI();

        ObjectPtr<CWorkMainControl> workFrame(Controler_WorkFrame, CFrameWork::getObjectMgr());
        workFrame->initWorkFrame();

        QStackedWidget *pStackedWidget = m_pMainView->getStackedWidget();
        if (pStackedWidget != Q_NULLPTR)
        {
            pStackedWidget->addWidget(new QPushButton("call"));
            pStackedWidget->addWidget(workFrame->getWidget());
            pStackedWidget->addWidget(new QPushButton("aotu call"));
        }

        m_pMainView->showMain();
    }
}

void CMainFrameControl::updateMainFrame()
{
}
