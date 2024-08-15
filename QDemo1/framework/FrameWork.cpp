#include "FrameWork.h"

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

// 初始化服务
void CFrameWork::init_service()
{
    m_serviceLocator.addService("objectMgr", new CObjectMgr);
    m_serviceLocator.addService("globalvar", new CAppConfig);

    m_serviceLocator.getService("globalvar")->init();
}

// 初始化对象
void CFrameWork::init_object()
{
	m_serviceLocator.getService("objectMgr")->addObject("topMainController", new CTopMainFrameController);
}

// 初始化
void CFrameWork::init()
{
	// 初始化服务
	init_service();
	
	// 初始化对象
	init_object();
}

