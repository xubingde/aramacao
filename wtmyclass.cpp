#include <typeinfo>
#include <functional>
#include <algorithm>
#include <QInputDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QAction>
#include <QAbstractScrollArea>
#include <QFrame>
#include <QList>
#include "field.h"
#include "highlighter.h"
#include "twobeforebehind.h"
#include "fourbeforebehind.h"
#include "fmt.h"
#include "mystruct.h"
#include "mystructdec.h"
#include "myclassdec.h"
#include "wtmyclass.h"

namespace xu {

WtMyClass::WtMyClass(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_className(nullptr),
        m_attribute(nullptr),
        m_alignas(nullptr),
        m_beforBehindPb(nullptr),
        m_mainTab(nullptr),
        m_docmentClass(nullptr),
        m_isFinalClass(nullptr),
        m_isSetterReturnThis(nullptr),
        m_isTemplate(nullptr),
        m_classTypeGroup(nullptr),
        m_finalClass(nullptr),
        m_baseClass(nullptr),
        m_inheritClass(nullptr),
        m_templateView(nullptr),
        m_templateModel(nullptr),
        m_classNameInherit(nullptr),
        m_inheritIsVirtual(nullptr),
        m_inheritIdGroup(nullptr),
        m_baseId(nullptr),
        m_borthId(nullptr),
        m_inheritId(nullptr),
        m_mulInhClassView(nullptr),
        m_mulInhClassModel(nullptr),
        m_fieldView(nullptr),
        m_fieldModel(nullptr),
        m_fieldDocment(nullptr),
        m_fieldAlignas(nullptr),
        m_fieldAttribute(nullptr),
        m_fieldArray(nullptr),
        m_fieldIsMutable(nullptr),
        m_fieldIdRegularView(nullptr),
        m_fieldIdRegularModel(nullptr),
        m_fieldIdView(nullptr),
        m_fieldIdModel(nullptr),
        m_fieldIdToStringView(nullptr),
        m_fieldIdToStringModel(nullptr),
        m_fieldIdIsToString(nullptr),
        m_fieldActionView(nullptr),
        m_fieldActionModel(nullptr),
        m_fieldActionAutoCode(nullptr),
        m_fieldActionDoc(nullptr),
        m_fieldActionAttribute(nullptr),
        m_fieldActionInline(nullptr),
        m_fieldActionNoexcept(nullptr),
        m_fieldActionVirtual(nullptr),
        m_fieldActionOverride(nullptr),
        m_fieldActionFinal(nullptr),
        m_fieldActionDelIdxView(nullptr),
        m_fieldActionDelIdxModel(nullptr),
        m_fieldActionInsertIdxView(nullptr),
        m_fieldActionInsertIdxModel(nullptr),
        m_fieldActionInsertCode(nullptr)
{
    init_obj();
    connect_obj();
    display_obj();
}

WtMyClass::~WtMyClass() noexcept
{
}

void
WtMyClass::className_editingFinished()
{
    QStandardItem *  itemPtr = getItemPtr();
    if (!m_objPtr)  return;

    std::string const  oldVal = m_objPtr->getClassName();
    std::string const  currVal = m_className->text().toUtf8().toStdString();
    if (oldVal == currVal)  return;
    m_objPtr->setClassName(currVal);
    std::string const  newVal = m_objPtr->getClassName();
    if (currVal != newVal) {
        m_className->setText(QString::fromStdString(newVal));
    }
    QVariant  treeLabel(QString::fromStdString(m_objPtr->getTreeLabel()));
    itemPtr->setData(treeLabel, Qt::EditRole);

    QStandardItem *  parentItem = itemPtr->parent();
    int const  count = parentItem->rowCount();
    for (int  i = 0; i < count; ++i) {
        QStandardItem *  item = parentItem->child(i);
        Etype const  etp = static_cast<Etype>(item->data(
                Qt::UserRole + 1).toInt());
        if (etp == Etype::eClassDeclaration) {
            MyClassDec *  ptr = static_cast<MyClassDec *>(item->data(
                    Qt::UserRole + 2).value<void *>());
            std::string const  cName = ptr->getClassName();
            if (newVal == cName) {
                ptr->setParentClassPtr(m_objPtr);
            } else {
                ptr->setParentClassPtr(nullptr);
            }
        }
    }
}

void
WtMyClass::attribute_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setAttribute(m_attribute->text().toUtf8().toStdString());
}

void
WtMyClass::alignas_editingFinished()
{
    if (!m_objPtr)  return;

    int const  oldVal = m_objPtr->getAlignByte();
    int  currVal = 0;
    bool  ok = false;
    currVal = m_alignas->text().toInt(&ok);
    if (!ok) {
        m_alignas->setText(QString::fromStdString(std::to_string(currVal)));
    }
    if (oldVal == currVal)  return;

    m_objPtr->setAlignByte(currVal);
    int const  newVal = m_objPtr->getAlignByte();
    if (currVal != newVal) {
        m_alignas->setText(QString::fromStdString(std::to_string(newVal)));
    }
}

void
WtMyClass::beforBehindPb_clicked()
{
    if (!m_objPtr)  return;

    std::string const  title = "Class: " + m_objPtr->getClassName();
    QString const  beforeFirstLabel("    class definition { insert ( .h )");
    QString const  behindFirstLabel("    class definition { follow ( .h )");
    QString const  beforeSecondLabel("    class definition }; insert ( .h )");
    QString const  behindSecondLabel("    class definition }; follow ( .h )");
    std::string  hBeginBefore = m_objPtr->getHBeginBefore();
    std::string  hBeginBehind = m_objPtr->getHBeginBehind();
    std::string  hEndBefore = m_objPtr->getHEndBefore();
    std::string  hEndBehind = m_objPtr->getHEndBehind();

    FourBeforeBehind  fbe(title,
            beforeFirstLabel, behindFirstLabel, hBeginBefore, hBeginBehind,
            beforeSecondLabel, behindSecondLabel, hEndBefore, hEndBehind);
    fbe.exec();
    m_objPtr->setHBeginBefore(hBeginBefore);
    m_objPtr->setHBeginBehind(hBeginBehind);
    m_objPtr->setHEndBefore(hEndBefore);
    m_objPtr->setHEndBehind(hEndBehind);
}

void
WtMyClass::docmentEdit_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setDocment(m_docmentClass->toHtml().toUtf8().toStdString());
}

