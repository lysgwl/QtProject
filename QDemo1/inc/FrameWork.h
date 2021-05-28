#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <stHeader.h>
#include <ObjectMgr.h>

class CFrameWork
{
public:
	CFrameWork();

    static CFrameWork &getFrameWork();
	
public:
    ObjectMgr* getObjectMgr();
	
    void* getObjectPointer(uint uiId);

    stGlobalVariant* getGlobalVariant();

    void initGlobalEnv();

    void setStyleSheet(QWidget *parent, QString strFileName);

private:
    ObjectMgr m_objectMgr;
    stGlobalVariant m_stGlobalVariant;
};

#endif
