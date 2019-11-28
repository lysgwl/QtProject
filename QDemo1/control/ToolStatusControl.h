#ifndef __TOOLSTATUS_CONTROL_H__
#define __TOOLSTATUS_CONTROL_H__

#include <QtWidgets>

class CToolStatusControl : public QObject
{
	Q_OBJECT
public:
	explicit CToolStatusControl(QObject *parent=Q_NULLPTR);
	
	void                initToolStatus();
	
	QObject*			getObject();
};

#endif
