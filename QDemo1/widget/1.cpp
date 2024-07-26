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
    createImageView();
    createMenus();


    initProcessDialog();

    createToolbars();
    createStatusbars();

    setWindowTitle("");
}

MainWindow::~MainWindow()
{
}

//////////////////////////////////////////////////////////////////////////
//Menus 目录
void MainWindow::createMenus()
{//目录
    createFileMenus();
    createViewMenus();
    createAdjustmentMenus();

    createOcrMenus();
    createWindowMenus();
    createHelpMenus();
}

void MainWindow::createFileMenus()
{//文件目录
    QMenu *fileMenu;
    fileMenu = new QMenu(tr("File(&F)"), this);

    //打开文件
    QAction *openAction = new QAction(tr("Open(&O)..."), this);
    openAction->setIcon(createIcon("open"));
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    fileMenu->addAction(openAction);

    //截屏
    QAction *screenshotAction = new QAction(tr("Screenshot(&X)..."), this);
    screenshotAction->setIcon(createIcon("screenshot"));
    screenshotAction->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_X);
    connect(screenshotAction, SIGNAL(triggered()), this, SLOT(screenshot()));
    fileMenu->addAction(screenshotAction);

    fileMenu->addSeparator();

    //保存
    QAction *saveAction = new QAction(tr("Save(&S)..."), this);
    saveAction->setIcon(createIcon("save"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setEnabled(false);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
    fileMenu->addAction(saveAction);

    //保持图像
    QAction *saveImageAction = new QAction(tr("Save Image..."), this);
    saveImageAction->setIcon(createIcon("save"));
    saveImageAction->setEnabled(false);
    connect(saveImageAction, SIGNAL(triggered()), this, SLOT(saveimage()));
    fileMenu->addAction(saveImageAction);

    //打印
    QAction *printAction = new QAction(tr("Print(&P)..."), this);
    printAction->setIcon(createIcon("print"));
    printAction->setShortcut(QKeySequence::Print);
    printAction->setEnabled(false);
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));
    fileMenu->addAction(printAction);

    fileMenu->addSeparator();

    //退出
    QAction *exitAction = new QAction(tr("Exit(&Q)"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    fileMenu->addAction(exitAction);

    menuBar()->addMenu(fileMenu);
}

void MainWindow::createViewMenus()
{//显示目录
    QMenu *viewMenu;
    viewMenu = new QMenu(tr("View(&V)"), this);

    //放大
    QAction *zoomInAction = new QAction(tr("Zoom In"), this);
    zoomInAction->setIcon(createIcon("zoom_in"));
    zoomInAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Equal));
    zoomInAction->setEnabled(false);
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));
    viewMenu->addAction(zoomInAction);

    //缩小
    QAction *zoomOutAction = new QAction(tr("Zoom Out"), this);
    zoomOutAction->setIcon(createIcon("zoom_out"));
    zoomOutAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Minus));
    zoomOutAction->setEnabled(false);
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));
    viewMenu->addAction(zoomOutAction);

    //按窗口大小显示
    QAction *zoomToWindowAction = new QAction(tr("Fit To Screen"), this);
    zoomToWindowAction->setIcon(createIcon("zoom_to_window"));
    zoomToWindowAction->setShortcut(Qt::CTRL | Qt::Key_0);
    zoomToWindowAction->setEnabled(false);
    connect(zoomToWindowAction, SIGNAL(triggered()), this, SLOT(zoomToWindow()));
    viewMenu->addAction(zoomToWindowAction);

    //实际大小
    QAction *resetZoomAction = new QAction(tr("Actual Size"), this);
    resetZoomAction->setIcon(createIcon("reset_zoom"));
    resetZoomAction->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_0);
    resetZoomAction->setEnabled(false);
    connect(resetZoomAction, SIGNAL(triggered()), this, SLOT(resetZoom()));
    viewMenu->addAction(resetZoomAction);

    menuBar()->addMenu(viewMenu);
}

void MainWindow::createAdjustmentMenus()
{//调整目录
    QMenu *adjustmentMenu;
    adjustmentMenu = new QMenu(tr("Adjustments(&A)"), this);

    //校正
    QAction *deskewAction = new QAction(tr("Deskew"), this);
    connect(deskewAction, SIGNAL(triggered()), this, SLOT(deskew()));
    adjustmentMenu->addAction(deskewAction);

    //灰度图
    QAction *grayscaleAction = new QAction(tr("Grayscale"), this);
    connect(grayscaleAction, SIGNAL(triggered()), this, SLOT(grayscale()));
    adjustmentMenu->addAction(grayscaleAction);

    menuBar()->addMenu(adjustmentMenu);
}

void MainWindow::createOcrMenus()
{//OCR目录
    QMenu *ocrMenu;
    ocrMenu = new QMenu(tr("OCR(&O)"), this);

    //字符识别
    QAction *ocrAction = new QAction(tr("Character Recognition"), this);
    ocrAction->setIcon(createIcon("ocr"));
    ocrAction->setShortcut(Qt::CTRL | Qt::Key_E);
    connect(ocrAction, SIGNAL(triggered()), this, SLOT(ocr()));
    ocrMenu->addAction(ocrAction);

    //下载数据
    QAction *downloadOCRLanguageDataAction = new QAction(tr("Download Language Data..."), this);
    connect(downloadOCRLanguageDataAction, SIGNAL(triggered()), this, SLOT(downloadOCRLanguageData()));
    ocrMenu->addAction(downloadOCRLanguageDataAction);

    createOcrLanguagesMenu(ocrMenu);
    createOcrPageSegModesMenu(ocrMenu);

    menuBar()->addMenu(ocrMenu);
}