void
WtMyClass::fieldConnect()
{
    QAction *  actAddItem = new QAction(tr("Add New"));
    QAction *  actInsertNew = new QAction(tr("Insert New"));
    QAction *  actDelete = new QAction(tr("Delete"));
    QAction *  actCopyToNew = new QAction(tr("Copy To New"));
    actAddItem->setParent(this);
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
    QAction *  actBeforBehind = new QAction(tr("Insert && Follow"));
    m_fieldView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_fieldView->addAction(actAddItem);
    m_fieldView->addAction(actInsertNew);
    m_fieldView->addAction(actDelete);
    m_fieldView->addAction(actCopyToNew);
    m_fieldView->addAction(actSpt);
    m_fieldView->addAction(actUp);
    m_fieldView->addAction(actDown);
    m_fieldView->addAction(actMoveToRow);
    m_fieldView->addAction(actSpt2);
    m_fieldView->addAction(actBeforBehind);

    connect(actAddItem, &QAction::triggered,
            this, &WtMyClass::field_AddItem_triggered);
    connect(actInsertNew, &QAction::triggered,
            this, &WtMyClass::field_InsertNew_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtMyClass::field_Delete_triggered);
    connect(actCopyToNew, &QAction::triggered,
            this, &WtMyClass::field_CopyToNew_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtMyClass::field_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtMyClass::field_Down_triggered);
    connect(actMoveToRow, &QAction::triggered,
            this, &WtMyClass::field_MoveToRow_triggered);

    connect(actBeforBehind, &QAction::triggered,
            this, &WtMyClass::field_BeforBehind_triggered);

    connect(m_fieldView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtMyClass::field_itemDelegate_closeEditor);
    connect(m_fieldView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &WtMyClass::field_selectChanged);

    connect(m_fieldAttribute, &QLineEdit::editingFinished,
            this, &WtMyClass::field_attribute_editingFinished);
    connect(m_fieldArray, &QLineEdit::editingFinished,
            this, &WtMyClass::field_array_editingFinished);
    connect(m_fieldAlignas, &QLineEdit::editingFinished,
            this, &WtMyClass::field_alignas_editingFinished);
    connect(m_fieldDocment, &QTextEdit::textChanged,
            this, &WtMyClass::field_docment_textChanged);
    connect(m_fieldIsMutable, &QCheckBox::stateChanged,
            this, &WtMyClass::field_isMutable_stateChanged);
}

