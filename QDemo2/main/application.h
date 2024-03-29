#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <QApplication>
#include "../widget/MainFrameWindow.h"

class CApplication : public QApplication
{
public:
	CApplication(int &argc, char **argv);
	
	void		initModule();
    void        runModule();
	
protected:
    void        setAppEnv();
    void        setAppModule();

private:
    CMainFrameWindow *m_pMainFrameWindow;
};

#endif
