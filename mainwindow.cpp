#include <iostream>
#include <typeinfo>
#include <cstring>
#include <memory>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QMessageBox>
#include <QVariant>
#include <QIcon>
#include "icode.h"
#include "fmt.h"
#include "mainwindow.h"
#include "itemstack.h"
#include "eobject.h"
#include "basicblock.h"
#include "function.h"
#include "functions.h"
#include "staticfunctions.h"
#include "constexprfunctions.h"
#include "tplfunctions.h"
#include "tplstaticfunctions.h"
#include "tplconstexprfunctions.h"
#include "myclass.h"
#include "myclassdec.h"
#include "myenum.h"
#include "mystruct.h"
#include "mystructdec.h"
#include "mytypedef.h"
#include "constructors.h"
#include "tplconstructors.h"
#include "label.h"
#include "publiclabel.h"
#include "protectedlabel.h"
#include "privatelabel.h"
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

MainWindow::MainWindow(QWidget *  parent /* = nullptr */):
        QWidget(parent),
        m_obj(),
        m_open(nullptr),
        m_new(nullptr),
        m_save(nullptr),
        m_quit(nullptr),
        m_aboutQt(nullptr),
        m_spvMain(nullptr),
        m_currIgnore(nullptr),
        m_mainTreeView(nullptr),
        m_mainTreeModel(nullptr),
        m_spaceMenu(nullptr),
        m_projectMenu(nullptr),
        m_moduleMenu(nullptr),
        m_classMenu(nullptr),
        m_functionsMenu(nullptr),
        m_fnMenu(nullptr),
        m_otherMenu(nullptr),
        m_defaultMenu(nullptr),
        m_spaceWindow(nullptr),
        m_wtBasicBlock(nullptr),
        m_wtLabel(nullptr),
        m_wtPublicLabel(nullptr),
        m_wtProtectedLabel(nullptr),
        m_wtPrivateLabel(nullptr),
        m_wtMyEnum(nullptr),
        m_wtProject(nullptr),
        m_wtFn(nullptr),
        m_wtTplFn(nullptr),
        m_wtCtorFn(nullptr),
        m_wtTplCtorFn(nullptr),
        m_wtMyClassDec(nullptr),
        m_wtMyStructDec(nullptr),
        m_wtMyStruct(nullptr),
        m_wtAutoFnEdit(nullptr)
{
    setWindowTitle("AraMacao");
    init_obj();
    connect_obj();
    display_obj();
    new_clicked();

}

MainWindow::~MainWindow() noexcept
{
}

void
MainWindow::open_clicked()
{
}

void
MainWindow::new_clicked()
{
    m_obj.clearEobjList();
    fillData();
}

void
MainWindow::save_clicked()
{
}

void
MainWindow::aboutQt_clicked()
{
    QMessageBox::aboutQt(this);
}

void
MainWindow::mainTreeView_clicked(QModelIndex const &  index)
{
    if (!index.isValid())  return;

    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    void *  selfPtr = selfItem->data(Qt::UserRole + 2).value<void *>();
    Etype  parentEtp;
    if (selfEtp == Etype::eFunction) {
        QStandardItem *  parentItem = selfItem->parent();
        parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    }

    switch (selfEtp) {
    case Etype::eBasicBlock :
        m_wtBasicBlock->setItemPtr(selfItem);
        m_wtBasicBlock->setObjPtr(static_cast<BasicBlock *>(selfPtr));
        if (m_spvMain->widget(1) != m_wtBasicBlock) {
            m_spvMain->replaceWidget(1, m_wtBasicBlock);
        }
        break;
    case Etype::eClassDeclaration :
        m_wtMyClassDec->setItemPtr(selfItem);
        m_wtMyClassDec->setObjPtr(static_cast<MyClassDec *>(selfPtr));
        if (m_spvMain->widget(1) != m_wtMyClassDec) {
            m_spvMain->replaceWidget(1, m_wtMyClassDec);
        }
        break;
    case Etype::eStructDeclaration :
        m_wtMyStructDec->setItemPtr(selfItem);
        m_wtMyStructDec->setObjPtr(static_cast<MyStructDec *>(selfPtr));
        if (m_spvMain->widget(1) != m_wtMyStructDec) {
            m_spvMain->replaceWidget(1, m_wtMyStructDec);
        }
        break;
    case Etype::eStruct :
        m_wtMyStruct->setItemPtr(selfItem);
        m_wtMyStruct->setObjPtr(static_cast<MyStruct *>(selfPtr));
        if (m_spvMain->widget(1) != m_wtMyStruct) {
            m_spvMain->replaceWidget(1, m_wtMyStruct);
        }
        break;
    case Etype::eLabel :
        m_wtLabel->setItemPtr(selfItem);
        m_wtLabel->setObjPtr(static_cast<Label *>(selfPtr));
        if (m_spvMain->widget(1) != m_wtLabel) {
            m_spvMain->replaceWidget(1, m_wtLabel);
        }
        break;
    case Etype::ePublicLabel :
        m_wtPublicLabel->setItemPtr(selfItem);
        m_wtPublicLabel->setObjPtr(static_cast<PublicLabel *>(selfPtr));
        if (m_spvMain->widget(1) != m_wtPublicLabel) {
            m_spvMain->replaceWidget(1, m_wtPublicLabel);
        }
        break;
    case Etype::eProtectedLabel :
        m_wtProtectedLabel->setItemPtr(selfItem);
        m_wtProtectedLabel->setObjPtr(static_cast<ProtectedLabel *>(selfPtr));
        if (m_spvMain->widget(1) != m_wtProtectedLabel) {
            m_spvMain->replaceWidget(1, m_wtProtectedLabel);
        }
        break;
    case Etype::ePrivateLabel :
        m_wtPrivateLabel->setItemPtr(selfItem);
        m_wtPrivateLabel->setObjPtr(static_cast<PrivateLabel *>(selfPtr));
        if (m_spvMain->widget(1) != m_wtPrivateLabel) {
            m_spvMain->replaceWidget(1, m_wtPrivateLabel);
        }
        break;
    case Etype::eEnum :
        m_wtMyEnum->setItemPtr(selfItem);
        m_wtMyEnum->setObjPtr(static_cast<MyEnum *>(selfPtr));
        if (m_spvMain->widget(1) != m_wtMyEnum) {
            m_spvMain->replaceWidget(1, m_wtMyEnum);
        }
        break;
    case Etype::eProject :
        m_wtProject->setItemPtr(selfItem);
        m_wtProject->setObjPtr(static_cast<Project *>(selfPtr));
        if (m_spvMain->widget(1) != m_wtProject) {
            m_spvMain->replaceWidget(1, m_wtProject);
        }
        break;
    case Etype::eDefaultConstructorFn :
    case Etype::eCopyConstructorFn :
    case Etype::eMoveConstructorFn :
    case Etype::eDestructorFn :
    case Etype::eCopyOperatorEqFn :
    case Etype::eMoveOperatorEqFn :
        m_wtAutoFnEdit->setItemPtr(selfItem);
        m_wtAutoFnEdit->setObjPtr(static_cast<Function *>(selfPtr));
        if (m_spvMain->widget(1) != m_wtAutoFnEdit) {
            m_spvMain->replaceWidget(1, m_wtAutoFnEdit);
        }
        break;
    case Etype::eFunction :
        switch (parentEtp) {
        case Etype::eFunctions :
        case Etype::eStaticFunctions :
        case Etype::eConstexprFunctions :
            m_wtFn->setItemPtr(selfItem);
            m_wtFn->setObjPtr(static_cast<Function *>(selfPtr));
            if (m_spvMain->widget(1) != m_wtFn) {
                m_spvMain->replaceWidget(1, m_wtFn);
            }
            break;
        case Etype::eTplFunctions :
        case Etype::eTplStaticFunctions :
        case Etype::eTplConstexprFunctions :
            m_wtTplFn->setItemPtr(selfItem);
            m_wtTplFn->setObjPtr(static_cast<Function *>(selfPtr));
            if (m_spvMain->widget(1) != m_wtTplFn) {
                m_spvMain->replaceWidget(1, m_wtTplFn);
            }
            break;
        case Etype::eConstructors :
            m_wtCtorFn->setItemPtr(selfItem);
            m_wtCtorFn->setObjPtr(static_cast<Function *>(selfPtr));
            if (m_spvMain->widget(1) != m_wtCtorFn) {
                m_spvMain->replaceWidget(1, m_wtCtorFn);
            }
            break;
        case Etype::eTplConstructors :
            m_wtTplCtorFn->setItemPtr(selfItem);
            m_wtTplCtorFn->setObjPtr(static_cast<Function *>(selfPtr));
            if (m_spvMain->widget(1) != m_wtTplCtorFn) {
                m_spvMain->replaceWidget(1, m_wtTplCtorFn);
            }
            break;
        default :
            if (m_spvMain->widget(1) != m_spaceWindow) {
                m_spvMain->replaceWidget(1, m_spaceWindow);
            }
            break;
        }
        break;
    default :
        if (m_spvMain->widget(1) != m_spaceWindow) {
            m_spvMain->replaceWidget(1, m_spaceWindow);
        }
        break;
    }
    m_spvMain->setStretchFactor(0, 30);
    m_spvMain->setStretchFactor(1, 70);
}

void
MainWindow::mainTreeView_customCxtMenu(QPoint const &  pos)
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    if (index.isValid()) {
        Etype const  etp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());

        switch (etp) {
        case Etype::eProject :
            m_projectMenu->exec(m_mainTreeView->mapToGlobal(pos));
            break;
        case Etype::eModule :
            m_moduleMenu->exec(m_mainTreeView->mapToGlobal(pos));
            break;
        case Etype::eClass :
            m_classMenu->exec(m_mainTreeView->mapToGlobal(pos));
            break;
        case Etype::eFunction :
            m_fnMenu->exec(m_mainTreeView->mapToGlobal(pos));
            break;
        case Etype::eFunctions :
        case Etype::eStaticFunctions :
        case Etype::eConstexprFunctions :
        case Etype::eTplFunctions :
        case Etype::eTplStaticFunctions :
        case Etype::eTplConstexprFunctions :

        case Etype::eConstructors :
        case Etype::eTplConstructors :
            m_functionsMenu->exec(m_mainTreeView->mapToGlobal(pos));
            break;
        case Etype::eBasicBlock :
        case Etype::eClassDeclaration :
        case Etype::eEnum :
        case Etype::eStruct :
        case Etype::eStructDeclaration :
        case Etype::eTypedef :

        case Etype::eLabel :
        case Etype::ePublicLabel :
        case Etype::eProtectedLabel :
        case Etype::ePrivateLabel :

        case Etype::eDefaultConstructorFn :
        case Etype::eCopyConstructorFn :
        case Etype::eMoveConstructorFn :
        case Etype::eDestructorFn :
        case Etype::eCopyOperatorEqFn :
        case Etype::eMoveOperatorEqFn :
            m_otherMenu->exec(m_mainTreeView->mapToGlobal(pos));
            break;
        default :
            m_defaultMenu->exec(m_mainTreeView->mapToGlobal(pos));
            break;
        }
    } else {
        m_spaceMenu->exec(m_mainTreeView->mapToGlobal(pos));
    }
}

