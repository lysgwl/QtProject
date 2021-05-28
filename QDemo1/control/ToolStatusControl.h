#ifndef TOOLSTATUS_CONTROL_H
#define TOOLSTATUS_CONTROL_H

#include <stHeader.h>
#include "../widget/ToolStatusView.h"

class CToolStatusControl : public QObject
{
	Q_OBJECT
public:
	explicit CToolStatusControl(QObject *parent=Q_NULLPTR);
	
	QObject* getObject();
	
    void initUI(CToolStatusView *pToolStatusView);
	
signals:

private:
	CToolStatusView *m_pToolStatusView = Q_NULLPTR;
};

#endif
