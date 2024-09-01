#include <typeinfo>
#include <algorithm>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSplitter>
#include <QAbstractScrollArea>
#include <QAction>
#include <QInputDialog>
#include <QList>
#include "twobeforebehind.h"
#include "fourbeforebehind.h"
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

    displayCodeConnect();
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

    QModelIndex const  index = m_insertIndexView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        std::vector<std::pair<size_t, std::string>>  listLine = m_objPtr->getNewCode();
        std::string const  oldVal = listLine[row].second;
        std::string const  currVal =
                m_insertCode->toPlainText().toUtf8().toStdString();
        if (oldVal != currVal) {
            listLine[row].second = currVal;
            m_objPtr->setNewCode(listLine);

            m_displayCode->setPlainText(QString::fromStdString(m_objPtr->updateAutoCode()));
        }
    }
}

void
WtAutoFnEdit::isDefault_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setEqDefault(true);
    } else {
        m_objPtr->setEqDefault(false);
    }
}

void
WtAutoFnEdit::isDelete_stateChanged(int  status)
{
    if (!m_objPtr)  return;

    if (status == Qt::Checked) {
        m_objPtr->setEqDelete(true);
    } else {
        m_objPtr->setEqDelete(false);
    }
}

void
WtAutoFnEdit::attribute_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setAttribute(m_attribute->text().toUtf8().toStdString());
}

void
WtAutoFnEdit::beforBehindPb_clicked()
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
WtAutoFnEdit::displayCodeConnect()
{
    QAction *  actPrevious = new QAction(tr("Previous Auto Source Code"));
    QAction *  actUpdate = new QAction(tr("Update Source Code"));
    actPrevious->setParent(this);
    actUpdate->setParent(this);
    m_displayCode->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_displayCode->addAction(actPrevious);
    m_displayCode->addAction(actUpdate);

    connect(actPrevious, &QAction::triggered,
            this, &WtAutoFnEdit::displayCode_Previous_triggered);
    connect(actUpdate, &QAction::triggered,
            this, &WtAutoFnEdit::displayCode_Update_triggered);
}

void
WtAutoFnEdit::displayCode_Previous_triggered()
{
    if (!m_objPtr)  return;

    m_displayCode->setPlainText(QString::fromStdString(m_objPtr->autoCode()));
}

void
WtAutoFnEdit::displayCode_Update_triggered()
{
    if (!m_objPtr)  return;

    m_displayCode->setPlainText(QString::fromStdString(m_objPtr->updateAutoCode()));
}

void
WtAutoFnEdit::deleteIndexConnect()
{
    QAction *  actAdd = new QAction(tr("Add New Index"));
    QAction *  actDelete = new QAction(tr("Delete"));
    actAdd->setParent(this);
    actDelete->setParent(this);
    m_deleteIndexView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_deleteIndexView->addAction(actAdd);
    m_deleteIndexView->addAction(actDelete);

    connect(actAdd, &QAction::triggered,
            this, &WtAutoFnEdit::deleteIndex_Add_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtAutoFnEdit::deleteIndex_Delete_triggered);
}

void
WtAutoFnEdit::deleteIndex_Add_triggered()
{
    if (!m_objPtr)  return;

    std::vector<size_t>  listLine = m_objPtr->getStrike();
    bool  ok = false;
    int const  inputIdx = QInputDialog::getInt(this, "Delete row",
                "Delete row: ", 0, 0, 2000000, 1, &ok);
    if (ok) {
        listLine.push_back(inputIdx);
        m_objPtr->setStrike(listLine);

        m_displayCode->setPlainText(QString::fromStdString(m_objPtr->updateAutoCode()));
        repDeleteIndex();

        listLine = m_objPtr->getStrike();
        auto  itF = std::find(listLine.begin(), listLine.end(), inputIdx);
        auto const  idx = std::distance(listLine.begin(), itF);
        m_deleteIndexView->setCurrentIndex(
                    m_deleteIndexModel->index(idx, 0));
    }
}

void
WtAutoFnEdit::deleteIndex_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_deleteIndexView->currentIndex();
    if (index.isValid()) {
        std::vector<size_t>  listLine = m_objPtr->getStrike();

        listLine.erase(listLine.begin() + index.row());
        m_objPtr->setStrike(listLine);

        m_displayCode->setPlainText(QString::fromStdString(m_objPtr->updateAutoCode()));
        repDeleteIndex();
    }
}

void
WtAutoFnEdit::insertIndexConnect()
{
    QAction *  actAdd = new QAction(tr("Add New Index"));
    QAction *  actDelete = new QAction(tr("Delete"));
    QAction *  actModify = new QAction(tr("Modify Index"));
    actAdd->setParent(this);
    actDelete->setParent(this);
    actModify->setParent(this);
    m_insertIndexView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_insertIndexView->addAction(actAdd);
    m_insertIndexView->addAction(actDelete);
    m_insertIndexView->addAction(actModify);

    connect(actAdd, &QAction::triggered,
            this, &WtAutoFnEdit::insertIndex_Add_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtAutoFnEdit::insertIndex_Delete_triggered);
    connect(actModify, &QAction::triggered,
            this, &WtAutoFnEdit::insertIndex_Modify_triggered);

    connect(m_insertIndexView->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            this, &WtAutoFnEdit::insertIndex_RowChanged);
}