void
MainWindow::menuConnect()
{
    {
        QAction *  actAddProject = new QAction(tr("Add Project"));
        m_spaceMenu->addAction(actAddProject);

        connect(actAddProject, &QAction::triggered,
                this, &MainWindow::addProject_triggered);
    }
    {
        QAction *  actAddProject = new QAction(tr("Add Project"));
        QAction *  actCopyProjectToNew = new QAction(tr("Copy Project To New"));
        QAction *  actDeleteProject = new QAction(tr("Delete Project"));
        QAction *  actUp = new QAction(tr("Up"));
        QAction *  actDown = new QAction(tr("Down"));
        QAction *  actMoveToRow = new QAction(tr("Move To Row"));
        QAction *  actAddModule = new QAction(tr("Add Module"));

        m_projectMenu->addAction(actAddModule);
        m_projectMenu->addSeparator();
        m_projectMenu->addAction(actUp);
        m_projectMenu->addAction(actDown);
        m_projectMenu->addAction(actMoveToRow);
        m_projectMenu->addSeparator();
        m_projectMenu->addAction(actAddProject);
        m_projectMenu->addAction(actCopyProjectToNew);
        m_projectMenu->addSeparator();
        m_projectMenu->addAction(actDeleteProject);

        connect(actAddProject, &QAction::triggered,
                this, &MainWindow::addProject_triggered);
        connect(actCopyProjectToNew, &QAction::triggered,
                this, &MainWindow::copyProject_triggered);
        connect(actDeleteProject, &QAction::triggered,
                this, &MainWindow::deleteProject_triggered);
        connect(actUp, &QAction::triggered,
                this, &MainWindow::upProject_triggered);
        connect(actDown, &QAction::triggered,
                this, &MainWindow::downProject_triggered);
        connect(actMoveToRow, &QAction::triggered,
                this, &MainWindow::moveToRowProject_triggered);
        connect(actAddModule, &QAction::triggered,
                this, &MainWindow::addModuleProject_triggered);
    }
    {
        QAction *  actAddModule = new QAction(tr("Add Module"));
        QAction *  actInsertNewModule = new QAction(tr("Insert New Module"));
        QAction *  actCopyModuleToNew = new QAction(tr("Copy Module To New"));
        QAction *  actDeleteModule = new QAction(tr("Delete Module"));
        QAction *  actUp = new QAction(tr("Up"));
        QAction *  actDown = new QAction(tr("Down"));
        QAction *  actMoveToRow = new QAction(tr("Move To Row"));

        QAction *  actAddClassDec = new QAction(tr("Add Class Declaration"));
        QAction *  actAddClass = new QAction(tr("Add Class"));
        QAction *  actAddStructDec = new QAction(tr("Add Struct Declaration"));
        QAction *  actAddStruct = new QAction(tr("Add Struct"));
        QAction *  actAddEnum = new QAction(tr("Add Enum"));
        QAction *  actAddTypedef = new QAction(tr("Add Typedef"));

        QAction *  actAddFns = new QAction(tr("Add Functions"));
        QAction *  actAddFnsStatic = new QAction(tr("Add Functions Static"));
        QAction *  actAddFnsCnex = new QAction(tr("Add Functions Constexpr"));
        QAction *  actAddTplFns = new QAction(tr("Add Template Functions"));
        QAction *  actAddTplFnsStatic = new QAction(tr("Add Template Functions Static"));
        QAction *  actAddTplFnsCnex = new QAction(tr("Add Template Functions Constexpr"));

        QAction *  actAddBasicBlock = new QAction(tr("Add BasicBlock"));

        m_moduleMenu->addAction(actAddClassDec);
        m_moduleMenu->addAction(actAddClass);
        m_moduleMenu->addAction(actAddStructDec);
        m_moduleMenu->addAction(actAddStruct);
        m_moduleMenu->addAction(actAddEnum);
        m_moduleMenu->addSeparator();
        m_moduleMenu->addAction(actAddBasicBlock);
        m_moduleMenu->addSeparator();
        m_moduleMenu->addAction(actAddFns);
        m_moduleMenu->addAction(actAddFnsStatic);
        m_moduleMenu->addAction(actAddFnsCnex);
        m_moduleMenu->addAction(actAddTplFns);
        m_moduleMenu->addAction(actAddTplFnsStatic);
        m_moduleMenu->addAction(actAddTplFnsCnex);
        m_moduleMenu->addSeparator();
        m_moduleMenu->addAction(actUp);
        m_moduleMenu->addAction(actDown);
        m_moduleMenu->addAction(actMoveToRow);
        m_moduleMenu->addSeparator();
        m_moduleMenu->addAction(actAddModule);
        m_moduleMenu->addAction(actInsertNewModule);
        m_moduleMenu->addAction(actCopyModuleToNew);
        m_moduleMenu->addSeparator();
        m_moduleMenu->addAction(actDeleteModule);

        connect(actAddModule, &QAction::triggered,
                this, &MainWindow::addModule_triggered);
        connect(actInsertNewModule, &QAction::triggered,
                this, &MainWindow::insertNewModule_triggered);
        connect(actCopyModuleToNew, &QAction::triggered,
                this, &MainWindow::copyModuleToNew_triggered);
        connect(actDeleteModule, &QAction::triggered,
                this, &MainWindow::deleteModule_triggered);
        connect(actUp, &QAction::triggered,
                this, &MainWindow::upModule_triggered);
        connect(actDown, &QAction::triggered,
                this, &MainWindow::downModule_triggered);
        connect(actMoveToRow, &QAction::triggered,
                this, &MainWindow::moveToRowModule_triggered);

        connect(actAddClassDec, &QAction::triggered,
                this, &MainWindow::addNewClassDecChild_triggered);
        connect(actAddClass, &QAction::triggered,
                this, &MainWindow::addNewClassChild_triggered);
        connect(actAddStructDec, &QAction::triggered,
                this, &MainWindow::addNewStructDecChild_triggered);
        connect(actAddStruct, &QAction::triggered,
                this, &MainWindow::addNewStructChild_triggered);
        connect(actAddEnum, &QAction::triggered,
                this, &MainWindow::addNewEnumChild_triggered);
        connect(actAddTypedef, &QAction::triggered,
                this, &MainWindow::addNewTypedefChild_triggered);

        connect(actAddFns, &QAction::triggered,
                this, &MainWindow::addNewFnsChild_triggered);
        connect(actAddFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewStaticFnsChild_triggered);
        connect(actAddFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewCoexFnsChild_triggered);
        connect(actAddTplFns, &QAction::triggered,
                this, &MainWindow::addNewTplFnsChild_triggered);
        connect(actAddTplFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewTplStaticFnsChild_triggered);
        connect(actAddTplFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewTplCoexFnsChild_triggered);

        connect(actAddBasicBlock, &QAction::triggered,
                this, &MainWindow::addNewBasicBlockChild_triggered);

    }
    {
        QAction *  actInsertNewClass = new QAction(tr("Insert New Class"));
        QAction *  actCopyClassToNew = new QAction(tr("Copy Class To New"));
        QAction *  actDeleteClass = new QAction(tr("Delete Class"));
        QAction *  actUp = new QAction(tr("Up"));
        QAction *  actDown = new QAction(tr("Down"));
        QAction *  actMoveToRow = new QAction(tr("Move To Row"));

        QAction *  actInsClassDec = new QAction(tr("New Class Declaration"));
        QAction *  actInsInClass = new QAction(tr("New Class"));
        QAction *  actInsStructDec = new QAction(tr("New Struct Declaration"));
        QAction *  actInsStruct = new QAction(tr("New Struct"));
        QAction *  actInsEnum = new QAction(tr("New Enum"));
        QAction *  actInsTypedef = new QAction(tr("New Typedef"));

        QAction *  actInsPubLabel = new QAction(tr("New Public Label"));
        QAction *  actInsProtLabel = new QAction(tr("New Protected Label"));
        QAction *  actInsPrvLabel = new QAction(tr("New Private Label"));
        QAction *  actInsLabel = new QAction(tr("New Label"));

        QAction *  actInsDefCtor = new QAction(tr("New Default Constructor"));
        QAction *  actInsCopyCtor = new QAction(tr("New Copy Constructor"));
        QAction *  actInsMoveCtor = new QAction(tr("New Move Constructor"));
        QAction *  actInsDtor = new QAction(tr("New ~Destructor"));
        QAction *  actInsCopyEq = new QAction(tr("New Copy Operator="));
        QAction *  actInsMoveEq = new QAction(tr("New Move Operator="));

        QAction *  actInsCtors = new QAction(tr("New Constructors"));
        QAction *  actInsTplCtors = new QAction(tr("New Template Constructors"));

        QAction *  actInsFns = new QAction(tr("New Functions"));
        QAction *  actInsFnsStatic = new QAction(tr("New Functions Static"));
        QAction *  actInsFnsCnex = new QAction(tr("New Functions Constexpr"));
        QAction *  actInsTplFns = new QAction(tr("New Template Functions"));
        QAction *  actInsTplFnsStatic = new QAction(tr("New Template Functions Static"));
        QAction *  actInsTplFnsCnex = new QAction(tr("New Template Functions Constexpr"));

        QAction *  actInsBasicBlock = new QAction(tr("New BasicBlock"));

        QAction *  actFlwClassDec = new QAction(tr("New Class Declaration"));
        QAction *  actFlwInClass = new QAction(tr("New Class"));
        QAction *  actFlwStructDec = new QAction(tr("New Struct Declaration"));
        QAction *  actFlwStruct = new QAction(tr("New Struct"));
        QAction *  actFlwEnum = new QAction(tr("New Enum"));
        QAction *  actFlwTypedef = new QAction(tr("New Typedef"));

        QAction *  actFlwPubLabel = new QAction(tr("New Public Label"));
        QAction *  actFlwProtLabel = new QAction(tr("New Protected Label"));
        QAction *  actFlwPrvLabel = new QAction(tr("New Private Label"));
        QAction *  actFlwLabel = new QAction(tr("New Label"));

        QAction *  actFlwDefCtor = new QAction(tr("New Default Constructor"));
        QAction *  actFlwCopyCtor = new QAction(tr("New Copy Constructor"));
        QAction *  actFlwMoveCtor = new QAction(tr("New Move Constructor"));
        QAction *  actFlwDtor = new QAction(tr("New ~Destructor"));
        QAction *  actFlwCopyEq = new QAction(tr("New Copy Operator="));
        QAction *  actFlwMoveEq = new QAction(tr("New Move Operator="));

        QAction *  actFlwCtors = new QAction(tr("New Constructors"));
        QAction *  actFlwTplCtors = new QAction(tr("New Template Constructors"));

        QAction *  actFlwFns = new QAction(tr("New Functions"));
        QAction *  actFlwFnsStatic = new QAction(tr("New Functions Static"));
        QAction *  actFlwFnsCnex = new QAction(tr("New Functions Constexpr"));
        QAction *  actFlwTplFns = new QAction(tr("New Template Functions"));
        QAction *  actFlwTplFnsStatic = new QAction(tr("New Template Functions Static"));
        QAction *  actFlwTplFnsCnex = new QAction(tr("New Template Functions Constexpr"));

        QAction *  actFlwBasicBlock = new QAction(tr("New BasicBlock"));

        QAction *  actAddClassDec = new QAction(tr("Add Class Declaration"));
        QAction *  actAddInClass = new QAction(tr("Add Internal Class"));
        QAction *  actAddStructDec = new QAction(tr("Add Struct Declaration"));
        QAction *  actAddStruct = new QAction(tr("Add Struct"));
        QAction *  actAddEnum = new QAction(tr("Add Enum"));
        QAction *  actAddTypedef = new QAction(tr("Add Typedef"));

        QAction *  actAddPubLabel = new QAction(tr("Add Public Label"));
        QAction *  actAddProtLabel = new QAction(tr("Add Protected Label"));
        QAction *  actAddPrvLabel = new QAction(tr("Add Private Label"));
        QAction *  actAddLabel = new QAction(tr("Add Label"));

        QAction *  actAddDefCtor = new QAction(tr("Add Default Constructor"));
        QAction *  actAddCopyCtor = new QAction(tr("Add Copy Constructor"));
        QAction *  actAddMoveCtor = new QAction(tr("Add Move Constructor"));
        QAction *  actAddDtor = new QAction(tr("Add ~Destructor"));
        QAction *  actAddCopyEq = new QAction(tr("Add Copy Operator="));
        QAction *  actAddMoveEq = new QAction(tr("Add Move Operator="));

        QAction *  actAddCtors = new QAction(tr("Add Constructors"));
        QAction *  actAddTplCtors = new QAction(tr("Add Template Constructors"));

        QAction *  actAddFns = new QAction(tr("Add Functions"));
        QAction *  actAddFnsStatic = new QAction(tr("Add Functions Static"));
        QAction *  actAddFnsCnex = new QAction(tr("Add Functions Constexpr"));
        QAction *  actAddTplFns = new QAction(tr("Add Template Functions"));
        QAction *  actAddTplFnsStatic = new QAction(tr("Add Template Functions Static"));
        QAction *  actAddTplFnsCnex = new QAction(tr("Add Template Functions Constexpr"));

        QAction *  actAddBasicBlock = new QAction(tr("Add BasicBlock"));


        QMenu *  menuAdd = new QMenu(m_classMenu);
        QMenu *  menuInsert = new QMenu(m_classMenu);
        QMenu *  menuFollow = new QMenu(m_classMenu);

        QAction *  actParentAdd = m_classMenu->addAction(tr("Add Child"));
        QAction *  actParentInsert = m_classMenu->addAction(tr("Insert"));
        QAction *  actParentFollow = m_classMenu->addAction(tr("Follow"));
        actParentAdd->setMenu(menuAdd);
        actParentInsert->setMenu(menuInsert);
        actParentFollow->setMenu(menuFollow);

        m_classMenu->addSeparator();
        m_classMenu->addAction(actUp);
        m_classMenu->addAction(actDown);
        m_classMenu->addAction(actMoveToRow);
        m_classMenu->addSeparator();
        m_classMenu->addAction(actCopyClassToNew);
        m_classMenu->addAction(actInsertNewClass);
        m_classMenu->addSeparator();
        m_classMenu->addAction(actDeleteClass);

        menuInsert->addAction(actInsClassDec);
        menuInsert->addAction(actInsInClass);
        menuInsert->addAction(actInsStructDec);
        menuInsert->addAction(actInsStruct);
        menuInsert->addAction(actInsEnum);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsBasicBlock);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsPubLabel);
        menuInsert->addAction(actInsProtLabel);
        menuInsert->addAction(actInsPrvLabel);
        menuInsert->addAction(actInsLabel);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsDefCtor);
        menuInsert->addAction(actInsCopyCtor);
        menuInsert->addAction(actInsMoveCtor);
        menuInsert->addAction(actInsDtor);
        menuInsert->addAction(actInsCopyEq);
        menuInsert->addAction(actInsMoveEq);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsCtors);
        menuInsert->addAction(actInsTplCtors);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsFns);
        menuInsert->addAction(actInsFnsStatic);
        menuInsert->addAction(actInsFnsCnex);
        menuInsert->addAction(actInsTplFns);
        menuInsert->addAction(actInsTplFnsStatic);
        menuInsert->addAction(actInsTplFnsCnex);

        menuFollow->addAction(actFlwClassDec);
        menuFollow->addAction(actFlwInClass);
        menuFollow->addAction(actFlwStructDec);
        menuFollow->addAction(actFlwStruct);
        menuFollow->addAction(actFlwEnum);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwBasicBlock);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwPubLabel);
        menuFollow->addAction(actFlwProtLabel);
        menuFollow->addAction(actFlwPrvLabel);
        menuFollow->addAction(actFlwLabel);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwDefCtor);
        menuFollow->addAction(actFlwCopyCtor);
        menuFollow->addAction(actFlwMoveCtor);
        menuFollow->addAction(actFlwDtor);
        menuFollow->addAction(actFlwCopyEq);
        menuFollow->addAction(actFlwMoveEq);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwCtors);
        menuFollow->addAction(actFlwTplCtors);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwFns);
        menuFollow->addAction(actFlwFnsStatic);
        menuFollow->addAction(actFlwFnsCnex);
        menuFollow->addAction(actFlwTplFns);
        menuFollow->addAction(actFlwTplFnsStatic);
        menuFollow->addAction(actFlwTplFnsCnex);

        menuAdd->addAction(actAddClassDec);
        menuAdd->addAction(actAddInClass);
        menuAdd->addAction(actAddStructDec);
        menuAdd->addAction(actAddStruct);
        menuAdd->addAction(actAddEnum);
        menuAdd->addSeparator();
        menuAdd->addAction(actAddBasicBlock);
        menuAdd->addSeparator();
        menuAdd->addAction(actAddPubLabel);
        menuAdd->addAction(actAddProtLabel);
        menuAdd->addAction(actAddPrvLabel);
        menuAdd->addAction(actAddLabel);
        menuAdd->addSeparator();
        menuAdd->addAction(actAddDefCtor);
        menuAdd->addAction(actAddCopyCtor);
        menuAdd->addAction(actAddMoveCtor);
        menuAdd->addAction(actAddDtor);
        menuAdd->addAction(actAddCopyEq);
        menuAdd->addAction(actAddMoveEq);
        menuAdd->addSeparator();
        menuAdd->addAction(actAddCtors);
        menuAdd->addAction(actAddTplCtors);
        menuAdd->addSeparator();
        menuAdd->addAction(actAddFns);
        menuAdd->addAction(actAddFnsStatic);
        menuAdd->addAction(actAddFnsCnex);
        menuAdd->addAction(actAddTplFns);
        menuAdd->addAction(actAddTplFnsStatic);
        menuAdd->addAction(actAddTplFnsCnex);

        connect(actInsertNewClass, &QAction::triggered,
                this, &MainWindow::addNewClassInsert_triggered);
        connect(actCopyClassToNew, &QAction::triggered,
                this, &MainWindow::addCopyClassFollow_triggered);
        connect(actDeleteClass, &QAction::triggered,
                this, &MainWindow::deleteRowValue_triggered);

        connect(actUp, &QAction::triggered,
                this, &MainWindow::upRowValue_triggered);
        connect(actDown, &QAction::triggered,
                this, &MainWindow::downRowValue_triggered);
        connect(actMoveToRow, &QAction::triggered,
                this, &MainWindow::moveToRowValue_triggered);

        connect(actAddBasicBlock, &QAction::triggered,
                this, &MainWindow::addNewBasicBlockChild_triggered);
        connect(actInsBasicBlock, &QAction::triggered,
                this, &MainWindow::addNewBasicBlockInsert_triggered);
        connect(actFlwBasicBlock, &QAction::triggered,
                this, &MainWindow::addNewBasicBlockFollow_triggered);

        connect(actAddLabel, &QAction::triggered,
                this, &MainWindow::addNewLabelChild_triggered);
        connect(actInsLabel, &QAction::triggered,
                this, &MainWindow::addNewLabelInsert_triggered);
        connect(actFlwLabel, &QAction::triggered,
                this, &MainWindow::addNewLabelFollow_triggered);
        connect(actAddPubLabel, &QAction::triggered,
                this, &MainWindow::addNewPublicLabelChild_triggered);
        connect(actInsPubLabel, &QAction::triggered,
                this, &MainWindow::addNewPublicLabelInsert_triggered);
        connect(actFlwPubLabel, &QAction::triggered,
                this, &MainWindow::addNewPublicLabelFollow_triggered);
        connect(actAddProtLabel, &QAction::triggered,
                this, &MainWindow::addNewProtectedLabelChild_triggered);
        connect(actInsProtLabel, &QAction::triggered,
                this, &MainWindow::addNewProtectedLabelInsert_triggered);
        connect(actFlwProtLabel, &QAction::triggered,
                this, &MainWindow::addNewProtectedLabelFollow_triggered);
        connect(actAddPrvLabel, &QAction::triggered,
                this, &MainWindow::addNewPrivateLabelChild_triggered);
        connect(actInsPrvLabel, &QAction::triggered,
                this, &MainWindow::addNewPrivateLabelInsert_triggered);
        connect(actFlwPrvLabel, &QAction::triggered,
                this, &MainWindow::addNewPrivateLabelFollow_triggered);

        connect(actAddCtors, &QAction::triggered,
                this, &MainWindow::addNewCtorsChild_triggered);
        connect(actInsCtors, &QAction::triggered,
                this, &MainWindow::addNewCtorsInsert_triggered);
        connect(actFlwCtors, &QAction::triggered,
                this, &MainWindow::addNewCtorsFollow_triggered);
        connect(actAddTplCtors, &QAction::triggered,
                this, &MainWindow::addNewTplCtorsChild_triggered);
        connect(actInsTplCtors, &QAction::triggered,
                this, &MainWindow::addNewTplCtorsInsert_triggered);
        connect(actFlwTplCtors, &QAction::triggered,
                this, &MainWindow::addNewTplCtorsFollow_triggered);
        connect(actAddDefCtor, &QAction::triggered,
                this, &MainWindow::addNewDefCtorFnChild_triggered);
        connect(actInsDefCtor, &QAction::triggered,
                this, &MainWindow::addNewDefCtorFnInsert_triggered);
        connect(actFlwDefCtor, &QAction::triggered,
                this, &MainWindow::addNewDefCtorFnFollow_triggered);
        connect(actAddCopyCtor, &QAction::triggered,
                this, &MainWindow::addNewCopyCtorFnChild_triggered);
        connect(actInsCopyCtor, &QAction::triggered,
                this, &MainWindow::addNewCopyCtorFnInsert_triggered);
        connect(actFlwCopyCtor, &QAction::triggered,
                this, &MainWindow::addNewCopyCtorFnFollow_triggered);
        connect(actAddMoveCtor, &QAction::triggered,
                this, &MainWindow::addNewMoveCtorFnChild_triggered);
        connect(actInsMoveCtor, &QAction::triggered,
                this, &MainWindow::addNewMoveCtorFnInsert_triggered);
        connect(actFlwMoveCtor, &QAction::triggered,
                this, &MainWindow::addNewMoveCtorFnFollow_triggered);
        connect(actAddDtor, &QAction::triggered,
                this, &MainWindow::addNewDtorFnChild_triggered);
        connect(actInsDtor, &QAction::triggered,
                this, &MainWindow::addNewDtorFnInsert_triggered);
        connect(actFlwDtor, &QAction::triggered,
                this, &MainWindow::addNewDtorFnFollow_triggered);
        connect(actAddCopyEq, &QAction::triggered,
                this, &MainWindow::addNewCopyOpEqFnChild_triggered);
        connect(actInsCopyEq, &QAction::triggered,
                this, &MainWindow::addNewCopyOpEqFnInsert_triggered);
        connect(actFlwCopyEq, &QAction::triggered,
                this, &MainWindow::addNewCopyOpEqFnFollow_triggered);
        connect(actAddMoveEq, &QAction::triggered,
                this, &MainWindow::addNewMoveOpEqFnChild_triggered);
        connect(actInsMoveEq, &QAction::triggered,
                this, &MainWindow::addNewMoveOpEqFnInsert_triggered);
        connect(actFlwMoveEq, &QAction::triggered,
                this, &MainWindow::addNewMoveOpEqFnFollow_triggered);

        connect(actInsClassDec, &QAction::triggered,
                this, &MainWindow::addNewClassDecInsert_triggered);
        connect(actInsInClass, &QAction::triggered,
                this, &MainWindow::addNewClassInsert_triggered);
        connect(actInsStructDec, &QAction::triggered,
                this, &MainWindow::addNewStructDecInsert_triggered);
        connect(actInsStruct, &QAction::triggered,
                this, &MainWindow::addNewStructInsert_triggered);
        connect(actInsEnum, &QAction::triggered,
                this, &MainWindow::addNewEnumInsert_triggered);
        connect(actInsTypedef, &QAction::triggered,
                this, &MainWindow::addNewTypedefInsert_triggered);

        connect(actFlwClassDec, &QAction::triggered,
                this, &MainWindow::addNewClassDecFollow_triggered);
        connect(actFlwInClass, &QAction::triggered,
                this, &MainWindow::addNewClassFollow_triggered);
        connect(actFlwStructDec, &QAction::triggered,
                this, &MainWindow::addNewStructDecFollow_triggered);
        connect(actFlwStruct, &QAction::triggered,
                this, &MainWindow::addNewStructFollow_triggered);
        connect(actFlwEnum, &QAction::triggered,
                this, &MainWindow::addNewEnumFollow_triggered);
        connect(actFlwTypedef, &QAction::triggered,
                this, &MainWindow::addNewTypedefFollow_triggered);

        connect(actAddClassDec, &QAction::triggered,
                this, &MainWindow::addNewClassDecChild_triggered);
        connect(actAddInClass, &QAction::triggered,
                this, &MainWindow::addNewClassChild_triggered);
        connect(actAddStructDec, &QAction::triggered,
                this, &MainWindow::addNewStructDecChild_triggered);
        connect(actAddStruct, &QAction::triggered,
                this, &MainWindow::addNewStructChild_triggered);
        connect(actAddEnum, &QAction::triggered,
                this, &MainWindow::addNewEnumChild_triggered);
        connect(actAddTypedef, &QAction::triggered,
                this, &MainWindow::addNewTypedefChild_triggered);

        connect(actInsFns, &QAction::triggered,
                this, &MainWindow::addNewFnsInsert_triggered);
        connect(actInsFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewStaticFnsInsert_triggered);
        connect(actInsFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewCoexFnsInsert_triggered);
        connect(actInsTplFns, &QAction::triggered,
                this, &MainWindow::addNewTplFnsInsert_triggered);
        connect(actInsTplFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewTplStaticFnsInsert_triggered);
        connect(actInsTplFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewTplCoexFnsInsert_triggered);

        connect(actFlwFns, &QAction::triggered,
                this, &MainWindow::addNewFnsFollow_triggered);
        connect(actFlwFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewStaticFnsFollow_triggered);
        connect(actFlwFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewCoexFnsFollow_triggered);
        connect(actFlwTplFns, &QAction::triggered,
                this, &MainWindow::addNewTplFnsFollow_triggered);
        connect(actFlwTplFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewTplStaticFnsFollow_triggered);
        connect(actFlwTplFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewTplCoexFnsFollow_triggered);

        connect(actAddFns, &QAction::triggered,
                this, &MainWindow::addNewFnsChild_triggered);
        connect(actAddFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewStaticFnsChild_triggered);
        connect(actAddFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewCoexFnsChild_triggered);
        connect(actAddTplFns, &QAction::triggered,
                this, &MainWindow::addNewTplFnsChild_triggered);
        connect(actAddTplFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewTplStaticFnsChild_triggered);
        connect(actAddTplFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewTplCoexFnsChild_triggered);

    }
    {
        QAction *  actAddFn = new QAction(tr("Add New Function"));
        QAction *  actUp = new QAction(tr("Up"));
        QAction *  actDown = new QAction(tr("Down"));
        QAction *  actMoveToRow = new QAction(tr("Move To Row"));
        QAction *  actDelete = new QAction(tr("Delete"));

        QAction *  actInsClassDec = new QAction(tr("New Class Declaration"));
        QAction *  actInsClass = new QAction(tr("New Class"));
        QAction *  actInsStructDec = new QAction(tr("New Struct Declaration"));
        QAction *  actInsStruct = new QAction(tr("New Struct"));
        QAction *  actInsEnum = new QAction(tr("New Enum"));
        QAction *  actInsTypedef = new QAction(tr("New Typedef"));

        QAction *  actInsPubLabel = new QAction(tr("New Public Label"));
        QAction *  actInsProtLabel = new QAction(tr("New Protected Label"));
        QAction *  actInsPrvLabel = new QAction(tr("New Private Label"));
        QAction *  actInsLabel = new QAction(tr("New Label"));

        QAction *  actInsDefCtor = new QAction(tr("New Default Constructor"));
        QAction *  actInsCopyCtor = new QAction(tr("New Copy Constructor"));
        QAction *  actInsMoveCtor = new QAction(tr("New Move Constructor"));
        QAction *  actInsDtor = new QAction(tr("New ~Destructor"));
        QAction *  actInsCopyEq = new QAction(tr("New Copy Operator="));
        QAction *  actInsMoveEq = new QAction(tr("New Move Operator="));

        QAction *  actInsCtors = new QAction(tr("New Constructors"));
        QAction *  actInsTplCtors = new QAction(tr("New Template Constructors"));

        QAction *  actInsFns = new QAction(tr("New Functions"));
        QAction *  actInsFnsStatic = new QAction(tr("New Functions Static"));
        QAction *  actInsFnsCnex = new QAction(tr("New Functions Constexpr"));
        QAction *  actInsTplFns = new QAction(tr("New Template Functions"));
        QAction *  actInsTplFnsStatic = new QAction(tr("New Template Functions Static"));
        QAction *  actInsTplFnsCnex = new QAction(tr("New Template Functions Constexpr"));

        QAction *  actInsBasicBlock = new QAction(tr("New BasicBlock"));

        QAction *  actFlwClassDec = new QAction(tr("New Class Declaration"));
        QAction *  actFlwClass = new QAction(tr("New Class"));
        QAction *  actFlwStructDec = new QAction(tr("New Struct Declaration"));
        QAction *  actFlwStruct = new QAction(tr("New Struct"));
        QAction *  actFlwEnum = new QAction(tr("New Enum"));
        QAction *  actFlwTypedef = new QAction(tr("New Typedef"));

        QAction *  actFlwPubLabel = new QAction(tr("New Public Label"));
        QAction *  actFlwProtLabel = new QAction(tr("New Protected Label"));
        QAction *  actFlwPrvLabel = new QAction(tr("New Private Label"));
        QAction *  actFlwLabel = new QAction(tr("New Label"));

        QAction *  actFlwDefCtor = new QAction(tr("New Default Constructor"));
        QAction *  actFlwCopyCtor = new QAction(tr("New Copy Constructor"));
        QAction *  actFlwMoveCtor = new QAction(tr("New Move Constructor"));
        QAction *  actFlwDtor = new QAction(tr("New ~Destructor"));
        QAction *  actFlwCopyEq = new QAction(tr("New Copy Operator="));
        QAction *  actFlwMoveEq = new QAction(tr("New Move Operator="));

        QAction *  actFlwCtors = new QAction(tr("New Constructors"));
        QAction *  actFlwTplCtors = new QAction(tr("New Template Constructors"));

        QAction *  actFlwFns = new QAction(tr("New Functions"));
        QAction *  actFlwFnsStatic = new QAction(tr("New Functions Static"));
        QAction *  actFlwFnsCnex = new QAction(tr("New Functions Constexpr"));
        QAction *  actFlwTplFns = new QAction(tr("New Template Functions"));
        QAction *  actFlwTplFnsStatic = new QAction(tr("New Template Functions Static"));
        QAction *  actFlwTplFnsCnex = new QAction(tr("New Template Functions Constexpr"));

        QAction *  actFlwBasicBlock = new QAction(tr("New BasicBlock"));

        m_functionsMenu->addAction(actAddFn);
        m_functionsMenu->addSeparator();

        QMenu *  menuInsert = new QMenu(m_functionsMenu);
        QMenu *  menuFollow = new QMenu(m_functionsMenu);

        QAction *  actParentInsert = m_functionsMenu->addAction(tr("Insert"));
        QAction *  actParentFollow = m_functionsMenu->addAction(tr("Follow"));
        actParentInsert->setMenu(menuInsert);
        actParentFollow->setMenu(menuFollow);

        m_functionsMenu->addSeparator();
        m_functionsMenu->addAction(actUp);
        m_functionsMenu->addAction(actDown);
        m_functionsMenu->addAction(actMoveToRow);
        m_functionsMenu->addSeparator();
        m_functionsMenu->addAction(actDelete);

        menuInsert->addAction(actInsClassDec);
        menuInsert->addAction(actInsClass);
        menuInsert->addAction(actInsStructDec);
        menuInsert->addAction(actInsStruct);
        menuInsert->addAction(actInsEnum);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsBasicBlock);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsPubLabel);
        menuInsert->addAction(actInsProtLabel);
        menuInsert->addAction(actInsPrvLabel);
        menuInsert->addAction(actInsLabel);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsDefCtor);
        menuInsert->addAction(actInsCopyCtor);
        menuInsert->addAction(actInsMoveCtor);
        menuInsert->addAction(actInsDtor);
        menuInsert->addAction(actInsCopyEq);
        menuInsert->addAction(actInsMoveEq);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsCtors);
        menuInsert->addAction(actInsTplCtors);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsFns);
        menuInsert->addAction(actInsFnsStatic);
        menuInsert->addAction(actInsFnsCnex);
        menuInsert->addAction(actInsTplFns);
        menuInsert->addAction(actInsTplFnsStatic);
        menuInsert->addAction(actInsTplFnsCnex);

        menuFollow->addAction(actFlwClassDec);
        menuFollow->addAction(actFlwClass);
        menuFollow->addAction(actFlwStructDec);
        menuFollow->addAction(actFlwStruct);
        menuFollow->addAction(actFlwEnum);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwBasicBlock);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwPubLabel);
        menuFollow->addAction(actFlwProtLabel);
        menuFollow->addAction(actFlwPrvLabel);
        menuFollow->addAction(actFlwLabel);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwDefCtor);
        menuFollow->addAction(actFlwCopyCtor);
        menuFollow->addAction(actFlwMoveCtor);
        menuFollow->addAction(actFlwDtor);
        menuFollow->addAction(actFlwCopyEq);
        menuFollow->addAction(actFlwMoveEq);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwCtors);
        menuFollow->addAction(actFlwTplCtors);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwFns);
        menuFollow->addAction(actFlwFnsStatic);
        menuFollow->addAction(actFlwFnsCnex);
        menuFollow->addAction(actFlwTplFns);
        menuFollow->addAction(actFlwTplFnsStatic);
        menuFollow->addAction(actFlwTplFnsCnex);

        connect(actAddFn, &QAction::triggered,
                this, &MainWindow::addNewFunctionChild_triggered);
        connect(actDelete, &QAction::triggered,
                this, &MainWindow::deleteRowValue_triggered);
        connect(actUp, &QAction::triggered,
                this, &MainWindow::upRowValue_triggered);
        connect(actDown, &QAction::triggered,
                this, &MainWindow::downRowValue_triggered);
        connect(actMoveToRow, &QAction::triggered,
                this, &MainWindow::moveToRowValue_triggered);

        connect(actInsBasicBlock, &QAction::triggered,
                this, &MainWindow::addNewBasicBlockInsert_triggered);
        connect(actFlwBasicBlock, &QAction::triggered,
                this, &MainWindow::addNewBasicBlockFollow_triggered);
        connect(actInsLabel, &QAction::triggered,
                this, &MainWindow::addNewLabelInsert_triggered);
        connect(actFlwLabel, &QAction::triggered,
                this, &MainWindow::addNewLabelFollow_triggered);
        connect(actInsPubLabel, &QAction::triggered,
                this, &MainWindow::addNewPublicLabelInsert_triggered);
        connect(actFlwPubLabel, &QAction::triggered,
                this, &MainWindow::addNewPublicLabelFollow_triggered);
        connect(actInsProtLabel, &QAction::triggered,
                this, &MainWindow::addNewProtectedLabelInsert_triggered);
        connect(actFlwProtLabel, &QAction::triggered,
                this, &MainWindow::addNewProtectedLabelFollow_triggered);
        connect(actInsPrvLabel, &QAction::triggered,
                this, &MainWindow::addNewPrivateLabelInsert_triggered);
        connect(actFlwPrvLabel, &QAction::triggered,
                this, &MainWindow::addNewPrivateLabelFollow_triggered);

        connect(actInsCtors, &QAction::triggered,
                this, &MainWindow::addNewCtorsInsert_triggered);
        connect(actFlwCtors, &QAction::triggered,
                this, &MainWindow::addNewCtorsFollow_triggered);
        connect(actInsTplCtors, &QAction::triggered,
                this, &MainWindow::addNewTplCtorsInsert_triggered);
        connect(actFlwTplCtors, &QAction::triggered,
                this, &MainWindow::addNewTplCtorsFollow_triggered);
        connect(actInsDefCtor, &QAction::triggered,
                this, &MainWindow::addNewDefCtorFnInsert_triggered);
        connect(actFlwDefCtor, &QAction::triggered,
                this, &MainWindow::addNewDefCtorFnFollow_triggered);
        connect(actInsCopyCtor, &QAction::triggered,
                this, &MainWindow::addNewCopyCtorFnInsert_triggered);
        connect(actFlwCopyCtor, &QAction::triggered,
                this, &MainWindow::addNewCopyCtorFnFollow_triggered);
        connect(actInsMoveCtor, &QAction::triggered,
                this, &MainWindow::addNewMoveCtorFnInsert_triggered);
        connect(actFlwMoveCtor, &QAction::triggered,
                this, &MainWindow::addNewMoveCtorFnFollow_triggered);
        connect(actInsDtor, &QAction::triggered,
                this, &MainWindow::addNewDtorFnInsert_triggered);
        connect(actFlwDtor, &QAction::triggered,
                this, &MainWindow::addNewDtorFnFollow_triggered);
        connect(actInsCopyEq, &QAction::triggered,
                this, &MainWindow::addNewCopyOpEqFnInsert_triggered);
        connect(actFlwCopyEq, &QAction::triggered,
                this, &MainWindow::addNewCopyOpEqFnFollow_triggered);
        connect(actInsMoveEq, &QAction::triggered,
                this, &MainWindow::addNewMoveOpEqFnInsert_triggered);
        connect(actFlwMoveEq, &QAction::triggered,
                this, &MainWindow::addNewMoveOpEqFnFollow_triggered);

        connect(actInsClassDec, &QAction::triggered,
                this, &MainWindow::addNewClassDecInsert_triggered);
        connect(actInsClass, &QAction::triggered,
                this, &MainWindow::addNewClassInsert_triggered);
        connect(actInsStructDec, &QAction::triggered,
                this, &MainWindow::addNewStructDecInsert_triggered);
        connect(actInsStruct, &QAction::triggered,
                this, &MainWindow::addNewStructInsert_triggered);
        connect(actInsEnum, &QAction::triggered,
                this, &MainWindow::addNewEnumInsert_triggered);
        connect(actInsTypedef, &QAction::triggered,
                this, &MainWindow::addNewTypedefInsert_triggered);

        connect(actFlwClassDec, &QAction::triggered,
                this, &MainWindow::addNewClassDecFollow_triggered);
        connect(actFlwClass, &QAction::triggered,
                this, &MainWindow::addNewClassFollow_triggered);
        connect(actFlwStructDec, &QAction::triggered,
                this, &MainWindow::addNewStructDecFollow_triggered);
        connect(actFlwStruct, &QAction::triggered,
                this, &MainWindow::addNewStructFollow_triggered);
        connect(actFlwEnum, &QAction::triggered,
                this, &MainWindow::addNewEnumFollow_triggered);
        connect(actFlwTypedef, &QAction::triggered,
                this, &MainWindow::addNewTypedefFollow_triggered);

        connect(actInsFns, &QAction::triggered,
                this, &MainWindow::addNewFnsInsert_triggered);
        connect(actInsFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewStaticFnsInsert_triggered);
        connect(actInsFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewCoexFnsInsert_triggered);
        connect(actInsTplFns, &QAction::triggered,
                this, &MainWindow::addNewTplFnsInsert_triggered);
        connect(actInsTplFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewTplStaticFnsInsert_triggered);
        connect(actInsTplFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewTplCoexFnsInsert_triggered);

        connect(actFlwFns, &QAction::triggered,
                this, &MainWindow::addNewFnsFollow_triggered);
        connect(actFlwFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewStaticFnsFollow_triggered);
        connect(actFlwFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewCoexFnsFollow_triggered);
        connect(actFlwTplFns, &QAction::triggered,
                this, &MainWindow::addNewTplFnsFollow_triggered);
        connect(actFlwTplFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewTplStaticFnsFollow_triggered);
        connect(actFlwTplFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewTplCoexFnsFollow_triggered);

    }
    {
        QAction *  actAddNewFn = new QAction(tr("Add New"));
        QAction *  actInsertNewFn = new QAction(tr("Insert New"));
        QAction *  actFollowNewFn = new QAction(tr("Follow New"));
        QAction *  actCopyFnInsertToNew = new QAction(tr("Copy Insert"));
        QAction *  actCopyFnToNew = new QAction(tr("Copy Follow"));
        QAction *  actCopyFnToNewEnd = new QAction(tr("Copy New"));

        QAction *  actDeleteFn = new QAction(tr("Delete"));
        QAction *  actUp = new QAction(tr("Up"));
        QAction *  actDown = new QAction(tr("Down"));
        QAction *  actMoveToRow = new QAction(tr("Move To Row"));

        QAction *  actMoveIntoClass = new QAction(tr("Move into Class"));
        QAction *  actMoveOutsideClass = new QAction(tr("Move outside the Class"));

        QAction *  actMoveToPublic = new QAction(tr("Move To Public"));
        QAction *  actMoveToProtected = new QAction(tr("Move To Protected"));
        QAction *  actMoveToPrivate = new QAction(tr("Move To Private"));

        QAction *  actMoveToFns = new QAction(tr("Move To Functions"));
        QAction *  actMoveToStaticFns = new QAction(tr("Move To Static Functions"));
        QAction *  actMoveToCoexFns = new QAction(tr("Move To Constexpr Functions"));
        QAction *  actMoveToTplFns = new QAction(tr("Move To Tpl Functions"));
        QAction *  actMoveToTplStaticFns = new QAction(tr("Move To Tpl Static Functions"));
        QAction *  actMoveToTplCoexFns = new QAction(tr("Move To Tpl Constexpr Functions"));

        m_fnMenu->addAction(actUp);
        m_fnMenu->addAction(actDown);
        m_fnMenu->addAction(actMoveToRow);
        m_fnMenu->addSeparator();
        m_fnMenu->addAction(actAddNewFn);
        m_fnMenu->addAction(actInsertNewFn);
        m_fnMenu->addAction(actFollowNewFn);
        m_fnMenu->addSeparator();
        m_fnMenu->addAction(actCopyFnInsertToNew);
        m_fnMenu->addAction(actCopyFnToNew);
        m_fnMenu->addAction(actCopyFnToNewEnd);
        m_fnMenu->addSeparator();
        m_fnMenu->addAction(actMoveToPublic);
        m_fnMenu->addAction(actMoveToProtected);
        m_fnMenu->addAction(actMoveToPrivate);
        m_fnMenu->addSeparator();
        m_fnMenu->addAction(actMoveToFns);
        m_fnMenu->addAction(actMoveToStaticFns);
        m_fnMenu->addAction(actMoveToCoexFns);
        m_fnMenu->addAction(actMoveToTplFns);
        m_fnMenu->addAction(actMoveToTplStaticFns);
        m_fnMenu->addAction(actMoveToTplCoexFns);
        m_fnMenu->addSeparator();
        m_fnMenu->addAction(actMoveIntoClass);
        m_fnMenu->addAction(actMoveOutsideClass);
        m_fnMenu->addSeparator();
        m_fnMenu->addAction(actDeleteFn);

        connect(actAddNewFn, &QAction::triggered,
                this, &MainWindow::addNewFunctionInsertEnd_triggered);
        connect(actInsertNewFn, &QAction::triggered,
                this, &MainWindow::addNewFunctionInsert_triggered);
        connect(actFollowNewFn, &QAction::triggered,
                this, &MainWindow::addNewFunctionFollow_triggered);
        connect(actCopyFnInsertToNew, &QAction::triggered,
                this, &MainWindow::addCopyFunctionInsert_triggered);
        connect(actCopyFnToNew, &QAction::triggered,
                this, &MainWindow::addCopyFunctionFollow_triggered);
        connect(actCopyFnToNewEnd, &QAction::triggered,
                this, &MainWindow::addCopyFunctionInsertEnd_triggered);

        connect(actDeleteFn, &QAction::triggered,
                this, &MainWindow::deleteRowFunction_triggered);
        connect(actUp, &QAction::triggered,
                this, &MainWindow::upRowFunction_triggered);
        connect(actDown, &QAction::triggered,
                this, &MainWindow::downRowFunction_triggered);
        connect(actMoveToRow, &QAction::triggered,
                this, &MainWindow::moveToRowFunction_triggered);

    }
    {
        QAction *  actCopyInsertToNew = new QAction(tr("Copy Insert"));
        QAction *  actCopyToNew = new QAction(tr("Copy Follow"));
        QAction *  actDelete = new QAction(tr("Delete"));
        QAction *  actUp = new QAction(tr("Up"));
        QAction *  actDown = new QAction(tr("Down"));
        QAction *  actMoveToRow = new QAction(tr("Move To Row"));

        QAction *  actInsClassDec = new QAction(tr("New Class Declaration"));
        QAction *  actInsClass = new QAction(tr("New Class"));
        QAction *  actInsStructDec = new QAction(tr("New Struct Declaration"));
        QAction *  actInsStruct = new QAction(tr("New Struct"));
        QAction *  actInsEnum = new QAction(tr("New Enum"));
        QAction *  actInsTypedef = new QAction(tr("New Typedef"));

        QAction *  actInsPubLabel = new QAction(tr("New Public Label"));
        QAction *  actInsProtLabel = new QAction(tr("New Protected Label"));
        QAction *  actInsPrvLabel = new QAction(tr("New Private Label"));
        QAction *  actInsLabel = new QAction(tr("New Label"));

        QAction *  actInsDefCtor = new QAction(tr("New Default Constructor"));
        QAction *  actInsCopyCtor = new QAction(tr("New Copy Constructor"));
        QAction *  actInsMoveCtor = new QAction(tr("New Move Constructor"));
        QAction *  actInsDtor = new QAction(tr("New ~Destructor"));
        QAction *  actInsCopyEq = new QAction(tr("New Copy Operator="));
        QAction *  actInsMoveEq = new QAction(tr("New Move Operator="));

        QAction *  actInsCtors = new QAction(tr("New Constructors"));
        QAction *  actInsTplCtors = new QAction(tr("New Template Constructors"));

        QAction *  actInsFns = new QAction(tr("New Functions"));
        QAction *  actInsFnsStatic = new QAction(tr("New Functions Static"));
        QAction *  actInsFnsCnex = new QAction(tr("New Functions Constexpr"));
        QAction *  actInsTplFns = new QAction(tr("New Template Functions"));
        QAction *  actInsTplFnsStatic = new QAction(tr("New Template Functions Static"));
        QAction *  actInsTplFnsCnex = new QAction(tr("New Template Functions Constexpr"));

        QAction *  actInsBasicBlock = new QAction(tr("New BasicBlock"));

        QAction *  actFlwClassDec = new QAction(tr("New Class Declaration"));
        QAction *  actFlwClass = new QAction(tr("New Class"));
        QAction *  actFlwStructDec = new QAction(tr("New Struct Declaration"));
        QAction *  actFlwStruct = new QAction(tr("New Struct"));
        QAction *  actFlwEnum = new QAction(tr("New Enum"));
        QAction *  actFlwTypedef = new QAction(tr("New Typedef"));

        QAction *  actFlwPubLabel = new QAction(tr("New Public Label"));
        QAction *  actFlwProtLabel = new QAction(tr("New Protected Label"));
        QAction *  actFlwPrvLabel = new QAction(tr("New Private Label"));
        QAction *  actFlwLabel = new QAction(tr("New Label"));

        QAction *  actFlwDefCtor = new QAction(tr("New Default Constructor"));
        QAction *  actFlwCopyCtor = new QAction(tr("New Copy Constructor"));
        QAction *  actFlwMoveCtor = new QAction(tr("New Move Constructor"));
        QAction *  actFlwDtor = new QAction(tr("New ~Destructor"));
        QAction *  actFlwCopyEq = new QAction(tr("New Copy Operator="));
        QAction *  actFlwMoveEq = new QAction(tr("New Move Operator="));

        QAction *  actFlwCtors = new QAction(tr("New Constructors"));
        QAction *  actFlwTplCtors = new QAction(tr("New Template Constructors"));

        QAction *  actFlwFns = new QAction(tr("New Functions"));
        QAction *  actFlwFnsStatic = new QAction(tr("New Functions Static"));
        QAction *  actFlwFnsCnex = new QAction(tr("New Functions Constexpr"));
        QAction *  actFlwTplFns = new QAction(tr("New Template Functions"));
        QAction *  actFlwTplFnsStatic = new QAction(tr("New Template Functions Static"));
        QAction *  actFlwTplFnsCnex = new QAction(tr("New Template Functions Constexpr"));

        QAction *  actFlwBasicBlock = new QAction(tr("New BasicBlock"));

        QMenu *  menuInsert = new QMenu(m_otherMenu);
        QMenu *  menuFollow = new QMenu(m_otherMenu);

        QAction *  actParentInsert = m_otherMenu->addAction(tr("Insert"));
        QAction *  actParentFollow = m_otherMenu->addAction(tr("Follow"));
        actParentInsert->setMenu(menuInsert);
        actParentFollow->setMenu(menuFollow);

        m_otherMenu->addSeparator();
        m_otherMenu->addAction(actUp);
        m_otherMenu->addAction(actDown);
        m_otherMenu->addAction(actMoveToRow);
        m_otherMenu->addSeparator();
        m_otherMenu->addAction(actCopyInsertToNew);
        m_otherMenu->addAction(actCopyToNew);
        m_otherMenu->addSeparator();
        m_otherMenu->addAction(actDelete);

        menuInsert->addAction(actInsClassDec);
        menuInsert->addAction(actInsClass);
        menuInsert->addAction(actInsStructDec);
        menuInsert->addAction(actInsStruct);
        menuInsert->addAction(actInsEnum);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsBasicBlock);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsPubLabel);
        menuInsert->addAction(actInsProtLabel);
        menuInsert->addAction(actInsPrvLabel);
        menuInsert->addAction(actInsLabel);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsDefCtor);
        menuInsert->addAction(actInsCopyCtor);
        menuInsert->addAction(actInsMoveCtor);
        menuInsert->addAction(actInsDtor);
        menuInsert->addAction(actInsCopyEq);
        menuInsert->addAction(actInsMoveEq);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsCtors);
        menuInsert->addAction(actInsTplCtors);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsFns);
        menuInsert->addAction(actInsFnsStatic);
        menuInsert->addAction(actInsFnsCnex);
        menuInsert->addAction(actInsTplFns);
        menuInsert->addAction(actInsTplFnsStatic);
        menuInsert->addAction(actInsTplFnsCnex);

        menuFollow->addAction(actFlwClassDec);
        menuFollow->addAction(actFlwClass);
        menuFollow->addAction(actFlwStructDec);
        menuFollow->addAction(actFlwStruct);
        menuFollow->addAction(actFlwEnum);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwBasicBlock);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwPubLabel);
        menuFollow->addAction(actFlwProtLabel);
        menuFollow->addAction(actFlwPrvLabel);
        menuFollow->addAction(actFlwLabel);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwDefCtor);
        menuFollow->addAction(actFlwCopyCtor);
        menuFollow->addAction(actFlwMoveCtor);
        menuFollow->addAction(actFlwDtor);
        menuFollow->addAction(actFlwCopyEq);
        menuFollow->addAction(actFlwMoveEq);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwCtors);
        menuFollow->addAction(actFlwTplCtors);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwFns);
        menuFollow->addAction(actFlwFnsStatic);
        menuFollow->addAction(actFlwFnsCnex);
        menuFollow->addAction(actFlwTplFns);
        menuFollow->addAction(actFlwTplFnsStatic);
        menuFollow->addAction(actFlwTplFnsCnex);

        connect(actCopyInsertToNew, &QAction::triggered,
                this, &MainWindow::copyInsertToNewValue_triggered);
        connect(actCopyToNew, &QAction::triggered,
                this, &MainWindow::copyToNewValue_triggered);
        connect(actDelete, &QAction::triggered,
                this, &MainWindow::deleteRowValue_triggered);
        connect(actUp, &QAction::triggered,
                this, &MainWindow::upRowValue_triggered);
        connect(actDown, &QAction::triggered,
                this, &MainWindow::downRowValue_triggered);
        connect(actMoveToRow, &QAction::triggered,
                this, &MainWindow::moveToRowValue_triggered);

        connect(actInsBasicBlock, &QAction::triggered,
                this, &MainWindow::addNewBasicBlockInsert_triggered);
        connect(actFlwBasicBlock, &QAction::triggered,
                this, &MainWindow::addNewBasicBlockFollow_triggered);
        connect(actInsLabel, &QAction::triggered,
                this, &MainWindow::addNewLabelInsert_triggered);
        connect(actFlwLabel, &QAction::triggered,
                this, &MainWindow::addNewLabelFollow_triggered);
        connect(actInsPubLabel, &QAction::triggered,
                this, &MainWindow::addNewPublicLabelInsert_triggered);
        connect(actFlwPubLabel, &QAction::triggered,
                this, &MainWindow::addNewPublicLabelFollow_triggered);
        connect(actInsProtLabel, &QAction::triggered,
                this, &MainWindow::addNewProtectedLabelInsert_triggered);
        connect(actFlwProtLabel, &QAction::triggered,
                this, &MainWindow::addNewProtectedLabelFollow_triggered);
        connect(actInsPrvLabel, &QAction::triggered,
                this, &MainWindow::addNewPrivateLabelInsert_triggered);
        connect(actFlwPrvLabel, &QAction::triggered,
                this, &MainWindow::addNewPrivateLabelFollow_triggered);

        connect(actInsCtors, &QAction::triggered,
                this, &MainWindow::addNewCtorsInsert_triggered);
        connect(actFlwCtors, &QAction::triggered,
                this, &MainWindow::addNewCtorsFollow_triggered);
        connect(actInsTplCtors, &QAction::triggered,
                this, &MainWindow::addNewTplCtorsInsert_triggered);
        connect(actFlwTplCtors, &QAction::triggered,
                this, &MainWindow::addNewTplCtorsFollow_triggered);
        connect(actInsDefCtor, &QAction::triggered,
                this, &MainWindow::addNewDefCtorFnInsert_triggered);
        connect(actFlwDefCtor, &QAction::triggered,
                this, &MainWindow::addNewDefCtorFnFollow_triggered);
        connect(actInsCopyCtor, &QAction::triggered,
                this, &MainWindow::addNewCopyCtorFnInsert_triggered);
        connect(actFlwCopyCtor, &QAction::triggered,
                this, &MainWindow::addNewCopyCtorFnFollow_triggered);
        connect(actInsMoveCtor, &QAction::triggered,
                this, &MainWindow::addNewMoveCtorFnInsert_triggered);
        connect(actFlwMoveCtor, &QAction::triggered,
                this, &MainWindow::addNewMoveCtorFnFollow_triggered);
        connect(actInsDtor, &QAction::triggered,
                this, &MainWindow::addNewDtorFnInsert_triggered);
        connect(actFlwDtor, &QAction::triggered,
                this, &MainWindow::addNewDtorFnFollow_triggered);
        connect(actInsCopyEq, &QAction::triggered,
                this, &MainWindow::addNewCopyOpEqFnInsert_triggered);
        connect(actFlwCopyEq, &QAction::triggered,
                this, &MainWindow::addNewCopyOpEqFnFollow_triggered);
        connect(actInsMoveEq, &QAction::triggered,
                this, &MainWindow::addNewMoveOpEqFnInsert_triggered);
        connect(actFlwMoveEq, &QAction::triggered,
                this, &MainWindow::addNewMoveOpEqFnFollow_triggered);

        connect(actInsClassDec, &QAction::triggered,
                this, &MainWindow::addNewClassDecInsert_triggered);
        connect(actInsClass, &QAction::triggered,
                this, &MainWindow::addNewClassInsert_triggered);
        connect(actInsStructDec, &QAction::triggered,
                this, &MainWindow::addNewStructDecInsert_triggered);
        connect(actInsStruct, &QAction::triggered,
                this, &MainWindow::addNewStructInsert_triggered);
        connect(actInsEnum, &QAction::triggered,
                this, &MainWindow::addNewEnumInsert_triggered);
        connect(actInsTypedef, &QAction::triggered,
                this, &MainWindow::addNewTypedefInsert_triggered);

        connect(actFlwClassDec, &QAction::triggered,
                this, &MainWindow::addNewClassDecFollow_triggered);
        connect(actFlwClass, &QAction::triggered,
                this, &MainWindow::addNewClassFollow_triggered);
        connect(actFlwStructDec, &QAction::triggered,
                this, &MainWindow::addNewStructDecFollow_triggered);
        connect(actFlwStruct, &QAction::triggered,
                this, &MainWindow::addNewStructFollow_triggered);
        connect(actFlwEnum, &QAction::triggered,
                this, &MainWindow::addNewEnumFollow_triggered);
        connect(actFlwTypedef, &QAction::triggered,
                this, &MainWindow::addNewTypedefFollow_triggered);

        connect(actInsFns, &QAction::triggered,
                this, &MainWindow::addNewFnsInsert_triggered);
        connect(actInsFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewStaticFnsInsert_triggered);
        connect(actInsFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewCoexFnsInsert_triggered);
        connect(actInsTplFns, &QAction::triggered,
                this, &MainWindow::addNewTplFnsInsert_triggered);
        connect(actInsTplFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewTplStaticFnsInsert_triggered);
        connect(actInsTplFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewTplCoexFnsInsert_triggered);

        connect(actFlwFns, &QAction::triggered,
                this, &MainWindow::addNewFnsFollow_triggered);
        connect(actFlwFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewStaticFnsFollow_triggered);
        connect(actFlwFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewCoexFnsFollow_triggered);
        connect(actFlwTplFns, &QAction::triggered,
                this, &MainWindow::addNewTplFnsFollow_triggered);
        connect(actFlwTplFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewTplStaticFnsFollow_triggered);
        connect(actFlwTplFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewTplCoexFnsFollow_triggered);

    }
    {
        QAction *  actUp = new QAction(tr("Up"));
        QAction *  actDown = new QAction(tr("Down"));
        QAction *  actMoveToRow = new QAction(tr("Move To Row"));

        QAction *  actInsClassDec = new QAction(tr("New Class Declaration"));
        QAction *  actInsClass = new QAction(tr("New Class"));
        QAction *  actInsStructDec = new QAction(tr("New Struct Declaration"));
        QAction *  actInsStruct = new QAction(tr("New Struct"));
        QAction *  actInsEnum = new QAction(tr("New Enum"));
        QAction *  actInsTypedef = new QAction(tr("New Typedef"));

        QAction *  actInsPubLabel = new QAction(tr("New Public Label"));
        QAction *  actInsProtLabel = new QAction(tr("New Protected Label"));
        QAction *  actInsPrvLabel = new QAction(tr("New Private Label"));
        QAction *  actInsLabel = new QAction(tr("New Label"));

        QAction *  actInsDefCtor = new QAction(tr("New Default Constructor"));
        QAction *  actInsCopyCtor = new QAction(tr("New Copy Constructor"));
        QAction *  actInsMoveCtor = new QAction(tr("New Move Constructor"));
        QAction *  actInsDtor = new QAction(tr("New ~Destructor"));
        QAction *  actInsCopyEq = new QAction(tr("New Copy Operator="));
        QAction *  actInsMoveEq = new QAction(tr("New Move Operator="));

        QAction *  actInsCtors = new QAction(tr("New Constructors"));
        QAction *  actInsTplCtors = new QAction(tr("New Template Constructors"));

        QAction *  actInsFns = new QAction(tr("New Functions"));
        QAction *  actInsFnsStatic = new QAction(tr("New Functions Static"));
        QAction *  actInsFnsCnex = new QAction(tr("New Functions Constexpr"));
        QAction *  actInsTplFns = new QAction(tr("New Template Functions"));
        QAction *  actInsTplFnsStatic = new QAction(tr("New Template Functions Static"));
        QAction *  actInsTplFnsCnex = new QAction(tr("New Template Functions Constexpr"));

        QAction *  actInsBasicBlock = new QAction(tr("New BasicBlock"));

        QAction *  actFlwClassDec = new QAction(tr("New Class Declaration"));
        QAction *  actFlwClass = new QAction(tr("New Class"));
        QAction *  actFlwStructDec = new QAction(tr("New Struct Declaration"));
        QAction *  actFlwStruct = new QAction(tr("New Struct"));
        QAction *  actFlwEnum = new QAction(tr("New Enum"));
        QAction *  actFlwTypedef = new QAction(tr("New Typedef"));

        QAction *  actFlwPubLabel = new QAction(tr("New Public Label"));
        QAction *  actFlwProtLabel = new QAction(tr("New Protected Label"));
        QAction *  actFlwPrvLabel = new QAction(tr("New Private Label"));
        QAction *  actFlwLabel = new QAction(tr("New Label"));

        QAction *  actFlwDefCtor = new QAction(tr("New Default Constructor"));
        QAction *  actFlwCopyCtor = new QAction(tr("New Copy Constructor"));
        QAction *  actFlwMoveCtor = new QAction(tr("New Move Constructor"));
        QAction *  actFlwDtor = new QAction(tr("New ~Destructor"));
        QAction *  actFlwCopyEq = new QAction(tr("New Copy Operator="));
        QAction *  actFlwMoveEq = new QAction(tr("New Move Operator="));

        QAction *  actFlwCtors = new QAction(tr("New Constructors"));
        QAction *  actFlwTplCtors = new QAction(tr("New Template Constructors"));

        QAction *  actFlwFns = new QAction(tr("New Functions"));
        QAction *  actFlwFnsStatic = new QAction(tr("New Functions Static"));
        QAction *  actFlwFnsCnex = new QAction(tr("New Functions Constexpr"));
        QAction *  actFlwTplFns = new QAction(tr("New Template Functions"));
        QAction *  actFlwTplFnsStatic = new QAction(tr("New Template Functions Static"));
        QAction *  actFlwTplFnsCnex = new QAction(tr("New Template Functions Constexpr"));

        QAction *  actFlwBasicBlock = new QAction(tr("New BasicBlock"));

        QMenu *  menuInsert = new QMenu(m_defaultMenu);
        QMenu *  menuFollow = new QMenu(m_defaultMenu);

        QAction *  actParentInsert = m_defaultMenu->addAction(tr("Insert"));
        QAction *  actParentFollow = m_defaultMenu->addAction(tr("Follow"));
        actParentInsert->setMenu(menuInsert);
        actParentFollow->setMenu(menuFollow);

        m_defaultMenu->addSeparator();
        m_defaultMenu->addAction(actUp);
        m_defaultMenu->addAction(actDown);
        m_defaultMenu->addAction(actMoveToRow);

        menuInsert->addAction(actInsClassDec);
        menuInsert->addAction(actInsClass);
        menuInsert->addAction(actInsStructDec);
        menuInsert->addAction(actInsStruct);
        menuInsert->addAction(actInsEnum);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsBasicBlock);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsPubLabel);
        menuInsert->addAction(actInsProtLabel);
        menuInsert->addAction(actInsPrvLabel);
        menuInsert->addAction(actInsLabel);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsDefCtor);
        menuInsert->addAction(actInsCopyCtor);
        menuInsert->addAction(actInsMoveCtor);
        menuInsert->addAction(actInsDtor);
        menuInsert->addAction(actInsCopyEq);
        menuInsert->addAction(actInsMoveEq);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsCtors);
        menuInsert->addAction(actInsTplCtors);
        menuInsert->addSeparator();
        menuInsert->addAction(actInsFns);
        menuInsert->addAction(actInsFnsStatic);
        menuInsert->addAction(actInsFnsCnex);
        menuInsert->addAction(actInsTplFns);
        menuInsert->addAction(actInsTplFnsStatic);
        menuInsert->addAction(actInsTplFnsCnex);

        menuFollow->addAction(actFlwClassDec);
        menuFollow->addAction(actFlwClass);
        menuFollow->addAction(actFlwStructDec);
        menuFollow->addAction(actFlwStruct);
        menuFollow->addAction(actFlwEnum);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwBasicBlock);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwPubLabel);
        menuFollow->addAction(actFlwProtLabel);
        menuFollow->addAction(actFlwPrvLabel);
        menuFollow->addAction(actFlwLabel);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwDefCtor);
        menuFollow->addAction(actFlwCopyCtor);
        menuFollow->addAction(actFlwMoveCtor);
        menuFollow->addAction(actFlwDtor);
        menuFollow->addAction(actFlwCopyEq);
        menuFollow->addAction(actFlwMoveEq);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwCtors);
        menuFollow->addAction(actFlwTplCtors);
        menuFollow->addSeparator();
        menuFollow->addAction(actFlwFns);
        menuFollow->addAction(actFlwFnsStatic);
        menuFollow->addAction(actFlwFnsCnex);
        menuFollow->addAction(actFlwTplFns);
        menuFollow->addAction(actFlwTplFnsStatic);
        menuFollow->addAction(actFlwTplFnsCnex);

        connect(actUp, &QAction::triggered,
                this, &MainWindow::upRowValue_triggered);
        connect(actDown, &QAction::triggered,
                this, &MainWindow::downRowValue_triggered);
        connect(actMoveToRow, &QAction::triggered,
                this, &MainWindow::moveToRowValue_triggered);

        connect(actInsBasicBlock, &QAction::triggered,
                this, &MainWindow::addNewBasicBlockInsert_triggered);
        connect(actFlwBasicBlock, &QAction::triggered,
                this, &MainWindow::addNewBasicBlockFollow_triggered);
        connect(actInsLabel, &QAction::triggered,
                this, &MainWindow::addNewLabelInsert_triggered);
        connect(actFlwLabel, &QAction::triggered,
                this, &MainWindow::addNewLabelFollow_triggered);
        connect(actInsPubLabel, &QAction::triggered,
                this, &MainWindow::addNewPublicLabelInsert_triggered);
        connect(actFlwPubLabel, &QAction::triggered,
                this, &MainWindow::addNewPublicLabelFollow_triggered);
        connect(actInsProtLabel, &QAction::triggered,
                this, &MainWindow::addNewProtectedLabelInsert_triggered);
        connect(actFlwProtLabel, &QAction::triggered,
                this, &MainWindow::addNewProtectedLabelFollow_triggered);
        connect(actInsPrvLabel, &QAction::triggered,
                this, &MainWindow::addNewPrivateLabelInsert_triggered);
        connect(actFlwPrvLabel, &QAction::triggered,
                this, &MainWindow::addNewPrivateLabelFollow_triggered);

        connect(actInsCtors, &QAction::triggered,
                this, &MainWindow::addNewCtorsInsert_triggered);
        connect(actFlwCtors, &QAction::triggered,
                this, &MainWindow::addNewCtorsFollow_triggered);
        connect(actInsTplCtors, &QAction::triggered,
                this, &MainWindow::addNewTplCtorsInsert_triggered);
        connect(actFlwTplCtors, &QAction::triggered,
                this, &MainWindow::addNewTplCtorsFollow_triggered);
        connect(actInsDefCtor, &QAction::triggered,
                this, &MainWindow::addNewDefCtorFnInsert_triggered);
        connect(actFlwDefCtor, &QAction::triggered,
                this, &MainWindow::addNewDefCtorFnFollow_triggered);
        connect(actInsCopyCtor, &QAction::triggered,
                this, &MainWindow::addNewCopyCtorFnInsert_triggered);
        connect(actFlwCopyCtor, &QAction::triggered,
                this, &MainWindow::addNewCopyCtorFnFollow_triggered);
        connect(actInsMoveCtor, &QAction::triggered,
                this, &MainWindow::addNewMoveCtorFnInsert_triggered);
        connect(actFlwMoveCtor, &QAction::triggered,
                this, &MainWindow::addNewMoveCtorFnFollow_triggered);
        connect(actInsDtor, &QAction::triggered,
                this, &MainWindow::addNewDtorFnInsert_triggered);
        connect(actFlwDtor, &QAction::triggered,
                this, &MainWindow::addNewDtorFnFollow_triggered);
        connect(actInsCopyEq, &QAction::triggered,
                this, &MainWindow::addNewCopyOpEqFnInsert_triggered);
        connect(actFlwCopyEq, &QAction::triggered,
                this, &MainWindow::addNewCopyOpEqFnFollow_triggered);
        connect(actInsMoveEq, &QAction::triggered,
                this, &MainWindow::addNewMoveOpEqFnInsert_triggered);
        connect(actFlwMoveEq, &QAction::triggered,
                this, &MainWindow::addNewMoveOpEqFnFollow_triggered);

        connect(actInsClassDec, &QAction::triggered,
                this, &MainWindow::addNewClassDecInsert_triggered);
        connect(actInsClass, &QAction::triggered,
                this, &MainWindow::addNewClassInsert_triggered);
        connect(actInsStructDec, &QAction::triggered,
                this, &MainWindow::addNewStructDecInsert_triggered);
        connect(actInsStruct, &QAction::triggered,
                this, &MainWindow::addNewStructInsert_triggered);
        connect(actInsEnum, &QAction::triggered,
                this, &MainWindow::addNewEnumInsert_triggered);
        connect(actInsTypedef, &QAction::triggered,
                this, &MainWindow::addNewTypedefInsert_triggered);

        connect(actFlwClassDec, &QAction::triggered,
                this, &MainWindow::addNewClassDecFollow_triggered);
        connect(actFlwClass, &QAction::triggered,
                this, &MainWindow::addNewClassFollow_triggered);
        connect(actFlwStructDec, &QAction::triggered,
                this, &MainWindow::addNewStructDecFollow_triggered);
        connect(actFlwStruct, &QAction::triggered,
                this, &MainWindow::addNewStructFollow_triggered);
        connect(actFlwEnum, &QAction::triggered,
                this, &MainWindow::addNewEnumFollow_triggered);
        connect(actFlwTypedef, &QAction::triggered,
                this, &MainWindow::addNewTypedefFollow_triggered);

        connect(actInsFns, &QAction::triggered,
                this, &MainWindow::addNewFnsInsert_triggered);
        connect(actInsFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewStaticFnsInsert_triggered);
        connect(actInsFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewCoexFnsInsert_triggered);
        connect(actInsTplFns, &QAction::triggered,
                this, &MainWindow::addNewTplFnsInsert_triggered);
        connect(actInsTplFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewTplStaticFnsInsert_triggered);
        connect(actInsTplFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewTplCoexFnsInsert_triggered);

        connect(actFlwFns, &QAction::triggered,
                this, &MainWindow::addNewFnsFollow_triggered);
        connect(actFlwFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewStaticFnsFollow_triggered);
        connect(actFlwFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewCoexFnsFollow_triggered);
        connect(actFlwTplFns, &QAction::triggered,
                this, &MainWindow::addNewTplFnsFollow_triggered);
        connect(actFlwTplFnsStatic, &QAction::triggered,
                this, &MainWindow::addNewTplStaticFnsFollow_triggered);
        connect(actFlwTplFnsCnex, &QAction::triggered,
                this, &MainWindow::addNewTplCoexFnsFollow_triggered);

    }
}

