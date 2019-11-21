#include "application.h"

int main(int argc, char *argv[])
{
    CApplication app(argc, argv);
	
    app.initModule();
    app.runModule();
    
    return app.exec();
}
