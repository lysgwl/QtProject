#ifndef ELS_DATA_ADAPTER_H
#define ELS_DATA_ADAPTER_H

class CElsDataAdapter : public CElsBaseAdapter
{
public:
	CElsDataAdapter();
	~CElsDataAdapter();
	
public:	
	//Pkg�������
	bool elsBuildPkg(int iPkgType, void *pstPkg, std::string &strJson, int &iMsgType);	
	
	//Pkg������
	bool elsParsePkg(int iPkgType, int iMsgType, char *pPayload, void* pstEvent);
	
	//Pkg��ת��json
	bool elsBuildJson(void* pstEvent, QJsonObject &json);
	
protected:
	//stBasicPkgFormat����
	bool buildBaseReqPkg(void *pstPkg, std::string &strJson, int &iMsgType);
	
	//stCfgPkgFormat����
	bool buildConfigReqPkg(void *pstPkg, std::string &strJson, int &iMsgType);
	
	//stBasicPkgFormat�ظ�
	bool buildBaseRespPkg(void* pstPkg, QJsonObject &json);
	
	//stCfgPkgFormat�ظ�
	bool buildConfigRespPkg(void* pstPkg, QJsonObject &json);
	
protected:
	//��¼Req
	void OnReqElsLogin(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType);
	
	//ע��Req
	void OnReqElsLoginOut(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType);
	
	//����Req
	void OnReqElsHeartBeat(const stBasicPkgFormat *pstPkg, std::string &strJson, int &iMsgType);
	
	//��¼Resp
	void OnRespElsLogin(bool bFlag, stBasicPkgFormat *pstPkg, QJsonObject &json);
	
	//����Resp
	void OnRespElsHeartBeat(bool bFlag, stBasicPkgFormat *pstPkg, QJsonObject &json);
};

#endif