void
MainWindow::addProject_triggered()
{
    insertProject(QModelIndex(), false);
}

void
MainWindow::copyProject_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  vec = m_obj.getEobjList();
        insertProject(index, true, *vec[row]);
    }
}

void
MainWindow::deleteProject_triggered()
{
    QStandardItem *  rootItem = m_mainTreeModel->invisibleRootItem();
    QModelIndex const  index = m_mainTreeView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  vec = m_obj.getEobjList();
        vec.erase(vec.begin() + row);
        m_obj.setEobjList(vec);

        rootItem->removeRow(row);
    }
}

void
MainWindow::upProject_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    const int  row = index.row();
    if (index.isValid() && row != 0) {
        auto  vec = m_obj.getEobjList();
        std::swap(vec[row], vec[row - 1]);
        m_obj.setEobjList(vec);

        QModelIndex  zeroIdx = index.sibling(row, 0);
        bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
        auto const  item = m_mainTreeModel->takeRow(row);
        m_mainTreeModel->insertRow(row - 1, item);
        zeroIdx = index.sibling(row - 1, 0);
        if (isExpanded) {
            m_mainTreeView->expand(zeroIdx);
        }
        QModelIndex const  idx = index.sibling(row - 1, 0);
        m_mainTreeView->setCurrentIndex(idx);
    }
}

