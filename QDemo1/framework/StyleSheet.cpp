#include "StyleSheet.h"

#include <internal.h>

CStyleSheet::CStyleSheet()
{
    m_stSln = CFrameWork::getFrameWork().getGlobalVariant()->vecUISolutions.first();
}

void CStyleSheet::setAppStyleSheet(const QString &strFileName)
{
    QString strQss;
    QString strRss;

    if (m_mapQss.contains(strFileName))
    {
        strQss = std::get<0>(m_mapQss[strFileName]);
        strRss = std::get<1>(m_mapQss[strFileName]);
    }
    else
    {
        readStyleSheet(strFileName, strQss, strRss);
    }

    qApp->setStyleSheet(strQss);
}

void CStyleSheet::setStyleSheet(QWidget *parent, const QString &strFileName)
{
    QString strQss;
    QString strRss;

    if (m_mapQss.contains(strFileName))
    {
        strQss = std::get<0>(m_mapQss[strFileName]);
        strRss = std::get<1>(m_mapQss[strFileName]);
    }
    else
    {
        readStyleSheet(strFileName, strQss, strRss);
    }

    parent->setStyleSheet(strQss);
}

void CStyleSheet::readStyleSheet(const QString &strFileName, QString &strQss, QString &strRss)
{
    strRss = CGenUtils::readfile(m_stSln.strQssPath + "/" + strFileName + ".rss");
    strRss = strRss.simplified();

    strQss = CGenUtils::readfile(m_stSln.strQssPath + "/" + strFileName + ".qss");
    m_mapQss[strFileName] = std::make_tuple(strQss, strRss);
}
