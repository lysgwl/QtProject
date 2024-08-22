#ifndef __TASK_STATUSBAR_CONTROLLER_H__
#define __TASK_STATUSBAR_CONTROLLER_H__

#include <IMgrController.h>
#include "../widget/TaskStatusBarView.h"

class CTaskStatusBarController : public IMgrController
{
private:
    CTaskStatusBarView *m_pTaskStatusBarView = Q_NULLPTR;
	
public:
	explicit CTaskStatusBarController();
	~CTaskStatusBarController();
	
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
	
    //void initUI(CToolStatusView *pToolStatusView);	
};

#endif
