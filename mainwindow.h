#pragma once

#ifndef XU_MAINWINDOW_H_
#define XU_MAINWINDOW_H_

#include <QMainWindow>
#include <QWidget>
#include <QAbstractScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QSplitter>
#include <QTreeView>
#include <QStandardItemModel>
#include <QMenu>
#include "manager.h"
#include "wtbasicblock.h"
#include "wtlabel.h"
#include "wtpubliclabel.h"
#include "wtprotectedlabel.h"
#include "wtprivatelabel.h"
#include "wtmyenum.h"
#include "wtproject.h"
#include "eobject.h"
#include "itemstack.h"
#include "function.h"
#include "wtfn.h"
#include "wttplfn.h"
#include "wtctorfn.h"
#include "wttplctorfn.h"
#include "wtmyclassdec.h"
#include "wtmystructdec.h"
#include "wtmystruct.h"
#include "wtautofnedit.h"
#include "wtmyclass.h"

namespace xu {

class MainWindow;

class MyClass;
class Functions;

class MainWindow : public QWidget
{

    Q_OBJECT

public:

    enum class AddMethod {
        insert,
        follow,
        childAdd,
        childInsert
    };

    MainWindow(QWidget *  parent = nullptr);
    virtual ~MainWindow() noexcept;

    void  open_clicked();
    void  new_clicked();
    void  save_clicked();
    void  aboutQt_clicked();
    void  mainTreeView_clicked(QModelIndex const &  index);
    void  mainTreeView_customCxtMenu(QPoint const &  pos);
    void  menuConnect();
    void  addProject_triggered();
    void  copyProject_triggered();
    void  deleteProject_triggered();
    void  upProject_triggered();
    void  downProject_triggered();
    void  moveToRowProject_triggered();
    void  addModuleProject_triggered();
    void  addModule_triggered();
    void  insertNewModule_triggered();
    void  copyModuleToNew_triggered();
    void  deleteModule_triggered();
    void  upModule_triggered();
    void  downModule_triggered();
    void  moveToRowModule_triggered();
    void  addNewBasicBlockChild_triggered();
    void  addNewBasicBlockInsert_triggered();
    void  addNewBasicBlockFollow_triggered();
    void  addCopyBasicBlockInsert_triggered();
    void  addCopyBasicBlockFollow_triggered();
    void  addNewLabelChild_triggered();
    void  addNewLabelInsert_triggered();
    void  addNewLabelFollow_triggered();
    void  addCopyLabelInsert_triggered();
    void  addCopyLabelFollow_triggered();
    void  addNewPublicLabelChild_triggered();
    void  addNewPublicLabelInsert_triggered();
    void  addNewPublicLabelFollow_triggered();
    void  addCopyPublicLabelInsert_triggered();
    void  addCopyPublicLabelFollow_triggered();
    void  addNewProtectedLabelChild_triggered();
    void  addNewProtectedLabelInsert_triggered();
    void  addNewProtectedLabelFollow_triggered();
    void  addCopyProtectedLabelInsert_triggered();
    void  addCopyProtectedLabelFollow_triggered();
    void  addNewPrivateLabelChild_triggered();
    void  addNewPrivateLabelInsert_triggered();
    void  addNewPrivateLabelFollow_triggered();
    void  addCopyPrivateLabelInsert_triggered();
    void  addCopyPrivateLabelFollow_triggered();
    void  deleteRowValue_triggered();
    void  upRowValue_triggered();
    void  downRowValue_triggered();
    void  moveToRowValue_triggered();
    void  copyInsertToNewValue_triggered();
    void  copyToNewValue_triggered();
    void  addNewClassChild_triggered();
    void  addNewClassInsert_triggered();
    void  addNewClassFollow_triggered();
    void  addCopyClassInsert_triggered();
    void  addCopyClassFollow_triggered();
    void  addNewCtorsChild_triggered();
    void  addNewCtorsInsert_triggered();
    void  addNewCtorsFollow_triggered();
    void  addCopyCtorsInsert_triggered();
    void  addCopyCtorsFollow_triggered();
    void  addNewTplCtorsChild_triggered();
    void  addNewTplCtorsInsert_triggered();
    void  addNewTplCtorsFollow_triggered();
    void  addCopyTplCtorsInsert_triggered();
    void  addCopyTplCtorsFollow_triggered();
    void  addNewDefCtorFnChild_triggered();
    void  addNewDefCtorFnInsert_triggered();
    void  addNewDefCtorFnFollow_triggered();
    void  addCopyDefCtorFnInsert_triggered();
    void  addCopyDefCtorFnFollow_triggered();
    void  addNewCopyCtorFnChild_triggered();
    void  addNewCopyCtorFnInsert_triggered();
    void  addNewCopyCtorFnFollow_triggered();
    void  addCopyCopyCtorFnInsert_triggered();
    void  addCopyCopyCtorFnFollow_triggered();
    void  addNewMoveCtorFnChild_triggered();
    void  addNewMoveCtorFnInsert_triggered();
    void  addNewMoveCtorFnFollow_triggered();
    void  addCopyMoveCtorFnInsert_triggered();
    void  addCopyMoveCtorFnFollow_triggered();
    void  addNewDtorFnChild_triggered();
    void  addNewDtorFnInsert_triggered();
    void  addNewDtorFnFollow_triggered();
    void  addCopyDtorFnInsert_triggered();
    void  addCopyDtorFnFollow_triggered();
    void  addNewCopyOpEqFnChild_triggered();
    void  addNewCopyOpEqFnInsert_triggered();
    void  addNewCopyOpEqFnFollow_triggered();
    void  addCopyCopyOpEqFnInsert_triggered();
    void  addCopyCopyOpEqFnFollow_triggered();
    void  addNewMoveOpEqFnChild_triggered();
    void  addNewMoveOpEqFnInsert_triggered();
    void  addNewMoveOpEqFnFollow_triggered();
    void  addCopyMoveOpEqFnInsert_triggered();
    void  addCopyMoveOpEqFnFollow_triggered();
    void  addNewClassDecChild_triggered();
    void  addNewClassDecInsert_triggered();
    void  addNewClassDecFollow_triggered();
    void  addCopyClassDecInsert_triggered();
    void  addCopyClassDecFollow_triggered();
    void  addNewStructChild_triggered();
    void  addNewStructInsert_triggered();
    void  addNewStructFollow_triggered();
    void  addCopyStructInsert_triggered();
    void  addCopyStructFollow_triggered();
    void  addNewStructDecChild_triggered();
    void  addNewStructDecInsert_triggered();
    void  addNewStructDecFollow_triggered();
    void  addCopyStructDecInsert_triggered();
    void  addCopyStructDecFollow_triggered();
    void  addNewEnumChild_triggered();
    void  addNewEnumInsert_triggered();
    void  addNewEnumFollow_triggered();
    void  addCopyEnumInsert_triggered();
    void  addCopyEnumFollow_triggered();
    void  addNewTypedefChild_triggered();
    void  addNewTypedefInsert_triggered();
    void  addNewTypedefFollow_triggered();
    void  addCopyTypedefInsert_triggered();
    void  addCopyTypedefFollow_triggered();
    void  addNewFnsChild_triggered();
    void  addNewFnsInsert_triggered();
    void  addNewFnsFollow_triggered();
    void  addCopyFnsInsert_triggered();
    void  addCopyFnsFollow_triggered();
    void  addNewStaticFnsChild_triggered();
    void  addNewStaticFnsInsert_triggered();
    void  addNewStaticFnsFollow_triggered();
    void  addCopyStaticFnsInsert_triggered();
    void  addCopyStaticFnsFollow_triggered();
    void  addNewCoexFnsChild_triggered();
    void  addNewCoexFnsInsert_triggered();
    void  addNewCoexFnsFollow_triggered();
    void  addCopyCoexFnsInsert_triggered();
    void  addCopyCoexFnsFollow_triggered();
    void  addNewTplFnsChild_triggered();
    void  addNewTplFnsInsert_triggered();
    void  addNewTplFnsFollow_triggered();
    void  addCopyTplFnsInsert_triggered();
    void  addCopyTplFnsFollow_triggered();
    void  addNewTplStaticFnsChild_triggered();
    void  addNewTplStaticFnsInsert_triggered();
    void  addNewTplStaticFnsFollow_triggered();
    void  addCopyTplStaticFnsInsert_triggered();
    void  addCopyTplStaticFnsFollow_triggered();
    void  addNewTplCoexFnsChild_triggered();
    void  addNewTplCoexFnsInsert_triggered();
    void  addNewTplCoexFnsFollow_triggered();
    void  addCopyTplCoexFnsInsert_triggered();
    void  addCopyTplCoexFnsFollow_triggered();
    void  addNewFunctionChild_triggered();
    void  addNewFunctionInsertEnd_triggered();
    void  addNewFunctionInsert_triggered();
    void  addNewFunctionFollow_triggered();
    void  addCopyFunctionInsertEnd_triggered();
    void  addCopyFunctionInsert_triggered();
    void  addCopyFunctionFollow_triggered();
    void  deleteRowFunction_triggered();
    void  upRowFunction_triggered();
    void  downRowFunction_triggered();
    void  moveToRowFunction_triggered();

