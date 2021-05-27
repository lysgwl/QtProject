#include "ToolStatusControl.h"

#include <internal.h>
#include "../widget/ToolStatusView.h"

CToolStatusControl::CToolStatusControl(QObject *parent) 
		: QObject(parent)
{
}

QObject* CToolStatusControl::getObject()
{
    return this;
}

void CToolStatusControl::initUI(CToolStatusView *pToolStatusView)
{
    m_pToolStatusView = pToolStatusView;
    m_pToolStatusView->initUI();
}
