#include "MainFrameControl.h"

#include <internal.h>

#include "ControlerMain.h"
#include "HomePageControl.h"
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
    ObjectMgr *pObjectMgr = CFrameWork::getFrameWork().getObjectMgr();
	if (pObjectMgr == Q_NULLPTR)
	{
		return;
	}
	
    if (m_pMainView == Q_NULLPTR)
    {
        m_pMainView = new CMainFrameView();
        m_pMainView->initUI();

        ObjectPtr<CWorkMainControl> workFrame(Controler_WorkFrame, pObjectMgr);
        workFrame->initWorkFrame();

        ObjectPtr<CHomePageControl> homePage(Controler_HomePage, pObjectMgr);
        homePage->initHomePage();

        QStackedWidget *pStackedWidget = m_pMainView->getStackedWidget();
        if (pStackedWidget != Q_NULLPTR)
        {
            pStackedWidget->addWidget(new QPushButton("call"));
            CWorkMainView *pWorkView = dynamic_cast<CWorkMainView*>(workFrame->getWidget());
            if (pWorkView != Q_NULLPTR)
            {
                pStackedWidget->addWidget(pWorkView);
            }

            pStackedWidget->addWidget(new QPushButton("aotu call"));
        }

        m_pMainView->showMain();
    }
}

void CMainFrameControl::updateMainFrame()
{
    QStackedWidget *pStackedWidget = m_pMainView->getStackedWidget();
    if (pStackedWidget != Q_NULLPTR)
    {
        pStackedWidget->setCurrentIndex(1);
    }
}
