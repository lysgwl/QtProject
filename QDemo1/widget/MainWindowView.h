#ifndef __MAIN_WINDOW_VIEW_H__
#define __MAIN_WINDOW_VIEW_H__

#include <IMgrView.h>

class CMainWindowView : public QWidget, public IMgrView
{
	Q_OBJECT
private:
    QStackedWidget *m_pStackedWidget;

public:
	explicit CMainWindowView(QWidget *parent = nullptr);
	~CMainWindowView();
	
public:
    void init() override;
    void exec() override;

protected:
	void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
 
};

#endif
