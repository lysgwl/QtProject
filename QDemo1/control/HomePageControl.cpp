#include "HomePageControl.h"

#include <internal.h>

CHomePageControl::CHomePageControl(QObject *parent) 
		: QObject(parent)
{
}

QObject* CHomePageControl::getObject()
{
    return this;
}

QWidget* CHomePageControl::getWidget()
{
    return m_pHomePageView;
}

void CHomePageControl::initHomePage()
{
    if (m_pHomePageView == Q_NULLPTR)
    {
        m_pHomePageView = new CHomePageView();
        m_pHomePageView->initUI();
    }
}

void CHomePageControl::updateHomePage()
{
}
