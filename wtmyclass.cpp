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
#include "field.h"
#include "highlighter.h"
#include "twobeforebehind.h"
#include "fourbeforebehind.h"
#include "fmt.h"
#include "mystruct.h"
#include "mystructdec.h"
#include "myclassdec.h"
#include "wtmyclass.h"
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

void
setItemProperty(QStandardItem *  item,
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

    switch (etp) {
    case Etype::eClass :
        item->setForeground(QBrush(QColor(0xe6, 0x91, 0x6f)));
        break;
    case Etype::eClassDeclaration :
        item->setForeground(QBrush(QColor(0xd3, 0x85, 0x66)));
        break;
    case Etype::eLabel :
    case Etype::ePublicLabel :
    case Etype::eProtectedLabel :
    case Etype::ePrivateLabel :
        item->setForeground(QBrush(QColor(0x7b, 0xc1, 0x3d)));
        break;
    case Etype::eFunctions :
    case Etype::eStaticFunctions :
    case Etype::eConstexprFunctions :
    case Etype::eTplFunctions :
    case Etype::eTplStaticFunctions :
    case Etype::eTplConstexprFunctions :
    case Etype::eConstructors :
    case Etype::eTplConstructors :
        item->setForeground(QBrush(QColor(0xaf, 0xbe, 0xf3)));
        break;
    default :
        break;
    }
}

WtMyClass::WtMyClass(QWidget *  parent /* = nullptr */):
        WtBase(parent),
        m_objPtr(nullptr),
        m_className(nullptr),
        m_attribute(nullptr),
        m_alignas(nullptr),
        m_beforBehindPb(nullptr),
        m_mainTab(nullptr),
        m_docmentClass(nullptr),
        m_replaceClassName(nullptr),
        m_isFinalClass(nullptr),
        m_isSetterReturnThis(nullptr),
        m_isTemplate(nullptr),
        m_isUpdateFilename(nullptr),
        m_isImpl(nullptr),
        m_isInternal(nullptr),
        m_isIndPublicLabel(nullptr),
        m_hasDefCtor(nullptr),
        m_hasCopyCtor(nullptr),
        m_hasMoveCtor(nullptr),
        m_hasDtor(nullptr),
        m_hasCopyOpEq(nullptr),
        m_hasMoveOpEq(nullptr),
        m_classTypeGroup(nullptr),
        m_finalClass(nullptr),
        m_baseClass(nullptr),
        m_inheritClass(nullptr),
        m_baseClassPrarm(nullptr),
        m_templateView(nullptr),
        m_templateModel(nullptr),
        m_friendClassView(nullptr),
        m_friendClassModel(nullptr),
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
        m_hasLessFunction(nullptr),
        m_hasEqFunction(nullptr),
        m_hasSwapFunction(nullptr),
        m_hasToStringFunction(nullptr),
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
        m_fieldActionInsertCode(nullptr),
        m_dotH(nullptr),
        m_dotCpp(nullptr)
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

    if (m_objPtr->isUpdateFilename()) {
        std::vector<QStandardItem *>  itemVec;
        QStandardItem *  itemTmp = itemPtr->parent();
        while (true) {
            if (!itemTmp)  break;
            itemVec.push_back(itemTmp);
            itemTmp = itemTmp->parent();
        }
        for (QStandardItem *  item: itemVec) {
            Etype const  etp = static_cast<Etype>(item->data(Qt::UserRole + 1).toInt());
            void *  ptr = item->data(Qt::UserRole + 2).value<void *>();
            if (etp == Etype::eModule) {
                Module *  mdPtr = static_cast<Module *>(ptr);
                QVariant  treeLabelMd(QString::fromStdString(mdPtr->getTreeLabel()));
                item->setData(treeLabelMd, Qt::EditRole);
                break;
            }
        }
    }

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

    std::vector<NamespaceItem>  selfNamespace;
    Etype const  parentEtp = static_cast<Etype>(parentItem->data(
            Qt::UserRole + 1).toInt());
    if (parentEtp == Etype::eModule) {
        Module *  mdPtr = static_cast<Module *>(parentItem->data(
                Qt::UserRole + 2).value<void *>());
        selfNamespace = mdPtr->getNamespace();
    }

    QStandardItem *  prjItem = parentItem->parent();
    Etype const  prjEtp = static_cast<Etype>(prjItem->data(
            Qt::UserRole + 1).toInt());
    if (prjEtp == Etype::eProject) {
        Project *  prjPtr = static_cast<Project *>(prjItem->data(
                Qt::UserRole + 2).value<void *>());

        std::vector<std::shared_ptr<Module>> &  vec = prjPtr->getModuleListRef();
        for (auto &  it: vec) {
            std::vector<NamespaceItem> const  nsp = it->getNamespace();
            if (selfNamespace != nsp)  continue;

            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  mdVec =
                    it->getEObjectListRef();
            for (auto &  mdIt:  mdVec) {
                if (mdIt.first == Etype::eClass) {
                    std::vector<std::string>  friendVec = static_cast<MyClass *>(
                            mdIt.second.get())->getFriendClassName();
                    for (auto &  fname:  friendVec) {
                        if (fname == oldVal)  fname = newVal;
                    }
                    static_cast<MyClass *>(mdIt.second.get())->setFriendClassName(friendVec);
                }
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
WtMyClass::replaceClassName_editingFinished()
{
    if (!m_objPtr)  return;

    m_objPtr->setReplaceClassName(m_replaceClassName->text().toUtf8().toStdString());
}

void
WtMyClass::isFinalClass_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->isFinalClass();
    if (currVal == oldVal)  return;

    m_objPtr->setFinalClass(currVal);
    bool const  newVal = m_objPtr->isFinalClass();
    if (newVal != currVal) {
        m_isFinalClass->setChecked(newVal);
    }
}

void
WtMyClass::isTemplate_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    m_objPtr->setTemplate(currVal);
}

void
WtMyClass::isSetterReturnThis_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    const bool  oldVal = m_objPtr->isSetterReturnThis();
    if (currVal != oldVal) {
        m_objPtr->setSetterReturnThis(currVal);
        repFieldAction();
    }
}

void
WtMyClass::isUpdateFilename_stateChanged(int const  status)
{
    QStandardItem *  itemPtr = getItemPtr();
    if (!m_objPtr || !itemPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    m_objPtr->setUpdateFilename(currVal);
    if (currVal) {
        std::vector<QStandardItem *>  itemVec;
        QStandardItem *  itemTmp = itemPtr->parent();
        while (true) {
            if (!itemTmp)  break;
            itemVec.push_back(itemTmp);
            itemTmp = itemTmp->parent();
        }
        for (QStandardItem *  item: itemVec) {
            Etype const  etp = static_cast<Etype>(item->data(Qt::UserRole + 1).toInt());
            void *  ptr = item->data(Qt::UserRole + 2).value<void *>();
            if (etp == Etype::eModule) {
                Module *  mdPtr = static_cast<Module *>(ptr);
                QVariant  treeLabelMd(QString::fromStdString(mdPtr->getTreeLabel()));
                item->setData(treeLabelMd, Qt::EditRole);
                break;
            }
        }
    }
}

void
WtMyClass::isImpl_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    m_objPtr->setImpl(currVal);
}

void
WtMyClass::isInternal_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }

    if (currVal) {
        QMessageBox::StandardButton  message = QMessageBox::question(this,
                "Internal Class", "Is Internal Class?",
                QMessageBox::Yes | QMessageBox::No,
                QMessageBox::No);
        if (message == QMessageBox::No) {
            m_isInternal->setChecked(false);
            return;
        }
    }

    m_objPtr->setInternal(currVal);

    if (currVal) {
        m_hasLessFunction->setChecked(false);
        m_hasEqFunction->setChecked(false);
        m_hasSwapFunction->setChecked(false);
        m_hasToStringFunction->setChecked(false);

        m_hasLessFunction->setCheckable(false);
        m_hasEqFunction->setCheckable(false);
        m_hasSwapFunction->setCheckable(false);
        m_hasToStringFunction->setCheckable(false);
    } else {
        m_hasLessFunction->setCheckable(true);
        m_hasEqFunction->setCheckable(true);
        m_hasSwapFunction->setCheckable(true);
        m_hasToStringFunction->setCheckable(true);
    }
}

void
WtMyClass::isIndPublicLabel_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    m_objPtr->setIndPublicLabel(currVal);
}

void
WtMyClass::hasDefCtor_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->hasDefCtor();
    if (currVal != oldVal) {
        if (currVal) {
            int  index = -1;
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                    m_objPtr->getEObjectRef();
            for (int  i = 0; i < vecClass.size(); ++i) {
                if (vecClass[i].first == Etype::ePublicLabel) {
                    index = i;
                    break;
                }
            }
            QStandardItem *  itemClass = getItemPtr();
            if (index == -1) {
                std::shared_ptr<PublicLabel>  objPtr =
                        std::make_shared<PublicLabel>();
                std::pair<Etype, std::shared_ptr<EObject>>  newObj;
                newObj.first = Etype::ePublicLabel;
                newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
                m_objPtr->appendEobjList(newObj);
                index = static_cast<int>(vecClass.size() - 1);

                QStandardItem *  item = new QStandardItem(
                        QString::fromStdString(newObj.second->getTreeLabel()));
                setItemProperty(item, newObj.first, newObj.second);
                item->setForeground(QBrush(QColor(0x7b, 0xc1, 0x3d)));
                itemClass->appendRow(item);
            }
            index++;
            std::pair<Etype, std::shared_ptr<EObject>>  fn =
                    std::make_pair<Etype, std::shared_ptr<EObject>>(
                    Etype::eDefaultConstructorFn,
                    std::make_shared<DefaultConstructorFn>(
                    DefaultConstructorFn(m_objPtr)));
            m_objPtr->insertEobjList(fn, index);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(fn.second->getTreeLabel()));
            setItemProperty(item, fn.first, fn.second);
            itemClass->insertRow(index, item);
        } else {
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  vecP =
                    m_objPtr->getEObjectPtr();
            auto  itF = std::find_if(vecP->begin(), vecP->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) -> bool {
                        if (val.first == Etype::eDefaultConstructorFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itF != vecP->end()) {
                vecP->erase(itF);
            }

            QStandardItem *  itemClass = getItemPtr();
            int const  count = itemClass->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemClass->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eDefaultConstructorFn) {
                    itemClass->removeRow(i);
                    break;
                }
            }
        }
        m_objPtr->setDefCtor(currVal);
    }
}

void
WtMyClass::hasCopyCtor_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->hasCopyCtor();
    if (currVal != oldVal) {
        if (currVal) {
            int  index = -1;
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                    m_objPtr->getEObjectRef();
            for (int  i = 0; i < vecClass.size(); ++i) {
                if (vecClass[i].first == Etype::ePublicLabel) {
                    index = i;
                    break;
                }
            }
            QStandardItem *  itemClass = getItemPtr();
            if (index == -1) {
                std::shared_ptr<PublicLabel>  objPtr =
                        std::make_shared<PublicLabel>();
                std::pair<Etype, std::shared_ptr<EObject>>  newObj;
                newObj.first = Etype::ePublicLabel;
                newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
                m_objPtr->appendEobjList(newObj);
                index = static_cast<int>(vecClass.size() - 1);

                QStandardItem *  item = new QStandardItem(
                        QString::fromStdString(newObj.second->getTreeLabel()));
                setItemProperty(item, newObj.first, newObj.second);
                item->setForeground(QBrush(QColor(0x7b, 0xc1, 0x3d)));
                itemClass->appendRow(item);
            }
            index++;
            std::pair<Etype, std::shared_ptr<EObject>>  fn =
                    std::make_pair<Etype, std::shared_ptr<EObject>>(
                    Etype::eCopyConstructorFn,
                    std::make_shared<CopyConstructorFn>(
                    CopyConstructorFn(m_objPtr)));
            m_objPtr->insertEobjList(fn, index);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(fn.second->getTreeLabel()));
            setItemProperty(item, fn.first, fn.second);
            itemClass->insertRow(index, item);
        } else {
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  vecP =
                    m_objPtr->getEObjectPtr();
            auto  itF = std::find_if(vecP->begin(), vecP->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) -> bool {
                        if (val.first == Etype::eCopyConstructorFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itF != vecP->end()) {
                vecP->erase(itF);
            }

            QStandardItem *  itemClass = getItemPtr();
            int const  count = itemClass->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemClass->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eCopyConstructorFn) {
                    itemClass->removeRow(i);
                    break;
                }
            }
        }
        m_objPtr->setCopyCtor(currVal);
    }
}

void
WtMyClass::hasMoveCtor_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->hasMoveCtor();
    if (currVal != oldVal) {
        if (currVal) {
            int  index = -1;
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                    m_objPtr->getEObjectRef();
            for (int  i = 0; i < vecClass.size(); ++i) {
                if (vecClass[i].first == Etype::ePublicLabel) {
                    index = i;
                    break;
                }
            }
            QStandardItem *  itemClass = getItemPtr();
            if (index == -1) {
                std::shared_ptr<PublicLabel>  objPtr =
                        std::make_shared<PublicLabel>();
                std::pair<Etype, std::shared_ptr<EObject>>  newObj;
                newObj.first = Etype::ePublicLabel;
                newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
                m_objPtr->appendEobjList(newObj);
                index = static_cast<int>(vecClass.size() - 1);

                QStandardItem *  item = new QStandardItem(
                        QString::fromStdString(newObj.second->getTreeLabel()));
                setItemProperty(item, newObj.first, newObj.second);
                item->setForeground(QBrush(QColor(0x7b, 0xc1, 0x3d)));
                itemClass->appendRow(item);
            }
            index++;
            std::pair<Etype, std::shared_ptr<EObject>>  fn =
                    std::make_pair<Etype, std::shared_ptr<EObject>>(
                    Etype::eMoveConstructorFn,
                    std::make_shared<MoveConstructorFn>(
                    MoveConstructorFn(m_objPtr)));
            m_objPtr->insertEobjList(fn, index);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(fn.second->getTreeLabel()));
            setItemProperty(item, fn.first, fn.second);
            itemClass->insertRow(index, item);
        } else {
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  vecP =
                    m_objPtr->getEObjectPtr();
            auto  itF = std::find_if(vecP->begin(), vecP->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) -> bool {
                        if (val.first == Etype::eMoveConstructorFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itF != vecP->end()) {
                vecP->erase(itF);
            }

            QStandardItem *  itemClass = getItemPtr();
            int const  count = itemClass->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemClass->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eMoveConstructorFn) {
                    itemClass->removeRow(i);
                    break;
                }
            }
        }
        m_objPtr->setMoveCtor(currVal);
    }
}

void
WtMyClass::hasDtor_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->hasDtor();
    if (currVal != oldVal) {
        if (currVal) {
            int  index = -1;
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                    m_objPtr->getEObjectRef();
            for (int  i = 0; i < vecClass.size(); ++i) {
                if (vecClass[i].first == Etype::ePublicLabel) {
                    index = i;
                    break;
                }
            }
            QStandardItem *  itemClass = getItemPtr();
            if (index == -1) {
                std::shared_ptr<PublicLabel>  objPtr =
                        std::make_shared<PublicLabel>();
                std::pair<Etype, std::shared_ptr<EObject>>  newObj;
                newObj.first = Etype::ePublicLabel;
                newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
                m_objPtr->appendEobjList(newObj);
                index = static_cast<int>(vecClass.size() - 1);

                QStandardItem *  item = new QStandardItem(
                        QString::fromStdString(newObj.second->getTreeLabel()));
                setItemProperty(item, newObj.first, newObj.second);
                item->setForeground(QBrush(QColor(0x7b, 0xc1, 0x3d)));
                itemClass->appendRow(item);
            }
            index++;
            std::pair<Etype, std::shared_ptr<EObject>>  fn =
                    std::make_pair<Etype, std::shared_ptr<EObject>>(
                    Etype::eDestructorFn,
                    std::make_shared<DestructorFn>(
                    DestructorFn(m_objPtr)));
            m_objPtr->insertEobjList(fn, index);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(fn.second->getTreeLabel()));
            setItemProperty(item, fn.first, fn.second);
            itemClass->insertRow(index, item);
        } else {
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  vecP =
                    m_objPtr->getEObjectPtr();
            auto  itF = std::find_if(vecP->begin(), vecP->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) -> bool {
                        if (val.first == Etype::eDestructorFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itF != vecP->end()) {
                vecP->erase(itF);
            }

            QStandardItem *  itemClass = getItemPtr();
            int const  count = itemClass->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemClass->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eDestructorFn) {
                    itemClass->removeRow(i);
                    break;
                }
            }
        }
        m_objPtr->setDtor(currVal);
    }
}

void
WtMyClass::hasCopyOpEq_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->hasCopyOpEq();
    if (currVal != oldVal) {
        if (currVal) {
            int  index = -1;
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                    m_objPtr->getEObjectRef();
            for (int  i = 0; i < vecClass.size(); ++i) {
                if (vecClass[i].first == Etype::ePublicLabel) {
                    index = i;
                    break;
                }
            }
            QStandardItem *  itemClass = getItemPtr();
            if (index == -1) {
                std::shared_ptr<PublicLabel>  objPtr =
                        std::make_shared<PublicLabel>();
                std::pair<Etype, std::shared_ptr<EObject>>  newObj;
                newObj.first = Etype::ePublicLabel;
                newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
                m_objPtr->appendEobjList(newObj);
                index = static_cast<int>(vecClass.size() - 1);

                QStandardItem *  item = new QStandardItem(
                        QString::fromStdString(newObj.second->getTreeLabel()));
                setItemProperty(item, newObj.first, newObj.second);
                item->setForeground(QBrush(QColor(0x7b, 0xc1, 0x3d)));
                itemClass->appendRow(item);
            }
            index++;
            std::pair<Etype, std::shared_ptr<EObject>>  fn =
                    std::make_pair<Etype, std::shared_ptr<EObject>>(
                    Etype::eCopyOperatorEqFn,
                    std::make_shared<CopyOperatorEqFn>(
                    CopyOperatorEqFn(m_objPtr)));
            m_objPtr->insertEobjList(fn, index);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(fn.second->getTreeLabel()));
            setItemProperty(item, fn.first, fn.second);
            itemClass->insertRow(index, item);
        } else {
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  vecP =
                    m_objPtr->getEObjectPtr();
            auto  itF = std::find_if(vecP->begin(), vecP->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) -> bool {
                        if (val.first == Etype::eCopyOperatorEqFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itF != vecP->end()) {
                vecP->erase(itF);
            }

            QStandardItem *  itemClass = getItemPtr();
            int const  count = itemClass->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemClass->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eCopyOperatorEqFn) {
                    itemClass->removeRow(i);
                    break;
                }
            }
        }
        m_objPtr->setCopyOpEq(currVal);
    }
}

void
WtMyClass::hasMoveOpEq_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->hasMoveOpEq();
    if (currVal != oldVal) {
        if (currVal) {
            int  index = -1;
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                    m_objPtr->getEObjectRef();
            for (int  i = 0; i < vecClass.size(); ++i) {
                if (vecClass[i].first == Etype::ePublicLabel) {
                    index = i;
                    break;
                }
            }
            QStandardItem *  itemClass = getItemPtr();
            if (index == -1) {
                std::shared_ptr<PublicLabel>  objPtr =
                        std::make_shared<PublicLabel>();
                std::pair<Etype, std::shared_ptr<EObject>>  newObj;
                newObj.first = Etype::ePublicLabel;
                newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
                m_objPtr->appendEobjList(newObj);
                index = static_cast<int>(vecClass.size() - 1);

                QStandardItem *  item = new QStandardItem(
                        QString::fromStdString(newObj.second->getTreeLabel()));
                setItemProperty(item, newObj.first, newObj.second);
                item->setForeground(QBrush(QColor(0x7b, 0xc1, 0x3d)));
                itemClass->appendRow(item);
            }
            index++;
            std::pair<Etype, std::shared_ptr<EObject>>  fn =
                    std::make_pair<Etype, std::shared_ptr<EObject>>(
                    Etype::eMoveOperatorEqFn,
                    std::make_shared<MoveOperatorEqFn>(
                    MoveOperatorEqFn(m_objPtr)));
            m_objPtr->insertEobjList(fn, index);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(fn.second->getTreeLabel()));
            setItemProperty(item, fn.first, fn.second);
            itemClass->insertRow(index, item);
        } else {
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  vecP =
                    m_objPtr->getEObjectPtr();
            auto  itF = std::find_if(vecP->begin(), vecP->end(), [](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) -> bool {
                        if (val.first == Etype::eMoveOperatorEqFn) {
                            return true;
                        } else {
                            return false;
                        }
                    });
            if (itF != vecP->end()) {
                vecP->erase(itF);
            }

            QStandardItem *  itemClass = getItemPtr();
            int const  count = itemClass->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemClass->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eMoveOperatorEqFn) {
                    itemClass->removeRow(i);
                    break;
                }
            }
        }
        m_objPtr->setMoveOpEq(currVal);
    }
}

