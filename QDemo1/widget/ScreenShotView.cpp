#include "ScreenShotView.h"

CScreenShotView::CScreenShotView(QWidget *parent)
	: QWidget(parent)
{
    m_pScreenImageLabel = nullptr;
}

void CScreenShotView::initUI()
{
    m_pScreenImageLabel = new QLabel(this);
    m_pScreenImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pScreenImageLabel->setAlignment(Qt::AlignCenter);
}

void CScreenShotView::resizeEvent(QResizeEvent *event)
{
}
