#include "MainWindowView.h"

CMainWindowView::CMainWindowView(QWidget *parent)
	: QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);  //Qt::WindowStaysOnTopHint
    setFixedSize(640, 480); //resize
}

CMainWindowView::~CMainWindowView()
{
}

void CMainWindowView::init()
{
	if (m_pStackedWidget == Q_NULLPTR)
	{
        m_pStackedWidget = new QStackedWidget(this);
		QVBoxLayout *pLayout = new QVBoxLayout();
		
		pLayout->addWidget(m_pStackedWidget);
		pLayout->setMargin(0);
        this->setLayout(pLayout);
	}
}

void CMainWindowView::exec()
{
    show();  //showMaximized //showFullScreen
}

void CMainWindowView::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void CMainWindowView::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}
