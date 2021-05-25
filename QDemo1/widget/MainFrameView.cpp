#include "MainFrameView.h"

CMainFrameView::CMainFrameView(QWidget *parent)
	: QWidget(parent)
{
}

QStackedWidget* CMainFrameView::getStackedWidget() const
{
    return m_pStackedWidget;
}

void CMainFrameView::initUI()
{
	if (m_pStackedWidget == Q_NULLPTR)
	{
        m_pStackedWidget = new QStackedWidget(this);
		QVBoxLayout *pLayout = new QVBoxLayout();
		
		pLayout->addWidget(m_pStackedWidget);
		pLayout->setMargin(0);
		setLayout(pLayout);
		
		setWindowFlags(Qt::FramelessWindowHint);  //Qt::WindowStaysOnTopHint
        setFixedSize(800, 600); //resize
	}
}

void CMainFrameView::showMain()
{
    if (m_pStackedWidget == Q_NULLPTR)
    {
        return;
    }

    show();  //showMaximized //showFullScreen
}

void CMainFrameView::mouseReleaseEvent(QMouseEvent *event)
{
}

void CMainFrameView::mouseMoveEvent(QMouseEvent *event)
{
}
