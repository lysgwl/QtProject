#ifndef WORKMAIN_VIEW_H
#define WORKMAIN_VIEW_H

#include <stHeader.h>
#include "../widget/ToolStatusView.h"
#include "../widget/BottomMenuView.h"

class CWorkMainView : public QWidget
{
	Q_OBJECT
public:
	explicit CWorkMainView(QWidget *parent = nullptr);

    QStackedWidget* getStackedWidget();

    CToolStatusView* getToolStatusView();

    CBottomMenuView* getButtomMenuView();
	
	void initUI();
	void showMain();	
	
protected:
	void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:

protected:
	CToolStatusView *m_pToolStatusView = Q_NULLPTR;
	CBottomMenuView *m_pBottomMenuView = Q_NULLPTR;
	
private:
    QStackedWidget *m_pStackedWidget = Q_NULLPTR;
};

#endif
