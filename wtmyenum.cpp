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
#include "wtmyenum.h"
#include "fmt.h"

namespace xu {

WtMyEnum::WtMyEnum(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_itemPtr(nullptr),
        m_enumName(nullptr),
        m_enumType(nullptr),
        m_beforBehindPb(nullptr),
        m_docmentEdit(nullptr),
        m_enumItemView(nullptr),
        m_enumItemModel(nullptr)
{
    m_enumName = new QLineEdit;
    m_enumName->setReadOnly(true);
    m_enumType = new QLineEdit;
    m_enumType->setReadOnly(true);
    m_beforBehindPb = new QPushButton(tr(" Insert && Follow "));
    m_beforBehindPb->setEnabled(false);
    m_docmentEdit = new QTextEdit;
    new Highlighter(m_docmentEdit->document());
    m_docmentEdit->setReadOnly(true);

    m_enumItemView = new QTableView;
    m_enumItemModel = new QStandardItemModel;
    m_enumItemModel->setHorizontalHeaderItem(0,
            new QStandardItem(tr("Enum Item")));
    m_enumItemModel->setHorizontalHeaderItem(1,
            new QStandardItem(tr("Docment")));
    m_enumItemModel->setHorizontalHeaderItem(2,
            new QStandardItem(tr("Item Value")));
    m_enumItemView->setModel(m_enumItemModel);

    m_enumItemView->setColumnWidth(0, 210);
    m_enumItemView->setColumnWidth(1, 460);
    m_enumItemView->setColumnWidth(2, 100);

    connect(m_enumName, &QLineEdit::editingFinished,
            this, &WtMyEnum::enumName_editingFinished);
    connect(m_enumType, &QLineEdit::editingFinished,
            this, &WtMyEnum::enumType_editingFinished);
    connect(m_beforBehindPb, &QPushButton::clicked,
            this, &WtMyEnum::beforBehindPb_clicked);
    connect(m_docmentEdit, &QTextEdit::textChanged,
            this, &WtMyEnum::docmentEdit_textChanged);
    enumItemConnect();

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

    QLabel *  label0 = new QLabel(tr(" Enum Class "));
    QLabel *  label1 = new QLabel(tr(" Enum Type "));
    fm0->addRow(label0, m_enumName);
    fm1->addRow(label1, m_enumType);
    fm2->addWidget(m_beforBehindPb);

    QSplitter *  vH = new QSplitter(Qt::Vertical);
    vH->setHandleWidth(1);
    vbox2->addWidget(vH);

    vH->addWidget(m_enumItemView);
    vH->addWidget(m_docmentEdit);
    vH->setStretchFactor(0, 70);
    vH->setStretchFactor(1, 30);
}

WtMyEnum::~WtMyEnum() noexcept
{
}

void
WtMyEnum::enumName_editingFinished()
{
    if (!m_objPtr)  return;

    std::string const  oldVal = m_objPtr->getName();
    std::string const  currVal = m_enumName->text().toUtf8().toStdString();
    if (oldVal == currVal)  return;
    m_objPtr->setName(currVal);
    std::string const  newVal = m_objPtr->getName();
    if (currVal != newVal) {
        m_enumName->setText(QString::fromStdString(newVal));
    }
    QVariant  treeLabel(QString::fromStdString(m_objPtr->getTreeLabel()));
    m_itemPtr->setData(treeLabel, Qt::EditRole);
}

void
WtMyEnum::enumType_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setType(m_enumType->text().toUtf8().toStdString());
}

void
WtMyEnum::beforBehindPb_clicked()
{
    if (!m_objPtr)  return;

    std::string const  title("Enum class");
    QString const  beforeLabel("    Enum class Insert ");
    QString const  behindLabel("    Enum class Follow ");
    std::string  beforeString = m_objPtr->getBefore();
    std::string  behindString = m_objPtr->getBehind();

    TwoBeforeBehind  tbe(title, beforeLabel, behindLabel, beforeString, behindString);
    tbe.exec();
    m_objPtr->setBefore(std::move(beforeString));
    m_objPtr->setBehind(std::move(behindString));
}

void
WtMyEnum::docmentEdit_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setDocment(m_docmentEdit->toHtml().toUtf8().toStdString());
}

