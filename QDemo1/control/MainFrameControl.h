#ifndef __MAINFRAME_CONTROL_H__
#define __MAINFRAME_CONTROL_H__

#include <QtWidgets>
#include <QStackedWidget>

class CMainFrameControl : public QObject
{
	Q_OBJECT
public:
	explicit CMainFrameControl(QObject *parent=Q_NULLPTR);
	
    void		initMainFrame();
	
    QObject*    getObject();

public slots:
};

#endif
