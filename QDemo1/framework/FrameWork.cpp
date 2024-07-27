#include "FrameWork.h"

#include "ObjectMgr.h"

CFrameWork::CFrameWork()
{
}

CFrameWork::~CFrameWork()
{
}

CFrameWork& CFrameWork::GetInstance()
{
    static CFrameWork instance;
    return instance;
}

// 初始化全局环境
void CFrameWork::init_global_env()
{
	int iIndex = QApplication::applicationDirPath().lastIndexOf ("/");
	m_stGlobalVariant.strAppDirPath = QApplication::applicationDirPath();
	m_stGlobalVariant.strBinPath = QApplication::applicationDirPath().left(iIndex);
	m_stGlobalVariant.strThemesPath = m_stGlobalVariant.strBinPath  + "/themes";
	m_stGlobalVariant.strConfigPath = m_stGlobalVariant.strBinPath  + "/config";
	m_stGlobalVariant.strDataPath = m_stGlobalVariant.strBinPath  + "/data";
	
	//CGenUtils::mkdir(m_stGlobalVariant.strThemesPath);
    //CGenUtils::mkdir(m_stGlobalVariant.strConfigPath);
    //CGenUtils::mkdir(m_stGlobalVariant.strDataPath);
}

// 初始化服务
void CFrameWork::init_service()
{
	m_serviceLocator.addService("objectMgr", new CObjectMgr);
}

// 初始化
void CFrameWork::init()
{
	// 初始化全局环境
	init_global_env();
	
	// 初始化服务
	init_service();
}

// 获取全局变量
stGlobalVariant* CFrameWork::get_global_variant()
{
    return &m_stGlobalVariant;
}