void
WtMyEnum::enumItemConnect()
{
    QAction *  actAddItem = new QAction(tr("Add Enum Item"));
    QAction *  actInsertNew = new QAction(tr("Insert New Enum Item"));
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
    m_enumItemView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_enumItemView->addAction(actAddItem);
    m_enumItemView->addAction(actInsertNew);
    m_enumItemView->addAction(actDelete);
    m_enumItemView->addAction(actCopyToNew);
    m_enumItemView->addAction(actSpt);
    m_enumItemView->addAction(actUp);
    m_enumItemView->addAction(actDown);
    m_enumItemView->addAction(actMoveToRow);
    m_enumItemView->addAction(actSpt2);
    m_enumItemView->addAction(actBeforBehind);

    connect(actAddItem, &QAction::triggered,
            this, &WtMyEnum::enum_AddItem_triggered);
    connect(actInsertNew, &QAction::triggered,
            this, &WtMyEnum::enum_InsertNew_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtMyEnum::enum_Delete_triggered);
    connect(actCopyToNew, &QAction::triggered,
            this, &WtMyEnum::enum_CopyToNew_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtMyEnum::enum_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtMyEnum::enum_Down_triggered);
    connect(actMoveToRow, &QAction::triggered,
            this, &WtMyEnum::enum_MoveToRow_triggered);

    connect(actBeforBehind, &QAction::triggered,
            this, &WtMyEnum::enum_BeforBehind_triggered);

    connect(m_enumItemView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtMyEnum::enum_itemDelegate_closeEditor);
}

void
WtMyEnum::enum_AddItem_triggered()
{
    if (!m_objPtr)  return;

    std::vector<MyEnumItem>  rawDataVec = m_objPtr->getItem();
    MyEnumItem  newData;
    newData.setName("item1");
    rawDataVec.push_back(std::move(newData));
    m_objPtr->setItem(std::move(rawDataVec));

    QList<QStandardItem *>  itemNew;
    itemNew << new QStandardItem("item1") << new QStandardItem << new QStandardItem;
    m_enumItemModel->appendRow(itemNew);
}

void
WtMyEnum::enum_InsertNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_enumItemView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getItem();
        MyEnumItem  newData;
        newData.setName("item1");
        rawDataVec.insert(rawDataVec.begin() + row, std::move(newData));
        m_objPtr->setItem(std::move(rawDataVec));

        QList<QStandardItem *>  itemNew;
        itemNew << new QStandardItem("item1") << new QStandardItem << new QStandardItem;
        m_enumItemModel->insertRow(row, itemNew);
    } else {
        enum_AddItem_triggered();
    }
}

void
WtMyEnum::enum_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_enumItemView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getItem();
        rawDataVec.erase(rawDataVec.begin() + row);
        m_objPtr->setItem(std::move(rawDataVec));

        m_enumItemModel->removeRows(row, 1);

        int const  count = m_enumItemModel->rowCount();
        if (count > 0 && row < count) {
            m_enumItemView->setCurrentIndex(m_enumItemModel->index(row, index.column()));
        } else if (count > 0 && row != 0) {
            m_enumItemView->setCurrentIndex(m_enumItemModel->index(row - 1, index.column()));
        } else if (count == 1) {
            m_enumItemView->setCurrentIndex(m_enumItemModel->index(0, index.column()));
        }
    }
}

void
WtMyEnum::enum_CopyToNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_enumItemView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getItem();
        MyEnumItem  newData = rawDataVec[row];
        std::string const  oldName = rawDataVec[row].getName();
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
        newData.setName(newName);
        rawDataVec.insert(rawDataVec.begin() + row + 1, newData);
        m_objPtr->setItem(std::move(rawDataVec));

        QList<QStandardItem *>  itemNew;
        QStandardItem *  item0 = new QStandardItem(QString::fromStdString(
                newData.getName()));
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
                newData.getDocment()));
        QStandardItem *  item2 = new QStandardItem(QString::fromStdString(
                newData.getDefalutValue()));
        itemNew << item0 << item1 << item2;
        m_enumItemModel->insertRow(row + 1, itemNew);
    }
}

void
WtMyEnum::enum_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_enumItemView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        auto  rawDataVec = m_objPtr->getItem();
        std::swap(rawDataVec[row], rawDataVec[row - 1]);
        m_objPtr->setItem(std::move(rawDataVec));

        auto const  item = m_enumItemModel->takeRow(row);
        m_enumItemModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_enumItemView->setCurrentIndex(idx);
    }
}

void
WtMyEnum::enum_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_enumItemView->currentIndex();
    int const  row = index.row();
    int const  count = m_enumItemModel->rowCount();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  rawDataVec = m_objPtr->getItem();
        std::swap(rawDataVec[row], rawDataVec[row + 1]);
        m_objPtr->setItem(std::move(rawDataVec));

        auto const  item = m_enumItemModel->takeRow(row + 1);
        m_enumItemModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_enumItemView->setCurrentIndex(idx);
    }
}

