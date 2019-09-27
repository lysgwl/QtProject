#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>

class ImageView : public QGraphicsView
{
public:
    ImageView(QWidget* parent = nullptr);

public:
    void    showImage(const QPixmap &pixmap);
    bool    isSelectRect();

    void    zoomIn();
    void    zoomOut();
    void    resetZoom();
    void    fitToView();

protected:
    //virtual void mousePressEvent(QMouseEvent* event);
    //virtual void mouseReleaseEvent(QMouseEvent* event);
    //virtual void mouseMoveEvent(QMouseEvent* event);
    //virtual void wheelEvent(QWheelEvent* event);
    //virtual void resizeEvent(QResizeEvent* event);
};

#endif // IMAGEVIEW_H
