#ifndef ESL_HEADER_H
#define ESL_HEADER_H

#define ESL_PROTOCOL_ID		0x1234abcd

#define STR_LEN_2		2
#define STR_LEN_6		6
#define STR_LEN_8		8
#define STR_LEN_16		32
#define STR_LEN_32		32
#define STR_LEN_64		64
#define STR_LEN_128		128
#define STR_LEN_196		196
#define STR_LEN_256		256
#define STR_LEN_512		512
#define STR_LEN_1024	1024
#define STR_LEN_2048	2048
#define STR_LEN_4096	4096

#define BUF_SIZE_64 	64
#define BUF_SIZE_512 	512
#define BUF_SIZE_1024 	1024
#define BUF_SIZE_2048 	2048
#define BUF_SIZE_4096 	4096
#define BUF_SIZE_8192 	8192

#define AC_MAX_PROTOCOL_PKG_LEN     4096
#define AC_RECV_BUF_MAX_SIZE        BUF_SIZE_4096 * 10 * 10

#define LOGIN_VIA_USR_NUMB                   0  //使用调度员号码登录，且兼容以调度员名字登录
#define LOGIN_VIA_USR_ORG_INFO               1  //使用单位、部门、调度员名字登录
#define LOGIN_NEED_CUSTOMED_SCHEDULER_NUMB   2  //使用调度员号码登录，且兼容以调度员名字登录,但需要系统返回一个定制的调度员号码

enum PACKAGE_TYPE
{
	PKG_TYPE_INVALID = 0,
	PKG_TYPE_BASIC = 1,
	PKG_TYPE_CONFIG = 2,
	PKG_TYPE_SCHEDULE = 3,
	PKG_TYPE_EVENT = 4,
	PKG_TYPE_MAX
};

enum BASIC_MSG_TYPE
{
	BASIC_MSG_MIN = 0,
	BASIC_MSG_LOGIN_REQ = 1,
	BASIC_MSG_LOGIN_RESP = 2,
	BASIC_MSG_LOGOUT_IND = 3,
	BASIC_MSG_HEARTBEAT = 4,
	BASIC_MSG_HEARTBEAT_ACK = 5,
	BASIC_MSG_LOGINEXT_REQ = 20,
	BASIC_MSG_LOGINEXT_RESP = 21,
};

enum enTERMINAL_TYPE
{
	TERMINAL_TYPE_UNKNOW = 0,
	TERMINAL_TYPE_CFG,
	TERMINAL_TYPE_SCHEDULE,
};

//pkg包类型
enum ELS_PKG_TYPE
{
	ESL_PKG_TYPE_DATA = 0,
	ESL_PKG_TYPE_MEET,
	ESL_PKG_TYPE_STATUS
};

//数据接口
enum ESL_DATA_MSG_TYPE 
{
	ESL_MSG_DATA_EMPTY = 0,
	ESL_MSG_LOGIN_REQ,
	ESL_MSG_LOGIN_RESP,
	ESL_MSG_LOGOUT_IND,
	ESL_MSG_HEARTBEAT_REQ,
	ESL_MSG_HEARTBEAT_RESP,
};

//会议接口
enum ESL_MEET_MSG_TYPE
{
	ESL_MSG_MEET_EMPTY = 0,
};

//状态接口
enum ELS_STATUS_MSG_TYPE
{
	ELS_MSG_STATUS_EMPTY = 0,
};

//pkg包头
struct stTerminalPkgHeader
{    
	int iProtocolId;
	char cPkgType;
	char cMsgType;
	char reserve[2];
	int iBodyLength;
	char body[0];
};

//msg包
typedef struct _MESSAGE_
{
	int ePskType;
	void *pvMessage;
}stMESSAGE;

typedef struct _tagBasicPkgFormat
{
	int iMsgType;
	char acProtocolVersion[STR_LEN_6];
	char acDeviceID[STR_LEN_32+1];
	int iReserver0;
	int iReserver1;
	char acReserver2[STR_LEN_1024];
	int iReqId;
	int iResult;
	int iTerminalId;
	char acUsrName[STR_LEN_32+1];
	char acPwd[STR_LEN_32+1];
	int iTerminalType;
	int iRight;                        
    unsigned int uiDataLen;
	char acData[BUF_SIZE_2048];
}stBasicPkgFormat;

typedef struct _tagConfigPkgFormat
{
	int iMsgType;
	char acProtocolVersion[STR_LEN_6];
	char acDeviceID[STR_LEN_32];
	int iReserver0;
	int iReserver1;
	char acReserver2[STR_LEN_1024];
    unsigned int uiRequestID;
    unsigned int uiTerminalId;
    unsigned int uiResult;
	char acNumber[STR_LEN_64];
	int iTransactionID;
    unsigned int uiMode;
    unsigned int uiActionType;
    unsigned int uiCfg;
    unsigned int uiDataType;
    unsigned int uiTotalItem;
    unsigned int uiStartIndex;
    unsigned int uiEndIndex;
    unsigned int uiDataLen;
	char acDescription[STR_LEN_64];
	char acData[BUF_SIZE_2048];
}stCfgPkgFormat;

typedef struct _tagSchedulePkgFormat
{
	int iMsgType;
	char acProtocolVersion[STR_LEN_6];
	char acDeviceID[STR_LEN_32];
	int iReserver0;
	int iReserver1;
	char acReserver2[STR_LEN_1024];
    unsigned int iReqId;
    unsigned int iTerminalId;
    unsigned int iResult;
	char acNumber[STR_LEN_64];
	char acNumbList[STR_LEN_2048];
    unsigned int iTransactionId;
    unsigned int uiCfg;
    unsigned int uiDataType;
    unsigned int uiTotalItem;
    unsigned int uiStartIndex;
    unsigned int uiEndIndex;
    unsigned int uiDataLen;
	char acData[BUF_SIZE_2048];
}stSchPkgFormat;

typedef struct _tagEventPkgFormat
{
	int iMsgType;
	char acProtocolVersion[STR_LEN_6];
	char acDeviceID[STR_LEN_32];
	int iReserver0;
	int iReserver1;
	char acReserver2[STR_LEN_1024];               
    unsigned int uiEventType;
	char acLoginUser[STR_LEN_16];
	char acGroupName[STR_LEN_16];
	char acUserNum[STR_LEN_16];
	unsigned uiTransactionId;
    unsigned int uiParamLen;
	char acParameter[BUF_SIZE_2048];
}stEventPkgFormat;

#endif