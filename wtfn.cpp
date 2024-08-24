#include <typeinfo>
#include <QInputDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QAction>
#include <QList>
#include "highlighter.h"
#include "twobeforebehind.h"
#include "fourbeforebehind.h"
#include "fmt.h"
#include "eobject.h"
#include "parameter.h"
#include "wtfn.h"
#include "myclass.h"
#include "module.h"
#include "functions.h"
#include "staticfunctions.h"
#include "constexprfunctions.h"
#include "tplfunctions.h"
#include "tplstaticfunctions.h"
#include "tplconstexprfunctions.h"
#include "constructors.h"
#include "tplconstructors.h"

namespace xu {

WtFn::WtFn(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_itemPtr(nullptr),
        m_functionName(nullptr),
        m_returnType(nullptr),
        m_attribute(nullptr),
        m_beforBehindPb(nullptr),
        m_codeEdit(nullptr),
        m_parameterView(nullptr),
        m_parameterModel(nullptr),
        m_isEnabled(nullptr),
        m_isInline(nullptr),
        m_isConst(nullptr),
        m_isExplicit(nullptr),
        m_isPureVirtual(nullptr),
        m_isVirtual(nullptr),
        m_isOverride(nullptr),
        m_isFinal(nullptr),
        m_isNoexcept(nullptr)
{
    m_functionName = new QLineEdit;
    m_returnType = new QLineEdit;
    m_attribute = new QLineEdit;
    m_beforBehindPb = new QPushButton(tr(" Insert && Follow "));
    m_codeEdit = new CodeEditor;
    new Highlighter(m_codeEdit->document());

    m_parameterView = new QTableView;
    m_parameterModel = new QStandardItemModel;
    m_parameterModel->setHorizontalHeaderItem(0,
            new QStandardItem(tr("Parameter Type")));
    m_parameterModel->setHorizontalHeaderItem(1,
            new QStandardItem(tr("Parameter Name")));
    m_parameterModel->setHorizontalHeaderItem(2,
            new QStandardItem(tr("Docment")));
    m_parameterModel->setHorizontalHeaderItem(3,
            new QStandardItem(tr("Default Value")));
    m_parameterView->setModel(m_parameterModel);

    m_parameterView->setColumnWidth(0, 240);
    m_parameterView->setColumnWidth(1, 160);
    m_parameterView->setColumnWidth(2, 220);
    m_parameterView->setColumnWidth(3, 140);

    m_isEnabled = new QCheckBox(tr("Enabled"));
    m_isInline = new QCheckBox(tr("inline"));
    m_isConst = new QCheckBox(tr("const"));
    m_isExplicit = new QCheckBox(tr("explicit"));
    m_isPureVirtual = new QCheckBox(tr(" = 0"));
    m_isVirtual = new QCheckBox(tr("virtual"));
    m_isOverride = new QCheckBox(tr("override"));
    m_isFinal = new QCheckBox(tr("final"));
    m_isNoexcept = new QCheckBox(tr("noexcept"));

    connect(m_functionName, &QLineEdit::editingFinished,
            this, &WtFn::functionName_editingFinished);
    connect(m_returnType, &QLineEdit::editingFinished,
            this, &WtFn::returnType_editingFinished);
    connect(m_attribute, &QLineEdit::editingFinished,
            this, &WtFn::attribute_editingFinished);
    connect(m_beforBehindPb, &QPushButton::clicked,
            this, &WtFn::beforBehindPb_clicked);
    connect(m_codeEdit, &CodeEditor::textChanged,
            this, &WtFn::codeEdit_textChanged);

    parameterItemConnect();

    connect(m_isEnabled, &QCheckBox::stateChanged,
            this, &WtFn::isEnabled_stateChanged);
    connect(m_isInline, &QCheckBox::stateChanged,
            this, &WtFn::isInline_stateChanged);
    connect(m_isConst, &QCheckBox::stateChanged,
            this, &WtFn::isConst_stateChanged);
    connect(m_isExplicit, &QCheckBox::stateChanged,
            this, &WtFn::isExplicit_stateChanged);
    connect(m_isPureVirtual, &QCheckBox::stateChanged,
            this, &WtFn::isPureVirtual_stateChanged);
    connect(m_isVirtual, &QCheckBox::stateChanged,
            this, &WtFn::isVirtual_stateChanged);
    connect(m_isOverride, &QCheckBox::stateChanged,
            this, &WtFn::isOverride_stateChanged);
    connect(m_isFinal, &QCheckBox::stateChanged,
            this, &WtFn::isFinal_stateChanged);
    connect(m_isNoexcept, &QCheckBox::stateChanged,
            this, &WtFn::isNoexcept_stateChanged);

    QVBoxLayout *  vbox = new QVBoxLayout;
    vbox->setContentsMargins(0, 0, 0, 0);
    this->setLayout(vbox);

    QHBoxLayout *  hbox1 = new QHBoxLayout;
    QVBoxLayout *  vbox2 = new QVBoxLayout;
    hbox1->setContentsMargins(0, 0, 0, 0);
    vbox2->setContentsMargins(0, 0, 0, 0);
    vbox->addLayout(hbox1);
    vbox->addLayout(vbox2);

    QFormLayout *  fm0 = new QFormLayout;
    QFormLayout *  fm1 = new QFormLayout;
    QHBoxLayout *  fm2 = new QHBoxLayout;
    fm0->setContentsMargins(0, 0, 0, 0);
    fm1->setContentsMargins(0, 0, 0, 0);
    fm2->setContentsMargins(0, 0, 0, 0);
    hbox1->addLayout(fm0);
    hbox1->addLayout(fm1);
    hbox1->addLayout(fm2);

    QLabel *  label0 = new QLabel(tr(" Function Name "));
    QLabel *  label1 = new QLabel(tr(" Return Type "));
    fm0->addRow(label0, m_functionName);
    fm1->addRow(label1, m_returnType);
    fm2->addWidget(m_beforBehindPb);

    QSplitter *  vH = new QSplitter(Qt::Vertical);
    vH->setHandleWidth(1);
    vbox2->addWidget(vH);

    vH->addWidget(m_parameterView);
    vH->addWidget(m_codeEdit);
    vH->setStretchFactor(0, 15);
    vH->setStretchFactor(1, 85);
}

WtFn::~WtFn() noexcept
{
}

void
WtFn::functionName_editingFinished()
{
    if (!m_objPtr)  return;

    std::string const  oldVal = m_objPtr->getFunctionName();
    std::string const  currVal = m_functionName->text().toUtf8().toStdString();
    if (oldVal == currVal)  return;
    m_objPtr->setFunctionName(currVal);
    std::string const  newVal = m_objPtr->getFunctionName();
    if (currVal != newVal) {
        m_functionName->setText(QString::fromStdString(newVal));
    }
    QVariant  treeLabel(QString::fromStdString(m_objPtr->getTreeLabel()));
    m_itemPtr->setData(treeLabel, Qt::EditRole);
}

void
WtFn::returnType_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setReturnType(m_returnType->text().toUtf8().toStdString());
}

void
WtFn::attribute_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setAttribute(m_attribute->text().toUtf8().toStdString());
}

