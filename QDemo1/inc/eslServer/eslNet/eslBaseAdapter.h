#ifndef ESL_BASE_ADAPTER_H
#define ESL_BASE_ADAPTER_H

#include "eslHeader.h"

class CEslBaseAdapter
{
public:
	CEslBaseAdapter();
	virtual ~CEslBaseAdapter();

public:
	//获取会议状态
	int eslGetMeetStatus(int iStatus);
};

#endif