void
MainWindow::downProject_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    const int  row = index.row();
    const int  count = m_mainTreeModel->rowCount();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  vec = m_obj.getEobjList();
        std::swap(vec[row], vec[row + 1]);
        m_obj.setEobjList(vec);

        QModelIndex  zeroIdx = index.sibling(row + 1, 0);
        bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
        auto const  item = m_mainTreeModel->takeRow(row + 1);
        m_mainTreeModel->insertRow(row, item);
        zeroIdx = index.sibling(row, 0);
        if (isExpanded) {
            m_mainTreeView->expand(zeroIdx);
        }
        QModelIndex const  idx = index.sibling(row + 1, 0);
        m_mainTreeView->setCurrentIndex(idx);
    }
}

void
MainWindow::moveToRowProject_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    int const  count = m_mainTreeModel->rowCount();
    size_t  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        size_t  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (!ok)  return;

        auto  vec = m_obj.getEobjList();
        if (!xu::moveVec_0(vec, currRow, movetoRow)) {
            return;
        }
        m_obj.setEobjList(vec);

        QModelIndex  zeroIdx = index.sibling(static_cast<int>(currRow), 0);
        bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
        auto const  item = m_mainTreeModel->takeRow(static_cast<int>(currRow));
        m_mainTreeModel->insertRow(static_cast<int>(movetoRow), item);
        zeroIdx = index.sibling(static_cast<int>(movetoRow), 0);
        if (isExpanded) {
            m_mainTreeView->expand(zeroIdx);
        }
        QModelIndex const  idx = index.sibling(static_cast<int>(movetoRow), 0);
        m_mainTreeView->setCurrentIndex(idx);
    }
}

