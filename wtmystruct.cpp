#include <typeinfo>
#include <QInputDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QAction>
#include <QList>
#include "field.h"
#include "highlighter.h"
#include "twobeforebehind.h"
#include "fmt.h"
#include "wtmystruct.h"
#include "mystructdec.h"

namespace xu {

WtMyStruct::WtMyStruct(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_itemPtr(nullptr),
        m_structName(nullptr),
        m_attribute(nullptr),
        m_alignas(),
        m_beforBehindPb(nullptr),
        m_docmentEdit(nullptr),
        m_structItemView(nullptr),
        m_structItemModel(nullptr)
{
    m_structName = new QLineEdit;
    m_attribute = new QLineEdit;
    m_alignas = new QLineEdit;
    m_beforBehindPb = new QPushButton(tr(" Insert && Follow "));
    m_docmentEdit = new QTextEdit;
    new Highlighter(m_docmentEdit->document());

    m_structItemView = new QTableView;
    m_structItemModel = new QStandardItemModel;
    m_structItemModel->setHorizontalHeaderItem(0,
            new QStandardItem(tr("Field Name")));
    m_structItemModel->setHorizontalHeaderItem(1,
            new QStandardItem(tr("Type")));
    m_structItemModel->setHorizontalHeaderItem(2,
            new QStandardItem(tr("Default Value")));
    m_structItemModel->setHorizontalHeaderItem(3,
            new QStandardItem(tr("Docment")));
    m_structItemModel->setHorizontalHeaderItem(4,
            new QStandardItem(tr("Alignas")));
    m_structItemModel->setHorizontalHeaderItem(5,
            new QStandardItem(tr("Attribute")));
    m_structItemView->setModel(m_structItemModel);

    m_structItemView->setColumnWidth(0, 180);
    m_structItemView->setColumnWidth(1, 160);
    m_structItemView->setColumnWidth(2, 120);
    m_structItemView->setColumnWidth(3, 180);
    m_structItemView->setColumnWidth(4, 60);
    m_structItemView->setColumnWidth(5, 70);

    connect(m_structName, &QLineEdit::editingFinished,
            this, &WtMyStruct::structName_editingFinished);
    connect(m_attribute, &QLineEdit::editingFinished,
            this, &WtMyStruct::attribute_editingFinished);
    connect(m_alignas, &QLineEdit::editingFinished,
            this, &WtMyStruct::alignas_editingFinished);
    connect(m_beforBehindPb, &QPushButton::clicked,
            this, &WtMyStruct::beforBehindPb_clicked);
    connect(m_docmentEdit, &QTextEdit::textChanged,
            this, &WtMyStruct::docmentEdit_textChanged);
    structItemConnect();

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

    QLabel *  label0 = new QLabel(tr("Struct Name"));
    QLabel *  label1 = new QLabel(tr("Attribute"));
    QLabel *  label2 = new QLabel(tr("Alignas"));
    fm0->addRow(label0, m_structName);
    fm1->addRow(label1, m_attribute);
    fm2->addRow(label2, m_alignas);
    fm3->addWidget(m_beforBehindPb);
    hbox1->setStretch(0, 40);
    hbox1->setStretch(1, 30);
    hbox1->setStretch(2, 15);
    hbox1->setStretch(3, 15);

    QSplitter *  vH = new QSplitter(Qt::Vertical);
    vH->setHandleWidth(1);
    vbox2->addWidget(vH);

    vH->addWidget(m_structItemView);
    vH->addWidget(m_docmentEdit);
    vH->setStretchFactor(0, 70);
    vH->setStretchFactor(1, 30);
}

WtMyStruct::~WtMyStruct() noexcept
{
}

void
WtMyStruct::structName_editingFinished()
{
    if (!m_objPtr)  return;

    std::string const  oldVal = m_objPtr->getName();
    std::string const  currVal = m_structName->text().toUtf8().toStdString();
    if (oldVal == currVal)  return;
    m_objPtr->setName(currVal);
    std::string const  newVal = m_objPtr->getName();
    if (currVal != newVal) {
        m_structName->setText(QString::fromStdString(newVal));
    }
    QVariant  treeLabel(QString::fromStdString(m_objPtr->getTreeLabel()));
    m_itemPtr->setData(treeLabel, Qt::EditRole);

    QStandardItem *  parentItem = m_itemPtr->parent();
    int const  count = parentItem->rowCount();
    for (int  i = 0; i < count; ++i) {
        QStandardItem *  item = parentItem->child(i);
        Etype const  etp = static_cast<Etype>(item->data(
                Qt::UserRole + 1).toInt());
        if (etp == Etype::eStructDeclaration) {
            MyStructDec *  ptr = static_cast<MyStructDec *>(item->data(
                    Qt::UserRole + 2).value<void *>());
            std::string const  cName = ptr->getStructName();
            if (newVal == cName) {
                ptr->setParentStructPtr(m_objPtr);
            } else {
                ptr->setParentStructPtr(nullptr);
            }
        }
    }
}

void
WtMyStruct::attribute_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setAttribute(m_attribute->text().toUtf8().toStdString());
}

void
WtMyStruct::alignas_editingFinished()
{
    if (!m_objPtr)  return;

    int const  oldVal = m_objPtr->getAlignas();
    int  currVal = 0;
    bool  ok = false;
    currVal = m_alignas->text().toInt(&ok);
    if (!ok) {
        m_alignas->setText(QString::fromStdString(std::to_string(currVal)));
    }
    if (oldVal == currVal)  return;

    m_objPtr->setAlignas(currVal);
    int const  newVal = m_objPtr->getAlignas();
    if (currVal != newVal) {
        m_alignas->setText(QString::fromStdString(std::to_string(newVal)));
    }
}

void
WtMyStruct::beforBehindPb_clicked()
{
    if (!m_objPtr)  return;

    std::string const  title("Struct: " + m_objPtr->getName());
    QString const  beforeLabel("    Struct Insert ");
    QString const  behindLabel("    Struct Follow ");
    std::string  beforeString = m_objPtr->getBefore();
    std::string  behindString = m_objPtr->getBehind();

    TwoBeforeBehind  tbe(title, beforeLabel, behindLabel, beforeString, behindString);
    tbe.exec();
    m_objPtr->setBefore(std::move(beforeString));
    m_objPtr->setBehind(std::move(behindString));
}

void
WtMyStruct::docmentEdit_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setDocment(m_docmentEdit->toHtml().toUtf8().toStdString());
}

