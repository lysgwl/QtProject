#include "ProcessDialog.h"

ProcessDialog::ProcessDialog(QWidget *parent, Qt::WindowFlags flags)
	: QProgressDialog(parent, flags)
{
}

void ProcessDialog::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Escape)
	{
		event->ignore();
	}
}