void
WtAutoFnEdit::insertIndex_Add_triggered()
{
    if (!m_objPtr)  return;

    std::vector<std::pair<size_t, std::string>>  listLine = m_objPtr->getNewCode();

    bool  ok = false;
    int const  inputIdx = QInputDialog::getInt(this, "Insert row position",
                "Insert row position: ", 0, 0, 2000000, 1, &ok);
    if (ok) {
        auto  itF = std::find_if(listLine.begin(), listLine.end(),
                [inputIdx](std::pair<size_t, std::string> const &  value){
            if (inputIdx == value.first) {
                return true;
            } else {
                return false;
            }
        });
        if (itF == listLine.end()) {
            listLine.push_back({ inputIdx, "" });
            m_objPtr->setNewCode(listLine);

            repInsertIndex();
            currInsert(inputIdx);
        }
    }
}

void
WtAutoFnEdit::insertIndex_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_insertIndexView->currentIndex();
    if (index.isValid()) {
        std::vector<std::pair<size_t, std::string>>  listLine = m_objPtr->getNewCode();

        listLine.erase(listLine.begin() + index.row());
        m_objPtr->setNewCode(listLine);

        m_displayCode->setPlainText(QString::fromStdString(m_objPtr->updateAutoCode()));
        repInsertIndex();
        currInsert();
    }
}

void
WtAutoFnEdit::insertIndex_Modify_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_insertIndexView->currentIndex();
    if (index.isValid()) {
        std::vector<std::pair<size_t, std::string>>  listLine = m_objPtr->getNewCode();

        bool  ok = false;
        int const  inputIdx = QInputDialog::getInt(this, "Modyfy to",
                    "Modify to: ", 0, 0, 2000000, 1, &ok);
        if (ok) {
            auto  itF = std::find_if(listLine.begin(), listLine.end(),
                    [inputIdx](std::pair<size_t, std::string> const &  value){
                if (inputIdx == value.first) {
                    return true;
                } else {
                    return false;
                }
            });
            if (itF == listLine.end()) {
                listLine[index.row()].first = inputIdx;
                m_objPtr->setNewCode(listLine);

                m_displayCode->setPlainText(QString::fromStdString(
                        m_objPtr->updateAutoCode()));
                repInsertIndex();
                currInsert(inputIdx);
            }
        }
    }
}

void
WtAutoFnEdit::insertIndex_RowChanged()
{
    if (!m_objPtr)  return;

    int const  row = m_insertIndexView->currentIndex().row();
    currInsert(row);
}

void
WtAutoFnEdit::repDeleteIndex()
{
    std::vector<size_t> const  sline = m_objPtr->getStrike();
    m_deleteIndexModel->removeRows(0, m_deleteIndexModel->rowCount());
    for (const auto &  it: sline) {
        QStandardItem *  newItem = new QStandardItem(
                    QString::fromStdString(std::to_string(it)));
        newItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        m_deleteIndexModel->appendRow(newItem);
    }
}

void
WtAutoFnEdit::repInsertIndex()
{
    std::vector<std::pair<size_t, std::string>> const  sline = m_objPtr->getNewCode();
    m_insertIndexModel->removeRows(0, m_insertIndexModel->rowCount());
    for (const auto &  it: sline) {
        QStandardItem *  newItem = new QStandardItem(
                    QString::fromStdString(std::to_string(it.first)));
        newItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        m_insertIndexModel->appendRow(newItem);
    }
}

void
WtAutoFnEdit::currInsert(int const  idx /* = INT_MAX */)
{
    std::vector<std::pair<size_t, std::string>> const  sline = m_objPtr->getNewCode();
    auto  itF = std::find_if(sline.begin(), sline.end(),
            [idx](std::pair<size_t, std::string> const & value) ->bool {
        if (idx == value.first) {
            return true;
        } else {
            return false;
        }
    });
    if (itF != sline.end()) {
        auto const  dis = std::distance(sline.begin(), itF);
        m_insertIndexView->setCurrentIndex(
                    m_insertIndexModel->index(dis, 0));
    }

    QModelIndex const  index = m_insertIndexView->currentIndex();
    if (!index.isValid()) {
        m_insertCode->setReadOnly(true);
        m_insertCode->clear();
        return;
    }
    m_insertCode->setReadOnly(false);
    m_insertCode->setPlainText(QString::fromStdString(
            sline[index.row()].second));
}

void
WtAutoFnEdit::setVisible()
{
    QStandardItem *  itemPtr = getItemPtr();
    if (!m_objPtr || !itemPtr)  return;

    Etype const  etp = static_cast<Etype>(itemPtr->data(Qt::UserRole + 1).toInt());
    switch (etp) {
    case Etype::eDefaultConstructorFn :
    case Etype::eCopyConstructorFn :
    case Etype::eCopyOperatorEqFn :
    case Etype::eDestructorFn :
        m_isDefault->show();
        m_isDelete->show();
        break;
    case Etype::eMoveConstructorFn :
    case Etype::eMoveOperatorEqFn :
        m_isDefault->hide();
        m_isDelete->show();
        break;
    default :
        m_isDefault->hide();
        m_isDelete->hide();
        break;
    }
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