void
WtMyClass::finalClass_toggled(bool const  isChecked)
{
    if (!m_objPtr)  return;

    if (isChecked) {
        ClassType const  currVal = ClassType::cppFinal;
        ClassType const  oldVal = m_objPtr->getClasstype();
        if (currVal == oldVal)  return;

        m_objPtr->setClasstype(currVal);
        repIsFinalClass();
        m_isFinalClass->hide();

        if (oldVal == ClassType::cppBase) {
            if (m_objPtr->hasEqFunction()) {
                EqFn  fnEq(m_objPtr->getClassName(), m_objPtr);
                NotEqFn  fnNotEq(m_objPtr->getClassName(), m_objPtr);
                VirtualEqFn  fnVirtualEq(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualEqFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualEq = std::move(*std::dynamic_pointer_cast<VirtualEqFn>(
                            itF->second));
                }

                Module *  mdPtr = m_objPtr->getParentModulePtr();
                objVec = mdPtr->getEObjectListPtr();
                auto  itEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eEqFn) {
                                if (std::dynamic_pointer_cast<EqFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itEqFn != objVec->end()) {
                    fnEq = std::move(*std::dynamic_pointer_cast<EqFn>(
                            itEqFn->second));
                }
                auto  itNotEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eNotEqFn) {
                                if (std::dynamic_pointer_cast<NotEqFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itNotEqFn != objVec->end()) {
                    fnNotEq = std::move(*std::dynamic_pointer_cast<NotEqFn>(
                            itNotEqFn->second));
                }

                fnEq.setStrike(fnVirtualEq.getStrike());
                fnEq.setNewCode(fnVirtualEq.getNewCode());
                fnEq.setAttribute(fnVirtualEq.getAttribute());
                fnEq.setHBefore(fnVirtualEq.getHBefore());
                fnEq.setHBehind(fnVirtualEq.getHBehind());
                fnEq.setCppBefore(fnVirtualEq.getCppBefore());
                fnEq.setCppBehind(fnVirtualEq.getCppBehind());
                fnVirtualEq.setStrike({});
                fnVirtualEq.setNewCode({});
                fnVirtualEq.setAttribute("");
                fnVirtualEq.setHBefore("");
                fnVirtualEq.setHBehind("");
                fnVirtualEq.setCppBefore("");
                fnVirtualEq.setCppBehind("");
                setEqFn(false);
                setEqFnAdd(std::move(fnEq), std::move(fnNotEq), std::move(fnVirtualEq));
            }

            if (m_objPtr->hasLessFunction()) {
                LessFn  fnLess(m_objPtr->getClassName(), m_objPtr);
                LessEqFn  fnLessEq(m_objPtr->getClassName(), m_objPtr);
                GreaterFn  fnGreater(m_objPtr->getClassName(), m_objPtr);
                GreaterEqFn  fnGreaterEq(m_objPtr->getClassName(), m_objPtr);
                VirtualLessFn  fnVirtualLess(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualLessFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualLess = std::move(*std::dynamic_pointer_cast<VirtualLessFn>(
                            itF->second));
                }

                Module *  mdPtr = m_objPtr->getParentModulePtr();
                objVec = mdPtr->getEObjectListPtr();
                auto  itLessFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eLessFn) {
                                if (std::dynamic_pointer_cast<LessFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itLessFn != objVec->end()) {
                    fnLess = std::move(*std::dynamic_pointer_cast<LessFn>(
                            itLessFn->second));
                }
                auto  itLessEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eLessEqFn) {
                                if (std::dynamic_pointer_cast<LessEqFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itLessEqFn != objVec->end()) {
                    fnLessEq = std::move(*std::dynamic_pointer_cast<LessEqFn>(
                            itLessEqFn->second));
                }
                auto  itGreaterFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eGreaterFn) {
                                if (std::dynamic_pointer_cast<GreaterFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itGreaterFn != objVec->end()) {
                    fnGreater = std::move(*std::dynamic_pointer_cast<GreaterFn>(
                            itGreaterFn->second));
                }
                auto  itGreaterEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eGreaterEqFn) {
                                if (std::dynamic_pointer_cast<GreaterEqFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itGreaterEqFn != objVec->end()) {
                    fnGreaterEq = std::move(*std::dynamic_pointer_cast<GreaterEqFn>(
                            itGreaterEqFn->second));
                }

                fnLess.setStrike(fnVirtualLess.getStrike());
                fnLess.setNewCode(fnVirtualLess.getNewCode());
                fnLess.setAttribute(fnVirtualLess.getAttribute());
                fnLess.setHBefore(fnVirtualLess.getHBefore());
                fnLess.setHBehind(fnVirtualLess.getHBehind());
                fnLess.setCppBefore(fnVirtualLess.getCppBefore());
                fnLess.setCppBehind(fnVirtualLess.getCppBehind());
                fnVirtualLess.setStrike({});
                fnVirtualLess.setNewCode({});
                fnVirtualLess.setAttribute("");
                fnVirtualLess.setHBefore("");
                fnVirtualLess.setHBehind("");
                fnVirtualLess.setCppBefore("");
                fnVirtualLess.setCppBehind("");
                setLessFn(false);
                setLessFnAdd(std::move(fnLess), std::move(fnLessEq), std::move(fnGreater),
                        std::move(fnGreaterEq), std::move(fnVirtualLess));
            }

            if (m_objPtr->hasSwapFunction()) {
                ExtSwapFn  fnExtSwap(m_objPtr->getClassName(), m_objPtr);
                InSwapFn  fnInSwap(m_objPtr);
                VirtualExchangeFn  fnVirtualExchange(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eInSwapFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnInSwap = std::move(*std::dynamic_pointer_cast<InSwapFn>(
                            itF->second));
                }
                itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualExchangeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualExchange = std::move(
                            *std::dynamic_pointer_cast<VirtualExchangeFn>(itF->second));
                }

                Module *  mdPtr = m_objPtr->getParentModulePtr();
                objVec = mdPtr->getEObjectListPtr();
                auto  itExtSwapFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eExtSwapFn) {
                                if (std::dynamic_pointer_cast<ExtSwapFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itExtSwapFn != objVec->end()) {
                    fnExtSwap = std::move(*std::dynamic_pointer_cast<ExtSwapFn>(
                            itExtSwapFn->second));
                }

                fnInSwap.setStrike(fnVirtualExchange.getStrike());
                fnInSwap.setNewCode(fnVirtualExchange.getNewCode());
                fnInSwap.setAttribute(fnVirtualExchange.getAttribute());
                fnInSwap.setHBefore(fnVirtualExchange.getHBefore());
                fnInSwap.setHBehind(fnVirtualExchange.getHBehind());
                fnInSwap.setCppBefore(fnVirtualExchange.getCppBefore());
                fnInSwap.setCppBehind(fnVirtualExchange.getCppBehind());
                fnVirtualExchange.setStrike({});
                fnVirtualExchange.setNewCode({});
                fnVirtualExchange.setAttribute("");
                fnVirtualExchange.setHBefore("");
                fnVirtualExchange.setHBehind("");
                fnVirtualExchange.setCppBefore("");
                fnVirtualExchange.setCppBehind("");
                setSwapFn(false);
                setSwapFnAdd(std::move(fnExtSwap), std::move(fnInSwap),
                        std::move(fnVirtualExchange));
            }

            if (m_objPtr->hasToStringFunction()) {
                ToStringFn  fnToString(m_objPtr);
                InFromStringFn  fnInFromString(m_objPtr);
                ExtFromStringFn  fnExtFromString(m_objPtr->getClassName(), m_objPtr);
                DeserializeFn  fnDeserialize(m_objPtr);
                VirtualSerializeFn  fnVirtualSerialize(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eToStringFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnToString = std::move(*std::dynamic_pointer_cast<ToStringFn>(
                            itF->second));
                }
                itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualSerializeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualSerialize = std::move(
                            *std::dynamic_pointer_cast<VirtualSerializeFn>(
                            itF->second));
                }
                itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eInFromStringFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnInFromString = std::move(*std::dynamic_pointer_cast<InFromStringFn>(
                            itF->second));
                }
                itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eDeserializeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnDeserialize = std::move(*std::dynamic_pointer_cast<DeserializeFn>(
                            itF->second));
                }

                Module *  mdPtr = m_objPtr->getParentModulePtr();
                objVec = mdPtr->getEObjectListPtr();
                auto  itExt = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eExtFromStringFn) {
                                if (std::dynamic_pointer_cast<ExtFromStringFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itExt != objVec->end()) {
                    fnExtFromString = std::move(*std::dynamic_pointer_cast<ExtFromStringFn>(
                            itExt->second));
                }

                fnToString.setStrike(fnVirtualSerialize.getStrike());
                fnToString.setNewCode(fnVirtualSerialize.getNewCode());
                fnToString.setAttribute(fnVirtualSerialize.getAttribute());
                fnToString.setHBefore(fnVirtualSerialize.getHBefore());
                fnToString.setHBehind(fnVirtualSerialize.getHBehind());
                fnToString.setCppBefore(fnVirtualSerialize.getCppBefore());
                fnToString.setCppBehind(fnVirtualSerialize.getCppBehind());
                fnVirtualSerialize.setStrike({});
                fnVirtualSerialize.setNewCode({});
                fnVirtualSerialize.setAttribute("");
                fnVirtualSerialize.setHBefore("");
                fnVirtualSerialize.setHBehind("");
                fnVirtualSerialize.setCppBefore("");
                fnVirtualSerialize.setCppBehind("");
                fnInFromString.setStrike(fnDeserialize.getStrike());
                fnInFromString.setNewCode(fnDeserialize.getNewCode());
                fnInFromString.setAttribute(fnDeserialize.getAttribute());
                fnInFromString.setHBefore(fnDeserialize.getHBefore());
                fnInFromString.setHBehind(fnDeserialize.getHBehind());
                fnInFromString.setCppBefore(fnDeserialize.getCppBefore());
                fnInFromString.setCppBehind(fnDeserialize.getCppBehind());
                fnDeserialize.setStrike({});
                fnDeserialize.setNewCode({});
                fnDeserialize.setAttribute("");
                fnDeserialize.setHBefore("");
                fnDeserialize.setHBehind("");
                fnDeserialize.setCppBefore("");
                fnDeserialize.setCppBehind("");
                setToStringFn(false);
                setToStringFnAdd(std::move(fnToString), std::move(fnVirtualSerialize),
                        std::move(fnExtFromString), std::move(fnInFromString),
                        std::move(fnDeserialize));
            }
        } else {
            if (m_objPtr->hasEqFunction()) {
                EqFn  fnEq(m_objPtr->getClassName(), m_objPtr);
                NotEqFn  fnNotEq(m_objPtr->getClassName(), m_objPtr);
                VirtualEqFn  fnVirtualEq(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualEqFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualEq = std::move(*std::dynamic_pointer_cast<VirtualEqFn>(
                            itF->second));
                }

                fnEq.setStrike(fnVirtualEq.getStrike());
                fnEq.setNewCode(fnVirtualEq.getNewCode());
                fnEq.setAttribute(fnVirtualEq.getAttribute());
                fnEq.setHBefore(fnVirtualEq.getHBefore());
                fnEq.setHBehind(fnVirtualEq.getHBehind());
                fnEq.setCppBefore(fnVirtualEq.getCppBefore());
                fnEq.setCppBehind(fnVirtualEq.getCppBehind());
                fnVirtualEq.setStrike({});
                fnVirtualEq.setNewCode({});
                fnVirtualEq.setAttribute("");
                fnVirtualEq.setHBefore("");
                fnVirtualEq.setHBehind("");
                fnVirtualEq.setCppBefore("");
                fnVirtualEq.setCppBehind("");
                setEqFn(false);
                setEqFnAdd(std::move(fnEq), std::move(fnNotEq), std::move(fnVirtualEq));
            }

            if (m_objPtr->hasLessFunction()) {
                LessFn  fnLess(m_objPtr->getClassName(), m_objPtr);
                LessEqFn  fnLessEq(m_objPtr->getClassName(), m_objPtr);
                GreaterFn  fnGreater(m_objPtr->getClassName(), m_objPtr);
                GreaterEqFn  fnGreaterEq(m_objPtr->getClassName(), m_objPtr);
                VirtualLessFn  fnVirtualLess(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualLessFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualLess = std::move(*std::dynamic_pointer_cast<VirtualLessFn>(
                            itF->second));
                }

                fnLess.setStrike(fnVirtualLess.getStrike());
                fnLess.setNewCode(fnVirtualLess.getNewCode());
                fnLess.setAttribute(fnVirtualLess.getAttribute());
                fnLess.setHBefore(fnVirtualLess.getHBefore());
                fnLess.setHBehind(fnVirtualLess.getHBehind());
                fnLess.setCppBefore(fnVirtualLess.getCppBefore());
                fnLess.setCppBehind(fnVirtualLess.getCppBehind());
                fnVirtualLess.setStrike({});
                fnVirtualLess.setNewCode({});
                fnVirtualLess.setAttribute("");
                fnVirtualLess.setHBefore("");
                fnVirtualLess.setHBehind("");
                fnVirtualLess.setCppBefore("");
                fnVirtualLess.setCppBehind("");
                setLessFn(false);
                setLessFnAdd(std::move(fnLess), std::move(fnLessEq), std::move(fnGreater),
                        std::move(fnGreaterEq), std::move(fnVirtualLess));
            }

            if (m_objPtr->hasSwapFunction()) {
                ExtSwapFn  fnExtSwap(m_objPtr->getClassName(), m_objPtr);
                InSwapFn  fnInSwap(m_objPtr);
                VirtualExchangeFn  fnVirtualExchange(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualExchangeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualExchange = std::move(
                            *std::dynamic_pointer_cast<VirtualExchangeFn>(itF->second));
                }

                fnInSwap.setStrike(fnVirtualExchange.getStrike());
                fnInSwap.setNewCode(fnVirtualExchange.getNewCode());
                fnInSwap.setAttribute(fnVirtualExchange.getAttribute());
                fnInSwap.setHBefore(fnVirtualExchange.getHBefore());
                fnInSwap.setHBehind(fnVirtualExchange.getHBehind());
                fnInSwap.setCppBefore(fnVirtualExchange.getCppBefore());
                fnInSwap.setCppBehind(fnVirtualExchange.getCppBehind());
                fnVirtualExchange.setStrike({});
                fnVirtualExchange.setNewCode({});
                fnVirtualExchange.setAttribute("");
                fnVirtualExchange.setHBefore("");
                fnVirtualExchange.setHBehind("");
                fnVirtualExchange.setCppBefore("");
                fnVirtualExchange.setCppBehind("");
                setSwapFn(false);
                setSwapFnAdd(std::move(fnExtSwap), std::move(fnInSwap),
                        std::move(fnVirtualExchange));
            }

            if (m_objPtr->hasToStringFunction()) {
                ToStringFn  fnToString(m_objPtr);
                InFromStringFn  fnInFromString(m_objPtr);
                ExtFromStringFn  fnExtFromString(m_objPtr->getClassName(), m_objPtr);
                DeserializeFn  fnDeserialize(m_objPtr);
                VirtualSerializeFn  fnVirtualSerialize(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualSerializeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualSerialize = std::move(
                            *std::dynamic_pointer_cast<VirtualSerializeFn>(
                            itF->second));
                }
                itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eDeserializeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnDeserialize = std::move(*std::dynamic_pointer_cast<DeserializeFn>(
                            itF->second));
                }

                fnToString.setStrike(fnVirtualSerialize.getStrike());
                fnToString.setNewCode(fnVirtualSerialize.getNewCode());
                fnToString.setAttribute(fnVirtualSerialize.getAttribute());
                fnToString.setHBefore(fnVirtualSerialize.getHBefore());
                fnToString.setHBehind(fnVirtualSerialize.getHBehind());
                fnToString.setCppBefore(fnVirtualSerialize.getCppBefore());
                fnToString.setCppBehind(fnVirtualSerialize.getCppBehind());
                fnVirtualSerialize.setStrike({});
                fnVirtualSerialize.setNewCode({});
                fnVirtualSerialize.setAttribute("");
                fnVirtualSerialize.setHBefore("");
                fnVirtualSerialize.setHBehind("");
                fnVirtualSerialize.setCppBefore("");
                fnVirtualSerialize.setCppBehind("");
                fnInFromString.setStrike(fnDeserialize.getStrike());
                fnInFromString.setNewCode(fnDeserialize.getNewCode());
                fnInFromString.setAttribute(fnDeserialize.getAttribute());
                fnInFromString.setHBefore(fnDeserialize.getHBefore());
                fnInFromString.setHBehind(fnDeserialize.getHBehind());
                fnInFromString.setCppBefore(fnDeserialize.getCppBefore());
                fnInFromString.setCppBehind(fnDeserialize.getCppBehind());
                fnDeserialize.setStrike({});
                fnDeserialize.setNewCode({});
                fnDeserialize.setAttribute("");
                fnDeserialize.setHBefore("");
                fnDeserialize.setHBehind("");
                fnDeserialize.setCppBefore("");
                fnDeserialize.setCppBehind("");
                setToStringFn(false);
                setToStringFnAdd(std::move(fnToString), std::move(fnVirtualSerialize),
                        std::move(fnExtFromString), std::move(fnInFromString),
                        std::move(fnDeserialize));
            }
        }
    }
}

