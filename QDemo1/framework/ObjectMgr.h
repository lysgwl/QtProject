#ifndef __OBJECT_MGR_H__
#define __OBJECT_MGR_H__

class CObjectMgr ：public IMgrObject, public IMgrService
{
private:
	std::map<ObjectKey, CObject*> m_mapData;
	
public:
	CObjectMgr();
	~CObjectMgr();
	
public:
	void init();

	void exec();

public:
	QString  getObjectName(CObject* obj) override;
	void 	 addObject(const ObjectKey& key, CObject* obj) override;
	
	CObject* getObject(const QString& strName, const int& index=-1) override;
	CObject* getObject(const ObjectKey& key) override;
};

#endif