#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class CApplication : public QApplication
{
public:
	CApplication(int &argc, char **argv);
	
    void initModule();
    void runModule();
	
protected:
    void setAppEnv();
    void setAppModule();
};

#endif
