#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <internal.h>

class CApplication : public QApplication
{
public:
	CApplication(int &argc, char **argv);
	
    void init_module();
    void run_module();
	
protected:
    void set_app_env();
    void set_app_module();
};

#endif
