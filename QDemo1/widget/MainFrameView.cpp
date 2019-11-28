#include "MainFrameView.h"

CMainFrameView::CMainFrameView(QWidget *parent)
	: QWidget(parent)
{
}

void CMainFrameView::initUI()
{
    //QVBoxLayout *pLayout = new QVBoxLayout();

    //pLayout->addWidget(m_pStackedWidget);
    //pLayout->setMargin(0);

    //setLayout(pLayout);
    //setWindowFlags(Qt::FramelessWindowHint);  //Qt::WindowStaysOnTopHint
    //resize(500,400);
}

void CMainFrameView::showMain()
{
    m_pStackedWidget = new QStackedWidget();
    QPushButton *pButton1 = new QPushButton("test1", this);
    QPushButton *pButton2 = new QPushButton("test2", this);
    QPushButton *pButton3 = new QPushButton("test3", this);

    //pButton1->move(200, 200);
    //pButton2->move(200, 250);
    //pButton3->move(200, 300);

    m_pStackedWidget->addWidget(pButton1);
    m_pStackedWidget->addWidget(pButton2);
    m_pStackedWidget->addWidget(pButton3);

    m_pStackedWidget->resize(200, 300);

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->setMargin(5);
    pLayout->setSpacing(5);
    pLayout->addWidget(m_pStackedWidget, 0, 0);   //Qt::AlignVCenter  Qt::AlignHCenter
    pLayout->setStretchFactor(m_pStackedWidget, 4);

    showMaximized();
}

void CMainFrameView::mouseReleaseEvent(QMouseEvent *event)
{
}

void CMainFrameView::mouseMoveEvent(QMouseEvent *event)
{
}
