#include "WorkMainControl.h"

CWorkMainControl::CWorkMainControl(QObject *parent) 
		: QObject(parent)
{
}

QObject* CWorkMainControl::getObject()
{
    return this;
}

QWidget* CWorkMainControl::getWidget()
{
    return m_pWorkView;
}

void CWorkMainControl::initWorkFrame()
{
    /*if (m_pWorkView == Q_NULLPTR)
	{
		m_pWorkView = new CWorkMainView();
		m_pWorkView->initUI();
    }*/
}

void CWorkMainControl::updateWorkFrame()
{
}
