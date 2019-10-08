#include "mainwindow.h"
#include "imageview.h"
#include "ProcessDialog.h"

#include <QtGui>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>

#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QStatusBar>
#include <QDockWidget>

#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createActions();
    createMenus();

    createImageView();
    //initProcessDialog();

    createToolbars();
    createStatusbars();
    createDockWindows();

    setWindowTitle("");
}

MainWindow::~MainWindow()
{
}

//////////////////////////////////////////////////////////////////////////
//Actions 菜单
void MainWindow::createActions()
{//菜单
    createFileActions();
    createViewActions();
    createAdjustmentActions();

    createOcrActions();
    createLangActions();
    createWindowActions();
    createHelpActions();
}

void MainWindow::createFileActions()
{//文件
    //打开文件
    openAction = new QAction(tr("Open(&O)..."), this);
    openAction->setIcon(createIcon("open"));
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    //截屏
    screenshotAction = new QAction(tr("Screenshot(&X)..."), this);
    screenshotAction->setIcon(createIcon("screenshot"));
    screenshotAction->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_X);
    connect(screenshotAction, SIGNAL(triggered()), this, SLOT(screenshot()));

    //保存
    saveAction = new QAction(tr("Save(&S)..."), this);
    saveAction->setIcon(createIcon("save"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setEnabled(false);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    //打印
    printAction = new QAction(tr("Print(&P)..."), this);
    printAction->setIcon(createIcon("print"));
    printAction->setShortcut(QKeySequence::Print);
    printAction->setEnabled(false);
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

    //退出
    exitAction = new QAction(tr("Exit(&Q)"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createViewActions()
{//显示
    //放大
    zoomInAction = new QAction(tr("Zoom In"), this);
    zoomInAction->setIcon(createIcon("zoom_in"));
    zoomInAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Equal));
    zoomInAction->setEnabled(false);
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));

    //缩小
    zoomOutAction = new QAction(tr("Zoom Out"), this);
    zoomOutAction->setIcon(createIcon("zoom_out"));
    zoomOutAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Minus));
    zoomOutAction->setEnabled(false);
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));

    //按窗口大小显示
    zoomToWindowAction = new QAction(tr("Fit To Screen"), this);
    zoomToWindowAction->setIcon(createIcon("zoom_to_window"));
    zoomToWindowAction->setShortcut(Qt::CTRL | Qt::Key_0);
    zoomToWindowAction->setEnabled(false);
    connect(zoomToWindowAction, SIGNAL(triggered()), this, SLOT(zoomToWindow()));

    //实际大小
    resetZoomAction = new QAction(tr("Actual Size"), this);
    resetZoomAction->setIcon(createIcon("reset_zoom"));
    resetZoomAction->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_0);
    resetZoomAction->setEnabled(false);
    connect(resetZoomAction, SIGNAL(triggered()), this, SLOT(resetZoom()));
}

void MainWindow::createAdjustmentActions()
{//调整
    //校正
    deskewAction = new QAction(tr("Deskew"), this);
    connect(deskewAction, SIGNAL(triggered()), this, SLOT(deskew()));

    //灰度图
    grayscaleAction = new QAction(tr("Grayscale"), this);
    connect(grayscaleAction, SIGNAL(triggered()), this, SLOT(grayscale()));
}

void MainWindow::createOcrActions()
{//OCR
    //字符识别
    ocrAction = new QAction(tr("Character Recognition"), this);
    ocrAction->setIcon(createIcon("ocr"));
    ocrAction->setShortcut(Qt::CTRL | Qt::Key_E);
    connect(ocrAction, SIGNAL(triggered()), this, SLOT(ocr()));

    //下载数据
    downloadOCRLanguageDataAction = new QAction(tr("Download Language Data..."), this);
    connect(downloadOCRLanguageDataAction, SIGNAL(triggered()), this, SLOT(downloadOCRLanguageData()));
}

void MainWindow::createLangActions()
{//语音

}

void MainWindow::createWindowActions()
{//窗口

}

