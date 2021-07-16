#ifndef ESL_HEADER_H
#define ESL_HEADER_H

#include <string>
#include <iostream>

#include <vector>
#include <tuple>

#include <QJsonObject>
#include <QJsonDocument>

#ifdef WIN32
	#include <winsock2.h>
#endif

#include "STHeader.h"
#include "mcBaseDef.h"
#include <DCProtocol.h>
#include <IRztAnnounceRequestVideoMgr.h>
#define ESL_PROTOCOL_ID		0x1234abcd

//pkg包类型
enum ELS_PKG_TYPE
{
	ESL_PKG_TYPE_DATA = 0,			//数据包类型
	ESL_PKG_TYPE_STATUS,			//状态包类型
	ESL_PKG_TYPE_NOTIFY,			//通知包类型
	ESL_PKG_TYPE_MEET,				//会议包类型
	ESL_PKG_TYPE_ANNC,				//通播包类型
	ESL_PKG_TYPE_RADIO,				//电台包类型
};

//数据接口
enum ESL_DATA_MSG_TYPE 
{
	ESL_MSG_LOGIN_REQ = 0,			//登录请求
	ESL_MSG_LOGIN_RESP,				//登录回复
	ESL_MSG_LOGOUT_IND,				//注销请求
	ESL_MSG_HEARTBEAT_REQ,			//心跳请求
	ESL_MSG_HEARTBEAT_RESP,			//心跳回复
};

//会议接口
enum ESL_MEET_MSG_TYPE
{
	ESL_MSG_CREATEMEET_REQ = 0,		//创建会议请求
	ESL_MSG_CREATEMEET_RESP,		//创建会议回复
	
	ESL_MSG_CLOSEMEET_REQ,			//关闭会议请求
	ESL_MSG_CLOSEMEET_RESP,			//关闭会议回复
	
	ESL_MSG_ADDMEETMEMB_REQ,		//添加会议成员请求
	ESL_MSG_ADDMEETMEMB_RESP,		//添加会议成员回复
	
	ESL_MSG_DELMEETMEMB_REQ,		//删除会议成员请求
	ESL_MSG_DELMEETMEMB_RESP,		//删除会议成员回复
	
	ESL_MSG_SILENCEMEETMEMB_REQ,	//禁言会议成员请求
	ESL_MSG_SILENCEMEETMEMB_RESP,	//禁言会议成员回复
	
	ESL_MSG_MUTEMEETMEMB_REQ,		//静音会议成员请求
	ESL_MSG_MUTEMEETMEMB_RESP,		//静音会议成员回复
	
	ESL_MSG_SPEECHMEETMEMB_REQ,		//会议成员演讲请求
	ESL_MSG_SPEECHMEETMEMB_RESP,	//会议成员演讲回复
	
	ESL_MSG_SPLITSCREENMEET_REQ,	//视频会议画面分割请求
	ESL_MSG_SPLITSCREENMEET_RESP,	//视频会议画面分割回复
	
	ESL_MSG_CALLTOMEET_REQ,			//通话转会议请求
	ESL_MSG_CALLTOMEET_RESP,		//通话转会议回复
};

//通播接口
enum ESL_ANNC_MSG_TYPE
{
	ESL_MSG_CREATEANNC_REQ = 0,		//创建通播请求
	ESL_MSG_CREATEANNC_RESP,		//创建通播回复
	
	ESL_MSG_ADDANNCMEMB_REQ,		//添加通播成员请求
	ESL_MSG_ADDANNCMEMB_RESP,		//添加通播成员回复
	
	ESL_MSG_DELANNCMEMB_REQ,		//删除通播成员请求
	ESL_MSG_DELANNCMEMB_RESP,		//删除通播成员回复
	
	ESL_MSG_CLOSEANNC_REQ,			//关闭通播请求
	ESL_MSG_CLOSEANNC_RESP,			//关闭通播回复
	
	ESL_MSG_STARTSPEAK_REQ,			//开启通播对讲请求
	ESL_MSG_STARTSPEAK_RESP,		//开启通播对讲回复
	
	ESL_MSG_STOPSPEAK_REQ,			//关闭通播对讲请求
	ESL_MSG_STOPSPEAK_RESP,			//关闭通播对讲回复
	
	ESL_MSG_STARTVIDEO_REQ,			//开启通播视频请求
	ESL_MSG_STARTVIDEO_RESP,		//开启通播视频回复
	
	ESL_MSG_STOPVIDEO_REQ,			//关闭通播视频请求
	ESL_MSG_STOPVIDEO_RESP,			//关闭通播视频回复
};

//通知接口
enum ESL_NOTIFY_MSG_TYP
{
	ESL_NOTIFY_SEATCONTACT = 1,		//席位通讯录通知
	ESL_NOTIFY_QUICKCONTACT,		//快捷通讯录通知
	ESL_NOTIFY_PUBLICCONTACT,		//公共通讯录通知
	ESL_NOTIFY_STYLECONFIG,			//个性化配置通知
	ESL_NOTIFY_CALLTOMEET,			//呼叫转会议通知
};

#endif