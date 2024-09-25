#include <typeinfo>
#include <utility>
#include <functional>
#include <algorithm>
#include <QMessageBox>
#include <QInputDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QAction>
#include <QAbstractScrollArea>
#include <QFrame>
#include <QList>
#include "wtmodule.h"
#include "publictype.h"
#include "field.h"
#include "highlighter.h"
#include "twobeforebehind.h"
#include "fourbeforebehind.h"
#include "fmt.h"
#include "mystruct.h"
#include "mystructdec.h"
#include "myclassdec.h"
#include "module.h"
#include "defaultconstructorfn.h"
#include "copyconstructorfn.h"
#include "moveconstructorfn.h"
#include "destructorfn.h"
#include "copyoperatoreqfn.h"
#include "moveoperatoreqfn.h"
#include "actfn.h"
#include "actgetfn.h"
#include "actsetcopyfn.h"
#include "actsetmovefn.h"
#include "actsetconstvaluefn.h"
#include "actsetmutvaluefn.h"
#include "actisfn.h"
#include "acthasfn.h"
#include "publiclabel.h"
#include "protectedlabel.h"
#include "privatelabel.h"
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
#include "module.h"
#include "project.h"

namespace xu {

WtModule::WtModule(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_filename(nullptr),
        m_hStart(nullptr),
        m_extension(nullptr),
        m_isHeaderOnly(nullptr),
        m_mainTab(nullptr),
        m_docment(nullptr),
        m_namespaceView(nullptr),
        m_namespaceModel(nullptr),
        m_hIncludeView(nullptr),
        m_hIncludeModel(nullptr),
        m_cppIncludeView(nullptr),
        m_cppIncludeModel(nullptr),
        m_cppGlobalCode(nullptr),
        m_cppEndCode(nullptr),
        m_dotH(nullptr),
        m_dotCpp(nullptr)
{
    init_obj();
    connect_obj();
    display_obj();
}

WtModule::~WtModule() noexcept
{
}

void
WtModule::filename_editingFinished()
{
    QStandardItem *  itemPtr = getItemPtr();
    if (!m_objPtr)  return;

    std::string const  oldVal = m_objPtr->getFilename();
    std::string const  currVal = m_filename->text().toUtf8().toStdString();
    if (oldVal == currVal)  return;

    m_objPtr->setFilename(currVal);
    std::string const  newVal = m_objPtr->getFilename();
    if (currVal != newVal) {
        m_filename->setText(QString::fromStdString(newVal));
    }
    QVariant  treeLabel(QString::fromStdString(m_objPtr->getTreeLabel()));
    itemPtr->setData(treeLabel, Qt::EditRole);
}

void
WtModule::hStart_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setHStart(m_hStart->text().toUtf8().toStdString());
}

void
WtModule::extension_currentIndexChanged(int  index)
{
    if (!m_objPtr)  return;

    bool const  isHeaderOnly = m_objPtr->isHeaderOnly();
    QString  doth;
    QString  dotcpp = "    ";
    if (isHeaderOnly) {
        doth = ".hpp";
    } else {
        doth = ".h  ";
    }

    switch (index) {
    case 0:
        m_objPtr->setExtension(Module::Extension::cpp);
        m_mainTab->setTabText(3, doth);
        if (isHeaderOnly) {
            m_mainTab->setTabText(4, dotcpp);
        } else {
            m_mainTab->setTabText(4, ".cpp");
        }
        break;
    case 1:
        m_objPtr->setExtension(Module::Extension::c);
        m_mainTab->setTabText(3, doth);
        if (isHeaderOnly) {
            m_mainTab->setTabText(4, dotcpp);
        } else {
            m_mainTab->setTabText(4, ".c  ");
        }
        break;
    case 2:
        m_objPtr->setExtension(Module::Extension::cc);
        m_mainTab->setTabText(3, doth);
        if (isHeaderOnly) {
            m_mainTab->setTabText(4, dotcpp);
        } else {
            m_mainTab->setTabText(4, ".cc ");
        }
        break;
    case 3:
        m_objPtr->setExtension(Module::Extension::cxx);
        m_mainTab->setTabText(3, doth);
        if (isHeaderOnly) {
            m_mainTab->setTabText(4, dotcpp);
        } else {
            m_mainTab->setTabText(4, ".cxx");
        }
        break;
    }
}

void
WtModule::isHeaderOnly_stateChanged(int  state)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (state == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->isHeaderOnly();
    if (currVal == oldVal)  return;

    m_objPtr->setHeaderOnly(currVal);
    bool const  newVal = m_objPtr->isHeaderOnly();
    if (newVal != currVal) {
        m_isHeaderOnly->setChecked(newVal);
    }

    int const  index = static_cast<int>(m_objPtr->getExtension());
    extension_currentIndexChanged(index);
}

void
WtModule::mainTab_tabBarClicked(int const  index)
{
    if (!m_objPtr)  return;

    switch (index) {
    case 3:
        m_dotH->setPlainText(QString::fromStdString(m_objPtr->toHBlock()));
        break;
    case 4:
        m_dotCpp->setPlainText(QString::fromStdString(m_objPtr->toCppBlock()));
        break;
    }
}

void
WtModule::docment_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setDocment(m_docment->toHtml().toUtf8().toStdString());
}

