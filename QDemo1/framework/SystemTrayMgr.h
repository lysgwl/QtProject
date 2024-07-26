#ifndef __SYSTEMTRAY_MGR_H__
#define __SYSTEMTRAY_MGR_H__

#include <QWidget>
#include <QSystemTrayIcon>

class CSystemTrayMgr : public QWidget
{
public:
	explicit CSystemTrayMgr(QWidget *pParent = nullptr);
	
public:
	void	initTray();

    void    setTrayIcon(const QIcon &icon);
    void    showTrayMessage(const QString &strTitle, const QString &strMsg);

private slots:
    void    activated(QSystemTrayIcon::ActivationReason reason);

protected:
    QSystemTrayIcon *m_pSystemTray;
};

#endif
