#include "FrameWork.h"

#include <internal.h>

CFrameWork::CFrameWork()
{
}

CFrameWork& CFrameWork::getFrameWork()
{
    static CFrameWork frameWork;
    return frameWork;
}

ObjectMgr* CFrameWork::getObjectMgr()
{
    return &m_objectMgr;
}

void* CFrameWork::getObjectPointer(uint uiId)
{
   return m_objectMgr.getObject(uiId);
}

stGlobalVariant* CFrameWork::getGlobalVariant()
{
    return &m_stGlobalVariant;
}

void CFrameWork::initGlobalEnv()
{
    int iIndex = QApplication::applicationDirPath().lastIndexOf ("/");
    m_stGlobalVariant.strAppDirPath = QApplication::applicationDirPath();
    m_stGlobalVariant.strBinPath = QApplication::applicationDirPath().left(iIndex);
    m_stGlobalVariant.strThemesPath = m_stGlobalVariant.strBinPath  + "/themes";
    m_stGlobalVariant.strConfigPath = m_stGlobalVariant.strBinPath  + "/config";
    m_stGlobalVariant.strDataPath = m_stGlobalVariant.strBinPath  + "/data";

    CGenUtils::mkdir(m_stGlobalVariant.strThemesPath);
    CGenUtils::mkdir(m_stGlobalVariant.strConfigPath);
    CGenUtils::mkdir(m_stGlobalVariant.strDataPath);

    stGlobalVariant *pGlobalVariant = &m_stGlobalVariant;
    auto lamdaScale = [pGlobalVariant](stUISolution &uiSln) {
        int nBaseWidth = uiSln.szBaseScreen.width();
        int nBaseHeight = uiSln.szBaseScreen.height();

        uiSln.dW = uiSln.szScreen.width()/double(nBaseWidth);
        uiSln.dH = uiSln.szScreen.height()/double(nBaseHeight);
        uiSln.dOther = qMin(uiSln.dW, uiSln.dH);

        pGlobalVariant->vecUISolutions.append(uiSln);
    };

    stUISolution uiSln;
    uiSln.szScreen = QSize(1280, 800);
    uiSln.szBaseScreen = QSize(1280, 800);
    uiSln.strQssPath = m_stGlobalVariant.strThemesPath + "/qss";
    uiSln.strImagePath = m_stGlobalVariant.strThemesPath + "/image";
    lamdaScale(uiSln);
}

void CFrameWork::setStyleSheet(QWidget *parent, QString strFileName)
{
    CStyleSheet styleSheet;
    styleSheet.setStyleSheet(parent, strFileName);
}