void
WtMyStruct::structItemConnect()
{
    QAction *  actAddItem = new QAction(tr("Add New Struct Item"));
    QAction *  actInsertNew = new QAction(tr("Insert New Struct Item"));
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
    m_structItemView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_structItemView->addAction(actAddItem);
    m_structItemView->addAction(actInsertNew);
    m_structItemView->addAction(actDelete);
    m_structItemView->addAction(actCopyToNew);
    m_structItemView->addAction(actSpt);
    m_structItemView->addAction(actUp);
    m_structItemView->addAction(actDown);
    m_structItemView->addAction(actMoveToRow);
    m_structItemView->addAction(actSpt2);
    m_structItemView->addAction(actBeforBehind);

    connect(actAddItem, &QAction::triggered,
            this, &WtMyStruct::structItem_AddItem_triggered);
    connect(actInsertNew, &QAction::triggered,
            this, &WtMyStruct::structItem_InsertNew_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtMyStruct::structItem_Delete_triggered);
    connect(actCopyToNew, &QAction::triggered,
            this, &WtMyStruct::structItem_CopyToNew_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtMyStruct::structItem_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtMyStruct::structItem_Down_triggered);
    connect(actMoveToRow, &QAction::triggered,
            this, &WtMyStruct::structItem_MoveToRow_triggered);

    connect(actBeforBehind, &QAction::triggered,
            this, &WtMyStruct::structItem_BeforBehind_triggered);

    connect(m_structItemView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtMyStruct::structItem_itemDelegate_closeEditor);
}

void
WtMyStruct::structItem_AddItem_triggered()
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
    QStandardItem *  item3 = new QStandardItem(QString::fromStdString(
            newData.getDocment()));
    QStandardItem *  item4 = new QStandardItem(QString::fromStdString(
            std::to_string(newData.getAlignByte())));
    QStandardItem *  item5 = new QStandardItem(QString::fromStdString(
            newData.getAttribute()));
    items << item0 << item1 << item2 << item3 << item4 << item5;

    std::vector<Field>  rawDataVec = m_objPtr->getField();
    rawDataVec.push_back(std::move(newData));
    m_objPtr->setField(std::move(rawDataVec));

    m_structItemModel->appendRow(items);
}

