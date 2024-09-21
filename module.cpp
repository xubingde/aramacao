#include <cstring>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <typeinfo>
#include "icode.h"
#include "fmt.h"
#include "eobject.h"
#include "module.h"
#include "publictype.h"
#include "myclass.h"
#include "function.h"
#include "functions.h"
#include "field.h"
#include "eqfn.h"
#include "noteqfn.h"
#include "lessfn.h"
#include "lesseqfn.h"
#include "greaterfn.h"
#include "greatereqfn.h"
#include "extswapfn.h"
#include "extfromstringfn.h"
#include "actfn.h"
#include "basicblock.h"
#include "staticfunctions.h"
#include "tplstaticfunctions.h"
#include "constexprfunctions.h"
#include "tplconstexprfunctions.h"
#include "myclassdec.h"
#include "myenum.h"
#include "mystruct.h"
#include "mystructdec.h"
#include "mytypedef.h"

namespace xu {

Module::Module():
        EObject(),
        m_eobjList(),
        m_filename(),
        m_cppGlobalCode(),
        m_cppEndCode(),
        m_hStart(),
        m_testCode(),
        m_hInclude(),
        m_cppInclude(),
        m_namespace(),
        m_extension(Extension::cpp),
        m_update(false),
        m_headerOnly(false)
{
    setBaseType(Etype::eModule);
    setFilename("file1");

    m_hStart = "#pragma once\n";
}

Module::Module(const Module &  other):
        EObject(other),
        m_eobjList(other.m_eobjList),
        m_filename(other.m_filename),
        m_cppGlobalCode(other.m_cppGlobalCode),
        m_cppEndCode(other.m_cppEndCode),
        m_hStart(other.m_hStart),
        m_testCode(other.m_testCode),
        m_hInclude(other.m_hInclude),
        m_cppInclude(other.m_cppInclude),
        m_namespace(other.m_namespace),
        m_extension(other.m_extension),
        m_update(other.m_update),
        m_headerOnly(other.m_headerOnly)
{
    copyEobjList();
}

Module::Module(Module &&  other) noexcept:
        EObject(std::move(other)),
        m_eobjList(std::move(other.m_eobjList)),
        m_filename(std::move(other.m_filename)),
        m_cppGlobalCode(std::move(other.m_cppGlobalCode)),
        m_cppEndCode(std::move(other.m_cppEndCode)),
        m_hStart(std::move(other.m_hStart)),
        m_testCode(std::move(other.m_testCode)),
        m_hInclude(std::move(other.m_hInclude)),
        m_cppInclude(std::move(other.m_cppInclude)),
        m_namespace(std::move(other.m_namespace)),
        m_extension(std::move(other.m_extension)),
        m_update(std::move(other.m_update)),
        m_headerOnly(std::move(other.m_headerOnly))
{
    moveEobjList();
}

Module::~Module() noexcept
{
}

Module &
Module::operator=(const Module &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_eobjList = other.m_eobjList;
    m_filename = other.m_filename;
    m_cppGlobalCode = other.m_cppGlobalCode;
    m_cppEndCode = other.m_cppEndCode;
    m_hStart = other.m_hStart;
    m_testCode = other.m_testCode;
    m_hInclude = other.m_hInclude;
    m_cppInclude = other.m_cppInclude;
    m_namespace = other.m_namespace;
    m_extension = other.m_extension;
    m_update = other.m_update;
    m_headerOnly = other.m_headerOnly;

    copyEobjList();

    return *this;
}

Module &
Module::operator=(Module &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_eobjList = std::move(other.m_eobjList);
    m_filename = std::move(other.m_filename);
    m_cppGlobalCode = std::move(other.m_cppGlobalCode);
    m_cppEndCode = std::move(other.m_cppEndCode);
    m_hStart = std::move(other.m_hStart);
    m_testCode = std::move(other.m_testCode);
    m_hInclude = std::move(other.m_hInclude);
    m_cppInclude = std::move(other.m_cppInclude);
    m_namespace = std::move(other.m_namespace);
    m_extension = std::move(other.m_extension);
    m_update = std::move(other.m_update);
    m_headerOnly = std::move(other.m_headerOnly);

    moveEobjList();

    return *this;
}

std::string
Module::toHCode() const
{
    std::string  res;

    res += m_hStart;
    res += "\n";
    res += begin_ifndef();
    res += "\n";
    res += h_include();
    res += "\n";
    res += begin_namespaceH();

    for (auto const &  it: m_eobjList) {
        res += it.second->toHBlock();
    }

    res += "\n";
    res += end_namespaceH();
    res += "\n";
    res += end_ifndef();

    return res;
}

std::string
Module::toCppCode() const
{
    std::string  res;

    res += cpp_include();
    res += "\n";
    res += begin_namespaceCpp();
    if (m_cppGlobalCode.size() > 0)  res += "\n";
    res += m_cppGlobalCode;

    for (auto const &  it: m_eobjList) {
        res += it.second->toCppBlock();
    }

    if (m_cppEndCode.size() > 0)  res += "\n";
    res += m_cppEndCode;
    res += "\n";
    res += end_namespaceCpp();

    return res;
}

std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &
Module::getEObjectListRef()
{
    return m_eobjList;
}

std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
Module::getEObjectListPtr()
{
    return &m_eobjList;
}

bool
Module::appendEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value)
{
    bool  res = false;

    if (checkEobject(value)) {
        m_eobjList.push_back(value);
        m_update = true;
        refreshPtr();
        res = true;
    }
    return res;
}

