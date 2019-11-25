#include "SerialServer.h"

CSerialServer::CSerialServer() :
	m_locker(QReadWriteLock::Recursive)
{
	m_pSerial = nullptr;
}

CSerialServer::~CSerialServer()
{
}

bool CSerialServer::Init()
{
	if (m_pSerial != nullptr)
	{
		return true;
	}
	
	m_pSerial = new QSerialPort;
	if (m_pSerial == nullptr)
	{
		return false;
	}
	
	return true;
}

void CSerialServer::Uninit()
{
	if (m_pSerial != nullptr)
	{
		delete m_pSerial;
		m_pSerial = nullptr;
	}
}

bool CSerialServer::Open(const QString &strName)
{
	if (m_pSerial == nullptr)
	{
		return false;
	}
	
	m_pSerial->setPortName(strName);
	if (!m_pSerial->open(QIODevice::ReadWrite))
	{
		return false;
	}
	
	m_pSerial->setBaudRate(QSerialPort::Baud19200);
	m_pSerial->setDataBits(QSerialPort::Data8);
	m_pSerial->setParity(QSerialPort::NoParity);
	m_pSerial->setStopBits(QSerialPort::OneStop);
	m_pSerial->setFlowControl(QSerialPort::NoFlowControl);
	
	connect(m_pSerial, SIGNAL(readyRead()), this, SLOT(ReadData()));
	return true;
}

void CSerialServer::Close()
{
	if (m_pSerial == nullptr)
	{
		return;
	}
	
	if (!m_pSerial->isOpen())
	{
		return;
	}
	
	m_pSerial->clear();
	m_pSerial->close();
}

size_t CSerialServer::Read(char *pData)
{
}

size_t CSerialServer::Write(const char *pData, uint uDataLen)
{
}

void CSerialServer::ReadData()
{
}
