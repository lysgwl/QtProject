#ifndef HOMEPAGE_VIEW_H
#define HOMEPAGE_VIEW_H

#include <stHeader.h>

class CHomePageView : public QWidget
{
	Q_OBJECT
public:
	explicit CHomePageView(QWidget *parent = nullptr);

	void initUI();
	void showHome();
	
signals:

private:	
};

#endif
