#include "MainWindowController.h"

#include <platform.h>

CMainWindowController::CMainWindowController() 
{
}

CMainWindowController::~CMainWindowController()
{
}

void CMainWindowController::registerobj()
{
   REGISTER_OBJECT(CTaskStatusBarController, new CTaskStatusBarController);

   CTaskStatusBarController* pStatusBar = GET_OBJECT_PTR(CTaskStatusBarController);
   if (pStatusBar != nullptr)
   {
       pStatusBar->registerobj();
   }
}

void CMainWindowController::init()
{
    if (m_pMainWindowView == Q_NULLPTR)
	{
        m_pMainWindowView = new CMainWindowView();
        m_pMainWindowView->init();

        CTaskStatusBarController* pStatusBar = GET_OBJECT_PTR(CTaskStatusBarController);
        if (pStatusBar != nullptr)
        {
            pStatusBar->init();
        }
    }
}

void CMainWindowController::exec()
{
    if (m_pMainWindowView == Q_NULLPTR)
    {
        return;
    }

    CTaskStatusBarController* pStatusBar = GET_OBJECT_PTR(CTaskStatusBarController);
    if (pStatusBar != nullptr)
    {
        pStatusBar->exec();
    }
}

CObject* CMainWindowController::getobject()
{
    return this;
}

QWidget* CMainWindowController::getview()
{
    return m_pMainWindowView;
}
