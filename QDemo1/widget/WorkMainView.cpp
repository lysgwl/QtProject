#include "WorkMainView.h"

CWorkMainView::CWorkMainView(QWidget *parent)
	: QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    //setFixedSize(640, 480); //resize
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background-color:rgb(199,237,204)");
}

QStackedWidget* CWorkMainView::getStackedWidget()
{
    return m_pStackedWidget;
}

CToolStatusView* CWorkMainView::getToolStatusView()
{
    return m_pToolStatusView;
}

void CWorkMainView::initUI()
{
    if (m_pStackedWidget == Q_NULLPTR)
    {
        m_pStackedWidget = new QStackedWidget(this);
        m_pToolStatusView = new CToolStatusView(this);
    }
}

void CWorkMainView::showMain()
{
}

void CWorkMainView::mouseReleaseEvent(QMouseEvent *event)
{
}

void CWorkMainView::mouseMoveEvent(QMouseEvent *event)
{
}
