#ifndef ST_HEAD_H
#define ST_HEAD_H

#include <QMap>
#include <QHash>

#include <QDir>
#include <QObject>
#include <QString>

#include <QtGui>
#include <QDebug>
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QApplication>
#include <QStackedWidget>

enum ControlerHandler{
    Controler_HomePage   = 0x1000,
    Controler_MainFrame  = 0x1001,
    Controler_WorkFrame  = 0x1002,
    Controler_ToolStatus = 0x1003,
};

typedef struct tagUISolution{
    double dW = 0.0;
    double dH = 0.0;
    double dOther = 0.0;
    QSize  szScreen;
    QSize  szBaseScreen;
    QRect  rcGeometry;
    QString strQssPath;
    QString strImagePath;
}stUISolution;

typedef struct tagGlobalVariant{
    QString strAppDirPath;
    QString strBinPath;
    QString strThemesPath;
    QString strConfigPath;
    QString strDataPath;
    QVector<stUISolution> vecUISolutions;
}stGlobalVariant;

#endif
