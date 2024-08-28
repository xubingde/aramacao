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
    std::string const  uiVal = m_codeEditor->toPlainText().toUtf8().toStdString();
    if (m_objPtr) {
        std::string const  dataVal = m_objPtr->getSourceCode();
        if (uiVal != dataVal) {
            m_codeEditor->setPlainText(QString::fromStdString(dataVal));
        }
    } else {
        if (uiVal.size() != 0)  m_codeEditor->clear();
    }
}

}
