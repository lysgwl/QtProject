#include "MainFrameWindow.h"
#include "ui_MainFrame.h"

#include <QtGui>

#include <QDebug>
#include <QPushButton>

CMainFrameWindow::CMainFrameWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

CMainFrameWindow::~CMainFrameWindow()
{
    delete ui;
}

void CMainFrameWindow::initUI()
{
}

void CMainFrameWindow::on_btnOpen_pressed()
{

}

void CMainFrameWindow::on_btnClose_pressed()
{

}

void CMainFrameWindow::on_btnAudio1_pressed()
{

}

void CMainFrameWindow::on_btnAudio2_pressed()
{

}

void CMainFrameWindow::on_btnAudio3_pressed()
{

}
