#include "WorkMainView.h"

CWorkMainView::CWorkMainView(QWidget *parent)
	: QWidget(parent)
{
}

QStackedWidget* CWorkMainView::getStackedWidget()
{
    return Q_NULLPTR;//m_pStackedWidget;
}

void CWorkMainView::initUI()
{
    //if (m_pStackedWidget == Q_NULLPTR)
    {
        //m_pStackedWidget = new QStackedWidget();

        //setWindowFlags(Qt::FramelessWindowHint);
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