void
WtModule::cppGlobalCode_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setCppGlobalCode(m_cppGlobalCode->toPlainText().
            toUtf8().toStdString());
}

void
WtModule::cppEndCode_textChanged()
{
    if (!m_objPtr)  return;

    m_objPtr->setCppEndCode(m_cppEndCode->toPlainText().
            toUtf8().toStdString());
}

void
WtModule::namespaceConnect()
{
    QAction *  actAdd = new QAction(tr("Add New"));
    QAction *  actInsertNew = new QAction(tr("Insert New"));
    QAction *  actDelete = new QAction(tr("Delete"));
    actAdd->setParent(this);
    actInsertNew->setParent(this);
    actDelete->setParent(this);
    QAction *  actSpt = new QAction;
    actSpt->setSeparator(true);
    QAction *  actSpt2 = new QAction;
    actSpt2->setSeparator(true);
    actSpt2->setParent(this);
    QAction *  actUp = new QAction(tr("Up"));
    QAction *  actDown = new QAction(tr("Down"));
    QAction *  actMoveTo = new QAction(tr("Move To Row"));
    QAction *  actHBeforBehind = new QAction(tr(".h Insert && Follow"));
    QAction *  actCppBeforBehind = new QAction(tr(".cpp Insert && Follow"));
    actSpt->setParent(this);
    actUp->setParent(this);
    actDown->setParent(this);
    actMoveTo->setParent(this);
    actHBeforBehind->setParent(this);
    actCppBeforBehind->setParent(this);
    m_namespaceView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_namespaceView->addAction(actAdd);
    m_namespaceView->addAction(actInsertNew);
    m_namespaceView->addAction(actDelete);
    m_namespaceView->addAction(actSpt);
    m_namespaceView->addAction(actUp);
    m_namespaceView->addAction(actDown);
    m_namespaceView->addAction(actMoveTo);
    m_namespaceView->addAction(actSpt2);
    m_namespaceView->addAction(actHBeforBehind);
    m_namespaceView->addAction(actCppBeforBehind);

    connect(actAdd, &QAction::triggered,
            this, &WtModule::namespace_Add_triggered);
    connect(actInsertNew, &QAction::triggered,
            this, &WtModule::namespace_InsertNew_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtModule::namespace_Delete_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtModule::namespace_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtModule::namespace_Down_triggered);
    connect(actMoveTo, &QAction::triggered,
            this, &WtModule::namespace_MoveTo_triggered);
    connect(actHBeforBehind, &QAction::triggered,
            this, &WtModule::namespace_HBeforBehind_triggered);
    connect(actCppBeforBehind, &QAction::triggered,
            this, &WtModule::namespace_CppBeforBehind_triggered);

    connect(m_namespaceView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtModule::namespace_itemDelegate_closeEditor);
}

void
WtModule::namespace_Add_triggered()
{
    if (!m_objPtr)  return;

    std::vector<NamespaceItem>  currVal = m_objPtr->getNamespace();
    NamespaceItem const  inc;
    currVal.push_back(inc);
    m_objPtr->setNamespace(std::move(currVal));

    QStandardItem *  item = new QStandardItem(
            QString::fromStdString(inc.getNamespaceValue()));
    m_namespaceModel->appendRow(item);
    if (m_namespaceModel->rowCount() == 1) {
        m_namespaceView->setCurrentIndex(m_namespaceModel->index(0, 0));
    }
}

void
WtModule::namespace_InsertNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_namespaceView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        std::vector<NamespaceItem>  currVal = m_objPtr->getNamespace();
        NamespaceItem const  inc;
        currVal.insert(currVal.begin() + row, inc);
        m_objPtr->setNamespace(std::move(currVal));

        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(inc.getNamespaceValue()));
        m_namespaceModel->appendRow(item);
    } else {
        namespace_Add_triggered();
    }
}

void
WtModule::namespace_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_namespaceView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  currVal = m_objPtr->getNamespace();
        currVal.erase(currVal.begin() + row);
        m_objPtr->setNamespace(currVal);

        m_namespaceModel->removeRows(row, 1);
    }
}

void
WtModule::namespace_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_namespaceView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        auto  currVal = m_objPtr->getNamespace();
        std::swap(currVal[row], currVal[row - 1]);
        m_objPtr->setNamespace(currVal);

        auto const  item = m_namespaceModel->takeRow(row);
        m_namespaceModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_namespaceView->setCurrentIndex(idx);
    }
}

