#include <typeinfo>
#include <QVBoxLayout>
#include <QSplitter>
#include <QLabel>
#include "wtprivatelabel.h"
#include "highlighter.h"

namespace xu {

WtPrivateLabel::WtPrivateLabel(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_beforeCode(nullptr),
        m_behindCode(nullptr)
{
    m_beforeCode = new CodeEditor;
    m_beforeCode->setReadOnly(true);
    new Highlighter(m_beforeCode->document());
    m_behindCode = new CodeEditor;
    m_behindCode->setReadOnly(true);
    new Highlighter(m_behindCode->document());

    connect(m_beforeCode, &CodeEditor::textChanged,
            this, &WtPrivateLabel::beforeCode_textChanged);
    connect(m_behindCode, &CodeEditor::textChanged,
            this, &WtPrivateLabel::behindCode_textChanged);

    QVBoxLayout *  vbox = new QVBoxLayout;
    vbox->setContentsMargins(0, 0, 0, 0);
    this->setLayout(vbox);

    QSplitter *  vH = new QSplitter(Qt::Vertical);
    vH->setHandleWidth(1);
    vbox->addWidget(vH);

    QLabel *  Llabel = new QLabel(tr(" private: "));

    vH->addWidget(m_beforeCode);
    vH->addWidget(Llabel);
    vH->addWidget(m_behindCode);
}

WtPrivateLabel::~WtPrivateLabel() noexcept
{
}

void
WtPrivateLabel::beforeCode_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setBefore(m_beforeCode->toPlainText().toUtf8().toStdString());
}

void
WtPrivateLabel::behindCode_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setBehind(m_behindCode->toPlainText().toUtf8().toStdString());
}

PrivateLabel *
WtPrivateLabel::getObjPtr() const
{
    return m_objPtr;
}

void
WtPrivateLabel::setObjPtr(PrivateLabel *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        m_beforeCode->setReadOnly(false);
        m_behindCode->setReadOnly(false);

        m_beforeCode->setPlainText(QString::fromStdString(m_objPtr->getBefore()));
        m_behindCode->setPlainText(QString::fromStdString(m_objPtr->getBehind()));
    } else {
        m_beforeCode->clear();
        m_behindCode->clear();

        m_beforeCode->setReadOnly(true);
        m_behindCode->setReadOnly(true);
    }
}

}
