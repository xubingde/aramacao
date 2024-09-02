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
        m_projectDir(),
        m_docmentEdit(nullptr)
{
    m_projectName = new QLineEdit;
    m_projectDir = new QLineEdit;
    m_docmentEdit = new QTextEdit;
    new Highlighter(m_docmentEdit->document());

    connect(m_projectName, &QLineEdit::editingFinished,
            this, &WtProject::projectName_editingFinished);
    connect(m_projectDir, &QLineEdit::editingFinished,
            this, &WtProject::projectDir_editingFinished);
    connect(m_docmentEdit, &QTextEdit::textChanged,
            this, &WtProject::docmentEdit_textChanged);

    QVBoxLayout *  vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);

    QFormLayout *  fm0 = new QFormLayout;
    QFormLayout *  fm1 = new QFormLayout;
    QHBoxLayout *  hbox1 = new QHBoxLayout;
    fm0->setContentsMargins(0, 0, 0, 0);
    fm1->setContentsMargins(0, 0, 0, 0);
    hbox1->setContentsMargins(0, 0, 0, 0);
    vbox->addLayout(fm0);
    vbox->addLayout(fm1);
    vbox->addLayout(hbox1);

    QLabel *  label0 = new QLabel(tr(" Project Name "));
    QLabel *  label1 = new QLabel(tr(" Project Dir  "));
    fm0->addRow(label0, m_projectName);
    fm1->addRow(label1, m_projectDir);
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
WtProject::projectDir_editingFinished()
{
    if (!m_objPtr)  return;

    std::string  currVal = m_projectDir->text().toUtf8().toStdString();
    const std::string  oldVal = m_objPtr->getDir();
    if (currVal != oldVal) {
        const size_t  size = currVal.size();
        if (size > 0 && currVal[size - 1] != '\\') {
            currVal += "\\";
        }
        m_objPtr->setDir(currVal);

        const std::string  newVal = m_objPtr->getDir();
        m_projectDir->setText(QString::fromStdString(newVal));
    }
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
        m_projectName->setText(QString::fromStdString(m_objPtr->getProjectName()));
        m_projectDir->setText(QString::fromStdString(m_objPtr->getDir()));
        m_docmentEdit->setText(QString::fromStdString(m_objPtr->getDocment()));
    }
}

}