void
MainWindow::addModuleProject_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    if (index.isValid()) {
        insertModule(index, AddMethod::childAdd, false);
    }
}

void
MainWindow::addModule_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    QModelIndex const  parentIndex = m_mainTreeModel->indexFromItem(parentItem);

    if (parentIndex.isValid()) {
        insertModule(parentIndex, AddMethod::childAdd, false);
    }
}

void
MainWindow::insertNewModule_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertModule(index, AddMethod::insert, false);
    }
}

void
MainWindow::copyModuleToNew_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    int const  row = index.row();
    QModelIndex const  parentIndex = m_mainTreeModel->indexFromItem(parentItem);
    int const  parentRow = parentIndex.row();

    if (index.isValid()) {
        auto  vecProj = m_obj.getEobjList();
        auto  vecMod = vecProj[parentRow]->getEobjList();
        insertModule(index, AddMethod::follow, true, *vecMod[row]);
    }
}

void
MainWindow::deleteModule_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    int const  row = index.row();
    QModelIndex const  parentIndex = m_mainTreeModel->indexFromItem(parentItem);
    int const  parentRow = parentIndex.row();

    if (index.isValid()) {
        auto  vecProj = m_obj.getEobjList();
        auto  vecMod = vecProj[parentRow]->getEobjList();
        vecMod.erase(vecMod.begin() + row);
        vecProj[parentRow]->setEobjList(vecMod);
        m_obj.setEobjList(vecProj);

        parentItem->removeRow(row);
    }
}

void
MainWindow::upModule_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    int const  row = index.row();
    QModelIndex const  parentIndex = m_mainTreeModel->indexFromItem(parentItem);
    int const  parentRow = parentIndex.row();

    if (index.isValid() && row != 0) {
        auto  vecProj = m_obj.getEobjList();
        auto  vecMod = vecProj[parentRow]->getEobjList();
        std::swap(vecMod[row], vecMod[row - 1]);
        vecProj[parentRow]->setEobjList(vecMod);
        m_obj.setEobjList(vecProj);

        QModelIndex  zeroIdx = index.sibling(row, 0);
        bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
        auto const  item = parentItem->takeRow(row);
        parentItem->insertRow(row - 1, item);
        zeroIdx = index.sibling(row - 1, 0);
        if (isExpanded) {
            m_mainTreeView->expand(zeroIdx);
        }
        QModelIndex const  idx = index.sibling(row - 1, 0);
        m_mainTreeView->setCurrentIndex(idx);
    }
}

