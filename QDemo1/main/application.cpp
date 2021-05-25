#include "application.h"

#include <QtGui>
#include <QDebug>

#include "../inc/FrameWork.h"
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
}

void CApplication::setAppModule()
{
    ControlerMain::registerObj();
}
