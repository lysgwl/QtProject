#ifndef WORKMAIN_VIEW_H
#define WORKMAIN_VIEW_H

#include <QtWidgets>
#include "../widget/ToolStatusView.h"

class CWorkMainView : public QWidget
{
	Q_OBJECT
public:
	explicit CWorkMainView(QWidget *parent = nullptr);

    QStackedWidget* getStackedWidget();

    CToolStatusView* getToolStatusView();
	
	void initUI();
	void showMain();	
	
protected:
	void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:

private:
    QStackedWidget *m_pStackedWidget = Q_NULLPTR;
    CToolStatusView *m_pToolStatusView = Q_NULLPTR;
};

#endif