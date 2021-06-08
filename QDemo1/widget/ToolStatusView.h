#ifndef TOOLSTATUS_VIEW_H
#define TOOLSTATUS_VIEW_H

#include <stHeader.h>

class CToolStatusView : public QWidget
{
	Q_OBJECT
public:
	explicit CToolStatusView(QWidget *parent = nullptr);
	
	void initUI();
	void showMain();
	
signals:

public slots:
    void slotInit(std::string s1);
    void setUserTimer();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

protected:
    void btnLogoutClicked();
    void btnTest1Clicked();

protected:
    void funcTest();
    void timerTest();
    void vsSdkTest();

protected:
	QLabel *m_lUserName;
	QLabel *m_lNumberName;
	
	QLabel *m_lLogoIcon;
	QLabel *m_lUserTime;
	
	QPushButton *m_btnLogout;
    QPushButton *m_btnTest1;
	
private:
	QTimer *m_timer;

	QHBoxLayout *m_layoutMain = Q_NULLPTR;
	QHBoxLayout *m_layoutStatus = Q_NULLPTR;
};

#endif