void
WtMyStruct::structItem_InsertNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_structItemView->currentIndex();
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
        QStandardItem *  item3 = new QStandardItem(QString::fromStdString(
                newData.getDocment()));
        QStandardItem *  item4 = new QStandardItem(QString::fromStdString(
                std::to_string(newData.getAlignByte())));
        QStandardItem *  item5 = new QStandardItem(QString::fromStdString(
                newData.getAttribute()));
        items << item0 << item1 << item2 << item3 << item4 << item5;

        auto  rawDataVec = m_objPtr->getField();
        rawDataVec.insert(rawDataVec.begin() + row, std::move(newData));
        m_objPtr->setField(std::move(rawDataVec));

        m_structItemModel->insertRow(row, items);
    } else {
        structItem_AddItem_triggered();
    }
}

void
WtMyStruct::structItem_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_structItemView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getField();
        rawDataVec.erase(rawDataVec.begin() + row);
        m_objPtr->setField(std::move(rawDataVec));

        m_structItemModel->removeRows(row, 1);

        int const  count = m_structItemModel->rowCount();
        if (count > 0 && row < count) {
            m_structItemView->setCurrentIndex(m_structItemModel->index(row, index.column()));
        } else if (count > 0 && row != 0) {
            m_structItemView->setCurrentIndex(m_structItemModel->index(row - 1, index.column()));
        } else if (count == 1) {
            m_structItemView->setCurrentIndex(m_structItemModel->index(0, index.column()));
        }
    }
}

void
WtMyStruct::structItem_CopyToNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_structItemView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getField();
        Field  newData = rawDataVec[row];
        std::string const  oldName = rawDataVec[row].getFieldName();
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
        newData.setFieldName(newName);
        rawDataVec.insert(rawDataVec.begin() + row + 1, newData);
        m_objPtr->setField(std::move(rawDataVec));

        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(QString::fromStdString(
                newData.getFieldName()));
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
                newData.getTypeName()));
        QStandardItem *  item2 = new QStandardItem(QString::fromStdString(
                newData.getDefValue()));
        QStandardItem *  item3 = new QStandardItem(QString::fromStdString(
                newData.getDocment()));
        QStandardItem *  item4 = new QStandardItem(QString::fromStdString(
                std::to_string(newData.getAlignByte())));
        QStandardItem *  item5 = new QStandardItem(QString::fromStdString(
                newData.getAttribute()));
        items << item0 << item1 << item2 << item3 << item4 << item5;
        m_structItemModel->insertRow(row + 1, items);
    }
}

void
WtMyStruct::structItem_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_structItemView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        auto  rawDataVec = m_objPtr->getField();
        std::swap(rawDataVec[row], rawDataVec[row - 1]);
        m_objPtr->setField(std::move(rawDataVec));

        auto const  item = m_structItemModel->takeRow(row);
        m_structItemModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_structItemView->setCurrentIndex(idx);
    }
}

void
WtMyStruct::structItem_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_structItemView->currentIndex();
    int const  row = index.row();
    int const  count = m_structItemModel->rowCount();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  rawDataVec = m_objPtr->getField();
        std::swap(rawDataVec[row], rawDataVec[row + 1]);
        m_objPtr->setField(std::move(rawDataVec));

        auto const  item = m_structItemModel->takeRow(row + 1);
        m_structItemModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_structItemView->setCurrentIndex(idx);
    }
}

void
WtMyStruct::structItem_MoveToRow_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_structItemView->currentIndex();
    int const  count = m_structItemModel->rowCount();
    size_t  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        size_t  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (!ok)  return;

        auto  rawDataVec = m_objPtr->getField();
        if (!xu::moveVec_0(rawDataVec, currRow, movetoRow)) {
            return;
        }
        m_objPtr->setField(std::move(rawDataVec));

        auto const  item = m_structItemModel->takeRow(static_cast<int>(currRow));
        m_structItemModel->insertRow(static_cast<int>(movetoRow), item);
        QModelIndex  idx = index.sibling(static_cast<int>(movetoRow), index.column());
        m_structItemView->setCurrentIndex(idx);
    }
}

