#include "ToolStatusControl.h"

#include "../inc/FrameWork.h"
#include "../widget/ToolStatusView.h"
#include "../widget/ViewMainHandler.h"

CToolStatusControl::CToolStatusControl(QObject *parent) 
		: QObject(parent)
{
}

void CToolStatusControl::initToolStatus()
{
    CToolStatusView *pToolStatus = (CToolStatusView*)CFrameWork::getObjectPointer(View_ToolStatus_id);
    if (pToolStatus == nullptr)
        return;

    pToolStatus->initUI();
}

QObject* CToolStatusControl::getObject()
{
    return this;
}
