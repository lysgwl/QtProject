#ifndef __MAIN_WINDOW_CONTROLLER_H__
#define __MAIN_WINDOW_CONTROLLER_H__

#include <IMgrController.h>
#include "../widget/MainWindowView.h"

class CMainWindowController : public IMgrController
{
private:
    CMainWindowView *m_pMainWindowView = Q_NULLPTR;
	
public:
	explicit CMainWindowController();
	~CMainWindowController();
	
public:	
	// 注册对象
	void registerobj();
	
	// 初始化
	void init();
	
	// 执行
	void exec();

    // 获取对象
    CObject* getobject();

    // 获取视图
    QWidget* getview();
};

DECLARE_OBJ(CMainWindowController, "org.CMainWindowControllers.service")
#endif
