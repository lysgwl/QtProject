#include "imageview.h"

ImageView::ImageView(QWidget* parent)
    : QGraphicsView(parent)
{
    setBackgroundRole(QPalette::Dark); 	//设置背景颜色
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);	//Antialiasing:抗锯齿绘制	SmoothPixmapTransform:使用平滑的pixmap变换算法

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);	//关闭水平滚动条
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);		//关闭垂直滚动条

    setScene(new QGraphicsScene(this));	//设置场景	
    setSceneRect(0, 0, rect().width(), rect().height());	//设置场景的范围	
    //setCenterPoint(QPointF(rect().width()/2, rect().height()/2));
    setCursor(Qt::OpenHandCursor);		//改变鼠标形状

    setMouseTracking(true);
}

void ImageView::showImage(const QPixmap &pixmap)
{
	scene()->clear();
	scene()->addPixmap(pixmap);
	setSceneRect(pixmap.rect());
}

bool ImageView::isSelectRect()
{}

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

//////////////////////////////////////////////////////////////////////////
//
void ImageView::mousePressEvent(QMouseEvent* event)
{
}

void ImageView::mouseReleaseEvent(QMouseEvent* event)
{
}

void ImageView::mouseMoveEvent(QMouseEvent* event)
{
}

void ImageView::wheelEvent(QWheelEvent* event)
{
}

void ImageView::resizeEvent(QResizeEvent* event)
{
}