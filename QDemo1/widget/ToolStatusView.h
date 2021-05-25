#ifndef TOOLSTATUS_VIEW_H
#define TOOLSTATUS_VIEW_H

#include <QtWidgets>

class CToolStatusView : public QWidget
{
	Q_OBJECT
public:
	explicit CToolStatusView(QWidget *parent = nullptr);
	
	void initUI();
	void showMain();
	
protected:
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

signals:
};

#endif
