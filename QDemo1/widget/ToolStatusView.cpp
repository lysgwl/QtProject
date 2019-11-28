#include "ToolStatusView.h"

CToolStatusView::CToolStatusView(QWidget *parent)
	: QWidget(parent)
{
}

void CToolStatusView::initUI()
{
    QPushButton *button1 = new QPushButton("One", this);
    QPushButton *button2 = new QPushButton("Two", this);
    QPushButton *button3 = new QPushButton("Three", this);
    QPushButton *button4 = new QPushButton("Four", this);
    QPushButton *button5 = new QPushButton("Five", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);
    layout->addWidget(button5);
    setLayout(layout);
}

void CToolStatusView::showTools()
{

}

void CToolStatusView::mouseReleaseEvent(QMouseEvent *event)
{
}

void CToolStatusView::mouseMoveEvent(QMouseEvent *event)
{
}