void
WtMyClass::baseClass_toggled(bool const  isChecked)
{
    if (!m_objPtr)  return;

    if (isChecked) {
        ClassType const  currVal = ClassType::cppBase;
        ClassType const  oldVal = m_objPtr->getClasstype();
        if (currVal == oldVal)  return;

        m_objPtr->setClasstype(currVal);
        repIsFinalClass();
        m_isFinalClass->hide();

        if (oldVal == ClassType::cppFinal) {
            if (m_objPtr->hasEqFunction()) {
                EqFn  fnEq(m_objPtr->getClassName(), m_objPtr);
                NotEqFn  fnNotEq(m_objPtr->getClassName(), m_objPtr);
                VirtualEqFn  fnVirtualEq(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec;
                Module *  mdPtr = m_objPtr->getParentModulePtr();
                objVec = mdPtr->getEObjectListPtr();
                auto  itEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eEqFn) {
                                if (std::dynamic_pointer_cast<EqFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itEqFn != objVec->end()) {
                    fnEq = std::move(*std::dynamic_pointer_cast<EqFn>(
                            itEqFn->second));
                }
                auto  itNotEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eNotEqFn) {
                                if (std::dynamic_pointer_cast<NotEqFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itNotEqFn != objVec->end()) {
                    fnNotEq = std::move(*std::dynamic_pointer_cast<NotEqFn>(
                            itNotEqFn->second));
                }

                fnVirtualEq.setStrike(fnEq.getStrike());
                fnVirtualEq.setNewCode(fnEq.getNewCode());
                fnVirtualEq.setAttribute(fnEq.getAttribute());
                fnVirtualEq.setHBefore(fnEq.getHBefore());
                fnVirtualEq.setHBehind(fnEq.getHBehind());
                fnVirtualEq.setCppBefore(fnEq.getCppBefore());
                fnVirtualEq.setCppBehind(fnEq.getCppBehind());
                fnEq.setStrike({});
                fnEq.setNewCode({});
                fnEq.setAttribute("");
                fnEq.setHBefore("");
                fnEq.setHBehind("");
                fnEq.setCppBefore("");
                fnEq.setCppBehind("");
                setEqFn(false);
                setEqFnAdd(std::move(fnEq), std::move(fnNotEq), std::move(fnVirtualEq));
            }

            if (m_objPtr->hasLessFunction()) {
                LessFn  fnLess(m_objPtr->getClassName(), m_objPtr);
                LessEqFn  fnLessEq(m_objPtr->getClassName(), m_objPtr);
                GreaterFn  fnGreater(m_objPtr->getClassName(), m_objPtr);
                GreaterEqFn  fnGreaterEq(m_objPtr->getClassName(), m_objPtr);
                VirtualLessFn  fnVirtualLess(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec;
                Module *  mdPtr = m_objPtr->getParentModulePtr();
                objVec = mdPtr->getEObjectListPtr();
                auto  itLessFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eLessFn) {
                                if (std::dynamic_pointer_cast<LessFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itLessFn != objVec->end()) {
                    fnLess = std::move(*std::dynamic_pointer_cast<LessFn>(
                            itLessFn->second));
                }
                auto  itLessEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eLessEqFn) {
                                if (std::dynamic_pointer_cast<LessEqFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itLessEqFn != objVec->end()) {
                    fnLessEq = std::move(*std::dynamic_pointer_cast<LessEqFn>(
                            itLessEqFn->second));
                }
                auto  itGreaterFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eGreaterFn) {
                                if (std::dynamic_pointer_cast<GreaterFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itGreaterFn != objVec->end()) {
                    fnGreater = std::move(*std::dynamic_pointer_cast<GreaterFn>(
                            itGreaterFn->second));
                }
                auto  itGreaterEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eGreaterEqFn) {
                                if (std::dynamic_pointer_cast<GreaterEqFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itGreaterEqFn != objVec->end()) {
                    fnGreaterEq = std::move(*std::dynamic_pointer_cast<GreaterEqFn>(
                            itGreaterEqFn->second));
                }

                fnVirtualLess.setStrike(fnLess.getStrike());
                fnVirtualLess.setNewCode(fnLess.getNewCode());
                fnVirtualLess.setAttribute(fnLess.getAttribute());
                fnVirtualLess.setHBefore(fnLess.getHBefore());
                fnVirtualLess.setHBehind(fnLess.getHBehind());
                fnVirtualLess.setCppBefore(fnLess.getCppBefore());
                fnVirtualLess.setCppBehind(fnLess.getCppBehind());
                fnLess.setStrike({});
                fnLess.setNewCode({});
                fnLess.setAttribute("");
                fnLess.setHBefore("");
                fnLess.setHBehind("");
                fnLess.setCppBefore("");
                fnLess.setCppBehind("");
                setLessFn(false);
                setLessFnAdd(std::move(fnLess), std::move(fnLessEq), std::move(fnGreater),
                        std::move(fnGreaterEq), std::move(fnVirtualLess));
            }

            if (m_objPtr->hasSwapFunction()) {
                ExtSwapFn  fnExtSwap(m_objPtr->getClassName(), m_objPtr);
                InSwapFn  fnInSwap(m_objPtr);
                VirtualExchangeFn  fnVirtualExchange(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eInSwapFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnInSwap = std::move(*std::dynamic_pointer_cast<InSwapFn>(
                            itF->second));
                }

                Module *  mdPtr = m_objPtr->getParentModulePtr();
                objVec = mdPtr->getEObjectListPtr();
                auto  itExtSwapFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eExtSwapFn) {
                                if (std::dynamic_pointer_cast<ExtSwapFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itExtSwapFn != objVec->end()) {
                    fnExtSwap = std::move(*std::dynamic_pointer_cast<ExtSwapFn>(
                            itExtSwapFn->second));
                }

                fnVirtualExchange.setStrike(fnInSwap.getStrike());
                fnVirtualExchange.setNewCode(fnInSwap.getNewCode());
                fnVirtualExchange.setAttribute(fnInSwap.getAttribute());
                fnVirtualExchange.setHBefore(fnInSwap.getHBefore());
                fnVirtualExchange.setHBehind(fnInSwap.getHBehind());
                fnVirtualExchange.setCppBefore(fnInSwap.getCppBefore());
                fnVirtualExchange.setCppBehind(fnInSwap.getCppBehind());
                fnInSwap.setStrike({});
                fnInSwap.setNewCode({});
                fnInSwap.setAttribute("");
                fnInSwap.setHBefore("");
                fnInSwap.setHBehind("");
                fnInSwap.setCppBefore("");
                fnInSwap.setCppBehind("");
                setSwapFn(false);
                setSwapFnAdd(std::move(fnExtSwap), std::move(fnInSwap),
                        std::move(fnVirtualExchange));
            }

            if (m_objPtr->hasToStringFunction()) {
                ToStringFn  fnToString(m_objPtr);
                InFromStringFn  fnInFromString(m_objPtr);
                ExtFromStringFn  fnExtFromString(m_objPtr->getClassName(), m_objPtr);
                DeserializeFn  fnDeserialize(m_objPtr);
                VirtualSerializeFn  fnVirtualSerialize(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eToStringFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnToString = std::move(*std::dynamic_pointer_cast<ToStringFn>(
                            itF->second));
                }
                itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eInFromStringFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnInFromString = std::move(*std::dynamic_pointer_cast<InFromStringFn>(
                            itF->second));
                }

                Module *  mdPtr = m_objPtr->getParentModulePtr();
                objVec = mdPtr->getEObjectListPtr();
                auto  itExt = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eExtFromStringFn) {
                                if (std::dynamic_pointer_cast<ExtFromStringFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itExt != objVec->end()) {
                    fnExtFromString = std::move(*std::dynamic_pointer_cast<ExtFromStringFn>(
                            itExt->second));
                }

                fnVirtualSerialize.setStrike(fnToString.getStrike());
                fnVirtualSerialize.setNewCode(fnToString.getNewCode());
                fnVirtualSerialize.setAttribute(fnToString.getAttribute());
                fnVirtualSerialize.setHBefore(fnToString.getHBefore());
                fnVirtualSerialize.setHBehind(fnToString.getHBehind());
                fnVirtualSerialize.setCppBefore(fnToString.getCppBefore());
                fnVirtualSerialize.setCppBehind(fnToString.getCppBehind());
                fnToString.setStrike({});
                fnToString.setNewCode({});
                fnToString.setAttribute("");
                fnToString.setHBefore("");
                fnToString.setHBehind("");
                fnToString.setCppBefore("");
                fnToString.setCppBehind("");
                fnDeserialize.setStrike(fnInFromString.getStrike());
                fnDeserialize.setNewCode(fnInFromString.getNewCode());
                fnDeserialize.setAttribute(fnInFromString.getAttribute());
                fnDeserialize.setHBefore(fnInFromString.getHBefore());
                fnDeserialize.setHBehind(fnInFromString.getHBehind());
                fnDeserialize.setCppBefore(fnInFromString.getCppBefore());
                fnDeserialize.setCppBehind(fnInFromString.getCppBehind());
                fnInFromString.setStrike({});
                fnInFromString.setNewCode({});
                fnInFromString.setAttribute("");
                fnInFromString.setHBefore("");
                fnInFromString.setHBehind("");
                fnInFromString.setCppBefore("");
                fnInFromString.setCppBehind("");
                setToStringFn(false);
                setToStringFnAdd(std::move(fnToString), std::move(fnVirtualSerialize),
                        std::move(fnExtFromString), std::move(fnInFromString),
                        std::move(fnDeserialize));
            }
        } else {
            if (m_objPtr->hasEqFunction()) {
                EqFn  fnEq(m_objPtr->getClassName(), m_objPtr);
                NotEqFn  fnNotEq(m_objPtr->getClassName(), m_objPtr);
                VirtualEqFn  fnVirtualEq(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualEqFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualEq = std::move(*std::dynamic_pointer_cast<VirtualEqFn>(
                            itF->second));
                }

                setEqFn(false);
                setEqFnAdd(std::move(fnEq), std::move(fnNotEq), std::move(fnVirtualEq));
            }

            if (m_objPtr->hasLessFunction()) {
                LessFn  fnLess(m_objPtr->getClassName(), m_objPtr);
                LessEqFn  fnLessEq(m_objPtr->getClassName(), m_objPtr);
                GreaterFn  fnGreater(m_objPtr->getClassName(), m_objPtr);
                GreaterEqFn  fnGreaterEq(m_objPtr->getClassName(), m_objPtr);
                VirtualLessFn  fnVirtualLess(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualLessFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualLess = std::move(*std::dynamic_pointer_cast<VirtualLessFn>(
                            itF->second));
                }

                setLessFn(false);
                setLessFnAdd(std::move(fnLess), std::move(fnLessEq), std::move(fnGreater),
                        std::move(fnGreaterEq), std::move(fnVirtualLess));
            }

            if (m_objPtr->hasSwapFunction()) {
                ExtSwapFn  fnExtSwap(m_objPtr->getClassName(), m_objPtr);
                InSwapFn  fnInSwap(m_objPtr);
                VirtualExchangeFn  fnVirtualExchange(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualExchangeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualExchange = std::move(
                            *std::dynamic_pointer_cast<VirtualExchangeFn>(itF->second));
                }

                setSwapFn(false);
                setSwapFnAdd(std::move(fnExtSwap), std::move(fnInSwap),
                        std::move(fnVirtualExchange));
            }

            if (m_objPtr->hasToStringFunction()) {
                ToStringFn  fnToString(m_objPtr);
                InFromStringFn  fnInFromString(m_objPtr);
                ExtFromStringFn  fnExtFromString(m_objPtr->getClassName(), m_objPtr);
                DeserializeFn  fnDeserialize(m_objPtr);
                VirtualSerializeFn  fnVirtualSerialize(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualSerializeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualSerialize = std::move(
                            *std::dynamic_pointer_cast<VirtualSerializeFn>(
                            itF->second));
                }
                itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eDeserializeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnDeserialize = std::move(*std::dynamic_pointer_cast<DeserializeFn>(
                            itF->second));
                }

                setToStringFn(false);
                setToStringFnAdd(std::move(fnToString), std::move(fnVirtualSerialize),
                        std::move(fnExtFromString), std::move(fnInFromString),
                        std::move(fnDeserialize));
            }
        }
    }
}

void
WtMyClass::inheritClass_toggled(bool const  isChecked)
{
    if (!m_objPtr)  return;

    if (isChecked) {
        ClassType const  currVal = ClassType::cppInherit;
        ClassType const  oldVal = m_objPtr->getClasstype();
        if (currVal == oldVal)  return;

        m_objPtr->setClasstype(currVal);
        repIsFinalClass();
        m_isFinalClass->show();

        if (oldVal == ClassType::cppBase) {
            if (m_objPtr->hasEqFunction()) {
                EqFn  fnEq(m_objPtr->getClassName(), m_objPtr);
                NotEqFn  fnNotEq(m_objPtr->getClassName(), m_objPtr);
                VirtualEqFn  fnVirtualEq(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualEqFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualEq = std::move(*std::dynamic_pointer_cast<VirtualEqFn>(
                            itF->second));
                }

                setEqFn(false);
                setEqFnAdd(std::move(fnEq), std::move(fnNotEq), std::move(fnVirtualEq));
            }

            if (m_objPtr->hasLessFunction()) {
                LessFn  fnLess(m_objPtr->getClassName(), m_objPtr);
                LessEqFn  fnLessEq(m_objPtr->getClassName(), m_objPtr);
                GreaterFn  fnGreater(m_objPtr->getClassName(), m_objPtr);
                GreaterEqFn  fnGreaterEq(m_objPtr->getClassName(), m_objPtr);
                VirtualLessFn  fnVirtualLess(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualLessFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualLess = std::move(*std::dynamic_pointer_cast<VirtualLessFn>(
                            itF->second));
                }

                setLessFn(false);
                setLessFnAdd(std::move(fnLess), std::move(fnLessEq), std::move(fnGreater),
                        std::move(fnGreaterEq), std::move(fnVirtualLess));
            }

            if (m_objPtr->hasSwapFunction()) {
                ExtSwapFn  fnExtSwap(m_objPtr->getClassName(), m_objPtr);
                InSwapFn  fnInSwap(m_objPtr);
                VirtualExchangeFn  fnVirtualExchange(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualExchangeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualExchange = std::move(
                            *std::dynamic_pointer_cast<VirtualExchangeFn>(itF->second));
                }

                setSwapFn(false);
                setSwapFnAdd(std::move(fnExtSwap), std::move(fnInSwap),
                        std::move(fnVirtualExchange));
            }

            if (m_objPtr->hasToStringFunction()) {
                ToStringFn  fnToString(m_objPtr);
                InFromStringFn  fnInFromString(m_objPtr);
                ExtFromStringFn  fnExtFromString(m_objPtr->getClassName(), m_objPtr);
                DeserializeFn  fnDeserialize(m_objPtr);
                VirtualSerializeFn  fnVirtualSerialize(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eVirtualSerializeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnVirtualSerialize = std::move(
                            *std::dynamic_pointer_cast<VirtualSerializeFn>(
                            itF->second));
                }
                itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eDeserializeFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnDeserialize = std::move(*std::dynamic_pointer_cast<DeserializeFn>(
                            itF->second));
                }

                setToStringFn(false);
                setToStringFnAdd(std::move(fnToString), std::move(fnVirtualSerialize),
                        std::move(fnExtFromString), std::move(fnInFromString),
                        std::move(fnDeserialize));
            }
        } else {
            if (m_objPtr->hasEqFunction()) {
                EqFn  fnEq(m_objPtr->getClassName(), m_objPtr);
                NotEqFn  fnNotEq(m_objPtr->getClassName(), m_objPtr);
                VirtualEqFn  fnVirtualEq(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec;
                Module *  mdPtr = m_objPtr->getParentModulePtr();
                objVec = mdPtr->getEObjectListPtr();
                auto  itEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eEqFn) {
                                if (std::dynamic_pointer_cast<EqFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itEqFn != objVec->end()) {
                    fnEq = std::move(*std::dynamic_pointer_cast<EqFn>(
                            itEqFn->second));
                }

                fnVirtualEq.setStrike(fnEq.getStrike());
                fnVirtualEq.setNewCode(fnEq.getNewCode());
                fnVirtualEq.setAttribute(fnEq.getAttribute());
                fnVirtualEq.setHBefore(fnEq.getHBefore());
                fnVirtualEq.setHBehind(fnEq.getHBehind());
                fnVirtualEq.setCppBefore(fnEq.getCppBefore());
                fnVirtualEq.setCppBehind(fnEq.getCppBehind());
                fnEq.setStrike({});
                fnEq.setNewCode({});
                fnEq.setAttribute("");
                fnEq.setHBefore("");
                fnEq.setHBehind("");
                fnEq.setCppBefore("");
                fnEq.setCppBehind("");
                setEqFn(false);
                setEqFnAdd(std::move(fnEq), std::move(fnNotEq), std::move(fnVirtualEq));
            }

            if (m_objPtr->hasLessFunction()) {
                LessFn  fnLess(m_objPtr->getClassName(), m_objPtr);
                LessEqFn  fnLessEq(m_objPtr->getClassName(), m_objPtr);
                GreaterFn  fnGreater(m_objPtr->getClassName(), m_objPtr);
                GreaterEqFn  fnGreaterEq(m_objPtr->getClassName(), m_objPtr);
                VirtualLessFn  fnVirtualLess(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec;
                Module *  mdPtr = m_objPtr->getParentModulePtr();
                objVec = mdPtr->getEObjectListPtr();
                auto  itLessFn = std::find_if(objVec->begin(), objVec->end(), [this](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eLessFn) {
                                if (std::dynamic_pointer_cast<LessFn>(val.second)->
                                        getParentClassPtr() == m_objPtr) {
                                    return true;
                                } else {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                        });
                if (itLessFn != objVec->end()) {
                    fnLess = std::move(*std::dynamic_pointer_cast<LessFn>(
                            itLessFn->second));
                }

                fnVirtualLess.setStrike(fnLess.getStrike());
                fnVirtualLess.setNewCode(fnLess.getNewCode());
                fnVirtualLess.setAttribute(fnLess.getAttribute());
                fnVirtualLess.setHBefore(fnLess.getHBefore());
                fnVirtualLess.setHBehind(fnLess.getHBehind());
                fnVirtualLess.setCppBefore(fnLess.getCppBefore());
                fnVirtualLess.setCppBehind(fnLess.getCppBehind());
                fnLess.setStrike({});
                fnLess.setNewCode({});
                fnLess.setAttribute("");
                fnLess.setHBefore("");
                fnLess.setHBehind("");
                fnLess.setCppBefore("");
                fnLess.setCppBehind("");
                setLessFn(false);
                setLessFnAdd(std::move(fnLess), std::move(fnLessEq), std::move(fnGreater),
                        std::move(fnGreaterEq), std::move(fnVirtualLess));
            }

            if (m_objPtr->hasSwapFunction()) {
                ExtSwapFn  fnExtSwap(m_objPtr->getClassName(), m_objPtr);
                InSwapFn  fnInSwap(m_objPtr);
                VirtualExchangeFn  fnVirtualExchange(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eInSwapFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnInSwap = std::move(*std::dynamic_pointer_cast<InSwapFn>(
                            itF->second));
                }

                fnVirtualExchange.setStrike(fnInSwap.getStrike());
                fnVirtualExchange.setNewCode(fnInSwap.getNewCode());
                fnVirtualExchange.setAttribute(fnInSwap.getAttribute());
                fnVirtualExchange.setHBefore(fnInSwap.getHBefore());
                fnVirtualExchange.setHBehind(fnInSwap.getHBehind());
                fnVirtualExchange.setCppBefore(fnInSwap.getCppBefore());
                fnVirtualExchange.setCppBehind(fnInSwap.getCppBehind());
                fnInSwap.setStrike({});
                fnInSwap.setNewCode({});
                fnInSwap.setAttribute("");
                fnInSwap.setHBefore("");
                fnInSwap.setHBehind("");
                fnInSwap.setCppBefore("");
                fnInSwap.setCppBehind("");
                setSwapFn(false);
                setSwapFnAdd(std::move(fnExtSwap), std::move(fnInSwap),
                        std::move(fnVirtualExchange));
            }

            if (m_objPtr->hasToStringFunction()) {
                ToStringFn  fnToString(m_objPtr);
                InFromStringFn  fnInFromString(m_objPtr);
                ExtFromStringFn  fnExtFromString(m_objPtr->getClassName(), m_objPtr);
                DeserializeFn  fnDeserialize(m_objPtr);
                VirtualSerializeFn  fnVirtualSerialize(m_objPtr);

                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                        m_objPtr->getEObjectPtr();
                auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eToStringFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnToString = std::move(*std::dynamic_pointer_cast<ToStringFn>(
                            itF->second));
                }
                itF = std::find_if(objVec->begin(), objVec->end(), [](
                        std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                            if (val.first == Etype::eInFromStringFn) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itF != objVec->end()) {
                    fnInFromString = std::move(*std::dynamic_pointer_cast<InFromStringFn>(
                            itF->second));
                }

                fnVirtualSerialize.setStrike(fnToString.getStrike());
                fnVirtualSerialize.setNewCode(fnToString.getNewCode());
                fnVirtualSerialize.setAttribute(fnToString.getAttribute());
                fnVirtualSerialize.setHBefore(fnToString.getHBefore());
                fnVirtualSerialize.setHBehind(fnToString.getHBehind());
                fnVirtualSerialize.setCppBefore(fnToString.getCppBefore());
                fnVirtualSerialize.setCppBehind(fnToString.getCppBehind());
                fnToString.setStrike({});
                fnToString.setNewCode({});
                fnToString.setAttribute("");
                fnToString.setHBefore("");
                fnToString.setHBehind("");
                fnToString.setCppBefore("");
                fnToString.setCppBehind("");
                fnDeserialize.setStrike(fnInFromString.getStrike());
                fnDeserialize.setNewCode(fnInFromString.getNewCode());
                fnDeserialize.setAttribute(fnInFromString.getAttribute());
                fnDeserialize.setHBefore(fnInFromString.getHBefore());
                fnDeserialize.setHBehind(fnInFromString.getHBehind());
                fnDeserialize.setCppBefore(fnInFromString.getCppBefore());
                fnDeserialize.setCppBehind(fnInFromString.getCppBehind());
                fnInFromString.setStrike({});
                fnInFromString.setNewCode({});
                fnInFromString.setAttribute("");
                fnInFromString.setHBefore("");
                fnInFromString.setHBehind("");
                fnInFromString.setCppBefore("");
                fnInFromString.setCppBehind("");
                setToStringFn(false);
                setToStringFnAdd(std::move(fnToString), std::move(fnVirtualSerialize),
                        std::move(fnExtFromString), std::move(fnInFromString),
                        std::move(fnDeserialize));
            }

        }
    }
}

void
WtMyClass::mulInhClassConnect()
{
    QAction *  actAdd = new QAction(tr("Add New"));
    QAction *  actDelete = new QAction(tr("Delete"));
    actAdd->setParent(this);
    actDelete->setParent(this);
    QAction *  actSpt = new QAction;
    actSpt->setSeparator(true);
    QAction *  actUp = new QAction(tr("Up"));
    QAction *  actDown = new QAction(tr("Down"));
    QAction *  actMoveTo = new QAction(tr("Move To Row"));
    actSpt->setParent(this);
    actUp->setParent(this);
    actDown->setParent(this);
    actMoveTo->setParent(this);
    m_mulInhClassView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_mulInhClassView->addAction(actAdd);
    m_mulInhClassView->addAction(actDelete);
    m_mulInhClassView->addAction(actSpt);
    m_mulInhClassView->addAction(actUp);
    m_mulInhClassView->addAction(actDown);
    m_mulInhClassView->addAction(actMoveTo);

    connect(actAdd, &QAction::triggered,
            this, &WtMyClass::mulInhClass_Add_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtMyClass::mulInhClass_Delete_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtMyClass::mulInhClass_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtMyClass::mulInhClass_Down_triggered);
    connect(actMoveTo, &QAction::triggered,
            this, &WtMyClass::mulInhClass_MoveTo_triggered);

    connect(m_mulInhClassView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtMyClass::mulInhClass_itemDelegate_closeEditor);

    m_mulInhClassView->setItemDelegateForColumn(1, new ComboBoxDelegate);
    connect(m_mulInhClassView->itemDelegateForColumn(1),
            &QAbstractItemDelegate::closeEditor,
            this, &WtMyClass::mulInhClass_itemDgtForCol_closeEditor);
}

void
WtMyClass::mulInhClass_Add_triggered()
{
    if (!m_objPtr)  return;

    std::string const  initBase("NewBase__cls");
    m_objPtr->appendMulInhClass({ initBase, Purview::purPublic, false });

    QStandardItem *  item1 = new QStandardItem(QString::fromStdString(initBase));
    QStandardItem *  item2 = new QStandardItem;
    QStandardItem *  item3 = new QStandardItem;
    item2->setData(QVariant("public"), Qt::EditRole | Qt::DisplayRole);
    item3->setData(QVariant(false), Qt::EditRole | Qt::DisplayRole);
    QList<QStandardItem *>  items;
    items << item1 << item2 << item3;
    m_mulInhClassModel->appendRow(items);

    if (m_mulInhClassModel->rowCount() == 1) {
        m_mulInhClassView->setCurrentIndex(m_mulInhClassModel->index(0, 0));
    }
}

void
WtMyClass::mulInhClass_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_mulInhClassView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        m_mulInhClassModel->removeRows(row, 1);
        m_objPtr->deleteMulInhClass(row);
    }
}

void
WtMyClass::mulInhClass_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_mulInhClassView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        m_objPtr->swapMulInhClass(row, row - 1);

        auto const  item = m_mulInhClassModel->takeRow(row);
        m_mulInhClassModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_mulInhClassView->setCurrentIndex(idx);
    }
}

void
WtMyClass::mulInhClass_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_mulInhClassView->currentIndex();
    int const  row = index.row();
    int const  count = m_mulInhClassModel->rowCount();
    if (index.isValid() && count > 1 && row != count - 1) {
        m_objPtr->swapMulInhClass(row, row + 1);

        auto const  item = m_mulInhClassModel->takeRow(row + 1);
        m_mulInhClassModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_mulInhClassView->setCurrentIndex(idx);
    }
}

void
WtMyClass::mulInhClass_MoveTo_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_mulInhClassView->currentIndex();
    int const  count = m_mulInhClassModel->rowCount();
    size_t  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        size_t  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (ok) {
            if (movetoRow > 0)  movetoRow--;
            if (movetoRow >= count)  movetoRow = count - 1;
            if (currRow != movetoRow) {
                m_objPtr->moveMulInhClass(currRow, movetoRow);

                repMulInhClass();
                QModelIndex const  idx = index.sibling(static_cast<int>(movetoRow),
                        index.column());
                m_mulInhClassView->setCurrentIndex(idx);
            }
        }
    }
}

void
WtMyClass::mulInhClass_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_mulInhClassView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  currMul = m_objPtr->getMulInhClass()[row];
        std::string const  currVal =
                m_mulInhClassModel->data(index).toString().toUtf8().toStdString();

        if (index.column() == 0) {
            std::string const  oldVal = std::get<0>(currMul);
            std::get<0>(currMul) = currVal;
            m_objPtr->updateMulInhClass(currMul, row);
            auto const  newMul = m_objPtr->getMulInhClass()[row];
            std::string const  newVal = std::get<0>(newMul);

            if (newVal != currVal) {
                m_mulInhClassModel->setData(index, QVariant(QString::fromStdString(newVal)));
            }
        } else if (index.column() == 2) {
            bool const  bValue = m_mulInhClassModel->data(index).toBool();
            std::get<2>(currMul) = bValue;
            m_objPtr->updateMulInhClass(currMul, row);
        }
    }
}

