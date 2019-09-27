#include "imageview.h"

ImageView::ImageView(QWidget* parent)
    : QGraphicsView(parent)
{
    setBackgroundRole(QPalette::Dark); //设置背景颜色
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setScene(new QGraphicsScene(this));
    setSceneRect(0, 0, rect().width(), rect().height());
    //setCenterPoint(QPointF(rect().width()/2, rect().height()/2));
    setCursor(Qt::OpenHandCursor);

    setMouseTracking(true);
}

void ImageView::showImage(const QPixmap &pixmap)
{}

bool ImageView::isSelectRect()
{}

void ImageView::zoomIn()
{}

void ImageView::zoomOut()
{}

void ImageView::resetZoom()
{}

void ImageView::fitToView()
{}
