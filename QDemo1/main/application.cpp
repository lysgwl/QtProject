#include "application.h"

#include "../framework/FrameWork.h"

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
    //ControlerMain::showControlMain();
}

void CApplication::set_app_env()
{
    CFrameWork::GetInstance().init();
}

void CApplication::set_app_module()
{
    //ControlerMain::registerObj();
}
