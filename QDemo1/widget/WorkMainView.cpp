#include "WorkMainView.h"

CWorkMainView::CWorkMainView(QWidget *parent)
	: QWidget(parent)
{
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

        setWindowFlags(Qt::FramelessWindowHint);
        //setFixedSize(500, 400); //resize
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
