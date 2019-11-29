#include "MainFrameView.h"

CMainFrameView::CMainFrameView(QWidget *parent)
	: QWidget(parent)
{
}

void CMainFrameView::initUI()
{
    m_pStackedWidget = new QStackedWidget();
    //QVBoxLayout *pLayout = new QVBoxLayout();

    //pLayout->addWidget(m_pStackedWidget);
    //pLayout->setMargin(0);

    //setLayout(pLayout);
    //setWindowFlags(Qt::FramelessWindowHint);  //Qt::WindowStaysOnTopHint
    //resize(500,400);
}

void CMainFrameView::showMain()
{
    QLabel *screenshotLabel = new QLabel(this);

    screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    screenshotLabel->setAlignment(Qt::AlignCenter);

   // const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
   // screenshotLabel->setMinimumSize(screenGeometry.width() / 8, screenGeometry.height() / 8);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(screenshotLabel);

    //QSpinBox *delaySpinBox;
    //QGroupBox *optionsGroupBox = new QGroupBox(tr("Options"), this);
    //delaySpinBox = new QSpinBox(optionsGroupBox);
    //delaySpinBox->setSuffix(tr(" s"));
    //delaySpinBox->setMaximum(60);

    //mainLayout->addWidget(optionsGroupBox);
    //showMaximized();
    show();
}

void CMainFrameView::mouseReleaseEvent(QMouseEvent *event)
{
}

void CMainFrameView::mouseMoveEvent(QMouseEvent *event)
{
}
