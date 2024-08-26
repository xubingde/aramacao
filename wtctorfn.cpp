#include <typeinfo>
#include <QInputDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
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
#include "wtctorfn.h"

namespace xu {

WtCtorFn::WtCtorFn(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_baseClassDefVal(nullptr),
        m_attribute(nullptr),
        m_beforBehindPb(nullptr),
        m_codeEdit(nullptr),
        m_parameterView(nullptr),
        m_parameterModel(nullptr),
        m_fieldValView(nullptr),
        m_fieldValModel(nullptr),
        m_baseClassValView(nullptr),
        m_baseClassValModel(nullptr),
        m_isEnabled(nullptr),
        m_isInline(nullptr),
        m_isExplicit(nullptr),
        m_isNoexcept(nullptr)
{
    m_baseClassDefVal = new QLineEdit;
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

    m_fieldValView = new QTableView;
    m_fieldValModel = new QStandardItemModel;
    m_fieldValModel->setHorizontalHeaderItem(0,
            new QStandardItem(tr("Field Name")));
    m_fieldValModel->setHorizontalHeaderItem(1,
            new QStandardItem(tr("Default Value")));
    m_fieldValView->setModel(m_fieldValModel);

    m_fieldValView->setColumnWidth(0, 100);
    m_fieldValView->setColumnWidth(1, 100);

    m_baseClassValView = new QTableView;
    m_baseClassValModel = new QStandardItemModel;
    m_baseClassValModel->setHorizontalHeaderItem(0,
            new QStandardItem(tr("Base Class")));
    m_baseClassValModel->setHorizontalHeaderItem(1,
            new QStandardItem(tr("Default Value")));
    m_baseClassValView->setModel(m_baseClassValModel);

    m_baseClassValView->setColumnWidth(0, 100);
    m_baseClassValView->setColumnWidth(1, 100);

    m_isEnabled = new QCheckBox(tr("Enabled"));
    m_isInline = new QCheckBox(tr("inline"));
    m_isExplicit = new QCheckBox(tr("explicit"));
    m_isNoexcept = new QCheckBox(tr("noexcept"));

    connect(m_baseClassDefVal, &QLineEdit::editingFinished,
            this, &WtCtorFn::baseClassDefVal_editingFinished);
    connect(m_attribute, &QLineEdit::editingFinished,
            this, &WtCtorFn::attribute_editingFinished);
    connect(m_beforBehindPb, &QPushButton::clicked,
            this, &WtCtorFn::beforBehindPb_clicked);
    connect(m_codeEdit, &CodeEditor::textChanged,
            this, &WtCtorFn::codeEdit_textChanged);

    parameterItemConnect();

    connect(m_fieldValView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtCtorFn::fieldVal_itemDelegate_closeEditor);
    connect(m_baseClassValView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtCtorFn::baseClassVal_itemDelegate_closeEditor);

    connect(m_isEnabled, &QCheckBox::stateChanged,
            this, &WtCtorFn::isEnabled_stateChanged);
    connect(m_isInline, &QCheckBox::stateChanged,
            this, &WtCtorFn::isInline_stateChanged);
    connect(m_isExplicit, &QCheckBox::stateChanged,
            this, &WtCtorFn::isExplicit_stateChanged);
    connect(m_isNoexcept, &QCheckBox::stateChanged,
            this, &WtCtorFn::isNoexcept_stateChanged);

    QVBoxLayout *  vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    {
        QHBoxLayout *  hbox1 = new QHBoxLayout;
        hbox1->setContentsMargins(0, 0, 0, 0);
        vbox->addLayout(hbox1);
        QSplitter *  vH = new QSplitter(Qt::Vertical);
        vH->setHandleWidth(1);
        hbox1->addWidget(vH);
        vH->addWidget(m_parameterView);
        QSplitter *  splitter = new QSplitter;
        splitter->setHandleWidth(1);
        vH->addWidget(splitter);
        vH->setStretchFactor(0, 15);
        vH->setStretchFactor(1, 85);

        splitter->addWidget(m_codeEdit);
        QAbstractScrollArea *  fr = new QAbstractScrollArea;
        splitter->addWidget(fr);
        splitter->setStretchFactor(0, 70);
        splitter->setStretchFactor(1, 30);

        QVBoxLayout *  vboxFr = new QVBoxLayout(fr);
        vboxFr->setContentsMargins(0, 0, 0, 0);

        QGridLayout *  box4g = new QGridLayout;
        QVBoxLayout *  vboxVal = new QVBoxLayout;
        box4g->setContentsMargins(0, 0, 0, 0);
        vboxVal->setContentsMargins(0, 0, 0, 0);
        vboxFr->addLayout(box4g);
        vboxFr->addLayout(vboxVal);

        box4g->addWidget(m_isEnabled, 0, 0);
        box4g->addWidget(m_isExplicit, 0, 1);
        box4g->addWidget(m_isNoexcept, 1, 0);
        box4g->addWidget(m_isInline, 1, 1);

        vboxVal->addWidget(m_fieldValView);
        vboxVal->addWidget(m_baseClassValView);
        vboxVal->setStretch(0, 80);
        vboxVal->setStretch(1, 20);
    }
    {
        QHBoxLayout *  hbox1 = new QHBoxLayout;
        hbox1->setContentsMargins(0, 0, 0, 0);
        vbox->addLayout(hbox1);

        QFormLayout *  fm0 = new QFormLayout;
        QFormLayout *  fm1 = new QFormLayout;
        QHBoxLayout *  fm2 = new QHBoxLayout;
        fm0->setContentsMargins(0, 0, 0, 0);
        fm1->setContentsMargins(0, 0, 0, 0);
        fm2->setContentsMargins(0, 0, 0, 0);
        hbox1->addLayout(fm0);
        hbox1->addLayout(fm1);
        hbox1->addLayout(fm2);

        QLabel *  label0 = new QLabel(tr("BaseClass DefValue"));
        QLabel *  label1 = new QLabel(tr(" Attribute"));
        fm0->addRow(label0, m_baseClassDefVal);
        fm1->addRow(label1, m_attribute);
        fm2->addWidget(m_beforBehindPb);
    }
}

WtCtorFn::~WtCtorFn() noexcept
{
}

void
WtCtorFn::baseClassDefVal_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setInhValueFirst(m_attribute->text().toUtf8().toStdString());
}

void
WtCtorFn::attribute_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setAttribute(m_attribute->text().toUtf8().toStdString());
}

