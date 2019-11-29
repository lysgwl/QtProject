#ifndef __SCREENSHOT_VIEW_H__
#define __SCREENSHOT_VIEW_H__

#include <QtWidgets>

class CScreenShotView : public QWidget
{
	Q_OBJECT
public:
	explicit CScreenShotView(QWidget *parent = nullptr);
	
	void	initUI();
	
protected:
	void 	resizeEvent(QResizeEvent *event) override;

protected:
    QLabel  *m_pScreenImageLabel;
};

#endif
