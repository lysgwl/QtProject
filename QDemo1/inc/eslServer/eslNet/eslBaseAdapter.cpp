#include "eslBaseAdapter.h"

CEslBaseAdapter::CEslBaseAdapter()
{
}

CEslBaseAdapter::~CEslBaseAdapter()
{
}

//获取会议状态
int CEslBaseAdapter::eslGetMeetStatus(int iStatus)
{
	int iMmsState = MMS_OFFLINE;
	switch (iStatus)
	{
	case ESL_MEMB_STATE_INIT:
		iMmsState = static_cast<int>(MMS_INIT);
		break;
		
	case ESL_MEMB_STATE_INVITING:
		iMmsState = static_cast<int>(MMS_INVITING);
		break;
		
	case ESL_MEMB_STATE_ANSWER:
		iMmsState = static_cast<int>(MMS_JOINED);
		break;
		
	case ESL_MEMB_STATE_NOANSWER:
		iMmsState = static_cast<int>(MMS_NO_ANSWER);
		break;
		
	case ESL_MEMB_STATE_REJECT:
		iMmsState = static_cast<int>(MMS_REJECT);
		break;
		
	case ESL_MEMB_STATE_EXIT:
		iMmsState = static_cast<int>(MMS_EXIT);
		break;
		
	case ESL_MEMB_STATE_SILENCE:
		iMmsState = static_cast<int>(MMS_MUTED);
		break;
		
	case ESL_MEMB_STATE_HOLDING:
		iMmsState = static_cast<int>(MMS_NON_TALK);
		break;
		
	case ESL_MEMB_STATE_SPEECHING:
		iMmsState = static_cast<int>(MMS_TALK);
		break;
		
	default:
		break;
	}
	
	return iMmsState;
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