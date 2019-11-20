#ifndef __VIEWMAIN_HANDLER_H__
#define __VIEWMAIN_HANDLER_H__

enum ViewHandlerId {
    View_MainFrame_id   = 0x2001,
    View_TopMenu_id     = 0x2002,
    View_ToolStatus_id  = 0x2003,
};

class CViewMainHandler
{
public:
	CViewMainHandler();
	
public:
	static void registerObj();
};

#endif