void
MainWindow::downModule_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    int const  row = index.row();
    QModelIndex const  parentIndex = m_mainTreeModel->indexFromItem(parentItem);
    int const  parentRow = parentIndex.row();
    int const  count = parentItem->rowCount();

    if (index.isValid() && count > 1 && row != count - 1) {
        auto  vecProj = m_obj.getEobjList();
        auto  vecMod = vecProj[parentRow]->getEobjList();
        std::swap(vecMod[row], vecMod[row + 1]);
        vecProj[parentRow]->setEobjList(vecMod);
        m_obj.setEobjList(vecProj);

        QModelIndex  zeroIdx = index.sibling(row + 1, 0);
        bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
        auto const  item = parentItem->takeRow(row + 1);
        parentItem->insertRow(row, item);
        zeroIdx = index.sibling(row, 0);
        if (isExpanded) {
            m_mainTreeView->expand(zeroIdx);
        }
        QModelIndex const  idx = index.sibling(row + 1, 0);
        m_mainTreeView->setCurrentIndex(idx);
    }
}

void
MainWindow::moveToRowModule_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    size_t  currRow = index.row();
    QModelIndex const  parentIndex = m_mainTreeModel->indexFromItem(parentItem);
    int const  parentRow = parentIndex.row();
    int const  count = parentItem->rowCount();

    if (index.isValid() && count > 1) {
        bool  ok = false;
        size_t  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (!ok)  return;

        auto  vecProj = m_obj.getEobjList();
        auto  vecMod = vecProj[parentRow]->getEobjList();
        if (!xu::moveVec_0(vecMod, currRow, movetoRow)) {
            return;
        }
        vecProj[parentRow]->setEobjList(vecMod);
        m_obj.setEobjList(vecProj);

        QModelIndex  zeroIdx = index.sibling(static_cast<int>(currRow), 0);
        bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
        auto const  item = parentItem->takeRow(static_cast<int>(currRow));
        parentItem->insertRow(static_cast<int>(movetoRow), item);
        zeroIdx = index.sibling(static_cast<int>(movetoRow), 0);
        if (isExpanded) {
            m_mainTreeView->expand(zeroIdx);
        }
        QModelIndex const  idx = index.sibling(static_cast<int>(movetoRow), 0);
        m_mainTreeView->setCurrentIndex(idx);
    }
}

void
MainWindow::addNewBasicBlockChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eBasicBlock, BasicBlock());
    }
}

void
MainWindow::addNewBasicBlockInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eBasicBlock, BasicBlock());
    }
}

void
MainWindow::addNewBasicBlockFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eBasicBlock, BasicBlock());
    }
}

void
MainWindow::addCopyBasicBlockInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eBasicBlock, *static_cast<BasicBlock *>(ptr));
    }
}

void
MainWindow::addCopyBasicBlockFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eBasicBlock, *static_cast<BasicBlock *>(ptr));
    }
}

void
MainWindow::addNewLabelChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eLabel, Label());
    }
}

void
MainWindow::addNewLabelInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eLabel, Label());
    }
}

void
MainWindow::addNewLabelFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eLabel, Label());
    }
}

void
MainWindow::addCopyLabelInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eLabel, *static_cast<Label *>(ptr));
    }
}

void
MainWindow::addCopyLabelFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eLabel, *static_cast<Label *>(ptr));
    }
}

void
MainWindow::addNewPublicLabelChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::ePublicLabel, PublicLabel());
    }
}

void
MainWindow::addNewPublicLabelInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::ePublicLabel, PublicLabel());
    }
}

void
MainWindow::addNewPublicLabelFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::ePublicLabel, PublicLabel());
    }
}

void
MainWindow::addCopyPublicLabelInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::ePublicLabel, *static_cast<PublicLabel *>(ptr));
    }
}

void
MainWindow::addCopyPublicLabelFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::ePublicLabel, *static_cast<PublicLabel *>(ptr));
    }
}

void
MainWindow::addNewProtectedLabelChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eProtectedLabel, ProtectedLabel());
    }
}

void
MainWindow::addNewProtectedLabelInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eProtectedLabel, ProtectedLabel());
    }
}

void
MainWindow::addNewProtectedLabelFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eProtectedLabel, ProtectedLabel());
    }
}

void
MainWindow::addCopyProtectedLabelInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eProtectedLabel, *static_cast<ProtectedLabel *>(ptr));
    }
}

void
MainWindow::addCopyProtectedLabelFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eProtectedLabel, *static_cast<ProtectedLabel *>(ptr));
    }
}

void
MainWindow::addNewPrivateLabelChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::ePrivateLabel, PrivateLabel());
    }
}

void
MainWindow::addNewPrivateLabelInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::ePrivateLabel, PrivateLabel());
    }
}

void
MainWindow::addNewPrivateLabelFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::ePrivateLabel, PrivateLabel());
    }
}

void
MainWindow::addCopyPrivateLabelInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::ePrivateLabel, *static_cast<PrivateLabel *>(ptr));
    }
}

void
MainWindow::addCopyPrivateLabelFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::ePrivateLabel, *static_cast<PrivateLabel *>(ptr));
    }
}

void
MainWindow::deleteRowValue_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
        Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
        void *  selfPtr = selfItem->data(Qt::UserRole + 2).value<void *>();

        QStandardItem *  parentItem = selfItem->parent();
        void *  parentPtr = parentItem->data(Qt::UserRole + 2).value<void *>();

        switch (selfEtp) {
        case Etype::eFunctions :
        case Etype::eStaticFunctions :
        case Etype::eConstexprFunctions :
        case Etype::eTplFunctions :
        case Etype::eTplStaticFunctions :
        case Etype::eTplConstexprFunctions :
        case Etype::eConstructors :
        case Etype::eTplConstructors :
            if (static_cast<Functions *>(selfPtr)->getFunctionRef().size() == 0) {
                deleteRowValue(index);
            }
            break;
        case Etype::eClass :
            {
                int const  count = parentItem->rowCount();
                for (int  i = 0; i < count; ++i) {
                    QStandardItem *  item = parentItem->child(i);
                    Etype const  etp = static_cast<Etype>(item->data(
                            Qt::UserRole + 1).toInt());
                    if (etp == Etype::eClassDeclaration) {
                        MyClassDec *  ptr = static_cast<MyClassDec *>(item->data(
                                Qt::UserRole + 2).value<void *>());
                        std::string const  cName = ptr->getClassName();
                        if (static_cast<MyClass *>(selfPtr)->getClassName() == cName) {
                            ptr->setParentClassPtr(nullptr);
                        }
                    }
                }
                deleteRowValue(index);
            }
            break;
        case Etype::eStruct :
            {
                int const  count = parentItem->rowCount();
                for (int  i = 0; i < count; ++i) {
                    QStandardItem *  item = parentItem->child(i);
                    Etype const  etp = static_cast<Etype>(item->data(
                            Qt::UserRole + 1).toInt());
                    if (etp == Etype::eStructDeclaration) {
                        MyStructDec *  ptr = static_cast<MyStructDec *>(item->data(
                                Qt::UserRole + 2).value<void *>());
                        std::string const  cName = ptr->getStructName();
                        if (static_cast<MyStruct *>(selfPtr)->getName() == cName) {
                            ptr->setParentStructPtr(nullptr);
                        }
                    }
                }
                deleteRowValue(index);
            }
            break;
        default :
            deleteRowValue(index);
            break;
        }
    }
}

void
MainWindow::upRowValue_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        upRowValue(index);
    }
}

void
MainWindow::downRowValue_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        downRowValue(index);
    }
}

void
MainWindow::moveToRowValue_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        moveToRowValue(index);
    }
}

void
MainWindow::copyInsertToNewValue_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  etp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());

    switch (etp) {
    case Etype::eClass :
        addCopyClassInsert_triggered();
        break;
    case Etype::eClassDeclaration :
        addCopyClassDecInsert_triggered();
        break;
    case Etype::eStruct :
        addCopyStructInsert_triggered();
        break;
    case Etype::eStructDeclaration :
        addCopyStructDecInsert_triggered();
        break;
    case Etype::eEnum :
        addCopyEnumInsert_triggered();
        break;
    case Etype::eTypedef :
        addCopyTypedefInsert_triggered();
        break;
    case Etype::eLabel :
        addCopyLabelInsert_triggered();
        break;
    case Etype::ePublicLabel :
        addCopyPublicLabelInsert_triggered();
        break;
    case Etype::eProtectedLabel :
        addCopyProtectedLabelInsert_triggered();
        break;
    case Etype::ePrivateLabel :
        addCopyPrivateLabelInsert_triggered();
        break;
    case Etype::eBasicBlock :
        addCopyBasicBlockInsert_triggered();
        break;
    default :
        break;
    }
}

void
MainWindow::copyToNewValue_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  etp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());

    switch (etp) {
    case Etype::eClass :
        addCopyClassFollow_triggered();
        break;
    case Etype::eClassDeclaration :
        addCopyClassDecFollow_triggered();
        break;
    case Etype::eStruct :
        addCopyStructFollow_triggered();
        break;
    case Etype::eStructDeclaration :
        addCopyStructDecFollow_triggered();
        break;
    case Etype::eEnum :
        addCopyEnumFollow_triggered();
        break;
    case Etype::eTypedef :
        addCopyTypedefFollow_triggered();
        break;
    case Etype::eLabel :
        addCopyLabelFollow_triggered();
        break;
    case Etype::ePublicLabel :
        addCopyPublicLabelFollow_triggered();
        break;
    case Etype::eProtectedLabel :
        addCopyProtectedLabelFollow_triggered();
        break;
    case Etype::ePrivateLabel :
        addCopyPrivateLabelFollow_triggered();
        break;
    case Etype::eBasicBlock :
        addCopyBasicBlockFollow_triggered();
        break;
    default :
        break;
    }
}

void
MainWindow::addNewClassChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eClass, MyClass());
    }
}

void
MainWindow::addNewClassInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eClass, MyClass());
    }
}

void
MainWindow::addNewClassFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eClass, MyClass());
    }
}

void
MainWindow::addCopyClassInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eClass, *static_cast<MyClass *>(ptr));
    }
}

void
MainWindow::addCopyClassFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eClass, *static_cast<MyClass *>(ptr));
    }
}

void
MainWindow::addNewCtorsChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eConstructors, Constructors());
    }
}

void
MainWindow::addNewCtorsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eConstructors, Constructors());
    }
}

void
MainWindow::addNewCtorsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eConstructors, Constructors());
    }
}

void
MainWindow::addCopyCtorsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eConstructors, *static_cast<Constructors *>(ptr));
    }
}

void
MainWindow::addCopyCtorsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eConstructors, *static_cast<Constructors *>(ptr));
    }
}

void
MainWindow::addNewTplCtorsChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eTplConstructors, TplConstructors());
    }
}

void
MainWindow::addNewTplCtorsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eTplConstructors, TplConstructors());
    }
}

void
MainWindow::addNewTplCtorsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eTplConstructors, TplConstructors());
    }
}

void
MainWindow::addCopyTplCtorsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eTplConstructors, *static_cast<TplConstructors *>(ptr));
    }
}

void
MainWindow::addCopyTplCtorsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eTplConstructors, *static_cast<TplConstructors *>(ptr));
    }
}

void
MainWindow::addNewDefCtorFnChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eDefaultConstructorFn, DefaultConstructorFn());
    }
}

void
MainWindow::addNewDefCtorFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eDefaultConstructorFn, DefaultConstructorFn());
    }
}

void
MainWindow::addNewDefCtorFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eDefaultConstructorFn, DefaultConstructorFn());
    }
}

void
MainWindow::addCopyDefCtorFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eDefaultConstructorFn, *static_cast<DefaultConstructorFn *>(ptr));
    }
}

void
MainWindow::addCopyDefCtorFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eDefaultConstructorFn, *static_cast<DefaultConstructorFn *>(ptr));
    }
}

void
MainWindow::addNewCopyCtorFnChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eCopyConstructorFn, CopyConstructorFn());
    }
}

void
MainWindow::addNewCopyCtorFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eCopyConstructorFn, CopyConstructorFn());
    }
}

void
MainWindow::addNewCopyCtorFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eCopyConstructorFn, CopyConstructorFn());
    }
}

void
MainWindow::addCopyCopyCtorFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eCopyConstructorFn, *static_cast<CopyConstructorFn *>(ptr));
    }
}

void
MainWindow::addCopyCopyCtorFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eCopyConstructorFn, *static_cast<CopyConstructorFn *>(ptr));
    }
}

void
MainWindow::addNewMoveCtorFnChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eMoveConstructorFn, MoveConstructorFn());
    }
}

void
MainWindow::addNewMoveCtorFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eMoveConstructorFn, MoveConstructorFn());
    }
}

void
MainWindow::addNewMoveCtorFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eMoveConstructorFn, MoveConstructorFn());
    }
}

void
MainWindow::addCopyMoveCtorFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eMoveConstructorFn, *static_cast<MoveConstructorFn *>(ptr));
    }
}

void
MainWindow::addCopyMoveCtorFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eMoveConstructorFn, *static_cast<MoveConstructorFn *>(ptr));
    }
}

void
MainWindow::addNewDtorFnChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eDestructorFn, DestructorFn());
    }
}

void
MainWindow::addNewDtorFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eDestructorFn, DestructorFn());
    }
}

void
MainWindow::addNewDtorFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eDestructorFn, DestructorFn());
    }
}

void
MainWindow::addCopyDtorFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eDestructorFn, *static_cast<DestructorFn *>(ptr));
    }
}

void
MainWindow::addCopyDtorFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eDestructorFn, *static_cast<DestructorFn *>(ptr));
    }
}

void
MainWindow::addNewCopyOpEqFnChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        CopyOperatorEqFn  fn;
        insertChildValue(index, AddMethod::childAdd,
                Etype::eCopyOperatorEqFn, fn);
    }
}

void
MainWindow::addNewCopyOpEqFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        CopyOperatorEqFn  fn;
        insertValue(index, AddMethod::insert,
                Etype::eCopyOperatorEqFn, fn);
    }
}

void
MainWindow::addNewCopyOpEqFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        CopyOperatorEqFn  fn;
        insertValue(index, AddMethod::follow,
                Etype::eCopyOperatorEqFn, fn);
    }
}

void
MainWindow::addCopyCopyOpEqFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eCopyOperatorEqFn, *static_cast<CopyOperatorEqFn *>(ptr));
    }
}

void
MainWindow::addCopyCopyOpEqFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eCopyOperatorEqFn, *static_cast<CopyOperatorEqFn *>(ptr));
    }
}

void
MainWindow::addNewMoveOpEqFnChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eMoveOperatorEqFn, MoveOperatorEqFn());
    }
}

void
MainWindow::addNewMoveOpEqFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eMoveOperatorEqFn, MoveOperatorEqFn());
    }
}

void
MainWindow::addNewMoveOpEqFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(Qt::UserRole + 1).toInt());
    if (parentEtp != Etype::eClass)  return;

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eMoveOperatorEqFn, MoveOperatorEqFn());
    }
}

void
MainWindow::addCopyMoveOpEqFnInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eMoveOperatorEqFn, *static_cast<MoveOperatorEqFn *>(ptr));
    }
}

void
MainWindow::addCopyMoveOpEqFnFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eMoveOperatorEqFn, *static_cast<MoveOperatorEqFn *>(ptr));
    }
}

void
MainWindow::addNewClassDecChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eClassDeclaration, MyClassDec());
    }
}

void
MainWindow::addNewClassDecInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eClassDeclaration, MyClassDec());
    }
}

void
MainWindow::addNewClassDecFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eClassDeclaration, MyClassDec());
    }
}

void
MainWindow::addCopyClassDecInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eClassDeclaration, *static_cast<MyClassDec *>(ptr));
    }
}

void
MainWindow::addCopyClassDecFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eClassDeclaration, *static_cast<MyClassDec *>(ptr));
    }
}

void
MainWindow::addNewStructChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eStruct, MyStruct());
    }
}

void
MainWindow::addNewStructInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eStruct, MyStruct());
    }
}

void
MainWindow::addNewStructFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eStruct, MyStruct());
    }
}

void
MainWindow::addCopyStructInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eStruct, *static_cast<MyStruct *>(ptr));
    }
}

void
MainWindow::addCopyStructFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eStruct, *static_cast<MyStruct *>(ptr));
    }
}

void
MainWindow::addNewStructDecChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eStructDeclaration, MyStructDec());
    }
}

void
MainWindow::addNewStructDecInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eStructDeclaration, MyStructDec());
    }
}

void
MainWindow::addNewStructDecFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eStructDeclaration, MyStructDec());
    }
}

void
MainWindow::addCopyStructDecInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eStructDeclaration, *static_cast<MyStructDec *>(ptr));
    }
}

void
MainWindow::addCopyStructDecFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eStructDeclaration, *static_cast<MyStructDec *>(ptr));
    }
}

void
MainWindow::addNewEnumChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd, Etype::eEnum, MyEnum());
    }
}

void
MainWindow::addNewEnumInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert, Etype::eEnum, MyEnum());
    }
}

void
MainWindow::addNewEnumFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow, Etype::eEnum, MyEnum());
    }
}

void
MainWindow::addCopyEnumInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eEnum, *static_cast<MyEnum *>(ptr));
    }
}

void
MainWindow::addCopyEnumFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eEnum, *static_cast<MyEnum *>(ptr));
    }
}

void
MainWindow::addNewTypedefChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eTypedef, MyTypedef());
    }
}

void
MainWindow::addNewTypedefInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eTypedef, MyTypedef());
    }
}

void
MainWindow::addNewTypedefFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eTypedef, MyTypedef());
    }
}

void
MainWindow::addCopyTypedefInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eTypedef, *static_cast<MyTypedef *>(ptr));
    }
}

void
MainWindow::addCopyTypedefFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eTypedef, *static_cast<MyTypedef *>(ptr));
    }
}

void
MainWindow::addNewFnsChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eFunctions, Functions());
    }
}

void
MainWindow::addNewFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eFunctions, Functions());
    }
}

