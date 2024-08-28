#include <typeinfo>
#include <QInputDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QAbstractScrollArea>
#include <QAction>
#include <QList>
#include "highlighter.h"
#include "twobeforebehind.h"
#include "fourbeforebehind.h"
#include "fmt.h"
#include "eobject.h"
#include "parameter.h"
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
#include "wttplfn.h"

namespace xu {

WtTplFn::WtTplFn(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_functionName(nullptr),
        m_returnType(nullptr),
        m_attribute(nullptr),
        m_beforBehindPb(nullptr),
        m_codeEdit(nullptr),
        m_paramTplView(nullptr),
        m_paramTplModel(nullptr),
        m_parameterView(nullptr),
        m_parameterModel(nullptr),
        m_friendClassView(nullptr),
        m_friendClassModel(nullptr),
        m_friendLabel(nullptr),
        m_hideWindow(nullptr),
        m_isEnabled(nullptr),
        m_isConst(nullptr),
        m_isNoexcept(nullptr)
{
    m_functionName = new QLineEdit;
    m_returnType = new QLineEdit;
    m_attribute = new QLineEdit;
    m_beforBehindPb = new QPushButton(tr(" Insert && Follow "));
    m_codeEdit = new CodeEditor;
    new Highlighter(m_codeEdit->document());

    m_paramTplView = new QTableView;
    m_paramTplModel = new QStandardItemModel;
    m_paramTplModel->setHorizontalHeaderItem(0,
            new QStandardItem(tr("typename / class")));
    m_paramTplModel->setHorizontalHeaderItem(1,
            new QStandardItem(tr("Type Name / T")));
    m_paramTplModel->setHorizontalHeaderItem(2,
            new QStandardItem(tr("Docment")));
    m_paramTplModel->setHorizontalHeaderItem(3,
            new QStandardItem(tr("Default Value")));
    m_paramTplModel->setHorizontalHeaderItem(4,
            new QStandardItem(tr("T / (isFriend)")));
    m_paramTplView->setModel(m_paramTplModel);

    m_paramTplView->setColumnWidth(0, 220);
    m_paramTplView->setColumnWidth(1, 110);
    m_paramTplView->setColumnWidth(2, 190);
    m_paramTplView->setColumnWidth(3, 120);
    m_paramTplView->setColumnWidth(4, 120);

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

    m_hideWindow = new QFrame;
    m_hideWindow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_friendClassView = new QListView;
    m_friendClassModel = new QStandardItemModel;
    m_friendClassView->setModel(m_friendClassModel);
    m_friendLabel = new QLabel(tr("Friend Class"));

    m_isEnabled = new QCheckBox(tr("Enabled"));
    m_isConst = new QCheckBox(tr("const"));
    m_isNoexcept = new QCheckBox(tr("noexcept"));

    connect(m_functionName, &QLineEdit::editingFinished,
            this, &WtTplFn::functionName_editingFinished);
    connect(m_returnType, &QLineEdit::editingFinished,
            this, &WtTplFn::returnType_editingFinished);
    connect(m_attribute, &QLineEdit::editingFinished,
            this, &WtTplFn::attribute_editingFinished);
    connect(m_beforBehindPb, &QPushButton::clicked,
            this, &WtTplFn::beforBehindPb_clicked);
    connect(m_codeEdit, &CodeEditor::textChanged,
            this, &WtTplFn::codeEdit_textChanged);

    paramTplItemConnect();
    parameterItemConnect();
    friendClassConnect();

    connect(m_isEnabled, &QCheckBox::stateChanged,
            this, &WtTplFn::isEnabled_stateChanged);
    connect(m_isConst, &QCheckBox::stateChanged,
            this, &WtTplFn::isConst_stateChanged);
    connect(m_isNoexcept, &QCheckBox::stateChanged,
            this, &WtTplFn::isNoexcept_stateChanged);

    QVBoxLayout *  vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *  hbox1 = new QHBoxLayout;
    QVBoxLayout *  vbox2 = new QVBoxLayout;
    hbox1->setContentsMargins(0, 0, 0, 0);
    vbox2->setContentsMargins(0, 0, 0, 0);
    vbox->addLayout(hbox1);
    vbox->addLayout(vbox2);

    QFormLayout *  fm0 = new QFormLayout;
    QFormLayout *  fm1 = new QFormLayout;
    fm0->setContentsMargins(0, 0, 0, 0);
    fm1->setContentsMargins(0, 0, 0, 0);
    hbox1->addLayout(fm0);
    hbox1->addLayout(fm1);

    QLabel *  label0 = new QLabel(tr("Function Name"));
    QLabel *  label1 = new QLabel(tr(" Return Type"));
    fm0->addRow(label0, m_functionName);
    fm1->addRow(label1, m_returnType);

    QSplitter *  vH = new QSplitter(Qt::Vertical);
    vH->setHandleWidth(1);
    vbox2->addWidget(vH);

    QSplitter *  splitter = new QSplitter;
    splitter->setHandleWidth(1);

    vH->addWidget(m_paramTplView);
    vH->addWidget(m_parameterView);
    vH->addWidget(splitter);
    vH->setStretchFactor(0, 15);
    vH->setStretchFactor(1, 15);
    vH->setStretchFactor(2, 70);

    QAbstractScrollArea *  fr = new QAbstractScrollArea;
    splitter->addWidget(m_codeEdit);
    splitter->addWidget(fr);
    splitter->setStretchFactor(0, 80);
    splitter->setStretchFactor(1, 20);

    QVBoxLayout *  rightVbox = new QVBoxLayout;
    rightVbox->setContentsMargins(5, 5, 5, 5);
    rightVbox->setAlignment(Qt::AlignTop);
    fr->setLayout(rightVbox);
    rightVbox->addWidget(m_isEnabled);
    rightVbox->addWidget(m_isConst);
    rightVbox->addWidget(m_isNoexcept);

    QLabel *  attr = new QLabel(tr("Attribute"));
    rightVbox->addSpacing(5);
    rightVbox->addWidget(attr);
    rightVbox->addWidget(m_attribute);
    rightVbox->addSpacing(5);
    rightVbox->addWidget(m_friendLabel);
    rightVbox->addWidget(m_friendClassView);
    rightVbox->addWidget(m_hideWindow);
    rightVbox->addWidget(m_beforBehindPb);
}

WtTplFn::~WtTplFn() noexcept
{
}

void
WtTplFn::functionName_editingFinished()
{
    if (!m_objPtr)  return;

    QStandardItem *  itemPtr = getItemPtr();
    std::string const  oldVal = m_objPtr->getFunctionName();
    std::string const  currVal = m_functionName->text().toUtf8().toStdString();
    if (oldVal == currVal)  return;
    m_objPtr->setFunctionName(currVal);
    std::string const  newVal = m_objPtr->getFunctionName();
    if (currVal != newVal) {
        m_functionName->setText(QString::fromStdString(newVal));
    }
    QVariant  treeLabel(QString::fromStdString(m_objPtr->getTreeLabel()));
    itemPtr->setData(treeLabel, Qt::EditRole);
}

void
WtTplFn::returnType_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setReturnType(m_returnType->text().toUtf8().toStdString());
}

void
WtTplFn::attribute_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setAttribute(m_attribute->text().toUtf8().toStdString());
}

