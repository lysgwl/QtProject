#include "ToolStatusView.h"

#include <internal.h>

CToolStatusView::CToolStatusView(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
}

void CToolStatusView::initUI()
{
	m_lUserName = new QLabel();
	m_lUserName->setObjectName("label user name");
    m_lUserName->setText(QString("%1(%2)").arg("16104016001").arg("16104016001"));

    m_lLogoIcon = new QLabel();
    m_lLogoIcon->setObjectName("label logo icon");

    m_btnLogout = new QPushButton("注销");
    m_btnLogout->setObjectName("button logout");
    connect(m_btnLogout, &QPushButton::clicked, this, &CToolStatusView::btnLogoutClicked);

    m_btnTest1 = new QPushButton("测试1");
    m_btnTest1->setObjectName("button test1");
    connect(m_btnTest1, &QPushButton::clicked, this, &CToolStatusView::btnTest1Clicked);

	m_lNumberName = new QLabel();
	m_lNumberName->setObjectName("label number name");
    //m_lNumberName->setText(QString("%1(%2)").arg("16104026001").arg("16104026001"));

	m_lUserTime = new QLabel();
	m_lUserTime->setObjectName("label user time");
    m_lUserTime->setText(QDateTime::currentDateTime().toString("MM月dd日 dddd hh:mm:ss"));

	m_timer = new QTimer(this);
	m_timer->start(1000);
    connect(m_timer, &QTimer::timeout, this, &CToolStatusView::setUserTimer);
	
	if (m_layoutMain == Q_NULLPTR)
	{
		m_layoutMain = new QHBoxLayout();
		m_layoutMain->setSpacing(0);
		m_layoutMain->setMargin(0);
        m_layoutMain->setAlignment(Qt::AlignCenter);
	}
	
	if (m_layoutStatus == Q_NULLPTR)
	{
		m_layoutStatus = new QHBoxLayout();
        m_layoutStatus->setSpacing(10);
	}
	
	m_layoutMain->addWidget(m_lUserName, 0, Qt::AlignLeft);
	m_layoutMain->addStretch();
	
    m_layoutMain->addWidget(m_lUserTime, 0, Qt::AlignCenter);
    m_layoutMain->addStretch();
	
	m_layoutMain->addLayout(m_layoutStatus);
	m_layoutMain->addWidget(m_lNumberName);
    m_layoutMain->addStretch();

    m_layoutMain->addWidget(m_btnLogout);
    m_layoutMain->addStretch();
    m_layoutMain->addWidget(m_btnTest1);
	
	this->setLayout(m_layoutMain);
	this->setProperty("showMode", "normal");

    /*this->setStyleSheet("QPushButton{background-color:black;\
              color: red;   border-radius: 10px;  border: 2px groove gray;\
              border-style: outset;}"
              "QPushButton:hover{background-color:white; color: black;}"
              "QPushButton:pressed{background-color:rgb(85, 170, 255);\
              border-style: inset; }");*/

    this->setStyleSheet("QWidget{padding-left:10px;padding-right:10px;background-color:rgba(0, 255, 0, 20%);border:0px solid red;}"
                        "QPushButton{font-size:20px;color:white;background-color:rgb(128,0,255);min-width:50px;max-width:50px;}"
                        "QPushButton:hover{background-color:rgb(128,0,128);}"
                        "QPushButton:pressed{background-color:rgb(85,170,255);}");

    m_lUserName->setStyleSheet("QLabel{font-size:15px;color:white;font-family:Microsoft YaHei;max-height:20px;min-height:20px;}");
    m_lUserTime->setStyleSheet("QLabel{font-size:15px;color:white;font-family:Microsoft YaHei;}");
}

void CToolStatusView::showMain()
{

}

void CToolStatusView::mouseReleaseEvent(QMouseEvent *event)
{
}

void CToolStatusView::mouseMoveEvent(QMouseEvent *event)
{
}

void CToolStatusView::btnLogoutClicked()
{
    //QMessageBox::information(NULL, "Title", "Content");
    qApp->quit();
}

void CToolStatusView::btnTest1Clicked()
{
    funcTest();
    timerTest();
    vsSdkTest();
}

//////////////////////////////////////////////////////////////////////////
//
void CToolStatusView::setUserTimer()
{
    QString strTemp = "";
    m_lUserTime->setText(QDateTime::currentDateTime().toString("MM月dd日 dddd hh:mm:ss") + strTemp);
}

void CToolStatusView::slotInit(std::string s1)
{
    printf("test1");
}

void CToolStatusView::funcTest()
{
    CFuncTest test1;
    test1.tuple_test();
    test1.string_test();
}

void CToolStatusView::timerTest()
{
    /*QTimer timer;
    timer.setSingleShot(true);
    QObject::connect(&timer, &QTimer::timeout, [this]{slotInit();});
    timer.start(3000);*/

    std::string s1 = "this is a test!";
    QTimer::singleShot(300, this, [&, s1]{
        slotInit(s1);
    });
}

void CToolStatusView::vsSdkTest()
{
}
