#ifndef __I_MGR_OBJECT_H__
#define __I_MGR_OBJECT_H__

#include <stheader.h>

// 对象管理抽象接口
class IMgrObject : public CObject
{
public:
    // 获取对象
    virtual CObject* getObject(const QString& strName) = 0;
	
	// 注册对象
	virtual void addObject(const QString& strName, CObject* obj) = 0;
};

#endif