void
MainWindow::addNewFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eFunctions, Functions());
    }
}

void
MainWindow::addCopyFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eFunctions, *static_cast<Functions *>(ptr));
    }
}

void
MainWindow::addCopyFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eFunctions, *static_cast<Functions *>(ptr));
    }
}

void
MainWindow::addNewStaticFnsChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eStaticFunctions, StaticFunctions());
    }
}

void
MainWindow::addNewStaticFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eStaticFunctions, StaticFunctions());
    }
}

void
MainWindow::addNewStaticFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eStaticFunctions, StaticFunctions());
    }
}

void
MainWindow::addCopyStaticFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eStaticFunctions, *static_cast<StaticFunctions *>(ptr));
    }
}

void
MainWindow::addCopyStaticFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eStaticFunctions, *static_cast<StaticFunctions *>(ptr));
    }
}

void
MainWindow::addNewCoexFnsChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eConstexprFunctions, ConstexprFunctions());
    }
}

void
MainWindow::addNewCoexFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eConstexprFunctions, ConstexprFunctions());
    }
}

void
MainWindow::addNewCoexFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eConstexprFunctions, ConstexprFunctions());
    }
}

void
MainWindow::addCopyCoexFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eConstexprFunctions, *static_cast<ConstexprFunctions *>(ptr));
    }
}

void
MainWindow::addCopyCoexFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eConstexprFunctions, *static_cast<ConstexprFunctions *>(ptr));
    }
}

void
MainWindow::addNewTplFnsChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eTplFunctions, TplFunctions());
    }
}

void
MainWindow::addNewTplFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eTplFunctions, TplFunctions());
    }
}

void
MainWindow::addNewTplFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eTplFunctions, TplFunctions());
    }
}

void
MainWindow::addCopyTplFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eTplFunctions, *static_cast<TplFunctions *>(ptr));
    }
}

void
MainWindow::addCopyTplFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eTplFunctions, *static_cast<TplFunctions *>(ptr));
    }
}

void
MainWindow::addNewTplStaticFnsChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eTplStaticFunctions, TplStaticFunctions());
    }
}

void
MainWindow::addNewTplStaticFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eTplStaticFunctions, TplStaticFunctions());
    }
}

void
MainWindow::addNewTplStaticFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eTplStaticFunctions, TplStaticFunctions());
    }
}

void
MainWindow::addCopyTplStaticFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eTplStaticFunctions, *static_cast<TplStaticFunctions *>(ptr));
    }
}

void
MainWindow::addCopyTplStaticFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eTplStaticFunctions, *static_cast<TplStaticFunctions *>(ptr));
    }
}

void
MainWindow::addNewTplCoexFnsChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eTplConstexprFunctions, TplConstexprFunctions());
    }
}

void
MainWindow::addNewTplCoexFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eTplConstexprFunctions, TplConstexprFunctions());
    }
}

void
MainWindow::addNewTplCoexFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eTplConstexprFunctions, TplConstexprFunctions());
    }
}

void
MainWindow::addCopyTplCoexFnsInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert, Etype::eTplConstexprFunctions,
                *static_cast<TplConstexprFunctions *>(ptr));
    }
}

void
MainWindow::addCopyTplCoexFnsFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index,AddMethod::follow, Etype::eTplConstexprFunctions,
                *static_cast<TplConstexprFunctions *>(ptr));
    }
}

void
MainWindow::addNewFunctionChild_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertChildValue(index, AddMethod::childAdd,
                Etype::eFunction, Function());
    }
}

void
MainWindow::addNewFunctionInsertEnd_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);

    if (index.isValid()) {
        QStandardItem *  parentItem = selfItem->parent();
        QModelIndex const  parentIndex = m_mainTreeModel->indexFromItem(parentItem);
        insertChildValue(parentIndex, AddMethod::childAdd,
                Etype::eFunction, Function());
    }
}

void
MainWindow::addNewFunctionInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eFunction, Function());
    }
}

void
MainWindow::addNewFunctionFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eFunction, Function());
    }
}

void
MainWindow::addCopyFunctionInsertEnd_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        QStandardItem *  parentItem = selfItem->parent();
        QModelIndex const  parentIndex = m_mainTreeModel->indexFromItem(parentItem);
        insertChildValue(parentIndex, AddMethod::childAdd,
                Etype::eFunction, *static_cast<Function *>(ptr));
    }
}

void
MainWindow::addCopyFunctionInsert_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::insert,
                Etype::eFunction, *static_cast<Function *>(ptr));
    }
}

void
MainWindow::addCopyFunctionFollow_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    void *  ptr = selfItem->data(Qt::UserRole + 2).value<void *>();

    if (index.isValid()) {
        insertValue(index, AddMethod::follow,
                Etype::eFunction, *static_cast<Function *>(ptr));
    }
}

void
MainWindow::deleteRowFunction_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        deleteRowValueFunction(index);
    }
}

void
MainWindow::upRowFunction_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        upRowValueFunction(index);
    }
}

void
MainWindow::downRowFunction_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        downRowValueFunction(index);
    }
}

void
MainWindow::moveToRowFunction_triggered()
{
    QModelIndex const  index = m_mainTreeView->currentIndex();

    if (index.isValid()) {
        moveToRowValueFunction(index);
    }
}

void
MainWindow::init_obj()
{
    m_open = new QPushButton(tr("open"));
    m_new = new QPushButton(tr("new"));
    m_save = new QPushButton(tr("save"));
    m_quit = new QPushButton(tr("quit"));
    m_aboutQt = new QPushButton(tr("About Qt"));

    m_spvMain = new QSplitter;
    m_spvMain->setHandleWidth(1);

    m_mainTreeView = new QTreeView;
    m_mainTreeView->setWordWrap(true);
    m_mainTreeModel = new QStandardItemModel;
    m_mainTreeModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Project")));
    m_mainTreeView->setModel(m_mainTreeModel);

    m_spaceMenu = new QMenu;
    m_projectMenu = new QMenu;
    m_moduleMenu = new QMenu;
    m_classMenu = new QMenu;
    m_functionsMenu = new QMenu;
    m_fnMenu = new QMenu;
    m_otherMenu = new QMenu;
    m_defaultMenu = new QMenu;

    m_spaceWindow = new QAbstractScrollArea;
    m_wtBasicBlock = new WtBasicBlock;
    m_wtLabel = new WtLabel;
    m_wtPublicLabel = new WtPublicLabel;
    m_wtProtectedLabel = new WtProtectedLabel;
    m_wtPrivateLabel = new WtPrivateLabel;
    m_wtMyEnum = new WtMyEnum;
    m_wtProject = new WtProject;
    m_wtFn = new WtFn;
    m_wtTplFn = new WtTplFn;
    m_wtCtorFn = new WtCtorFn;
    m_wtTplCtorFn = new WtTplCtorFn;
    m_wtMyClassDec = new WtMyClassDec;
    m_wtMyStructDec = new WtMyStructDec;
    m_wtMyStruct = new WtMyStruct;
    m_wtAutoFnEdit = new WtAutoFnEdit;
}

void
MainWindow::connect_obj()
{
    connect(m_open, &QPushButton::clicked, this, &MainWindow::open_clicked);
    connect(m_new, &QPushButton::clicked, this, &MainWindow::new_clicked);
    connect(m_save, &QPushButton::clicked, this, &MainWindow::save_clicked);
    connect(m_quit, &QPushButton::clicked, this, &QWidget::close);
    connect(m_aboutQt, &QPushButton::clicked, this, &MainWindow::aboutQt_clicked);

    connect(m_mainTreeView, &QTreeView::clicked,
            this, &MainWindow::mainTreeView_clicked);

    m_mainTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_mainTreeView, &QTreeView::customContextMenuRequested,
            this, &MainWindow::mainTreeView_customCxtMenu);
    menuConnect();

}

void
MainWindow::display_obj()
{
    resize(1200, 690);

    QVBoxLayout *  lv = new QVBoxLayout(this);
    lv->setContentsMargins(5, 5, 5, 5);

    {
        QHBoxLayout *  tlhl = new QHBoxLayout;
        tlhl->setContentsMargins(0, 0, 0, 0);
        lv->addLayout(tlhl);
        tlhl->addWidget(m_open);
        tlhl->addWidget(m_new);
        tlhl->addWidget(m_save);
        tlhl->addWidget(m_quit);
        tlhl->addSpacing(18);
        tlhl->addWidget(new QLabel);
        tlhl->addWidget(m_aboutQt);

        tlhl->setStretch(0, 12);
        tlhl->setStretch(1, 12);
        tlhl->setStretch(2, 12);
        tlhl->setStretch(3, 12);
        tlhl->setStretch(4, 0);
        tlhl->setStretch(5, 40);
        tlhl->setStretch(6, 12);
    }
    {
        QHBoxLayout *  tlhl = new QHBoxLayout;
        tlhl->setContentsMargins(0, 0, 0, 0);
        lv->addLayout(tlhl);
        QFrame *  tlvline = new QFrame;
        tlhl->addWidget(tlvline);
        tlvline->setFrameStyle(QFrame::HLine | QFrame::Plain);
        tlvline->setLineWidth(1);
    }
    {
        QHBoxLayout *  lh1 = new QHBoxLayout;
        QHBoxLayout *  lh2 = new QHBoxLayout;
        lh1->setContentsMargins(0, 0, 0, 0);
        lh2->setContentsMargins(0, 0, 0, 0);
        lv->addLayout(lh1);
        QFrame *  tlvline = new QFrame;
        lh1->addWidget(tlvline);
        tlvline->setLayout(lh2);

        lh2->addWidget(m_spvMain);

        m_spvMain->addWidget(m_mainTreeView);
        m_spvMain->addWidget(m_spaceWindow);
        m_spvMain->setStretchFactor(0, 30);
        m_spvMain->setStretchFactor(1, 70);
    }
}

void
MainWindow::fillData()
{
    m_mainTreeModel->removeRows(0, m_mainTreeModel->rowCount());
    m_mainTreeModel->setHeaderData(0, Qt::Horizontal, "Project");
    QStandardItem *  itemRoot = m_mainTreeModel->invisibleRootItem();

    std::vector<std::shared_ptr<Project>> &  projList = m_obj.getProjectListRef();
    size_t const  projSize = projList.size();
    for (size_t  i = 0; i < projSize; ++i) {
        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(projList[i]->getTreeLabel()));
        setItemProperty(item, Etype::eProject, projList[i]);
        itemRoot->appendRow(item);

        fillProject(*projList[i], item);
    }
}

void
MainWindow::fillProject(Project &  project,
                        QStandardItem *  projectItem)
{
    std::vector<std::shared_ptr<Module>> &  moduleList = project.getModuleListRef();
    size_t const  moduleSize = moduleList.size();
    for (size_t  i = 0; i < moduleSize; ++i) {
        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(moduleList[i]->getTreeLabel()));
        setItemProperty(item, Etype::eModule, moduleList[i]);
        projectItem->appendRow(item);

        fillModule(*moduleList[i], item);
    }
}

void
MainWindow::fillModule(Module &  module,
                       QStandardItem *  moduleItem)
{
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  eList =
            module.getEObjectListRef();
    size_t const  eSize = eList.size();
    for (size_t  i = 0; i < eSize; ++i) {
        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(eList[i].second->getTreeLabel()));
        setItemProperty(item, eList[i].first, eList[i].second);
        moduleItem->appendRow(item);
        void *  modulePtr = moduleItem->data(Qt::UserRole + 2).value<void *>();

        if (eList[i].first == Etype::eClass) {
            std::shared_ptr<MyClass>  classPtr =
                    std::dynamic_pointer_cast<MyClass>(eList[i].second);
            classPtr->setParentModulePtr(static_cast<Module *>(modulePtr));
            fillClass(*classPtr, item);
        } else if (eList[i].first == Etype::eConstructors ||
                   eList[i].first == Etype::eTplConstructors ||
                   eList[i].first == Etype::eFunctions ||
                   eList[i].first == Etype::eStaticFunctions ||
                   eList[i].first == Etype::eConstexprFunctions ||
                   eList[i].first == Etype::eTplFunctions ||
                   eList[i].first == Etype::eTplStaticFunctions ||
                   eList[i].first == Etype::eTplConstexprFunctions ) {
            std::shared_ptr<Functions>  fnsPtr =
                    std::dynamic_pointer_cast<Functions>(eList[i].second);
            fillFunctions(*fnsPtr, item);
        }
    }
}

void
MainWindow::fillClass(MyClass &  myClass,
                      QStandardItem *  myClassItem)
{
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  eList =
            myClass.getEObjectRef();
    size_t const  eSize = eList.size();
    for (size_t  i = 0; i < eSize; ++i) {
        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(eList[i].second->getTreeLabel()));
        setItemProperty(item, eList[i].first, eList[i].second);
        myClassItem->appendRow(item);
        void *  classPtr = myClassItem->data(Qt::UserRole + 2).value<void *>();

        if (eList[i].first == Etype::eClass) {
            std::shared_ptr<MyClass>  classPtr =
                    std::dynamic_pointer_cast<MyClass>(eList[i].second);
            fillClass(*classPtr, item);
        } else if (eList[i].first == Etype::eConstructors ||
                   eList[i].first == Etype::eTplConstructors ||
                   eList[i].first == Etype::eFunctions ||
                   eList[i].first == Etype::eStaticFunctions ||
                   eList[i].first == Etype::eConstexprFunctions ||
                   eList[i].first == Etype::eTplFunctions ||
                   eList[i].first == Etype::eTplStaticFunctions ||
                   eList[i].first == Etype::eTplConstexprFunctions ) {
            std::shared_ptr<Functions>  fnsPtr =
                    std::dynamic_pointer_cast<Functions>(eList[i].second);
            fnsPtr->setParentClassPtr(static_cast<MyClass *>(classPtr));
            fillFunctions(*fnsPtr, item);
        }
    }
}

void
MainWindow::fillFunctions(Functions &  functions,
                          QStandardItem *  functionsItem)
{
    std::vector<std::shared_ptr<Function>> &  fnList = functions.getFunctionRef();
    size_t const  fnSize = fnList.size();
    for (size_t  i = 0; i < fnSize; ++i) {
        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(fnList[i]->getTreeLabel()));
        setItemProperty(item, Etype::eFunction, fnList[i]);
        functionsItem->appendRow(item);
    }
}

void
MainWindow::setItemProperty(QStandardItem *  item,
                            Etype const  etp,
                            std::shared_ptr<EObject>  objPtr)
{
    QVariant  valType = static_cast<int>(etp);
    item->setData(valType, Qt::UserRole + 1);

    QVariant  valPtr = QVariant::fromValue(static_cast<void *>(objPtr.get()));
    item->setData(valPtr, Qt::UserRole + 2);

    item->setFlags(Qt::NoItemFlags);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled |
                   Qt::ItemIsDropEnabled | Qt::ItemIsUserCheckable |
                   Qt::ItemIsEnabled );
}

void
MainWindow::getItemStack(std::vector<ItemStack> &  res,
                         QModelIndex const &  index)
{
    if (!index.isValid())  return;

    ItemStack  iStack;
    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    int const  selfRow = index.row();
    QModelIndex const  parentIndex = m_mainTreeModel->indexFromItem(parentItem);
    int const  parentRow = parentIndex.row();

    Etype const  selfEtp = static_cast<Etype>(selfItem->data(Qt::UserRole + 1).toInt());
    if (selfEtp == Etype::eProject) {
        return;
    }
    void *  selfPtr = selfItem->data(Qt::UserRole + 2).value<void *>();
    if (selfEtp == Etype::eModule) {
        iStack.setVecPtr(static_cast<Module *>(selfPtr)->getEObjectListPtr());
    } else if (selfEtp == Etype::eClass) {
        iStack.setVecPtr(static_cast<MyClass *>(selfPtr)->getEObjectPtr());
    } else if (selfEtp == Etype::eFunctions || selfEtp == Etype::eStaticFunctions ||
            selfEtp == Etype::eConstexprFunctions || selfEtp == Etype::eTplFunctions ||
            selfEtp == Etype::eTplStaticFunctions || selfEtp == Etype::eTplConstexprFunctions ||
            selfEtp == Etype::eConstructors || selfEtp == Etype::eTplConstructors ) {
        iStack.setVecPtr(static_cast<Functions *>(selfPtr)->getFunctionPtr());
    }
    iStack.setSelfItem(selfItem);
    iStack.setSelfIndex(index);
    iStack.setSelfRow(selfRow);
    iStack.setParentItem(parentItem);
    iStack.setParentIndex(parentIndex);
    iStack.setParentRow(parentRow);

    res.push_back(iStack);
    getItemStack(res, parentIndex);
}

void
MainWindow::insertProject(QModelIndex const &  index,
                          bool const  isFromMould,
                          Project const &  mouldVal /* = Project() */)
{
    QStandardItem *  rootItem = m_mainTreeModel->invisibleRootItem();

    std::shared_ptr<Project>  newProjPtr;
    if (isFromMould) {
        Project  proj = mouldVal;
        nameCheckProject(proj, rootItem);
        newProjPtr = std::make_shared<Project>(std::move(proj));
    } else {
        newProjPtr = std::make_shared<Project>();
    }
    auto  vec = m_obj.getEobjList();
    vec.push_back(newProjPtr);
    m_obj.setEobjList(vec);
    size_t const  size = vec.size();

    QStandardItem *  item = new QStandardItem(
            QString::fromStdString(newProjPtr->getTreeLabel()));
    setItemProperty(item, Etype::eProject, newProjPtr);
    rootItem->appendRow(item);
    if (isFromMould) {
        fillProject(*newProjPtr, item);
    }

    QModelIndex const  idx = index.sibling(static_cast<int>(size) - 1, 0);
    m_mainTreeView->setCurrentIndex(idx);
}

