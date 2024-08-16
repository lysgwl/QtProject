#include "MainWindowController.h"

CMainWindowController::CMainWindowController() 
{
}

CMainWindowController::~CMainWindowController()
{
}

void CMainWindowController::registerobj()
{
}

void CMainWindowController::init()
{
    if (m_pMainWindowView == Q_NULLPTR)
	{
        m_pMainWindowView = new CMainWindowView();
        m_pMainWindowView->init();
    }
}

void CMainWindowController::exec()
{
}

CObject* CMainWindowController::getobject()
{
    return this;
}

QWidget* CMainWindowController::getview()
{
    return m_pMainWindowView;
}
