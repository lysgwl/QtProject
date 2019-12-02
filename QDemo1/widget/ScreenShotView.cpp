#include "ScreenShotView.h"

CScreenShotView::CScreenShotView(QWidget *parent)
	: QWidget(parent)
{
    m_pSpinBox = nullptr;
    m_pCheckBox = nullptr;
    m_pScreenImageLabel = nullptr;

    m_pNewScreenShotBtn  = nullptr;
    m_pSaveScreenShotBtn = nullptr;
}

void CScreenShotView::initUI()
{
    QVBoxLayout *pLayout = new QVBoxLayout(this);
    if (pLayout != nullptr)
    {
        m_pScreenImageLabel = new QLabel(this);
        if (m_pScreenImageLabel != nullptr)
        {
           m_pScreenImageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
           m_pScreenImageLabel->setAlignment(Qt::AlignCenter);

           const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
           m_pScreenImageLabel->setMinimumSize(screenGeometry.width()/8, screenGeometry.height()/8);

           pLayout->addWidget(m_pScreenImageLabel);
        }

        QGroupBox *pGroupBox = new QGroupBox(tr("---"), this);
        if (pGroupBox != nullptr)
        {
            m_pSpinBox = new QSpinBox(pGroupBox);
            m_pSpinBox->setSuffix(tr("s"));
            m_pSpinBox->setMaximum(60);

            m_pCheckBox = new QCheckBox(tr("Hide Windows"), pGroupBox);
            QGridLayout *pGridLayout = new QGridLayout(pGroupBox);

            pGridLayout->addWidget(new QLabel(tr("Screenshot Delay:"), this), 0, 0);
            pGridLayout->addWidget(m_pSpinBox, 0, 1);
            pGridLayout->addWidget(m_pCheckBox, 1, 0, 1, 2);

            pLayout->addWidget(pGroupBox);
            m_pSpinBox->setValue(5);
        }
    }

    QHBoxLayout *pBtnLayout = new QHBoxLayout(this);
    if (pLayout != nullptr)
    {
        m_pNewScreenShotBtn = new QPushButton(tr("New Screen Shot"), this);
        connect(m_pNewScreenShotBtn, &QPushButton::clicked, this, &CScreenShotView::newScreenShot);
        pBtnLayout->addWidget(m_pNewScreenShotBtn);

        m_pSaveScreenShotBtn = new QPushButton(tr("Save Screen Shot"), this);
        connect(m_pSaveScreenShotBtn, &QPushButton::clicked, this, &CScreenShotView::saveScreenShot);
        pBtnLayout->addWidget(m_pSaveScreenShotBtn);

        QPushButton *pQuitScreenShotBtn = new QPushButton(tr("Quit"), this);
        connect(pQuitScreenShotBtn, &QPushButton::clicked, this, &QWidget::close);
        pBtnLayout->addWidget(pQuitScreenShotBtn);

        pBtnLayout->addStretch();
        pLayout->addLayout(pBtnLayout);
    }

    screenShot();
    show();
}

void CScreenShotView::resizeEvent(QResizeEvent *event)
{
    setWndLayout();
}

void CScreenShotView::setWndLayout()
{
    if (m_pScreenImageLabel == nullptr)
        return;

    QSize size = m_pixmap.size();
    size.scale(m_pScreenImageLabel->size(), Qt::KeepAspectRatio);

    if (!m_pScreenImageLabel->pixmap() || size != m_pScreenImageLabel->pixmap()->size())
        showImageLabel(m_pixmap);
}

void CScreenShotView::setWidgetCtrl(bool bFlag)
{
    if (bFlag)
    {
        if (m_pCheckBox->isChecked())
            hide();

        m_pNewScreenShotBtn->setDisabled(true);
        m_pSaveScreenShotBtn->setDisabled(true);
    }
    else
    {
        if (m_pCheckBox->isChecked())
            show();

        m_pNewScreenShotBtn->setDisabled(false);
        m_pSaveScreenShotBtn->setDisabled(false);
    }
}

void CScreenShotView::showImageLabel(QPixmap &pixmap)
{
    if (m_pScreenImageLabel == nullptr)
        return;

    if (pixmap.isNull())
        return;

    m_pScreenImageLabel->setPixmap(pixmap.scaled(m_pScreenImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void CScreenShotView::newScreenShot()
{
    int value = 0;

    if (m_pSpinBox != nullptr)
        value = m_pSpinBox->value();

    setWidgetCtrl(true);
    QTimer::singleShot(value*1000, this, &CScreenShotView::screenShot);
}

void CScreenShotView::saveScreenShot()
{
    const QString format = "png";

    QString strImagePath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (strImagePath.isEmpty())
        strImagePath = QDir::currentPath();
    strImagePath += tr("\\*.") + format;

    QFileDialog fileDialog(this, tr("Save As"), strImagePath);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setDirectory(strImagePath);

    QStringList mimeTypes;
    const QList<QByteArray> baMimeTypes = QImageWriter::supportedMimeTypes();
    for (const QByteArray &bf : baMimeTypes)
        mimeTypes.append(QLatin1String(bf));

    fileDialog.setMimeTypeFilters(mimeTypes);
    fileDialog.selectMimeTypeFilter("image/" + format);
    fileDialog.setDefaultSuffix(format);

    if (fileDialog.exec() != QDialog::Accepted)
        return;

    const QString fileName = fileDialog.selectedFiles().first();
    if (m_pixmap.isNull())
        return;

    m_pixmap.save(fileName);
}

void CScreenShotView::screenShot()
{
    QScreen *pScreen = QGuiApplication::primaryScreen();
    if (const QWindow *pWindow = windowHandle())
        pScreen = pWindow->screen();

    if (pScreen == nullptr)
        return;

    m_pixmap = pScreen->grabWindow(0);
    if (!m_pixmap.isNull())
    {
        showImageLabel(m_pixmap);
    }

    setWidgetCtrl(false);
}