void
WtModule::namespace_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_namespaceView->currentIndex();
    int const  count = m_namespaceModel->rowCount();
    int const  row = index.row();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  currVal = m_objPtr->getNamespace();
        std::swap(currVal[row], currVal[row + 1]);
        m_objPtr->setNamespace(currVal);

        auto const  item = m_namespaceModel->takeRow(row + 1);
        m_namespaceModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_namespaceView->setCurrentIndex(idx);
    }
}

void
WtModule::namespace_MoveTo_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_namespaceView->currentIndex();
    int const  count = m_namespaceModel->rowCount();
    int const  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        int  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (ok) {
            if (movetoRow > 0)  movetoRow--;
            if (movetoRow >= count)  movetoRow = count - 1;
            if (currRow != movetoRow) {
                auto  currVal = m_objPtr->getNamespace();
                auto const  dVal = currVal[currRow];
                currVal.erase(currVal.begin() + currRow);
                currVal.insert(currVal.begin() + movetoRow, dVal);
                m_objPtr->setNamespace(currVal);

                repNamespace();
                const QModelIndex  idx = index.sibling(movetoRow, index.column());
                m_namespaceView->setCurrentIndex(idx);
            }
        }
    }
}

void
WtModule::namespace_HBeforBehind_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_namespaceView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  inc = m_objPtr->getNamespace();
        std::string const  title = "namespace " + inc[row].getNamespaceValue();
        QString const  beforeFirstLabel("    namespace begin Insert ( .h )");
        QString const  behindFirstLabel("    namespace begin Follow ( .h )");
        QString const  beforeSecondLabel("    namespace end Insert ( .h )");
        QString const  behindSecondLabel("    namespace end Follow ( .h )");
        std::string  hBeginBefor = inc[row].getHBeginBefor();
        std::string  hBeginBehind = inc[row].getHBeginBehind();
        std::string  hEndBefor = inc[row].getHEndBefor();
        std::string  hEndBehind = inc[row].getHEndBehind();
        FourBeforeBehind  fbe(title, beforeFirstLabel, behindFirstLabel,
                hBeginBefor, hBeginBehind,
                beforeSecondLabel, behindSecondLabel,
                hEndBefor, hEndBehind);
        fbe.exec();
        inc[row].setHBeginBefor(std::move(hBeginBefor));
        inc[row].setHBeginBehind(std::move(hBeginBehind));
        inc[row].setHEndBefor(std::move(hEndBefor));
        inc[row].setHEndBehind(std::move(hEndBehind));
        m_objPtr->setNamespace(std::move(inc));
    }
}

void
WtModule::namespace_CppBeforBehind_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_namespaceView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  inc = m_objPtr->getNamespace();
        std::string const  title = "namespace " + inc[row].getNamespaceValue();
        QString const  beforeFirstLabel("    namespace begin Insert ( .cpp )");
        QString const  behindFirstLabel("    namespace begin Follow ( .cpp )");
        QString const  beforeSecondLabel("    namespace end Insert ( .cpp )");
        QString const  behindSecondLabel("    namespace end Follow ( .cpp )");
        std::string  cppBeginBefor = inc[row].getCppBeginBefor();
        std::string  cppBeginBehind = inc[row].getCppBeginBehind();
        std::string  cppEndBefor = inc[row].getCppEndBefor();
        std::string  cppEndBehind = inc[row].getCppEndBehind();
        FourBeforeBehind  fbe(title, beforeFirstLabel, behindFirstLabel,
                cppBeginBefor, cppBeginBehind,
                beforeSecondLabel, behindSecondLabel,
                cppEndBefor, cppEndBehind);
        fbe.exec();
        inc[row].setCppBeginBefor(std::move(cppBeginBefor));
        inc[row].setCppBeginBehind(std::move(cppBeginBehind));
        inc[row].setCppEndBefor(std::move(cppEndBefor));
        inc[row].setCppEndBehind(std::move(cppEndBehind));
        m_objPtr->setNamespace(std::move(inc));
    }
}

void
WtModule::namespace_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_namespaceView->currentIndex();
    if (index.isValid()) {
        auto  currVec = m_objPtr->getNamespace();
        int const  idx = index.row();
        std::string const  currVal =
                m_namespaceModel->data(index).toString().toUtf8().toStdString();

        switch (index.column()) {
        case 0:
            {
                currVec[idx].setNamespaceValue(currVal);
                m_objPtr->setNamespace(currVec);
                const auto  newVal = m_objPtr->getNamespace()[idx].getNamespaceValue();

                if (currVal != newVal) {
                    m_namespaceModel->setData(index,
                            QVariant(QString::fromStdString(newVal)));
                }
            }
            break;
        }
    }
}