void
WtTplFn::beforBehindPb_clicked()
{
    if (!m_objPtr)  return;

    std::string const  title("Function: " + m_objPtr->getFunctionName());
    QString const  beforeFirstLabel("    function declaration Insert ( .h )");
    QString const  behindFirstLabel("    function declaration Follow ( .h )");
    QString const  beforeSecondLabel("    function definition Insert ( .cpp )");
    QString const  behindSecondLabel("    function definition Follow ( .cpp )");
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
WtTplFn::codeEdit_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setMCode(m_codeEdit->toPlainText().toUtf8().toStdString());
}

void
WtTplFn::parameterItemConnect()
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
            this, &WtTplFn::param_AddNew_triggered);
    connect(actInsertNew, &QAction::triggered,
            this, &WtTplFn::param_InsertNew_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtTplFn::param_Delete_triggered);
    connect(actCopyToNew, &QAction::triggered,
            this, &WtTplFn::param_CopyToNew_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtTplFn::param_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtTplFn::param_Down_triggered);
    connect(actMoveToRow, &QAction::triggered,
            this, &WtTplFn::param_MoveToRow_triggered);

    connect(actBeforBehind, &QAction::triggered,
            this, &WtTplFn::param_BeforBehind_triggered);

    connect(m_parameterView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtTplFn::param_itemDelegate_closeEditor);
}

