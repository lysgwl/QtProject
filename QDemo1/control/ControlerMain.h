#ifndef CONTROLERMAIN_H
#define CONTROLERMAIN_H

#include <QObject>

enum ControlerHandler{
    Controler_MainFrame  = 0x1001,
    Controler_WorkFrame  = 0x1002,
    Controler_ToolStatus = 0x1003,
};

class ControlerMain
{
public:
    explicit ControlerMain();
	
public:
	static void registerObj();

    static void showControlMain();
};

#endif
