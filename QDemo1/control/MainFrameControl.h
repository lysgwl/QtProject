#ifndef MAINFRAME_CONTROL_H
#define MAINFRAME_CONTROL_H

#include <QStackedWidget>
#include "../widget/MainFrameView.h"

class CMainFrameControl : public QObject
{
    Q_OBJECT
public:
    explicit CMainFrameControl(QObject *parent=Q_NULLPTR);

    QObject* getObject();

    QWidget* getWidget();
	
    void initMainFrame();
	
    void updateMainFrame();
	
public slots:

private:
    CMainFrameView *m_pMainView = Q_NULLPTR;
};

#endif
