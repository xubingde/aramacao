#include <typeinfo>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSplitter>
#include <QAbstractScrollArea>
#include <QAction>
#include <QList>
#include "highlighter.h"
#include "wtautofnedit.h"
#include "defaultconstructorfn.h"
#include "copyconstructorfn.h"
#include "moveconstructorfn.h"
#include "destructorfn.h"
#include "copyoperatoreqfn.h"
#include "moveoperatoreqfn.h"
#include "eqfn.h"
#include "noteqfn.h"
#include "virtualeqfn.h"
#include "lessfn.h"
#include "lesseqfn.h"
#include "virtuallessfn.h"
#include "greaterfn.h"
#include "greatereqfn.h"
#include "extswapfn.h"
#include "inswapfn.h"
#include "virtualexchangefn.h"
#include "tostringfn.h"
#include "virtualserializefn.h"
#include "extfromstringfn.h"
#include "infromstringfn.h"
#include "deserializefn.h"

namespace xu {

WtAutoFnEdit::WtAutoFnEdit(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_functionDecLabel(nullptr),
        m_isDefault(nullptr),
        m_isDelete(nullptr),
        m_attribute(nullptr),
        m_beforBehindPb(nullptr),
        m_displayCode(nullptr),
        m_insertCode(nullptr),
        m_deleteIndexView(nullptr),
        m_deleteIndexModel(nullptr),
        m_insertIndexView(nullptr),
        m_insertIndexModel(nullptr)
{
    m_functionDecLabel = new QLabel;
    m_isDefault = new QCheckBox(tr(" = default"));
    m_isDelete = new QCheckBox(tr("= delete"));
    m_attribute = new QLineEdit;
    m_beforBehindPb = new QPushButton(tr(" Insert && Follow "));

    m_displayCode = new CodeEditor;
    new Highlighter(m_displayCode->document());
    m_displayCode->setReadOnly(true);
    m_insertCode = new CodeEditor;
    new Highlighter(m_insertCode->document());
    m_insertCode->setReadOnly(true);

    m_deleteIndexView = new QTableView;
    m_deleteIndexModel = new QStandardItemModel;
    m_deleteIndexModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Index")));
    m_deleteIndexView->setModel(m_deleteIndexModel);
    m_deleteIndexView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_insertIndexView = new QTableView;
    m_insertIndexModel = new QStandardItemModel;
    m_insertIndexModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Index")));
    m_insertIndexView->setModel(m_insertIndexModel);
    m_insertIndexView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(m_isDefault, &QCheckBox::stateChanged,
            this, &WtAutoFnEdit::isDefault_stateChanged);
    connect(m_isDelete, &QCheckBox::stateChanged,
            this, &WtAutoFnEdit::isDelete_stateChanged);
    connect(m_attribute, &QLineEdit::editingFinished,
            this, &WtAutoFnEdit::attribute_editingFinished);
    connect(m_beforBehindPb, &QPushButton::clicked,
            this, &WtAutoFnEdit::beforBehindPb_clicked);
    connect(m_insertCode, &CodeEditor::textChanged,
            this, &WtAutoFnEdit::insertCode_textChanged);

    insertIndexConnect();
    deleteIndexConnect();

    QVBoxLayout *  vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *  hbox1 = new QHBoxLayout;
    QHBoxLayout *  hbox2 = new QHBoxLayout;
    QHBoxLayout *  hbox3 = new QHBoxLayout;
    hbox1->setContentsMargins(0, 0, 0, 0);
    hbox2->setContentsMargins(0, 0, 0, 0);
    hbox3->setContentsMargins(0, 0, 0, 0);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);

    {
        QFormLayout *  fm0 = new QFormLayout;
        QHBoxLayout *  fm1 = new QHBoxLayout;
        QHBoxLayout *  fm2 = new QHBoxLayout;
        QHBoxLayout *  fm3 = new QHBoxLayout;
        fm0->setContentsMargins(0, 0, 0, 0);
        fm1->setContentsMargins(0, 0, 0, 0);
        fm2->setContentsMargins(0, 0, 0, 0);
        fm3->setContentsMargins(0, 0, 0, 0);
        hbox1->addLayout(fm0);
        hbox1->addLayout(fm1);
        hbox1->addLayout(fm2);
        hbox1->addLayout(fm3);

        QLabel *  attr = new QLabel(tr("Attribute"));
        fm0->addRow(attr, m_attribute);
        fm1->addWidget(m_isDefault);
        fm2->addWidget(m_isDelete);
        fm3->addWidget(m_beforBehindPb);
    }
    {
        QSplitter *  splitter = new QSplitter(Qt::Vertical);
        QSplitter *  spv1 = new QSplitter;
        QSplitter *  spv2 = new QSplitter;
        splitter->setHandleWidth(1);
        spv1->setHandleWidth(1);
        spv2->setHandleWidth(1);
        hbox2->addWidget(splitter);

        splitter->addWidget(spv1);
        splitter->addWidget(spv2);
        splitter->setStretchFactor(0, 50);
        splitter->setStretchFactor(1, 50);

        QAbstractScrollArea *  sa1 = new QAbstractScrollArea;
        QAbstractScrollArea *  sa2 = new QAbstractScrollArea;
        QVBoxLayout *  sa1Vbox = new QVBoxLayout(sa1);
        QVBoxLayout *  sa2Vbox = new QVBoxLayout(sa2);
        sa1Vbox->setContentsMargins(0, 0, 0, 0);
        sa2Vbox->setContentsMargins(0, 0, 0, 0);

        spv1->addWidget(sa1);
        spv1->addWidget(m_displayCode);
        spv1->setStretchFactor(0, 15);
        spv1->setStretchFactor(1, 85);

        spv2->addWidget(sa2);
        spv2->addWidget(m_insertCode);
        spv2->setStretchFactor(0, 15);
        spv2->setStretchFactor(1, 85);

        QLabel *  lbDelete = new QLabel(tr("Delete Row"));
        QLabel *  lbInsert = new QLabel(tr("Insert Row"));
        sa1Vbox->addWidget(lbDelete);
        sa1Vbox->addWidget(m_deleteIndexView);
        sa2Vbox->addWidget(lbInsert);
        sa2Vbox->addWidget(m_insertIndexView);
    }
    {
        hbox3->addWidget(m_functionDecLabel);
    }
}

WtAutoFnEdit::~WtAutoFnEdit() noexcept
{
}

void
WtAutoFnEdit::insertCode_textChanged()
{
    if (!m_objPtr)  return;
}

void
WtAutoFnEdit::isDefault_stateChanged()
{
    if (!m_objPtr)  return;
}

void
WtAutoFnEdit::isDelete_stateChanged()
{
    if (!m_objPtr)  return;
}

void
WtAutoFnEdit::attribute_editingFinished()
{
    if (!m_objPtr)  return;
}

void
WtAutoFnEdit::beforBehindPb_clicked()
{
    if (!m_objPtr)  return;
}

void
WtAutoFnEdit::insertIndexConnect()
{
}

void
WtAutoFnEdit::deleteIndexConnect()
{
}

void
WtAutoFnEdit::repDeleteIndex()
{
}

void
WtAutoFnEdit::repInsertIndex()
{
}

void
WtAutoFnEdit::setVisible()
{
    QStandardItem *  itemPtr = getItemPtr();
    if (!m_objPtr || !itemPtr)  return;
}

Function *
WtAutoFnEdit::getObjPtr() const
{
    return m_objPtr;
}

void
WtAutoFnEdit::setObjPtr(Function *  value)
{
    m_objPtr = value;
    if (m_objPtr) {

        m_functionDecLabel->setText(QString::fromStdString(m_objPtr->declLabel()));
        m_attribute->setText(QString::fromStdString(m_objPtr->getAttribute()));
        m_isDefault->setChecked(m_objPtr->isEqDefault());
        m_isDelete->setChecked(m_objPtr->isEqDelete());
        m_displayCode->setPlainText(QString::fromStdString(m_objPtr->updateAutoCode()));

        repDeleteIndex();
        repInsertIndex();

        setVisible();
    }
}

}
