#if defined(_MSC_VER)
#  pragma execution_character_set("utf-8")
#endif

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QTextCharFormat>
#include <QSpinBox>
#include <QFontComboBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QStyle>

static QString U8(const char *s) { return QString::fromUtf8(s); }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent)
    {
        setWindowTitle("QWMainWind");
        resize(800, 500);

        m_edit = new QTextEdit(this);
        setCentralWidget(m_edit);

        QStyle *style = this->style();

        actNew = new QAction(style->standardIcon(QStyle::SP_FileIcon), U8("新建"), this);
        actNew->setShortcut(tr("Ctrl+N"));
        connect(actNew, &QAction::triggered, this, [=]{ m_edit->clear(); });

        actAbout = new QAction(style->standardIcon(QStyle::SP_MessageBoxInformation),
                               U8("关于"), this);
        connect(actAbout, &QAction::triggered, this, &MainWindow::onAbout);

        actOpen = new QAction(style->standardIcon(QStyle::SP_DialogOpenButton), U8("打开"), this);
        actOpen->setShortcut(tr("Ctrl+O"));
        connect(actOpen, &QAction::triggered, this, &MainWindow::onOpen);

        actClear = new QAction(style->standardIcon(QStyle::SP_DialogResetButton), U8("清空"), this);
        connect(actClear, &QAction::triggered, this, [=]{ m_edit->clear(); });

        actCut = new QAction(style->standardIcon(QStyle::SP_DialogCancelButton), U8("剪切"), this);
        actCut->setShortcut(tr("Ctrl+X"));
        connect(actCut, &QAction::triggered, m_edit, &QTextEdit::cut);

        actCopy = new QAction(style->standardIcon(QStyle::SP_FileDialogDetailedView), U8("复制"), this);
        actCopy->setShortcut(tr("Ctrl+C"));
        connect(actCopy, &QAction::triggered, m_edit, &QTextEdit::copy);

        actPaste = new QAction(style->standardIcon(QStyle::SP_FileDialogNewFolder), U8("粘贴"), this);
        actPaste->setShortcut(tr("Ctrl+V"));
        connect(actPaste, &QAction::triggered, m_edit, &QTextEdit::paste);

        actItalic = new QAction(style->standardIcon(QStyle::SP_FileDialogContentsView), U8("斜体"), this);
        actItalic->setCheckable(true);
        connect(actItalic, &QAction::triggered, this, [=]{
            QTextCharFormat f;
            f.setFontItalic(actItalic->isChecked());
            m_edit->mergeCurrentCharFormat(f);
        });

        actBold = new QAction(style->standardIcon(QStyle::SP_ComputerIcon), U8("粗体"), this);
        actBold->setCheckable(true);
        connect(actBold, &QAction::triggered, this, [=]{
            QTextCharFormat f;
            f.setFontWeight(actBold->isChecked() ? QFont::Bold : QFont::Normal);
            m_edit->mergeCurrentCharFormat(f);
        });

        actUnderline = new QAction(style->standardIcon(QStyle::SP_DesktopIcon), U8("下划线"), this);
        actUnderline->setCheckable(true);
        connect(actUnderline, &QAction::triggered, this, [=]{
            QTextCharFormat f;
            f.setFontUnderline(actUnderline->isChecked());
            m_edit->mergeCurrentCharFormat(f);
        });

        QMenuBar *mb = menuBar();
        QMenu *mf = mb->addMenu(U8("文件"));
        mf->addAction(actNew);
        mf->addAction(actOpen);
        mf->addAction(actClear);
        QMenu *me = mb->addMenu(U8("编辑"));
        me->addAction(actCut);
        me->addAction(actCopy);
        me->addAction(actPaste);
        QMenu *mF = mb->addMenu(U8("格式"));
        mF->addAction(actItalic);
        mF->addAction(actBold);
        mF->addAction(actUnderline);
        QMenu *mh = mb->addMenu(U8("帮助"));
        mh->addAction(actAbout);

        QToolBar *tb = addToolBar("main");
        tb->addAction(actNew);
        tb->addAction(actAbout);
        tb->addAction(actOpen);
        tb->addAction(actClear);
        tb->addSeparator();
        tb->addAction(actCut);
        tb->addAction(actCopy);
        tb->addAction(actPaste);
        tb->addSeparator();
        tb->addAction(actItalic);
        tb->addAction(actBold);
        tb->addAction(actUnderline);
        tb->addSeparator();

        m_fontCombo = new QFontComboBox(this);
        tb->addWidget(m_fontCombo);
        connect(m_fontCombo, &QFontComboBox::currentFontChanged, this, [=](const QFont &f){
            QTextCharFormat fmt;
            fmt.setFontFamily(f.family());
            m_edit->mergeCurrentCharFormat(fmt);
        });
        tb->addSeparator();

        tb->addWidget(new QLabel(U8("字体大小 "), this));
        m_spinSize = new QSpinBox(this);
        m_spinSize->setRange(6, 72);
        m_spinSize->setValue(16);
        tb->addWidget(m_spinSize);
        connect(m_spinSize, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int s){
            QTextCharFormat fmt;
            fmt.setFontPointSize(s);
            m_edit->mergeCurrentCharFormat(fmt);
        });

        statusBar()->showMessage(U8("就绪"));
    }

private slots:
    void onAbout()
    {
        // ★ 只改下面两行引号里的中文
        QString name = U8("刘文果");
        QString sid  = U8("2023xxxxxx");

        QMessageBox::about(this, "samp2_4",
                           U8("开发人员信息：%1\n学号：%2").arg(name, sid));
    }

    void onOpen()
    {
        QString fn = QFileDialog::getOpenFileName(this,
                                                  U8("打开"), "",
                                                  U8("文本文件 (*.txt *.cpp *.h);;所有文件 (*.*)"));
        if (fn.isEmpty()) return;
        QFile f(fn);
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            m_edit->setPlainText(f.readAll());
            f.close();
        }
    }

private:
    QTextEdit     *m_edit       = nullptr;
    QSpinBox      *m_spinSize   = nullptr;
    QFontComboBox *m_fontCombo  = nullptr;
    QAction *actNew=nullptr, *actAbout=nullptr, *actOpen=nullptr, *actClear=nullptr,
                                                                            *actCut=nullptr, *actCopy=nullptr, *actPaste=nullptr,
                                                                                                                       *actItalic=nullptr, *actBold=nullptr, *actUnderline=nullptr;
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


