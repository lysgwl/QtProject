#ifndef ESL_SERVER_H
#define ESL_SERVER_H

#include "STHeader.h"
#include "./eslHttp/eslHttpControl.h"

class CEslServer
{
public:
	CEslServer();
	~CEslServer();

	static CEslServer &Instance();

public:
	//是否开启服务
	bool isEslServer();
	
	//登录用户
	bool loginUser(const QJsonObject &json);
	
	//创建会议
	bool createMeeting(STMeetingDetailInfo &detailInfo, const QVector<QString> &vecMember);
	
	//关闭会议
	void closeMeeting(int iType, int iMeetId);
	
	//获取会议信息
	bool getMeetingInfo(int iType, int iMeetId, QJsonObject &jsonValue);
	
	//获取会议成员
	bool getMeetingUserList(int iType, int iMeetId, QVector<STMeetingMemberVs> &vecMember);
	
	//获取会议状态
	int getMeetStatusFromEsl(int iStatus);
	
	//获取通播状态
	int getAnncStatusFromEsl(int iStatus);
	
protected:
	//登录席位号码
	bool loginSeatNumber(const QJsonObject &json);

	//登录用户号码
	bool loginUserNumber(const QJsonObject &json);	
	
	//连接服务器
	bool connectSvr(const QJsonObject &json);
	
protected:
	CEslHttpControl *m_pHttpCtrl = Q_NULLPTR;	
};

#endif