void
WtModule::hIncludeConnect()
{
    QAction *  actAdd = new QAction(tr("Add New"));
    QAction *  actInsertNew = new QAction(tr("Insert New"));
    QAction *  actDelete = new QAction(tr("Delete"));
    actAdd->setParent(this);
    actInsertNew->setParent(this);
    actDelete->setParent(this);
    QAction *  actSpt = new QAction;
    actSpt->setSeparator(true);
    QAction *  actSpt2 = new QAction;
    actSpt2->setSeparator(true);
    actSpt2->setParent(this);
    QAction *  actSpt3 = new QAction;
    actSpt3->setSeparator(true);
    actSpt3->setParent(this);
    QAction *  actUp = new QAction(tr("Up"));
    QAction *  actDown = new QAction(tr("Down"));
    QAction *  actMoveTo = new QAction(tr("Move To Row"));
    QAction *  actMoveToCpp = new QAction(tr("Move To .cpp"));
    QAction *  actBeforBehind = new QAction(tr("Insert && Follow"));
    actSpt->setParent(this);
    actUp->setParent(this);
    actDown->setParent(this);
    actMoveTo->setParent(this);
    actMoveToCpp->setParent(this);
    actBeforBehind->setParent(this);
    m_hIncludeView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_hIncludeView->addAction(actAdd);
    m_hIncludeView->addAction(actInsertNew);
    m_hIncludeView->addAction(actDelete);
    m_hIncludeView->addAction(actSpt);
    m_hIncludeView->addAction(actUp);
    m_hIncludeView->addAction(actDown);
    m_hIncludeView->addAction(actMoveTo);
    m_hIncludeView->addAction(actSpt2);
    m_hIncludeView->addAction(actMoveToCpp);
    m_hIncludeView->addAction(actSpt3);
    m_hIncludeView->addAction(actBeforBehind);

    connect(actAdd, &QAction::triggered,
            this, &WtModule::hinclude_Add_triggered);
    connect(actInsertNew, &QAction::triggered,
            this, &WtModule::hinclude_InsertNew_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtModule::hinclude_Delete_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtModule::hinclude_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtModule::hinclude_Down_triggered);
    connect(actMoveTo, &QAction::triggered,
            this, &WtModule::hinclude_MoveToRow_triggered);
    connect(actBeforBehind, &QAction::triggered,
            this, &WtModule::hinclude_BeforBehind_triggered);
    connect(actMoveToCpp, &QAction::triggered,
            this, &WtModule::hinclude_MoveToCpp_triggered);

    connect(m_hIncludeView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtModule::hinclude_itemDelegate_closeEditor);
}

void
WtModule::hinclude_Add_triggered()
{
    if (!m_objPtr)  return;

    std::vector<IncludeItem>  currVal = m_objPtr->getHInclude();
    IncludeItem const  inc;
    currVal.push_back(inc);
    m_objPtr->setHInclude(std::move(currVal));

    repHInclude();
}

void
WtModule::hinclude_InsertNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_hIncludeView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        std::vector<IncludeItem>  currVal = m_objPtr->getHInclude();
        IncludeItem const  inc;
        currVal.insert(currVal.begin() + row, inc);
        m_objPtr->setHInclude(std::move(currVal));

        repHInclude();
    } else {
        hinclude_Add_triggered();
    }
}

void
WtModule::hinclude_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_hIncludeView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  currVal = m_objPtr->getHInclude();
        currVal.erase(currVal.begin() + row);
        m_objPtr->setHInclude(currVal);

        repHInclude();
    }
}

void
WtModule::hinclude_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_hIncludeView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        auto  currVal = m_objPtr->getHInclude();
        std::swap(currVal[row], currVal[row - 1]);
        m_objPtr->setHInclude(currVal);

        repHInclude();
    }
}

void
WtModule::hinclude_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_hIncludeView->currentIndex();
    int const  count = m_hIncludeModel->rowCount();
    int const  row = index.row();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  currVal = m_objPtr->getHInclude();
        std::swap(currVal[row], currVal[row + 1]);
        m_objPtr->setHInclude(currVal);

        repHInclude();
    }
}

void
WtModule::hinclude_MoveToRow_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_hIncludeView->currentIndex();
    int const  count = m_hIncludeModel->rowCount();
    int const  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        int  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (ok) {
            if (movetoRow > 0)  movetoRow--;
            if (movetoRow >= count)  movetoRow = count - 1;
            if (currRow != movetoRow) {
                auto  currVal = m_objPtr->getHInclude();
                auto const  dVal = currVal[currRow];
                currVal.erase(currVal.begin() + currRow);
                currVal.insert(currVal.begin() + movetoRow, dVal);
                m_objPtr->setHInclude(currVal);

                repHInclude();
                const QModelIndex  idx = index.sibling(movetoRow, index.column());
                m_hIncludeView->setCurrentIndex(idx);
            }
        }
    }
}