void
WtMyClass::mulInhClass_itemDgtForCol_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_mulInhClassView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  currMul = m_objPtr->getMulInhClass()[row];
        std::string const  newVal = m_mulInhClassModel->data(index)
                .toString().toUtf8().toStdString();
        if (newVal == "public") {
            std::get<1>(currMul) = Purview::purPublic;
        } else if (newVal == "protected") {
            std::get<1>(currMul) = Purview::purProtected;
        } else {
            std::get<1>(currMul) = Purview::purPrivate;
        }
        m_objPtr->updateMulInhClass(currMul, row);
    }
}

void
WtMyClass::templateConnect()
{
    QAction *  actAdd = new QAction(tr("Add New"));
    QAction *  actDelete = new QAction(tr("Delete"));
    actAdd->setParent(this);
    actDelete->setParent(this);
    QAction *  actSpt = new QAction;
    actSpt->setSeparator(true);
    QAction *  actUp = new QAction(tr("Up"));
    QAction *  actDown = new QAction(tr("Down"));
    QAction *  actMoveTo = new QAction(tr("Move To Row"));
    actSpt->setParent(this);
    actUp->setParent(this);
    actDown->setParent(this);
    actMoveTo->setParent(this);
    m_templateView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_templateView->addAction(actAdd);
    m_templateView->addAction(actDelete);
    m_templateView->addAction(actSpt);
    m_templateView->addAction(actUp);
    m_templateView->addAction(actDown);
    m_templateView->addAction(actMoveTo);

    connect(actAdd, &QAction::triggered,
            this, &WtMyClass::template_Add_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtMyClass::template_Delete_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtMyClass::template_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtMyClass::template_Down_triggered);
    connect(actMoveTo, &QAction::triggered,
            this, &WtMyClass::template_MoveTo_triggered);

    connect(m_templateView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtMyClass::template_itemDelegate_closeEditor);
}

void
WtMyClass::template_Add_triggered()
{
    if (!m_objPtr)  return;

    auto  currVal = m_objPtr->getClassTparam();
    Tpl  tpl;
    currVal.push_back(tpl);
    m_objPtr->setClassTparam(currVal);

    QList<QStandardItem *>  items;
    QStandardItem *  item1 = new QStandardItem(QString::fromStdString(tpl.getTypename()));
    QStandardItem *  item2 = new QStandardItem(QString::fromStdString(tpl.getTName()));
    items << item1 << item2;
    m_templateModel->appendRow(items);
    if (m_templateModel->rowCount() == 1) {
        m_templateView->setCurrentIndex(m_templateModel->index(0, 0));
    }
}

void
WtMyClass::template_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_templateView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  currVal = m_objPtr->getClassTparam();
        currVal.erase(currVal.begin() + row);
        m_objPtr->setClassTparam(currVal);

        m_templateModel->removeRows(row, 1);
    }
}

void
WtMyClass::template_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_templateView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        auto  currVal = m_objPtr->getClassTparam();
        std::swap(currVal[row], currVal[row - 1]);
        m_objPtr->setClassTparam(currVal);

        auto const  item = m_templateModel->takeRow(row);
        m_templateModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_templateView->setCurrentIndex(idx);
    }
}

void
WtMyClass::template_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_templateView->currentIndex();
    int const  count = m_templateModel->rowCount();
    int const  row = index.row();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  currVal = m_objPtr->getClassTparam();
        std::swap(currVal[row], currVal[row + 1]);
        m_objPtr->setClassTparam(currVal);

        auto const  item = m_templateModel->takeRow(row + 1);
        m_templateModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_templateView->setCurrentIndex(idx);
    }
}

void
WtMyClass::template_MoveTo_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_templateView->currentIndex();
    int const  count = m_templateModel->rowCount();
    int const  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        int  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (ok) {
            if (movetoRow > 0)  movetoRow--;
            if (movetoRow >= count)  movetoRow = count - 1;
            if (currRow != movetoRow) {
                auto  currVal = m_objPtr->getClassTparam();
                auto const  dVal = currVal[currRow];
                currVal.erase(currVal.begin() + currRow);
                currVal.insert(currVal.begin() + movetoRow, dVal);
                m_objPtr->setClassTparam(currVal);

                repTemplateClass();
                const QModelIndex  idx = index.sibling(movetoRow, index.column());
                m_templateView->setCurrentIndex(idx);
            }
        }
    }
}

void
WtMyClass::template_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_templateView->currentIndex();
    if (index.isValid()) {
        auto  paraTpl = m_objPtr->getClassTparam();
        int const  idx = index.row();
        std::string const  currVal =
                m_templateModel->data(index).toString().toUtf8().toStdString();

        switch (index.column()) {
        case 0:
            {
                paraTpl[idx].setTypename(currVal);
                m_objPtr->setClassTparam(paraTpl);
                const auto  newVal = m_objPtr->getClassTparam()[idx].getTypename();

                if (currVal != newVal) {
                    m_templateModel->setData(index,
                            QVariant(QString::fromStdString(newVal)));
                }
            }
            break;
        case 1:
            {
                auto const  oldVal = paraTpl[idx].getTName();
                paraTpl[idx].setTName(currVal);
                m_objPtr->setClassTparam(paraTpl);
                auto const  newVal = m_objPtr->getClassTparam()[idx].getTName();

                if (currVal != newVal) {
                    m_templateModel->setData(index,
                            QVariant(QString::fromStdString(newVal)));
                }
            }
            break;
        case 2:
            paraTpl[idx].setDocment(currVal);
            m_objPtr->setClassTparam(paraTpl);
            break;
        case 3:
            {
                paraTpl[idx].setDefalutValue(currVal);
                m_objPtr->setClassTparam(paraTpl);
                auto const  newVal = m_objPtr->getClassTparam()[idx].getDefalutValue();

                if (currVal != newVal) {
                    m_templateModel->setData(index,
                            QVariant(QString::fromStdString(newVal)));
                }
            }
            break;
        }
    }
}

void
WtMyClass::friendClassConnect()
{
    QAction *  actAdd = new QAction(tr("Add New"));
    QAction *  actDelete = new QAction(tr("Delete"));
    actAdd->setParent(this);
    actDelete->setParent(this);
    QAction *  actSpt = new QAction;
    actSpt->setSeparator(true);
    QAction *  actUp = new QAction(tr("Up"));
    QAction *  actDown = new QAction(tr("Down"));
    QAction *  actMoveTo = new QAction(tr("Move To Row"));
    actSpt->setParent(this);
    actUp->setParent(this);
    actDown->setParent(this);
    actMoveTo->setParent(this);
    m_friendClassView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_friendClassView->addAction(actAdd);
    m_friendClassView->addAction(actDelete);
    m_friendClassView->addAction(actSpt);
    m_friendClassView->addAction(actUp);
    m_friendClassView->addAction(actDown);
    m_friendClassView->addAction(actMoveTo);

    connect(actAdd, &QAction::triggered,
            this, &WtMyClass::friendClass_Add_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtMyClass::friendClass_Delete_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtMyClass::friendClass_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtMyClass::friendClass_Down_triggered);
    connect(actMoveTo, &QAction::triggered,
            this, &WtMyClass::friendClass_MoveTo_triggered);

    connect(m_friendClassView->itemDelegate(),
            &QAbstractItemDelegate::closeEditor,
            this, &WtMyClass::friendClass_itemDelegate_closeEditor);
}

void
WtMyClass::friendClass_Add_triggered()
{
    if (!m_objPtr)  return;

    auto  currVal = m_objPtr->getFriendClassName();
    std::string const  fName("MyClass1_1");
    currVal.push_back(fName);
    m_objPtr->setFriendClassName(currVal);

    QStandardItem *  item = new QStandardItem(QString::fromStdString(fName));
    m_friendClassModel->appendRow(item);
    if (m_friendClassModel->rowCount() == 1) {
        m_friendClassView->setCurrentIndex(m_friendClassModel->index(0, 0));
    }
}

void
WtMyClass::friendClass_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_friendClassView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        auto  currVal = m_objPtr->getFriendClassName();
        currVal.erase(currVal.begin() + row);
        m_objPtr->setFriendClassName(currVal);

        m_friendClassModel->removeRows(row, 1);
    }
}

void
WtMyClass::friendClass_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_friendClassView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        auto  currVal = m_objPtr->getFriendClassName();
        std::swap(currVal[row], currVal[row - 1]);
        m_objPtr->setFriendClassName(currVal);

        auto const  item = m_friendClassModel->takeRow(row);
        m_friendClassModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_friendClassView->setCurrentIndex(idx);
    }
}

void
WtMyClass::friendClass_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_friendClassView->currentIndex();
    int const  count = m_friendClassModel->rowCount();
    int const  row = index.row();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  currVal = m_objPtr->getFriendClassName();
        std::swap(currVal[row], currVal[row + 1]);
        m_objPtr->setFriendClassName(currVal);

        auto const  item = m_friendClassModel->takeRow(row + 1);
        m_friendClassModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_friendClassView->setCurrentIndex(idx);
    }
}

void
WtMyClass::friendClass_MoveTo_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_friendClassView->currentIndex();
    int const  count = m_friendClassModel->rowCount();
    int const  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        int  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (ok) {
            if (movetoRow > 0)  movetoRow--;
            if (movetoRow >= count)  movetoRow = count - 1;
            if (currRow != movetoRow) {
                auto  currVal = m_objPtr->getFriendClassName();
                auto const  dVal = currVal[currRow];
                currVal.erase(currVal.begin() + currRow);
                currVal.insert(currVal.begin() + movetoRow, dVal);
                m_objPtr->setFriendClassName(currVal);

                repFriendClass();
                const QModelIndex  idx = index.sibling(movetoRow, index.column());
                m_friendClassView->setCurrentIndex(idx);
            }
        }
    }
}

void
WtMyClass::friendClass_itemDelegate_closeEditor()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_friendClassView->currentIndex();
    if (index.isValid()) {
        auto  currVec = m_objPtr->getFriendClassName();
        int const  idx = index.row();
        std::string const  currVal =
                m_friendClassModel->data(index).toString().toUtf8().toStdString();

        switch (index.column()) {
        case 0:
            {
                currVec[idx] = currVal;
                m_objPtr->setFriendClassName(currVec);
                const auto  newVal = m_objPtr->getFriendClassName()[idx];

                if (currVal != newVal) {
                    m_friendClassModel->setData(index,
                            QVariant(QString::fromStdString(newVal)));
                }
            }
            break;
        }
    }
}

void
WtMyClass::baseClassPrarm_editingFinished()
{
    if (!m_objPtr)  return;

    std::string const  currVal = m_baseClassPrarm->text().toUtf8().toStdString();
    std::string const  oldVal = m_objPtr->getBaseClassPrarm();
    if (currVal == oldVal)  return;

    m_objPtr->setBaseClassPrarm(currVal);
    std::string const  newVal = m_objPtr->getBaseClassPrarm();
    if (newVal != currVal) {
        m_baseClassPrarm->setText(QString::fromStdString(newVal));
    }
}

void
WtMyClass::classNameInherit_editingFinished()
{
    if (!m_objPtr)  return;

    std::string const  currVal = m_classNameInherit->text().toUtf8().toStdString();
    std::pair<std::string, bool>  oldVal = m_objPtr->getBaseClassFirst();
    if (currVal == oldVal.first)  return;

    oldVal.first = currVal;
    m_objPtr->setBaseClassFirst(oldVal);
    std::pair<std::string, bool> const  newVal = m_objPtr->getBaseClassFirst();
    if (newVal.first != currVal) {
        m_classNameInherit->setText(QString::fromStdString(newVal.first));
    }
}

void
WtMyClass::inheritIsVirtual_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    std::pair<std::string, bool>  oldVal = m_objPtr->getBaseClassFirst();
    if (currVal == oldVal.second)  return;

    oldVal.second = currVal;
    m_objPtr->setBaseClassFirst(oldVal);
    std::pair<std::string, bool> const  newVal = m_objPtr->getBaseClassFirst();
    if (newVal.second != currVal) {
        m_inheritIsVirtual->setChecked(newVal.second);
    }
}

void
WtMyClass::baseId_toggled(bool const  isChecked)
{
    if (!m_objPtr)  return;

    if (isChecked) {
        InheritID const  currVal = InheritID::baseId;
        m_objPtr->setInheritID(currVal);
    }
}

void
WtMyClass::borthId_toggled(bool const  isChecked)
{
    if (!m_objPtr)  return;

    if (isChecked) {
        InheritID const  currVal = InheritID::borthId;
        m_objPtr->setInheritID(currVal);
    }
}

void
WtMyClass::inheritId_toggled(bool const  isChecked)
{
    if (!m_objPtr)  return;

    if (isChecked) {
        InheritID const  currVal = InheritID::inheritId;
        m_objPtr->setInheritID(currVal);
    }
}

void
WtMyClass::hasEqFunction_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->hasEqFunction();
    if (!currVal && currVal == oldVal)  return;

    if (currVal) {
        if (currVal == oldVal) {
            setEqFn(false);
            setEqFn(true);
        } else {
            setEqFn(true);
        }
    } else {
        setEqFn(false);
    }
}

void
WtMyClass::hasLessFunction_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->hasLessFunction();
    if (!currVal && currVal == oldVal)  return;

    if (currVal) {
        bool const  eqVal = m_objPtr->hasEqFunction();
        if (!eqVal) {
            m_hasEqFunction->setChecked(true);
        }
        if (currVal == oldVal) {
            setLessFn(false);
            setLessFn(true);
        } else {
            setLessFn(true);
        }
    } else {
        setLessFn(false);
    }
}

void
WtMyClass::hasSwapFunction_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->hasSwapFunction();
    if (!currVal && currVal == oldVal)  return;

    if (currVal) {
        if (currVal == oldVal) {
            setSwapFn(false);
            setSwapFn(true);
        } else {
            setSwapFn(true);
        }
    } else {
        setSwapFn(false);
    }
}

void
WtMyClass::hasToStringFunction_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    bool const  oldVal = m_objPtr->hasToStringFunction();
    if (!currVal && currVal == oldVal)  return;

    if (currVal) {
        if (currVal == oldVal) {
            setToStringFn(false);
            setToStringFn(true);
        } else {
            setToStringFn(true);
        }
    } else {
        setToStringFn(false);
    }
}

void
WtMyClass::fieldIdIsToString_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

    bool  currVal = false;
    if (status == Qt::Checked) {
        currVal = true;
    }
    m_objPtr->setUpdateToString(currVal);
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
    repFieldIdRegular();
    repFieldIdToString();
    repFieldAction();

    m_fieldModel->appendRow(items);

    int const  count = m_fieldModel->rowCount();
    QVariant const  filedIdx = QVariant::fromValue(QString::fromStdString(
            std::to_string(count - 1)));
    m_fieldModel->setHeaderData(count - 1, Qt::Vertical, filedIdx,
            Qt::EditRole | Qt::DisplayRole);
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
        repFieldIdRegular();
        repFieldIdToString();
        repFieldAction();

        m_fieldModel->insertRow(row, items);

        int const  count = m_fieldModel->rowCount();
        for (int  i = row; i < count; ++i) {
            QVariant const  newHeader = QVariant::fromValue(
                    QString::fromStdString(std::to_string(i)));
            m_fieldModel->setHeaderData(i, Qt::Vertical, newHeader,
                    Qt::EditRole | Qt::DisplayRole);
        }
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

        for (int i = 0; i < count; ++i) {
            QVariant const  oldHeader = m_fieldModel->headerData(i,
                    Qt::Vertical, Qt::DisplayRole);
            if (std::stoi(oldHeader.toString().toUtf8().toStdString()) > row) {
                QVariant const  newHeader = QVariant::fromValue(
                        QString::fromStdString(std::to_string(std::stoi(
                        oldHeader.toString().toUtf8().toStdString()) - 1)));
                m_fieldModel->setHeaderData(i, Qt::Vertical, newHeader,
                        Qt::EditRole | Qt::DisplayRole);
            }
        }

        field_selectChanged();

        repFieldIdRegular();
        repFieldId();
        repFieldIdToString();

        repFieldAction();
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
        Field  newData = *rawDataVec[row];
        std::string const  oldName = rawDataVec[row]->getFieldName();
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

        int const  count = m_fieldModel->rowCount();
        for (int  i = row; i < count; ++i) {
            QVariant const  newHeader = QVariant::fromValue(
                    QString::fromStdString(std::to_string(i)));
            m_fieldModel->setHeaderData(i, Qt::Vertical, newHeader,
                    Qt::EditRole | Qt::DisplayRole);
        }

        repFieldIdRegular();
        repFieldIdToString();
        repFieldAction();
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

        QVariant const  headerIdx1(QString::fromStdString(std::to_string(row - 1)));
        QVariant const  headerIdx2(QString::fromStdString(std::to_string(row)));
        m_fieldModel->setHeaderData(row - 1, Qt::Vertical, headerIdx1,
                Qt::EditRole | Qt::DisplayRole);
        m_fieldModel->setHeaderData(row, Qt::Vertical, headerIdx2,
                Qt::EditRole | Qt::DisplayRole);

        repFieldIdRegular();
        repFieldId();
        repFieldIdToString();

        repFieldAction();
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

        QVariant const  headerIdx1(QString::fromStdString(std::to_string(row)));
        QVariant const  headerIdx2(QString::fromStdString(std::to_string(row + 1)));
        m_fieldModel->setHeaderData(row, Qt::Vertical, headerIdx1,
                Qt::EditRole | Qt::DisplayRole);
        m_fieldModel->setHeaderData(row + 1, Qt::Vertical, headerIdx2,
                Qt::EditRole | Qt::DisplayRole);

        repFieldIdRegular();
        repFieldId();
        repFieldIdToString();

        repFieldAction();
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

        repField();
        QModelIndex const  idx = index.sibling(static_cast<int>(movetoRow), index.column());
        m_fieldView->setCurrentIndex(idx);

        repFieldId();
        repFieldIdRegular();
        repFieldIdToString();

        repFieldAction();
    }
}

void
WtMyClass::field_BeforBehind_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldView->currentIndex();
    int const  row = index.row();
    if (index.isValid()) {
        Field  rawData = *m_objPtr->getField()[row];

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
        Field  rawData = *m_objPtr->getField()[row];
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

        repFieldIdRegular();
        repFieldId();
        repFieldIdToString();
        repFieldAction();
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

        Field const  fd = *m_objPtr->getField()[index.row()];
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
        Field  fd = *m_objPtr->getField()[row];
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
        Field  fd = *m_objPtr->getField()[row];
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
        Field  fd = *m_objPtr->getField()[row];
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
        Field  fd = *m_objPtr->getField()[row];
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
        Field  fd = *m_objPtr->getField()[row];
        fd.setMutable(currVal);
        m_objPtr->updateField(std::move(fd), row);
    }
}

void
WtMyClass::fieldIdRegularConnect()
{
    QAction *  actUp = new QAction(tr("Up"));
    QAction *  actDown = new QAction(tr("Down"));
    QAction *  actMoveTo = new QAction(tr("Move To Row"));
    actUp->setParent(this);
    actDown->setParent(this);
    actMoveTo->setParent(this);
    m_fieldIdRegularView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_fieldIdRegularView->addAction(actUp);
    m_fieldIdRegularView->addAction(actDown);
    m_fieldIdRegularView->addAction(actMoveTo);

    connect(actUp, &QAction::triggered,
            this, &WtMyClass::fieldIdRegular_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtMyClass::fieldIdRegular_Down_triggered);
    connect(actMoveTo, &QAction::triggered,
            this, &WtMyClass::fieldIdRegular_MoveTo_triggered);
}

void
WtMyClass::fieldIdRegular_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldIdRegularView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && index.row() != 0) {
        auto  dVal = m_objPtr->getStyleField();
        std::swap(dVal[row], dVal[row - 1]);
        m_objPtr->setStyleField(dVal);

        auto const  item = m_fieldIdRegularModel->takeRow(row);
        m_fieldIdRegularModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_fieldIdRegularView->setCurrentIndex(idx);
    }
}

void
WtMyClass::fieldIdRegular_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldIdRegularView->currentIndex();
    int const  row = index.row();
    const int  count = m_fieldIdRegularModel->rowCount();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  dVal = m_objPtr->getStyleField();
        std::swap(dVal[index.row()], dVal[index.row() + 1]);
        m_objPtr->setStyleField(dVal);

        auto const  item = m_fieldIdRegularModel->takeRow(row + 1);
        m_fieldIdRegularModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_fieldIdRegularView->setCurrentIndex(idx);
    }
}

void
WtMyClass::fieldIdRegular_MoveTo_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldIdRegularView->currentIndex();
    int const  count = m_fieldIdRegularModel->rowCount();
    int const  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        int  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (ok) {
            if (movetoRow > 0)  movetoRow--;
            if (movetoRow >= count)  movetoRow = count - 1;
            if (currRow != movetoRow) {
                auto  nsp = m_objPtr->getStyleField();
                auto const  dval = nsp[currRow];
                nsp.erase(nsp.begin() + currRow);
                nsp.insert(nsp.begin() + movetoRow, dval);
                m_objPtr->setStyleField(nsp);

                repFieldIdRegular();
                QModelIndex const  idx = index.sibling(movetoRow, index.column());
                m_fieldIdRegularView->setCurrentIndex(idx);
            }
        }
    }
}