void
WtFn::beforBehindPb_clicked()
{
    if (!m_objPtr)  return;

    std::string const  title("Function: " + m_objPtr->getFunctionName());
    QString const  beforeFirstLabel("    function declaration Insert ( .h )");
    QString const  behindFirstLabel("    function declaration Follow ( .h )");
    QString const  beforeSecondLabel("    function definition Insert ( .h )");
    QString const  behindSecondLabel("    function definition Follow ( .h )");
    std::string  beforeFirstString = m_objPtr->getHBefore();
    std::string  behindFirstString = m_objPtr->getHBehind();
    std::string  beforeSecondString = m_objPtr->getCppBefore();
    std::string  behindSecondString = m_objPtr->getCppBehind();

    FourBeforeBehind  fbe(title, beforeFirstLabel, behindFirstLabel,
            beforeFirstString, behindFirstString,
            beforeSecondLabel, behindSecondLabel,
            beforeSecondString, beforeSecondString);
    fbe.exec();
    m_objPtr->setHBefore(std::move(beforeFirstString));
    m_objPtr->setHBehind(std::move(behindFirstString));
    m_objPtr->setCppBefore(std::move(beforeSecondString));
    m_objPtr->setCppBehind(std::move(behindSecondString));
}

void
WtFn::codeEdit_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setMCode(m_codeEdit->toPlainText().toUtf8().toStdString());
}