void
WtMyClass::field_AddItem_triggered()
{
    if (!m_objPtr)  return;

    Field  newData;
    QList<QStandardItem *>  items;
    QStandardItem *  item0 = new QStandardItem(QString::fromStdString(
            newData.getFieldName()));
    QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
            newData.getTypeName()));
    QStandardItem *  item2 = new QStandardItem(QString::fromStdString(
            newData.getDefValue()));
    QStandardItem *  isPtr = new QStandardItem;
    isPtr->setData(QVariant(false), Qt::EditRole | Qt::DisplayRole);
    items << item0 << item1 << item2 << isPtr;

    m_objPtr->appendField(std::move(newData));

    m_fieldModel->appendRow(items);
}

void
WtMyClass::field_InsertNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        Field  newData;
        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(QString::fromStdString(
                newData.getFieldName()));
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
                newData.getTypeName()));
        QStandardItem *  item2 = new QStandardItem(QString::fromStdString(
                newData.getDefValue()));
        QStandardItem *  isPtr = new QStandardItem;
        isPtr->setData(QVariant(false), Qt::EditRole | Qt::DisplayRole);
        items << item0 << item1 << item2 << isPtr;

        m_objPtr->insertField(std::move(newData), row);

        m_fieldModel->insertRow(row, items);
    } else {
        field_AddItem_triggered();
    }
}

void
WtMyClass::field_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        m_objPtr->deleteField(row);

        m_fieldModel->removeRows(row, 1);

        int const  count = m_fieldModel->rowCount();
        if (count > 0 && row < count) {
            m_fieldView->setCurrentIndex(m_fieldModel->index(row, index.column()));
        } else if (count > 0 && row != 0) {
            m_fieldView->setCurrentIndex(m_fieldModel->index(row - 1, index.column()));
        } else if (count == 1) {
            m_fieldView->setCurrentIndex(m_fieldModel->index(0, index.column()));
        }
    }
}

void
WtMyClass::field_CopyToNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getField();
        Field  newData = rawDataVec[row];
        std::string const  oldName = rawDataVec[row].getFieldName();
        std::string const  baseNewName = oldName + "_";
        std::string  newName;
        size_t  nameIdx = 0;
        while (true) {
            ++nameIdx;
            newName = baseNewName + std::to_string(nameIdx);
            if (!nameCheckDuplication(newName)) {
                break;
            }
        }
        newData.setFieldName(newName);
        m_objPtr->insertField(newData, row + 1);

        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(QString::fromStdString(
                newData.getFieldName()));
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
                newData.getTypeName()));
        QStandardItem *  item2 = new QStandardItem(QString::fromStdString(
                newData.getDefValue()));
        QStandardItem *  isPtr = new QStandardItem;
        isPtr->setData(QVariant(false), Qt::EditRole | Qt::DisplayRole);
        items << item0 << item1 << item2 << isPtr;

        m_fieldModel->insertRow(row + 1, items);
    }
}