void
WtModule::hinclude_BeforBehind_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_hIncludeView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  inc = m_objPtr->getHInclude();
        std::string const  title("#include  " + inc[row].getIncludeValue());
        QString const  beforeLabel("    .h include Insert ( .h ) ");
        QString const  behindLabel("    .h include Follow ( .h ) ");
        std::string  before = inc[row].getBefore();
        std::string  behind = inc[row].getBehind();
        TwoBeforeBehind  tbe(title, beforeLabel, behindLabel, before, behind);
        tbe.exec();
        inc[row].setBefore(std::move(before));
        inc[row].setBehind(std::move(behind));
        m_objPtr->setHInclude(std::move(inc));
    }
}

void
WtModule::hinclude_MoveToCpp_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_hIncludeView->currentIndex();
    int  row = index.row();
    if (index.isValid()) {
        auto  vecH = m_objPtr->getHInclude();
        auto  dVal = vecH[row];
        vecH.erase(vecH.begin() + row);
        m_objPtr->setHInclude(vecH);
        repHInclude();

        auto  vecCpp = m_objPtr->getCppInclude();
        vecCpp.push_back(std::move(dVal));
        m_objPtr->setCppInclude(vecCpp);
        repCppInclude();
    }
}

void
WtModule::hinclude_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_hIncludeView->currentIndex();
    if (index.isValid()) {
        auto  currVec = m_objPtr->getHInclude();
        int const  idx = index.row();
        std::string const  currVal =
                m_hIncludeModel->data(index).toString().toUtf8().toStdString();

        switch (index.column()) {
        case 0:
            {
                currVec[idx].setIncludeValue(currVal);
                m_objPtr->setHInclude(currVec);
                const auto  newVal = m_objPtr->getHInclude()[idx].getIncludeValue();

                if (currVal != newVal) {
                    m_hIncludeModel->setData(index,
                            QVariant(QString::fromStdString(newVal)));
                }
            }
            break;
        }
    }
}

void
WtModule::cppIncludeConnect()
{
    QAction *  actAdd = new QAction(tr("Add New"));
    QAction *  actInsertNew = new QAction(tr("Insert New"));
    QAction *  actDelete = new QAction(tr("Delete"));
    actAdd->setParent(this);
    actInsertNew->setParent(this);
    actDelete->setParent(this);
    QAction *  actSpt = new QAction;
    actSpt->setSeparator(true);
    QAction *  actSpt2 = new QAction;
    actSpt2->setSeparator(true);
    actSpt2->setParent(this);
    QAction *  actSpt3 = new QAction;
    actSpt3->setSeparator(true);
    actSpt3->setParent(this);
    QAction *  actUp = new QAction(tr("Up"));
    QAction *  actDown = new QAction(tr("Down"));
    QAction *  actMoveTo = new QAction(tr("Move To Row"));
    QAction *  actMoveToH = new QAction(tr("Move To .h"));
    QAction *  actBeforBehind = new QAction(tr("Insert && Follow"));
    actSpt->setParent(this);
    actUp->setParent(this);
    actDown->setParent(this);
    actMoveTo->setParent(this);
    actMoveToH->setParent(this);
    actBeforBehind->setParent(this);
    m_cppIncludeView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_cppIncludeView->addAction(actAdd);
    m_cppIncludeView->addAction(actInsertNew);
    m_cppIncludeView->addAction(actDelete);
    m_cppIncludeView->addAction(actSpt);
    m_cppIncludeView->addAction(actUp);
    m_cppIncludeView->addAction(actDown);
    m_cppIncludeView->addAction(actMoveTo);
    m_cppIncludeView->addAction(actSpt2);
    m_cppIncludeView->addAction(actMoveToH);
    m_cppIncludeView->addAction(actSpt3);
    m_cppIncludeView->addAction(actBeforBehind);

    connect(actAdd, &QAction::triggered,
            this, &WtModule::cppinclude_Add_triggered);
    connect(actInsertNew, &QAction::triggered,
            this, &WtModule::cppinclude_InsertNew_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtModule::cppinclude_Delete_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtModule::cppinclude_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtModule::cppinclude_Down_triggered);
    connect(actMoveTo, &QAction::triggered,
            this, &WtModule::cppinclude_MoveToRow_triggered);
    connect(actMoveToH, &QAction::triggered,
            this, &WtModule::cppinclude_MoveToH_triggered);
    connect(actBeforBehind, &QAction::triggered,
            this, &WtModule::cppinclude_BeforBehind_triggered);

    connect(m_cppIncludeView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtModule::cppinclude_itemDelegate_closeEditor);
}

void
WtModule::cppinclude_Add_triggered()
{
    if (!m_objPtr)  return;

    std::vector<IncludeItem>  currVal = m_objPtr->getCppInclude();
    IncludeItem const  inc;
    currVal.push_back(inc);
    m_objPtr->setCppInclude(std::move(currVal));

    repCppInclude();
}