void
WtMyClass::fieldIdConnect()
{
    QAction *  actAdd = new QAction(tr("Add New"));
    QAction *  actDelete = new QAction(tr("Delete"));
    actAdd->setParent(this);
    actDelete->setParent(this);
    QAction *  actSpt = new QAction;
    actSpt->setSeparator(true);
    QAction *  actUp = new QAction(tr("Up"));
    QAction *  actDown = new QAction(tr("Down"));
    QAction *  actMoveTo = new QAction(tr("Move To Row"));
    actSpt->setParent(this);
    actUp->setParent(this);
    actDown->setParent(this);
    actMoveTo->setParent(this);
    m_fieldIdView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_fieldIdView->addAction(actAdd);
    m_fieldIdView->addAction(actDelete);
    m_fieldIdView->addAction(actSpt);
    m_fieldIdView->addAction(actUp);
    m_fieldIdView->addAction(actDown);
    m_fieldIdView->addAction(actMoveTo);

    connect(actAdd, &QAction::triggered,
            this, &WtMyClass::fieldId_Add_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtMyClass::fieldId_Delete_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtMyClass::fieldId_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtMyClass::fieldId_Down_triggered);
    connect(actMoveTo, &QAction::triggered,
            this, &WtMyClass::fieldId_MoveTo_triggered);
}

void
WtMyClass::fieldId_Add_triggered()
{
    if (!m_objPtr)  return;

    bool  ok = false;
    int  inputIdx = QInputDialog::getInt(this, "Input Field Index",
                "Field Index: ", 0, 0, 2000000, 1, &ok);
    if (ok) {
        auto  sID = m_objPtr->getIDField();
        sID.push_back(inputIdx);
        m_objPtr->setIDField(sID);
        repFieldId();
    }
}

void
WtMyClass::fieldId_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldIdView->currentIndex();
    if (index.isValid()) {
        auto  sID = m_objPtr->getIDField();
        sID.erase(sID.begin() + index.row());
        m_objPtr->setIDField(sID);
        repFieldId();
    }
}

void
WtMyClass::fieldId_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldIdView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        auto  dVal = m_objPtr->getIDField();
        std::swap(dVal[row], dVal[row - 1]);
        m_objPtr->setIDField(dVal);

        auto const  item = m_fieldIdModel->takeRow(row);
        m_fieldIdModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_fieldIdView->setCurrentIndex(idx);
    }
}

void
WtMyClass::fieldId_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldIdView->currentIndex();
    int const  row = index.row();
    int const  count = m_fieldIdModel->rowCount();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  dVal = m_objPtr->getIDField();
        std::swap(dVal[row], dVal[row + 1]);
        m_objPtr->setIDField(dVal);

        auto const  item = m_fieldIdModel->takeRow(row + 1);
        m_fieldIdModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_fieldIdView->setCurrentIndex(idx);
    }
}

void
WtMyClass::fieldId_MoveTo_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldIdView->currentIndex();
    int const  count = m_fieldIdModel->rowCount();
    int const  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        int  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (ok) {
            if (movetoRow > 0)  movetoRow--;
            if (movetoRow >= count)  movetoRow = count - 1;
            if (currRow != movetoRow) {
                auto  nsp = m_objPtr->getIDField();
                const auto  dval = nsp[currRow];
                nsp.erase(nsp.begin() + currRow);
                nsp.insert(nsp.begin() + movetoRow, dval);
                m_objPtr->setIDField(nsp);

                repFieldId();
                QModelIndex const  idx = index.sibling(movetoRow, index.column());
                m_fieldIdView->setCurrentIndex(idx);
            }
        }
    }
}

void
WtMyClass::fieldIdToStringConnect()
{
    QAction *  actAdd = new QAction(tr("Add New"));
    QAction *  actDelete = new QAction(tr("Delete"));
    actAdd->setParent(this);
    actDelete->setParent(this);
    QAction *  actSpt = new QAction;
    actSpt->setSeparator(true);
    QAction *  actUp = new QAction(tr("Up"));
    QAction *  actDown = new QAction(tr("Down"));
    QAction *  actMoveTo = new QAction(tr("Move To Row"));
    actSpt->setParent(this);
    actUp->setParent(this);
    actDown->setParent(this);
    actMoveTo->setParent(this);
    m_fieldIdToStringView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_fieldIdToStringView->addAction(actAdd);
    m_fieldIdToStringView->addAction(actDelete);
    m_fieldIdToStringView->addAction(actSpt);
    m_fieldIdToStringView->addAction(actUp);
    m_fieldIdToStringView->addAction(actDown);
    m_fieldIdToStringView->addAction(actMoveTo);

    connect(actAdd, &QAction::triggered,
            this, &WtMyClass::fieldIdToString_Add_triggered);
    connect(actDelete, &QAction::triggered,
            this, &WtMyClass::fieldIdToString_Delete_triggered);
    connect(actUp, &QAction::triggered,
            this, &WtMyClass::fieldIdToString_Up_triggered);
    connect(actDown, &QAction::triggered,
            this, &WtMyClass::fieldIdToString_Down_triggered);
    connect(actMoveTo, &QAction::triggered,
            this, &WtMyClass::fieldIdToString_MoveTo_triggered);
}

void
WtMyClass::fieldIdToString_Add_triggered()
{
    if (!m_objPtr)  return;

    bool  ok = false;
    int  inputIdx = QInputDialog::getInt(this, "Input Field Index",
                "Field Index: ", 0, 0, 2000000, 1, &ok);
    if (ok) {
        auto  sID = m_objPtr->getSerzField();
        sID.push_back(inputIdx);
        m_objPtr->setSerzField(sID);
        repFieldIdToString();
    }
}

void
WtMyClass::fieldIdToString_Delete_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldIdToStringView->currentIndex();
    if (index.isValid()) {
        auto  sID = m_objPtr->getSerzField();
        sID.erase(sID.begin() + index.row());
        m_objPtr->setSerzField(sID);
        repFieldIdToString();
    }
}

void
WtMyClass::fieldIdToString_Up_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldIdToStringView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && row != 0) {
        auto  dVal = m_objPtr->getSerzField();
        std::swap(dVal[row], dVal[row - 1]);
        m_objPtr->setSerzField(dVal);

        auto const  item = m_fieldIdToStringModel->takeRow(row);
        m_fieldIdToStringModel->insertRow(row - 1, item);
        QModelIndex const  idx = index.sibling(row - 1, index.column());
        m_fieldIdToStringView->setCurrentIndex(idx);
    }
}

void
WtMyClass::fieldIdToString_Down_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldIdToStringView->currentIndex();
    int const  count = m_fieldIdToStringModel->rowCount();
    int const  row = index.row();
    if (index.isValid() && count > 1 && row != count - 1) {
        auto  dVal = m_objPtr->getSerzField();
        std::swap(dVal[row], dVal[row + 1]);
        m_objPtr->setSerzField(dVal);

        auto const  item = m_fieldIdToStringModel->takeRow(row + 1);
        m_fieldIdToStringModel->insertRow(row, item);
        QModelIndex const  idx = index.sibling(row + 1, index.column());
        m_fieldIdToStringView->setCurrentIndex(idx);
    }
}

void
WtMyClass::fieldIdToString_MoveTo_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldIdToStringView->currentIndex();
    int const  count = m_fieldIdToStringModel->rowCount();
    int const  currRow = index.row();
    if (index.isValid() && count > 1) {
        bool  ok = false;
        int  movetoRow = QInputDialog::getInt(this, "Move To Row",
                    "Move To Row: ", 0, 0, 2000000, 1, &ok);
        if (ok) {
            if (movetoRow > 0)  movetoRow--;
            if (movetoRow >= count)  movetoRow = count - 1;
            if (currRow != movetoRow) {
                auto  nsp = m_objPtr->getSerzField();
                auto const  dval = nsp[currRow];
                nsp.erase(nsp.begin() + currRow);
                nsp.insert(nsp.begin() + movetoRow, dval);
                m_objPtr->setSerzField(nsp);

                repFieldIdToString();
                QModelIndex const  idx = index.sibling(movetoRow, index.column());
                m_fieldIdToStringView->setCurrentIndex(idx);
            }
        }
    }
}

void
WtMyClass::fieldActionConnect()
{
    QAction *  actSpt1 = new QAction;
    actSpt1->setSeparator(true);
    actSpt1->setParent(this);
    QAction *  actAddActionFalse = new QAction(tr("Add Action"));
    QAction *  actDeleteAction = new QAction(tr("Delete Action"));
    QAction *  actInsertBeforBehind = new QAction(tr("Insert && Follow"));
    actAddActionFalse->setParent(this);
    actDeleteAction->setParent(this);
    actInsertBeforBehind->setParent(this);
    m_fieldActionView->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_fieldActionView->addAction(actAddActionFalse);
    m_fieldActionView->addAction(actDeleteAction);
    m_fieldActionView->addAction(actSpt1);
    m_fieldActionView->addAction(actInsertBeforBehind);

    connect(actAddActionFalse, &QAction::triggered,
            this, &WtMyClass::fieldAction_AddActionFalse_triggered);
    connect(actDeleteAction, &QAction::triggered,
            this, &WtMyClass::fieldAction_DeleteAction_triggered);
    connect(actInsertBeforBehind, &QAction::triggered,
            this, &WtMyClass::fieldAction_InsBeforBehind_triggered);

    connect(m_fieldActionView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this, &WtMyClass::fieldAction_selectChanged);
}

void
WtMyClass::fieldAction_selectChanged()
{
    if (!m_objPtr)  return;

    QModelIndex const  index = m_fieldActionView->currentIndex();
    int const  row = index.row();
    if (index.isValid() && index.parent().isValid()) {
        m_fieldActionInline->setCheckable(true);
        m_fieldActionNoexcept->setCheckable(true);
        m_fieldActionVirtual->setCheckable(true);
        m_fieldActionOverride->setCheckable(true);
        m_fieldActionFinal->setCheckable(true);

        m_fieldActionDoc->setReadOnly(false);
        m_fieldActionAttribute->setReadOnly(false);

        std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  fnVec =
                m_objPtr->getField()[index.parent().row()]->getActionFnRef();
        std::shared_ptr<ActFn>  fn = fnVec[row].second;
        m_fieldActionInline->setChecked(fn->isInline());
        m_fieldActionNoexcept->setChecked(fn->isNoexcept());
        m_fieldActionVirtual->setChecked(fn->isVirtual());
        m_fieldActionOverride->setChecked(fn->isOverride());
        m_fieldActionFinal->setChecked(fn->isFinal());

        m_fieldActionAutoCode->setPlainText(QString::fromStdString(fn->updateAutoCode()));
        m_fieldActionDoc->setHtml(QString::fromStdString(fn->getDocment()));
        m_fieldActionAttribute->setText(QString::fromStdString(fn->getAttribute()));

        repFieldActionDelIdx();
        repFieldActionInsertIdx();

        if (m_fieldActionInsertIdxModel->rowCount() == 0) {
            m_fieldActionInsertCode->setReadOnly(true);
            m_fieldActionInsertCode->clear();
        } else {
            m_fieldActionInsertCode->setReadOnly(false);
            m_fieldActionInsertIdxView->setCurrentIndex(
                    m_fieldActionInsertIdxModel->index(0, 0));
            currFieldActionInsertIdx();
        }
    } else {
        m_fieldActionInline->setChecked(false);
        m_fieldActionNoexcept->setChecked(false);
        m_fieldActionVirtual->setChecked(false);
        m_fieldActionOverride->setChecked(false);
        m_fieldActionFinal->setChecked(false);

        if (index.isValid() && !index.parent().isValid()) {
            m_fieldActionDoc->setReadOnly(false);
            m_fieldActionAttribute->setReadOnly(false);

            const std::string  doc = m_objPtr->getField()[row]->getDocment();
            const std::string  attrVal = m_objPtr->getField()[row]->getAttribute();
            m_fieldActionDoc->setHtml(QString::fromStdString(doc));
            m_fieldActionAttribute->setText(QString::fromStdString(attrVal));
        } else {
            m_fieldActionDoc->setReadOnly(true);
            m_fieldActionDoc->clear();
            m_fieldActionAttribute->setReadOnly(true);
            m_fieldActionAttribute->clear();
        }
        m_fieldActionDelIdxModel->removeRows(0, m_fieldActionDelIdxModel->rowCount());
        m_fieldActionInsertIdxModel->removeRows(0, m_fieldActionInsertIdxModel->rowCount());

        m_fieldActionInsertCode->setReadOnly(true);
        m_fieldActionInline->setCheckable(false);
        m_fieldActionNoexcept->setCheckable(false);
        m_fieldActionVirtual->setCheckable(false);
        m_fieldActionOverride->setCheckable(false);
        m_fieldActionFinal->setCheckable(false);

        m_fieldActionAutoCode->clear();
        m_fieldActionInsertCode->clear();
    }
}

void
WtMyClass::fieldAction_AddActionFalse_triggered()
{
    if (!m_objPtr)  return;

    fieldAction_AddAction(false);
}

void
WtMyClass::fieldAction_AddAction(bool const  isInline)
{
    if (!m_objPtr)  return;

    QStandardItem *  itemRoot = m_fieldActionModel->invisibleRootItem();
    QModelIndex const  idxRoot = m_fieldActionModel->indexFromItem(itemRoot);

    QModelIndex  index = m_fieldActionView->currentIndex();
    QModelIndex  idxOperator = index.parent();
    if (index.isValid()) {
        if (index.column() != 0) {
            index = index.sibling(index.row(), 0);
        }
        if (idxOperator == idxRoot) {
            idxOperator = index;
        }
        int const  idx = idxOperator.row();

        QString const  g0("get           () const");
        QString const  g1("setCopy         (const T &)");
        QString const  g2("setMove         (T &&)");
        QString const  g3("setConstValue   (const T)");
        QString const  g4("setMutValue     (T)");
        QString const  g5("is            () const");
        QString const  g6("has           () const");
        bool  ok = false;
        QStringList  actions;

        std::string const  currFieldType = m_objPtr->getField()[idx]->getTypeName();
        if (currFieldType == "bool") {
            actions << g5 << g6 << g3 << g4 << g1 << g2 << g0;
        } else if (xu::isPrmType(currFieldType)) {
            actions << g0 << g3 << g4 << g1 << g2 << g5 << g6;
        } else {
            actions << g0 << g1 << g2 << g3 << g4 << g5 << g6;
        }

        QString  myAction = QInputDialog::getItem(this,
                    tr("QInputDialog::getItem()"),
                    tr("Action:"), actions, 0, false, &ok);
        if (ok && !myAction.isEmpty()) {
            if (myAction == g0) {
                myAction = "get";
            } else if (myAction == g1) {
                myAction = "setCopy";
            } else if (myAction == g2) {
                myAction = "setMove";
            } else if (myAction == g3) {
                myAction = "setConstValue";
            } else if (myAction == g4) {
                myAction = "setMutValue";
            } else if (myAction == g5) {
                myAction = "is";
            } else if (myAction == g6) {
                myAction = "has";
            }
            Action const  action = fromActionString(
                    myAction.toUtf8().toStdString());
            Field  fdFs = *m_objPtr->getField()[idx];
            std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  fnVec =
                    fdFs.getActionFnRef();

            auto  itF = std::find_if(fnVec.begin(), fnVec.end(), [action](
                    std::pair<Action, std::shared_ptr<ActFn>> const &  val) -> bool {
                if (action == val.first) {
                    return true;
                } else {
                    return false;
                }
            });

            if (itF == fnVec.end()) {
                std::pair<Action, std::shared_ptr<ActFn>>  actFn;
                actFn.first = action;
                switch (action) {
                case Action::get :
                    actFn.second = std::make_shared<ActGetFn>(m_objPtr,
                            m_objPtr->getFieldRef()[idx].get());
                    break;
                case Action::setCopy :
                    actFn.second = std::make_shared<ActSetCopyFn>(m_objPtr,
                            m_objPtr->getFieldRef()[idx].get());
                    break;
                case Action::setMove :
                    actFn.second = std::make_shared<ActSetMoveFn>(m_objPtr,
                            m_objPtr->getFieldRef()[idx].get());
                    break;
                case Action::setConstValue :
                    actFn.second = std::make_shared<ActSetConstValueFn>(m_objPtr,
                            m_objPtr->getFieldRef()[idx].get());
                    break;
                case Action::setMutValue :
                    actFn.second = std::make_shared<ActSetMutValueFn>(m_objPtr,
                            m_objPtr->getFieldRef()[idx].get());
                    break;
                case Action::is :
                    actFn.second = std::make_shared<ActIsFn>(m_objPtr,
                            m_objPtr->getFieldRef()[idx].get());
                    break;
                case Action::has :
                    actFn.second = std::make_shared<ActHasFn>(m_objPtr,
                            m_objPtr->getFieldRef()[idx].get());
                    break;
                case Action::none :
                    break;
                }
                if (isInline) {
                    actFn.second->setInline(true);
                }
                fnVec.push_back(actFn);
                m_objPtr->updateField(fdFs, idx);

                QStandardItem *  itemAct1 = new QStandardItem(
                        QString::fromStdString("    " + toActionString(action)));
                QStandardItem *  itemAct2 = new QStandardItem(
                        QString::fromStdString(actFn.second->declLabel()));
                QList<QStandardItem *>  itemActs;
                itemActs << itemAct1 << itemAct2;
                m_fieldActionModel->itemFromIndex(idxOperator)->appendRow(itemActs);
                if (!m_fieldActionView->isExpanded(idxOperator)) {
                    m_fieldActionView->expand(idxOperator);
                }
                fieldAction_selectChanged();
            }
        }
    }
}

void
WtMyClass::fieldAction_DeleteAction_triggered()
{
    if (!m_objPtr)  return;

    QModelIndex  index = m_fieldActionView->currentIndex();
    if (index.isValid() && index.parent().isValid()) {
        if (index.column() != 0) {
            index = index.sibling(index.row(), 0);
        }

        QStandardItem *  itemParent = m_fieldActionModel
                ->itemFromIndex(index.parent());
        itemParent->removeRow(index.row());

        int const  idx = index.parent().row();
        Field  fdF = *m_objPtr->getField()[idx];
        std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  fnVec =
                fdF.getActionFnRef();
        fnVec.erase(fnVec.begin() + index.row());
        m_objPtr->updateField(fdF, idx);

        m_fieldActionView->setCurrentIndex(index.parent());
    } else if (index.isValid() && !index.parent().isValid()) {
        if (index.column() != 0) {
            index = index.sibling(index.row(), 0);
        }
        int const  idx = index.row();
        Field  fdF = *m_objPtr->getField()[idx];
        fdF.setActionFn({});
        m_objPtr->updateField(fdF, idx);

        m_fieldActionModel->itemFromIndex(index)->removeRows(
                0, m_fieldActionModel->itemFromIndex(index)->rowCount());
    }
}

void
WtMyClass::fieldAction_InsBeforBehind_triggered()
{
    if (!m_objPtr)  return;

}

void
WtMyClass::fieldActionAutoCodeConnect()
{
}

void
WtMyClass::fieldActionDelIdxConnect()
{
}

void
WtMyClass::fieldActionInsertIdxConnect()
{
}

void
WtMyClass::fdActAttribute_editingFinished()
{
    if (!m_objPtr)  return;

}

void
WtMyClass::fdActInline_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

}

void
WtMyClass::fdActNoexcept_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

}

void
WtMyClass::fdActVirtual_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

}

void
WtMyClass::fdActOverride_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

}

void
WtMyClass::fdActFinal_stateChanged(int const  status)
{
    if (!m_objPtr)  return;

}

void
WtMyClass::fdActInsertCode_textChanged()
{
    if (!m_objPtr)  return;

}

void
WtMyClass::repDefCtor()
{
    if (!m_objPtr)  return;

    m_hasDefCtor->setChecked(m_objPtr->hasDefCtor());
}

void
WtMyClass::repCopyCtor()
{
    if (!m_objPtr)  return;

    m_hasCopyCtor->setChecked(m_objPtr->hasCopyCtor());
}

void
WtMyClass::repMoveCtor()
{
    if (!m_objPtr)  return;

    m_hasMoveCtor->setChecked(m_objPtr->hasMoveCtor());
}

void
WtMyClass::repDtor()
{
    if (!m_objPtr)  return;

    m_hasDtor->setChecked(m_objPtr->hasDtor());
}

void
WtMyClass::repCopyOpEq()
{
    if (!m_objPtr)  return;

    m_hasCopyOpEq->setChecked(m_objPtr->hasCopyOpEq());
}

void
WtMyClass::repMoveOpEq()
{
    if (!m_objPtr)  return;

    m_hasMoveOpEq->setChecked(m_objPtr->hasMoveOpEq());
}

void
WtMyClass::repInheritIsVirtual()
{
    if (!m_objPtr)  return;

    m_inheritIsVirtual->setChecked(m_objPtr->getBaseClassFirst().second);
}

