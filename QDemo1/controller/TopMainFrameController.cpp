#include "TopMainFrameController.h"

#include <platform.h>

CTopMainFrameController::CTopMainFrameController()
{
}

CTopMainFrameController::~CTopMainFrameController()
{
}

void CTopMainFrameController::registerobj()
{
	REGISTER_OBJECT(CMainWindowController, new CMainWindowController);

    CMainWindowController* pMainWindow = GET_OBJECT_PTR(CMainWindowController);
    if (pMainWindow != nullptr)
    {
        pMainWindow->registerobj();
    }
}

void CTopMainFrameController::init()
{
	if (m_topFrameMain == Q_NULLPTR)
	{
		m_stkWdg = new QStackedWidget;
		
		QVBoxLayout *layoutMain = new QVBoxLayout;
		layoutMain->addWidget(m_stkWdg);
		layoutMain->setMargin(0);
		
		m_topFrameMain = new QWidget;
		m_topFrameMain->setLayout(layoutMain);
		m_topFrameMain->setWindowFlags(Qt::FramelessWindowHint/* | Qt::WindowStaysOnTopHint*/);
		m_topFrameMain->setFixedSize(800,600);

        CMainWindowController* pMainWindow = GET_OBJECT_PTR(CMainWindowController);
        if (pMainWindow != nullptr)
        {
            pMainWindow->init();
            m_pMainWindow = pMainWindow->getview();
        }

        m_stkWdg->addWidget(new QPushButton("test1"));
        m_stkWdg->addWidget(m_pMainWindow);
        m_stkWdg->addWidget(new QPushButton("test2"));

        // 设置初始显示的页面
        m_stkWdg->setCurrentIndex(0);
	}
}

void CTopMainFrameController::exec()
{
    if (m_topFrameMain != Q_NULLPTR)
    {
        // 获取所有屏幕
        QList<QScreen *> screens = QGuiApplication::screens();
        if (!screens.isEmpty())
        {
            // 获取主屏幕
            QScreen *screen = screens.first();

            // 获取屏幕的几何信息
            QRect screenGeometry = screen->geometry();

            // 计算居中位置
            int x = (screenGeometry.width() - m_topFrameMain->width()) / 2;
            int y = (screenGeometry.height() - m_topFrameMain->height()) / 2;

            // 设置窗口的位置和显示
            m_topFrameMain->move(x, y);
        }

        m_topFrameMain->showFullScreen();
    }
}

CObject* CTopMainFrameController::getobject()
{
    return this;
}

QWidget* CTopMainFrameController::getview()
{
    return m_topFrameMain;
}

//
void CTopMainFrameController::setcurrentview(QWidget* pWidget)
{
    if (m_stkWdg && pWidget)
    {
        m_stkWdg->setCurrentWidget(pWidget);
    }
}