void
WtModule::cppinclude_InsertNew_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_cppIncludeView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        std::vector<IncludeItem>  currVal = m_objPtr->getCppInclude();
        IncludeItem const  inc;
        currVal.insert(currVal.begin() + row, inc);
        m_objPtr->setCppInclude(std::move(currVal));

        repCppInclude();
    } else {
        cppinclude_Add_triggered();
    }
}

void
WtModule::cppinclude_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_cppIncludeView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  currVal = m_objPtr->getCppInclude();
        currVal.erase(currVal.begin() + row);
        m_objPtr->setCppInclude(currVal);

        repCppInclude();
    }
}

void
WtModule::cppinclude_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_cppIncludeView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        auto  currVal = m_objPtr->getCppInclude();
        std::swap(currVal[row], currVal[row - 1]);
        m_objPtr->setCppInclude(currVal);

        repCppInclude();
    }
}

void
WtModule::cppinclude_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_cppIncludeView->currentIndex();
    int const  count = m_cppIncludeModel->rowCount();
    int const  row = index.row();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  currVal = m_objPtr->getCppInclude();
        std::swap(currVal[row], currVal[row + 1]);
        m_objPtr->setCppInclude(currVal);

        repCppInclude();
    }
}

void
WtModule::cppinclude_MoveToRow_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_cppIncludeView->currentIndex();
    int const  count = m_cppIncludeModel->rowCount();
    int const  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        int  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (ok) {
            if (movetoRow > 0)  movetoRow--;
            if (movetoRow >= count)  movetoRow = count - 1;
            if (currRow != movetoRow) {
                auto  currVal = m_objPtr->getCppInclude();
                auto const  dVal = currVal[currRow];
                currVal.erase(currVal.begin() + currRow);
                currVal.insert(currVal.begin() + movetoRow, dVal);
                m_objPtr->setCppInclude(currVal);

                repCppInclude();
                const QModelIndex  idx = index.sibling(movetoRow, index.column());
                m_cppIncludeView->setCurrentIndex(idx);
            }
        }
    }
}

void
WtModule::cppinclude_MoveToH_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_cppIncludeView->currentIndex();
    int  row = index.row();
    if (index.isValid()) {
        auto  vecCpp = m_objPtr->getCppInclude();
        auto  dVal = vecCpp[row];
        vecCpp.erase(vecCpp.begin() + row);
        m_objPtr->setCppInclude(vecCpp);
        repCppInclude();

        auto  vecH = m_objPtr->getHInclude();
        vecH.push_back(std::move(dVal));
        m_objPtr->setHInclude(vecH);
        repHInclude();
    }
}

void
WtModule::cppinclude_BeforBehind_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_cppIncludeView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  inc = m_objPtr->getCppInclude();
        std::string const  title("#include  " + inc[row].getIncludeValue());
        QString const  beforeLabel("    .cpp include Insert ( .cpp ) ");
        QString const  behindLabel("    .cpp include Follow ( .cpp ) ");
        std::string  before = inc[row].getBefore();
        std::string  behind = inc[row].getBehind();
        TwoBeforeBehind  tbe(title, beforeLabel, behindLabel, before, behind);
        tbe.exec();
        inc[row].setBefore(std::move(before));
        inc[row].setBehind(std::move(behind));
        m_objPtr->setCppInclude(std::move(inc));
    }
}

void
WtModule::cppinclude_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_cppIncludeView->currentIndex();
    if (index.isValid()) {
        auto  currVec = m_objPtr->getCppInclude();
        int const  idx = index.row();
        std::string const  currVal =
                m_cppIncludeModel->data(index).toString().toUtf8().toStdString();

        switch (index.column()) {
        case 0:
            {
                currVec[idx].setIncludeValue(currVal);
                m_objPtr->setCppInclude(currVec);
                const auto  newVal = m_objPtr->getCppInclude()[idx].getIncludeValue();

                if (currVal != newVal) {
                    m_cppIncludeModel->setData(index,
                            QVariant(QString::fromStdString(newVal)));
                }
            }
            break;
        }
    }
}

void
WtModule::dotHConnect()
{
    QAction *  actPrevious = new QAction(tr("Previous Auto Source Code"));
    QAction *  actUpdate = new QAction(tr("Update Source Code"));
    actPrevious->setParent(this);
    actUpdate->setParent(this);
    m_dotH->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_dotH->addAction(actPrevious);
    m_dotH->addAction(actUpdate);

    connect(actPrevious, &QAction::triggered,
            this, &WtModule::dotH_Previous_triggered);
    connect(actUpdate, &QAction::triggered,
            this, &WtModule::dotH_Update_triggered);
}

void
WtModule::dotH_Previous_triggered()
{
    m_dotH->setPlainText(QString::fromStdString(deleteSingleLineComment(
            m_objPtr->toHBlock())));
}

void
WtModule::dotH_Update_triggered()
{
    m_dotH->setPlainText(QString::fromStdString(m_objPtr->toHBlock()));
}