void
WtMyClass::repIsFinalClass()
{
    if (!m_objPtr)  return;

    m_isFinalClass->setChecked(m_objPtr->isFinalClass());
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
    m_fieldActionAutoCode->setReadOnly(true);
    m_dotH = new CodeEditor;
    new Highlighter(m_dotH->document());
    m_dotH->setReadOnly(true);
    m_dotCpp = new CodeEditor;
    new Highlighter(m_dotCpp->document());
    m_dotCpp->setReadOnly(true);

    m_fieldActionDoc = new QTextEdit;
    new Highlighter(m_fieldActionDoc->document());
    m_fieldActionInsertCode = new CodeEditor;
    new Highlighter(m_fieldActionInsertCode->document());
    m_fieldActionAttribute = new QLineEdit;

    m_replaceClassName = new QLineEdit;
    m_baseClassPrarm = new QLineEdit;

    m_isFinalClass = new QCheckBox(tr("Class isFinal"));
    m_isSetterReturnThis = new QCheckBox(tr("setter is return *this"));
    m_isTemplate = new QCheckBox(tr("is Template Class"));
    m_inheritIsVirtual = new QCheckBox(tr("First Base Class isVirtual"));

    m_fieldIdIsToString = new QCheckBox(tr("Append Field"));

    m_fieldActionInline = new QCheckBox(tr("inline"));
    m_fieldActionVirtual = new QCheckBox(tr("virtual"));
    m_fieldActionOverride = new QCheckBox(tr("override"));
    m_fieldActionFinal = new QCheckBox(tr("final"));
    m_fieldActionNoexcept = new QCheckBox(tr("noexcept"));

    m_hasLessFunction = new QCheckBox(tr("has operator< <= > >="));
    m_hasEqFunction = new QCheckBox(tr("has operator== !="));
    m_hasSwapFunction = new QCheckBox(tr("has swap"));
    m_hasToStringFunction = new QCheckBox(tr("has toString"));

    m_hasDefCtor = new QCheckBox(tr("Default_Ctor"));
    m_hasCopyCtor = new QCheckBox(tr("Copy_Ctor"));
    m_hasMoveCtor = new QCheckBox(tr("Move_Ctor "));
    m_hasDtor = new QCheckBox(tr("~Destructor"));
    m_hasCopyOpEq = new QCheckBox(tr("Copy operator="));
    m_hasMoveOpEq = new QCheckBox(tr("Move operator="));

    m_fieldIsMutable = new QCheckBox(tr("mutable"));
    m_isUpdateFilename = new QCheckBox(tr("Class Name Update Module File Name"));
    m_isImpl = new QCheckBox(tr("Impl Class"));
    m_isInternal = new QCheckBox(tr("is Internal"));
    m_isIndPublicLabel = new QCheckBox(tr("public label"));

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

    m_templateView->setColumnWidth(0, 200);
    m_templateView->setColumnWidth(1, 200);
    m_templateView->setColumnWidth(2, 200);
    m_templateView->setColumnWidth(3, 160);

    m_mulInhClassView = new QTableView;
    m_mulInhClassModel = new QStandardItemModel;
    m_mulInhClassModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Base Class")));
    m_mulInhClassModel->setHorizontalHeaderItem(1,
                        new QStandardItem(tr("Encapsulation")));
    m_mulInhClassModel->setHorizontalHeaderItem(2,
                        new QStandardItem(tr("isVirtual")));
    m_mulInhClassView->setModel(m_mulInhClassModel);

    m_mulInhClassView->setColumnWidth(0, 260);
    m_mulInhClassView->setColumnWidth(1, 125);
    m_mulInhClassView->setColumnWidth(2, 85);

    m_friendClassView = new QTableView;
    m_friendClassModel = new QStandardItemModel;
    m_friendClassModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Friend Class")));
    m_friendClassView->setModel(m_friendClassModel);

    m_friendClassView->setColumnWidth(0, 220);

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

    m_fieldIdRegularView->setColumnWidth(0, 55);
    m_fieldIdRegularView->setColumnWidth(1, 160);

    m_fieldIdView = new QTableView;
    m_fieldIdModel = new QStandardItemModel;
    m_fieldIdModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Index")));
    m_fieldIdModel->setHorizontalHeaderItem(1,
                        new QStandardItem(tr("Field Name")));
    m_fieldIdView->setModel(m_fieldIdModel);
    m_fieldIdView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_fieldIdView->setColumnWidth(0, 55);
    m_fieldIdView->setColumnWidth(1, 160);

    m_fieldIdToStringView = new QTableView;
    m_fieldIdToStringModel = new QStandardItemModel;
    m_fieldIdToStringModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Index")));
    m_fieldIdToStringModel->setHorizontalHeaderItem(1,
                        new QStandardItem(tr("Field Name")));
    m_fieldIdToStringView->setModel(m_fieldIdToStringModel);
    m_fieldIdToStringView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_fieldIdIsToString = new QCheckBox(tr("Append Field"));

    m_fieldIdToStringView->setColumnWidth(0, 55);
    m_fieldIdToStringView->setColumnWidth(1, 160);

    m_fieldActionView = new QTreeView;
    m_fieldActionModel = new QStandardItemModel;
    m_fieldActionModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Field / Action")));
    m_fieldActionModel->setHorizontalHeaderItem(1,
                        new QStandardItem(tr("Function Declaration")));
    m_fieldActionView->setModel(m_fieldActionModel);
    m_fieldActionView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_fieldActionView->setColumnWidth(0, 200);
    m_fieldActionView->setColumnWidth(1, 415);

    m_fieldActionDelIdxView = new QTableView;
    m_fieldActionDelIdxModel = new QStandardItemModel;
    m_fieldActionDelIdxModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Index")));
    m_fieldActionDelIdxView->setModel(m_fieldActionDelIdxModel);
    m_fieldActionDelIdxView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_fieldActionDelIdxView->setColumnWidth(0, 60);

    m_fieldActionInsertIdxView = new QTableView;
    m_fieldActionInsertIdxModel = new QStandardItemModel;
    m_fieldActionInsertIdxModel->setHorizontalHeaderItem(0,
                        new QStandardItem(tr("Index")));
    m_fieldActionInsertIdxView->setModel(m_fieldActionInsertIdxModel);
    m_fieldActionInsertIdxView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_fieldActionInsertIdxView->setColumnWidth(0, 60);
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

    connect(m_replaceClassName, &QLineEdit::editingFinished,
            this, &WtMyClass::replaceClassName_editingFinished);
    connect(m_isFinalClass, &QCheckBox::stateChanged,
            this, &WtMyClass::isFinalClass_stateChanged);
    connect(m_isTemplate, &QCheckBox::stateChanged,
            this, &WtMyClass::isTemplate_stateChanged);
    connect(m_isUpdateFilename, &QCheckBox::stateChanged,
            this, &WtMyClass::isUpdateFilename_stateChanged);
    connect(m_isImpl, &QCheckBox::stateChanged,
            this, &WtMyClass::isImpl_stateChanged);
    connect(m_isSetterReturnThis, &QCheckBox::stateChanged,
            this, &WtMyClass::isSetterReturnThis_stateChanged);
    connect(m_isInternal, &QCheckBox::stateChanged,
            this, &WtMyClass::isInternal_stateChanged);
    connect(m_isIndPublicLabel, &QCheckBox::stateChanged,
            this, &WtMyClass::isIndPublicLabel_stateChanged);

    connect(m_hasDefCtor, &QCheckBox::stateChanged,
            this, &WtMyClass::hasDefCtor_stateChanged);
    connect(m_hasCopyCtor, &QCheckBox::stateChanged,
            this, &WtMyClass::hasCopyCtor_stateChanged);
    connect(m_hasMoveCtor, &QCheckBox::stateChanged,
            this, &WtMyClass::hasMoveCtor_stateChanged);
    connect(m_hasDtor, &QCheckBox::stateChanged,
            this, &WtMyClass::hasDtor_stateChanged);
    connect(m_hasCopyOpEq, &QCheckBox::stateChanged,
            this, &WtMyClass::hasCopyOpEq_stateChanged);
    connect(m_hasMoveOpEq, &QCheckBox::stateChanged,
            this, &WtMyClass::hasMoveOpEq_stateChanged);

    connect(m_finalClass, &QRadioButton::toggled,
            this, &WtMyClass::finalClass_toggled);
    connect(m_baseClass, &QRadioButton::toggled,
            this, &WtMyClass::baseClass_toggled);
    connect(m_inheritClass, &QRadioButton::toggled,
            this, &WtMyClass::inheritClass_toggled);

    templateConnect();
    friendClassConnect();

    connect(m_baseClassPrarm, &QLineEdit::editingFinished,
            this, &WtMyClass::baseClassPrarm_editingFinished);
    connect(m_classNameInherit, &QLineEdit::editingFinished,
            this, &WtMyClass::classNameInherit_editingFinished);

    connect(m_inheritIsVirtual, &QCheckBox::stateChanged,
            this, &WtMyClass::inheritIsVirtual_stateChanged);

    connect(m_baseId, &QRadioButton::toggled,
            this, &WtMyClass::baseId_toggled);
    connect(m_borthId, &QRadioButton::toggled,
            this, &WtMyClass::borthId_toggled);
    connect(m_inheritId, &QRadioButton::toggled,
            this, &WtMyClass::inheritId_toggled);

    mulInhClassConnect();

    fieldConnect();

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

    connect(m_hasLessFunction, &QCheckBox::stateChanged,
            this, &WtMyClass::hasLessFunction_stateChanged);
    connect(m_hasEqFunction, &QCheckBox::stateChanged,
            this, &WtMyClass::hasEqFunction_stateChanged);
    connect(m_hasSwapFunction, &QCheckBox::stateChanged,
            this, &WtMyClass::hasSwapFunction_stateChanged);
    connect(m_hasToStringFunction, &QCheckBox::stateChanged,
            this, &WtMyClass::hasToStringFunction_stateChanged);

    connect(m_fieldIdIsToString, &QCheckBox::stateChanged,
            this, &WtMyClass::fieldIdIsToString_stateChanged);

    fieldIdRegularConnect();
    fieldIdConnect();
    fieldIdToStringConnect();

    fieldActionConnect();
    fieldActionAutoCodeConnect();
    fieldActionDelIdxConnect();
    fieldActionInsertIdxConnect();

    connect(m_fieldActionAttribute, &QLineEdit::editingFinished,
            this, &WtMyClass::fdActAttribute_editingFinished);
    connect(m_fieldActionInline, &QCheckBox::stateChanged,
            this, &WtMyClass::fdActInline_stateChanged);
    connect(m_fieldActionNoexcept, &QCheckBox::stateChanged,
            this, &WtMyClass::fdActNoexcept_stateChanged);
    connect(m_fieldActionVirtual, &QCheckBox::stateChanged,
            this, &WtMyClass::fdActVirtual_stateChanged);
    connect(m_fieldActionOverride, &QCheckBox::stateChanged,
            this, &WtMyClass::fdActOverride_stateChanged);
    connect(m_fieldActionFinal, &QCheckBox::stateChanged,
            this, &WtMyClass::fdActFinal_stateChanged);

    connect(m_fieldActionInsertCode, &CodeEditor::textChanged,
            this, &WtMyClass::fdActInsertCode_textChanged);
}

void
WtMyClass::display_obj()
{
    QVBoxLayout *  vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 3, 0, 0);

    QHBoxLayout *  hboxClass = new QHBoxLayout;
    QHBoxLayout *  hboxLine = new QHBoxLayout;
    QHBoxLayout *  hboxProperty = new QHBoxLayout;
    hboxClass->setContentsMargins(0, 0, 0, 0);
    hboxLine->setContentsMargins(0, 0, 0, 0);
    hboxProperty->setContentsMargins(0, 0, 0, 0);
    vbox->addLayout(hboxClass);
    vbox->addLayout(hboxLine);
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
        QFrame *  tlvline = new QFrame;
        hboxLine->addWidget(tlvline);
        tlvline->setFrameStyle(QFrame::HLine | QFrame::Plain);
        tlvline->setLineWidth(1);
    }
    {
        hboxProperty->addWidget(m_mainTab);
    }

    QSplitter *  spvField = new QSplitter(Qt::Vertical);
    QWidget * spvFieldId = new QWidget;
    spvFieldId->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSplitter *  spvFieldAction = new QSplitter(Qt::Vertical);
    QWidget * spvGeneral = new QWidget;
    spvGeneral->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spvField->setHandleWidth(1);
    spvFieldAction->setHandleWidth(1);
    m_mainTab->addTab(spvField, tr(" Field "));
    m_mainTab->addTab(spvFieldId, tr(" Field_Id "));
    m_mainTab->addTab(spvFieldAction, tr(" Field_Action "));
    m_mainTab->addTab(spvGeneral, tr(" Class_General "));
    m_mainTab->addTab(m_dotH, tr(" .h "));
    m_mainTab->addTab(m_dotCpp, tr(" .cpp "));

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
    {
        QVBoxLayout *  vbox1 = new QVBoxLayout(spvFieldId);
        vbox1->setContentsMargins(0, 0, 0, 0);
        QHBoxLayout *  hbox1 = new QHBoxLayout;
        QHBoxLayout *  hbox2 = new QHBoxLayout;
        hbox1->setContentsMargins(0, 0, 0, 0);
        hbox2->setContentsMargins(0, 0, 0, 0);
        vbox1->addLayout(hbox1);
        vbox1->addLayout(hbox2);

        QSplitter *  fdidSp = new QSplitter;
        fdidSp->setHandleWidth(1);
        hbox1->addWidget(fdidSp);

        QFrame *  fr1 = new QFrame;
        QFrame *  fr2 = new QFrame;
        QFrame *  fr3 = new QFrame;
        fr1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        fr2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        fr3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        fdidSp->addWidget(fr1);
        fdidSp->addWidget(fr2);
        fdidSp->addWidget(fr3);

        QVBoxLayout *  vbox1_1 = new QVBoxLayout(fr1);
        QVBoxLayout *  vbox1_2 = new QVBoxLayout(fr2);
        QVBoxLayout *  vbox1_3 = new QVBoxLayout(fr3);
        vbox1_1->setContentsMargins(0, 0, 0, 0);
        vbox1_2->setContentsMargins(0, 0, 0, 0);
        vbox1_3->setContentsMargins(0, 0, 0, 0);

        QLabel *  label1 = new QLabel(tr("ragular sort"));
        QLabel *  label2 = new QLabel(tr("Id sort"));
        QLabel *  label3 = new QLabel(tr("toString sort"));
        vbox1_1->addWidget(label1);
        vbox1_1->addWidget(m_fieldIdRegularView);
        vbox1_2->addWidget(label2);
        vbox1_2->addWidget(m_fieldIdView);
        vbox1_3->addWidget(label3);
        vbox1_3->addWidget(m_fieldIdIsToString);
        vbox1_3->addWidget(m_fieldIdToStringView);

        hbox2->setAlignment(Qt::AlignLeft);
        hbox2->addWidget(m_hasLessFunction);
        hbox2->addSpacing(15);
        hbox2->addWidget(m_hasEqFunction);
        hbox2->addSpacing(15);
        hbox2->addWidget(m_hasSwapFunction);
        hbox2->addSpacing(15);
        hbox2->addWidget(m_hasToStringFunction);
    }
    {
        QSplitter *  sptr1 = new QSplitter;
        QSplitter *  sptr2 = new QSplitter;
        QSplitter *  sptr3 = new QSplitter;
        sptr1->setHandleWidth(1);
        sptr2->setHandleWidth(1);
        sptr3->setHandleWidth(1);
        spvFieldAction->addWidget(sptr1);
        spvFieldAction->addWidget(sptr2);
        spvFieldAction->addWidget(sptr3);
        spvFieldAction->setStretchFactor(0, 50);
        spvFieldAction->setStretchFactor(1, 15);
        spvFieldAction->setStretchFactor(2, 35);

        QAbstractScrollArea *  faAfr = new QAbstractScrollArea;
        sptr1->addWidget(m_fieldActionView);
        sptr1->addWidget(faAfr);
        sptr1->setStretchFactor(0, 88);
        sptr1->setStretchFactor(1, 12);
        QVBoxLayout *  vbox1 = new QVBoxLayout(faAfr);
        vbox1->setContentsMargins(2, 0, 2, 0);
        vbox1->setAlignment(Qt::AlignTop);
        vbox1->addWidget(m_fieldActionNoexcept);
        vbox1->addWidget(m_fieldActionInline);
        vbox1->addWidget(m_fieldActionVirtual);
        vbox1->addWidget(m_fieldActionOverride);
        vbox1->addWidget(m_fieldActionFinal);
        QLabel *  label0 = new QLabel(tr("Attribute"));
        vbox1->addWidget(label0);
        vbox1->addWidget(m_fieldActionAttribute);

        QFrame *  spt2fr = new QFrame;
        QVBoxLayout *  spt2vbox = new QVBoxLayout(spt2fr);
        spt2vbox->setContentsMargins(0, 0, 0, 0);
        QLabel *  labelSp2 = new QLabel(tr("Delete Row"));
        spt2vbox->addWidget(labelSp2);
        spt2vbox->addWidget(m_fieldActionDelIdxView);
        sptr2->addWidget(spt2fr);
        sptr2->addWidget(m_fieldActionAutoCode);
        sptr2->setStretchFactor(0, 12);
        sptr2->setStretchFactor(1, 88);

        QFrame *  spt3fr = new QFrame;
        QVBoxLayout *  spt3vbox = new QVBoxLayout(spt3fr);
        spt3vbox->setContentsMargins(0, 0, 0, 0);
        QLabel *  labelSp3 = new QLabel(tr("Insert Row"));
        spt3vbox->addWidget(labelSp3);
        spt3vbox->addWidget(m_fieldActionInsertIdxView);
        sptr3->addWidget(spt3fr);
        sptr3->addWidget(m_fieldActionInsertCode);
        sptr3->setStretchFactor(0, 12);
        sptr3->setStretchFactor(1, 88);
    }
    {
        QVBoxLayout *  gVbox = new QVBoxLayout(spvGeneral);
        gVbox->setContentsMargins(0, 0, 0, 0);
        QHBoxLayout *  hbox0 = new QHBoxLayout;
        QHBoxLayout *  hbox1 = new QHBoxLayout;
        QHBoxLayout *  hbox2 = new QHBoxLayout;
        QHBoxLayout *  hbox3 = new QHBoxLayout;
        QHBoxLayout *  hbox4 = new QHBoxLayout;
        QHBoxLayout *  hbox5 = new QHBoxLayout;
        QHBoxLayout *  hbox6 = new QHBoxLayout;
        QHBoxLayout *  hbox7 = new QHBoxLayout;
        QHBoxLayout *  hbox8 = new QHBoxLayout;
        hbox0->setContentsMargins(0, 0, 0, 0);
        hbox1->setContentsMargins(0, 0, 0, 0);
        hbox2->setContentsMargins(0, 0, 0, 0);
        hbox3->setContentsMargins(0, 0, 0, 0);
        hbox4->setContentsMargins(0, 0, 11, 0);
        hbox5->setContentsMargins(0, 0, 0, 0);
        hbox6->setContentsMargins(0, 0, 0, 0);
        hbox7->setContentsMargins(0, 0, 0, 0);
        hbox8->setContentsMargins(0, 0, 0, 0);
        gVbox->addLayout(hbox0);
        gVbox->addLayout(hbox1);
        gVbox->addLayout(hbox2);
        gVbox->addLayout(hbox3);
        gVbox->addLayout(hbox4);
        gVbox->addLayout(hbox5);
        gVbox->addLayout(hbox6);
        gVbox->addLayout(hbox7);
        gVbox->addLayout(hbox8);

        QLabel *  repClassDfLabel = new QLabel(tr("replace class definition"));
        hbox0->addWidget(repClassDfLabel);
        hbox0->addWidget(m_replaceClassName);

        hbox1->setAlignment(Qt::AlignLeft);
        hbox1->addWidget(m_isInternal);
        hbox1->addSpacing(9);
        hbox1->addWidget(m_isIndPublicLabel);
        hbox1->addSpacing(28);
        hbox1->addWidget(m_finalClass);
        hbox1->addSpacing(11);
        hbox1->addWidget(m_baseClass);
        hbox1->addSpacing(11);
        hbox1->addWidget(m_inheritClass);
        hbox1->addSpacing(11);
        hbox1->addWidget(m_isFinalClass);

        hbox2->setAlignment(Qt::AlignLeft);
        hbox2->addWidget(m_isTemplate);
        hbox2->addSpacing(11);
        hbox2->addWidget(m_isSetterReturnThis);
        hbox2->addSpacing(11);
        hbox2->addWidget(m_isUpdateFilename);
        hbox2->addSpacing(11);
        hbox2->addWidget(m_isImpl);

        hbox3->addWidget(m_templateView);

        QLabel *  baseClassLabel = new QLabel(tr("First Base Class"));
        hbox4->addWidget(baseClassLabel);
        hbox4->addWidget(m_classNameInherit);
        hbox4->addSpacing(11);
        hbox4->addWidget(m_inheritIsVirtual);

        hbox5->setAlignment(Qt::AlignLeft);
        hbox5->addWidget(m_baseId);
        hbox5->addSpacing(11);
        hbox5->addWidget(m_borthId);
        hbox5->addSpacing(11);
        hbox5->addWidget(m_inheritId);
        hbox5->addSpacing(18);
        QLabel *  baseClassPrarmLb = new QLabel(tr("Base Class Parameter"));
        hbox5->addWidget(baseClassPrarmLb);
        hbox5->addWidget(m_baseClassPrarm);

        hbox6->addWidget(m_mulInhClassView);
        hbox6->addWidget(m_friendClassView);
        hbox6->setStretch(0, 70);
        hbox6->setStretch(1, 30);

        hbox7->setAlignment(Qt::AlignLeft);
        hbox7->addWidget(m_hasDefCtor);
        hbox7->addSpacing(11);
        hbox7->addWidget(m_hasCopyCtor);
        hbox7->addSpacing(11);
        hbox7->addWidget(m_hasMoveCtor);
        hbox7->addSpacing(11);
        hbox7->addWidget(m_hasDtor);
        hbox7->addSpacing(11);
        hbox7->addWidget(m_hasCopyOpEq);
        hbox7->addSpacing(11);
        hbox7->addWidget(m_hasMoveOpEq);

        hbox8->addWidget(m_docmentClass);
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
    m_fieldIdIsToString->setChecked(m_objPtr->isUpdateToString());

    m_hasLessFunction->setChecked(m_objPtr->hasLessFunction());
    m_hasEqFunction->setChecked(m_objPtr->hasEqFunction());
    m_hasSwapFunction->setChecked(m_objPtr->hasSwapFunction());
    m_hasToStringFunction->setChecked(m_objPtr->hasToStringFunction());

    m_hasDefCtor->setChecked(m_objPtr->hasDefCtor());
    m_hasCopyCtor->setChecked(m_objPtr->hasCopyCtor());
    m_hasMoveCtor->setChecked(m_objPtr->hasMoveCtor());
    m_hasDtor->setChecked(m_objPtr->hasDtor());
    m_hasCopyOpEq->setChecked(m_objPtr->hasCopyOpEq());
    m_hasMoveOpEq->setChecked(m_objPtr->hasMoveOpEq());

    m_replaceClassName->setText(QString::fromStdString(m_objPtr->getReplaceClassName()));
    m_isInternal->setChecked(m_objPtr->isInternal());
    m_isIndPublicLabel->setChecked(m_objPtr->isIndPublicLabel());
    m_isFinalClass->setChecked(m_objPtr->isFinalClass());
    m_isTemplate->setChecked(m_objPtr->isTemplate());
    m_isSetterReturnThis->setChecked(m_objPtr->isSetterReturnThis());
    m_isImpl->setChecked(m_objPtr->isImpl());

    std::pair<std::string, bool> const  baseClassFirst = m_objPtr->getBaseClassFirst();
    m_classNameInherit->setText(QString::fromStdString(baseClassFirst.first));
    m_inheritIsVirtual->setChecked(baseClassFirst.second);

    m_baseClassPrarm->setText(QString::fromStdString(m_objPtr->getBaseClassPrarm()));

    ClassType const  cType = m_objPtr->getClasstype();
    if (cType == ClassType::cppFinal) {
        m_finalClass->setChecked(true);
        m_isFinalClass->hide();
    } else if (cType == ClassType::cppBase) {
        m_baseClass->setChecked(true);
        m_isFinalClass->hide();
    } else {
        m_inheritClass->setChecked(true);
        m_isFinalClass->show();
    }

    InheritID const  inhId = m_objPtr->getInheritID();
    if (inhId == InheritID::baseId) {
        m_baseId->setChecked(true);
    } else if (inhId == InheritID::inheritId) {
        m_inheritId->setChecked(true);
    } else {
        m_borthId->setChecked(true);
    }

    repField();
    field_selectChanged();

    repFieldIdRegular();
    repFieldId();
    repFieldIdToString();

    repFieldAction();
    fieldAction_selectChanged();

    repMulInhClass();
    repTemplateClass();
    repFriendClass();
}

