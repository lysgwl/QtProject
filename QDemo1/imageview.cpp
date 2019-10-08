#include "imageview.h"

#include <QtGui>
#include <QRubberBand>

ImageView::ImageView(QWidget* parent)
    : QGraphicsView(parent)
{
    isMousePress = false;
    isMoveImageWithCurrentState = true;

    setBackgroundRole(QPalette::Dark); 	//设置背景颜色
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);	//Antialiasing:抗锯齿绘制	SmoothPixmapTransform:使用平滑的pixmap变换算法

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	//关闭水平滚动条
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);		//关闭垂直滚动条

    setScene(new QGraphicsScene(this));	//设置场景	
    setSceneRect(0, 0, rect().width(), rect().height());	//设置场景的范围	
    //setCenterPoint(QPointF(rect().width()/2, rect().height()/2));
    setCursor(Qt::OpenHandCursor);		//改变鼠标形状

    setMouseTracking(true);
    rubberBand = nullptr;
}

void ImageView::showImage(const QPixmap &pixmap)
{
	scene()->clear();
	scene()->addPixmap(pixmap);
	setSceneRect(pixmap.rect());
}

bool ImageView::isSelectRect()
{
    if (rubberBand)
    {

    }

    return false;
}

void ImageView::zoomIn()
{
	double scaleFactor = 1.15;
	scale(scaleFactor, scaleFactor);
}

void ImageView::zoomOut()
{
	double scaleFactor = 1.15;
	scale(1.0/scaleFactor, 1.0/scaleFactor);
}

void ImageView::resetZoom()
{
	resetCachedContent();
	resetMatrix();
	resetTransform();
}

void ImageView::fitToView()
{
	fitInView(0, 0, scene()->width(), scene()->height());
}

void ImageView::setMoveImageState(bool state)
{
    isMoveImageWithCurrentState = state;

    if (state)
    {
        setCursor(Qt::OpenHandCursor);
    }
    else
    {
        setCursor(Qt::CrossCursor);
    }
}

//////////////////////////////////////////////////////////////////////////
//
void ImageView::mousePressEvent(QMouseEvent* event)
{
    isMousePress = true;

    if (isMoveImageWithCurrentState)
    {
        lastPoint = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    else
    {
        origin = event->pos();

        if (!rubberBand)
        {
            rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        }

        rubberBand->setGeometry(QRect(origin, QSize()));
        rubberBand->show();
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent* event)
{
    isMousePress = false;

    if (isMoveImageWithCurrentState)
    {
        setCursor(Qt::OpenHandCursor);
        lastPoint = QPoint();
    }
    else
    {
        if (rubberBand)
        {
            QRect selectedRect = QRect(origin, event->pos()).normalized();  //
            QRectF selectedRectF = mapToScene(QRect(selectedRect.topLeft(), selectedRect.bottomRight())).boundingRect();    //

            int selectedRectWidth = selectedRectF.width();
            int selectedRectHeight = selectedRectF.height();

            QPixmap outputImage(selectedRectWidth, selectedRectHeight); //

            QPainter outputPainter(&outputImage);
            outputPainter.fillRect(outputImage.rect(), Qt::white);

            QRectF targetRect(0, 0, selectedRectWidth, selectedRectHeight);
            render(&outputPainter, targetRect, selectedRect);
            //outputImage.save(m_selectedRectImageFilename, "JPG");

            outputPainter.end();
        }
    }
}

void ImageView::mouseMoveEvent(QMouseEvent* event)
{
    if (isMoveImageWithCurrentState)
    {
        if (!lastPoint.isNull())
        {
            QPointF delta = mapToScene(lastPoint) - mapToScene(event->pos());   //
            lastPoint = event->pos();

            //setCenterPoint(centerPoint() + delta);
        }
    }
    else
    {
        if (isMousePress && rubberBand)
        {
            rubberBand->setGeometry(QRect(origin, event->pos()).normalized());  //
        }
    }
}

void ImageView::wheelEvent(QWheelEvent* event)
{
    QPointF pointBeforeScale(mapToScene(event->pos()));

    //QPointF screenCenter = centerPoint(); //CurrentCenterPoint;

    if(event->delta() > 0)
    {
        zoomIn();
    }
    else
    {
        zoomOut();
    }
}

void ImageView::resizeEvent(QResizeEvent* event)
{
    QRectF visibleArea = mapToScene(rect()).boundingRect();
    //setCenterPoint(visibleArea.center());

    QGraphicsView::resizeEvent(event);
}