void
WtMyClass::field_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        m_objPtr->swapField(row, row - 1);

        auto const  item = m_fieldModel->takeRow(row);
        m_fieldModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_fieldView->setCurrentIndex(idx);
    }
}

void
WtMyClass::field_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    int const  count = m_fieldModel->rowCount();
    if (index.isValid() && count > 1 && row != count - 1) {
        m_objPtr->swapField(row, row + 1);

        auto const  item = m_fieldModel->takeRow(row + 1);
        m_fieldModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_fieldView->setCurrentIndex(idx);
    }
}

void
WtMyClass::field_MoveToRow_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  count = m_fieldModel->rowCount();
    size_t  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        size_t  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (!ok)  return;

        m_objPtr->moveField(currRow, movetoRow);

        auto const  item = m_fieldModel->takeRow(static_cast<int>(currRow));
        m_fieldModel->insertRow(static_cast<int>(movetoRow), item);
        QModelIndex  idx = index.sibling(static_cast<int>(movetoRow), index.column());
        m_fieldView->setCurrentIndex(idx);
    }
}

void
WtMyClass::field_BeforBehind_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        Field  rawData = m_objPtr->getField()[row];

        std::string const  title("Field: " + rawData.getFieldName());
        QString const  beforeLabel("    Field definition Insert ");
        QString const  behindLabel("    Field definition Follow ");
        std::string  beforeString = rawData.getBefore();
        std::string  behindString = rawData.getBehind();

        TwoBeforeBehind  tbe(title, beforeLabel, behindLabel, beforeString, behindString);
        tbe.exec();
        rawData.setBefore(std::move(beforeString));
        rawData.setBehind(std::move(behindString));

        m_objPtr->updateField(std::move(rawData), row);
    }
}

void
WtMyClass::field_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        Field  rawData = m_objPtr->getField()[row];
        std::string const  currVal = m_fieldModel->data(index).
                toString().toUtf8().toStdString();

        switch (index.column()) {
        case 0 :
            {
                std::string const  oldVal = rawData.getFieldName();
                if (oldVal == currVal)  return;
                rawData.setFieldName(currVal);
                std::string const  newVal = rawData.getFieldName();
                if (currVal != newVal) {
                    m_fieldModel->setData(index, QVariant(
                            QString::fromStdString(newVal)));
                }
                m_objPtr->updateField(std::move(rawData), row);
            }
            break;
        case 1 :
            rawData.setTypeName(currVal);
            m_objPtr->updateField(std::move(rawData), row);
            break;
        case 2 :
            rawData.setDefValue(currVal);
            m_objPtr->updateField(std::move(rawData), row);
            break;
        case 3 :
            {
                bool const  isPtr = m_fieldModel->data(index).toBool();
                if (isPtr == rawData.isPointer()) {
                    return;
                }
                rawData.setPointer(isPtr);
                m_objPtr->updateField(std::move(rawData), row);
            }
            break;
        }
    }
}

void
WtMyClass::field_selectChanged()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    if (index.isValid()) {
        m_fieldDocment->setReadOnly(false);
        m_fieldAlignas->setReadOnly(false);
        m_fieldAttribute->setReadOnly(false);
        m_fieldArray->setReadOnly(false);

        m_fieldIsMutable->setEnabled(true);

        Field const  fd = m_objPtr->getField()[index.row()];
        m_fieldDocment->setHtml(QString::fromStdString(fd.getDocment()));
        m_fieldAttribute->setText(QString::fromStdString(fd.getAttribute()));
        m_fieldAlignas->setText(QString::fromStdString(std::to_string(fd.getAlignByte())));
        m_fieldArray->setText(QString::fromStdString(fd.getArray()));

        m_fieldIsMutable->setChecked(fd.isMutable());
    } else {
        m_fieldDocment->setReadOnly(true);
        m_fieldDocment->clear();
        m_fieldAlignas->setReadOnly(true);
        m_fieldAlignas->clear();
        m_fieldAttribute->setReadOnly(true);
        m_fieldAttribute->clear();
        m_fieldArray->setReadOnly(true);
        m_fieldArray->clear();

        m_fieldIsMutable->setEnabled(false);
    }
}

