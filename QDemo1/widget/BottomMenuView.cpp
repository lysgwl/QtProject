#include "BottomMenuView.h"

CBottomMenuView::CBottomMenuView(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
}

void CBottomMenuView::initUI()
{
    if (m_layoutBar == Q_NULLPTR)
    {
        m_layoutBar = new QHBoxLayout();
        m_layoutBar->setContentsMargins(15,0,15,0);
        m_layoutBar->setSpacing(10);
        m_layoutBar->setAlignment(Qt::AlignCenter);
    }

    this->setLayout(m_layoutBar);
}

void CBottomMenuView::showMenu()
{

}
