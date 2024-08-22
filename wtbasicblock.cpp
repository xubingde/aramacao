#include <typeinfo>
#include <QHBoxLayout>
#include "wtbasicblock.h"
#include "highlighter.h"

namespace xu {

WtBasicBlock::WtBasicBlock(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_codeEditor(nullptr)
{
    m_codeEditor = new CodeEditor;
    m_codeEditor->setReadOnly(true);
    new Highlighter(m_codeEditor->document());

    connect(m_codeEditor, &CodeEditor::textChanged,
            this, &WtBasicBlock::codeEditor_textChanged);

    QHBoxLayout *  hbox = new QHBoxLayout;
    hbox->setContentsMargins(0, 0, 0, 0);
    this->setLayout(hbox);
    hbox->addWidget(m_codeEditor);
}

WtBasicBlock::~WtBasicBlock() noexcept
{
}

void
WtBasicBlock::codeEditor_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setSourceCode(m_codeEditor->toPlainText().toUtf8().toStdString());
}

BasicBlock *
WtBasicBlock::getObjPtr() const
{
    return m_objPtr;
}

void
WtBasicBlock::setObjPtr(BasicBlock *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        m_codeEditor->setReadOnly(false);
        m_codeEditor->setPlainText(QString::fromStdString(m_objPtr->getSourceCode()));
    } else {
        m_codeEditor->clear();
        m_codeEditor->setReadOnly(true);
    }
}

}