void
WtFn::parameterItemConnect()
{
    QAction *  actAddNew = new QAction(tr("Add New"));
    QAction *  actInsertNew = new QAction(tr("Insert New"));
    QAction *  actDelete = new QAction(tr("Delete"));
    QAction *  actCopyToNew = new QAction(tr("Copy To New"));
    actAddNew->setParent(this);
    actInsertNew->setParent(this);
    actDelete->setParent(this);
    actCopyToNew->setParent(this);
    QAction *  actSpt = new QAction;
    actSpt->setSeparator(true);
    actSpt->setParent(this);
    QAction *  actUp = new QAction(tr("Up"));
    QAction *  actDown = new QAction(tr("Down"));
    QAction *  actMoveToRow = new QAction(tr("Move To Row"));
    actUp->setParent(this);
    actDown->setParent(this);
    actMoveToRow->setParent(this);
    QAction *  actSpt2 = new QAction;
    actSpt2->setSeparator(true);
    actSpt2->setParent(this);
    QAction *  actBeforBehind = new QAction(tr("ReturnType Insert && Follow"));
    m_parameterView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_parameterView->addAction(actAddNew);
    m_parameterView->addAction(actInsertNew);
    m_parameterView->addAction(actDelete);
    m_parameterView->addAction(actCopyToNew);
    m_parameterView->addAction(actSpt);
    m_parameterView->addAction(actUp);
    m_parameterView->addAction(actDown);
    m_parameterView->addAction(actMoveToRow);
    m_parameterView->addAction(actSpt2);
    m_parameterView->addAction(actBeforBehind);

    connect(actAddNew, &QAction::triggered,
            this, &WtFn::param_AddNew_triggered);
    connect(actInsertNew, &QAction::triggered,
            this, &WtFn::param_InsertNew_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtFn::param_Delete_triggered);
    connect(actCopyToNew, &QAction::triggered,
            this, &WtFn::param_CopyToNew_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtFn::param_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtFn::param_Down_triggered);
    connect(actMoveToRow, &QAction::triggered,
            this, &WtFn::param_MoveToRow_triggered);

    connect(actBeforBehind, &QAction::triggered,
            this, &WtFn::param_BeforBehind_triggered);

    connect(m_parameterView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtFn::param_itemDelegate_closeEditor);
}

void
WtFn::param_AddNew_triggered()
{
    if (!m_objPtr)  return;

    std::vector<Parameter>  rawDataVec = m_objPtr->getParam();
    Parameter  newData;
    QList<QStandardItem *>  items;
    QStandardItem *  item0 = new QStandardItem(
            QString::fromStdString(newData.getType()));
    QStandardItem *  item1 = new QStandardItem(
            QString::fromStdString(newData.getParameterName()));
    QStandardItem *  item2 = new QStandardItem(
            QString::fromStdString(newData.getDocment()));
    QStandardItem *  item3 = new QStandardItem(
            QString::fromStdString(newData.getDefalutValue()));
    items << item0 << item1 << item2 << item3;

    rawDataVec.push_back(std::move(newData));
    m_objPtr->setParam(std::move(rawDataVec));

    m_parameterModel->appendRow(items);
}

void
WtFn::param_InsertNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_parameterView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getParam();
        Parameter  newData;
        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(
                QString::fromStdString(newData.getType()));
        QStandardItem *  item1 = new QStandardItem(
                QString::fromStdString(newData.getParameterName()));
        QStandardItem *  item2 = new QStandardItem(
                QString::fromStdString(newData.getDocment()));
        QStandardItem *  item3 = new QStandardItem(
                QString::fromStdString(newData.getDefalutValue()));
        items << item0 << item1 << item2 << item3;

        rawDataVec.insert(rawDataVec.begin() + row, std::move(newData));
        m_objPtr->setParam(std::move(rawDataVec));

        m_parameterModel->insertRow(row, items);
    } else {
        param_AddNew_triggered();
    }
}

void
WtFn::param_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_parameterView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getParam();
        rawDataVec.erase(rawDataVec.begin() + row);
        m_objPtr->setParam(std::move(rawDataVec));

        m_parameterModel->removeRows(row, 1);

        int const  count = m_parameterModel->rowCount();
        if (count > 0 && row < count) {
            m_parameterView->setCurrentIndex(m_parameterModel->index(row, index.column()));
        } else if (count > 0 && row != 0) {
            m_parameterView->setCurrentIndex(m_parameterModel->index(row - 1, index.column()));
        } else if (count == 1) {
            m_parameterView->setCurrentIndex(m_parameterModel->index(0, index.column()));
        }
    }
}