void
WtMyClass::repField()
{
    m_fieldModel->removeRows(0, m_fieldModel->rowCount());
    std::vector<std::shared_ptr<Field>> const  fds = m_objPtr->getField();
    size_t const  fdSize = fds.size();
    for (size_t  i = 0; i < fdSize; ++i) {
        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(QString::fromStdString(
                fds[i]->getFieldName()));
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
                fds[i]->getTypeName()));
        QStandardItem *  item2 = new QStandardItem(QString::fromStdString(
                fds[i]->getDefValue()));
        QStandardItem *  isPtr = new QStandardItem;
        isPtr->setData(QVariant(fds[i]->isPointer()), Qt::EditRole | Qt::DisplayRole);
        items << item0 << item1 << item2 << isPtr;
        m_fieldModel->appendRow(items);

        QVariant const  headerIdx(QString::fromStdString(std::to_string(i)));
        m_fieldModel->setHeaderData(static_cast<int>(i), Qt::Vertical,
                headerIdx, Qt::EditRole | Qt::DisplayRole);
    }
}

void
WtMyClass::repFieldIdRegular()
{
    m_fieldIdRegularModel->removeRows(0, m_fieldIdRegularModel->rowCount());
    int const  colWidth = m_fieldIdRegularView->columnWidth(0);
    std::vector<std::shared_ptr<Field>>  fdVec = m_objPtr->getField();
    std::vector<size_t>  styleID = m_objPtr->getStyleField();
    for (auto const &  it: styleID) {
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
                std::to_string(it)));
        item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *  item2 = new QStandardItem(QString::fromStdString(
                fdVec[it]->getFieldName()));
        QList<QStandardItem *>  items;
        items << item1 << item2;
        m_fieldIdRegularModel->appendRow(items);
    }
    m_fieldIdRegularView->setColumnWidth(0, colWidth);
}

void
WtMyClass::repFieldId()
{
    m_fieldIdModel->removeRows(0, m_fieldIdModel->rowCount());
    const int  colWidth = m_fieldIdView->columnWidth(0);
    std::vector<std::shared_ptr<Field>>  fdVec = m_objPtr->getField();
    std::vector<size_t>  sID = m_objPtr->getIDField();
    for (auto const &  it: sID) {
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
                std::to_string(it)));
        item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *  item2 = new QStandardItem(QString::fromStdString(
                fdVec[it]->getFieldName()));
        QList<QStandardItem *>  items;
        items << item1 << item2;
        m_fieldIdModel->appendRow(items);
    }
    m_fieldIdView->setColumnWidth(0, colWidth);
}

void
WtMyClass::repFieldIdToString()
{
    m_fieldIdToStringModel->removeRows(0, m_fieldIdToStringModel->rowCount());
    const int  colWidth = m_fieldIdToStringView->columnWidth(0);
    std::vector<std::shared_ptr<Field>>  fdVec = m_objPtr->getField();
    std::vector<size_t>  serzID = m_objPtr->getSerzField();
    for (auto const &  it: serzID) {
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(
                std::to_string(it)));
        item1->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *  item2 = new QStandardItem(QString::fromStdString(
                fdVec[it]->getFieldName()));
        QList<QStandardItem *>  items;
        items << item1 << item2;
        m_fieldIdToStringModel->appendRow(items);
    }
    m_fieldIdToStringView->setColumnWidth(0, colWidth);
}

void
WtMyClass::repFieldAction()
{
    m_fieldActionModel->removeRows(0, m_fieldActionModel->rowCount());
    m_fieldActionDelIdxModel->removeRows(0, m_fieldActionDelIdxModel->rowCount());
    m_fieldActionInsertIdxModel->removeRows(0, m_fieldActionInsertIdxModel->rowCount());
    auto  fdF = m_objPtr->getField();
    for (size_t  i = 0; i < fdF.size(); ++i) {
        updateActionTitle(i);

        QStandardItem *  currItem = m_fieldActionModel->item(static_cast<int>(i), 0);
        std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  actFn =
                fdF[i]->getActionFnRef();
        for (auto &  it: actFn) {
            QStandardItem *  itemAct1 = new QStandardItem(QString::fromStdString(
                    "    " + toActionString(it.first)));
            std::string  fnDcl = it.second->declLabel();
            QStandardItem *  itemAct2 = new QStandardItem(QString::fromStdString(fnDcl));
            QList<QStandardItem *>  itemActs;
            itemActs << itemAct1 << itemAct2;
            currItem->appendRow(itemActs);
        }
    }
    m_fieldActionView->expandAll();
    fieldAction_selectChanged();
}

void
WtMyClass::updateActionTitle(size_t const  fieldIdx)
{
    Field  fd = *m_objPtr->getField()[fieldIdx];
    std::string const  tab(8, '-');
    std::string const  fName = std::to_string(fieldIdx) + "  " + fd.getFieldName();
    QStandardItem *  item0 = new QStandardItem(QString::fromStdString(fName));
    QStandardItem *  item1 = new QStandardItem;
    if (fd.isPointer()) {
        item1->setData(QVariant(QString::fromStdString(tab + " " +
                fd.getTypeName() + " * " + tab)), Qt::DisplayRole);
    } else {
        item1->setData(QVariant(QString::fromStdString(tab + " " +
                fd.getTypeName() + " " + tab)), Qt::DisplayRole);
    }

    int const  width0 = m_fieldActionView->columnWidth(0);
    int const  width1 = m_fieldActionView->columnWidth(1);
    m_fieldActionModel->setItem(static_cast<int>(fieldIdx), 0, item0);
    m_fieldActionModel->setItem(static_cast<int>(fieldIdx), 1, item1);
    m_fieldActionView->setColumnWidth(0, width0);
    m_fieldActionView->setColumnWidth(1, width1);
}

void
WtMyClass::updateActionChildren(size_t const  fieldIdx)
{
    Field  fdF = *m_objPtr->getField()[fieldIdx];
    std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  fnVec =
            fdF.getActionFnRef();
    for (int  i = 0; i < fnVec.size(); ++i) {
        Action const  action = fnVec[i].first;
        std::string const  actStr = "    " + toActionString(action);
        std::string  fnStr = fnVec[i].second->declLabel();
        QStandardItem *  item0 = new QStandardItem(QString::fromStdString(actStr));
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(fnStr));
        const int  width0 = m_fieldActionView->columnWidth(0);
        const int  width1 = m_fieldActionView->columnWidth(1);
        m_fieldActionModel->item(static_cast<int>(fieldIdx))->setChild(i, 0, item0);
        m_fieldActionModel->item(static_cast<int>(fieldIdx))->setChild(i, 1, item1);
        m_fieldActionView->setColumnWidth(0, width0);
        m_fieldActionView->setColumnWidth(1, width1);
    }
}

void
WtMyClass::repFieldActionDelIdx()
{
    m_fieldActionDelIdxModel->removeRows(0, m_fieldActionDelIdxModel->rowCount());
    QModelIndex const  index = m_fieldActionView->currentIndex();
    if (index.isValid() && index.parent().isValid()) {
        int const  row = index.parent().row();
        Field  fdF = *m_objPtr->getField()[row];
        std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  fnVec =
                fdF.getActionFnRef();
        std::shared_ptr<ActFn>  fn = fnVec[index.row()].second;
        auto  sline = fn->getStrike();
        for (auto const &  it: sline) {
            QStandardItem *  newItem = new QStandardItem(
                        QString::fromStdString(std::to_string(it)));
            newItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            m_fieldActionDelIdxModel->appendRow(newItem);
        }
    }
}

void
WtMyClass::repFieldActionInsertIdx()
{
    m_fieldActionInsertIdxModel->removeRows(0, m_fieldActionInsertIdxModel->rowCount());
    QModelIndex const  index = m_fieldActionView->currentIndex();
    if (index.isValid() && index.parent().isValid()) {
        int const  row = index.parent().row();
        Field  fdF = *m_objPtr->getField()[row];
        std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  fnVec =
                fdF.getActionFnRef();
        std::shared_ptr<ActFn>  fn = fnVec[index.row()].second;
        auto  sline = fn->getNewCode();
        for (auto const &  it: sline) {
            QStandardItem *  newItem = new QStandardItem(
                        QString::fromStdString(std::to_string(it.first)));
            newItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            m_fieldActionInsertIdxModel->appendRow(newItem);
        }
    }
}

void
WtMyClass::currFieldActionInsertIdx(int const  idx /* = INT_MAX */)
{
    QModelIndex const  indexFd = m_fieldActionView->currentIndex();
    if (indexFd.isValid() && indexFd.parent().isValid()) {
        int const  row = indexFd.parent().row();
        Field  fdF = *m_objPtr->getField()[row];
        std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  fnVec =
                fdF.getActionFnRef();
        std::shared_ptr<ActFn>  fn = fnVec[indexFd.row()].second;
        auto  sline = fn->getNewCode();

        auto  itF = std::find_if(sline.begin(), sline.end(),
                [idx](const std::pair<size_t, std::string> &  value) ->bool {
            if (idx == value.first) {
                return true;
            } else {
                return false;
            }
        });
        if (itF != sline.end()) {
            auto const  dis = std::distance(sline.begin(), itF);
            m_fieldActionInsertIdxView->setCurrentIndex(
                        m_fieldActionInsertIdxModel->index(dis, 0));
        }

        QModelIndex const  indexInsert = m_fieldActionInsertIdxView->currentIndex();
        if (!indexInsert.isValid()) {
            m_fieldActionInsertCode->setReadOnly(true);
            m_fieldActionInsertCode->clear();
            return;
        }
        m_fieldActionInsertCode->setReadOnly(false);
        m_fieldActionInsertCode->setPlainText(QString::fromStdString(
                sline[indexInsert.row()].second));
    }
}

void
WtMyClass::repMulInhClass()
{
    if (!m_objPtr)  return;

    m_mulInhClassModel->removeRows(0, m_mulInhClassModel->rowCount());
    auto const  currMul = m_objPtr->getMulInhClass();
    for (auto const & [baseClass, pur, isVirtual]: currMul) {
        QStandardItem *  item1 = new QStandardItem(QString::fromStdString(baseClass));
        QStandardItem *  item2 = new QStandardItem;
        QStandardItem *  item3 = new QStandardItem;

        if (pur == Purview::purPublic) {
            item2->setData(QVariant("public"), Qt::EditRole | Qt::DisplayRole);
        } else if (pur == Purview::purProtected) {
            item2->setData(QVariant("protected"), Qt::EditRole | Qt::DisplayRole);
        } else {
            item2->setData(QVariant("private"), Qt::EditRole | Qt::DisplayRole);
        }
        item3->setData(QVariant(isVirtual), Qt::EditRole | Qt::DisplayRole);
        QList<QStandardItem *>  items;
        items << item1 << item2 << item3;
        m_mulInhClassModel->appendRow(items);
    }
}

void
WtMyClass::repTemplateClass()
{
    if (!m_objPtr)  return;

    auto const  tpl = m_objPtr->getClassTparam();
    m_templateModel->removeRows(0, m_templateModel->rowCount());
    for (size_t  i = 0; i < tpl.size(); ++i) {
        QList<QStandardItem *>  items;
        QStandardItem *  item0 = new QStandardItem(
                QString::fromStdString(tpl[i].getTypename()));
        QStandardItem *  item1 = new QStandardItem(
                QString::fromStdString(tpl[i].getTName()));
        QStandardItem *  item2 = new QStandardItem(
                QString::fromStdString(tpl[i].getDocment()));
        QStandardItem *  item3 = new QStandardItem(
                QString::fromStdString(tpl[i].getDefalutValue()));
        items << item0 << item1 << item2 << item3;
        m_templateModel->appendRow(items);
    }
}

void
WtMyClass::repFriendClass()
{
    if (!m_objPtr)  return;

    auto const  vec = m_objPtr->getFriendClassName();
    m_friendClassModel->removeRows(0, m_friendClassModel->rowCount());
    for (size_t  i = 0; i < vec.size(); ++i) {
        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(vec[i]));
        m_friendClassModel->appendRow(item);
    }
}

bool
WtMyClass::nameCheckDuplication(std::string const &  fnName)
{
    bool  res = false;

    auto  rawDataVec = m_objPtr->getField();
    for (const auto &  fn: rawDataVec) {
        res = fn->getFieldName() == fnName;
        if (res)  return res;
    }

    return res;
}

void
WtMyClass::setEqFn(bool const  status)
{
    if (!status) {
        QStandardItem *  itemClass = getItemPtr();
        int  count = itemClass->rowCount();
        for (int  i = 0; i < count; ++i) {
            QStandardItem *  chit = itemClass->child(i);
            Etype const  etp = static_cast<Etype>(chit->data(
                    Qt::UserRole + 1).toInt());
            if (etp == Etype::eVirtualEqFn) {
                itemClass->removeRow(i);
                break;
            }
        }

        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                m_objPtr->getEObjectPtr();
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

        Module *  mdPtr = m_objPtr->getParentModulePtr();
        if (mdPtr) {
            QStandardItem *  itemModule = itemClass->parent();
            count = itemModule->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemModule->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eEqFn) {
                    EqFn *  ptr = static_cast<EqFn *>(chit->data(
                            Qt::UserRole + 2).value<void *>());
                    if (ptr->getParentClassPtr() == m_objPtr) {
                        itemModule->removeRow(i);
                        break;
                    }
                }
            }
            count = itemModule->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemModule->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eNotEqFn) {
                    NotEqFn *  ptr = static_cast<NotEqFn *>(chit->data(
                            Qt::UserRole + 2).value<void *>());
                    if (ptr->getParentClassPtr() == m_objPtr) {
                        itemModule->removeRow(i);
                        break;
                    }
                }
            }

            objVec = mdPtr->getEObjectListPtr();
            auto  itEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eEqFn) {
                            if (std::dynamic_pointer_cast<EqFn>(val.second)->
                                    getParentClassPtr() == m_objPtr) {
                                return true;
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    });
            if (itEqFn != objVec->end()) {
                objVec->erase(itEqFn);
            }
            auto  itNotEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eNotEqFn) {
                            if (std::dynamic_pointer_cast<NotEqFn>(val.second)->
                                    getParentClassPtr() == m_objPtr) {
                                return true;
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    });
            if (itNotEqFn != objVec->end()) {
                objVec->erase(itNotEqFn);
            }
        }

        m_objPtr->setEqFunction(false);
        return;
    }

    EqFn  fnEq(m_objPtr->getClassName(), m_objPtr);
    NotEqFn  fnNotEq(m_objPtr->getClassName(), m_objPtr);
    VirtualEqFn  fnVirtualEq(m_objPtr);
    setEqFnAdd(std::move(fnEq), std::move(fnNotEq), std::move(fnVirtualEq));
}

void
WtMyClass::setEqFnAdd(EqFn &&  fnEq,
                      NotEqFn &&  fnNotEq,
                      VirtualEqFn &&  fnVirtualEq)
{
    m_objPtr->setEqFunction(true);
    ClassType const  ct = m_objPtr->getClasstype();
    if (ct == ClassType::cppBase || ct == ClassType::cppInherit) {
        int  index = -1;
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                m_objPtr->getEObjectRef();
        for (int  i = 0; i < vecClass.size(); ++i) {
            if (vecClass[i].first == Etype::eProtectedLabel) {
                index = i;
                break;
            }
        }
        QStandardItem *  itemClass = getItemPtr();
        if (index == -1) {
            std::shared_ptr<ProtectedLabel>  objPtr =
                    std::make_shared<ProtectedLabel>();
            std::pair<Etype, std::shared_ptr<EObject>>  newObj;
            newObj.first = Etype::eProtectedLabel;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
            m_objPtr->appendEobjList(newObj);
            index = static_cast<int>(vecClass.size() - 1);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemClass->appendRow(item);
        }
        index++;
        std::shared_ptr<VirtualEqFn>  objPtr =
                std::make_shared<VirtualEqFn>(std::move(fnVirtualEq));
        std::pair<Etype, std::shared_ptr<EObject>>  newObj;
        newObj.first = Etype::eVirtualEqFn;
        newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
        m_objPtr->insertEobjList(newObj, index);

        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(newObj.second->getTreeLabel()));
        setItemProperty(item, newObj.first, newObj.second);
        itemClass->insertRow(index, item);
    }

    if (!(ct == ClassType::cppBase || ct == ClassType::cppFinal))  return;
    Module *  modulePtr = m_objPtr->getParentModulePtr();
    if (modulePtr) {
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>>
                vecMobj = modulePtr->getEobjList();
        int  index = -1;
        for (int  i = 0; i < vecMobj.size(); ++i) {
            if (vecMobj[i].first == Etype::eClass) {
                MyClass *  classPtr = static_cast<MyClass *>(
                        vecMobj[i].second.get());
                if (classPtr == m_objPtr) {
                    index = i;
                    break;
                }
            }
        }
        if (index != -1) {
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
                    moduleObjVec = modulePtr->getEObjectListPtr();

            std::shared_ptr<EqFn>  objPtr1 =
                    std::make_shared<EqFn>(std::move(fnEq));
            std::pair<Etype, std::shared_ptr<EObject>>  newObj;
            newObj.first = Etype::eEqFn;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr1);
            moduleObjVec->insert(moduleObjVec->begin() + index, newObj);

            QStandardItem *  itemClass = getItemPtr();
            QStandardItem *  itemModule = itemClass->parent();
            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemModule->insertRow(index, item);

            index++;

            std::shared_ptr<NotEqFn>  objPtr2 =
                    std::make_shared<NotEqFn>(std::move(fnNotEq));
            newObj.first = Etype::eNotEqFn;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr2);
            moduleObjVec->insert(moduleObjVec->begin() + index, newObj);

            item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemModule->insertRow(index, item);
        }
    }
}

void
WtMyClass::setLessFn(bool const  status)
{
    if (!status) {
        QStandardItem *  itemClass = getItemPtr();
        int  count = itemClass->rowCount();
        for (int  i = 0; i < count; ++i) {
            QStandardItem *  chit = itemClass->child(i);
            Etype const  etp = static_cast<Etype>(chit->data(
                    Qt::UserRole + 1).toInt());
            if (etp == Etype::eVirtualLessFn) {
                itemClass->removeRow(i);
                break;
            }
        }

        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                m_objPtr->getEObjectPtr();
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

        Module *  mdPtr = m_objPtr->getParentModulePtr();
        if (mdPtr) {
            QStandardItem *  itemModule = itemClass->parent();
            count = itemModule->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemModule->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eLessFn) {
                    LessFn *  ptr = static_cast<LessFn *>(chit->data(
                            Qt::UserRole + 2).value<void *>());
                    if (ptr->getParentClassPtr() == m_objPtr) {
                        itemModule->removeRow(i);
                        break;
                    }
                }
            }
            count = itemModule->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemModule->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eLessEqFn) {
                    LessEqFn *  ptr = static_cast<LessEqFn *>(chit->data(
                            Qt::UserRole + 2).value<void *>());
                    if (ptr->getParentClassPtr() == m_objPtr) {
                        itemModule->removeRow(i);
                        break;
                    }
                }
            }
            count = itemModule->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemModule->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eGreaterFn) {
                    GreaterFn *  ptr = static_cast<GreaterFn *>(chit->data(
                            Qt::UserRole + 2).value<void *>());
                    if (ptr->getParentClassPtr() == m_objPtr) {
                        itemModule->removeRow(i);
                        break;
                    }
                }
            }
            count = itemModule->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemModule->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eGreaterEqFn) {
                    GreaterEqFn *  ptr = static_cast<GreaterEqFn *>(chit->data(
                            Qt::UserRole + 2).value<void *>());
                    if (ptr->getParentClassPtr() == m_objPtr) {
                        itemModule->removeRow(i);
                        break;
                    }
                }
            }

            objVec = mdPtr->getEObjectListPtr();
            auto  itLessFn = std::find_if(objVec->begin(), objVec->end(), [this](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eLessFn) {
                            if (std::dynamic_pointer_cast<LessFn>(val.second)->
                                    getParentClassPtr() == m_objPtr) {
                                return true;
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    });
            if (itLessFn != objVec->end()) {
                objVec->erase(itLessFn);
            }
            auto  itLessEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eLessEqFn) {
                            if (std::dynamic_pointer_cast<LessEqFn>(val.second)->
                                    getParentClassPtr() == m_objPtr) {
                                return true;
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    });
            if (itLessEqFn != objVec->end()) {
                objVec->erase(itLessEqFn);
            }
            auto  itGreaterFn = std::find_if(objVec->begin(), objVec->end(), [this](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eGreaterFn) {
                            if (std::dynamic_pointer_cast<GreaterFn>(val.second)->
                                    getParentClassPtr() == m_objPtr) {
                                return true;
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    });
            if (itGreaterFn != objVec->end()) {
                objVec->erase(itGreaterFn);
            }
            auto  itGreaterEqFn = std::find_if(objVec->begin(), objVec->end(), [this](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eGreaterEqFn) {
                            if (std::dynamic_pointer_cast<GreaterEqFn>(val.second)->
                                    getParentClassPtr() == m_objPtr) {
                                return true;
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    });
            if (itGreaterEqFn != objVec->end()) {
                objVec->erase(itGreaterEqFn);
            }
        }

        m_objPtr->setLessFunction(false);
        return;
    }

    LessFn  fnLess(m_objPtr->getClassName(), m_objPtr);
    LessEqFn  fnLessEq(m_objPtr->getClassName(), m_objPtr);
    GreaterFn  fnGreater(m_objPtr->getClassName(), m_objPtr);
    GreaterEqFn  fnGreaterEq(m_objPtr->getClassName(), m_objPtr);
    VirtualLessFn  fnVirtualLess(m_objPtr);
    setLessFnAdd(std::move(fnLess), std::move(fnLessEq), std::move(fnGreater),
            std::move(fnGreaterEq), std::move(fnVirtualLess));
}

