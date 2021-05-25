#ifndef WORKMAIN_CONTROL_H
#define WORKMAIN_CONTROL_H

#include <QtWidgets>
#include "../widget/WorkMainView.h"

class CWorkMainControl : public QObject
{
	Q_OBJECT
public:
	explicit CWorkMainControl(QObject *parent=Q_NULLPTR);
	
	QObject* getObject();
	
	QWidget* getWidget();
	
	void initWorkFrame();
	
	void updateWorkFrame();
	
public slots:

private:
	CWorkMainView *m_pWorkView = Q_NULLPTR;
};

#endif