void
WtMyClass::field_attribute_editingFinished()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        Field  fd = m_objPtr->getField()[row];
        fd.setAttribute(m_fieldAttribute->text().toUtf8().toStdString());
        m_objPtr->updateField(std::move(fd), row);
    }
}

void
WtMyClass::field_array_editingFinished()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        Field  fd = m_objPtr->getField()[row];
        fd.setArray(m_fieldArray->text().toUtf8().toStdString());
        m_objPtr->updateField(std::move(fd), row);
    }
}

void
WtMyClass::field_alignas_editingFinished()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        Field  fd = m_objPtr->getField()[row];
        int const  oldVal = fd.getAlignByte();
        int  currIntVal = 0;
        bool  ok = false;
        currIntVal = m_fieldAlignas->text().toInt(&ok);
        if (!ok) {
            m_fieldAlignas->setText(
                    QString::fromStdString(std::to_string(currIntVal)));
        }
        if (oldVal == currIntVal)  return;
        fd.setAlignByte(currIntVal);
        int const  newVal = fd.getAlignByte();
        if (currIntVal != newVal) {
            m_fieldAlignas->setText(
                    QString::fromStdString(std::to_string(newVal)));
        }
        m_objPtr->updateField(std::move(fd), row);
    }
}

void
WtMyClass::field_docment_textChanged()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        Field  fd = m_objPtr->getField()[row];
        fd.setDocment(m_fieldDocment->toHtml().toUtf8().toStdString());
        m_objPtr->updateField(std::move(fd), row);
    }
}

void
WtMyClass::field_isMutable_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        bool  currVal = false;
        if (status == Qt::Checked) {
            currVal = true;
        }
        Field  fd = m_objPtr->getField()[row];
        fd.setMutable(currVal);
        m_objPtr->updateField(std::move(fd), row);
    }
}

