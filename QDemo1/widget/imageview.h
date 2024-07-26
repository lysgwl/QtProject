#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>

class QRubberBand;
class ImageView : public QGraphicsView
{
	Q_OBJECT
public:
    ImageView(QWidget* parent = nullptr);

public:
    void    showImage(const QPixmap &pixmap);
    bool    isSelectRect();

    void    zoomIn();
    void    zoomOut();
    void    resetZoom();
    void    fitToView();

public slots:
    void    setMoveImageState(bool state);

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void resizeEvent(QResizeEvent* event);

    void    setCenterPoint(const QPointF &centerPoint);

protected:
    QPoint  origin;
    QPoint  lastPoint;

    QPointF curCenterPoint;

private:
    bool    isMousePress;
    bool    isMoveImageWithCurrentState;

    QRubberBand *rubberBand;
};

#endif // IMAGEVIEW_H