void
WtFn::param_CopyToNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_parameterView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getParam();
        Parameter  newData = rawDataVec[row];
        std::string const  oldName = rawDataVec[row].getParameterName();
        std::string const  baseNewName = oldName + "_copy";
        std::string  newName;
        size_t  nameIdx = 0;
        while (true) {
            ++nameIdx;
            newName = baseNewName + std::to_string(nameIdx);
            if (!nameCheckDuplication(newName)) {
                break;
            }
        }
        newData.setParameterName(newName);
        rawDataVec.insert(rawDataVec.begin() + row + 1, newData);
        m_objPtr->setParam(std::move(rawDataVec));

        QList<QStandardItem *>  itemNew;
        QStandardItem *  item0 = new QStandardItem(
                QString::fromStdString(newData.getType()));
        QStandardItem *  item1 = new QStandardItem(
                QString::fromStdString(newData.getParameterName()));
        QStandardItem *  item2 = new QStandardItem(
                QString::fromStdString(newData.getDocment()));
        QStandardItem *  item3 = new QStandardItem(
                QString::fromStdString(newData.getDefalutValue()));
        itemNew << item0 << item1 << item2 << item3;
        m_parameterModel->insertRow(row + 1, itemNew);
    }
}

void
WtFn::param_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_parameterView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        auto  rawDataVec = m_objPtr->getParam();
        std::swap(rawDataVec[row], rawDataVec[row - 1]);
        m_objPtr->setParam(std::move(rawDataVec));

        auto const  item = m_parameterModel->takeRow(row);
        m_parameterModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_parameterView->setCurrentIndex(idx);
    }
}

void
WtFn::param_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_parameterView->currentIndex();
    int const  row = index.row();
    int const  count = m_parameterModel->rowCount();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  rawDataVec = m_objPtr->getParam();
        std::swap(rawDataVec[row], rawDataVec[row + 1]);
        m_objPtr->setParam(std::move(rawDataVec));

        auto const  item = m_parameterModel->takeRow(row + 1);
        m_parameterModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_parameterView->setCurrentIndex(idx);
    }
}

void
WtFn::param_MoveToRow_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_parameterView->currentIndex();
    int const  count = m_parameterModel->rowCount();
    size_t  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        size_t  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (!ok)  return;

        auto  rawDataVec = m_objPtr->getParam();
        if (!xu::moveVec_0(rawDataVec, currRow, movetoRow)) {
            return;
        }
        m_objPtr->setParam(std::move(rawDataVec));

        auto const  item = m_parameterModel->takeRow(static_cast<int>(currRow));
        m_parameterModel->insertRow(static_cast<int>(movetoRow), item);
        QModelIndex  idx = index.sibling(static_cast<int>(movetoRow), index.column());
        m_parameterView->setCurrentIndex(idx);
    }
}

void
WtFn::param_BeforBehind_triggered()
{
    if (!m_objPtr)  return;

    std::string const  title("ReturnType + Follow_1 + Follow_2");
    QString const  beforeLabel("    Follow_1 ( .h ) ");
    QString const  behindLabel("    Follow_2 ( .h ) ( .cpp )");
    std::string  beforeString = m_objPtr->getHReturnTypeBehind();
    std::string  behindString = m_objPtr->getHReturnTypeBehind2();

    TwoBeforeBehind  tbe(title, beforeLabel, behindLabel, beforeString, behindString);
    tbe.exec();
    m_objPtr->setHReturnTypeBehind(std::move(beforeString));
    m_objPtr->setHReturnTypeBehind2(std::move(behindString));
}

void
WtFn::param_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_parameterView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getParam();
        std::string const  currVal = m_parameterModel->data(index).
                toString().toUtf8().toStdString();

        switch (index.column()) {
        case 0 :
            {
                rawDataVec[row].setType(currVal);
                std::string const  newVal = rawDataVec[row].getType();
                if (currVal != newVal) {
                    m_parameterModel->setData(index, QVariant(
                            QString::fromStdString(newVal)));
                }
                m_objPtr->setParam(std::move(rawDataVec));
            }
            break;
        case 1 :
            {
                std::string const  oldVal = rawDataVec[row].getParameterName();
                if (oldVal == currVal)  return;
                rawDataVec[row].setParameterName(currVal);
                std::string const  newVal = rawDataVec[row].getParameterName();
                if (currVal != newVal) {
                    m_parameterModel->setData(index, QVariant(
                            QString::fromStdString(newVal)));
                }
                m_objPtr->setParam(std::move(rawDataVec));
            }
            break;
        case 2 :
            rawDataVec[row].setDocment(currVal);
            m_objPtr->setParam(std::move(rawDataVec));
            break;
        case 3 :
            {
                rawDataVec[row].setDefalutValue(currVal);
                std::string const  newVal = rawDataVec[row].getDefalutValue();
                if (currVal != newVal) {
                    m_parameterModel->setData(index, QVariant(
                            QString::fromStdString(newVal)));
                }
                m_objPtr->setParam(std::move(rawDataVec));
            }
            break;
        }
    }
}