void
WtModule::dotCppConnect()
{
    QAction *  actPrevious = new QAction(tr("Previous Auto Source Code"));
    QAction *  actUpdate = new QAction(tr("Update Source Code"));
    actPrevious->setParent(this);
    actUpdate->setParent(this);
    m_dotCpp->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_dotCpp->addAction(actPrevious);
    m_dotCpp->addAction(actUpdate);

    connect(actPrevious, &QAction::triggered,
            this, &WtModule::dotCpp_Previous_triggered);
    connect(actUpdate, &QAction::triggered,
            this, &WtModule::dotCpp_Update_triggered);
}

void
WtModule::dotCpp_Previous_triggered()
{
    m_dotCpp->setPlainText(QString::fromStdString(
            deleteSingleLineComment(m_objPtr->toCppBlock())));
}

void
WtModule::dotCpp_Update_triggered()
{
    m_dotCpp->setPlainText(QString::fromStdString(m_objPtr->toCppBlock()));
}

void
WtModule::init_obj()
{
    m_filename = new QLineEdit;
    m_hStart = new QLineEdit;
    m_isHeaderOnly = new QCheckBox(tr("isHeaderOnly "));

    m_extension = new QComboBox;
    m_extension->addItem(QString::fromLocal8Bit(".cpp"));
    m_extension->addItem(QString::fromLocal8Bit(".c"));
    m_extension->addItem(QString::fromLocal8Bit(".cc"));
    m_extension->addItem(QString::fromLocal8Bit(".cxx"));
    m_extension->setCurrentIndex(0);

    m_mainTab = new QTabWidget;

    m_docment = new QTextEdit;
    new Highlighter(m_docment->document());
    m_cppGlobalCode = new CodeEditor;
    new Highlighter(m_cppGlobalCode->document());
    m_cppEndCode = new CodeEditor;
    new Highlighter(m_cppEndCode->document());

    m_dotH = new CodeEditor;
    new Highlighter(m_dotH->document());
    m_dotH->setReadOnly(true);
    m_dotCpp = new CodeEditor;
    new Highlighter(m_dotCpp->document());
    m_dotCpp->setReadOnly(true);

    m_namespaceView = new QTableView;
    m_namespaceModel = new QStandardItemModel;
    m_namespaceModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("namespace")));
    m_namespaceView->setModel(m_namespaceModel);
    m_namespaceView->setColumnWidth(0, 210);

    m_cppIncludeView = new QTableView;
    m_cppIncludeModel = new QStandardItemModel;
    m_cppIncludeModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr(".cpp include")));
    m_cppIncludeView->setModel(m_cppIncludeModel);
    m_cppIncludeView->setColumnWidth(0, 210);

    m_hIncludeView = new QTableView;
    m_hIncludeModel = new QStandardItemModel;
    m_hIncludeModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr(".h include")));
    m_hIncludeView->setModel(m_hIncludeModel);
    m_hIncludeView->setColumnWidth(0, 210);
}

void
WtModule::connect_obj()
{
    connect(m_filename, &QLineEdit::editingFinished,
            this, &WtModule::filename_editingFinished);
    connect(m_hStart, &QLineEdit::editingFinished,
            this, &WtModule::hStart_editingFinished);
    connect(m_extension, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &WtModule::extension_currentIndexChanged);
    connect(m_isHeaderOnly, &QCheckBox::stateChanged,
            this, &WtModule::isHeaderOnly_stateChanged);
    connect(m_docment, &QTextEdit::textChanged,
            this, &WtModule::docment_textChanged);

    connect(m_mainTab, &QTabWidget::tabBarClicked,
            this, &WtModule::mainTab_tabBarClicked);
    connect(m_cppGlobalCode, &CodeEditor::textChanged,
            this, &WtModule::cppGlobalCode_textChanged);
    connect(m_cppEndCode, &CodeEditor::textChanged,
            this, &WtModule::cppEndCode_textChanged);

    namespaceConnect();
    hIncludeConnect();
    cppIncludeConnect();

    dotHConnect();
    dotCppConnect();
}

