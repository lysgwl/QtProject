#include "application.h"

#include <platform.h>

CApplication::CApplication(int &argc, char **argv):
    QApplication(argc, argv)
{
}

void CApplication::init_module()
{
    set_app_env();
    set_app_module();
}

void CApplication::run_module()
{
    CTopMainFrameController* pTopMainFrame = GET_OBJECT_PTR(CTopMainFrameController);
    CMainWindowController* pMainWindow = GET_OBJECT_PTR(CMainWindowController);
    if (pTopMainFrame != nullptr && pMainWindow != nullptr)
    {
        pTopMainFrame->setcurrentview(pMainWindow->getview());
        pTopMainFrame->exec();
    }
}

void CApplication::set_app_env()
{
    CFrameWork::GetInstance().init();
}

void CApplication::set_app_module()
{
    CTopMainFrameController* pTopMainFrame = GET_OBJECT_PTR(CTopMainFrameController);
    if (pTopMainFrame != nullptr)
    {
        pTopMainFrame->init();
    }
}