void MainWindow::createHelpActions()
{//帮助
    //关于
    aboutAction = new QAction(tr("About(&A)"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

//////////////////////////////////////////////////////////////////////////
//Menus 目录
void MainWindow::createMenus()
{//目录
    createFileMenus();
    createViewMenus();
    createAdjustmentMenus();

    createOcrMenus();
    createLanguageMenus();
    createWindowMenus();
    createHelpMenus();
}

void MainWindow::createFileMenus()
{//文件目录
    fileMenu = new QMenu(tr("File(&F)"), this);

    fileMenu->addAction(openAction);
    fileMenu->addAction(screenshotAction);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    menuBar()->addMenu(fileMenu);
}

void MainWindow::createViewMenus()
{//显示目录
    viewMenu = new QMenu(tr("View(&V)"), this);

    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addAction(zoomToWindowAction);
    viewMenu->addAction(resetZoomAction);

    menuBar()->addMenu(viewMenu);
}

void MainWindow::createAdjustmentMenus()
{//调整目录
    adjustmentMenu = new QMenu(tr("Adjustments(&A)"), this);

    adjustmentMenu->addAction(deskewAction);
    adjustmentMenu->addAction(grayscaleAction);

    menuBar()->addMenu(adjustmentMenu);
}

void MainWindow::createOcrMenus()
{//OCR目录
    ocrMenu = new QMenu(tr("OCR(&O)"), this);

    ocrMenu->addAction(ocrAction);
    ocrMenu->addAction(downloadOCRLanguageDataAction);

    createOcrLanguagesMenu();
    createOcrPageSegModesMenu();

    menuBar()->addMenu(ocrMenu);
}

void MainWindow::createOcrLanguagesMenu()
{
    ocrLanguagesMenu = new QMenu(tr("Languages(&L)"));
    ocrMenu->addMenu(ocrLanguagesMenu);


}

void MainWindow::createOcrPageSegModesMenu()
{
    ocrPageSegModesMenu = new QMenu(tr("Page Layout Analysis"));
    ocrMenu->addMenu(ocrPageSegModesMenu);
}

void MainWindow::createLanguageMenus()
{//语言目录
    languagesMenu = new QMenu(tr("Languages(&L)"), this);

    languagesActionGroup = new QActionGroup(this);

    menuBar()->addMenu(languagesMenu);
}

void MainWindow::createWindowMenus()
{//窗口目录
    windowMenu = new QMenu(tr("Window(&W)"), this);
    menuBar()->addMenu(windowMenu);
}

void MainWindow::createHelpMenus()
{//帮助目录
    helpMenu = new QMenu(tr("Help(&H)"), this);
    helpMenu->addAction(aboutAction);

    menuBar()->addMenu(helpMenu);
}

//////////////////////////////////////////////////////////////////////////
//
void MainWindow::createImageView()
{//业务窗口
    imageView = new ImageView();

    setCentralWidget(imageView);
}

void MainWindow::initProcessDialog()
{//预处理窗口
    progressDlg = new ProcessDialog(this, Qt::SplashScreen);

    progressDlg->setRange(0, 0);
    progressDlg->setWindowModality(Qt::WindowModal);
    progressDlg->setWindowTitle(tr("Please Wait"));
    progressDlg->setLabelText(tr("Optical Character Recognition......"));
    progressDlg->setCancelButton(nullptr);
    progressDlg->setMinimumWidth(300);
    progressDlg->setCursor(Qt::WaitCursor);
}

void MainWindow::createToolbars()
{//工具条
    moveImageToolButton = createToolButton(tr("Move Image"), tr("move_image"));
    moveImageToolButton->setCheckable(true);
    moveImageToolButton->setChecked(true);

    rectSelectionToolButton = createToolButton(tr("Rectangular Selection"), tr("rect_selection"));
    rectSelectionToolButton->setCheckable(true);

    pointerTypeButtonGroup = new QButtonGroup(this);
    pointerTypeButtonGroup->addButton(moveImageToolButton, int(1));
    pointerTypeButtonGroup->addButton(rectSelectionToolButton, int(2));
    connect(pointerTypeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(pointerGroupClicked(int)));

    toolbar = addToolBar("OCR Style Toolbar");
    toolbar->addAction(openAction);
    toolbar->addAction(screenshotAction);
    toolbar->addSeparator();
    toolbar->addAction(saveAction);
    toolbar->addAction(printAction);
    toolbar->addSeparator();
    toolbar->addWidget(moveImageToolButton);
    toolbar->addWidget(rectSelectionToolButton);
    toolbar->addSeparator();
    toolbar->addAction(zoomInAction);
    toolbar->addAction(zoomOutAction);
    toolbar->addAction(zoomToWindowAction);
    toolbar->addAction(resetZoomAction);
    toolbar->addSeparator();
    toolbar->addAction(ocrAction);
    toolbar->addWidget(new QLabel(tr(" OCR Languages ")));

    ocrLanguagesComboBox = new QComboBox(toolbar);
    toolbar->addWidget(ocrLanguagesComboBox);
    connect(ocrLanguagesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectedOcrLanguageWithIndex(int)));

    updateOcrComboBox();
}

void MainWindow::createStatusbars()
{//状态条
    statusBar()->addWidget(new QLabel(""));
}

void MainWindow::createDockWindows()
{//Dock窗口
    createDockWndOcrResult();
}

void MainWindow::createDockWndOcrResult()
{
    QDockWidget *dockWnd = new QDockWidget(tr("OCR Result"), this);
    dockWnd->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    ocrResultWnd = new QTextEdit(dockWnd);
    dockWnd->setWidget(ocrResultWnd);
    addDockWidget(Qt::RightDockWidgetArea, dockWnd);

    windowMenu->addAction(dockWnd->toggleViewAction());
}

void MainWindow::updateOcrComboBox()
{
    ocrLanguagesComboBox->clear();
}

void MainWindow::updateActions()
{
    printAction->setEnabled(true);
    zoomToWindowAction->setEnabled(true);

    zoomInAction->setEnabled(!zoomToWindowAction->isChecked());
    zoomOutAction->setEnabled(!zoomToWindowAction->isChecked());
    resetZoomAction->setEnabled(!zoomToWindowAction->isChecked());
}

//////////////////////////////////////////////////////////////////////////
//
QIcon MainWindow::createIcon(const QString &strIconName)
{
    QIcon icon;

    icon.addFile(QString(":images/res/images/16/")+strIconName+".png", QSize(16,16));
    icon.addFile(QString(":images/res/images/32/")+strIconName+".png", QSize(32, 32));

    return icon;
}

QToolButton* MainWindow::createToolButton(const QString &strText, const QString &strIconName)
{
    QToolButton *pToolButton = new QToolButton();

    pToolButton->setText(strText);
    pToolButton->setIcon(createIcon(strIconName));
    pToolButton->setCheckable(true);

    return pToolButton;
}

void MainWindow::loadImage()
{
    QImage image(m_filename);
    if (image.isNull())
    {
        QMessageBox::information(this, "Wnd", tr("loadImage failed! %1.").arg(m_filename));
        return;
    }

    pixmap = QPixmap::fromImage(image, nullptr);
    showImage(pixmap);
}

void MainWindow::showImage(const QPixmap &pixmap)
{
    imageView->showImage(pixmap);

    updateActions();

    if (!zoomToWindowAction->isChecked())
    {
        zoomToWindow();
    }
}

void MainWindow::saveScreenShot(QPixmap &pixmap)
{
	
}

void MainWindow::imageDeskew()
{

}

void MainWindow::imageGrayscale()
{

}

//////////////////////////////////////////////////////////////////////////
//
void MainWindow::open()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(),
            "All Files (*.jpg;*.jpeg;*.jpe;*.jfif;*.tif;*.tiff;*.png;*.gif);;JPEG (*.jpg;*.jpeg;*.jpe;*.jfif);;TIFF (*.tif;*.tiff);;PNG (*.png);;GIF (*.gif)");

    if (filename.isEmpty())
    {
        return;
    }

    m_filename = filename;
    loadImage();
}