void
WtTplFn::param_AddNew_triggered()
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
WtTplFn::param_InsertNew_triggered()
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
WtTplFn::param_Delete_triggered()
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
WtTplFn::param_CopyToNew_triggered()
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
WtTplFn::param_Up_triggered()
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
WtTplFn::param_Down_triggered()
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
WtTplFn::param_MoveToRow_triggered()
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
WtTplFn::param_BeforBehind_triggered()
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
WtTplFn::param_itemDelegate_closeEditor()
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
WtTplFn::isEnabled_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setEnabled(true);
    } else {
        m_objPtr->setEnabled(false);
    }
}

void
WtTplFn::isConst_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setConst(true);
    } else {
        m_objPtr->setConst(false);
    }
}

void
WtTplFn::isNoexcept_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setNoexcept(true);
    } else {
        m_objPtr->setNoexcept(false);
    }
}

void
WtTplFn::friendClassConnect()
{
    QAction *  actAdd = new QAction(tr("Add New"));
    QAction *  actInsertNew = new QAction(tr("Insert New"));
    QAction *  actDelete = new QAction(tr("Delete"));
    actAdd->setParent(this);
    actInsertNew->setParent(this);
    actDelete->setParent(this);
    QAction *  actSpt = new QAction;
    actSpt->setSeparator(true);
    actSpt->setParent(this);
    QAction *  actUp = new QAction(tr("Up"));
    QAction *  actDown = new QAction(tr("Down"));
    QAction *  actMoveTo = new QAction(tr("Move To Row"));
    actUp->setParent(this);
    actDown->setParent(this);
    actMoveTo->setParent(this);
    m_friendClassView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_friendClassView->addAction(actAdd);
    m_friendClassView->addAction(actInsertNew);
    m_friendClassView->addAction(actDelete);
    m_friendClassView->addAction(actSpt);
    m_friendClassView->addAction(actUp);
    m_friendClassView->addAction(actDown);
    m_friendClassView->addAction(actMoveTo);

    connect(actAdd, &QAction::triggered,
            this, &WtTplFn::friendClass_Add_triggered);
    connect(actInsertNew, &QAction::triggered,
            this, &WtTplFn::friendClass_InsertNew_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtTplFn::friendClass_Delete_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtTplFn::friendClass_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtTplFn::friendClass_Down_triggered);
    connect(actMoveTo, &QAction::triggered,
            this, &WtTplFn::friendClass_MoveToRow_triggered);

    connect(m_friendClassView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtTplFn::friendClass_itemDelegate_closeEditor);
}

void
WtTplFn::friendClass_Add_triggered()
{
    if (!m_objPtr)  return;

    auto  frs = m_objPtr->getFriendClassName();
    frs.push_back("MyClass1");
    m_objPtr->setFriendClassName(frs);

    repFriendItem();
}

void
WtTplFn::friendClass_InsertNew_triggered()
{
    if (!m_objPtr)  return;

    const QModelIndex  index = m_friendClassView->currentIndex();
    if (index.isValid()) {
        auto  frs = m_objPtr->getFriendClassName();
        frs.insert(frs.begin() + index.row(), "MyClass1");
        m_objPtr->setFriendClassName(frs);

        repFriendItem();
    } else {
        friendClass_Add_triggered();
    }
}

void
WtTplFn::friendClass_Delete_triggered()
{
    if (!m_objPtr)  return;

    const QModelIndex  index = m_friendClassView->currentIndex();
    if (index.isValid()) {
        auto  frs = m_objPtr->getFriendClassName();
        frs.erase(frs.begin() + index.row());
        m_objPtr->setFriendClassName(frs);

        repFriendItem();
    }
}

void
WtTplFn::friendClass_Up_triggered()
{
    if (!m_objPtr)  return;

    const QModelIndex  index = m_friendClassView->currentIndex();
    const int  row = index.row();
    if (index.isValid() && row != 0) {
        auto  frs = m_objPtr->getFriendClassName();
        std::swap(frs[row], frs[row - 1]);
        m_objPtr->setFriendClassName(frs);

        const auto  item = m_friendClassModel->takeRow(row);
        m_friendClassModel->insertRow(row - 1, item);
        const QModelIndex  idx = index.sibling(row - 1, index.column());
        m_friendClassView->setCurrentIndex(idx);
    }
}

void
WtTplFn::friendClass_Down_triggered()
{
    if (!m_objPtr)  return;

    const QModelIndex  index = m_friendClassView->currentIndex();
    const int  row = index.row();
    const int  count = m_friendClassModel->rowCount();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  frs = m_objPtr->getFriendClassName();
        std::swap(frs[row], frs[row + 1]);
        m_objPtr->setFriendClassName(frs);

        const auto  item = m_friendClassModel->takeRow(row + 1);
        m_friendClassModel->insertRow(row, item);
        const QModelIndex  idx = index.sibling(row + 1, index.column());
        m_friendClassView->setCurrentIndex(idx);
    }
}

