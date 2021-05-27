#ifndef MAINFRAME_VIEW_H
#define MAINFRAME_VIEW_H

#include <stHeader.h>

class CMainFrameView : public QWidget
{
	Q_OBJECT
public:
    explicit CMainFrameView(QWidget *parent = nullptr);

    QStackedWidget* getStackedWidget() const;
	
    void initUI();
    void showMain();

protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:

protected:
    QStackedWidget *m_pStackedWidget = Q_NULLPTR;
};

#endif // MAINWINDOW_H
