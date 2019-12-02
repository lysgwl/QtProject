#include "application.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    CApplication app(argc, argv);

    QApplication::setQuitOnLastWindowClosed(false);
    
	app.initModule();
    app.runModule();
	
    return app.exec();
}