void
WtTplFn::friendClass_MoveToRow_triggered()
{
    if (!m_objPtr)  return;

    const QModelIndex  index = m_friendClassView->currentIndex();
    const int  count = m_friendClassModel->rowCount();
    int  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        int  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (ok) {
            if (movetoRow > count)  movetoRow = count;
            if (movetoRow == 0)  movetoRow = 1;
            ++currRow;
            if (currRow == movetoRow)  return;
            movetoRow--;  currRow--;

            auto  frs = m_objPtr->getFriendClassName();
            auto  dval = frs[currRow];
            frs.erase(frs.begin() + currRow);
            frs.insert(frs.begin() + movetoRow, std::move(dval));
            m_objPtr->setFriendClassName(frs);

            const auto  item = m_friendClassModel->takeRow(currRow);
            QModelIndex  idx;
            m_friendClassModel->insertRow(movetoRow, item);
            idx = index.sibling(movetoRow, index.column());

            m_friendClassView->setCurrentIndex(idx);
        }
    }
}

void
WtTplFn::friendClass_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    const QModelIndex  index = m_friendClassView->currentIndex();
    if (index.isValid()) {
        const std::string  newVal = m_friendClassModel->itemFromIndex(index)
                                    ->text().toUtf8().toStdString();
        auto  frs = m_objPtr->getFriendClassName();
        frs[index.row()] = newVal;
        m_objPtr->setFriendClassName(frs);

        repFriendItem();
    }
}

void
WtTplFn::paramTplItemConnect()
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
    m_paramTplView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_paramTplView->addAction(actAddNew);
    m_paramTplView->addAction(actInsertNew);
    m_paramTplView->addAction(actDelete);
    m_paramTplView->addAction(actCopyToNew);
    m_paramTplView->addAction(actSpt);
    m_paramTplView->addAction(actUp);
    m_paramTplView->addAction(actDown);
    m_paramTplView->addAction(actMoveToRow);
    m_paramTplView->addAction(actSpt2);
    m_paramTplView->addAction(actBeforBehind);

    connect(actAddNew, &QAction::triggered,
            this, &WtTplFn::paramTpl_AddNew_triggered);
    connect(actInsertNew, &QAction::triggered,
            this, &WtTplFn::paramTpl_InsertNew_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtTplFn::paramTpl_Delete_triggered);
    connect(actCopyToNew, &QAction::triggered,
            this, &WtTplFn::paramTpl_CopyToNew_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtTplFn::paramTpl_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtTplFn::paramTpl_Down_triggered);
    connect(actMoveToRow, &QAction::triggered,
            this, &WtTplFn::paramTpl_MoveToRow_triggered);

    connect(actBeforBehind, &QAction::triggered,
            this, &WtTplFn::param_BeforBehind_triggered);

    connect(m_paramTplView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtTplFn::paramTpl_itemDelegate_closeEditor);
}

void
WtTplFn::paramTpl_AddNew_triggered()
{
    if (!m_objPtr)  return;

    std::vector<Tpl>  rawDataVec = m_objPtr->getTparam();
    Tpl  newData;
    QList<QStandardItem *>  items;
    QStandardItem *  item0 = new QStandardItem(
            QString::fromStdString(newData.getTypename()));
    QStandardItem *  item1 = new QStandardItem(
            QString::fromStdString(newData.getTName()));
    QStandardItem *  item2 = new QStandardItem(
            QString::fromStdString(newData.getDocment()));
    QStandardItem *  item3 = new QStandardItem(
            QString::fromStdString(newData.getDefalutValue()));
    QStandardItem *  item4 = new QStandardItem(
            QString::fromStdString(newData.getFriendTypeName()));
    items << item0 << item1 << item2 << item3 << item4;

    rawDataVec.push_back(std::move(newData));
    m_objPtr->setTparam(std::move(rawDataVec));

    m_paramTplModel->appendRow(items);
}

