#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include <IMgrService.h>

class CAppConfig : public IMgrService, public stGlobalVariant
{
public:
    CAppConfig();
    ~CAppConfig();

public:
    // 初始化服务
    void init() override;

    // 执行服务
    void exec() override;
};

DECLARE_OBJ(CAppConfig, "org.CAppConfig.service")

#endif
