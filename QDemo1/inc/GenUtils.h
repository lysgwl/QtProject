#ifndef GEN_UTILS_H
#define GEN_UTILS_H

#include <stHeader.h>

class CGenUtils
{
public:
	explicit CGenUtils();
	
public:
	static void mkdir(const QString &strDir);

	static QString readfile(const QString &strFile);
};

#endif