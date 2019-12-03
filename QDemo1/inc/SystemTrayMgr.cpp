#include "SystemTrayMgr.h"

#include <QMenu>

CSystemTrayMgr::CSystemTrayMgr(QWidget *pParent)
    : QWidget(pParent)
{
    m_pSystemTray = nullptr;
}

void CSystemTrayMgr::initTray()
{
    if (m_pSystemTray == nullptr)
    {
        m_pSystemTray = new QSystemTrayIcon(this);
    }

    QMenu *pTrayMenu = new QMenu(this);
    if (pTrayMenu != nullptr)
    {
        QAction *pMinAction = new QAction(tr("Mi&nimize"), this);
        pTrayMenu->addAction(pMinAction);

        QAction *pMaxAction = new QAction(tr("Ma&ximize"), this);
        pTrayMenu->addAction(pMaxAction);

        QAction *pRestoreAction = new QAction(tr("&Restore"), this);
        pTrayMenu->addAction(pRestoreAction);

        pTrayMenu->addSeparator();

        QAction *pQuitAction = new QAction(tr("&Quit"), this);
        pTrayMenu->addAction(pQuitAction);
    }

    connect(m_pSystemTray, &QSystemTrayIcon::activated, this, &CSystemTrayMgr::activated);

    m_pSystemTray->setContextMenu(pTrayMenu);
}

void CSystemTrayMgr::setTrayIcon(const QIcon &icon)
{
    if (m_pSystemTray == nullptr || icon.isNull())
        return;

    m_pSystemTray->setIcon(icon);
    setWindowIcon(icon);
}

void CSystemTrayMgr::showTrayMessage(const QString &strTitle, const QString &strMsg)
{
    if (m_pSystemTray == nullptr || strMsg.isEmpty())
        return;

    QIcon icon = m_pSystemTray->icon();
    m_pSystemTray->showMessage(strTitle, strMsg, icon);
}

void CSystemTrayMgr::activated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        break;

    case QSystemTrayIcon::MiddleClick:
        break;

    default:
        break;
    }
}
