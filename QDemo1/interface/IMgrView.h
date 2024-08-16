#ifndef __I_MGR_VIEW_H__
#define __I_MGR_VIEW_H__

#include <objects.h>

// 视图模型
class IMgrView
{
public:
    virtual ~IMgrView() = default;

public:
    // 初始化
    virtual void init() = 0;

    // 执行
    virtual void exec() = 0;
};

#endif
