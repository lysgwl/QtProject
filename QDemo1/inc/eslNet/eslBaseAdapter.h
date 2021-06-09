#ifndef ESL_BASE_ADAPTER_H
#define ESL_BASE_ADAPTER_H

#include <iostream>
#include <string>

#include <vector>
#include <tuple>

#include <QJsonObject>
#include <QJsonDocument>

#include <winsock2.h>
#include "eslHeader.h"

class CEslBaseAdapter
{
public:
	CEslBaseAdapter();
	virtual ~CEslBaseAdapter();

public:
    //解析json数据段
    bool eslParseSegment(const QJsonObject &json, int iPkgType, void *pstPkg);
	
protected:
    //解析消息数据
    bool parseSegment(int iPkgType, void *pstPkg, std::vector<std::tuple<std::string, std::string>> &vecTuple);

    //设置Basic数据
    void setBasicPkgData(std::string &strKey, std::string &strValue, void *pstPkg);

    //设置Config数据
    void setConfigPkgData(std::string &strKey, std::string &strValue, void *pstPkg);

    //设置Schedule数据
    void setSchPkgData(std::string &strKey, std::string &strValue, void *pstPkg);

    //设置Event数据
    void setEventPkgData(std::string &strKey, std::string &strValue, void *pstPkg);
};

#endif
