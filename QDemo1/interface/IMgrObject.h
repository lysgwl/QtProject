#ifndef __I_MGR_OBJECT_H__
#define __I_MGR_OBJECT_H__

#include <internal.h>

typedef std::tuple<std::string, int> ObjectKey;

// 对象管理抽象接口
class IMgrObject : public CObject
{
public:
	// 获取对象名称
	virtual std::string getObjectName(CObject* obj) = 0;
	
	// 注册对象
	virtual void addObject(const ObjectKey& key, CObject* obj) = 0;
	
	// 获取对象
	virtual CObject* getObject(const std::string& strName, const int& index=-1) = 0;
	virtual CObject* getObject(const ObjectKey& key) = 0;
};


#endif
