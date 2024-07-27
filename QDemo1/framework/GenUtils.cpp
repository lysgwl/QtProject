#include "GenUtils.h"

CGenUtils::CGenUtils()
{
}

CGenUtils::~CGenUtils()
{
}

CGenUtils& CGenUtils::GetInstance()
{
    static CGenUtils instance;
    return instance;
}

void CGenUtils::mkdir(const QString &strDir)
{
	QDir dir(strDir);
	if (!dir.exists())
	{
		dir.mkpath(strDir);
	}
}

QString CGenUtils::readfile(const QString &strFile)
{
	QString strRet;
	
	QFile file(strFile);
	if (file.open(QIODevice::ReadOnly))
	{
		strRet = file.readAll();
        file.close();
	}
	
	return strRet;
}