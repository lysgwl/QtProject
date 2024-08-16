#ifndef __I_MGR_CONTROLLER_H__
#define __I_MGR_CONTROLLER_H__

#include <objects.h>

// 控制器模型
class IMgrController : public CObject
{
public:
	virtual ~IMgrController() = default;
	
public:
	// 注册对象
	virtual void registerobj() = 0;	
	
	// 初始化
	virtual void init() = 0;
	
	// 执行
    virtual void exec() = 0;

    //
    virtual CObject* getobject() =0;

    //
    virtual QWidget* getview() = 0;
};

#endif