bool
Module::appendEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value)
{
    bool  res = false;

    if (checkEobject(value)) {
        m_eobjList.push_back(std::move(value));
        m_update = true;
        refreshPtr();
        res = true;
    }
    return res;
}

bool
Module::updateEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value,
                       size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size() && checkEobject(value)) {
        m_eobjList[index] = value;
        m_update = true;
        refreshPtr();
        res = true;
    }
    return res;
}

bool
Module::updateEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value,
                       size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size() && checkEobject(value)) {
        m_eobjList[index] = std::move(value);
        m_update = true;
        refreshPtr();
        res = true;
    }
    return res;
}

bool
Module::insertEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value,
                       size_t  index)
{
    bool  res = false;

    if (index > m_eobjList.size()) {
        index = m_eobjList.size();
    }
    if (checkEobject(value)) {
        m_eobjList.insert(m_eobjList.begin() + index, value);
        m_update = true;
        refreshPtr();
        res = true;
    }

    return res;
}

bool
Module::insertEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value,
                       size_t  index)
{
    bool  res = false;

    if (index > m_eobjList.size()) {
        index = m_eobjList.size();
    }
    if (checkEobject(value)) {
        m_eobjList.insert(m_eobjList.begin() + index, std::move(value));
        m_update = true;
        refreshPtr();
        res = true;
    }

    return res;
}

bool
Module::deleteEobjList(size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size()) {
        m_eobjList.erase(m_eobjList.begin() + index);
        m_update = true;
        refreshPtr();
        res = true;
    }

    return res;
}

bool
Module::takeEobjList(std::pair<Etype, std::shared_ptr<EObject>> &  result,
                     size_t const  index)
{
    if (index < m_eobjList.size()) {
        result = std::move(m_eobjList[index]);
        m_eobjList.erase(m_eobjList.begin() + index);
        m_update = true;
        refreshPtr();
        return true;
    }
    return false;
}

bool
Module::swapEobjList(size_t const  indexLhs,
                     size_t const  indexRhs)
{
    if (indexLhs < m_eobjList.size() && indexRhs < m_eobjList.size() && indexLhs != indexRhs) {
        std::swap(m_eobjList[indexLhs], m_eobjList[indexRhs]);
        m_update = true;
        refreshPtr();
        return true;
    } else {
        return false;
    }
}

bool
Module::moveEobjList(size_t &  indexFrom,
                     size_t &  indexTo)
{
    if (xu::moveVec_1(m_eobjList, indexFrom, indexTo)) {
        m_update = true;
        refreshPtr();
        return true;
    }
    return false;
}

