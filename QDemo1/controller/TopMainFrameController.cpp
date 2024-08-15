#include "TopMainFrameController.h"

CTopMainFrameController::CTopMainFrameController()
{
}

CTopMainFrameController::~CTopMainFrameController()
{
}

void CTopMainFrameController::registerObj()
{
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
	}
}

void CTopMainFrameController::exec()
{
}