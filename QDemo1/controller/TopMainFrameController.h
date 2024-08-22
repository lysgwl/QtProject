#ifndef __TOP_MAINFRAME_CONTROLLER_H__
#define __TOP_MAINFRAME_CONTROLLER_H__

#include <IMgrController.h>

class CTopMainFrameController : public IMgrController
{
private:
	QStackedWidget* m_stkWdg = Q_NULLPTR;
	QWidget* m_topFrameMain = Q_NULLPTR;
    QWidget* m_pMainWindow = Q_NULLPTR;
	
public:
    explicit CTopMainFrameController();
	~CTopMainFrameController();
	
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

    //
    void setcurrentview(QWidget* pWidget);
};

DECLARE_OBJ(CTopMainFrameController, "org.CTopMainFrameController.service")
#endif