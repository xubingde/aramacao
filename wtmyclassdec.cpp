#include <typeinfo>
#include <QFrame>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSplitter>
#include "highlighter.h"
#include "wtmyclassdec.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

WtMyClassDec::WtMyClassDec(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_itemPtr(nullptr),
        m_myClassPtr(nullptr),
        m_beforeCode(nullptr),
        m_behindCode(nullptr),
        m_classNameEdit(nullptr)
{
    m_beforeCode = new CodeEditor;
    new Highlighter(m_beforeCode->document());
    m_behindCode = new CodeEditor;
    new Highlighter(m_behindCode->document());
    m_classNameEdit = new QLineEdit;

    connect(m_beforeCode, &CodeEditor::textChanged,
            this, &WtMyClassDec::beforeCode_textChanged);
    connect(m_behindCode, &CodeEditor::textChanged,
            this, &WtMyClassDec::behindCode_textChanged);
    connect(m_classNameEdit, &QLineEdit::editingFinished,
            this, &WtMyClassDec::classNameEdit_editingFinished);

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
    QLabel *  Llabel = new QLabel(tr(" Class Name "));
    fm0->addRow(Llabel, m_classNameEdit);
    fr->setLayout(fm0);

    vH->setStretchFactor(0, 45);
    vH->setStretchFactor(1, 10);
    vH->setStretchFactor(2, 45);
}

WtMyClassDec::~WtMyClassDec() noexcept
{
}

void
WtMyClassDec::beforeCode_textChanged()
{
    if (!m_objPtr || !m_itemPtr || !m_myClassPtr)  return;

    m_myClassPtr->setBeforeDcl(m_beforeCode->toPlainText().toUtf8().toStdString());
}

void
WtMyClassDec::behindCode_textChanged()
{
    if (!m_objPtr || !m_itemPtr || !m_myClassPtr)  return;

    m_myClassPtr->setBehindDcl(m_behindCode->toPlainText().toUtf8().toStdString());
}

void
WtMyClassDec::classNameEdit_editingFinished()
{
    if (!m_objPtr || !m_itemPtr)  return;

    m_objPtr->setClassName(m_classNameEdit->text().toUtf8().toStdString());
    QVariant  treeLabel(QString::fromStdString(m_objPtr->getTreeLabel()));
    m_itemPtr->setData(treeLabel, Qt::EditRole);

    QStandardItem *  parentItem = m_itemPtr->parent();
    int const  count = parentItem->rowCount();
    for (int  i = 0; i < count; ++i) {
        QStandardItem *  item = parentItem->child(i);
        Etype const  etp = static_cast<Etype>(item->data(
                Qt::UserRole + 1).toInt());
        if (etp == Etype::eClass) {
            MyClass *  ptr = static_cast<MyClass *>(item->data(
                    Qt::UserRole + 2).value<void *>());
            std::string const  cName = ptr->getClassName();
            if (m_objPtr->getClassName() == cName) {
                m_myClassPtr = ptr;
                m_beforeCode->setPlainText(QString::fromStdString(
                        ptr->getBeforeDcl()));
                m_behindCode->setPlainText(QString::fromStdString(
                        ptr->getBehindDcl()));
                break;
            } else {
                m_myClassPtr = nullptr;
            }
        }
    }
}

MyClassDec *
WtMyClassDec::getObjPtr() const
{
    return m_objPtr;
}

void
WtMyClassDec::setObjPtr(MyClassDec *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        m_classNameEdit->setText(QString::fromStdString(
                m_objPtr->getClassName()));
        if (!m_itemPtr)  return;

        QStandardItem *  parentItem = m_itemPtr->parent();
        int const  count = parentItem->rowCount();
        for (int  i = 0; i < count; ++i) {
            QStandardItem *  item = parentItem->child(i);
            Etype const  etp = static_cast<Etype>(item->data(
                    Qt::UserRole + 1).toInt());
            if (etp == Etype::eClass) {
                MyClass *  ptr = static_cast<MyClass *>(item->data(
                        Qt::UserRole + 2).value<void *>());
                std::string const  cName = ptr->getClassName();
                if (m_objPtr->getClassName() == cName) {
                    m_myClassPtr = ptr;
                    m_beforeCode->setPlainText(QString::fromStdString(
                            ptr->getBeforeDcl()));
                    m_behindCode->setPlainText(QString::fromStdString(
                            ptr->getBehindDcl()));
                    break;
                } else {
                    m_myClassPtr = nullptr;
                }
            }
        }
    }
}

QStandardItem *
WtMyClassDec::getItemPtr() const
{
    return m_itemPtr;
}

void
WtMyClassDec::setItemPtr(QStandardItem *  value)
{
    m_itemPtr = value;
}

}
