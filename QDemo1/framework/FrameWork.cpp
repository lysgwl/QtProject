#include "FrameWork.h"

#include <platform.h>

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
    m_serviceLocator.addService(GET_IID(CObjectMgr), new CObjectMgr);
    m_serviceLocator.addService(GET_IID(CAppConfig), new CAppConfig);

    m_serviceLocator.getService(GET_IID(CAppConfig))->init();
}

// 初始化对象
void CFrameWork::init_object()
{
    REGISTER_OBJECT(CTopMainFrameController, new CTopMainFrameController);

    CTopMainFrameController* pController = GET_OBJECT_PTR(CTopMainFrameController);
    if (pController != nullptr)
    {
        pController->registerobj();
    }
}

// 初始化
void CFrameWork::init()
{
	// 初始化服务
	init_service();
	
	// 初始化对象
	init_object();
}

// 根据名称获取服务
IMgrService* CFrameWork::get_object_service(const QString& strServiceName)
{
	return m_serviceLocator.getService(strServiceName);
}
