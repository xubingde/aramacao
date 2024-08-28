#include <typeinfo>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "highlighter.h"
#include "wtproject.h"

namespace xu {

WtProject::WtProject(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_projectName(nullptr),
        m_docmentEdit(nullptr)
{
    m_projectName = new QLineEdit;
    m_projectName->setReadOnly(true);
    m_docmentEdit = new QTextEdit;
    new Highlighter(m_docmentEdit->document());
    m_docmentEdit->setReadOnly(true);

    connect(m_projectName, &QLineEdit::editingFinished,
            this, &WtProject::projectName_editingFinished);
    connect(m_docmentEdit, &QTextEdit::textChanged,
            this, &WtProject::docmentEdit_textChanged);

    QVBoxLayout *  vbox = new QVBoxLayout;
    vbox->setContentsMargins(0, 0, 0, 0);
    this->setLayout(vbox);

    QFormLayout *  fm0 = new QFormLayout;
    QHBoxLayout *  hbox1 = new QHBoxLayout;
    fm0->setContentsMargins(0, 0, 0, 0);
    hbox1->setContentsMargins(0, 0, 0, 0);
    vbox->addLayout(fm0);
    vbox->addLayout(hbox1);

    QLabel *  label0 = new QLabel(tr(" Project Name "));
    fm0->addRow(label0, m_projectName);
    hbox1->addWidget(m_docmentEdit);
}

WtProject::~WtProject() noexcept
{
}

void
WtProject::projectName_editingFinished()
{
    QStandardItem *  itemPtr = getItemPtr();
    if (!m_objPtr)  return;

    m_objPtr->setProjectName(m_projectName->text().toUtf8().toStdString());
    QVariant  treeLabel(QString::fromStdString(m_objPtr->getTreeLabel()));
    itemPtr->setData(treeLabel, Qt::EditRole);
}

void
WtProject::docmentEdit_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setDocment(m_docmentEdit->toHtml().toUtf8().toStdString());
}

Project *
WtProject::getObjPtr() const
{
    return m_objPtr;
}

void
WtProject::setObjPtr(Project *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        m_projectName->setReadOnly(false);
        m_docmentEdit->setReadOnly(false);

        m_projectName->setText(QString::fromStdString(m_objPtr->getProjectName()));
        m_docmentEdit->setText(QString::fromStdString(m_objPtr->getDocment()));
    } else {
        m_projectName->clear();
        m_docmentEdit->clear();

        m_projectName->setReadOnly(true);
        m_docmentEdit->setReadOnly(true);
    }
}

}
