#ifndef HOMEPAGE_CONTROL_H
#define HOMEPAGE_CONTROL_H

#include <stHeader.h>
#include "../widget/HomePageView.h"

class CHomePageControl : public QObject
{
	Q_OBJECT
public:
	explicit CHomePageControl(QObject *parent=Q_NULLPTR);
	
	QObject* getObject();
	
	QWidget* getWidget();
	
	void initHomePage();
	
	void updateHomePage();
	
public slots:

private:
	CHomePageView *m_pHomePageView = Q_NULLPTR;	
};

#endif
