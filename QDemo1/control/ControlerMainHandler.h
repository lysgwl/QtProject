#ifndef __CONTROLERMAIN_HANDLER_H__
#define __CONTROLERMAIN_HANDLER_H__

enum ControlerHandlerId {
    Controler_MainFrame_Id  = 0x1001,
    Controler_TopMenu_Id    = 0x1002,
    Controler_ToolStatus_Id = 0x1003,
};

class CControlerMainHandler
{
public:
    CControlerMainHandler();
	
public:
	static void		registerObj();
};

#endif
