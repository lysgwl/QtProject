//#include <QtWidgets>
//#include <QGuiApplication>

#include <QtGui>
#include <QTimer>
#include <QTextCodec>
#include <QTranslator>
#include <QSplashScreen>
#include <QStyleFactory>
#include <QApplication>

#include "mainwindow.h"

#include <QLabel>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/res/ocrstyle.png"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    //qDebug() << "测试" << endl;

    MainWindow mainWindow;
    mainWindow.showMaximized();
    mainWindow.show();

    return a.exec();
}
