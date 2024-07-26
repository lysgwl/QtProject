#ifndef BOTTOMMENU_VIEW_H
#define BOTTOMMENU_VIEW_H

#include <stHeader.h>

class CBottomMenuView : public QWidget
{
	Q_OBJECT
public:
	explicit CBottomMenuView(QWidget *parent = nullptr);
	
	void initUI();
	void showMenu();
	
signals:

private:
     QHBoxLayout *m_layoutBar = Q_NULLPTR;
};

#endif
