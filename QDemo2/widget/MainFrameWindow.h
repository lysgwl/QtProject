#ifndef __MAINFRAME_WINDOW_H__
#define __MAINFRAME_WINDOW_H__

#include <QWidget>

QT_BEGIN_NAMESPACE
    namespace Ui { class Widget; }
QT_END_NAMESPACE

class CMainFrameWindow : public QWidget
{
    Q_OBJECT
public:
    CMainFrameWindow(QWidget *parent = nullptr);
    ~CMainFrameWindow();
	
public:
    void		initUI();

private slots:
    void on_btnOpen_pressed();

    void on_btnClose_pressed();

    void on_btnAudio1_pressed();

    void on_btnAudio2_pressed();

    void on_btnAudio3_pressed();

private:
    Ui::Widget  *ui;
};

#endif