void
WtCtorFn::beforBehindPb_clicked()
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
WtCtorFn::codeEdit_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setMCode(m_codeEdit->toPlainText().toUtf8().toStdString());
}

void
WtCtorFn::parameterItemConnect()
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
            this, &WtCtorFn::param_AddNew_triggered);
    connect(actInsertNew, &QAction::triggered,
            this, &WtCtorFn::param_InsertNew_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtCtorFn::param_Delete_triggered);
    connect(actCopyToNew, &QAction::triggered,
            this, &WtCtorFn::param_CopyToNew_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtCtorFn::param_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtCtorFn::param_Down_triggered);
    connect(actMoveToRow, &QAction::triggered,
            this, &WtCtorFn::param_MoveToRow_triggered);

    connect(actBeforBehind, &QAction::triggered,
            this, &WtCtorFn::param_BeforBehind_triggered);

    connect(m_parameterView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtCtorFn::param_itemDelegate_closeEditor);
}

void
WtCtorFn::param_AddNew_triggered()
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
WtCtorFn::param_InsertNew_triggered()
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
WtCtorFn::param_Delete_triggered()
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
WtCtorFn::param_CopyToNew_triggered()
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
WtCtorFn::param_Up_triggered()
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
WtCtorFn::param_Down_triggered()
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
WtCtorFn::param_MoveToRow_triggered()
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
WtCtorFn::param_BeforBehind_triggered()
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
WtCtorFn::param_itemDelegate_closeEditor()
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
WtCtorFn::isEnabled_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setEnabled(true);
    } else {
        m_objPtr->setEnabled(false);
    }
}

void
WtCtorFn::isInline_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setInline(true);
    } else {
        m_objPtr->setInline(false);
    }
}

void
WtCtorFn::isExplicit_stateChanged(int  status)
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
WtCtorFn::isNoexcept_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setNoexcept(true);
    } else {
        m_objPtr->setNoexcept(false);
    }
}