void MainWindow::createWindowMenus()
{//窗口目录
    QMenu *windowMenu;
    windowMenu = new QMenu(tr("Window(&W)"), this);
    menuBar()->addMenu(windowMenu);

    createDockWindows(windowMenu);
}

void MainWindow::createHelpMenus()
{//帮助目录
    QMenu *helpMenu;
    helpMenu = new QMenu(tr("Help(&H)"), this);

    //关于
    QAction *aboutAction = new QAction(tr("About(&A)"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    helpMenu->addAction(aboutAction);

    menuBar()->addMenu(helpMenu);
}

void MainWindow::createOcrLanguagesMenu(QMenu *pMenu)
{
    QMenu *ocrLanguagesMenu;
    ocrLanguagesMenu = new QMenu(tr("Languages(&L)"));
    //ocrMenu->addMenu(ocrLanguagesMenu);
}

void MainWindow::createOcrPageSegModesMenu(QMenu *pMenu)
{
    QMenu *ocrPageSegModesMenu;
    ocrPageSegModesMenu = new QMenu(tr("Page Layout Analysis"));
    //ocrMenu->addMenu(ocrPageSegModesMenu);
}

void MainWindow::createDockWindows(QMenu *pMenu)
{//Dock窗口
    QDockWidget *dockWnd = new QDockWidget(tr("OCR Result"), this);
    dockWnd->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    ocrResultWnd = new QTextEdit(dockWnd);
    dockWnd->setWidget(ocrResultWnd);
    addDockWidget(Qt::RightDockWidgetArea, dockWnd);

    pMenu->addAction(dockWnd->toggleViewAction());
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
#if 0
    progressDlg = new ProcessDialog(this, Qt::SplashScreen);

    progressDlg->setRange(0, 0);
    progressDlg->setWindowModality(Qt::WindowModal);
    progressDlg->setWindowTitle(tr("Please Wait"));
    progressDlg->setLabelText(tr("Optical Character Recognition......"));
    progressDlg->setCancelButton(nullptr);
    progressDlg->setMinimumWidth(300);
    progressDlg->setCursor(Qt::WaitCursor);
#endif

    progressDlg = nullptr;
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
#if 0
    toolbar = addToolBar("OCR Style Toolbar");
    toolbar->addAction(openAction);
    toolbar->addAction(screenshotAction);
    toolbar->addSeparator();
    toolbar->addAction(saveAction);
    toolbar->addAction(saveImageAction);
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
#endif
}

void MainWindow::createStatusbars()
{//状态条
    statusBar()->addWidget(new QLabel(""));
}

void MainWindow::updateOcrComboBox()
{
    ocrLanguagesComboBox->clear();
}

void MainWindow::updateActions()
{
#if 0
    saveImageAction->setEnabled(true);
    printAction->setEnabled(true);
    zoomToWindowAction->setEnabled(true);

    zoomInAction->setEnabled(!zoomToWindowAction->isChecked());
    zoomOutAction->setEnabled(!zoomToWindowAction->isChecked());
    resetZoomAction->setEnabled(!zoomToWindowAction->isChecked());
#endif
}

//////////////////////////////////////////////////////////////////////////
//
QIcon MainWindow::createIcon(const QString &strIconName)
{
    QIcon icon;

    icon.addFile(QString(":Images/res/images/16/")+strIconName+".png", QSize(16,16));
    icon.addFile(QString(":Images/res/images/32/")+strIconName+".png", QSize(32, 32));

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

void MainWindow::showImage(const QPixmap &pixmap)
{
    imageView->showImage(pixmap);

    updateActions();

    //if (!zoomToWindowAction->isChecked())
    {
        zoomToWindow();
    }
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

   QImage image(filename);
    if (image.isNull())
    {
        QMessageBox::information(this, "Wnd", tr("loadImage failed! %1.").arg(filename));
        return;
    }

    pixmap = QPixmap::fromImage(image, nullptr);
    showImage(pixmap);
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

    QFile file(fileName);
    if (file.open(QFile::WriteOnly))
    {
        QTextStream textStream(&file);
        textStream.setCodec("utf-8");
        file.close();
    }
}

void MainWindow::saveimage()
{
    if (pixmap.isNull())
    {
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(), tr("Images (*.bmp *.jpg *.png)"));
    if (fileName.isEmpty())
    {
        return;
    }

    pixmap.save(fileName);
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

	imageView->unsetCursor();
}

void MainWindow::grayscale()
{
    imageView->setCursor(Qt::WaitCursor);

    imageGrayscale();

    imageView->unsetCursor();
}

void MainWindow::ocr()
{
    if (progressDlg == nullptr)
        return;

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
            if (screen != nullptr)
            {
                pixmap = screen->grabWindow(0);
                //pixmap = QPixmap::grabWindow(QApplication::desktop()->winId());

                showImage(pixmap);
            }

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
