#include "RubberBand.h"

#include <QtGui>

RubberBand::RubberBand(Shape shape, QWidget *parent)
	: QRubberBand(shape, parent), m_pt(4, 4)
{
}

void RubberBand::setRect(QRect rect)
{
	m_rect = rect;
}

QRect RubberBand::topLeftRect()
{
	QPoint ptTopLeft = m_rect.topLeft();
	return QRect(ptTopLeft-m_pt, ptTopLeft+m_pt);
}

QRect RubberBand::topRightRect()
{
	QPoint ptTopRight = m_rect.topRight();
    return QRect(ptTopRight-m_pt, ptTopRight+m_pt);
}

QRect RubberBand::bottomLeftRect()
{
	QPoint ptBottomLeft = m_rect.bottomLeft();
    return QRect(ptBottomLeft-m_pt, ptBottomLeft+m_pt);
}

QRect RubberBand::bottomRightRect()
{
	QPoint ptBottomRight = m_rect.bottomRight();
    return QRect(ptBottomRight-m_pt, ptBottomRight+m_pt);
}

void RubberBand::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);	//没有实质性的作用，用来避免编译器警告
    //QApplication::processEvents();	//让程序处理那些还没有处理的事件，然后再把使用权返回给调用者
	
	QPainter painter;
    QPen pen = QPen(Qt::white);
	pen.setWidth(2);
    pen.setStyle(Qt::DashLine);
	
	painter.begin(this);
    painter.setPen(pen);
    painter.setOpacity(0.7);
    //painter.setBrush(brush);
    painter.drawRect(event->rect());
    painter.end();
}
