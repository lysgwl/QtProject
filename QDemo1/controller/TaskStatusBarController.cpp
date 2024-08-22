#include "TaskStatusBarController.h"

CTaskStatusBarController::CTaskStatusBarController() 
{
}

CTaskStatusBarController::~CTaskStatusBarController()
{
}

void CTaskStatusBarController::registerobj()
{
}

void CTaskStatusBarController::init()
{
    if (m_pTaskStatusBarView == nullptr)
    {
        m_pTaskStatusBarView = new CTaskStatusBarView;
        m_pTaskStatusBarView->init();
    }
}

void CTaskStatusBarController::exec()
{
    if (m_pTaskStatusBarView != nullptr)
    {
        m_pTaskStatusBarView->exec();
    }
}

CObject* CTaskStatusBarController::getobject()
{
    return this;
}

QWidget* CTaskStatusBarController::getview()
{
    return m_pTaskStatusBarView;
}

/*
void CToolStatusControl::initUI(CToolStatusView *pToolStatusView)
{
    m_pToolStatusView = pToolStatusView;
    m_pToolStatusView->initUI();
}
*/
