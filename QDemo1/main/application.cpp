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
    CTopMainFrameController* pController = GET_OBJECT_PTR(CTopMainFrameController);
    if (pController != nullptr)
    {
        pController->init();
    }
}

void CApplication::set_app_env()
{
    CFrameWork::GetInstance().init();
}

void CApplication::set_app_module()
{
    //ControlerMain::registerObj();
}