void
Module::refreshPtr()
{
    std::vector<std::pair<std::string, MyClass *>>  clsName;
    for (auto const &  it: m_eobjList) {
        if (it.first == Etype::eClass) {
            std::shared_ptr<MyClass>  myclassPtr =
                    std::dynamic_pointer_cast<MyClass>(it.second);
            std::pair<std::string, MyClass *>  clsPtr;
            clsName.push_back({myclassPtr->getClassName(), myclassPtr.get()});
            myclassPtr->setParentModulePtr(this);

            std::vector<std::shared_ptr<Field>> &  fdVec = myclassPtr->getFieldRef();
            for (auto &  fd: fdVec) {
                std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  actVec
                        = fd->getActionFnRef();
                for (auto &  actFn: actVec) {
                    actFn.second->setParentFieldPtr(fd.get());
                    actFn.second->setParentClassPtr(myclassPtr.get());
                }
            }

            auto &  obj = myclassPtr->getEObjectRef();
            for (auto &  fn: obj) {
                switch (fn.first) {
                case Etype::eFunctions :
                case Etype::eStaticFunctions :
                case Etype::eConstexprFunctions :
                case Etype::eTplFunctions :
                case Etype::eTplStaticFunctions :
                case Etype::eTplConstexprFunctions :
                case Etype::eConstructors :
                case Etype::eTplConstructors :
                    std::dynamic_pointer_cast<Functions>(it.second)->
                            setParentClassPtr(myclassPtr.get());
                    break;
                case Etype::eFunction :
                case Etype::eDefaultConstructorFn :
                case Etype::eCopyConstructorFn :
                case Etype::eMoveConstructorFn :
                case Etype::eDestructorFn :
                case Etype::eCopyOperatorEqFn :
                case Etype::eMoveOperatorEqFn :
                case Etype::eVirtualEqFn :
                case Etype::eVirtualLessFn :
                case Etype::eInSwapFn :
                case Etype::eVirtualExchangeFn :
                case Etype::eToStringFn :
                case Etype::eVirtualSerializeFn :
                case Etype::eInFromStringFn :
                case Etype::eDeserializeFn :
                    std::dynamic_pointer_cast<Function>(it.second)->
                            setParentClassPtr(myclassPtr.get());
                    break;
                default :
                    break;
                }
            }
        }
    }

    for (auto const &  it: m_eobjList) {
        switch (it.first) {
        case Etype::eEqFn :
            {
                std::shared_ptr<EqFn>  extFn =
                        std::dynamic_pointer_cast<EqFn>(it.second);
                std::string const  cName = extFn->getClassName();
                auto  itor = std::find_if(clsName.begin(), clsName.end(),
                        [cName](std::pair<std::string, MyClass *> const &  val)
                        ->bool {
                            if (val.first == cName) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itor != clsName.end()) {
                    extFn->setParentClassPtr(itor->second);
                }
            }
            break;
        case Etype::eNotEqFn :
            {
                std::shared_ptr<NotEqFn>  extFn =
                        std::dynamic_pointer_cast<NotEqFn>(it.second);
                std::string const  cName = extFn->getClassName();
                auto  itor = std::find_if(clsName.begin(), clsName.end(),
                        [cName](std::pair<std::string, MyClass *> const &  val)
                        ->bool {
                            if (val.first == cName) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itor != clsName.end()) {
                    extFn->setParentClassPtr(itor->second);
                }
            }
            break;
        case Etype::eLessFn :
            {
                std::shared_ptr<LessFn>  extFn =
                        std::dynamic_pointer_cast<LessFn>(it.second);
                std::string const  cName = extFn->getClassName();
                auto  itor = std::find_if(clsName.begin(), clsName.end(),
                        [cName](std::pair<std::string, MyClass *> const &  val)
                        ->bool {
                            if (val.first == cName) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itor != clsName.end()) {
                    extFn->setParentClassPtr(itor->second);
                }
            }
            break;
        case Etype::eLessEqFn :
            {
                std::shared_ptr<LessEqFn>  extFn =
                        std::dynamic_pointer_cast<LessEqFn>(it.second);
                std::string const  cName = extFn->getClassName();
                auto  itor = std::find_if(clsName.begin(), clsName.end(),
                        [cName](std::pair<std::string, MyClass *> const &  val)
                        ->bool {
                            if (val.first == cName) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itor != clsName.end()) {
                    extFn->setParentClassPtr(itor->second);
                }
            }
            break;
        case Etype::eGreaterFn :
            {
                std::shared_ptr<GreaterFn>  extFn =
                        std::dynamic_pointer_cast<GreaterFn>(it.second);
                std::string const  cName = extFn->getClassName();
                auto  itor = std::find_if(clsName.begin(), clsName.end(),
                        [cName](std::pair<std::string, MyClass *> const &  val)
                        ->bool {
                            if (val.first == cName) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itor != clsName.end()) {
                    extFn->setParentClassPtr(itor->second);
                }
            }
            break;
        case Etype::eGreaterEqFn :
            {
                std::shared_ptr<GreaterEqFn>  extFn =
                        std::dynamic_pointer_cast<GreaterEqFn>(it.second);
                std::string const  cName = extFn->getClassName();
                auto  itor = std::find_if(clsName.begin(), clsName.end(),
                        [cName](std::pair<std::string, MyClass *> const &  val)
                        ->bool {
                            if (val.first == cName) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itor != clsName.end()) {
                    extFn->setParentClassPtr(itor->second);
                }
            }
            break;
        case Etype::eExtSwapFn :
            {
                std::shared_ptr<ExtSwapFn>  extFn =
                        std::dynamic_pointer_cast<ExtSwapFn>(it.second);
                std::string const  cName = extFn->getClassName();
                auto  itor = std::find_if(clsName.begin(), clsName.end(),
                        [cName](std::pair<std::string, MyClass *> const &  val)
                        ->bool {
                            if (val.first == cName) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itor != clsName.end()) {
                    extFn->setParentClassPtr(itor->second);
                }
            }
            break;
        case Etype::eExtFromStringFn :
            {
                std::shared_ptr<ExtFromStringFn>  extFn =
                        std::dynamic_pointer_cast<ExtFromStringFn>(it.second);
                std::string const  cName = extFn->getClassName();
                auto  itor = std::find_if(clsName.begin(), clsName.end(),
                        [cName](std::pair<std::string, MyClass *> const &  val)
                        ->bool {
                            if (val.first == cName) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (itor != clsName.end()) {
                    extFn->setParentClassPtr(itor->second);
                }
            }
            break;
        default :
            break;
        }
    }
}

bool
Module::checkEobject(std::pair<Etype, std::shared_ptr<EObject>> const &  value) const
{
    bool  res = false;
    if (value.first != value.second->getBaseType())  return res;

    switch (value.first) {
    case Etype::eBasicBlock :
    case Etype::eFunctions :
    case Etype::eStaticFunctions :
    case Etype::eConstexprFunctions :
    case Etype::eTplFunctions :
    case Etype::eTplStaticFunctions :
    case Etype::eTplConstexprFunctions :
    case Etype::eClass :
    case Etype::eClassDeclaration :
    case Etype::eEnum :
    case Etype::eStruct :
    case Etype::eStructDeclaration :
    case Etype::eTypedef :

    case Etype::eEqFn :
    case Etype::eNotEqFn :
    case Etype::eLessFn :
    case Etype::eLessEqFn :
    case Etype::eGreaterFn :
    case Etype::eGreaterEqFn :
    case Etype::eExtSwapFn :
    case Etype::eExtFromStringFn :
        res = true;
        break;
    default :
        break;
    }

    return res;
}

std::string
Module::begin_ifndef() const
{
    std::string  res;

    std::string  defTarget;
    for (auto const &  it : m_namespace) {
        std::string  nspace = it.getNamespaceValue();
        std::transform(nspace.begin(), nspace.end(), nspace.begin(), xu::toupperS);
        defTarget += nspace + "_";
    }

    std::string  tmp = m_filename;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), xu::toupperS);
    defTarget += tmp + "_H_";

    res = "#ifndef " + defTarget + "\n";
    res += "#define " + defTarget + "\n" ;

    return res;
}

std::string
Module::end_ifndef() const
{
    std::string  res("#endif  // ");

    for (auto const &  it : m_namespace) {
        std::string  nspace = it.getNamespaceValue();
        std::transform(nspace.begin(), nspace.end(), nspace.begin(), xu::toupperS);
        res += nspace + "_";
    }
    std::string  tmp = m_filename;
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), xu::toupperS);
    res += tmp + "_H_";
    res += "\n";

    return res;
}

std::string
Module::h_include() const
{
    std::string  res;

    for (auto const &  it : m_hInclude) {
        res += it.toHCode();
    }

    return res;
}

std::string
Module::cpp_include() const
{
    std::string  res;

    for (auto const &  it : m_cppInclude) {
        res += it.toHCode();
    }

    return res;
}

std::string
Module::begin_namespaceH() const
{
    std::string  res;

    for (auto const &  it : m_namespace) {
        res += it.hCodeStart();
    }

    return res;
}

std::string
Module::begin_namespaceCpp() const
{
    std::string  res;

    for (auto const &  it : m_namespace) {
        res += it.cppCodeStart();
    }

    return res;
}

std::string
Module::end_namespaceH() const
{
    std::string  res;

    for (auto const &  it : m_namespace) {
        res += it.hCodeEnd();
    }

    return res;
}

std::string
Module::end_namespaceCpp() const
{
    std::string  res;

    for (auto const &  it : m_namespace) {
        res += it.cppCodeEnd();
    }

    return res;
}

void
Module::copyEobjList()
{
    for (auto &  obj: m_eobjList) {
        std::shared_ptr<EObject>  ptr;
        switch (obj.first) {
        case Etype::eBasicBlock :
            ptr = std::make_shared<BasicBlock>(
                    *std::dynamic_pointer_cast<BasicBlock>(obj.second));
            break;
        case Etype::eFunctions :
            ptr = std::make_shared<Functions>(
                    *std::dynamic_pointer_cast<Functions>(obj.second));
            std::dynamic_pointer_cast<Functions>(ptr)->setParentClassPtr(nullptr);
            break;
        case Etype::eStaticFunctions :
            ptr = std::make_shared<StaticFunctions>(
                    *std::dynamic_pointer_cast<StaticFunctions>(obj.second));
            std::dynamic_pointer_cast<StaticFunctions>(ptr)->setParentClassPtr(nullptr);
            break;
        case Etype::eConstexprFunctions :
            ptr = std::make_shared<ConstexprFunctions>(
                    *std::dynamic_pointer_cast<ConstexprFunctions>(obj.second));
            std::dynamic_pointer_cast<ConstexprFunctions>(ptr)->setParentClassPtr(nullptr);
            break;
        case Etype::eTplFunctions :
            ptr = std::make_shared<TplFunctions>(
                    *std::dynamic_pointer_cast<TplFunctions>(obj.second));
            std::dynamic_pointer_cast<TplFunctions>(ptr)->setParentClassPtr(nullptr);
            break;
        case Etype::eTplStaticFunctions :
            ptr = std::make_shared<TplStaticFunctions>(
                    *std::dynamic_pointer_cast<TplStaticFunctions>(obj.second));
            std::dynamic_pointer_cast<TplStaticFunctions>(ptr)->setParentClassPtr(nullptr);
            break;
        case Etype::eTplConstexprFunctions :
            ptr = std::make_shared<TplConstexprFunctions>(
                    *std::dynamic_pointer_cast<TplConstexprFunctions>(obj.second));
            std::dynamic_pointer_cast<TplConstexprFunctions>(ptr)->setParentClassPtr(nullptr);
            break;
        case Etype::eClass :
            ptr = std::make_shared<MyClass>(
                    *std::dynamic_pointer_cast<MyClass>(obj.second));
            std::dynamic_pointer_cast<MyClass>(ptr)->setParentModulePtr(this);
            break;
        case Etype::eClassDeclaration :
            ptr = std::make_shared<MyClassDec>(
                    *std::dynamic_pointer_cast<MyClassDec>(obj.second));
            break;
        case Etype::eEnum :
            ptr = std::make_shared<MyEnum>(
                    *std::dynamic_pointer_cast<MyEnum>(obj.second));
            break;
        case Etype::eStruct :
            ptr = std::make_shared<MyStruct>(
                    *std::dynamic_pointer_cast<MyStruct>(obj.second));
            break;
        case Etype::eStructDeclaration :
            ptr = std::make_shared<MyStructDec>(
                    *std::dynamic_pointer_cast<MyStructDec>(obj.second));
            break;
        case Etype::eTypedef :
            ptr = std::make_shared<MyTypedef>(
                    *std::dynamic_pointer_cast<MyTypedef>(obj.second));
            break;
        case Etype::eEqFn :
            ptr = std::make_shared<EqFn>(
                    *std::dynamic_pointer_cast<EqFn>(obj.second));
            break;
        case Etype::eNotEqFn :
            ptr = std::make_shared<NotEqFn>(
                    *std::dynamic_pointer_cast<NotEqFn>(obj.second));
            break;
        case Etype::eLessFn :
            ptr = std::make_shared<LessFn>(
                    *std::dynamic_pointer_cast<LessFn>(obj.second));
            break;
        case Etype::eLessEqFn :
            ptr = std::make_shared<LessEqFn>(
                    *std::dynamic_pointer_cast<LessEqFn>(obj.second));
            break;
        case Etype::eGreaterFn :
            ptr = std::make_shared<GreaterFn>(
                    *std::dynamic_pointer_cast<GreaterFn>(obj.second));
            break;
        case Etype::eGreaterEqFn :
            ptr = std::make_shared<GreaterEqFn>(
                    *std::dynamic_pointer_cast<GreaterEqFn>(obj.second));
            break;
        case Etype::eExtSwapFn :
            ptr = std::make_shared<ExtSwapFn>(
                    *std::dynamic_pointer_cast<ExtSwapFn>(obj.second));
            break;
        case Etype::eExtFromStringFn :
            ptr = std::make_shared<ExtFromStringFn>(
                    *std::dynamic_pointer_cast<ExtFromStringFn>(obj.second));
            break;
        default :
            break;
        }
        obj.second = ptr;
    }
}

void
Module::moveEobjList()
{
    for (auto &  obj: m_eobjList) {
        switch (obj.first) {
        case Etype::eFunctions :
            std::dynamic_pointer_cast<Functions>(
                    obj.second)->setParentClassPtr(nullptr);
            break;
        case Etype::eStaticFunctions :
            std::dynamic_pointer_cast<StaticFunctions>(
                    obj.second)->setParentClassPtr(nullptr);
            break;
        case Etype::eConstexprFunctions :
            std::dynamic_pointer_cast<ConstexprFunctions>(
                    obj.second)->setParentClassPtr(nullptr);
            break;
        case Etype::eTplFunctions :
            std::dynamic_pointer_cast<TplFunctions>(
                    obj.second)->setParentClassPtr(nullptr);
            break;
        case Etype::eTplStaticFunctions :
            std::dynamic_pointer_cast<TplStaticFunctions>(
                    obj.second)->setParentClassPtr(nullptr);
            break;
        case Etype::eTplConstexprFunctions :
            std::dynamic_pointer_cast<TplConstexprFunctions>(
                    obj.second)->setParentClassPtr(nullptr);
            break;
        case Etype::eClass :
            std::dynamic_pointer_cast<MyClass>(
                    obj.second)->setParentModulePtr(this);
            break;
        default :
            break;
        }
    }
}

std::vector<std::pair<Etype, std::shared_ptr<EObject>>>
Module::getEobjList() const
{
    return m_eobjList;
}

std::string
Module::getFilename() const
{
    return m_filename;
}

void
Module::setFilename(const std::string &  value)
{
    m_filename = value;
    std::transform(m_filename.begin(), m_filename.end(),
            m_filename.begin(), xu::tolowerS);
    m_update = true;

    setTreeLabel("M   " + m_filename);
}

void
Module::setFilename(std::string &&  value)
{
    m_filename = std::move(value);
    std::transform(m_filename.begin(), m_filename.end(),
            m_filename.begin(), xu::tolowerS);
    m_update = true;

    setTreeLabel("M   " + m_filename);
}

std::string
Module::getCppGlobalCode() const
{
    return m_cppGlobalCode;
}

void
Module::setCppGlobalCode(const std::string &  value)
{
    m_cppGlobalCode = value;
    xu::procCode(m_cppGlobalCode);
    m_update = true;
}

void
Module::setCppGlobalCode(std::string &&  value)
{
    m_cppGlobalCode = std::move(value);
    xu::procCode(m_cppGlobalCode);
    m_update = true;
}

std::string
Module::getCppEndCode() const
{
    return m_cppEndCode;
}

void
Module::setCppEndCode(const std::string &  value)
{
    m_cppEndCode = value;
    xu::procCode(m_cppEndCode);
    m_update = true;
}

void
Module::setCppEndCode(std::string &&  value)
{
    m_cppEndCode = std::move(value);
    xu::procCode(m_cppEndCode);
    m_update = true;
}

std::string
Module::getHStart() const
{
    return m_hStart;
}

void
Module::setHStart(const std::string &  value)
{
    m_hStart = value;
}

void
Module::setHStart(std::string &&  value)
{
    m_hStart = std::move(value);
}

std::string
Module::getTestCode() const
{
    return m_testCode;
}

void
Module::setTestCode(const std::string &  value)
{
    m_testCode = value;
    xu::procCode(m_testCode);
}

void
Module::setTestCode(std::string &&  value)
{
    m_testCode = std::move(value);
    xu::procCode(m_testCode);
}

std::vector<IncludeItem>
Module::getHInclude() const
{
    return m_hInclude;
}

void
Module::setHInclude(const std::vector<IncludeItem> &  value)
{
    m_hInclude = value;
    m_update = true;
}

void
Module::setHInclude(std::vector<IncludeItem> &&  value)
{
    m_hInclude = std::move(value);
    m_update = true;
}

std::vector<IncludeItem>
Module::getCppInclude() const
{
    return m_cppInclude;
}

void
Module::setCppInclude(const std::vector<IncludeItem> &  value)
{
    m_cppInclude = value;
    m_update = true;
}

void
Module::setCppInclude(std::vector<IncludeItem> &&  value)
{
    m_cppInclude = std::move(value);
    m_update = true;
}

std::vector<NamespaceItem>
Module::getNamespace() const
{
    return m_namespace;
}

void
Module::setNamespace(const std::vector<NamespaceItem> &  value)
{
    m_namespace = value;
    m_update = true;
}

void
Module::setNamespace(std::vector<NamespaceItem> &&  value)
{
    m_namespace = std::move(value);
    m_update = true;
}

Module::Extension
Module::getExtension() const
{
    return m_extension;
}

void
Module::setExtension(const Module::Extension  value)
{
    m_extension = value;
    m_update = true;
}

bool
Module::isUpdate() const
{
    return m_update;
}

bool
Module::isHeaderOnly() const
{
    return m_headerOnly;
}

void
Module::setHeaderOnly(const bool  value)
{
    m_headerOnly = value;
    m_update = true;
}

bool
Module::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const Module &  rhs = dynamic_cast<const Module &>(value);

        result = this->EObject::equal(value);
        if (!result) return result;

        result = ( m_filename == rhs.m_filename );
        if (!result) return result;

        result = ( m_extension == rhs.m_extension );
        if (!result) return result;

        result = ( m_eobjList == rhs.m_eobjList );
        if (!result) return result;

        result = ( m_update == rhs.m_update );
        if (!result) return result;

        result = ( m_cppGlobalCode == rhs.m_cppGlobalCode );
        if (!result) return result;

        result = ( m_cppEndCode == rhs.m_cppEndCode );
        if (!result) return result;

        result = ( m_hInclude == rhs.m_hInclude );
        if (!result) return result;

        result = ( m_cppInclude == rhs.m_cppInclude );
        if (!result) return result;

        result = ( m_namespace == rhs.m_namespace );
        if (!result) return result;

        result = ( m_hStart == rhs.m_hStart );
        if (!result) return result;

        result = ( m_headerOnly == rhs.m_headerOnly );
        if (!result) return result;

        result = ( m_testCode == rhs.m_testCode );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
Module::less(const EObject &  value) const
{
    if (this->EObject::less(value)) return true;
    if (!(this->EObject::equal(value))) return false;

    try {
        const Module &  rhs = dynamic_cast<const Module &>(value);

        if (m_filename < rhs.m_filename) return true;
        if (rhs.m_filename < m_filename) return false;

        if (m_extension < rhs.m_extension) return true;
        if (rhs.m_extension < m_extension) return false;

        if (m_eobjList < rhs.m_eobjList) return true;
        if (rhs.m_eobjList < m_eobjList) return false;

        if (m_update < rhs.m_update) return true;
        if (rhs.m_update < m_update) return false;

        if (m_cppGlobalCode < rhs.m_cppGlobalCode) return true;
        if (rhs.m_cppGlobalCode < m_cppGlobalCode) return false;

        if (m_cppEndCode < rhs.m_cppEndCode) return true;
        if (rhs.m_cppEndCode < m_cppEndCode) return false;

        if (m_hInclude < rhs.m_hInclude) return true;
        if (rhs.m_hInclude < m_hInclude) return false;

        if (m_cppInclude < rhs.m_cppInclude) return true;
        if (rhs.m_cppInclude < m_cppInclude) return false;

        if (m_namespace < rhs.m_namespace) return true;
        if (rhs.m_namespace < m_namespace) return false;

        if (m_hStart < rhs.m_hStart) return true;
        if (rhs.m_hStart < m_hStart) return false;

        if (m_headerOnly < rhs.m_headerOnly) return true;
        if (rhs.m_headerOnly < m_headerOnly) return false;

        if (m_testCode < rhs.m_testCode) return true;
        if (rhs.m_testCode < m_testCode) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
Module::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_eobjList));
    xu::append(res, xu::toString(m_filename));
    xu::append(res, xu::toString(m_cppGlobalCode));
    xu::append(res, xu::toString(m_cppEndCode));
    xu::append(res, xu::toString(m_hStart));
    xu::append(res, xu::toString(m_testCode));
    xu::append(res, xu::toString(m_hInclude));
    xu::append(res, xu::toString(m_cppInclude));
    xu::append(res, xu::toString(m_namespace));
    xu::append(res, xu::toString(m_extension));
    xu::append(res, xu::toString(m_update));
    xu::append(res, xu::toString(m_headerOnly));

    return res;
}

bool
Module::deserialize(const char *  data,
                    const size_t  size)
{
    Module  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 12) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_eobjList, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_filename, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_cppGlobalCode, vi[3]))  err.push_back({3});
        if (!xu::fromString(me.m_cppEndCode, vi[4]))  err.push_back({4});
        if (!xu::fromString(me.m_hStart, vi[5]))  err.push_back({5});
        if (!xu::fromString(me.m_testCode, vi[6]))  err.push_back({6});
        if (!xu::fromString(me.m_hInclude, vi[7]))  err.push_back({7});
        if (!xu::fromString(me.m_cppInclude, vi[8]))  err.push_back({8});
        if (!xu::fromString(me.m_namespace, vi[9]))  err.push_back({9});
        if (!xu::fromString(me.m_extension, vi[10]))  err.push_back({10});
        if (!xu::fromString(me.m_update, vi[11]))  err.push_back({11});
        if (!xu::fromString(me.m_headerOnly, vi[12]))  err.push_back({12});
    }
    bool  result = false;

    if (err.size() == 0) {
        refreshPtr();
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
Module::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        Module &  rhs = dynamic_cast<Module &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_eobjList, rhs.m_eobjList);
        swap(m_filename, rhs.m_filename);
        swap(m_cppGlobalCode, rhs.m_cppGlobalCode);
        swap(m_cppEndCode, rhs.m_cppEndCode);
        swap(m_hStart, rhs.m_hStart);
        swap(m_testCode, rhs.m_testCode);
        swap(m_hInclude, rhs.m_hInclude);
        swap(m_cppInclude, rhs.m_cppInclude);
        swap(m_namespace, rhs.m_namespace);
        swap(m_extension, rhs.m_extension);
        swap(m_update, rhs.m_update);
        swap(m_headerOnly, rhs.m_headerOnly);

        result = true;
    }
    return result;
}

}
