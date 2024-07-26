#include <QMainWindow>
#include "ProcessDialog.h"
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
QT_END_NAMESPACE

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
    void    saveimage();
    void    print();

    void    zoomIn();
    void    zoomOut();
	void    resetZoom();
    void    zoomToWindow();
    
    void    deskew();
    void    grayscale();

    void    ocr();
    void    downloadOCRLanguageData();
    void    about();

    void    onTimerScreenShot();
    void    pointerGroupClicked(int pointerType);

protected:
    void    createMenus();
    void    createFileMenus();
    void    createViewMenus();
    void    createAdjustmentMenus();
    void    createOcrMenus();
    void    createWindowMenus();
    void    createHelpMenus();

    void    createOcrLanguagesMenu(QMenu *pMenu);
    void    createOcrPageSegModesMenu(QMenu *pMenu);
    void    createDockWindows(QMenu *pMenu);

protected:
    void    createImageView();
    void    initProcessDialog();
    void    createToolbars();
    void    createStatusbars();
    void    updateOcrComboBox();
    void    updateActions();

protected:
    QIcon   createIcon(const QString &strIconName);
    QToolButton* createToolButton(const QString &strText, const QString &strIconName);

    void    showImage(const QPixmap &pixmap);

    void    imageDeskew();
    void    imageGrayscale();

protected:
    //
    QToolBar *toolbar;
    QTextEdit *ocrResultWnd;
    QComboBox *ocrLanguagesComboBox;

    QToolButton *moveImageToolButton;
    QToolButton *rectSelectionToolButton;
    QButtonGroup *pointerTypeButtonGroup;

protected:
	//QPrinter printer;
	QPixmap pixmap;

    ImageView *imageView;
    ProcessDialog *progressDlg;
};