    template <typename T>
    void  insertValue(QModelIndex const &  index, AddMethod const  addmethod, Etype const  newEtp, T const &  mouldVal);
    template <typename T>
    void  insertChildValue(QModelIndex const &  index, AddMethod const  addmethod, Etype const  newEtp, T const &  mouldVal, int const  insertRow = 0);

protected:

private:

    void  init_obj();
    void  connect_obj();
    void  display_obj();
    void  fillData();
    void  fillProject(Project &  project, QStandardItem *  projectItem);
    void  fillModule(Module &  module, QStandardItem *  moduleItem);
    void  fillClass(MyClass &  myClass, QStandardItem *  myClassItem);
    void  fillFunctions(Functions &  functions, QStandardItem *  functionsItem);
    void  insertProject(QModelIndex const &  index, bool const  isFromMould, Project const &  mouldVal = Project());
    void  insertModule(QModelIndex const &  index, AddMethod const  addmethod, bool const  isFromMould, Module const &  mouldVal = Module());
    void  deleteRowValue(QModelIndex const &  index);
    void  deleteRowValueFunction(QModelIndex const &  index);
    void  upRowValue(QModelIndex const &  index);
    void  upRowValueFunction(QModelIndex const &  index);
    void  downRowValue(QModelIndex const &  index);
    void  downRowValueFunction(QModelIndex const &  index);
    void  moveToRowValue(QModelIndex const &  index);
    void  moveToRowValueFunction(QModelIndex const &  index);
    void  nameCheckProject(Project &  objVal, QStandardItem *  parentItem);
    void  nameCheckModule(Module &  objVal, QStandardItem *  parentItem);
    void  nameCheckClass(MyClass &  objVal, QStandardItem *  parentItem);
    void  nameCheckStruct(MyStruct &  objVal, QStandardItem *  parentItem);
    void  nameCheckEnum(MyEnum &  objVal, QStandardItem *  parentItem);
    void  nameCheckFunction(Function &  objVal, QStandardItem *  parentItem);
    void  getItemStack(std::vector<ItemStack> &  res, QModelIndex const &  index);

