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

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

protected:
	void setUserTimer();
    void btnLogoutClicked();

protected:
	QLabel *m_lUserName;
	QLabel *m_lNumberName;
	
	QLabel *m_lLogoIcon;
	QLabel *m_lUserTime;
	
	QPushButton *m_btnLogout;
	
private:
	QTimer *m_timer;
	QHBoxLayout *m_layoutMain = Q_NULLPTR;
	QHBoxLayout *m_layoutStatus = Q_NULLPTR;
};

#endif
