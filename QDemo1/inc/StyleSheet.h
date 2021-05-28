#ifndef STYLE_SHEET_H
#define STYLE_SHEET_H

#include <stHeader.h>

class CStyleSheet
{
public:
	CStyleSheet();
	
public:
    void setAppStyleSheet(const QString &strFileName);

	void setStyleSheet(QWidget *parent, const QString &strFileName);

    void readStyleSheet(const QString &strFileName, QString &strQss, QString &strRss);

private:
    stUISolution m_stSln;
    QMap<QString, std::tuple<QString, QString>> m_mapQss;
};

#endif