void
WtTplFn::paramTpl_InsertNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_paramTplView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getTparam();
        Tpl  newData;
        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(
                QString::fromStdString(newData.getTypename()));
        QStandardItem *  item1 = new QStandardItem(
                QString::fromStdString(newData.getTName()));
        QStandardItem *  item2 = new QStandardItem(
                QString::fromStdString(newData.getDocment()));
        QStandardItem *  item3 = new QStandardItem(
                QString::fromStdString(newData.getDefalutValue()));
        QStandardItem *  item4 = new QStandardItem(
                QString::fromStdString(newData.getFriendTypeName()));
        items << item0 << item1 << item2 << item3 << item4;

        rawDataVec.insert(rawDataVec.begin() + row, std::move(newData));
        m_objPtr->setTparam(std::move(rawDataVec));

        m_paramTplModel->insertRow(row, items);
    } else {
        paramTpl_AddNew_triggered();
    }
}

void
WtTplFn::paramTpl_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_paramTplView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getTparam();
        rawDataVec.erase(rawDataVec.begin() + row);
        m_objPtr->setTparam(std::move(rawDataVec));

        m_paramTplModel->removeRows(row, 1);

        int const  count = m_paramTplModel->rowCount();
        if (count > 0 && row < count) {
            m_paramTplView->setCurrentIndex(m_paramTplModel->index(row, index.column()));
        } else if (count > 0 && row != 0) {
            m_paramTplView->setCurrentIndex(m_paramTplModel->index(row - 1, index.column()));
        } else if (count == 1) {
            m_paramTplView->setCurrentIndex(m_paramTplModel->index(0, index.column()));
        }
    }
}

void
WtTplFn::paramTpl_CopyToNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_paramTplView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getTparam();
        Tpl  newData = rawDataVec[row];
        rawDataVec.insert(rawDataVec.begin() + row + 1, newData);
        m_objPtr->setTparam(std::move(rawDataVec));

        QList<QStandardItem *>  itemNew;
        QStandardItem *  item0 = new QStandardItem(
                QString::fromStdString(newData.getTypename()));
        QStandardItem *  item1 = new QStandardItem(
                QString::fromStdString(newData.getTName()));
        QStandardItem *  item2 = new QStandardItem(
                QString::fromStdString(newData.getDocment()));
        QStandardItem *  item3 = new QStandardItem(
                QString::fromStdString(newData.getDefalutValue()));
        QStandardItem *  item4 = new QStandardItem(
                QString::fromStdString(newData.getFriendTypeName()));
        itemNew << item0 << item1 << item2 << item3 << item4;
        m_paramTplModel->insertRow(row + 1, itemNew);
    }
}

void
WtTplFn::paramTpl_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_paramTplView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        auto  rawDataVec = m_objPtr->getTparam();
        std::swap(rawDataVec[row], rawDataVec[row - 1]);
        m_objPtr->setTparam(std::move(rawDataVec));

        auto const  item = m_paramTplModel->takeRow(row);
        m_paramTplModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_paramTplView->setCurrentIndex(idx);
    }
}

void
WtTplFn::paramTpl_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_paramTplView->currentIndex();
    int const  row = index.row();
    int const  count = m_paramTplModel->rowCount();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  rawDataVec = m_objPtr->getTparam();
        std::swap(rawDataVec[row], rawDataVec[row + 1]);
        m_objPtr->setTparam(std::move(rawDataVec));

        auto const  item = m_paramTplModel->takeRow(row + 1);
        m_paramTplModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_paramTplView->setCurrentIndex(idx);
    }
}

void
WtTplFn::paramTpl_MoveToRow_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_paramTplView->currentIndex();
    int const  count = m_paramTplModel->rowCount();
    size_t  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        size_t  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (!ok)  return;

        auto  rawDataVec = m_objPtr->getTparam();
        if (!xu::moveVec_0(rawDataVec, currRow, movetoRow)) {
            return;
        }
        m_objPtr->setTparam(std::move(rawDataVec));

        auto const  item = m_paramTplModel->takeRow(static_cast<int>(currRow));
        m_paramTplModel->insertRow(static_cast<int>(movetoRow), item);
        QModelIndex  idx = index.sibling(static_cast<int>(movetoRow), index.column());
        m_paramTplView->setCurrentIndex(idx);
    }
}

