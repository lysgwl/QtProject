#ifndef __OBJECT_HEADER_H__
#define __OBJECT_HEADER_H__

#include "stheader.h"

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
    QVector<stUISolution> vecUISolutions;
}stGlobalVariant;

#define GET_DECLARE_OBJ(IFace, IID) template <> inline const char * get_obj_iid<IFace*>() { return IID; }
#define GET_IID(IFace) (get_obj_iid<IFace*>())

//#define ADD_OBJECT_CLASS 
#endif
