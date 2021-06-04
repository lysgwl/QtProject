#ifndef __SCREENSHOT_VIEW_H__
#define __SCREENSHOT_VIEW_H__

#include <QtWidgets>
#include <QPixmap>

class CScreenShotView : public QWidget
{
	Q_OBJECT
public:
	explicit CScreenShotView(QWidget *parent = nullptr);
	
	void	initUI();
	
protected:
	void 	resizeEvent(QResizeEvent *event) override;

    void    setWndLayout();
    void    setWidgetCtrl(bool bFlag);
    void    showImageLabel(QPixmap &pixmap);

private slots:
    void    newScreenShot();
    void    saveScreenShot();
    void    screenShot();

protected:
    QSpinBox *m_pSpinBox;
    QCheckBox *m_pCheckBox;
    QLabel  *m_pScreenImageLabel;

    QPushButton *m_pNewScreenShotBtn;
    QPushButton *m_pSaveScreenShotBtn;

private:
    QPixmap m_pixmap;
};

#endif