void
WtMyClass::setLessFnAdd(LessFn &&  fnLess,
                        LessEqFn &&  fnLessEq,
                        GreaterFn &&  fnGreater,
                        GreaterEqFn &&  fnGreaterEq,
                        VirtualLessFn &&  fnVirtualLess)
{
    m_objPtr->setLessFunction(true);
    ClassType const  ct = m_objPtr->getClasstype();
    if (ct == ClassType::cppBase || ct == ClassType::cppInherit) {
        int  index = -1;
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                m_objPtr->getEObjectRef();
        for (int  i = 0; i < vecClass.size(); ++i) {
            if (vecClass[i].first == Etype::eProtectedLabel) {
                index = i;
                break;
            }
        }
        QStandardItem *  itemClass = getItemPtr();
        if (index == -1) {
            std::shared_ptr<ProtectedLabel>  objPtr =
                    std::make_shared<ProtectedLabel>();
            std::pair<Etype, std::shared_ptr<EObject>>  newObj;
            newObj.first = Etype::eProtectedLabel;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
            m_objPtr->appendEobjList(newObj);
            index = static_cast<int>(vecClass.size() - 1);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemClass->appendRow(item);
        }
        index++;
        std::shared_ptr<VirtualLessFn>  objPtr =
                std::make_shared<VirtualLessFn>(std::move(fnVirtualLess));
        std::pair<Etype, std::shared_ptr<EObject>>  newObj;
        newObj.first = Etype::eVirtualLessFn;
        newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
        m_objPtr->insertEobjList(newObj, index);

        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(newObj.second->getTreeLabel()));
        setItemProperty(item, newObj.first, newObj.second);
        itemClass->insertRow(index, item);
    }

    if (!(ct == ClassType::cppBase || ct == ClassType::cppFinal))  return;
    Module *  modulePtr = m_objPtr->getParentModulePtr();
    if (modulePtr) {
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>>
                vecMobj = modulePtr->getEobjList();
        int  index = -1;
        for (int  i = 0; i < vecMobj.size(); ++i) {
            if (vecMobj[i].first == Etype::eClass) {
                MyClass *  classPtr = static_cast<MyClass *>(
                        vecMobj[i].second.get());
                if (classPtr == m_objPtr) {
                    index = i;
                    break;
                }
            }
        }
        if (index != -1) {
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
                    moduleObjVec = modulePtr->getEObjectListPtr();

            std::shared_ptr<LessFn>  objPtr1 =
                    std::make_shared<LessFn>(std::move(fnLess));
            std::pair<Etype, std::shared_ptr<EObject>>  newObj;
            newObj.first = Etype::eLessFn;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr1);
            moduleObjVec->insert(moduleObjVec->begin() + index, newObj);

            QStandardItem *  itemClass = getItemPtr();
            QStandardItem *  itemModule = itemClass->parent();
            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemModule->insertRow(index, item);

            index++;

            std::shared_ptr<LessEqFn>  objPtr2 =
                    std::make_shared<LessEqFn>(std::move(fnLessEq));
            newObj.first = Etype::eLessEqFn;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr2);
            moduleObjVec->insert(moduleObjVec->begin() + index, newObj);

            item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemModule->insertRow(index, item);

            index++;

            std::shared_ptr<GreaterFn>  objPtr3 =
                    std::make_shared<GreaterFn>(std::move(fnGreater));
            newObj.first = Etype::eGreaterFn;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr3);
            moduleObjVec->insert(moduleObjVec->begin() + index, newObj);

            item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemModule->insertRow(index, item);

            index++;

            std::shared_ptr<GreaterEqFn>  objPtr4 =
                    std::make_shared<GreaterEqFn>(std::move(fnGreaterEq));
            newObj.first = Etype::eGreaterEqFn;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr4);
            moduleObjVec->insert(moduleObjVec->begin() + index, newObj);

            item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemModule->insertRow(index, item);
        }
    }
}

void
WtMyClass::setSwapFn(bool const  status)
{
    if (!status) {
        QStandardItem *  itemClass = getItemPtr();
        int  count = itemClass->rowCount();
        for (int  i = 0; i < count; ++i) {
            QStandardItem *  chit = itemClass->child(i);
            Etype const  etp = static_cast<Etype>(chit->data(
                    Qt::UserRole + 1).toInt());
            if (etp == Etype::eInSwapFn) {
                itemClass->removeRow(i);
                break;
            }
        }
        count = itemClass->rowCount();
        for (int  i = 0; i < count; ++i) {
            QStandardItem *  chit = itemClass->child(i);
            Etype const  etp = static_cast<Etype>(chit->data(
                    Qt::UserRole + 1).toInt());
            if (etp == Etype::eVirtualExchangeFn) {
                itemClass->removeRow(i);
                break;
            }
        }

        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                m_objPtr->getEObjectPtr();
        auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                    if (val.first == Etype::eInSwapFn) {
                        return true;
                    } else {
                        return false;
                    }
                });
        if (itF != objVec->end()) {
            objVec->erase(itF);
        }
        itF = std::find_if(objVec->begin(), objVec->end(), [](
                std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                    if (val.first == Etype::eVirtualExchangeFn) {
                        return true;
                    } else {
                        return false;
                    }
                });
        if (itF != objVec->end()) {
            objVec->erase(itF);
        }

        Module *  mdPtr = m_objPtr->getParentModulePtr();
        if (mdPtr) {
            QStandardItem *  itemModule = itemClass->parent();
            count = itemModule->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemModule->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eExtSwapFn) {
                    ExtSwapFn *  ptr = static_cast<ExtSwapFn *>(chit->data(
                            Qt::UserRole + 2).value<void *>());
                    if (ptr->getParentClassPtr() == m_objPtr) {
                        itemModule->removeRow(i);
                        break;
                    }
                }
            }

            objVec = mdPtr->getEObjectListPtr();
            auto  itExtSwapFn = std::find_if(objVec->begin(), objVec->end(), [this](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eExtSwapFn) {
                            if (std::dynamic_pointer_cast<ExtSwapFn>(val.second)->
                                    getParentClassPtr() == m_objPtr) {
                                return true;
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    });
            if (itExtSwapFn != objVec->end()) {
                objVec->erase(itExtSwapFn);
            }
        }

        m_objPtr->setSwapFunction(false);
        return;
    }

    ExtSwapFn  fnExtSwap(m_objPtr->getClassName(), m_objPtr);
    InSwapFn  fnInSwap(m_objPtr);
    VirtualExchangeFn  fnVirtualExchange(m_objPtr);
    setSwapFnAdd(std::move(fnExtSwap), std::move(fnInSwap), std::move(fnVirtualExchange));
}

void
WtMyClass::setSwapFnAdd(ExtSwapFn &&  fnExtSwap,
                        InSwapFn &&  fnInSwap,
                        VirtualExchangeFn &&  fnVirtualExchange)
{
    m_objPtr->setSwapFunction(true);
    ClassType const  ct = m_objPtr->getClasstype();
    if (ct == ClassType::cppBase || ct == ClassType::cppFinal) {
        int  index = -1;
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                m_objPtr->getEObjectRef();
        for (int  i = 0; i < vecClass.size(); ++i) {
            if (vecClass[i].first == Etype::ePublicLabel) {
                index = i;
                break;
            }
        }
        QStandardItem *  itemClass = getItemPtr();
        if (index == -1) {
            std::shared_ptr<PublicLabel>  objPtr =
                    std::make_shared<PublicLabel>();
            std::pair<Etype, std::shared_ptr<EObject>>  newObj;
            newObj.first = Etype::ePublicLabel;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
            m_objPtr->appendEobjList(newObj);
            index = static_cast<int>(vecClass.size() - 1);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemClass->appendRow(item);
        }
        index++;
        std::shared_ptr<InSwapFn>  objPtr =
                std::make_shared<InSwapFn>(std::move(fnInSwap));
        std::pair<Etype, std::shared_ptr<EObject>>  newObj;
        newObj.first = Etype::eInSwapFn;
        newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
        m_objPtr->insertEobjList(newObj, index);

        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(newObj.second->getTreeLabel()));
        setItemProperty(item, newObj.first, newObj.second);
        itemClass->insertRow(index, item);
    }

    if (ct == ClassType::cppBase || ct == ClassType::cppInherit) {
        int  index = -1;
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                m_objPtr->getEObjectRef();
        for (int  i = 0; i < vecClass.size(); ++i) {
            if (vecClass[i].first == Etype::eProtectedLabel) {
                index = i;
                break;
            }
        }
        QStandardItem *  itemClass = getItemPtr();
        if (index == -1) {
            std::shared_ptr<ProtectedLabel>  objPtr =
                    std::make_shared<ProtectedLabel>();
            std::pair<Etype, std::shared_ptr<EObject>>  newObj;
            newObj.first = Etype::eProtectedLabel;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
            m_objPtr->appendEobjList(newObj);
            index = static_cast<int>(vecClass.size() - 1);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemClass->appendRow(item);
        }
        index++;
        std::shared_ptr<VirtualExchangeFn>  objPtr =
                std::make_shared<VirtualExchangeFn>(std::move(fnVirtualExchange));
        std::pair<Etype, std::shared_ptr<EObject>>  newObj;
        newObj.first = Etype::eVirtualExchangeFn;
        newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
        m_objPtr->insertEobjList(newObj, index);

        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(newObj.second->getTreeLabel()));
        setItemProperty(item, newObj.first, newObj.second);
        itemClass->insertRow(index, item);
    }

    if (!(ct == ClassType::cppBase || ct == ClassType::cppFinal))  return;
    Module *  modulePtr = m_objPtr->getParentModulePtr();
    if (modulePtr) {
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>>
                vecMobj = modulePtr->getEobjList();
        int  index = -1;
        for (int  i = 0; i < vecMobj.size(); ++i) {
            if (vecMobj[i].first == Etype::eClass) {
                MyClass *  classPtr = static_cast<MyClass *>(
                        vecMobj[i].second.get());
                if (classPtr == m_objPtr) {
                    index = i;
                    break;
                }
            }
        }
        if (index != -1) {
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
                    moduleObjVec = modulePtr->getEObjectListPtr();

            std::shared_ptr<ExtSwapFn>  objPtr1 =
                    std::make_shared<ExtSwapFn>(std::move(fnExtSwap));
            std::pair<Etype, std::shared_ptr<EObject>>  newObj;
            newObj.first = Etype::eExtSwapFn;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr1);
            moduleObjVec->insert(moduleObjVec->begin() + index, newObj);

            QStandardItem *  itemClass = getItemPtr();
            QStandardItem *  itemModule = itemClass->parent();
            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemModule->insertRow(index, item);
        }
    }
}

void
WtMyClass::setToStringFn(bool const  status)
{
    if (!status) {
        QStandardItem *  itemClass = getItemPtr();
        int  count = itemClass->rowCount();
        for (int  i = 0; i < count; ++i) {
            QStandardItem *  chit = itemClass->child(i);
            Etype const  etp = static_cast<Etype>(chit->data(
                    Qt::UserRole + 1).toInt());
            if (etp == Etype::eToStringFn) {
                itemClass->removeRow(i);
                break;
            }
        }
        count = itemClass->rowCount();
        for (int  i = 0; i < count; ++i) {
            QStandardItem *  chit = itemClass->child(i);
            Etype const  etp = static_cast<Etype>(chit->data(
                    Qt::UserRole + 1).toInt());
            if (etp == Etype::eVirtualSerializeFn) {
                itemClass->removeRow(i);
                break;
            }
        }
        count = itemClass->rowCount();
        for (int  i = 0; i < count; ++i) {
            QStandardItem *  chit = itemClass->child(i);
            Etype const  etp = static_cast<Etype>(chit->data(
                    Qt::UserRole + 1).toInt());
            if (etp == Etype::eInFromStringFn) {
                itemClass->removeRow(i);
                break;
            }
        }
        count = itemClass->rowCount();
        for (int  i = 0; i < count; ++i) {
            QStandardItem *  chit = itemClass->child(i);
            Etype const  etp = static_cast<Etype>(chit->data(
                    Qt::UserRole + 1).toInt());
            if (etp == Etype::eDeserializeFn) {
                itemClass->removeRow(i);
                break;
            }
        }

        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  objVec =
                m_objPtr->getEObjectPtr();
        auto  itF = std::find_if(objVec->begin(), objVec->end(), [](
                std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                    if (val.first == Etype::eToStringFn) {
                        return true;
                    } else {
                        return false;
                    }
                });
        if (itF != objVec->end()) {
            objVec->erase(itF);
        }
        itF = std::find_if(objVec->begin(), objVec->end(), [](
                std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                    if (val.first == Etype::eVirtualSerializeFn) {
                        return true;
                    } else {
                        return false;
                    }
                });
        if (itF != objVec->end()) {
            objVec->erase(itF);
        }
        itF = std::find_if(objVec->begin(), objVec->end(), [](
                std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                    if (val.first == Etype::eInFromStringFn) {
                        return true;
                    } else {
                        return false;
                    }
                });
        if (itF != objVec->end()) {
            objVec->erase(itF);
        }
        itF = std::find_if(objVec->begin(), objVec->end(), [](
                std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                    if (val.first == Etype::eDeserializeFn) {
                        return true;
                    } else {
                        return false;
                    }
                });
        if (itF != objVec->end()) {
            objVec->erase(itF);
        }

        Module *  mdPtr = m_objPtr->getParentModulePtr();
        if (mdPtr) {
            QStandardItem *  itemModule = itemClass->parent();
            count = itemModule->rowCount();
            for (int  i = 0; i < count; ++i) {
                QStandardItem *  chit = itemModule->child(i);
                Etype const  etp = static_cast<Etype>(chit->data(
                        Qt::UserRole + 1).toInt());
                if (etp == Etype::eExtFromStringFn) {
                    ExtFromStringFn *  ptr = static_cast<ExtFromStringFn *>(chit->data(
                            Qt::UserRole + 2).value<void *>());
                    if (ptr->getParentClassPtr() == m_objPtr) {
                        itemModule->removeRow(i);
                        break;
                    }
                }
            }

            objVec = mdPtr->getEObjectListPtr();
            auto  itExt = std::find_if(objVec->begin(), objVec->end(), [this](
                    std::pair<Etype, std::shared_ptr<EObject>> const &  val) ->bool {
                        if (val.first == Etype::eExtFromStringFn) {
                            if (std::dynamic_pointer_cast<ExtFromStringFn>(val.second)->
                                    getParentClassPtr() == m_objPtr) {
                                return true;
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    });
            if (itExt != objVec->end()) {
                objVec->erase(itExt);
            }
        }

        m_objPtr->setToStringFunction(false);
        return;
    }

    ToStringFn  fnToString(m_objPtr);
    VirtualSerializeFn  fnVirtualSerialize(m_objPtr);
    ExtFromStringFn  fnExtFromString(m_objPtr->getClassName(), m_objPtr);
    InFromStringFn  fnInFromString(m_objPtr);
    DeserializeFn  fnDeserialize(m_objPtr);
    setToStringFnAdd(std::move(fnToString), std::move(fnVirtualSerialize),
            std::move(fnExtFromString), std::move(fnInFromString),
            std::move(fnDeserialize));
}

void
WtMyClass::setToStringFnAdd(ToStringFn &&  fnToString,
                            VirtualSerializeFn &&  fnVirtualSerialize,
                            ExtFromStringFn &&  fnExtFromString,
                            InFromStringFn &&  fnInFromString,
                            DeserializeFn &&  fnDeserialize)
{
    m_objPtr->setToStringFunction(true);
    ClassType const  ct = m_objPtr->getClasstype();
    if (ct == ClassType::cppBase || ct == ClassType::cppFinal) {
        int  index = -1;
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                m_objPtr->getEObjectRef();
        for (int  i = 0; i < vecClass.size(); ++i) {
            if (vecClass[i].first == Etype::ePublicLabel) {
                index = i;
                break;
            }
        }
        QStandardItem *  itemClass = getItemPtr();
        if (index == -1) {
            std::shared_ptr<PublicLabel>  objPtr =
                    std::make_shared<PublicLabel>();
            std::pair<Etype, std::shared_ptr<EObject>>  newObj;
            newObj.first = Etype::ePublicLabel;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
            m_objPtr->appendEobjList(newObj);
            index = static_cast<int>(vecClass.size() - 1);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemClass->appendRow(item);
        }
        index++;
        std::shared_ptr<ToStringFn>  objPtr =
                std::make_shared<ToStringFn>(std::move(fnToString));
        std::pair<Etype, std::shared_ptr<EObject>>  newObj;
        newObj.first = Etype::eToStringFn;
        newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
        m_objPtr->insertEobjList(newObj, index);

        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(newObj.second->getTreeLabel()));
        setItemProperty(item, newObj.first, newObj.second);
        itemClass->insertRow(index, item);

        index++;
        std::shared_ptr<InFromStringFn>  objPtrIF =
                std::make_shared<InFromStringFn>(std::move(fnInFromString));
        newObj.first = Etype::eInFromStringFn;
        newObj.second = std::dynamic_pointer_cast<EObject>(objPtrIF);
        m_objPtr->insertEobjList(newObj, index);

        item = new QStandardItem(
                QString::fromStdString(newObj.second->getTreeLabel()));
        setItemProperty(item, newObj.first, newObj.second);
        itemClass->insertRow(index, item);
    }

    if (ct == ClassType::cppBase || ct == ClassType::cppInherit) {
        int  index = -1;
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  vecClass =
                m_objPtr->getEObjectRef();
        for (int  i = 0; i < vecClass.size(); ++i) {
            if (vecClass[i].first == Etype::eProtectedLabel) {
                index = i;
                break;
            }
        }
        QStandardItem *  itemClass = getItemPtr();
        if (index == -1) {
            std::shared_ptr<ProtectedLabel>  objPtr =
                    std::make_shared<ProtectedLabel>();
            std::pair<Etype, std::shared_ptr<EObject>>  newObj;
            newObj.first = Etype::eProtectedLabel;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
            m_objPtr->appendEobjList(newObj);
            index = static_cast<int>(vecClass.size() - 1);

            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemClass->appendRow(item);
        }
        index++;
        std::shared_ptr<VirtualSerializeFn>  objPtr =
                std::make_shared<VirtualSerializeFn>(std::move(fnVirtualSerialize));
        std::pair<Etype, std::shared_ptr<EObject>>  newObj;
        newObj.first = Etype::eVirtualSerializeFn;
        newObj.second = std::dynamic_pointer_cast<EObject>(objPtr);
        m_objPtr->insertEobjList(newObj, index);

        QStandardItem *  item = new QStandardItem(
                QString::fromStdString(newObj.second->getTreeLabel()));
        setItemProperty(item, newObj.first, newObj.second);
        itemClass->insertRow(index, item);

        index++;
        std::shared_ptr<DeserializeFn>  objPtrDF =
                std::make_shared<DeserializeFn>(std::move(fnDeserialize));
        newObj.first = Etype::eDeserializeFn;
        newObj.second = std::dynamic_pointer_cast<EObject>(objPtrDF);
        m_objPtr->insertEobjList(newObj, index);

        item = new QStandardItem(
                QString::fromStdString(newObj.second->getTreeLabel()));
        setItemProperty(item, newObj.first, newObj.second);
        itemClass->insertRow(index, item);
    }

    if (!(ct == ClassType::cppBase || ct == ClassType::cppFinal))  return;
    Module *  modulePtr = m_objPtr->getParentModulePtr();
    if (modulePtr) {
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>>
                vecMobj = modulePtr->getEobjList();
        int  index = -1;
        for (int  i = 0; i < vecMobj.size(); ++i) {
            if (vecMobj[i].first == Etype::eClass) {
                MyClass *  classPtr = static_cast<MyClass *>(
                        vecMobj[i].second.get());
                if (classPtr == m_objPtr) {
                    index = i;
                    break;
                }
            }
        }
        if (index != -1) {
            std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
                    moduleObjVec = modulePtr->getEObjectListPtr();

            std::shared_ptr<ExtFromStringFn>  objPtr1 =
                    std::make_shared<ExtFromStringFn>(std::move(fnExtFromString));
            std::pair<Etype, std::shared_ptr<EObject>>  newObj;
            newObj.first = Etype::eExtFromStringFn;
            newObj.second = std::dynamic_pointer_cast<EObject>(objPtr1);
            moduleObjVec->insert(moduleObjVec->begin() + index, newObj);

            QStandardItem *  itemClass = getItemPtr();
            QStandardItem *  itemModule = itemClass->parent();
            QStandardItem *  item = new QStandardItem(
                    QString::fromStdString(newObj.second->getTreeLabel()));
            setItemProperty(item, newObj.first, newObj.second);
            itemModule->insertRow(index, item);
        }
    }
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
