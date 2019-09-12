#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QLabel;
class QComboBox;
class QTextEdit;
class QToolButton;
class QScrollArea;
class QScrollBar;
class QActionGroup;
class QButtonGroup;
class QProgressDialog;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

public slots:

protected:
    void    createActions();
    void    createFileActions();
    void    createViewActions();
    void    createAdjustmentActions();
    void    createOcrActions();
    void    createLangActions();
    void    createWindowActions();
    void    createHelpActions();

protected:
    void    createMenus();
    void    createFileMenus();
    void    createViewMenus();
    void    createAdjustmentMenus();
    void    createOcrMenus();
    void    createOcrLanguagesMenu();
    void    createOcrPageSegModesMenu();
    void    createLanguageMenus();
    void    createWindowMenus();
    void    createHelpMenus();

protected:
    void    initProcessDialog();
    void    createToolbars();
    void    createStatusbars();
    void    createDockWindows();

protected:
    //action
    QAction *openAction;
    QAction *screenshotAction;
    QAction *saveAction;
    QAction *printAction;
    QAction *exitAction;

    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *zoomToWindowAction;
    QAction *resetZoomAction;

    QAction *deskewAction;
    QAction *grayscaleAction;

    QAction *ocrAction;
    QAction *downloadOCRLanguageDataAction;
    QAction *aboutAction;

    //menu
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *adjustmentMenu;

    QMenu *ocrMenu;
    QMenu *ocrLanguagesMenu;

    QMenu *languagesMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    //
    QToolBar *toolbar;

    QComboBox *ocrLanguagesComboBox;
    QToolButton *moveImageToolButton;
    QButtonGroup *pointerTypeButtonGroup;
};

#endif // MAINWINDOW_H
