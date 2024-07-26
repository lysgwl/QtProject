#include "WorkMainControl.h"

#include <internal.h>
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
    ObjectMgr *pObjectMgr = CFrameWork::getFrameWork().getObjectMgr();
	if (pObjectMgr == Q_NULLPTR)
	{
		return;
	}
	
    if (m_pWorkView == Q_NULLPTR)
	{
		m_pWorkView = new CWorkMainView();
		m_pWorkView->initUI();

        ObjectPtr<CToolStatusControl> toolStatus(Controler_ToolStatus, pObjectMgr);
        toolStatus->initUI(m_pWorkView->getToolStatusView());
    }
}

void CWorkMainControl::updateWorkFrame()
{
}
