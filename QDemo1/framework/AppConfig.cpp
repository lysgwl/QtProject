#include "AppConfig.h"

#include "GenUtils.h"

CAppConfig::CAppConfig()
{
}

CAppConfig::~CAppConfig()
{
}

void CAppConfig::init()
{
    int iIndex = QApplication::applicationDirPath().lastIndexOf ("/");

    // 获取当前应用程序的目录
    strAppDirPath=QApplication::applicationDirPath();

    // 获取应用程序的 bin 目录
    strBinPath = QApplication::applicationDirPath().left(iIndex);

    // 获取bin目录下的 themes 目录
    strThemesPath = strBinPath  + "/themes";

    // 获取bin目录下的 config 目录
    strConfigPath = strBinPath  + "/config";

    // 获取bin目录下的 data 目录
    strDataPath = strBinPath  + "/data";
}

void CAppConfig::exec()
{
	// 创建 themes 目录
    CGenUtils::GetInstance().mkdir(strThemesPath);
	
	// 创建 config 目录
    CGenUtils::GetInstance().mkdir(strConfigPath);
	
	// 创建 data 目录
    CGenUtils::GetInstance().mkdir(strDataPath);
}
