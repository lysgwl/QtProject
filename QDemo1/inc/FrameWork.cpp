#include "FrameWork.h"

CFrameWork::CFrameWork()
{
}

CFrameWork* CFrameWork::getFrameWork()
{
    static CFrameWork frameWork;
    return &frameWork;
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
    m_stGlobalVariant.strThemesPath = m_stGlobalVariant.strBinPath  + "/Themes";
    m_stGlobalVariant.strConfigPath = m_stGlobalVariant.strBinPath  + "/config";
    m_stGlobalVariant.strDataPath = m_stGlobalVariant.strBinPath  + "/data";
}
