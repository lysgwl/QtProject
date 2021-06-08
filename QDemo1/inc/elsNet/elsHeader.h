#ifndef ELS_HEADER_H
#define ELS_HEADER_H

#define ELS_PROTOCOL_ID		0x1234abcd

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

//pkg包类型
enum ELS_PKG_TYPE
{
	ELS_PKG_TYPE_DATA = 0,
	ELS_PKG_TYPE_MEET,
	ELS_PKG_TYPE_STATUS
};

//数据接口
enum ELS_DATA_MSG_TYPE 
{
	ELS_MSG_DATA_EMPTY = 0,
	ELS_MSG_LOGIN_REQ,
	ELS_MSG_LOGIN_RESP,
	ELS_MSG_LOGOUT_IND,
	ELS_MSG_HEARTBEAT_REQ,
	ELS_MSG_HEARTBEAT_RESP,
};

//会议接口
enum ELS_MEET_MSG_TYPE
{
	ELS_MSG_DATA_EMPTY = 0,
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