void
MainWindow::insertModule(QModelIndex const &  index,
                         MainWindow::AddMethod const  addmethod,
                         bool const  isFromMould,
                         Module const &  mouldVal /* = Module() */)
{
    if (!index.isValid())  return;

    QStandardItem *  selfItem = m_mainTreeModel->itemFromIndex(index);
    QStandardItem *  parentItem = selfItem->parent();
    int const  row = index.row();
    QModelIndex const  parentIndex = m_mainTreeModel->indexFromItem(parentItem);
    int const  parentRow = parentIndex.row();

    std::shared_ptr<Module>  newModulePtr;
    if (isFromMould) {
        Module  mdObj = mouldVal;
        nameCheckModule(mdObj, parentItem);
        newModulePtr = std::make_shared<Module>(std::move(mdObj));
    } else {
        newModulePtr = std::make_shared<Module>();
    }
    auto  vec = m_obj.getEobjList();
    switch (addmethod) {
    case AddMethod::insert :
        {
            auto  vecMod = vec[parentRow]->getEobjList();
            vecMod.insert(vecMod.begin() + row, newModulePtr);
            vec[parentRow]->setEobjList(vecMod);
            m_obj.setEobjList(vec);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newModulePtr->getTreeLabel()));
            setItemProperty(item, Etype::eModule, newModulePtr);
            parentItem->insertRow(row, item);
            if (isFromMould) {
                fillModule(*newModulePtr, item);
            }
        }
        break;
    case AddMethod::follow :
        {
            auto  vecMod = vec[parentRow]->getEobjList();
            vecMod.insert(vecMod.begin() + row + 1, newModulePtr);
            vec[parentRow]->setEobjList(vecMod);
            m_obj.setEobjList(vec);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newModulePtr->getTreeLabel()));
            setItemProperty(item, Etype::eModule, newModulePtr);
            parentItem->insertRow(row + 1, item);
            if (isFromMould) {
                fillModule(*newModulePtr, item);
            }
        }
        break;
    case AddMethod::childAdd :
        {
            auto  vecMod = vec[row]->getEobjList();
            vecMod.push_back(newModulePtr);
            vec[row]->setEobjList(vecMod);
            m_obj.setEobjList(vec);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newModulePtr->getTreeLabel()));
            setItemProperty(item, Etype::eModule, newModulePtr);
            selfItem->appendRow(item);
            if (isFromMould) {
                fillModule(*newModulePtr, item);
            }

            if (!m_mainTreeView->isExpanded(index)) {
                m_mainTreeView->expand(index);
            }
        }
        break;
    default :
        break;
    }
}

void
MainWindow::deleteRowValue(QModelIndex const &  index)
{
    if (!index.isValid())  return;
    std::vector<ItemStack>  vecItemStack;
    getItemStack(vecItemStack, index);

    void *  ptrTmp = vecItemStack[1].getVecPtr();
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
            parentVec = static_cast<std::vector<std::pair<Etype,
            std::shared_ptr<EObject>>> *>(ptrTmp);
    int const  selfRow = vecItemStack[0].getSelfRow();
    parentVec->erase(parentVec->begin() + selfRow);

    QStandardItem *  parentItem = vecItemStack[0].getParentItem();
    parentItem->removeRow(selfRow);
}

void
MainWindow::deleteRowValueFunction(QModelIndex const &  index)
{
    if (!index.isValid())  return;
    std::vector<ItemStack>  vecItemStack;
    getItemStack(vecItemStack, index);

    void *  ptrTmp = vecItemStack[1].getVecPtr();
    std::vector<std::shared_ptr<Function>> *  parentVec =
            static_cast<std::vector<std::shared_ptr<Function>> *>(ptrTmp);
    int const  selfRow = vecItemStack[0].getSelfRow();
    parentVec->erase(parentVec->begin() + selfRow);

    QStandardItem *  parentItem = vecItemStack[0].getParentItem();
    parentItem->removeRow(selfRow);
}

void
MainWindow::upRowValue(QModelIndex const &  index)
{
    if (!index.isValid())  return;
    std::vector<ItemStack>  vecItemStack;
    getItemStack(vecItemStack, index);

    void *  ptrTmp = vecItemStack[1].getVecPtr();
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
            parentVec = static_cast<std::vector<std::pair<Etype,
            std::shared_ptr<EObject>>> *>(ptrTmp);
    int const  selfRow = vecItemStack[0].getSelfRow();
    if (selfRow == 0)  return;
    std::swap((*parentVec)[selfRow], (*parentVec)[selfRow - 1]);

    QStandardItem *  parentItem = vecItemStack[0].getParentItem();
    QModelIndex  zeroIdx = index.sibling(selfRow, 0);
    bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
    auto const  item = parentItem->takeRow(selfRow);
    parentItem->insertRow(selfRow - 1, item);
    zeroIdx = index.sibling(selfRow - 1, 0);
    if (isExpanded) {
        m_mainTreeView->expand(zeroIdx);
    }
    QModelIndex const  idx = index.sibling(selfRow - 1, 0);
    m_mainTreeView->setCurrentIndex(idx);
}

void
MainWindow::upRowValueFunction(QModelIndex const &  index)
{
    if (!index.isValid())  return;
    std::vector<ItemStack>  vecItemStack;
    getItemStack(vecItemStack, index);

    void *  ptrTmp = vecItemStack[1].getVecPtr();
    std::vector<std::shared_ptr<Function>> *  parentVec =
            static_cast<std::vector<std::shared_ptr<Function>> *>(ptrTmp);
    int const  selfRow = vecItemStack[0].getSelfRow();
    if (selfRow == 0)  return;
    std::swap((*parentVec)[selfRow], (*parentVec)[selfRow - 1]);

    QStandardItem *  parentItem = vecItemStack[0].getParentItem();
    QModelIndex  zeroIdx = index.sibling(selfRow, 0);
    bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
    auto const  item = parentItem->takeRow(selfRow);
    parentItem->insertRow(selfRow - 1, item);
    zeroIdx = index.sibling(selfRow - 1, 0);
    if (isExpanded) {
        m_mainTreeView->expand(zeroIdx);
    }
    QModelIndex const  idx = index.sibling(selfRow - 1, 0);
    m_mainTreeView->setCurrentIndex(idx);
}

void
MainWindow::downRowValue(QModelIndex const &  index)
{
    if (!index.isValid())  return;
    std::vector<ItemStack>  vecItemStack;
    getItemStack(vecItemStack, index);

    void *  ptrTmp = vecItemStack[1].getVecPtr();
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
            parentVec = static_cast<std::vector<std::pair<Etype,
            std::shared_ptr<EObject>>> *>(ptrTmp);
    int const  selfRow = vecItemStack[0].getSelfRow();
    QStandardItem *  parentItem = vecItemStack[0].getParentItem();
    int const  count = parentItem->rowCount();
    if (count > 1 && selfRow != count - 1) {
        std::swap((*parentVec)[selfRow], (*parentVec)[selfRow + 1]);

        QModelIndex  zeroIdx = index.sibling(selfRow + 1, 0);
        bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
        auto const  item = parentItem->takeRow(selfRow + 1);
        parentItem->insertRow(selfRow, item);
        zeroIdx = index.sibling(selfRow, 0);
        if (isExpanded) {
            m_mainTreeView->expand(zeroIdx);
        }
        QModelIndex const  idx = index.sibling(selfRow + 1, 0);
        m_mainTreeView->setCurrentIndex(idx);
    }
}

void
MainWindow::downRowValueFunction(QModelIndex const &  index)
{
    if (!index.isValid())  return;
    std::vector<ItemStack>  vecItemStack;
    getItemStack(vecItemStack, index);

    void *  ptrTmp = vecItemStack[1].getVecPtr();
    std::vector<std::shared_ptr<Function>> *  parentVec =
            static_cast<std::vector<std::shared_ptr<Function>> *>(ptrTmp);
    int const  selfRow = vecItemStack[0].getSelfRow();
    QStandardItem *  parentItem = vecItemStack[0].getParentItem();
    int const  count = parentItem->rowCount();
    if (count > 1 && selfRow != count - 1) {
        std::swap((*parentVec)[selfRow], (*parentVec)[selfRow + 1]);

        QModelIndex  zeroIdx = index.sibling(selfRow + 1, 0);
        bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
        auto const  item = parentItem->takeRow(selfRow + 1);
        parentItem->insertRow(selfRow, item);
        zeroIdx = index.sibling(selfRow, 0);
        if (isExpanded) {
            m_mainTreeView->expand(zeroIdx);
        }
        QModelIndex const  idx = index.sibling(selfRow + 1, 0);
        m_mainTreeView->setCurrentIndex(idx);
    }
}

void
MainWindow::moveToRowValue(QModelIndex const &  index)
{
    if (!index.isValid())  return;
    std::vector<ItemStack>  vecItemStack;
    getItemStack(vecItemStack, index);

    void *  ptrTmp = vecItemStack[1].getVecPtr();
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
            parentVec = static_cast<std::vector<std::pair<Etype,
            std::shared_ptr<EObject>>> *>(ptrTmp);
    size_t  currRow = vecItemStack[0].getSelfRow();
    QStandardItem *  parentItem = vecItemStack[0].getParentItem();
    int const  count = parentItem->rowCount();
    if (count > 1) {
        bool  ok = false;
        size_t  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (!ok)  return;
        if (!xu::moveVec_0(*parentVec, currRow, movetoRow)) {
            return;
        }

        QModelIndex  zeroIdx = index.sibling(static_cast<int>(currRow), 0);
        bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
        auto const  item = parentItem->takeRow(static_cast<int>(currRow));
        parentItem->insertRow(static_cast<int>(movetoRow), item);
        zeroIdx = index.sibling(static_cast<int>(movetoRow), 0);
        if (isExpanded) {
            m_mainTreeView->expand(zeroIdx);
        }
        QModelIndex const  idx = index.sibling(static_cast<int>(movetoRow), 0);
        m_mainTreeView->setCurrentIndex(idx);
    }
}

void
MainWindow::moveToRowValueFunction(QModelIndex const &  index)
{
    if (!index.isValid())  return;
    std::vector<ItemStack>  vecItemStack;
    getItemStack(vecItemStack, index);

    void *  ptrTmp = vecItemStack[1].getVecPtr();
    std::vector<std::shared_ptr<Function>> *  parentVec =
            static_cast<std::vector<std::shared_ptr<Function>> *>(ptrTmp);
    size_t  currRow = vecItemStack[0].getSelfRow();
    QStandardItem *  parentItem = vecItemStack[0].getParentItem();
    int const  count = parentItem->rowCount();
    if (count > 1) {
        bool  ok = false;
        size_t  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (!ok)  return;
        if (!xu::moveVec_0(*parentVec, currRow, movetoRow)) {
            return;
        }

        QModelIndex  zeroIdx = index.sibling(static_cast<int>(currRow), 0);
        bool const  isExpanded = m_mainTreeView->isExpanded(zeroIdx);
        auto const  item = parentItem->takeRow(static_cast<int>(currRow));
        parentItem->insertRow(static_cast<int>(movetoRow), item);
        zeroIdx = index.sibling(static_cast<int>(movetoRow), 0);
        if (isExpanded) {
            m_mainTreeView->expand(zeroIdx);
        }
        QModelIndex const  idx = index.sibling(static_cast<int>(movetoRow), 0);
        m_mainTreeView->setCurrentIndex(idx);
    }
}

void
MainWindow::nameCheckProject(Project &  objVal,
                             QStandardItem *  parentItem)
{
    std::vector<std::string>  vecName;
    int const  count = parentItem->rowCount();
    for (int  i = 0; i < count; ++i) {
         QStandardItem *  chItem = parentItem->child(i);
         Etype const  etp = static_cast<Etype>(chItem->data(Qt::UserRole + 1).toInt());
         void *  ptr = chItem->data(Qt::UserRole + 2).value<void *>();
         if (etp == Etype::eProject) {
             vecName.push_back(static_cast<Project *>(ptr)->getProjectName());
         }
    }

    std::string const  oldName = objVal.getProjectName();
    std::string const  baseNewName = oldName + "_copy";
    std::string  newName;
    size_t  nameIdx = 0;
    while (true) {
        ++nameIdx;
        newName = baseNewName + std::to_string(nameIdx);
        auto  itor = std::find(vecName.begin(), vecName.end(), newName);
        if (itor == vecName.end()) {
            break;
        }
    }
    objVal.setProjectName(newName);
}

void
MainWindow::nameCheckModule(Module &  objVal,
                            QStandardItem *  parentItem)
{
    std::vector<std::string>  vecName;
    int const  count = parentItem->rowCount();
    for (int  i = 0; i < count; ++i) {
         QStandardItem *  chItem = parentItem->child(i);
         Etype const  etp = static_cast<Etype>(chItem->data(Qt::UserRole + 1).toInt());
         void *  ptr = chItem->data(Qt::UserRole + 2).value<void *>();
         if (etp == Etype::eModule) {
             vecName.push_back(static_cast<Module *>(ptr)->getFilename());
         }
    }

    std::string const  oldName = objVal.getFilename();
    std::string const  baseNewName = oldName + "_copy";
    std::string  newName;
    size_t  nameIdx = 0;
    while (true) {
        ++nameIdx;
        newName = baseNewName + std::to_string(nameIdx);
        auto  itor = std::find(vecName.begin(), vecName.end(), newName);
        if (itor == vecName.end()) {
            break;
        }
    }
    objVal.setFilename(newName);
}

void
MainWindow::nameCheckClass(MyClass &  objVal,
                           QStandardItem *  parentItem)
{
    std::vector<std::string>  vecName;
    int const  count = parentItem->rowCount();
    for (int  i = 0; i < count; ++i) {
         QStandardItem *  chItem = parentItem->child(i);
         Etype const  etp = static_cast<Etype>(chItem->data(Qt::UserRole + 1).toInt());
         void *  ptr = chItem->data(Qt::UserRole + 2).value<void *>();
         if (etp == Etype::eClass) {
             vecName.push_back(static_cast<MyClass *>(ptr)->getClassName());
         }
    }

    std::string const  oldName = objVal.getClassName();
    std::string const  baseNewName = oldName + "_";
    std::string  newName;
    size_t  nameIdx = 0;
    while (true) {
        ++nameIdx;
        newName = baseNewName + std::to_string(nameIdx);
        auto  itor = std::find(vecName.begin(), vecName.end(), newName);
        if (itor == vecName.end()) {
            break;
        }
    }
    objVal.setClassName(newName);
}

void
MainWindow::nameCheckStruct(MyStruct &  objVal,
                            QStandardItem *  parentItem)
{
    std::vector<std::string>  vecName;
    int const  count = parentItem->rowCount();
    for (int  i = 0; i < count; ++i) {
         QStandardItem *  chItem = parentItem->child(i);
         Etype const  etp = static_cast<Etype>(chItem->data(Qt::UserRole + 1).toInt());
         void *  ptr = chItem->data(Qt::UserRole + 2).value<void *>();
         if (etp == Etype::eStruct) {
             vecName.push_back(static_cast<MyStruct *>(ptr)->getName());
         }
    }

    std::string const  oldName = objVal.getName();
    std::string const  baseNewName = oldName + "_";
    std::string  newName;
    size_t  nameIdx = 0;
    while (true) {
        ++nameIdx;
        newName = baseNewName + std::to_string(nameIdx);
        auto  itor = std::find(vecName.begin(), vecName.end(), newName);
        if (itor == vecName.end()) {
            break;
        }
    }
    objVal.setName(newName);
}

void
MainWindow::nameCheckEnum(MyEnum &  objVal,
                          QStandardItem *  parentItem)
{
    std::vector<std::string>  vecName;
    int const  count = parentItem->rowCount();
    for (int  i = 0; i < count; ++i) {
         QStandardItem *  chItem = parentItem->child(i);
         Etype const  etp = static_cast<Etype>(chItem->data(Qt::UserRole + 1).toInt());
         void *  ptr = chItem->data(Qt::UserRole + 2).value<void *>();
         if (etp == Etype::eEnum) {
             vecName.push_back(static_cast<MyEnum *>(ptr)->getName());
         }
    }

    std::string const  oldName = objVal.getName();
    std::string const  baseNewName = oldName + "_";
    std::string  newName;
    size_t  nameIdx = 0;
    while (true) {
        ++nameIdx;
        newName = baseNewName + std::to_string(nameIdx);
        auto  itor = std::find(vecName.begin(), vecName.end(), newName);
        if (itor == vecName.end()) {
            break;
        }
    }
    objVal.setName(newName);
}

void
MainWindow::nameCheckFunction(Function &  objVal,
                              QStandardItem *  parentItem)
{
    std::vector<std::string>  vecName;
    int const  count = parentItem->rowCount();
    for (int  i = 0; i < count; ++i) {
         QStandardItem *  chItem = parentItem->child(i);
         Etype const  etp = static_cast<Etype>(chItem->data(Qt::UserRole + 1).toInt());
         void *  ptr = chItem->data(Qt::UserRole + 2).value<void *>();
         if (etp == Etype::eFunction) {
             vecName.push_back(static_cast<Function *>(ptr)->getFunctionName());
         }
    }

    std::string const  oldName = objVal.getFunctionName();
    std::string const  baseNewName = oldName + "_";
    std::string  newName;
    size_t  nameIdx = 0;
    while (true) {
        ++nameIdx;
        newName = baseNewName + std::to_string(nameIdx);
        auto  itor = std::find(vecName.begin(), vecName.end(), newName);
        if (itor == vecName.end()) {
            break;
        }
    }
    objVal.setFunctionName(newName);
}

}
