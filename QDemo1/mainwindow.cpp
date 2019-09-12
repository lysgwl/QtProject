#include "mainwindow.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    createActions();
    createMenus();

    initProcessDialog();
    createToolbars();
    createStatusbars();
    createDockWindows();

    setWindowTitle("Wnd Test!");
}

MainWindow::~MainWindow()
{
}

//////////////////////////////////////////////////////////////////////////
//Actions
void MainWindow::createActions()
{
    createFileActions();
    createViewActions();
    createAdjustmentActions();

    createOcrActions();
    createLangActions();
    createWindowActions();
    createHelpActions();
}

void MainWindow::createFileActions()
{
    openAction = new QAction(tr("Open(&O)..."), this);
    openAction->setShortcut(QKeySequence::Open);

    screenshotAction = new QAction(tr("Screenshot(&X)..."), this);
    screenshotAction->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_X);

    saveAction = new QAction(tr("Save(&S)..."), this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setEnabled(false);

    printAction = new QAction(tr("Print(&P)..."), this);
    printAction->setShortcut(QKeySequence::Print);
    printAction->setEnabled(false);

    exitAction = new QAction(tr("Exit(&Q)"), this);
    exitAction->setShortcut(QKeySequence::Quit);
}

void MainWindow::createViewActions()
{
    zoomInAction = new QAction(tr("Zoom In"), this);
    zoomInAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Equal));
    zoomInAction->setEnabled(false);

    zoomOutAction = new QAction(tr("Zoom Out"), this);
    zoomOutAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Minus));
    zoomOutAction->setEnabled(false);

    zoomToWindowAction = new QAction(tr("Fit To Screen"), this);
    zoomToWindowAction->setShortcut(Qt::CTRL | Qt::Key_0);
    zoomToWindowAction->setEnabled(false);

    resetZoomAction = new QAction(tr("Actual Size"), this);
    resetZoomAction->setShortcut(Qt::CTRL | Qt::ALT | Qt::Key_0);
    resetZoomAction->setEnabled(false);
}

void MainWindow::createAdjustmentActions()
{
    deskewAction = new QAction(tr("Deskew"), this);

    grayscaleAction = new QAction(tr("Grayscale"), this);
}

void MainWindow::createOcrActions()
{
    ocrAction = new QAction(tr("Character Recognition"), this);
    ocrAction->setShortcut(Qt::CTRL | Qt::Key_E);

    downloadOCRLanguageDataAction = new QAction(tr("Download Language Data..."), this);
}

void MainWindow::createLangActions()
{}

void MainWindow::createWindowActions()
{}

void MainWindow::createHelpActions()
{
    aboutAction = new QAction(tr("About(&A)"), this);
}

//////////////////////////////////////////////////////////////////////////
//Menus
void MainWindow::createMenus()
{
    createFileMenus();
    createViewMenus();
    createAdjustmentMenus();

    createOcrMenus();
    createLanguageMenus();
    createWindowMenus();
    createHelpMenus();
}

void MainWindow::createFileMenus()
{
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
{
    viewMenu = new QMenu(tr("View(&V)"), this);
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addAction(zoomToWindowAction);
    viewMenu->addAction(resetZoomAction);

    menuBar()->addMenu(viewMenu);
}

void MainWindow::createAdjustmentMenus()
{
    adjustmentMenu = new QMenu(tr("Adjustments(&A)"), this);
    adjustmentMenu->addAction(deskewAction);
    adjustmentMenu->addAction(grayscaleAction);

    menuBar()->addMenu(adjustmentMenu);
}

void MainWindow::createOcrMenus()
{
    ocrMenu = new QMenu(tr("OCR(&O)"), this);
    ocrMenu->addAction(ocrAction);
    ocrMenu->addAction(downloadOCRLanguageDataAction);

    createOcrLanguagesMenu();
    createOcrPageSegModesMenu();
}

void MainWindow::createOcrLanguagesMenu()
{

}

void MainWindow::createOcrPageSegModesMenu()
{}

void MainWindow::createLanguageMenus()
{
    languagesMenu = new QMenu(tr("Languages(&L)"), this);
    menuBar()->addMenu(languagesMenu);
}

void MainWindow::createWindowMenus()
{
    windowMenu = new QMenu(tr("Window(&W)"), this);
    menuBar()->addMenu(windowMenu);
}

void MainWindow::createHelpMenus()
{
    helpMenu = new QMenu(tr("Help(&H)"), this);
    helpMenu->addAction(aboutAction);

    menuBar()->addMenu(helpMenu);
}

//////////////////////////////////////////////////////////////////////////
//
void MainWindow::initProcessDialog()
{
    moveImageToolButton = createToolButton(tr("Move Image"), "move_image");
}

void MainWindow::createToolbars()
{

}

void MainWindow::createStatusbars()
{

}

void MainWindow::createDockWindows()
{

}
