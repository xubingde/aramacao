#include <typeinfo>
#include <QFrame>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSplitter>
#include "wtlabel.h"
#include "highlighter.h"

namespace xu {

WtLabel::WtLabel(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_itemPtr(nullptr),
        m_beforeCode(nullptr),
        m_behindCode(nullptr),
        m_labelValueEdit(nullptr)
{
    m_beforeCode = new CodeEditor;
    m_beforeCode->setReadOnly(true);
    new Highlighter(m_beforeCode->document());
    m_behindCode = new CodeEditor;
    m_behindCode->setReadOnly(true);
    new Highlighter(m_behindCode->document());
    m_labelValueEdit = new QLineEdit;
    m_labelValueEdit->setReadOnly(true);

    connect(m_beforeCode, &CodeEditor::textChanged,
            this, &WtLabel::beforeCode_textChanged);
    connect(m_behindCode, &CodeEditor::textChanged,
            this, &WtLabel::behindCode_textChanged);
    connect(m_labelValueEdit, &QLineEdit::editingFinished,
            this, &WtLabel::labelValueEdit_editingFinished);

    QVBoxLayout *  vbox = new QVBoxLayout;
    vbox->setContentsMargins(0, 0, 0, 0);
    this->setLayout(vbox);

    QHBoxLayout *  hbox1 = new QHBoxLayout;
    QHBoxLayout *  hbox2 = new QHBoxLayout;
    hbox1->setContentsMargins(0, 0, 0, 0);
    hbox2->setContentsMargins(0, 0, 0, 0);

    QFormLayout *  fm0 = new QFormLayout;
    fm0->setContentsMargins(0, 0, 0, 0);
    QLabel *  Llabel = new QLabel(tr(" Label Value "));
    fm0->addRow(Llabel, m_labelValueEdit);

    vbox->addLayout(hbox1);
    vbox->addLayout(fm0);
    vbox->addLayout(hbox2);

    hbox1->addWidget(m_beforeCode);
    hbox2->addWidget(m_behindCode);
}

WtLabel::~WtLabel() noexcept
{
}

void
WtLabel::beforeCode_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setBefore(m_beforeCode->toPlainText().toUtf8().toStdString());
}

void
WtLabel::behindCode_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setBehind(m_behindCode->toPlainText().toUtf8().toStdString());
}

void
WtLabel::labelValueEdit_editingFinished()
{
    if (!m_objPtr || !m_itemPtr)  return;

    m_objPtr->setLabelValue(m_labelValueEdit->text().toUtf8().toStdString());
    QVariant  treeLabel(QString::fromStdString(m_objPtr->getTreeLabel()));
    m_itemPtr->setData(treeLabel, Qt::EditRole);
}

Label *
WtLabel::getObjPtr() const
{
    return m_objPtr;
}

void
WtLabel::setObjPtr(Label *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        m_beforeCode->setReadOnly(false);
        m_behindCode->setReadOnly(false);
        m_labelValueEdit->setReadOnly(false);

        m_beforeCode->setPlainText(QString::fromStdString(m_objPtr->getBefore()));
        m_behindCode->setPlainText(QString::fromStdString(m_objPtr->getBehind()));
        m_labelValueEdit->setText(QString::fromStdString(m_objPtr->getLabelValue()));
    } else {
        m_beforeCode->clear();
        m_behindCode->clear();
        m_labelValueEdit->clear();

        m_beforeCode->setReadOnly(true);
        m_behindCode->setReadOnly(true);
        m_labelValueEdit->setReadOnly(true);
    }
}

QStandardItem *
WtLabel::getItemPtr() const
{
    return m_itemPtr;
}

void
WtLabel::setItemPtr(QStandardItem *  value)
{
    m_itemPtr = value;
}

}
