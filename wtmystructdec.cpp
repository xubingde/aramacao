#include <typeinfo>
#include <QFrame>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSplitter>
#include "highlighter.h"
#include "eobject.h"
#include "mystruct.h"
#include "wtmystructdec.h"

namespace xu {

WtMyStructDec::WtMyStructDec(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_itemPtr(nullptr),
        m_beforeCode(nullptr),
        m_behindCode(nullptr),
        m_structNameEdit(nullptr)
{
    m_beforeCode = new CodeEditor;
    new Highlighter(m_beforeCode->document());
    m_beforeCode->setReadOnly(true);
    m_behindCode = new CodeEditor;
    new Highlighter(m_behindCode->document());
    m_behindCode->setReadOnly(true);
    m_structNameEdit = new QLineEdit;

    connect(m_beforeCode, &CodeEditor::textChanged,
            this, &WtMyStructDec::beforeCode_textChanged);
    connect(m_behindCode, &CodeEditor::textChanged,
            this, &WtMyStructDec::behindCode_textChanged);
    connect(m_structNameEdit, &QLineEdit::editingFinished,
            this, &WtMyStructDec::structNameEdit_editingFinished);

    QVBoxLayout *  vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);

    QSplitter *  vH = new QSplitter(Qt::Vertical);
    vH->setHandleWidth(1);
    vbox->addWidget(vH);

    QFrame *  fr = new QFrame;
    vH->addWidget(m_beforeCode);
    vH->addWidget(fr);
    vH->addWidget(m_behindCode);

    QFormLayout *  fm0 = new QFormLayout;
    fm0->setContentsMargins(5, 5, 5, 5);
    QLabel *  Llabel = new QLabel(tr(" Struct Name "));
    fm0->addRow(Llabel, m_structNameEdit);
    fr->setLayout(fm0);

    vH->setStretchFactor(0, 45);
    vH->setStretchFactor(1, 10);
    vH->setStretchFactor(2, 45);
}

WtMyStructDec::~WtMyStructDec() noexcept
{
}

void
WtMyStructDec::beforeCode_textChanged()
{
    if (!m_objPtr || !m_itemPtr)  return;

    updatePtr();
    std::string  before = m_beforeCode->toPlainText().toUtf8().toStdString();
    MyStruct *  cPtr = m_objPtr->getParentStructPtr();
    if (cPtr) {
        cPtr->setBeforeDcl(std::move(before));
    } else {
        if (before.size() != 0)  m_beforeCode->clear();
        m_beforeCode->setReadOnly(true);
    }
}

void
WtMyStructDec::behindCode_textChanged()
{
    if (!m_objPtr || !m_itemPtr)  return;

    updatePtr();
    std::string  behind = m_behindCode->toPlainText().toUtf8().toStdString();
    MyStruct *  cPtr = m_objPtr->getParentStructPtr();
    if (cPtr) {
        cPtr->setBehindDcl(std::move(behind));
    } else {
        if (behind.size() != 0)  m_behindCode->clear();
        m_behindCode->setReadOnly(true);
    }
}

void
WtMyStructDec::structNameEdit_editingFinished()
{
    if (!m_objPtr || !m_itemPtr)  return;

    m_objPtr->setStructName(m_structNameEdit->text().toUtf8().toStdString());
    QVariant  treeLabel(QString::fromStdString(m_objPtr->getTreeLabel()));
    m_itemPtr->setData(treeLabel, Qt::EditRole);

    updatePtr();
    std::string const  uiBefore = m_beforeCode->toPlainText().toUtf8().toStdString();
    std::string const  uiBehind = m_behindCode->toPlainText().toUtf8().toStdString();
    MyStruct *  cPtr = m_objPtr->getParentStructPtr();
    if (cPtr) {
        std::string const  dataBefore = cPtr->getBeforeDcl();
        std::string const  dataBehind = cPtr->getBehindDcl();
        m_beforeCode->setReadOnly(false);
        m_behindCode->setReadOnly(false);
        if (uiBefore != dataBefore) {
            m_beforeCode->setPlainText(QString::fromStdString(dataBefore));
        }
        if (uiBehind != dataBehind) {
            m_behindCode->setPlainText(QString::fromStdString(dataBehind));
        }
    } else {
        if (uiBefore.size() != 0)  m_beforeCode->clear();
        if (uiBehind.size() != 0)  m_behindCode->clear();
        m_beforeCode->setReadOnly(true);
        m_behindCode->setReadOnly(true);
    }
}

void
WtMyStructDec::updatePtr()
{
    if (!m_objPtr || !m_itemPtr)  return;

    QStandardItem *  parentItem = m_itemPtr->parent();
    int const  count = parentItem->rowCount();
    for (int  i = 0; i < count; ++i) {
        QStandardItem *  item = parentItem->child(i);
        Etype const  etp = static_cast<Etype>(item->data(
                Qt::UserRole + 1).toInt());
        if (etp == Etype::eStruct) {
            MyStruct *  ptr = static_cast<MyStruct *>(item->data(
                    Qt::UserRole + 2).value<void *>());
            std::string const  cName = ptr->getName();
            if (m_objPtr->getStructName() == cName) {
                m_objPtr->setParentStructPtr(ptr);
                break;
            } else {
                m_objPtr->setParentStructPtr(nullptr);
            }
        }
    }
}

MyStructDec *
WtMyStructDec::getObjPtr() const
{
    return m_objPtr;
}

void
WtMyStructDec::setObjPtr(MyStructDec *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        m_structNameEdit->setText(QString::fromStdString(
                m_objPtr->getStructName()));
        if (!m_itemPtr)  return;

        updatePtr();
        std::string const  uiBefore = m_beforeCode->toPlainText().
                toUtf8().toStdString();
        std::string const  uiBehind = m_behindCode->toPlainText().
                toUtf8().toStdString();
        MyStruct *  cPtr = m_objPtr->getParentStructPtr();
        if (cPtr) {
            std::string const  dataBefore = cPtr->getBeforeDcl();
            std::string const  dataBehind = cPtr->getBehindDcl();
            m_beforeCode->setReadOnly(false);
            m_behindCode->setReadOnly(false);
            if (uiBefore != dataBefore) {
                m_beforeCode->setPlainText(QString::fromStdString(dataBefore));
            }
            if (uiBehind != dataBehind) {
                m_behindCode->setPlainText(QString::fromStdString(dataBehind));
            }
        } else {
            if (uiBefore.size() != 0)  m_beforeCode->clear();
            if (uiBehind.size() != 0)  m_behindCode->clear();
            m_beforeCode->setReadOnly(true);
            m_behindCode->setReadOnly(true);
        }
    }
}

QStandardItem *
WtMyStructDec::getItemPtr() const
{
    return m_itemPtr;
}

void
WtMyStructDec::setItemPtr(QStandardItem *  value)
{
    m_itemPtr = value;
}

}
