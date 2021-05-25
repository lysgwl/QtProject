#include "WorkMainControl.h"

#include "../inc/FrameWork.h"
#include "./ControlerMain.h"
#include "./ToolStatusControl.h"

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
    if (m_pWorkView == Q_NULLPTR)
	{
		m_pWorkView = new CWorkMainView();
		m_pWorkView->initUI();

        ObjectPtr<CToolStatusControl> toolStatus(Controler_ToolStatus, CFrameWork::getObjectMgr());
        toolStatus->initUI(m_pWorkView->getToolStatusView());
    }
}

void CWorkMainControl::updateWorkFrame()
{
}
