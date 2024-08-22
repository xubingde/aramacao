#include <typeinfo>
#include <QVBoxLayout>
#include <QFrame>
#include <QTextDocument>
#include <QSplitter>
#include "highlighter.h"
#include "field.h"
#include "twobeforebehind.h"

namespace xu {

TwoBeforeBehind::TwoBeforeBehind(const std::string &  title,
                                 const QString &  beforeLabel,
                                 const QString &  behindLabel,
                                 std::string &  beforeString,
                                 std::string &  behindString,
                                 QWidget *  parent /* = nullptr */):
        QDialog(parent),
        m_titleLabel(nullptr),
        m_beforeString(beforeString),
        m_behindString(behindString),
        m_beforeEdit(nullptr),
        m_behindEdit(nullptr),
        m_buttonBox(nullptr)
{
    resize(800, 600);

    m_titleLabel = new QLabel;
    m_titleLabel->setText(QString::fromStdString(title));

    m_beforeEdit = new CodeEditor;
    new Highlighter(m_beforeEdit->document());
    m_behindEdit = new CodeEditor;
    new Highlighter(m_behindEdit->document());

    m_beforeEdit->setPlainText(QString::fromStdString(beforeString));
    m_behindEdit->setPlainText(QString::fromStdString(behindString));

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    connect(m_buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(m_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    connect(m_beforeEdit, &CodeEditor::textChanged,
            this, &TwoBeforeBehind::beforeEdit_textChanged);
    connect(m_behindEdit, &CodeEditor::textChanged,
            this, &TwoBeforeBehind::behindEdit_textChanged);

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
    QFrame *  qf5 = new QFrame;
    fna->addWidget(qf1);
    fna->addWidget(qf2);
    fna->addWidget(qf5);

    fna->setStretchFactor(0, 50);
    fna->setStretchFactor(1, 50);
    fna->setStretchFactor(2, 2);

    QVBoxLayout *  tlvb_1 = new QVBoxLayout(qf1);
    QVBoxLayout *  tlvb_2 = new QVBoxLayout(qf2);
    QVBoxLayout *  tlvb_5 = new QVBoxLayout(qf5);
    tlvb_1->setContentsMargins(0, 0, 0, 0);
    tlvb_2->setContentsMargins(0, 0, 0, 0);
    tlvb_5->setContentsMargins(10, 5, 10, 10);

    QLabel *  lbBeforeLabel = new QLabel(beforeLabel);
    QLabel *  lbBehindLabel = new QLabel(behindLabel);

    tlvb_1->addWidget(lbBeforeLabel);
    tlvb_1->addWidget(m_beforeEdit);
    tlvb_2->addWidget(lbBehindLabel);
    tlvb_2->addWidget(m_behindEdit);
    tlvb_5->addWidget(m_buttonBox);
}

TwoBeforeBehind::~TwoBeforeBehind() noexcept
{
}

void
TwoBeforeBehind::beforeEdit_textChanged()
{
    m_beforeString = m_beforeEdit->toPlainText().toUtf8().toStdString();
}

void
TwoBeforeBehind::behindEdit_textChanged()
{
    m_behindString = m_behindEdit->toPlainText().toUtf8().toStdString();
}

}