void
WtMyStruct::structItem_BeforBehind_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_structItemView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getField();

        std::string const  title("Struct item: " + rawDataVec[row].getFieldName());
        QString const  beforeLabel("    Struct Item Insert ");
        QString const  behindLabel("    Struct Item Follow ");
        std::string  beforeString = rawDataVec[row].getBefore();
        std::string  behindString = rawDataVec[row].getBehind();

        TwoBeforeBehind  tbe(title, beforeLabel, behindLabel, beforeString, behindString);
        tbe.exec();
        rawDataVec[row].setBefore(std::move(beforeString));
        rawDataVec[row].setBehind(std::move(behindString));

        m_objPtr->setField(std::move(rawDataVec));
    }
}

void
WtMyStruct::structItem_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_structItemView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getField();
        std::string const  currVal = m_structItemModel->data(index).
                toString().toUtf8().toStdString();

        switch (index.column()) {
        case 0 :
            {
                std::string const  oldVal = rawDataVec[row].getFieldName();
                if (oldVal == currVal)  return;
                rawDataVec[row].setFieldName(currVal);
                std::string const  newVal = rawDataVec[row].getFieldName();
                if (currVal != newVal) {
                    m_structItemModel->setData(index, QVariant(
                            QString::fromStdString(newVal)));
                }
                m_objPtr->setField(std::move(rawDataVec));
            }
            break;
        case 1 :
            rawDataVec[row].setTypeName(currVal);
            m_objPtr->setField(std::move(rawDataVec));
            break;
        case 2 :
            rawDataVec[row].setDefValue(currVal);
            m_objPtr->setField(std::move(rawDataVec));
            break;
        case 3 :
            rawDataVec[row].setDocment(currVal);
            m_objPtr->setField(std::move(rawDataVec));
            break;
        case 4 :
            {
                int const  oldVal = rawDataVec[row].getAlignByte();
                int  currIntVal = 0;
                bool  ok = false;
                currIntVal = m_structItemModel->data(index).toInt(&ok);
                if (!ok) {
                    m_structItemModel->setData(index, QVariant(
                            QString::fromStdString(std::to_string(currIntVal))));
                }
                if (oldVal == currIntVal)  return;
                rawDataVec[row].setAlignByte(currIntVal);
                int const  newVal = rawDataVec[row].getAlignByte();
                if (currIntVal != newVal) {
                    m_structItemModel->setData(index, QVariant(
                            QString::fromStdString(std::to_string(newVal))));
                }
                m_objPtr->setField(std::move(rawDataVec));
            }
            break;
        case 5 :
            rawDataVec[row].setAttribute(currVal);
            m_objPtr->setField(std::move(rawDataVec));
            break;
        }
    }
}

void
WtMyStruct::repStructItem()
{
    m_structItemModel->removeRows(0, m_structItemModel->rowCount());
    std::vector<Field> const  item = m_objPtr->getField();
    for (auto const &  it: item) {
        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(QString::fromStdString(
                it.getFieldName()));
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
                it.getTypeName()));
        QStandardItem *  item2 = new QStandardItem(QString::fromStdString(
                it.getDefValue()));
        QStandardItem *  item3 = new QStandardItem(QString::fromStdString(
                it.getDocment()));
        QStandardItem *  item4 = new QStandardItem(QString::fromStdString(
                std::to_string(it.getAlignByte())));
        QStandardItem *  item5 = new QStandardItem(QString::fromStdString(
                it.getAttribute()));
        items << item0 << item1 << item2 << item3 << item4 << item5;
        m_structItemModel->appendRow(items);
    }
}

bool
WtMyStruct::nameCheckDuplication(std::string const &  fnName)
{
    bool  res = false;

    auto  rawDataVec = m_objPtr->getField();
    for (const auto &  fn: rawDataVec) {
        res = fn.getFieldName() == fnName;
        if (res)  return res;
    }

    return res;
}

MyStruct *
WtMyStruct::getObjPtr() const
{
    return m_objPtr;
}

void
WtMyStruct::setObjPtr(MyStruct *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        m_structName->setText(QString::fromStdString(m_objPtr->getName()));
        m_attribute->setText(QString::fromStdString(m_objPtr->getAttribute()));
        m_alignas->setText(QString::fromStdString(
                std::to_string(m_objPtr->getAlignas())));
        m_docmentEdit->setText(QString::fromStdString(m_objPtr->getDocment()));
        repStructItem();
    }
}

QStandardItem *
WtMyStruct::getItemPtr() const
{
    return m_itemPtr;
}

void
WtMyStruct::setItemPtr(QStandardItem *  value)
{
    m_itemPtr = value;
}

}
