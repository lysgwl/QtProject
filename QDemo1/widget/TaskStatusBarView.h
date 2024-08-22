#ifndef __TASK_STATUSBAR_VIEW_H__
#define __TASK_STATUSBAR_VIEW_H__

#include <IMgrView.h>

class CTaskStatusBarView : public QWidget, public IMgrView
{
	Q_OBJECT
private:
	QTimer *m_timer;

	QHBoxLayout *m_layoutMain = Q_NULLPTR;
	QHBoxLayout *m_layoutStatus = Q_NULLPTR;
	
protected:
	QLabel *m_lUserName;
	QLabel *m_lNumberName;
	
	QLabel *m_lLogoIcon;
	QLabel *m_lUserTime;
	
	QPushButton *m_btnLogout;
	QPushButton *m_btnTest;
	
public:
	explicit CTaskStatusBarView(QWidget *parent = nullptr);
	~CTaskStatusBarView();
	
public:
	void init() override;
    void exec() override;	
	
protected:
	void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
	
	void btnLogoutClicked();
    void btnTestClicked();
	
public slots:
	void setUserTimer();
	
signals:
};

#endif
