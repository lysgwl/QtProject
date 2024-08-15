#ifndef __TOP_MAINFRAME_CONTROLLER_H__
#define __TOP_MAINFRAME_CONTROLLER_H__

#include <internal.h>

class CTopMainFrameController : public IMgrController
{
private:
	QStackedWidget* m_stkWdg = Q_NULLPTR;
	QWidget* m_topFrameMain = Q_NULLPTR;
	
public:
    explicit CTopMainFrameController();
	~CTopMainFrameController();
	
public:
	// 注册对象
	void registerobj();

	// 初始化
	void init();
	
	//
	void exec();
};

#endif