void MainWindow::screenshot()
{
	hide();
    QTimer::singleShot(0, this, SLOT(onTimerScreenShot()));
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(), tr("Text (*.txt)"));

    if (fileName.isEmpty())
    {
        return;
    }
}

void MainWindow::print()
{
}

void MainWindow::zoomIn()
{
    imageView->zoomIn();
}

void MainWindow::zoomOut()
{
    imageView->zoomOut();
}

void MainWindow::resetZoom()
{
	imageView->resetZoom();
}

void MainWindow::zoomToWindow()
{
    double viewWidth = imageView->width();
	double viewHeight = imageView->height();
	
	double imageWidth = pixmap.width();
	double imageHeight = pixmap.height();
	
	double widthScaleFactor = imageWidth/viewWidth;
	double heightScaleFactor = imageHeight/viewHeight;
	
	double maxScaleFactor = std::max(widthScaleFactor, heightScaleFactor);
	double minScaleFactor = std::min(widthScaleFactor, heightScaleFactor);
	
	double scaleFactor = maxScaleFactor/minScaleFactor;
	if (widthScaleFactor < heightScaleFactor)
		imageView->fitInView(0, 0, imageWidth*scaleFactor, imageHeight);
	else
		imageView->fitInView(0, 0, imageWidth, imageHeight*scaleFactor);
}

void MainWindow::deskew()
{
	imageView->setCursor(Qt::WaitCursor);

    imageDeskew();
	loadImage();

	imageView->unsetCursor();
}

void MainWindow::grayscale()
{
    imageView->setCursor(Qt::WaitCursor);

    imageGrayscale();
    loadImage();

    imageView->unsetCursor();
}

void MainWindow::ocr()
{
    progressDlg->show();
    progressDlg->exec();
}

void MainWindow::downloadOCRLanguageData()
{}

void MainWindow::about()
{

}

void MainWindow::onTimerScreenShot()
{
    while (true)
    {
        if (isHidden())
        {
            qApp->beep();
            QThread::msleep(500);

            QScreen *screen = QGuiApplication::primaryScreen();

            pixmap = screen->grabWindow(0);
            //pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());

            saveScreenShot(pixmap);
            showImage(pixmap);

            show();
            break;
        }

        QThread::msleep(0);
    }
}

void MainWindow::pointerGroupClicked(int pointerType)
{
    if (pointerType == 1)
    {
        imageView->setMoveImageState(true);
    }
    else if (pointerType == 2)
    {
        imageView->setMoveImageState(false);
    }
}
