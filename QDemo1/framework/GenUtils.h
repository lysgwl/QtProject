#ifndef __GEN_UTILS_H__
#define __GEN_UTILS_H__

#include <internal.h>

class CGenUtils
{
private:
	explicit CGenUtils();
	~CGenUtils();
	
	// 禁止拷贝构造和赋值
	CGenUtils(const CGenUtils&) = delete;
	CGenUtils& operator=(const CGenUtils&) = delete;
	
public:
	static CGenUtils &GetInstance();	
	
public:
	// 创建目录
	void mkdir(const QString &strDir);

	// 读取文件
	QString readfile(const QString &strFile);
};

#endif