void
WtModule::display_obj()
{
    QVBoxLayout *  vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 3, 0, 0);

    QHBoxLayout *  hboxModule = new QHBoxLayout;
    QHBoxLayout *  hboxLine = new QHBoxLayout;
    QHBoxLayout *  hboxProperty = new QHBoxLayout;
    hboxModule->setContentsMargins(0, 0, 0, 0);
    hboxLine->setContentsMargins(0, 0, 0, 0);
    hboxProperty->setContentsMargins(0, 0, 0, 0);
    vbox->addLayout(hboxModule);
    vbox->addLayout(hboxLine);
    vbox->addLayout(hboxProperty);

    {
        QFormLayout *  fm0 = new QFormLayout;
        QFormLayout *  fm1 = new QFormLayout;
        QHBoxLayout *  fm2 = new QHBoxLayout;
        QHBoxLayout *  fm3 = new QHBoxLayout;
        fm0->setContentsMargins(0, 0, 0, 0);
        fm1->setContentsMargins(0, 0, 0, 0);
        fm2->setContentsMargins(0, 0, 0, 0);
        fm3->setContentsMargins(0, 0, 0, 0);
        hboxModule->addLayout(fm0);
        hboxModule->addLayout(fm1);
        hboxModule->addLayout(fm2);
        hboxModule->addLayout(fm3);

        QLabel *  label0 = new QLabel(tr("File Name"));
        QLabel *  label1 = new QLabel(tr(".h Start"));
        fm0->addRow(label0, m_filename);
        fm1->addRow(label1, m_hStart);
        fm2->addWidget(m_extension);
        fm3->addWidget(m_isHeaderOnly);
        hboxModule->setStretch(0, 40);
        hboxModule->setStretch(1, 40);
        hboxModule->setStretch(2, 10);
        hboxModule->setStretch(3, 10);
    }
    {
        QFrame *  tlvline = new QFrame;
        hboxLine->addWidget(tlvline);
        tlvline->setFrameStyle(QFrame::HLine | QFrame::Plain);
        tlvline->setLineWidth(1);
    }
    {
        hboxProperty->addWidget(m_mainTab);
    }

    QSplitter *  spvInclude = new QSplitter;
    spvInclude->setHandleWidth(1);
    QSplitter *  spvCppCode = new QSplitter(Qt::Vertical);
    spvCppCode->setHandleWidth(1);
    m_mainTab->addTab(spvInclude, tr(" Include "));
    m_mainTab->addTab(spvCppCode, tr(" .cpp Begin && End "));
    m_mainTab->addTab(m_docment, tr(" Docment "));
    m_mainTab->addTab(m_dotH, tr(" .h "));
    m_mainTab->addTab(m_dotCpp, tr(" .cpp "));

    {
        spvInclude->addWidget(m_namespaceView);
        spvInclude->addWidget(m_hIncludeView);
        spvInclude->addWidget(m_cppIncludeView);
    }
    {
        spvCppCode->addWidget(m_cppGlobalCode);
        spvCppCode->addWidget(m_cppEndCode);
    }
}

void
WtModule::fillData()
{
    m_filename->setText(QString::fromStdString(m_objPtr->getFilename()));
    m_hStart->setText(QString::fromStdString(m_objPtr->getHStart()));
    m_docment->setText(QString::fromStdString(m_objPtr->getDocment()));
    {
        Module::Extension  extension = m_objPtr->getExtension();
        switch (extension) {
        case Module::Extension::cpp :
            m_extension->setCurrentIndex(0);
            break;
        case Module::Extension::c :
            m_extension->setCurrentIndex(1);
            break;
        case Module::Extension::cc :
            m_extension->setCurrentIndex(2);
            break;
        case Module::Extension::cxx :
            m_extension->setCurrentIndex(3);
            break;
        }
    }
    m_isHeaderOnly->setChecked(m_objPtr->isHeaderOnly());
    m_cppGlobalCode->setPlainText(QString::fromStdString(
            m_objPtr->getCppGlobalCode()));
    m_cppEndCode->setPlainText(QString::fromStdString(
            m_objPtr->getCppEndCode()));

    repNamespace();
    repHInclude();
    repCppInclude();

    m_dotH->setPlainText(QString::fromStdString(m_objPtr->toHBlock()));
    m_dotCpp->setPlainText(QString::fromStdString(m_objPtr->toCppBlock()));
}

void
WtModule::repNamespace()
{
    if (!m_objPtr)  return;

    auto const  vec = m_objPtr->getNamespace();
    m_namespaceModel->removeRows(0, m_namespaceModel->rowCount());
    for (size_t  i = 0; i < vec.size(); ++i) {
        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(vec[i].getNamespaceValue()));
        m_namespaceModel->appendRow(item);
    }
}

void
WtModule::repHInclude()
{
    if (!m_objPtr)  return;

    auto const  vec = m_objPtr->getHInclude();
    m_hIncludeModel->removeRows(0, m_hIncludeModel->rowCount());
    for (size_t  i = 0; i < vec.size(); ++i) {
        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(vec[i].getIncludeValue()));
        m_hIncludeModel->appendRow(item);
    }
}

void
WtModule::repCppInclude()
{
    if (!m_objPtr)  return;

    auto const  vec = m_objPtr->getCppInclude();
    m_cppIncludeModel->removeRows(0, m_cppIncludeModel->rowCount());
    for (size_t  i = 0; i < vec.size(); ++i) {
        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(vec[i].getIncludeValue()));
        m_cppIncludeModel->appendRow(item);
    }
}

Module *
WtModule::getObjPtr() const
{
    return m_objPtr;
}

void
WtModule::setObjPtr(Module *  value)
{
    m_objPtr = value;
    if (m_objPtr) {
        fillData();
    }
}

}
