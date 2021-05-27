#ifndef FRAME_STYLESHEET_H
#define FRAME_STYLESHEET_H

#include <stHeader.h>

class CFrameStyleSheet
{
public:
	CFrameStyleSheet();
	
public:
	void setStyleSheet(QWidget *parent, const QString &strFileName);

    void readStyleSheet(const QString &strFileName, QString &strQss, QString &strRss);
};

#endif
