#ifndef __SERIAL_SERVER_H__
#define __SERIAL_SERVER_H__

#include <QReadWriteLock>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QserialPortInfo>

class CSerialServer
{
public:
	CSerialServer();
	~CSerialServer();
	
public:
	bool			Init();
	void			Uninit();
	
	bool			Open(const QString &strName);
	void			Close();
	
	size_t			Read(char *pData);
	size_t			Write(const char *pData, uint uDataLen);
	
protected:
	void			ReadData();	
	
private:
	QSerialPort*	m_pSerial;
	QReadWriteLock	m_locker;	
};

#endif