void
WtMyEnum::enum_MoveToRow_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_enumItemView->currentIndex();
    int const  count = m_enumItemModel->rowCount();
    size_t  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        size_t  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (!ok)  return;

        auto  rawDataVec = m_objPtr->getItem();
        if (!xu::moveVec_0(rawDataVec, currRow, movetoRow)) {
            return;
        }
        m_objPtr->setItem(std::move(rawDataVec));

        auto const  item = m_enumItemModel->takeRow(static_cast<int>(currRow));
        m_enumItemModel->insertRow(static_cast<int>(movetoRow), item);
        QModelIndex  idx = index.sibling(static_cast<int>(movetoRow), index.column());
        m_enumItemView->setCurrentIndex(idx);
    }
}

void
WtMyEnum::enum_BeforBehind_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_enumItemView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getItem();

        std::string const  title("Enum item: " + rawDataVec[row].getName());
        QString const  beforeLabel("    Enum item Insert ");
        QString const  behindLabel("    Enum item Follow ");
        std::string  beforeString = rawDataVec[row].getBefore();
        std::string  behindString = rawDataVec[row].getBehind();

        TwoBeforeBehind  tbe(title, beforeLabel, behindLabel, beforeString, behindString);
        tbe.exec();
        rawDataVec[row].setBefore(std::move(beforeString));
        rawDataVec[row].setBehind(std::move(behindString));

        m_objPtr->setItem(std::move(rawDataVec));
    }
}

void
WtMyEnum::enum_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_enumItemView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  rawDataVec = m_objPtr->getItem();
        std::string const  currVal = m_enumItemModel->data(index).
                toString().toUtf8().toStdString();

        switch (index.column()) {
        case 0 :
            {
                std::string const  oldVal = rawDataVec[row].getName();
                if (oldVal == currVal)  return;
                rawDataVec[row].setName(currVal);
                std::string const  newVal = rawDataVec[row].getName();
                if (currVal != newVal) {
                    m_enumItemModel->setData(index, QVariant(
                            QString::fromStdString(newVal)));
                }
                m_objPtr->setItem(std::move(rawDataVec));
            }
            break;
        case 1 :
            rawDataVec[row].setDocment(currVal);
            m_objPtr->setItem(std::move(rawDataVec));
            break;
        case 2 :
            {
                rawDataVec[row].setDefalutValue(currVal);
                std::string const  newVal = rawDataVec[row].getDefalutValue();
                if (currVal != newVal) {
                    m_enumItemModel->setData(index, QVariant(
                            QString::fromStdString(newVal)));
                }
                m_objPtr->setItem(std::move(rawDataVec));
            }
            break;
        }
    }
}

void
WtMyEnum::repEnumItem()
{
    m_enumItemModel->removeRows(0, m_enumItemModel->rowCount());
    std::vector<MyEnumItem> const  item = m_objPtr->getItem();
    for (auto const &  it: item) {
        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(QString::fromStdString(it.getName()));
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(it.getDocment()));
        QStandardItem *  item2 = new QStandardItem(QString::fromStdString(it.getDefalutValue()));
        items << item0 << item1 << item2;
        m_enumItemModel->appendRow(items);
    }
}

bool
WtMyEnum::nameCheckDuplication(std::string const &  fnName)
{
    bool  res = false;

    auto  rawDataVec = m_objPtr->getItem();
    for (const auto &  fn: rawDataVec) {
        res = fn.getName() == fnName;
        if (res)  return res;
    }

    return res;
}

MyEnum *
WtMyEnum::getObjPtr() const
{
    return m_objPtr;
}

void
WtMyEnum::setObjPtr(MyEnum *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        m_enumName->setReadOnly(false);
        m_enumType->setReadOnly(false);
        m_docmentEdit->setReadOnly(false);
        m_beforBehindPb->setEnabled(true);

        m_enumName->setText(QString::fromStdString(m_objPtr->getName()));
        m_enumType->setText(QString::fromStdString(m_objPtr->getType()));
        m_docmentEdit->setText(QString::fromStdString(m_objPtr->getDocment()));
        repEnumItem();
    } else {
        m_enumName->clear();
        m_enumType->clear();
        m_docmentEdit->clear();
        m_enumItemModel->removeRows(0, m_enumItemModel->rowCount());

        m_enumName->setReadOnly(true);
        m_enumType->setReadOnly(true);
        m_docmentEdit->setReadOnly(true);
        m_beforBehindPb->setEnabled(false);
    }
}

QStandardItem *
WtMyEnum::getItemPtr() const
{
    return m_itemPtr;
}

void
WtMyEnum::setItemPtr(QStandardItem *  value)
{
    m_itemPtr = value;
}

}
