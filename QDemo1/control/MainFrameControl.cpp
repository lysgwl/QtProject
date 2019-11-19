#include "MainFrameControl.h"


CMainFrameControl::CMainFrameControl(QObject *parent) 
		: QObject(parent)
{
    m_pMainView = nullptr;
    m_pStackedWidget = nullptr;
}

void CMainFrameControl::initMainFrame()
{
	if (m_pMainView == nullptr)
	{
		m_pMainView = new CMainFrameView();
		m_pStackedWidget = new QStackedWidget(); 
		
		QVBoxLayout *pLayout = new QVBoxLayout();
		pLayout->addWidget(m_pStackedWidget);
		pLayout->setMargin(0);
		
        //setMainWindow(m_pMainView);
		m_pMainView->initUI();
	}
}

QWidget* CMainFrameControl::getMainFrame()
{
    return m_pMainView;
}
