#ifndef __MAINFRAME_VIEW_H__
#define __MAINFRAME_VIEW_H__

#include <QtWidgets>

class CMainFrameView : public QWidget
{
	Q_OBJECT
public:
	explicit CMainFrameView(QWidget *parent = nullptr);	
	
	void		initUI();
	
protected:
	void		mouseReleaseEvent(QMouseEvent *event) override;
	void        mouseMoveEvent(QMouseEvent *event) override;
	
signals:
		
};

#endif // MAINWINDOW_H