void
WtMyClass::init_obj()
{
    m_className = new QLineEdit;
    m_attribute = new QLineEdit;
    m_alignas = new QLineEdit;

    m_fieldAttribute = new QLineEdit;
    m_fieldAlignas = new QLineEdit;
    m_fieldArray = new QLineEdit;

    m_mainTab = new QTabWidget;

    m_beforBehindPb = new QPushButton(tr(" Insert && Follow "));
    m_docmentClass = new QTextEdit;
    new Highlighter(m_docmentClass->document());

    m_classNameInherit = new QLineEdit;
    m_fieldDocment = new QTextEdit;
    new Highlighter(m_fieldDocment->document());

    m_fieldActionAutoCode = new CodeEditor;
    new Highlighter(m_fieldActionAutoCode->document());
    m_fieldActionDoc = new QTextEdit;
    new Highlighter(m_fieldActionDoc->document());
    m_fieldActionInsertCode = new CodeEditor;
    new Highlighter(m_fieldActionInsertCode->document());
    m_fieldActionAttribute = new QLineEdit;

    m_isFinalClass = new QCheckBox(tr("Class isFinal"));
    m_isSetterReturnThis = new QCheckBox(tr("setter is return *this"));
    m_isTemplate = new QCheckBox(tr("is Template Class"));
    m_inheritIsVirtual = new QCheckBox(tr("Base Class isVirtual"));

    m_fieldIdIsToString = new QCheckBox(tr("Append Field"));

    m_fieldActionInline = new QCheckBox(tr("inline"));
    m_fieldActionVirtual = new QCheckBox(tr("virtual"));
    m_fieldActionOverride = new QCheckBox(tr("override"));
    m_fieldActionFinal = new QCheckBox(tr("final"));
    m_fieldActionNoexcept = new QCheckBox(tr("noexcept"));

    m_fieldIsMutable = new QCheckBox(tr("mutable"));

    m_classTypeGroup = new QButtonGroup(this);
    m_finalClass = new QRadioButton(tr("Final_Class"));
    m_baseClass = new QRadioButton(tr("Base_Class"));
    m_inheritClass = new QRadioButton(tr("Derived_Class"));
    m_classTypeGroup->addButton(m_finalClass);
    m_classTypeGroup->addButton(m_baseClass);
    m_classTypeGroup->addButton(m_inheritClass);
    m_finalClass->setChecked(true);

    m_inheritIdGroup = new QButtonGroup(this);
    m_baseId = new QRadioButton(tr("Base_Id"));
    m_borthId = new QRadioButton(tr("Borth_Id"));
    m_inheritId = new QRadioButton(tr("Inherit_Id"));
    m_inheritIdGroup->addButton(m_baseId);
    m_inheritIdGroup->addButton(m_borthId);
    m_inheritIdGroup->addButton(m_inheritId);
    m_baseId->setChecked(true);

    m_templateView = new QTableView;
    m_templateModel = new QStandardItemModel;
    m_templateModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("typename / class")));
    m_templateModel->setHorizontalHeaderItem(1,
                        new QStandardItem(tr("Type Name / T")));
    m_templateModel->setHorizontalHeaderItem(2,
                        new QStandardItem(tr("Docment")));
    m_templateModel->setHorizontalHeaderItem(3,
                        new QStandardItem(tr("Defalut Value")));
    m_templateView->setModel(m_templateModel);

    m_mulInhClassView = new QTableView;
    m_mulInhClassModel = new QStandardItemModel;
    m_mulInhClassModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Base Class")));
    m_mulInhClassModel->setHorizontalHeaderItem(1,
                        new QStandardItem(tr("Encapsulation")));
    m_mulInhClassModel->setHorizontalHeaderItem(2,
                        new QStandardItem(tr("isVirtual")));
    m_mulInhClassView->setModel(m_mulInhClassModel);

    m_fieldView = new QTableView;
    m_fieldModel = new QStandardItemModel;
    m_fieldModel->setHorizontalHeaderItem(0,
            new QStandardItem(tr("Field Name")));
    m_fieldModel->setHorizontalHeaderItem(1,
            new QStandardItem(tr("Type")));
    m_fieldModel->setHorizontalHeaderItem(2,
            new QStandardItem(tr("Default Value")));
    m_fieldModel->setHorizontalHeaderItem(3,
            new QStandardItem(tr("isPointer")));
    m_fieldView->setModel(m_fieldModel);

    m_fieldView->setColumnWidth(0, 220);
    m_fieldView->setColumnWidth(1, 200);
    m_fieldView->setColumnWidth(2, 230);
    m_fieldView->setColumnWidth(3, 100);

    m_fieldIdRegularView = new QTableView;
    m_fieldIdRegularModel = new QStandardItemModel;
    m_fieldIdRegularModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Index")));
    m_fieldIdRegularModel->setHorizontalHeaderItem(1,
                        new QStandardItem(tr("Field Name")));
    m_fieldIdRegularView->setModel(m_fieldIdRegularModel);
    m_fieldIdRegularView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_fieldIdView = new QTableView;
    m_fieldIdModel = new QStandardItemModel;
    m_fieldIdModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Index")));
    m_fieldIdModel->setHorizontalHeaderItem(1,
                        new QStandardItem(tr("Field Name")));
    m_fieldIdView->setModel(m_fieldIdModel);
    m_fieldIdView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_fieldIdToStringView = new QTableView;
    m_fieldIdToStringModel = new QStandardItemModel;
    m_fieldIdToStringModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Index")));
    m_fieldIdToStringModel->setHorizontalHeaderItem(1,
                        new QStandardItem(tr("Field Name")));
    m_fieldIdToStringView->setModel(m_fieldIdToStringModel);
    m_fieldIdToStringView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_fieldIdIsToString = new QCheckBox(tr("Append Field"));

    m_fieldActionView = new QTreeView;
    m_fieldActionModel = new QStandardItemModel;
    m_fieldActionModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Field / Action")));
    m_fieldActionModel->setHorizontalHeaderItem(1,
                        new QStandardItem(tr("Function Declaration")));
    m_fieldActionView->setModel(m_fieldActionModel);
    m_fieldActionView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_fieldActionDelIdxView = new QTableView;
    m_fieldActionDelIdxModel = new QStandardItemModel;
    m_fieldActionDelIdxModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Index")));
    m_fieldActionDelIdxView->setModel(m_fieldActionDelIdxModel);
    m_fieldActionDelIdxView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_fieldActionInsertIdxView = new QTableView;
    m_fieldActionInsertIdxModel = new QStandardItemModel;
    m_fieldActionInsertIdxModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Index")));
    m_fieldActionInsertIdxView->setModel(m_fieldActionInsertIdxModel);
    m_fieldActionInsertIdxView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void
