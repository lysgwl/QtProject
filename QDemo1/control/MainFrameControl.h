#ifndef __MAINFRAME_CONTROL_H__
#define __MAINFRAME_CONTROL_H__

#include <QtWidgets>
#include <QStackedWidget>

#include "../widget/MainFrameView.h"

class CMainFrameControl : public QObject
{
	Q_OBJECT
public:
	explicit CMainFrameControl(QObject *parent=Q_NULLPTR);
	
    void		initMainFrame();
	
    QWidget*	getMainFrame();

public slots:

protected:
	
private:
	QStackedWidget	*m_pStackedWidget;
	CMainFrameView	*m_pMainView;
};

#endif
