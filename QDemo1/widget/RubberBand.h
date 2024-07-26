#ifndef RUBBERBAND_H
#define RUBBERBAND_H

#include <QRubberBand>

class RubberBand : public QRubberBand
{
	Q_OBJECT
public:
	explicit RubberBand(Shape, QWidget *parent = nullptr);
	
	void  	setRect(QRect rect);
	QRect 	topLeftRect();
	QRect 	topRightRect();
	QRect 	bottomLeftRect();
	QRect 	bottomRightRect();
	
signals:

public slots:

protected:
	void	paintEvent(QPaintEvent *);
	
private:
	const QPoint m_pt;
	QRect 	m_rect;
};

#endif