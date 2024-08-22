#include "MainWindowView.h"

CMainWindowView::CMainWindowView(QWidget *parent)
	: QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);  //Qt::WindowStaysOnTopHint
    setFixedSize(800, 600); //resize

    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color:rgb(150,130,80)");
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