WtMyClass::connect_obj()
{
    connect(m_className, &QLineEdit::editingFinished,
            this, &WtMyClass::className_editingFinished);
    connect(m_attribute, &QLineEdit::editingFinished,
            this, &WtMyClass::attribute_editingFinished);
    connect(m_alignas, &QLineEdit::editingFinished,
            this, &WtMyClass::alignas_editingFinished);
    connect(m_beforBehindPb, &QPushButton::clicked,
            this, &WtMyClass::beforBehindPb_clicked);
    connect(m_docmentClass, &QTextEdit::textChanged,
            this, &WtMyClass::docmentEdit_textChanged);

    fieldConnect();
}

void
WtMyClass::display_obj()
{
    QVBoxLayout *  vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *  hboxClass = new QHBoxLayout;
    QHBoxLayout *  hboxProperty = new QHBoxLayout;
    hboxClass->setContentsMargins(0, 0, 0, 0);
    hboxProperty->setContentsMargins(0, 0, 0, 0);
    vbox->addLayout(hboxClass);
    vbox->addLayout(hboxProperty);

    {
        QFormLayout *  fm0 = new QFormLayout;
        QFormLayout *  fm1 = new QFormLayout;
        QFormLayout *  fm2 = new QFormLayout;
        QHBoxLayout *  fm3 = new QHBoxLayout;
        fm0->setContentsMargins(0, 0, 0, 0);
        fm1->setContentsMargins(0, 0, 0, 0);
        fm2->setContentsMargins(0, 0, 0, 0);
        fm3->setContentsMargins(0, 0, 0, 0);
        hboxClass->addLayout(fm0);
        hboxClass->addLayout(fm1);
        hboxClass->addLayout(fm2);
        hboxClass->addLayout(fm3);

        QLabel *  label0 = new QLabel(tr("Class Name"));
        QLabel *  label1 = new QLabel(tr("Attribute"));
        QLabel *  label2 = new QLabel(tr("Alignas"));
        fm0->addRow(label0, m_className);
        fm1->addRow(label1, m_attribute);
        fm2->addRow(label2, m_alignas);
        fm3->addWidget(m_beforBehindPb);
        hboxClass->setStretch(0, 40);
        hboxClass->setStretch(1, 30);
        hboxClass->setStretch(2, 15);
        hboxClass->setStretch(3, 15);
    }
    {
        hboxProperty->addWidget(m_mainTab);
    }

    QSplitter *  spvField = new QSplitter(Qt::Vertical);
    spvField->setHandleWidth(1);
    QAbstractScrollArea *  spvFieldId = new QAbstractScrollArea;
    QAbstractScrollArea *  spvFieldAction = new QAbstractScrollArea;
    QAbstractScrollArea *  spvGeneral = new QAbstractScrollArea;
    m_mainTab->addTab(spvField, tr(" Field "));
    m_mainTab->addTab(spvFieldId, tr(" Field_Id "));
    m_mainTab->addTab(spvFieldAction, tr(" Field_Action "));
    m_mainTab->addTab(spvGeneral, tr(" Class_General "));

    {
        QFrame *  fr = new QFrame;
        fr->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QHBoxLayout *  hbox1 = new QHBoxLayout(fr);
        hbox1->setContentsMargins(0, 3, 0, 0);

        QFormLayout *  fm0 = new QFormLayout;
        QFormLayout *  fm1 = new QFormLayout;
        QFormLayout *  fm2 = new QFormLayout;
        QHBoxLayout *  fm3 = new QHBoxLayout;
        fm0->setContentsMargins(0, 0, 0, 0);
        fm1->setContentsMargins(0, 0, 0, 0);
        fm2->setContentsMargins(0, 0, 0, 0);
        fm3->setContentsMargins(0, 0, 0, 0);
        hbox1->addLayout(fm0);
        hbox1->addLayout(fm1);
        hbox1->addLayout(fm2);
        hbox1->addLayout(fm3);

        QLabel *  label0 = new QLabel(tr("Field Attribute"));
        QLabel *  label1 = new QLabel(tr("Field Array"));
        QLabel *  label2 = new QLabel(tr("Field Alignas"));
        fm0->addRow(label0, m_fieldAttribute);
        fm1->addRow(label1, m_fieldArray);
        fm2->addRow(label2, m_fieldAlignas);
        fm3->addWidget(m_fieldIsMutable);
        hbox1->setStretch(0, 38);
        hbox1->setStretch(1, 30);
        hbox1->setStretch(2, 20);
        hbox1->setStretch(3, 12);

        spvField->addWidget(m_fieldView);
        spvField->addWidget(m_fieldDocment);
        spvField->addWidget(fr);
        spvField->setStretchFactor(0, 90);
        spvField->setStretchFactor(1, 9);
        spvField->setStretchFactor(2, 1);
    }
}

