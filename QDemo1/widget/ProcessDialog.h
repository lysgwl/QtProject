#ifndef PROCESSDIALOG_H
#define PROCESSDIALOG_H

#include <QKeyEvent>
#include <QProgressDialog>

class ProcessDialog : public QProgressDialog
{
	Q_OBJECT
public:
    explicit ProcessDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::Widget);

protected:
	void	 keyPressEvent(QKeyEvent *event);
};

#endif
