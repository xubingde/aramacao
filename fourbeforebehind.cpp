#include <typeinfo>
#include <QVBoxLayout>
#include <QFrame>
#include <QTextDocument>
#include <QSplitter>
#include "highlighter.h"
#include "fourbeforebehind.h"

namespace xu {

FourBeforeBehind::FourBeforeBehind(const std::string &  title,
                                   const QString &  beforeFirstLabel,
                                   const QString &  behindFirstLabel,
                                   std::string &  beforeFirst,
                                   std::string &  behindFirst,
                                   const QString &  beforeSecondLabel,
                                   const QString &  behindSecondLabel,
                                   std::string &  beforeSecond,
                                   std::string &  behindSecond,
                                   QWidget *  parent /* = nullptr */):
        QDialog(parent),
        m_titleLabel(nullptr),
        m_beforeFirst(beforeFirst),
        m_behindFirst(behindFirst),
        m_beforeFirstEdit(nullptr),
        m_behindFirstEdit(nullptr),
        m_beforeSecond(beforeSecond),
        m_behindSecond(behindSecond),
        m_beforeSecondEdit(nullptr),
        m_behindSecondEdit(nullptr),
        m_buttonBox(nullptr)
{
    resize(800, 600);

    m_titleLabel = new QLabel;
    m_titleLabel->setText(QString::fromStdString(title));

    m_beforeFirstEdit = new CodeEditor;
    new Highlighter(m_beforeFirstEdit->document());
    m_behindFirstEdit = new CodeEditor;
    new Highlighter(m_behindFirstEdit->document());
    m_beforeSecondEdit = new CodeEditor;
    new Highlighter(m_beforeSecondEdit->document());
    m_behindSecondEdit = new CodeEditor;
    new Highlighter(m_behindSecondEdit->document());

    m_beforeFirstEdit->setPlainText(QString::fromStdString(beforeFirst));
    m_behindFirstEdit->setPlainText(QString::fromStdString(behindFirst));
    m_beforeSecondEdit->setPlainText(QString::fromStdString(beforeSecond));
    m_behindSecondEdit->setPlainText(QString::fromStdString(behindSecond));

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    connect(m_beforeFirstEdit, &CodeEditor::textChanged,
            this, &FourBeforeBehind::beforeFirstEdit_textChanged);
    connect(m_behindFirstEdit, &CodeEditor::textChanged,
            this, &FourBeforeBehind::behindFirstEdit_textChanged);
    connect(m_beforeSecondEdit, &CodeEditor::textChanged,
            this, &FourBeforeBehind::beforeSecondEdit_textChanged);
    connect(m_behindSecondEdit, &CodeEditor::textChanged,
            this, &FourBeforeBehind::behindSecondEdit_textChanged);

    QVBoxLayout *  tlvb = new QVBoxLayout(this);
    tlvb->setContentsMargins(0, 0, 0, 0);

    tlvb->addWidget(m_titleLabel);
    QFrame *  tlvline = new QFrame;
    tlvline->setFrameStyle(QFrame::HLine | QFrame::Plain);
    tlvline->setLineWidth(1);
    tlvb->addWidget(tlvline);

    QSplitter *  fna = new QSplitter(Qt::Vertical);
    fna->setHandleWidth(1);
    tlvb->addWidget(fna);

    QFrame *  qf1 = new QFrame;
    QFrame *  qf2 = new QFrame;
    QFrame *  qf3 = new QFrame;
    QFrame *  qf4 = new QFrame;
    QFrame *  qf5 = new QFrame;
    fna->addWidget(qf1);
    fna->addWidget(qf2);
    fna->addWidget(qf3);
    fna->addWidget(qf4);
    fna->addWidget(qf5);

    fna->setStretchFactor(0, 25);
    fna->setStretchFactor(1, 25);
    fna->setStretchFactor(2, 25);
    fna->setStretchFactor(3, 25);
    fna->setStretchFactor(4, 2);

    QVBoxLayout *  tlvb_1 = new QVBoxLayout(qf1);
    QVBoxLayout *  tlvb_2 = new QVBoxLayout(qf2);
    QVBoxLayout *  tlvb_3 = new QVBoxLayout(qf3);
    QVBoxLayout *  tlvb_4 = new QVBoxLayout(qf4);
    QVBoxLayout *  tlvb_5 = new QVBoxLayout(qf5);
    tlvb_1->setContentsMargins(0, 0, 0, 0);
    tlvb_2->setContentsMargins(0, 0, 0, 0);
    tlvb_3->setContentsMargins(0, 0, 0, 0);
    tlvb_4->setContentsMargins(0, 0, 0, 0);
    tlvb_5->setContentsMargins(10, 5, 10, 10);

    QLabel *  lbBeforeFirstLabel = new QLabel(beforeFirstLabel);
    QLabel *  lbBehindFirstLabel = new QLabel(behindFirstLabel);
    QLabel *  lbBeforeSecondLabel = new QLabel(beforeSecondLabel);
    QLabel *  lbBehindSecondLabel = new QLabel(behindSecondLabel);

    tlvb_1->addWidget(lbBeforeFirstLabel);
    tlvb_1->addWidget(m_beforeFirstEdit);
    tlvb_2->addWidget(lbBehindFirstLabel);
    tlvb_2->addWidget(m_behindFirstEdit);
    tlvb_3->addWidget(lbBeforeSecondLabel);
    tlvb_3->addWidget(m_beforeSecondEdit);
    tlvb_4->addWidget(lbBehindSecondLabel);
    tlvb_4->addWidget(m_behindSecondEdit);

    tlvb_5->addWidget(m_buttonBox);
}

FourBeforeBehind::~FourBeforeBehind() noexcept
{
}

void
FourBeforeBehind::beforeFirstEdit_textChanged()
{
    m_beforeFirst = m_beforeFirstEdit->toPlainText().toUtf8().toStdString();
}

void
FourBeforeBehind::behindFirstEdit_textChanged()
{
    m_behindFirst = m_behindFirstEdit->toPlainText().toUtf8().toStdString();
}

void
FourBeforeBehind::beforeSecondEdit_textChanged()
{
    m_beforeSecond = m_beforeSecondEdit->toPlainText().toUtf8().toStdString();
}

void
FourBeforeBehind::behindSecondEdit_textChanged()
{
    m_behindSecond = m_behindSecondEdit->toPlainText().toUtf8().toStdString();
}

}
