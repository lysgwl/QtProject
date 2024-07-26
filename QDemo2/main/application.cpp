#include "application.h"

#include <QtGui>
#include <QDebug>

CApplication::CApplication(int &argc, char **argv):
    QApplication(argc, argv)
{
    m_pMainFrameWindow = nullptr;
}

void CApplication::initModule()
{
    setAppEnv();
    setAppModule();
}

void CApplication::runModule()
{
    m_pMainFrameWindow->initUI();
    uint uFlag = m_pMainFrameWindow->windowFlags();
    //m_pMainFrameWindow->setWindowFlags(uFlag&~Qt::WindowMaximizeButtonHint);
    m_pMainFrameWindow->show();
}

void CApplication::setAppEnv()
{
}

void CApplication::setAppModule()
{
    m_pMainFrameWindow = new CMainFrameWindow;
}
