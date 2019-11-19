#ifndef __CONTROLERMAIN_HANDLER_H__
#define __CONTROLERMAIN_HANDLER_H__

enum ControlerHandlerId {
    Controler_MainFrame_Id  = 0x1001,
};

class CControlerMainHandler
{
public:
    CControlerMainHandler();
	
public:
	static void		registerObj();
};

#endif
