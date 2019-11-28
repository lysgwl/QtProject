#ifndef __TOOLSTATUS_VIEW_H__
#define __TOOLSTATUS_VIEW_H__

#include <QtWidgets>

class CToolStatusView : public QWidget
{
	Q_OBJECT
public:
	explicit CToolStatusView(QWidget *parent = nullptr);
	
	void                initUI();
	void				showTools();
	
protected:
    void                mouseReleaseEvent(QMouseEvent *event) override;
    void                mouseMoveEvent(QMouseEvent *event) override;

signals:	
};

#endif
