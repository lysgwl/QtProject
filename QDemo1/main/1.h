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


app.setWindowIcon(QIcon(":/Images/res/ocrstyle.png"));

    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

    //qDebug() << QLocale::system().name() << endl;
    QString strFileName = QString("style_") + QLocale::system().name();
    QString strFileDir = ":/Languages/res/translations";

    QTranslator translator;
    translator.load(strFileName, strFileDir);
    app.installTranslator(&translator);

    MainWindow mainWindow;
    mainWindow.showMaximized();
    mainWindow.show();