#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <stheader.h>

class CObject : public QObject
{
public:
    CObject() {};
    virtual ~CObject() {};
};

// 获取接口的 IID
template<typename T>
inline const char* get_obj_iid() {
    return nullptr;
}

// 关联接口和IID
#define DECLARE_OBJ(IFace, IID_IFace) \
	template<> \
	inline const char* get_obj_iid<IFace*>() { \
		return IID_IFace; \
	}
	
// 用于获取接口的 IID
#define GET_IID(IFace) (get_obj_iid<IFace*>())

// 获取指定接口类型的服务
#define GET_SERVICE(IFace) \
    CFrameWork::GetInstance().get_object_service(GET_IID(IFace))

// 将给定的服务对象添加到 CObjectMgr
#define REGISTER_OBJECT(IFace, objService) { \
    CObjectMgr* objectMgr=dynamic_cast<CObjectMgr*>(GET_SERVICE(CObjectMgr)); \
    if (objectMgr != nullptr) { \
        objectMgr->addObject(GET_IID(IFace), objService); \
    } else { \
        std::cerr << "Error: Failed to get CObjectMgr service." << std::endl; \
    } \
}

// 获取CObjectMgr中已注册的特定对象类型
#define GET_OBJECT_PTR(IFace) ( \
    dynamic_cast<IFace*>( \
        (dynamic_cast<CObjectMgr*>(GET_SERVICE(CObjectMgr)))->getObject(GET_IID(IFace)) \
    ) \
)

#endif
