#ifndef __ST_HEAD_H__
#define __ST_HEAD_H__

#include <map>
#include <tuple>

#include <string>
#include <sstream>
#include <iostream>

#include <utility>
#include <functional>

#include <QMap>
#include <QHash>

#include <QDir>
#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

#include <QtGui>
#include <QDebug>
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QLayout>
#include <QScreen>
#include <QMessageBox>
#include <QPushButton>
#include <QApplication>
#include <QDesktopWidget>
#include <QStackedWidget>
#include <QMouseEvent>

typedef struct tagUISolution {
    double dW = 0.0;
    double dH = 0.0;
    double dOther = 0.0;
    QSize  szScreen;
    QSize  szBaseScreen;
    QRect  rcGeometry;
    QString strQssPath;
    QString strImagePath;
}stUISolution;

typedef struct tagGlobalVariant {
    QString strAppDirPath;
    QString strBinPath;
    QString strThemesPath;
    QString strConfigPath;
    QString strDataPath;
    QString strFontPath;
    QString strSoundPath;
    QVector<stUISolution> vecUISolutions;
}stGlobalVariant;

#endif