    Manager         m_obj;
    QPushButton *   m_open;
    QPushButton *   m_new;
    QPushButton *   m_save;
    QPushButton *   m_quit;
    QPushButton *   m_aboutQt;
    QSplitter *     m_spvMain;
    QWidget *       m_currIgnore;
    QTreeView *     m_mainTreeView;
    QStandardItemModel *    m_mainTreeModel;
    QMenu *         m_spaceMenu;
    QMenu *         m_projectMenu;
    QMenu *         m_moduleMenu;
    QMenu *         m_classMenu;
    QMenu *         m_functionsMenu;
    QMenu *         m_fnMenu;
    QMenu *         m_otherMenu;
    QMenu *         m_defaultMenu;
    QAbstractScrollArea *   m_spaceWindow;
    WtBasicBlock *      m_wtBasicBlock;
    WtLabel *       m_wtLabel;
    WtPublicLabel *     m_wtPublicLabel;
    WtProtectedLabel *      m_wtProtectedLabel;
    WtPrivateLabel *    m_wtPrivateLabel;
    WtMyEnum *      m_wtMyEnum;
    WtProject *     m_wtProject;
    WtFn *          m_wtFn;
    WtTplFn *       m_wtTplFn;
    WtCtorFn *      m_wtCtorFn;
    WtTplCtorFn *   m_wtTplCtorFn;
    WtMyClassDec *      m_wtMyClassDec;
    WtMyStructDec *     m_wtMyStructDec;
    WtMyStruct *    m_wtMyStruct;
    WtAutoFnEdit *      m_wtAutoFnEdit;
    WtMyClass *     m_wtMyClass;
};

template <typename T> inline
void
MainWindow::insertValue(QModelIndex const &  index,
                        MainWindow::AddMethod const  addmethod,
                        Etype const  newEtp,
                        T const &  mouldVal)
{
    if (!index.isValid())  return;
    std::vector<ItemStack>  vecItemStack;
    getItemStack(vecItemStack, index);

    QStandardItem *  selfItem = vecItemStack[0].getSelfItem();
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(
            Qt::UserRole + 1).toInt());
    void *  selfPtr = selfItem->data(Qt::UserRole + 2).value<void *>();

