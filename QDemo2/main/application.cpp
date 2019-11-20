#include "application.h"

#include <QtGui>
#include <QDebug>

#include "../inc/FrameWork.h"
#include "../control/MainFrameControl.h"

#include "../widget/ViewMainHandler.h"
#include "../control/ControlerMainHandler.h"

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
    CMainFrameControl *pMainFrameControl = (CMainFrameControl*)CFrameWork::getObjectPointer(Controler_MainFrame_Id);
    if (pMainFrameControl == nullptr)
    {
        return;
    }

    pMainFrameControl->initMainFrame();
}

void CApplication::setAppEnv()
{
   setWindowIcon(QIcon(":/Images/ocrstyle.png"));

   //qDebug() << QLocale::system().name() << endl;
   QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

   QString strFileDir = ":/Languages/translations";
   QString strFileName = QString("style_") + QLocale::system().name();

   QTranslator translator;
   translator.load(strFileName, strFileDir);
   installTranslator(&translator);
}

void CApplication::setAppModule()
{
    CViewMainHandler::registerObj();
    CControlerMainHandler::registerObj();
}
