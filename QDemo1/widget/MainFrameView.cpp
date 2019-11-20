#include "MainFrameView.h"

CMainFrameView::CMainFrameView(QWidget *parent)
	: QWidget(parent)
{
}

void CMainFrameView::initUI()
{
/*
    QPushButton *button1 = new QPushButton("One");
    QPushButton *button2 = new QPushButton("Two");
    QPushButton *button3 = new QPushButton("Three");
    QPushButton *button4 = new QPushButton("Four");
    QPushButton *button5 = new QPushButton("Five");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);
    layout->addWidget(button5);
    setLayout(layout);
*/
    QMenu *fileMenu;
    fileMenu = new QMenu(tr("File(&F)"), this);

    QAction *openAction = new QAction(tr("Open(&O)..."), this);
}

void CMainFrameView::mouseReleaseEvent(QMouseEvent *event)
{
}

void CMainFrameView::mouseMoveEvent(QMouseEvent *event)
{
}
