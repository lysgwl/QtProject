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
#include <QMessageBox>
#include <QPushButton>
#include <QApplication>
#include <QStackedWidget>

enum ControlerHandler {
    Controler_HomePage   = 0x1000,
    Controler_MainFrame  = 0x1001,
    Controler_WorkFrame  = 0x1002,
    Controler_ToolStatus = 0x1003,
};

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

class CObject : public QObject
{
public:
    CObject() {};
    virtual ~CObject() {};
};

template <class T> inline const char * get_obj_iid() { return nullptr; }
#define GET_DECLARE_OBJ(IFace, IID) template <> inline const char * get_obj_iid<IFace*>() { return IID; }
#define GET_IID(IFace) (get_obj_iid<IFace*>())


#endif