    QStandardItem *  parentItem = vecItemStack[0].getParentItem();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(
            Qt::UserRole + 1).toInt());
    void *  parentPtr = parentItem->data(Qt::UserRole + 2).value<void *>();

    std::shared_ptr<T>  newMePtr = std::make_shared<T>(mouldVal);
    std::pair<Etype, std::shared_ptr<EObject>>  newData;
    newData.first = newEtp;
    newData.second = newMePtr;

    {
        void *  ptrTmp = vecItemStack[1].getVecPtr();
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
                parentVec = static_cast<std::vector<std::pair<Etype,
                std::shared_ptr<EObject>>> *>(ptrTmp);

        switch (newEtp) {
        case Etype::eDefaultConstructorFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eDefaultConstructorFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        case Etype::eCopyConstructorFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eCopyConstructorFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        case Etype::eMoveConstructorFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eMoveConstructorFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        case Etype::eDestructorFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eDestructorFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        case Etype::eCopyOperatorEqFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eCopyOperatorEqFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        case Etype::eMoveOperatorEqFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eMoveOperatorEqFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        default :
            break;
        }
    }

    switch (newEtp) {
    case Etype::eClass :
        nameCheckClass(*std::dynamic_pointer_cast<MyClass>(newMePtr), parentItem);
        if (parentEtp == Etype::eModule) {
            std::dynamic_pointer_cast<MyClass>(newMePtr)->setParentModulePtr(
                    static_cast<Module *>(parentPtr));
        }
        if (std::dynamic_pointer_cast<MyClass>(newMePtr)->hasEqFunction()) {
            std::dynamic_pointer_cast<MyClass>(newMePtr)->setEqFunction(false);
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                    std::dynamic_pointer_cast<MyClass>(newMePtr)->getEObjectPtr();
            auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eVirtualEqFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itF != objVec->end()) {
                objVec->erase(itF);
            }
        }
        if (std::dynamic_pointer_cast<MyClass>(newMePtr)->hasLessFunction()) {
            std::dynamic_pointer_cast<MyClass>(newMePtr)->setLessFunction(false);
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                    std::dynamic_pointer_cast<MyClass>(newMePtr)->getEObjectPtr();
            auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eVirtualLessFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itF != objVec->end()) {
                objVec->erase(itF);
            }
        }
        if (std::dynamic_pointer_cast<MyClass>(newMePtr)->hasSwapFunction()) {
            std::dynamic_pointer_cast<MyClass>(newMePtr)->setSwapFunction(false);
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                    std::dynamic_pointer_cast<MyClass>(newMePtr)->getEObjectPtr();
            auto  itFIn = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eInSwapFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFIn != objVec->end()) {
                objVec->erase(itFIn);
            }
            auto  itFVir = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eVirtualExchangeFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFVir != objVec->end()) {
                objVec->erase(itFVir);
            }
        }
        if (std::dynamic_pointer_cast<MyClass>(newMePtr)->hasToStringFunction()) {
            std::dynamic_pointer_cast<MyClass>(newMePtr)->setToStringFunction(false);
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                    std::dynamic_pointer_cast<MyClass>(newMePtr)->getEObjectPtr();
            auto  itFToString = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eToStringFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFToString != objVec->end()) {
                objVec->erase(itFToString);
            }
            auto  itFVirS = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eVirtualSerializeFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFVirS != objVec->end()) {
                objVec->erase(itFVirS);
            }
            auto  itFFromString = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eInFromStringFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFFromString != objVec->end()) {
                objVec->erase(itFFromString);
            }
            auto  itFDes = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eDeserializeFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFDes != objVec->end()) {
                objVec->erase(itFDes);
            }
        }
        break;
    case Etype::eStruct :
        nameCheckStruct(*std::dynamic_pointer_cast<MyStruct>(newMePtr), parentItem);
        break;
    case Etype::eEnum :
        nameCheckEnum(*std::dynamic_pointer_cast<MyEnum>(newMePtr), parentItem);
        break;
    case Etype::eFunction :
        nameCheckFunction(*std::dynamic_pointer_cast<Function>(newMePtr), parentItem);
        {
            QStandardItem *  rootItem = parentItem->parent();
            Etype const  rootEtp = static_cast<Etype>(rootItem->data(
                    Qt::UserRole + 1).toInt());
            void *  rootPtr = rootItem->data(Qt::UserRole + 2).value<void *>();
            if (rootEtp == Etype::eClass) {
                std::dynamic_pointer_cast<Function>(newMePtr)
                        ->setParentClassPtr(static_cast<MyClass *>(rootPtr));
            }

            switch (parentEtp) {
            case Etype::eFunctions :
            case Etype::eStaticFunctions :
            case Etype::eConstexprFunctions :
            case Etype::eTplFunctions :
            case Etype::eTplStaticFunctions :
            case Etype::eTplConstexprFunctions :
            case Etype::eConstructors :
            case Etype::eTplConstructors :
                static_cast<Functions *>(parentPtr)->procFunction(
                        *std::dynamic_pointer_cast<Function>(newMePtr));
                break;
            default :
                break;
            }
        }
        std::dynamic_pointer_cast<Function>(newMePtr)->init();
        break;
    case Etype::eFunctions :
    case Etype::eStaticFunctions :
    case Etype::eConstexprFunctions :
    case Etype::eTplFunctions :
    case Etype::eTplStaticFunctions :
    case Etype::eTplConstexprFunctions :
    case Etype::eConstructors :
    case Etype::eTplConstructors :
        if (parentEtp == Etype::eClass) {
            std::dynamic_pointer_cast<Functions>(newMePtr)->setParentClassPtr(
                    static_cast<MyClass *>(parentPtr));
        }
        break;
    case Etype::eDefaultConstructorFn :
    case Etype::eCopyConstructorFn :
    case Etype::eMoveConstructorFn :
    case Etype::eDestructorFn :
    case Etype::eCopyOperatorEqFn :
    case Etype::eMoveOperatorEqFn :
        if (parentEtp == Etype::eClass) {
            std::dynamic_pointer_cast<Function>(newMePtr)->setParentClassPtr(
                    static_cast<MyClass *>(parentPtr));
        }
        std::dynamic_pointer_cast<Function>(newMePtr)->init();
        break;
    default :
        break;
    }

    int  selfRow = 0;
    switch (addmethod) {
    case AddMethod::insert :
        selfRow = vecItemStack[0].getSelfRow();
        break;
    case AddMethod::follow :
        selfRow = vecItemStack[0].getSelfRow();
        selfRow++;
        break;
    default :
        break;
    }

    if (newEtp == Etype::eFunction) {
        void *  ptrTmp = vecItemStack[1].getVecPtr();
        std::vector<std::shared_ptr<Function>> *  parentVec =
                static_cast<std::vector<std::shared_ptr<Function>> *>(ptrTmp);
        parentVec->insert(parentVec->begin() + selfRow,
                std::dynamic_pointer_cast<Function>(newMePtr));
    } else {
        void *  ptrTmp = vecItemStack[1].getVecPtr();
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
                parentVec = static_cast<std::vector<std::pair<Etype,
                std::shared_ptr<EObject>>> *>(ptrTmp);
        parentVec->insert(parentVec->begin() + selfRow, newData);
    }

    QStandardItem *  item = new QStandardItem(
            QString::fromStdString(newMePtr->getTreeLabel()));
    setItemProperty(item, newEtp, newMePtr);
    parentItem->insertRow(selfRow, item);

    switch (newEtp) {
    case Etype::eDefaultConstructorFn :
        if (parentEtp == Etype::eClass) {
            static_cast<MyClass *>(parentPtr)->setDefCtor(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repDefCtor();
        }
        break;
    case Etype::eCopyConstructorFn :
        if (parentEtp == Etype::eClass) {
            static_cast<MyClass *>(parentPtr)->setCopyCtor(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repCopyCtor();
        }
        break;
    case Etype::eMoveConstructorFn :
        if (parentEtp == Etype::eClass) {
            static_cast<MyClass *>(parentPtr)->setMoveCtor(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repMoveCtor();
        }
        break;
    case Etype::eDestructorFn :
        if (parentEtp == Etype::eClass) {
            static_cast<MyClass *>(parentPtr)->setDtor(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repDtor();
        }
        break;
    case Etype::eCopyOperatorEqFn :
        if (parentEtp == Etype::eClass) {
            static_cast<MyClass *>(parentPtr)->setCopyOpEq(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repCopyOpEq();
        }
        break;
    case Etype::eMoveOperatorEqFn :
        if (parentEtp == Etype::eClass) {
            static_cast<MyClass *>(parentPtr)->setMoveOpEq(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repMoveOpEq();
        }
        break;
    default :
        break;
    }
}

template <typename T> inline
void
MainWindow::insertChildValue(QModelIndex const &  index,
                             MainWindow::AddMethod const  addmethod,
                             Etype const  newEtp,
                             T const &  mouldVal,
                             int const  insertRow /* = 0 */)
{
    if (!index.isValid())  return;
    std::vector<ItemStack>  vecItemStack;
    getItemStack(vecItemStack, index);

    QStandardItem *  selfItem = vecItemStack[0].getSelfItem();
    Etype const  selfEtp = static_cast<Etype>(selfItem->data(
            Qt::UserRole + 1).toInt());
    void *  selfPtr = selfItem->data(Qt::UserRole + 2).value<void *>();

    QStandardItem *  parentItem = vecItemStack[0].getParentItem();
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(
            Qt::UserRole + 1).toInt());
    void *  parentPtr = parentItem->data(Qt::UserRole + 2).value<void *>();

    std::shared_ptr<T>  newMePtr = std::make_shared<T>(mouldVal);
    std::pair<Etype, std::shared_ptr<EObject>>  newData;
    newData.first = newEtp;
    newData.second = newMePtr;

    {
        void *  ptrTmp = vecItemStack[0].getVecPtr();
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
                parentVec = static_cast<std::vector<std::pair<Etype,
                std::shared_ptr<EObject>>> *>(ptrTmp);

        switch (newEtp) {
        case Etype::eDefaultConstructorFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eDefaultConstructorFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        case Etype::eCopyConstructorFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eCopyConstructorFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        case Etype::eMoveConstructorFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eMoveConstructorFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        case Etype::eDestructorFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eDestructorFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        case Etype::eCopyOperatorEqFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eCopyOperatorEqFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        case Etype::eMoveOperatorEqFn :
            {
                auto  itF = std::find_if(parentVec->begin(), parentVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eMoveOperatorEqFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != parentVec->end())  return;
            }
            break;
        default :
            break;
        }
    }

    switch (newEtp) {
    case Etype::eClass :
        nameCheckClass(*std::dynamic_pointer_cast<MyClass>(newMePtr), selfItem);
        if (selfEtp == Etype::eModule) {
            std::dynamic_pointer_cast<MyClass>(newMePtr)->setParentModulePtr(
                    static_cast<Module *>(selfPtr));
        }
        if (std::dynamic_pointer_cast<MyClass>(newMePtr)->hasEqFunction()) {
            std::dynamic_pointer_cast<MyClass>(newMePtr)->setEqFunction(false);
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                    std::dynamic_pointer_cast<MyClass>(newMePtr)->getEObjectPtr();
            auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eVirtualEqFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itF != objVec->end()) {
                objVec->erase(itF);
            }
        }
        if (std::dynamic_pointer_cast<MyClass>(newMePtr)->hasLessFunction()) {
            std::dynamic_pointer_cast<MyClass>(newMePtr)->setLessFunction(false);
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                    std::dynamic_pointer_cast<MyClass>(newMePtr)->getEObjectPtr();
            auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eVirtualLessFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itF != objVec->end()) {
                objVec->erase(itF);
            }
        }
        if (std::dynamic_pointer_cast<MyClass>(newMePtr)->hasSwapFunction()) {
            std::dynamic_pointer_cast<MyClass>(newMePtr)->setSwapFunction(false);
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                    std::dynamic_pointer_cast<MyClass>(newMePtr)->getEObjectPtr();
            auto  itFIn = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eInSwapFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFIn != objVec->end()) {
                objVec->erase(itFIn);
            }
            auto  itFVir = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eVirtualExchangeFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFVir != objVec->end()) {
                objVec->erase(itFVir);
            }
        }
        if (std::dynamic_pointer_cast<MyClass>(newMePtr)->hasToStringFunction()) {
            std::dynamic_pointer_cast<MyClass>(newMePtr)->setToStringFunction(false);
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                    std::dynamic_pointer_cast<MyClass>(newMePtr)->getEObjectPtr();
            auto  itFToString = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eToStringFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFToString != objVec->end()) {
                objVec->erase(itFToString);
            }
            auto  itFVirS = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eVirtualSerializeFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFVirS != objVec->end()) {
                objVec->erase(itFVirS);
            }
            auto  itFFromString = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eInFromStringFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFFromString != objVec->end()) {
                objVec->erase(itFFromString);
            }
            auto  itFDes = std::find_if(objVec->begin(), objVec->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eDeserializeFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itFDes != objVec->end()) {
                objVec->erase(itFDes);
            }
        }
        break;
    case Etype::eStruct :
        nameCheckStruct(*std::dynamic_pointer_cast<MyStruct>(newMePtr), selfItem);
        break;
    case Etype::eEnum :
        nameCheckEnum(*std::dynamic_pointer_cast<MyEnum>(newMePtr), selfItem);
        break;
    case Etype::eFunction :
        nameCheckFunction(*std::dynamic_pointer_cast<Function>(newMePtr), selfItem);
        {
            if (parentEtp == Etype::eClass) {
                std::dynamic_pointer_cast<Function>(newMePtr)
                        ->setParentClassPtr(static_cast<MyClass *>(parentPtr));
            }

            switch (selfEtp) {
            case Etype::eFunctions :
            case Etype::eStaticFunctions :
            case Etype::eConstexprFunctions :
            case Etype::eTplFunctions :
            case Etype::eTplStaticFunctions :
            case Etype::eTplConstexprFunctions :
            case Etype::eConstructors :
            case Etype::eTplConstructors :
                static_cast<Functions *>(selfPtr)->procFunction(
                        *std::dynamic_pointer_cast<Function>(newMePtr));
                break;
            default :
                break;
            }
        }
        break;
    case Etype::eFunctions :
    case Etype::eStaticFunctions :
    case Etype::eConstexprFunctions :
    case Etype::eTplFunctions :
    case Etype::eTplStaticFunctions :
    case Etype::eTplConstexprFunctions :
    case Etype::eConstructors :
    case Etype::eTplConstructors :
        if (selfEtp == Etype::eClass) {
            std::dynamic_pointer_cast<Functions>(newMePtr)->setParentClassPtr(
                    static_cast<MyClass *>(selfPtr));
        }
        break;
    case Etype::eDefaultConstructorFn :
    case Etype::eCopyConstructorFn :
    case Etype::eMoveConstructorFn :
    case Etype::eDestructorFn :
    case Etype::eCopyOperatorEqFn :
    case Etype::eMoveOperatorEqFn :
        if (selfEtp == Etype::eClass) {
            std::dynamic_pointer_cast<Function>(newMePtr)->setParentClassPtr(
                    static_cast<MyClass *>(selfPtr));
        }
        std::dynamic_pointer_cast<Function>(newMePtr)->init();
        break;
    default :
        break;
    }

    int  selfRow = selfItem->rowCount();
    if (addmethod == AddMethod::childInsert) {
        selfRow = insertRow;
    }

    if (newEtp == Etype::eFunction) {
        void *  ptrTmp = vecItemStack[0].getVecPtr();
        std::vector<std::shared_ptr<Function>> *  parentVec =
                static_cast<std::vector<std::shared_ptr<Function>> *>(ptrTmp);
        parentVec->insert(parentVec->begin() + selfRow,
                std::dynamic_pointer_cast<Function>(newMePtr));
    } else {
        void *  ptrTmp = vecItemStack[0].getVecPtr();
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
                parentVec = static_cast<std::vector<std::pair<Etype,
                std::shared_ptr<EObject>>> *>(ptrTmp);
        parentVec->insert(parentVec->begin() + selfRow, newData);
    }

    QStandardItem *  item = new QStandardItem(
            QString::fromStdString(newMePtr->getTreeLabel()));
    setItemProperty(item, newEtp, newMePtr);
    selfItem->insertRow(selfRow, item);

    if (!m_mainTreeView->isExpanded(index)) {
        m_mainTreeView->expand(index);
    }

    switch (newEtp) {
    case Etype::eDefaultConstructorFn :
        if (selfEtp == Etype::eClass) {
            static_cast<MyClass *>(selfPtr)->setDefCtor(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repDefCtor();
        }
        break;
    case Etype::eCopyConstructorFn :
        if (selfEtp == Etype::eClass) {
            static_cast<MyClass *>(selfPtr)->setCopyCtor(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repCopyCtor();
        }
        break;
    case Etype::eMoveConstructorFn :
        if (selfEtp == Etype::eClass) {
            static_cast<MyClass *>(selfPtr)->setMoveCtor(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repMoveCtor();
        }
        break;
    case Etype::eDestructorFn :
        if (selfEtp == Etype::eClass) {
            static_cast<MyClass *>(selfPtr)->setDtor(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repDtor();
        }
        break;
    case Etype::eCopyOperatorEqFn :
        if (selfEtp == Etype::eClass) {
            static_cast<MyClass *>(selfPtr)->setCopyOpEq(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repCopyOpEq();
        }
        break;
    case Etype::eMoveOperatorEqFn :
        if (selfEtp == Etype::eClass) {
            static_cast<MyClass *>(selfPtr)->setMoveOpEq(true);
        }
        if (m_spvMain->widget(1) == m_wtMyClass) {
            m_wtMyClass->repMoveOpEq();
        }
        break;
    default :
        break;
    }
}

}

#endif