void
WtMyClass::fillData()
{
    m_className->setText(QString::fromStdString(m_objPtr->getClassName()));
    m_attribute->setText(QString::fromStdString(m_objPtr->getAttribute()));
    m_alignas->setText(QString::fromStdString(
            std::to_string(m_objPtr->getAlignByte())));
    m_docmentClass->setText(QString::fromStdString(m_objPtr->getDocment()));

    repField();
}

void
WtMyClass::repField()
{
    m_fieldModel->removeRows(0, m_fieldModel->rowCount());
    std::vector<Field> const  fds = m_objPtr->getField();
    for (auto const &  it: fds) {
        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(QString::fromStdString(
                it.getFieldName()));
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
                it.getTypeName()));
        QStandardItem *  item2 = new QStandardItem(QString::fromStdString(
                it.getDefValue()));
        QStandardItem *  isPtr = new QStandardItem;
        isPtr->setData(QVariant(it.isPointer()), Qt::EditRole | Qt::DisplayRole);
        items << item0 << item1 << item2 << isPtr;
        m_fieldModel->appendRow(items);
    }
}

bool
WtMyClass::nameCheckDuplication(std::string const &  fnName)
{
    bool  res = false;

    auto  rawDataVec = m_objPtr->getField();
    for (const auto &  fn: rawDataVec) {
        res = fn.getFieldName() == fnName;
        if (res)  return res;
    }

    return res;
}

MyClass *
WtMyClass::getObjPtr() const
{
    return m_objPtr;
}

void
WtMyClass::setObjPtr(MyClass *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        fillData();
    }
}

}
