#include "MainFrameView.h"

CMainFrameView::CMainFrameView(QWidget *parent)
	: QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);  //Qt::WindowStaysOnTopHint
    setFixedSize(640, 480); //resize
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
        this->setLayout(pLayout);
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

void CMainFrameView::closeEvent(QCloseEvent*event)
{
    //QString::fromLocal8Bit
    auto temp = QMessageBox::information(this, tr("提示！"), tr("你是否要关闭?"), QMessageBox::Yes | QMessageBox::No);
    if (temp == QMessageBox::Yes)
    {
        qApp->quit();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