void
WtTplFn::paramTpl_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_paramTplView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getTparam();
        std::string const  currVal = m_paramTplModel->data(index).
                toString().toUtf8().toStdString();

        switch (index.column()) {
        case 0 :
            {
                rawDataVec[row].setTypename(currVal);
                std::string const  newVal = rawDataVec[row].getTypename();
                if (currVal != newVal) {
                    m_paramTplModel->setData(index, QVariant(
                            QString::fromStdString(newVal)));
                }
                m_objPtr->setTparam(std::move(rawDataVec));
            }
            break;
        case 1 :
            {
                std::string const  oldVal = rawDataVec[row].getTName();
                if (oldVal == currVal)  return;
                rawDataVec[row].setTName(currVal);
                std::string const  newVal = rawDataVec[row].getTName();
                if (currVal != newVal) {
                    m_paramTplModel->setData(index, QVariant(
                            QString::fromStdString(newVal)));
                }
                m_objPtr->setTparam(std::move(rawDataVec));
            }
            break;
        case 2 :
            rawDataVec[row].setDocment(currVal);
            m_objPtr->setTparam(std::move(rawDataVec));
            break;
        case 3 :
            {
                rawDataVec[row].setDefalutValue(currVal);
                std::string const  newVal = rawDataVec[row].getDefalutValue();
                if (currVal != newVal) {
                    m_paramTplModel->setData(index, QVariant(
                            QString::fromStdString(newVal)));
                }
                m_objPtr->setTparam(std::move(rawDataVec));
            }
            break;
        case 4 :
            {
                rawDataVec[row].setFriendTypeName(currVal);
                std::string const  newVal = rawDataVec[row].getFriendTypeName();
                if (currVal != newVal) {
                    m_paramTplModel->setData(index, QVariant(
                            QString::fromStdString(newVal)));
                }
                m_objPtr->setTparam(std::move(rawDataVec));
            }
            break;
        }
    }
}

void
WtTplFn::repParamTplItem()
{
    m_paramTplModel->removeRows(0, m_paramTplModel->rowCount());
    std::vector<Tpl> const  item = m_objPtr->getTparam();
    for (auto const &  it: item) {
        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(
                QString::fromStdString(it.getTypename()));
        QStandardItem *  item1 = new QStandardItem(
                QString::fromStdString(it.getTName()));
        QStandardItem *  item2 = new QStandardItem(
                QString::fromStdString(it.getDocment()));
        QStandardItem *  item3 = new QStandardItem(
                QString::fromStdString(it.getDefalutValue()));
        QStandardItem *  item4 = new QStandardItem(
                QString::fromStdString(it.getFriendTypeName()));
        items << item0 << item1 << item2 << item3 << item4;
        m_paramTplModel->appendRow(items);
    }
}

void
WtTplFn::repParameterItem()
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

void
WtTplFn::repFriendItem()
{
    m_friendClassModel->removeRows(0, m_friendClassModel->rowCount());
    const auto  nps = m_objPtr->getFriendClassName();
    for (const auto &  it: nps) {
        m_friendClassModel->appendRow(new QStandardItem(
                QString::fromStdString(it)));
    }
}

bool
WtTplFn::nameCheckDuplication(std::string const &  fnName)
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
WtTplFn::setVisible()
{
    QStandardItem *  itemPtr = getItemPtr();
    if (!m_objPtr || !itemPtr)  return;

    QStandardItem *  parentItem = itemPtr->parent();
    QStandardItem *  rootItem = parentItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(
            Qt::UserRole + 1).toInt());
    Etype const  rootEtp = static_cast<Etype>(rootItem->data(
            Qt::UserRole + 1).toInt());

    if (rootEtp == Etype::eModule) {
        m_isConst->hide();

        if (parentEtp == Etype::eTplConstexprFunctions) {
            m_friendLabel->hide();
            m_friendClassView->hide();
            m_hideWindow->show();
        } else {
            m_friendLabel->show();
            m_friendClassView->show();
            m_hideWindow->hide();
        }
    } else {
        m_isConst->show();

        m_friendLabel->hide();
        m_friendClassView->hide();
        m_hideWindow->show();

        if (parentEtp == Etype::eTplStaticFunctions ||
                parentEtp == Etype::eTplConstexprFunctions) {
            m_isConst->hide();
        }
    }
}

Function *
WtTplFn::getObjPtr() const
{
    return m_objPtr;
}

void
WtTplFn::setObjPtr(Function *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        m_functionName->setText(QString::fromStdString(m_objPtr->getFunctionName()));
        m_returnType->setText(QString::fromStdString(m_objPtr->getReturnType()));
        m_attribute->setText(QString::fromStdString(m_objPtr->getAttribute()));
        m_codeEdit->setPlainText(QString::fromStdString(m_objPtr->getMCode()));

        m_isEnabled->setChecked(m_objPtr->isEnabled());
        m_isConst->setChecked(m_objPtr->isConst());
        m_isNoexcept->setChecked(m_objPtr->isNoexcept());

        repParamTplItem();
        repParameterItem();
        repFriendItem();

        setVisible();
    }
}

}