void
WtFn::isEnabled_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setEnabled(true);
    } else {
        m_objPtr->setEnabled(false);
    }
}

void
WtFn::isInline_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setInline(true);
    } else {
        m_objPtr->setInline(false);
    }
}

void
WtFn::isConst_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setConst(true);
    } else {
        m_objPtr->setConst(false);
    }
}

void
WtFn::isExplicit_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setExplicit(true);
        bool const  newVal = m_objPtr->isExplicit();
        if (!newVal) {
            m_isExplicit->setChecked(false);
        }
    } else {
        m_objPtr->setExplicit(false);
    }
}

void
WtFn::isPureVirtual_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setPureVirtual(true);
    } else {
        m_objPtr->setPureVirtual(false);
    }
}

void
WtFn::isVirtual_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setVirtual(true);
    } else {
        m_objPtr->setVirtual(false);
    }
}

void
WtFn::isOverride_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setOverride(true);
    } else {
        m_objPtr->setOverride(false);
    }
}

void
WtFn::isFinal_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setFinal(true);
    } else {
        m_objPtr->setFinal(false);
    }
}

void
WtFn::isNoexcept_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setNoexcept(true);
    } else {
        m_objPtr->setNoexcept(false);
    }
}

void
WtFn::repParameterItem()
{
    m_parameterModel->removeRows(0, m_parameterModel->rowCount());
    std::vector<Parameter> const  item = m_objPtr->getParam();
    for (auto const &  it: item) {
        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(
                QString::fromStdString(it.getType()));
        QStandardItem *  item1 = new QStandardItem(
                QString::fromStdString(it.getParameterName()));
        QStandardItem *  item2 = new QStandardItem(
                QString::fromStdString(it.getDocment()));
        QStandardItem *  item3 = new QStandardItem(
                QString::fromStdString(it.getDefalutValue()));
        items << item0 << item1 << item2 << item3;
        m_parameterModel->appendRow(items);
    }
}

bool
WtFn::nameCheckDuplication(std::string const &  fnName)
{
    bool  res = false;

    auto  rawDataVec = m_objPtr->getParam();
    for (const auto &  fn: rawDataVec) {
        res = fn.getParameterName() == fnName;
        if (res)  return res;
    }

    return res;
}

void
WtFn::setVisible()
{
    if (!m_objPtr || !m_itemPtr)  return;

    QStandardItem *  parentItem = m_itemPtr->parent();
    QStandardItem *  rootItem = parentItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(
            Qt::UserRole + 1).toInt());
    Etype const  rootEtp = static_cast<Etype>(rootItem->data(
            Qt::UserRole + 1).toInt());

    if (rootEtp == Etype::eModule) {
        m_isConst->hide();
        m_isExplicit->hide();
        m_isPureVirtual->hide();
        m_isVirtual->hide();
        m_isOverride->hide();
        m_isFinal->hide();
    } else {
        m_isConst->show();
        m_isExplicit->show();
        m_isPureVirtual->show();
        m_isVirtual->show();
        m_isOverride->show();
        m_isFinal->show();

        if (parentEtp == Etype::eStaticFunctions) {
            m_isConst->hide();
        }
    }
}

Function *
WtFn::getObjPtr() const
{
    return m_objPtr;
}

void
WtFn::setObjPtr(Function *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        m_functionName->setText(QString::fromStdString(m_objPtr->getFunctionName()));
        m_returnType->setText(QString::fromStdString(m_objPtr->getReturnType()));
        m_attribute->setText(QString::fromStdString(m_objPtr->getAttribute()));
        m_codeEdit->setPlainText(QString::fromStdString(m_objPtr->getMCode()));

        m_isEnabled->setChecked(m_objPtr->isEnabled());
        m_isInline->setChecked(m_objPtr->isInline());
        m_isConst->setChecked(m_objPtr->isConst());
        m_isExplicit->setChecked(m_objPtr->isExplicit());
        m_isPureVirtual->setChecked(m_objPtr->isPureVirtual());
        m_isVirtual->setChecked(m_objPtr->isVirtual());
        m_isOverride->setChecked(m_objPtr->isOverride());
        m_isFinal->setChecked(m_objPtr->isFinal());
        m_isNoexcept->setChecked(m_objPtr->isNoexcept());

        repParameterItem();

        setVisible();
    }
}

QStandardItem *
WtFn::getItemPtr() const
{
    return m_itemPtr;
}

void
WtFn::setItemPtr(QStandardItem *  value)
{
    m_itemPtr = value;
    setVisible();
}

}
