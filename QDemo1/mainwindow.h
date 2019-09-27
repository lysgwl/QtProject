#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QKeyEvent>
#include <QProgressDialog>
//#include <QtPrintSupport/QPrinter>

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
class ImageView;
class QProgressDialog;
QT_END_NAMESPACE

class OCRProgressDialog : public QProgressDialog
{
    Q_OBJECT
public:
    explicit OCRProgressDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::Widget)
            : QProgressDialog(parent, flags)
        {
        }

protected:
    void keyPressEvent(QKeyEvent *event)
    {
        if(event->key() == Qt::Key_Escape)
            event->ignore();
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:

public slots:
    void    open();
    void    screenshot();
    void    save();
    void    print();

    void    zoomIn();
    void    zoomOut();
    void    zoomToWindow();
    void    resetZoom();

    void    deskew();
    void    grayscale();

    void    ocr();
    void    downloadOCRLanguageData();
    void    about();

   // void    pointerGroupClicked(int pointerType);

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
    void    createImageView();
    void    initProcessDialog();
    void    createToolbars();
    void    createStatusbars();
    void    createDockWindows();

    void    createDockWndOcrResult();
    void    updateOcrComboBox();

protected:
    QIcon   createIcon(const QString &strIconName);
    QToolButton* createToolButton(const QString &strText);

    void    loadImage();
    void    showImage(const QPixmap &pixmap);

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
    QMenu *ocrPageSegModesMenu;
    QMenu *languagesMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    //
    QToolBar *toolbar;
    QTextEdit *ocrResultWnd;
    QComboBox *ocrLanguagesComboBox;

    QToolButton *moveImageToolButton;
    QToolButton *rectSelectionToolButton;
    QButtonGroup *pointerTypeButtonGroup;

    QActionGroup *languagesActionGroup;

protected:
   // QPrinter printer;

    ImageView *imageView;
    OCRProgressDialog *progressDlg;

    QString m_filename;
};

#endif // MAINWINDOW_H
