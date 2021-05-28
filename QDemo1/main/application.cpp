#include "application.h"

#include <internal.h>
#include "../control/ControlerMain.h"

CApplication::CApplication(int &argc, char **argv):
    QApplication(argc, argv)
{
}

void CApplication::initModule()
{
    setAppEnv();
    setAppModule();
}

void CApplication::runModule()
{
    ControlerMain::showControlMain();
}

void CApplication::setAppEnv()
{
    CFrameWork::getFrameWork().initGlobalEnv();
}

void CApplication::setAppModule()
{
    ControlerMain::registerObj();
}
