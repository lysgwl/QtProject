#include "eslBaseAdapter.h"

CEslBaseAdapter::CEslBaseAdapter()
{
}

CEslBaseAdapter::~CEslBaseAdapter()
{
}

//获取视频会议分屏数
int CEslBaseAdapter::eslGetMeetSplitNum(int iNum)
{
	int iSplitNum = 4;
	switch (iNum)
	{
	case vsmS1:
		iSplitNum = 1;
		break;
		
	case vsmS4:
		iSplitNum = 4;
		break;
		
	case vsmS5_1:
		iSplitNum = 6;
		break;
		
	case vsmS7_1:
		iSplitNum = 8;
		break;
		
	case vsmS9:
		iSplitNum = 9;
		break;
		
	case vsmS12_1:
		iSplitNum = 12;	//暂不支持13
		break;
		
	case vsmS16:
		iSplitNum = 16;
		break;
		
	default:
		break;
	}
	
	return iSplitNum;
}