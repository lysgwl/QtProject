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
	}
}

void CTopMainFrameController::exec()
{

}

CObject* CTopMainFrameController::getobject()
{
    return this;
}

QWidget* CTopMainFrameController::getview()
{
    return m_topFrameMain;
}