void
WtCtorFn::fieldVal_itemDelegate_closeEditor()
{
    QModelIndex const  index = m_fieldValView->currentIndex();
    int const  row = index.row();

    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getDefValueCtor();
        std::string const  currVal = m_fieldValModel->data(index).
                toString().toUtf8().toStdString();

        switch (index.column()) {
        case 1 :
            rawDataVec[row] = currVal;
            m_objPtr->setDefValueCtor(rawDataVec);
            break;
        }
    }
}

void
WtCtorFn::baseClassVal_itemDelegate_closeEditor()
{
    QModelIndex const  index = m_baseClassValView->currentIndex();
    int const  row = index.row();

    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getInhValueBaseClass();
        std::string const  currVal = m_baseClassValModel->data(index).
                toString().toUtf8().toStdString();

        switch (index.column()) {
        case 1 :
            rawDataVec[row] = currVal;
            m_objPtr->setInhValueBaseClass(rawDataVec);
            break;
        }
    }
}

void
WtCtorFn::repParameterItem()
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
WtCtorFn::repFieldValItem()
{
    m_fieldValModel->removeRows(0, m_fieldValModel->rowCount());

    std::vector<Field> &  fieldRef = m_objPtr->getParentClassPtr()->getFieldRef();
    std::vector<std::string>  fieldVal = m_objPtr->getDefValueCtor();
    int const  width0 = m_fieldValView->columnWidth(0);
    int const  width1 = m_fieldValView->columnWidth(1);
    int const  defSize = static_cast<int>(fieldVal.size());
    for (int i = 0; i < defSize; ++i) {
        QStandardItem *  item0 = new QStandardItem(QString::fromStdString(
                fieldRef[i].getPrivateName()));
        item0->setFlags(Qt::NoItemFlags);
        item0->setFlags(Qt::ItemIsSelectable |
                Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(fieldVal[i]));
        QList<QStandardItem *>  items;
        items << item0 << item1;
        m_fieldValModel->appendRow(items);
    }
    m_fieldValView->setColumnWidth(0, width0);
    m_fieldValView->setColumnWidth(1, width1);
}

void
WtCtorFn::repBaseClassValItem()
{
    m_baseClassValModel->removeRows(0, m_baseClassValModel->rowCount());

    std::vector<std::tuple<std::string, Purview, bool>>  mulInhClass =
            m_objPtr->getParentClassPtr()->getMulInhClass();
    std::vector<std::string>  inhBaseClassVal = m_objPtr->getInhValueBaseClass();
    int const  width0 = m_baseClassValView->columnWidth(0);
    int const  width1 = m_baseClassValView->columnWidth(1);
    int const  inhSize = static_cast<int>(inhBaseClassVal.size());
    for (int i = 0; i < inhSize; ++i) {
        QStandardItem *  item0 = new QStandardItem(QString::fromStdString(
                std::get<0>(mulInhClass[i])));
        item0->setFlags(Qt::NoItemFlags);
        item0->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                            | Qt::ItemIsEnabled);
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
                inhBaseClassVal[i]));
        QList<QStandardItem *>  items;
        items << item0 << item1;
        m_baseClassValModel->appendRow(items);
    }
    m_baseClassValView->setColumnWidth(0, width0);
    m_baseClassValView->setColumnWidth(1, width1);
}

bool
WtCtorFn::nameCheckDuplication(std::string const &  fnName)
{
    bool  res = false;

    auto  rawDataVec = m_objPtr->getParam();
    for (const auto &  fn: rawDataVec) {
        res = fn.getParameterName() == fnName;
        if (res)  return res;
    }

    return res;
}

Function *
WtCtorFn::getObjPtr() const
{
    return m_objPtr;
}

void
WtCtorFn::setObjPtr(Function *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        m_baseClassDefVal->setText(QString::fromStdString(
                m_objPtr->getInhValueFirst()));
        m_attribute->setText(QString::fromStdString(m_objPtr->getAttribute()));
        m_codeEdit->setPlainText(QString::fromStdString(m_objPtr->getMCode()));

        m_isEnabled->setChecked(m_objPtr->isEnabled());
        m_isInline->setChecked(m_objPtr->isInline());
        m_isExplicit->setChecked(m_objPtr->isExplicit());
        m_isNoexcept->setChecked(m_objPtr->isNoexcept());

        repParameterItem();
        repFieldValItem();
        repBaseClassValItem();
    }
}

}
