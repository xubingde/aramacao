#include <cstring>
#include <typeinfo>
#include <functional>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include "myclass.h"
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "function.h"
#include "functions.h"
#include "module.h"
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
#include "publiclabel.h"
#include "protectedlabel.h"
#include "privatelabel.h"

namespace xu {

MyClass::MyClass():
        EObject(),
        m_stringErr(),
        m_parentModulePtr(nullptr),
        m_eobjList(),
        m_field(),
        m_styleField(),
        m_IDField(),
        m_serzField(),
        m_className("MyClass1"),
        m_replaceClassName(),
        m_docment(),
        m_testCode(),
        m_classtype(ClassType::cppFinal),
        m_alignByte(0),
        m_baseClassPrarm(),
        m_baseClassFirst({ "", false }),
        m_mulInhClass(),
        m_inheritID(InheritID::baseId),
        m_classTparam(),
        m_attribute(),
        m_friendClassName(),
        m_hBeginBefore(),
        m_hBeginBehind(),
        m_hEndBefore(),
        m_hEndBehind(),
        m_beforeDcl(),
        m_behindDcl(),
        m_updateToString(true),
        m_finalClass(false),
        m_template(false),
        m_updateFilename(false),
        m_setterReturnThis(false),
        m_impl(false),
        m_lessFunction(false),
        m_eqFunction(false),
        m_swapFunction(false),
        m_toStringFunction(false),
        m_internal(false),
        m_indPublicLabel(false),
        m_defCtor(false),
        m_copyCtor(false),
        m_moveCtor(false),
        m_dtor(false),
        m_copyOpEq(false),
        m_moveOpEq(false)
{
    setBaseType(Etype::eClass);
    setClassName("MyClass1");
    setIndPublicLabel(true);
}

MyClass::MyClass(const MyClass &  other):
        EObject(other),
        m_stringErr(other.m_stringErr),
        m_parentModulePtr(other.m_parentModulePtr),
        m_eobjList(other.m_eobjList),
        m_field(other.m_field),
        m_styleField(other.m_styleField),
        m_IDField(other.m_IDField),
        m_serzField(other.m_serzField),
        m_className(other.m_className),
        m_replaceClassName(other.m_replaceClassName),
        m_docment(other.m_docment),
        m_testCode(other.m_testCode),
        m_classtype(other.m_classtype),
        m_alignByte(other.m_alignByte),
        m_baseClassPrarm(other.m_baseClassPrarm),
        m_baseClassFirst(other.m_baseClassFirst),
        m_mulInhClass(other.m_mulInhClass),
        m_inheritID(other.m_inheritID),
        m_classTparam(other.m_classTparam),
        m_attribute(other.m_attribute),
        m_friendClassName(other.m_friendClassName),
        m_hBeginBefore(other.m_hBeginBefore),
        m_hBeginBehind(other.m_hBeginBehind),
        m_hEndBefore(other.m_hEndBefore),
        m_hEndBehind(other.m_hEndBehind),
        m_beforeDcl(other.m_beforeDcl),
        m_behindDcl(other.m_behindDcl),
        m_updateToString(other.m_updateToString),
        m_finalClass(other.m_finalClass),
        m_template(other.m_template),
        m_updateFilename(other.m_updateFilename),
        m_setterReturnThis(other.m_setterReturnThis),
        m_impl(other.m_impl),
        m_lessFunction(other.m_lessFunction),
        m_eqFunction(other.m_eqFunction),
        m_swapFunction(other.m_swapFunction),
        m_toStringFunction(other.m_toStringFunction),
        m_internal(other.m_internal),
        m_indPublicLabel(other.m_indPublicLabel),
        m_defCtor(other.m_defCtor),
        m_copyCtor(other.m_copyCtor),
        m_moveCtor(other.m_moveCtor),
        m_dtor(other.m_dtor),
        m_copyOpEq(other.m_copyOpEq),
        m_moveOpEq(other.m_moveOpEq)
{
}

MyClass::MyClass(MyClass &&  other) noexcept:
        EObject(std::move(other)),
        m_stringErr(std::move(other.m_stringErr)),
        m_parentModulePtr(std::move(other.m_parentModulePtr)),
        m_eobjList(std::move(other.m_eobjList)),
        m_field(std::move(other.m_field)),
        m_styleField(std::move(other.m_styleField)),
        m_IDField(std::move(other.m_IDField)),
        m_serzField(std::move(other.m_serzField)),
        m_className(std::move(other.m_className)),
        m_replaceClassName(std::move(other.m_replaceClassName)),
        m_docment(std::move(other.m_docment)),
        m_testCode(std::move(other.m_testCode)),
        m_classtype(std::move(other.m_classtype)),
        m_alignByte(std::move(other.m_alignByte)),
        m_baseClassPrarm(std::move(other.m_baseClassPrarm)),
        m_baseClassFirst(std::move(other.m_baseClassFirst)),
        m_mulInhClass(std::move(other.m_mulInhClass)),
        m_inheritID(std::move(other.m_inheritID)),
        m_classTparam(std::move(other.m_classTparam)),
        m_attribute(std::move(other.m_attribute)),
        m_friendClassName(std::move(other.m_friendClassName)),
        m_hBeginBefore(std::move(other.m_hBeginBefore)),
        m_hBeginBehind(std::move(other.m_hBeginBehind)),
        m_hEndBefore(std::move(other.m_hEndBefore)),
        m_hEndBehind(std::move(other.m_hEndBehind)),
        m_beforeDcl(std::move(other.m_beforeDcl)),
        m_behindDcl(std::move(other.m_behindDcl)),
        m_updateToString(std::move(other.m_updateToString)),
        m_finalClass(std::move(other.m_finalClass)),
        m_template(std::move(other.m_template)),
        m_updateFilename(std::move(other.m_updateFilename)),
        m_setterReturnThis(std::move(other.m_setterReturnThis)),
        m_impl(std::move(other.m_impl)),
        m_lessFunction(std::move(other.m_lessFunction)),
        m_eqFunction(std::move(other.m_eqFunction)),
        m_swapFunction(std::move(other.m_swapFunction)),
        m_toStringFunction(std::move(other.m_toStringFunction)),
        m_internal(std::move(other.m_internal)),
        m_indPublicLabel(std::move(other.m_indPublicLabel)),
        m_defCtor(std::move(other.m_defCtor)),
        m_copyCtor(std::move(other.m_copyCtor)),
        m_moveCtor(std::move(other.m_moveCtor)),
        m_dtor(std::move(other.m_dtor)),
        m_copyOpEq(std::move(other.m_copyOpEq)),
        m_moveOpEq(std::move(other.m_moveOpEq))
{
}

MyClass::~MyClass() noexcept
{
}

MyClass &
MyClass::operator=(const MyClass &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_stringErr = other.m_stringErr;
    m_parentModulePtr = other.m_parentModulePtr;
    m_eobjList = other.m_eobjList;
    m_field = other.m_field;
    m_styleField = other.m_styleField;
    m_IDField = other.m_IDField;
    m_serzField = other.m_serzField;
    m_className = other.m_className;
    m_replaceClassName = other.m_replaceClassName;
    m_docment = other.m_docment;
    m_testCode = other.m_testCode;
    m_classtype = other.m_classtype;
    m_alignByte = other.m_alignByte;
    m_baseClassPrarm = other.m_baseClassPrarm;
    m_baseClassFirst = other.m_baseClassFirst;
    m_mulInhClass = other.m_mulInhClass;
    m_inheritID = other.m_inheritID;
    m_classTparam = other.m_classTparam;
    m_attribute = other.m_attribute;
    m_friendClassName = other.m_friendClassName;
    m_hBeginBefore = other.m_hBeginBefore;
    m_hBeginBehind = other.m_hBeginBehind;
    m_hEndBefore = other.m_hEndBefore;
    m_hEndBehind = other.m_hEndBehind;
    m_beforeDcl = other.m_beforeDcl;
    m_behindDcl = other.m_behindDcl;
    m_updateToString = other.m_updateToString;
    m_finalClass = other.m_finalClass;
    m_template = other.m_template;
    m_updateFilename = other.m_updateFilename;
    m_setterReturnThis = other.m_setterReturnThis;
    m_impl = other.m_impl;
    m_lessFunction = other.m_lessFunction;
    m_eqFunction = other.m_eqFunction;
    m_swapFunction = other.m_swapFunction;
    m_toStringFunction = other.m_toStringFunction;
    m_internal = other.m_internal;
    m_indPublicLabel = other.m_indPublicLabel;
    m_defCtor = other.m_defCtor;
    m_copyCtor = other.m_copyCtor;
    m_moveCtor = other.m_moveCtor;
    m_dtor = other.m_dtor;
    m_copyOpEq = other.m_copyOpEq;
    m_moveOpEq = other.m_moveOpEq;

    return *this;
}

MyClass &
MyClass::operator=(MyClass &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_stringErr = std::move(other.m_stringErr);
    m_parentModulePtr = std::move(other.m_parentModulePtr);
    m_eobjList = std::move(other.m_eobjList);
    m_field = std::move(other.m_field);
    m_styleField = std::move(other.m_styleField);
    m_IDField = std::move(other.m_IDField);
    m_serzField = std::move(other.m_serzField);
    m_className = std::move(other.m_className);
    m_replaceClassName = std::move(other.m_replaceClassName);
    m_docment = std::move(other.m_docment);
    m_testCode = std::move(other.m_testCode);
    m_classtype = std::move(other.m_classtype);
    m_alignByte = std::move(other.m_alignByte);
    m_baseClassPrarm = std::move(other.m_baseClassPrarm);
    m_baseClassFirst = std::move(other.m_baseClassFirst);
    m_mulInhClass = std::move(other.m_mulInhClass);
    m_inheritID = std::move(other.m_inheritID);
    m_classTparam = std::move(other.m_classTparam);
    m_attribute = std::move(other.m_attribute);
    m_friendClassName = std::move(other.m_friendClassName);
    m_hBeginBefore = std::move(other.m_hBeginBefore);
    m_hBeginBehind = std::move(other.m_hBeginBehind);
    m_hEndBefore = std::move(other.m_hEndBefore);
    m_hEndBehind = std::move(other.m_hEndBehind);
    m_beforeDcl = std::move(other.m_beforeDcl);
    m_behindDcl = std::move(other.m_behindDcl);
    m_updateToString = std::move(other.m_updateToString);
    m_finalClass = std::move(other.m_finalClass);
    m_template = std::move(other.m_template);
    m_updateFilename = std::move(other.m_updateFilename);
    m_setterReturnThis = std::move(other.m_setterReturnThis);
    m_impl = std::move(other.m_impl);
    m_lessFunction = std::move(other.m_lessFunction);
    m_eqFunction = std::move(other.m_eqFunction);
    m_swapFunction = std::move(other.m_swapFunction);
    m_toStringFunction = std::move(other.m_toStringFunction);
    m_internal = std::move(other.m_internal);
    m_indPublicLabel = std::move(other.m_indPublicLabel);
    m_defCtor = std::move(other.m_defCtor);
    m_copyCtor = std::move(other.m_copyCtor);
    m_moveCtor = std::move(other.m_moveCtor);
    m_dtor = std::move(other.m_dtor);
    m_copyOpEq = std::move(other.m_copyOpEq);
    m_moveOpEq = std::move(other.m_moveOpEq);

    return *this;
}

std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &
MyClass::getEObjectRef()
{
    return m_eobjList;
}

std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
MyClass::getEObjectPtr()
{
    return &m_eobjList;
}

std::vector<Field> &
MyClass::getFieldRef()
{
    return m_field;
}

std::string
MyClass::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    if (!m_impl) {
        res = definition(tabStr);
    }

    return res;
}

std::string
MyClass::toCppBlock(std::string const & /* = std::string() */) const
{
    std::string  res;

    if (m_impl) {
        res = definition();
    }

    return res;
}

std::string
MyClass::declaration(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res = m_beforeDcl;

    if (m_template) {
        res += tabStr + "template <";
        for (size_t  i = 0; i < m_classTparam.size(); ++i) {
            res += m_classTparam[i].getTypename() + " " + m_classTparam[i].getTName();
            if (m_classTparam[i].getDefalutValue().size() > 0) {
                res += " = " + m_classTparam[i].getDefalutValue();
            }
            if (i != m_classTparam.size() - 1) {
                res += ", ";
            }
        }
        res += ">\n";
    }

    res += tabStr +  "class ";
    if (m_attribute.size() > 0) {
        res += m_attribute + " ";
    }
    res += m_className + ";\n" + m_behindDcl;

    return res;
}

std::string
MyClass::friendDeclaration(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    if (m_template) {
        res += tabStr + "template <";
        for (size_t  i = 0; i < m_classTparam.size(); ++i) {
            res += m_classTparam[i].getTypename();
            if (m_classTparam[i].getTypename().size() > 0) {
                res += " ";
            }

            if (m_classTparam[i].getFriendTypeName().size() > 0) {
                res += m_classTparam[i].getFriendTypeName();
            } else {
                res += m_classTparam[i].getTName();
            }

            if (m_classTparam[i].getDefalutValue().size() > 0) {
                res += " /* = " + m_classTparam[i].getDefalutValue() + " */";
            }
            if (i != m_classTparam.size() - 1) {
                res += ", ";
            }
        }
        res += ">\n";
    }

    res += tabStr +  "class ";
    res += m_className + ";\n";

    return res;
}

std::string
MyClass::definition(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res("\n");

    res += class_begin(tabStr);
    res += class_friend(tabStr);

    if (m_indPublicLabel) {
        res += class_field_FnDcl(m_indPublicLabel, tabStr);
    } else {
        bool  pubLabel = true;
        for (auto const &  it: m_eobjList) {
            res += it.second->toHBlock(tabStr);
            Etype const  etp = it.second->getBaseType();
            if (etp == Etype::ePublicLabel) {
                pubLabel = false;
            } else if (etp == Etype::eProtectedLabel ||
                       etp == Etype::ePrivateLabel ) {
                pubLabel = true;
           }
        }

        res += class_field_FnDcl(pubLabel, tabStr);
    }

    res += class_field_toHBlock(tabStr);
    res += class_end(tabStr);

    return res;
}

std::string
MyClass::toFCodeEq() const
{
    std::string  autoCode;
    std::string const  tab1(getDefTab());
    std::string const  tab2(getDefTab() + getDefTab());

    std::vector<size_t>  sortID;
    if (std::begin(m_IDField) != std::end(m_IDField)) {
        for (auto  it = m_IDField.begin(); it != m_IDField.end(); ++it) {
            sortID.push_back(*it);
        }
    } else {
        for (auto it = m_styleField.begin(); it != m_styleField.end(); ++it) {
            sortID.push_back(*it);
        }
    }
    const size_t  IDsize = sortID.size();

    std::string const  lhs(getLhs());
    std::string const  rhs(getRhs());
    std::string const  sig(getSig());
    switch (m_classtype) {
    case ClassType::cppFinal:
        autoCode += tab1 + "if (&" + lhs + " == &" + rhs + ") return true;\n";
        autoCode += tab1 + "bool  result = false;\n";
        for (size_t i = 0; i < IDsize; ++i) {
            autoCode += toFCodeEqIndex(m_field[sortID[i]], "", lhs, rhs);
        }
        autoCode += "\n";
        autoCode += tab1 + "return result;\n";
        break;
    case ClassType::cppBase:
        autoCode += tab1 + "bool  result = false;\n";
        for (size_t i = 0; i < IDsize; ++i) {
            autoCode += toFCodeEqIndex(m_field[sortID[i]], "", "", sig);
        }
        autoCode += "\n";
        autoCode += tab1 + "return result;\n";
        break;
    case ClassType::cppInherit:
        if (m_inheritID == InheritID::baseId) {
            autoCode += tab1 + "return this->" + m_baseClassFirst.first +
                    "::equal(" + sig + ");\n";
        } else if (m_inheritID == InheritID::inheritId) {
            if (IDsize == 0) {
                autoCode += tab1 + "return true;\n";
            } else {
                autoCode += tab1 + "bool  result = false;\n";
                autoCode += tab1 + "try {\n";
                autoCode += tab2 + "const " + m_className + " &  " + rhs +
                        " = dynamic_cast<const " + m_className + " &>(" +
                        sig + ");\n";
                for (size_t  i = 0; i < IDsize; ++i) {
                    autoCode += toFCodeEqIndex(m_field[sortID[i]], tab1, "", rhs);
                }
                autoCode += "\n";
                autoCode += tab1 + "} catch (const std::bad_cast &) {\n";
                autoCode += tab2 + ";\n";
                autoCode += tab1 + "}\n";
                autoCode += tab1 + "return result;\n";
            }
        } else {
            if (IDsize == 0) {
                autoCode += tab1 + "return this->" + m_baseClassFirst.first +
                        "::equal("  + sig + ");\n";
            } else {
                autoCode += tab1 + "bool  result = false;\n";
                autoCode += tab1 + "try {\n";
                autoCode += tab2 + "const " + m_className + " &  " + rhs +
                        " = dynamic_cast<const " + m_className + " &>(" +
                        sig + ");\n";
                autoCode += "\n";
                autoCode += tab2 + "result = this->" + m_baseClassFirst.first +
                        "::equal(" + sig + ");\n";
                autoCode += tab2 + "if (!result) return result;\n";
                for (size_t  i = 0; i < IDsize; ++i) {
                    autoCode += toFCodeEqIndex(m_field[sortID[i]], tab1, "", rhs);
                }
                autoCode += "\n";
                autoCode += tab1 + "} catch (const std::bad_cast &) {\n";
                autoCode += tab2 + ";\n";
                autoCode += tab1 + "}\n";
                autoCode += tab1 + "return result;\n";
            }
        }
        break;
    }

    return autoCode;
}

std::string
MyClass::toFCodeLess() const
{
    std::string  autoCode;
    const std::string  tab1(getDefTab());
    const std::string  tab2(getDefTab() + getDefTab());

    std::vector<size_t>  sortID;
    if (std::begin(m_IDField) != std::end(m_IDField)) {
        for (auto  it = m_IDField.begin(); it != m_IDField.end(); ++it) {
            sortID.push_back(*it);
        }
    } else {
        for (auto  it = m_styleField.begin(); it != m_styleField.end(); ++it) {
            sortID.push_back(*it);
        }
    }
    const size_t  IDsize = sortID.size();

    std::string const  lhs(getLhs());
    std::string const  rhs(getRhs());
    std::string const  sig(getSig());
    switch (m_classtype) {
    case ClassType::cppFinal:
        if (IDsize == 0) {
            autoCode += tab1 + "return false;\n";
        } else {
            autoCode += tab1 + "if (&" + lhs + " == &" + rhs + ") return false;\n";
            for (size_t  i = 0; i < IDsize; ++i) {
                autoCode += "\n";
                autoCode += toFCodeLessIndex(m_field[sortID[i]], "", lhs, rhs);
            }
            autoCode += "\n";
            autoCode += tab1 + "return false;\n";
        }
        break;
    case ClassType::cppBase:
        if (IDsize == 0) {
            autoCode += tab1 + "return false;\n";
        } else {
            for (size_t  i = 0; i < IDsize; ++i) {
                if (i != 0)  autoCode += "\n";
                autoCode += toFCodeLessIndex(m_field[sortID[i]], "", "", sig);
            }
            autoCode += "\n";
            autoCode += tab1 + "return false;\n";
        }
        break;
    case ClassType::cppInherit:
        if (m_inheritID == InheritID::baseId) {
            autoCode += tab1 + "return this->" + m_baseClassFirst.first +
                    "::less(" + sig + ");\n";
        } else if (m_inheritID == InheritID::inheritId) {
            if (IDsize == 0) {
                autoCode += tab1 + "return false;\n";
            } else {
                autoCode += tab1 + "try {\n";
                autoCode += tab2 + "const " + m_className + " &  " + rhs +
                        " = dynamic_cast<const " + m_className + " &>(" +
                        sig + ");\n";
                for (size_t  i = 0; i < IDsize; ++i) {
                    autoCode += "\n";
                    autoCode += toFCodeLessIndex(m_field[sortID[i]], tab1, "", rhs);
                }
                autoCode += "\n";
                autoCode += tab1 + "} catch (const std::bad_cast &) {\n";
                autoCode += tab2 + ";\n";
                autoCode += tab1 + "}\n";
                autoCode += tab1 + "return false;\n";
            }
        } else {
            if (IDsize == 0) {
                autoCode += tab1 + "return this->" + m_baseClassFirst.first +
                        "::less(" + sig + ");\n";
            } else {
                autoCode += tab1 + "if (this->" + m_baseClassFirst.first +
                        "::less(" + sig + ")) return true;\n";
                autoCode += tab1 + "if (!(this->" + m_baseClassFirst.first +
                        "::equal(" + sig + "))) return false;\n";
                autoCode += "\n";
                autoCode += tab1 + "try {\n";
                autoCode += tab2 + "const " + m_className + " &  " +
                        rhs + " = dynamic_cast<const " + m_className + " &>(" +
                        sig + ");\n";
                for (size_t  i = 0; i < IDsize; ++i) {
                    autoCode += "\n";
                    autoCode += toFCodeLessIndex(m_field[sortID[i]], tab1, "", rhs);
                }
                autoCode += "\n";
                autoCode += tab1 + "} catch (const std::bad_cast &) {\n";
                autoCode += tab2 + ";\n";
                autoCode += tab1 + "}\n";
                autoCode += tab1 + "return false;\n";
            }
        }
        break;
    }

    return autoCode;
}

std::string
MyClass::toFCodeSwap() const
{
    std::string  res;
    const std::string  tab1(getDefTab());
    const std::string  tab2(getDefTab() + getDefTab());

    std::string const  rhs(getRhs());
    std::string const  sig(getSig());
    if (m_classtype == ClassType::cppFinal) {
        res += tab1 + "if (this == &" + sig + ") return;\n";
        res += tab1 + "using std::swap;\n";
        for (size_t  i = 0; i < m_field.size(); ++i) {
            res += tab1 + "swap(" + m_field[i].getPrivateName() + ", " +
                    sig + "." + m_field[i].getPrivateName() + ");\n";
        }
    } else if (m_classtype == ClassType::cppBase) {
        res += tab1 + "bool  result = false;\n";
        res += tab1 + "if (typeid(*this) == typeid(" + sig + ")) {\n";
        res += tab2 + "using std::swap;\n";
        for (size_t  i = 0; i < m_field.size(); ++i) {
            res += tab2 + "swap(" + m_field[i].getPrivateName() + ", " +
                    sig + "." + m_field[i].getPrivateName() + ");\n";
        }
        res += "\n";
        res += tab2 + "result = true;\n";
        res += tab1 + "}\n";
        res += tab1 + "return result;\n";
    } else {
        res += tab1 + "bool  result = false;\n";
        res += tab1 + "if (typeid(*this) == typeid(" + sig + ")) {\n";

        res += tab2 + m_className + " &  " + rhs + " = dynamic_cast<" +
                m_className + " &>(" + sig + ");\n";
        res += tab2 + "this->" + m_baseClassFirst.first + "::exchange(rhs);\n";
        for (const auto & it: m_mulInhClass) {
            res += tab2 + "this->" + std::get<0>(it) + "::exchange(rhs);\n";
        }
        res += "\n";
        res += tab2 + "using std::swap;\n";
        for (size_t  i = 0; i < m_field.size(); ++i) {
            res += tab2 + "swap(" + m_field[i].getPrivateName() + ", " +
                    rhs + "." + m_field[i].getPrivateName() + ");\n";
        }
        res += "\n";
        res += tab2 + "result = true;\n";
        res += tab1 + "}\n";
        res += tab1 + "return result;\n";
    }
    return res;
}

std::string
MyClass::toFCodeToString() const
{
    std::string  res;
    const std::string  tab1(getDefTab());

    res += tab1 + "std::string  res;\n";
    res += "\n";
    if (m_classtype == ClassType::cppInherit) {
        res += tab1 + "xu::append(res, this->" + m_baseClassFirst.first +
                "::serialize());\n";
        for (const auto &  it: m_mulInhClass) {
            res += tab1 + "xu::append(res, this->" + std::get<0>(it) +
                    "::serialize());\n";
        }
        res += "\n";
    }
    for (size_t  i = 0; i < m_serzField.size(); ++i) {
        res += toFCodeToStringIndex(m_field[m_serzField[i]]);
    }
    res += "\n";
    res += tab1 + "return res;\n";

    return res;
}

std::string
MyClass::toFCodeFromString() const
{
    std::string  res;
    const std::string  tab1(getDefTab());
    const std::string  tab2(getDefTab() + getDefTab());

    res += tab1 + m_className + "  me;\n";
    res += tab1 + "std::vector<size_t>  err;\n";
    res += tab1 + "const auto  vi { xu::viewIcode(data, size) };\n";
    res += "\n";

    size_t  vi_index = 0;
    const size_t  serzSize = m_serzField.size();
    size_t  greaterSize = serzSize;
    if (m_classtype == ClassType::cppInherit) {
        greaterSize += m_mulInhClass.size();
    }

    if (m_classtype == ClassType::cppInherit) {
        res += tab1 + "if (vi.size() > " + std::to_string(greaterSize) + ") {\n";
        res += tab2 + "if (!me." + m_baseClassFirst.first +
                "::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});\n";
        ++vi_index;
        for (const auto &  it: m_mulInhClass) {
            res += tab2 + "if (!me." + std::get<0>(it) + "::deserialize(vi[" +
                    std::to_string(vi_index) + "].data(), vi[" +
                    std::to_string(vi_index) + "].size()))  err.push_back({" +
                    std::to_string(vi_index) + "});\n";
            ++vi_index;
        }
        res += "\n";
    } else {
        if (greaterSize == 0) {
            res += tab1 + "if (vi.size() > 0) {\n";
        } else {
            --greaterSize;
            res += tab1 + "if (vi.size() > " + std::to_string(greaterSize) + ") {\n";
        }
    }

    for (size_t  i = 0; i < serzSize; ++i) {
        res += toFCodeFromStringIndex(m_field[m_serzField[i]], vi_index);
        ++vi_index;
    }

    res += tab1 + "}   // ----- vi.size() > " + std::to_string(greaterSize) + " -----\n";
    res += tab1 + "bool  result = false;\n";
    res += "\n";
    res += tab1 + "if (err.size() == 0) {\n";
    res += tab2 + "*this = std::move(me);\n";
    res += tab2 + "result = true;\n";
    res += tab1 + "}\n";
    res += "\n";
    res += tab1 + "return result;\n";

    return res;
}

void
MyClass::appendField(Field const &  value)
{
    m_field.push_back(value);
    appendFieldIndex();
}

void
MyClass::appendField(Field &&  value)
{
    m_field.push_back(std::move(value));
    appendFieldIndex();
}

bool
MyClass::updateField(Field const &  value,
                     size_t const  index)
{
    if (index < m_field.size()) {
        m_field[index] = value;
        updateFieldIndex(index);
        return true;
    } else {
        return false;
    }
}

bool
MyClass::updateField(Field &&  value,
                     size_t const  index)
{
    if (index < m_field.size()) {
        m_field[index] = std::move(value);
        updateFieldIndex(index);
        return true;
    } else {
        return false;
    }
}

void
MyClass::insertField(Field const &  value,
                     size_t  index)
{
    if (index > m_field.size()) {
        index = m_field.size();
    }
    m_field.insert(m_field.begin() + index, value);
    insertFieldIndex(index);
}

void
MyClass::insertField(Field &&  value,
                     size_t  index)
{
    if (index > m_field.size()) {
        index = m_field.size();
    }
    m_field.insert(m_field.begin() + index, std::move(value));
    insertFieldIndex(index);
}

bool
MyClass::deleteField(size_t const  index)
{
    if (index < m_field.size()) {
        m_field.erase(m_field.begin() + index);
        deleteFieldIndex(index);
        return true;
    } else {
        return false;
    }
}

bool
MyClass::takeField(Field &  result,
                   size_t const  index)
{
    if (index < m_field.size()) {
        result = std::move(m_field[index]);
        m_field.erase(m_field.begin() + index);
        deleteFieldIndex(index);
        return true;
    }
    return false;
}

bool
MyClass::swapField(size_t const  idxLhs,
                   size_t const  idxRhs)
{
    if (idxLhs < m_field.size() && idxRhs < m_field.size() && idxLhs != idxRhs) {
        std::swap(m_field[idxLhs], m_field[idxRhs]);
        {
            auto  itLhs = std::find(m_styleField.begin(), m_styleField.end(), idxLhs);
            auto  itRhs = std::find(m_styleField.begin(), m_styleField.end(), idxRhs);
            if (itLhs != m_styleField.end()) {
                *itLhs = idxRhs;
            }
            if (itRhs != m_styleField.end()) {
                *itRhs = idxLhs;
            }
        }
        {
            auto  itLhs = std::find(m_IDField.begin(), m_IDField.end(), idxLhs);
            auto  itRhs = std::find(m_IDField.begin(), m_IDField.end(), idxRhs);
            if (itLhs != m_IDField.end()) {
                *itLhs = idxRhs;
            }
            if (itRhs != m_IDField.end()) {
                *itRhs = idxLhs;
            }
        }
        {
            auto  itLhs = std::find(m_serzField.begin(), m_serzField.end(), idxLhs);
            auto  itRhs = std::find(m_serzField.begin(), m_serzField.end(), idxRhs);
            if (itLhs != m_serzField.end()) {
                *itLhs = idxRhs;
            }
            if (itRhs != m_serzField.end()) {
                *itRhs = idxLhs;
            }
        }

        for (auto &  it: m_eobjList) {
            switch (it.first) {
            case Etype::eConstructors :
            case Etype::eTplConstructors :
                {
                    std::shared_ptr<Functions>  vec =
                            std::dynamic_pointer_cast<Functions>(it.second);
                    std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                    for (auto &  fn: fns) {
                        auto  defV = fn->getDefValueCtor();
                        std::swap(defV[idxLhs], defV[idxRhs]);
                        fn->setDefValueCtor(defV);
                    }
                    vec->setObjList(fns);
                }
                break;
            case Etype::eDefaultConstructorFn :
            case Etype::eCopyConstructorFn :
            case Etype::eMoveConstructorFn :
                {
                    std::shared_ptr<Function>  fn =
                            std::dynamic_pointer_cast<Function>(it.second);
                    auto  defV = fn->getDefValueCtor();
                    std::swap(defV[idxLhs], defV[idxRhs]);
                    fn->setDefValueCtor(defV);
                }
                break;
            default :
                break;
            }
        }

        return true;
    } else {
        return false;
    }
}

bool
MyClass::moveField(size_t &  idxFrom,
                   size_t &  idxTo)
{
    if (xu::moveVec_0(m_field, idxFrom, idxTo)) {
        auto  it1 = std::find(m_styleField.begin(), m_styleField.end(), idxFrom);
        for (auto &  id: m_styleField) {
            if (id > idxFrom)  id--;
        }
        for (auto &  id: m_styleField) {
            if (id >= idxTo)  id++;
        }
        *it1 = idxTo;

        auto  it2 = std::find(m_IDField.begin(), m_IDField.end(), idxFrom);
        for (auto &  id: m_IDField) {
            if (id > idxFrom)  id--;
        }
        for (auto &  id: m_IDField) {
            if (id >= idxTo)  id++;
        }
        if (it2 != m_IDField.end()) {
            *it2 = idxTo;
        }

        auto  it3 = std::find(m_serzField.begin(), m_serzField.end(), idxFrom);
        for (auto &  id: m_serzField) {
            if (id > idxFrom)  id--;
        }
        for (auto &  id: m_serzField) {
            if (id >= idxTo)  id++;
        }
        if (it3 != m_serzField.end()) {
            *it3 = idxTo;
        }

        for (auto &  it: m_eobjList) {
            switch (it.first) {
            case Etype::eConstructors :
            case Etype::eTplConstructors :
                {
                    std::shared_ptr<Functions>  vec =
                            std::dynamic_pointer_cast<Functions>(it.second);
                    std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                    for (auto &  fn: fns) {
                        auto  defV = fn->getDefValueCtor();
                        const auto  dV = defV[idxFrom];
                        defV.erase(defV.begin() + idxFrom);
                        defV.insert(defV.begin() + idxTo, dV);
                        fn->setDefValueCtor(defV);
                    }
                    vec->setObjList(fns);
                }
                break;
            case Etype::eDefaultConstructorFn :
            case Etype::eCopyConstructorFn :
            case Etype::eMoveConstructorFn :
                {
                    std::shared_ptr<Function>  fn =
                            std::dynamic_pointer_cast<Function>(it.second);
                    auto  defV = fn->getDefValueCtor();
                    const auto  dV = defV[idxFrom];
                    defV.erase(defV.begin() + idxFrom);
                    defV.insert(defV.begin() + idxTo, dV);
                    fn->setDefValueCtor(defV);
                }
                break;
            default :
                break;
            }
        }

        return true;
    }
    return false;
}

void
MyClass::clearField()
{
    m_field.clear();

    m_styleField.clear();
    m_IDField.clear();
    m_serzField.clear();

    for (auto &  it: m_eobjList) {
        switch (it.first) {
        case Etype::eConstructors :
        case Etype::eTplConstructors :
            {
                std::shared_ptr<Functions>  vec =
                        std::dynamic_pointer_cast<Functions>(it.second);
                std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                for (auto &  fn: fns) {
                    fn->setDefValueCtor({});
                }
                vec->setObjList(fns);
            }
            break;
        case Etype::eDefaultConstructorFn :
        case Etype::eCopyConstructorFn :
        case Etype::eMoveConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                fn->setDefValueCtor({});
            }
            break;
        default :
            break;
        }
    }
}

void
MyClass::appendMulInhClass(std::tuple<std::string, Purview, bool> const &  value)
{
    m_mulInhClass.push_back(value);
    appendMulInhClassIndex();
}

void
MyClass::appendMulInhClass(std::tuple<std::string, Purview, bool> &&  value)
{
    m_mulInhClass.push_back(std::move(value));
    appendMulInhClassIndex();
}

bool
MyClass::updateMulInhClass(std::tuple<std::string, Purview, bool> const &  value,
                           size_t const  index)
{
    if (index < m_mulInhClass.size()) {
        m_mulInhClass[index] = value;
        return true;
    } else {
        return false;
    }
}

bool
MyClass::updateMulInhClass(std::tuple<std::string, Purview, bool> &&  value,
                           size_t const  index)
{
    if (index < m_mulInhClass.size()) {
        m_mulInhClass[index] = std::move(value);
        return true;
    } else {
        return false;
    }
}

void
MyClass::insertMulInhClass(std::tuple<std::string, Purview, bool> const &  value,
                           size_t  index)
{
    if (index > m_mulInhClass.size()) {
        index = m_mulInhClass.size();
    }
    m_mulInhClass.insert(m_mulInhClass.begin() + index, value);
    insertMulInhClassIndex(index);
}

void
MyClass::insertMulInhClass(std::tuple<std::string, Purview, bool> &&  value,
                           size_t  index)
{
    if (index > m_mulInhClass.size()) {
        index = m_mulInhClass.size();
    }
    m_mulInhClass.insert(m_mulInhClass.begin() + index, std::move(value));
    insertMulInhClassIndex(index);
}

bool
MyClass::deleteMulInhClass(size_t const  index)
{
    if (index < m_mulInhClass.size()) {
        m_mulInhClass.erase(m_mulInhClass.begin() + index);
        deleteMulInhClassIndex(index);
        return true;
    } else {
        return false;
    }
}

bool
MyClass::takeMulInhClass(std::tuple<std::string, Purview, bool> &  result,
                         size_t const  index)
{
    if (index < m_mulInhClass.size()) {
        result = std::move(m_mulInhClass[index]);
        m_mulInhClass.erase(m_mulInhClass.begin() + index);
        deleteMulInhClassIndex(index);
        return true;
    }
    return false;
}

bool
MyClass::swapMulInhClass(size_t const  indexLhs,
                         size_t const  indexRhs)
{
    if (indexLhs < m_mulInhClass.size() && indexRhs < m_mulInhClass.size() &&
            indexLhs != indexRhs) {
        std::swap(m_mulInhClass[indexLhs], m_mulInhClass[indexRhs]);

        for (auto &  it: m_eobjList) {
            switch (it.first) {
            case Etype::eConstructors :
            case Etype::eTplConstructors :
                {
                    std::shared_ptr<Functions>  vec =
                            std::dynamic_pointer_cast<Functions>(it.second);
                    std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                    for (auto &  fn: fns) {
                        auto  mulV = fn->getInhValueBaseClass();
                        std::swap(mulV[indexLhs], mulV[indexRhs]);
                        fn->setInhValueBaseClass(mulV);
                    }
                    vec->setObjList(fns);
                }
                break;
            case Etype::eDefaultConstructorFn :
            case Etype::eCopyConstructorFn :
            case Etype::eMoveConstructorFn :
                {
                    std::shared_ptr<Function>  fn =
                            std::dynamic_pointer_cast<Function>(it.second);
                    auto  mulV = fn->getInhValueBaseClass();
                    std::swap(mulV[indexLhs], mulV[indexRhs]);
                    fn->setInhValueBaseClass(mulV);
                }
                break;
            default :
                break;
            }
        }

        return true;
    } else {
        return false;
    }
}

bool
MyClass::moveMulInhClass(size_t &  indexFrom,
                         size_t &  indexTo)
{
    if (xu::moveVec_1(m_mulInhClass, indexFrom, indexTo)) {
        for (auto &  it: m_eobjList) {
            switch (it.first) {
            case Etype::eConstructors :
            case Etype::eTplConstructors :
                {
                    std::shared_ptr<Functions>  vec =
                            std::dynamic_pointer_cast<Functions>(it.second);
                    std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                    for (auto &  fn: fns) {
                        auto  mulV = fn->getInhValueBaseClass();
                        xu::moveVec_0(mulV, indexFrom, indexTo);
                        fn->setInhValueBaseClass(mulV);
                    }
                    vec->setObjList(fns);
                }
                break;
            case Etype::eDefaultConstructorFn :
            case Etype::eCopyConstructorFn :
            case Etype::eMoveConstructorFn :
                {
                    std::shared_ptr<Function>  fn =
                            std::dynamic_pointer_cast<Function>(it.second);
                    auto  mulV = fn->getInhValueBaseClass();
                    xu::moveVec_0(mulV, indexFrom, indexTo);
                    fn->setInhValueBaseClass(mulV);
                }
                break;
            default :
                break;
            }
        }

        return true;
    }
    return false;
}

void
MyClass::clearMulInhClass()
{
    m_mulInhClass.clear();

    for (auto &  it: m_eobjList) {
        switch (it.first) {
        case Etype::eConstructors :
        case Etype::eTplConstructors :
            {
                std::shared_ptr<Functions>  vec =
                        std::dynamic_pointer_cast<Functions>(it.second);
                std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                for (auto &  fn: fns) {
                    fn->setInhValueBaseClass({});
                }
                vec->setObjList(fns);
            }
            break;
        case Etype::eDefaultConstructorFn :
        case Etype::eCopyConstructorFn :
        case Etype::eMoveConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                fn->setInhValueBaseClass({});
            }
            break;
        default :
            break;
        }
    }
}

bool
MyClass::appendEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value)
{
    bool  res = false;

    if (checkEobject(value)) {
        m_eobjList.push_back(value);
        res = true;
    }
    return res;
}

bool
MyClass::appendEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value)
{
    bool  res = false;

    if (checkEobject(value)) {
        m_eobjList.push_back(std::move(value));
        res = true;
    }
    return res;
}

bool
MyClass::updateEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value,
                        size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size() && checkEobject(value)) {
        m_eobjList[index] = value;
        res = true;
    }
    return res;
}

bool
MyClass::updateEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value,
                        size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size() && checkEobject(value)) {
        m_eobjList[index] = std::move(value);
        res = true;
    }
    return res;
}

bool
MyClass::insertEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value,
                        size_t  index)
{
    bool  res = false;

    if (index > m_eobjList.size()) {
        index = m_eobjList.size();
    }
    if (checkEobject(value)) {
        m_eobjList.insert(m_eobjList.begin() + index, value);
        res = true;
    }

    return res;
}

bool
MyClass::insertEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value,
                        size_t  index)
{
    bool  res = false;

    if (index > m_eobjList.size()) {
        index = m_eobjList.size();
    }
    if (checkEobject(value)) {
        m_eobjList.insert(m_eobjList.begin() + index, std::move(value));
        res = true;
    }

    return res;
}

bool
MyClass::deleteEobjList(size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size() && checkDeleteEobject(index)) {
        m_eobjList.erase(m_eobjList.begin() + index);
        res = true;
    }

    return res;
}

bool
MyClass::takeEobjList(std::pair<Etype, std::shared_ptr<EObject>> &  result,
                      size_t const  index)
{
    if (index < m_eobjList.size() && checkDeleteEobject(index)) {
        result = std::move(m_eobjList[index]);
        m_eobjList.erase(m_eobjList.begin() + index);
        return true;
    }
    return false;
}

bool
MyClass::swapEobjList(size_t const  indexLhs,
                      size_t const  indexRhs)
{
    if (indexLhs < m_eobjList.size() && indexRhs < m_eobjList.size() && indexLhs != indexRhs) {
        std::swap(m_eobjList[indexLhs], m_eobjList[indexRhs]);
        return true;
    } else {
        return false;
    }
}

bool
MyClass::moveEobjList(size_t &  indexFrom,
                      size_t &  indexTo)
{
    if (xu::moveVec_1(m_eobjList, indexFrom, indexTo)) {
        return true;
    }
    return false;
}

std::string
MyClass::toFCodeEqIndex(Field const &  fd,
                        std::string const &  tab,
                        std::string const &  lhsName,
                        std::string const &  rhsName) const
{
    std::string  res;
    std::string const  tab1 = tab + std::string(getDefTab());
    std::string const  tab2 = tab + std::string(getDefTab() + getDefTab());

    std::string const  rhs = rhsName + "." + fd.getPrivateName();
    std::string  lhs = fd.getPrivateName();
    if (!lhsName.empty()) {
        lhs = lhsName + "." + fd.getPrivateName();
    }

    res += "\n";
    if (fd.isPointer()) {
        res += tab1 + "if (" + lhs + " == nullptr || " + rhs + " == nullptr) {\n";
        res += tab2 + "result = ( " + lhs + " == " + rhs + " );\n";
        res += tab1 + "} else {\n";
        res += tab2 + "result = ( *" + lhs + " == *" + rhs + " );\n";
        res += tab1 + "}\n";
        res += tab1 + "if (!result) return result;\n";
    } else {
        res += tab1 + "result = ( " + lhs + " == " +  rhs + " );\n";
        res += tab1 + "if (!result) return result;\n";
    }

    return res;
}

std::string
MyClass::toFCodeLessIndex(Field const &  fd,
                          std::string const &  tab,
                          std::string const &  lhsName,
                          std::string const &  rhsName) const
{
    std::string  res;
    std::string const  tab1 = tab + std::string(getDefTab());
    std::string const  tab2 = tab + std::string(getDefTab() + getDefTab());

    std::string const  rhs = rhsName + "." + fd.getPrivateName();
    std::string  lhs = fd.getPrivateName();
    if (!lhsName.empty()) {
        lhs = lhsName + "." + fd.getPrivateName();
    }

    if (fd.isPointer()) {
        res += tab1 + "if (" + lhs + " == nullptr && " + rhs + " != nullptr) {\n";
        res += tab2 + "return true;\n";
        res += tab1 + "}\n";
        res += tab1 + "if (" + rhs + " == nullptr && " + lhs + " != nullptr) {\n";
        res += tab2 + "return false;\n";
        res += tab1 + "}\n";
        res += tab1 + "if (" + lhs + " == nullptr && " + rhs + " == nullptr) {\n";
        res += tab2 + ";\n";
        res += tab1 + "} else {\n";
        res += tab2 + "if (*" + lhs + " < *" + rhs + ") return true;\n";
        res += tab2 + "if (*" + rhs + " < *" + lhs + ") return false;\n";
        res += tab1 + "}\n";
    } else {
        res += tab1 + "if (" + lhs + " < " + rhs + ") return true;\n";
        res += tab1 + "if (" + rhs + " < " + lhs + ") return false;\n";
    }

    return res;
}

std::string
MyClass::toFCodeToStringIndex(Field const &  fd) const
{
    std::string  res;
    std::string const  tab1(getDefTab());
    std::string const  tab2(getDefTab() + getDefTab());
    std::string const  functionName("toString");

    if (fd.isPointer()) {
        res += tab1 + "if (" + fd.getPrivateName() + " == nullptr) {\n";
        res += tab2 + "xu::append(res, \"\");\n";
        res += tab1 + "} else {\n";
        res += tab2 + "std::string  ptrRes;\n";
        res += tab2 + "xu::append(ptrRes, xu::" + functionName + "(*" +
                fd.getPrivateName() + "));\n";
        res += tab2 + "xu::append(res, ptrRes);\n";
        res += tab1 + "}\n";
    } else {
        res += tab1 + "xu::append(res, xu::" + functionName + "(" +
                fd.getPrivateName() + "));\n";
    }

    return res;
}

std::string
MyClass::toFCodeFromStringIndex(Field const &  fd,
                                size_t const  vi_index) const
{
    std::string  res;
    std::string const  tab1(getDefTab());
    std::string const  tab2(tab1 + tab1);
    std::string const  tab3(tab1 + tab2);
    std::string const  tab4(tab2 + tab2);
    std::string const  functionName("fromString");

    if (fd.isPointer()) {
        res += tab2 + "{\n";
        res += tab3 + "delete me." + fd.getPrivateName() + ";\n";
        res += tab3 + "me." + fd.getPrivateName() + " = nullptr;\n";
        res += tab3 + "const auto  v2vi { xu::viewIcode(vi[" +
                std::to_string(vi_index) + "]) };\n";
        res += tab3 + "if (v2vi.size() == 1) {\n";
        res += tab4 + "me." + fd.getPrivateName() + " = new " + fd.getTypeName() +
                ";\n";
        res += tab4 + "if (!xu::" + functionName + "(*me." +
                fd.getPrivateName() + ", v2vi[0]))  err.push_back({" +
                std::to_string(vi_index) + "});\n";
        res += tab3 + "}\n";
        res += tab2 + "}\n";
    } else {
        res += tab2 + "if (!xu::" + functionName + "(me." + fd.getPrivateName() +
                ", vi[" + std::to_string(vi_index) + "]))  err.push_back({" +
                std::to_string(vi_index) + "});\n";
    }

    return res;
}

void
MyClass::appendFieldIndex()
{
    size_t const  index = m_field.size() - 1;
    Field const &  fd = m_field[index];

    m_styleField.push_back(index);
    if (m_updateToString)  m_serzField.push_back(index);

    for (auto &  it: m_eobjList) {
        switch (it.first) {
        case Etype::eConstructors :
        case Etype::eTplConstructors :
            {
                std::shared_ptr<Functions>  vec =
                        std::dynamic_pointer_cast<Functions>(it.second);
                std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                for (auto &  fn: fns) {
                    auto  defV = fn->getDefValueCtor();
                    defV.push_back(fd.getCtorDefValue());
                    fn->setDefValueCtor(defV);
                }
                vec->setObjList(fns);
            }
            break;
        case Etype::eDefaultConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  defV = fn->getDefValueCtor();
                defV.push_back(fd.getCtorDefValue());
                fn->setDefValueCtor(defV);
            }
            break;
        case Etype::eCopyConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  defV = fn->getDefValueCtor();
                defV.push_back(getOther() + "." + fd.getPrivateName());
                fn->setDefValueCtor(defV);
            }
            break;
        case Etype::eMoveConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  defV = fn->getDefValueCtor();
                defV.push_back("std::move(" + getOther() + "." + fd.getPrivateName() + ")");
                fn->setDefValueCtor(defV);
            }
            break;
        default :
            break;
        }
    }
}

void
MyClass::updateFieldIndex(size_t const  index)
{
    Field const &  fd = m_field[index];

    for (auto &  it: m_eobjList) {
        switch (it.first) {
        case Etype::eDefaultConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  defV = fn->getDefValueCtor();
                defV[index] = fd.getCtorDefValue();
                fn->setDefValueCtor(defV);
            }
            break;
        case Etype::eCopyConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  defV = fn->getDefValueCtor();
                defV[index] = getOther() + "." + fd.getPrivateName();
                fn->setDefValueCtor(defV);
            }
            break;
        case Etype::eMoveConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  defV = fn->getDefValueCtor();
                defV[index] = "std::move(" + getOther() + "." + fd.getPrivateName() + ")";
                fn->setDefValueCtor(defV);
            }
            break;
        default :
            break;
        }
    }
}

void
MyClass::insertFieldIndex(size_t const  index)
{
    Field const &  fd = m_field[index];

    for (auto &  id: m_styleField) {
        if (id >= index)  id++;
    }
    for (auto &  id: m_IDField) {
        if (id >= index)  id++;
    }
    for (auto &  id: m_serzField) {
        if (id >= index)  id++;
    }

    m_styleField.push_back(index);
    if (m_updateToString)  m_serzField.push_back(index);

    for (auto &  it: m_eobjList) {
        switch (it.first) {
        case Etype::eConstructors :
        case Etype::eTplConstructors :
            {
                std::shared_ptr<Functions>  vec =
                        std::dynamic_pointer_cast<Functions>(it.second);
                std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                for (auto &  fn: fns) {
                    auto  defV = fn->getDefValueCtor();
                    auto  dv = defV.begin() + index;
                    defV.insert(dv, fd.getCtorDefValue());
                    fn->setDefValueCtor(defV);
                }
                vec->setObjList(fns);
            }
            break;
        case Etype::eDefaultConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  defV = fn->getDefValueCtor();
                auto  dv = defV.begin() + index;
                defV.insert(dv, fd.getCtorDefValue());
                fn->setDefValueCtor(defV);
            }
            break;
        case Etype::eCopyConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  defV = fn->getDefValueCtor();
                auto  dv = defV.begin() + index;
                defV.insert(dv, getOther() + "." + fd.getPrivateName());
                fn->setDefValueCtor(defV);
            }
            break;
        case Etype::eMoveConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  defV = fn->getDefValueCtor();
                auto  dv = defV.begin() + index;
                defV.insert(dv, "std::move(" + getOther() + "." + fd.getPrivateName() + ")");
                fn->setDefValueCtor(defV);
            }
            break;
        default :
            break;
        }
    }
}

void
MyClass::deleteFieldIndex(size_t const  index)
{
    auto  it1 = std::find(m_styleField.begin(), m_styleField.end(), index);
    m_styleField.erase(it1);
    for (auto &  id: m_styleField) {
        if (id > index)  id--;
    }

    auto  it2 = std::find(m_IDField.begin(), m_IDField.end(), index);
    if (it2 != m_IDField.end()) {
        m_IDField.erase(it2);
    }
    for (auto &  id: m_IDField) {
        if (id > index)  id--;
    }

    auto  it3 = std::find(m_serzField.begin(), m_serzField.end(), index);
    if (it3 != m_serzField.end()) {
        m_serzField.erase(it3);
    }
    for (auto &  id: m_serzField) {
        if (id > index)  id--;
    }

    for (auto &  it: m_eobjList) {
        switch (it.first) {
        case Etype::eConstructors :
        case Etype::eTplConstructors :
            {
                std::shared_ptr<Functions>  vec =
                        std::dynamic_pointer_cast<Functions>(it.second);
                std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                for (auto &  fn: fns) {
                    auto  defV = fn->getDefValueCtor();
                    defV.erase(defV.begin() + index);
                    fn->setDefValueCtor(defV);
                }
                vec->setObjList(fns);
            }
            break;
        case Etype::eDefaultConstructorFn :
        case Etype::eCopyConstructorFn :
        case Etype::eMoveConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  defV = fn->getDefValueCtor();
                defV.erase(defV.begin() + index);
                fn->setDefValueCtor(defV);
            }
            break;
        default :
            break;
        }
    }
}

void
MyClass::appendMulInhClassIndex()
{
    for (auto &  it: m_eobjList) {
        switch (it.first) {
        case Etype::eConstructors :
        case Etype::eTplConstructors :
            {
                std::shared_ptr<Functions>  vec =
                        std::dynamic_pointer_cast<Functions>(it.second);
                std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                for (auto &  fn: fns) {
                    auto  mulV = fn->getInhValueBaseClass();
                    mulV.push_back("");
                    fn->setInhValueBaseClass(mulV);
                }
                vec->setObjList(fns);
            }
            break;
        case Etype::eDefaultConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  mulV = fn->getInhValueBaseClass();
                mulV.push_back("");
                fn->setInhValueBaseClass(mulV);
            }
            break;
        case Etype::eCopyConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  mulV = fn->getInhValueBaseClass();
                mulV.push_back(getOther());
                fn->setInhValueBaseClass(mulV);
            }
            break;
        case Etype::eMoveConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  mulV = fn->getInhValueBaseClass();
                mulV.push_back("std::move(" + getOther() + ")");
                fn->setInhValueBaseClass(mulV);
            }
            break;
        default :
            break;
        }
    }
}

void
MyClass::insertMulInhClassIndex(size_t const  index)
{
    for (auto &  it: m_eobjList) {
        switch (it.first) {
        case Etype::eConstructors :
        case Etype::eTplConstructors :
            {
                std::shared_ptr<Functions>  vec =
                        std::dynamic_pointer_cast<Functions>(it.second);
                std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                for (auto &  fn: fns) {
                    auto  mulV = fn->getInhValueBaseClass();
                    auto  mulVit = mulV.begin() + index;
                    mulV.insert(mulVit, "");
                    fn->setInhValueBaseClass(mulV);
                }
                vec->setObjList(fns);
            }
            break;
        case Etype::eDefaultConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  mulV = fn->getInhValueBaseClass();
                auto  mulVit = mulV.begin() + index;
                mulV.insert(mulVit, "");
                fn->setInhValueBaseClass(mulV);
            }
            break;
        case Etype::eCopyConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  mulV = fn->getInhValueBaseClass();
                auto  mulVit = mulV.begin() + index;
                mulV.insert(mulVit, getOther());
                fn->setInhValueBaseClass(mulV);
            }
            break;
        case Etype::eMoveConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  mulV = fn->getInhValueBaseClass();
                auto  mulVit = mulV.begin() + index;
                mulV.insert(mulVit, "std::move(" + getOther() + ")");
                fn->setInhValueBaseClass(mulV);
            }
            break;
        default :
            break;
        }
    }
}

void
MyClass::deleteMulInhClassIndex(size_t const  index)
{
    for (auto &  it: m_eobjList) {
        switch (it.first) {
        case Etype::eConstructors :
        case Etype::eTplConstructors :
            {
                std::shared_ptr<Functions>  vec =
                        std::dynamic_pointer_cast<Functions>(it.second);
                std::vector<std::shared_ptr<Function>>  fns = vec->getObjList();
                for (auto &  fn: fns) {
                    auto  mulV = fn->getInhValueBaseClass();
                    mulV.erase(mulV.begin() + index);
                    fn->setInhValueBaseClass(mulV);
                }
                vec->setObjList(fns);
            }
            break;
        case Etype::eDefaultConstructorFn :
        case Etype::eCopyConstructorFn :
        case Etype::eMoveConstructorFn :
            {
                std::shared_ptr<Function>  fn =
                        std::dynamic_pointer_cast<Function>(it.second);
                auto  mulV = fn->getInhValueBaseClass();
                mulV.erase(mulV.begin() + index);
                fn->setInhValueBaseClass(mulV);
            }
            break;
        default :
            break;
        }
    }
}

bool
MyClass::checkEobject(std::pair<Etype, std::shared_ptr<EObject>> const &  value) const
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
    case Etype::eConstructors :
    case Etype::eTplConstructors :
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

    case Etype::eVirtualEqFn :
    case Etype::eVirtualLessFn :
    case Etype::eInSwapFn :
    case Etype::eVirtualExchangeFn :
    case Etype::eToStringFn :
    case Etype::eVirtualSerializeFn :
    case Etype::eInFromStringFn :
    case Etype::eDeserializeFn :
        res = true;
        break;
    default :
        break;
    }

    return res;
}

bool
MyClass::checkDeleteEobject(size_t const  index) const
{
    bool  res = true;

    Etype const  etp = m_eobjList[index].first;
    switch (m_classtype) {
    case ClassType::cppFinal :
        if ((etp == Etype::eInSwapFn && m_swapFunction) ||
                (etp == Etype::eToStringFn && m_toStringFunction) ||
                (etp == Etype::eInFromStringFn && m_toStringFunction)) {
            res = false;
        }
        break;
    case ClassType::cppBase :
        if ((etp == Etype::eInSwapFn && m_swapFunction) ||
                (etp == Etype::eToStringFn && m_toStringFunction) ||
                (etp == Etype::eInFromStringFn && m_toStringFunction)) {
            res = false;
        }
        if ((etp == Etype::eVirtualEqFn && m_eqFunction) ||
                (etp == Etype::eVirtualLessFn && m_lessFunction) ||
                (etp == Etype::eVirtualExchangeFn && m_swapFunction) ||
                (etp == Etype::eVirtualSerializeFn && m_toStringFunction) ||
                (etp == Etype::eDeserializeFn && m_toStringFunction)) {
            res = false;
        }
        break;
    case ClassType::cppInherit :
        if ((etp == Etype::eVirtualEqFn && m_eqFunction) ||
                (etp == Etype::eVirtualLessFn && m_lessFunction) ||
                (etp == Etype::eVirtualExchangeFn && m_swapFunction) ||
                (etp == Etype::eVirtualSerializeFn && m_toStringFunction) ||
                (etp == Etype::eDeserializeFn && m_toStringFunction)) {
            res = false;
        }
        break;
    }

    return res;
}

std::string
MyClass::class_field_toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    std::string  fdAutoCode;
    for (auto const &  fd: m_field) {
        fdAutoCode += fd.toHBlock(tabStr);
    }

    if (fdAutoCode.size() > 0) {
        res += "\n";
        res += tabStr + "private:\n";
        res += "\n";
        res += fdAutoCode;
    }

    return res;
}

std::string
MyClass::class_field_FnDcl(bool const  isPubLabel /* = true */,
                           std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    std::string  fdAutoCode;
    for (auto const &  fd: m_field) {
        fdAutoCode += "\n";
        fdAutoCode += fd.hCodeDcl(tabStr);
    }

    if (fdAutoCode.size() > 0) {
        res += "\n";
        if (isPubLabel) {
            res += tabStr + "public:\n";
        }
        res += fdAutoCode;
    }

    return res;
}

std::string
MyClass::class_begin(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;
    const std::string  tab1(getDefTab());

    res += m_hBeginBefore;

    if (m_replaceClassName.size() > 0) {
        res += m_replaceClassName;
    } else {
        res += class_tplStringNotDefVal() + tabStr + "class ";

        if (m_attribute.size() > 0) {
            res += m_attribute + " ";
        }
        if (m_alignByte > 1) {
            res += "alignas(" + std::to_string(m_alignByte) + ") ";
        }
        res += m_className;

        if (m_finalClass) {
            res += " final";
        }
    }

    if (m_classtype == ClassType::cppFinal ||
            m_classtype == ClassType::cppBase ) {
        if (m_replaceClassName.size() == 0) {
            res += "\n";
        }
        res += "{\n";
    } else {
        if (m_replaceClassName.size() == 0) {
            res += " : public ";
            if (std::get<1>(m_baseClassFirst)) {
                res += "virtual ";
            }
            res += std::get<0>(m_baseClassFirst);

            const std::string  sp(m_baseClassFirst.first.size() + 9, '\x20');
            for (auto const &  it: m_mulInhClass) {
                res += ",\n";
                switch (std::get<1>(it)) {
                case Purview::purPublic:
                    res += sp + "public ";
                    break;
                case Purview::purProtected:
                    res += sp + "protected ";
                    break;
                case Purview::purPrivate:
                    res += sp + "private ";
                    break;
                }
                if (std::get<2>(it)) {
                    res += "virtual ";
                }
                res += std::get<0>(it);
            }
            res += "\n";
        }
        res += "{\n";
    }
    res += m_hBeginBehind;

    return res;
}

std::string
MyClass::class_end(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;
    res += m_hEndBefore;
    res += "\n" + tabStr + "};\n";
    res += m_hEndBehind;
    return res;
}

std::string
MyClass::class_friend(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    if (m_parentModulePtr) {
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> const
                mobj = m_parentModulePtr->getEobjList();
        for (auto const &  it: mobj) {
            switch (it.first) {
            case Etype::eFunction :
            case Etype::eEqFn :
            case Etype::eNotEqFn :
            case Etype::eLessFn :
            case Etype::eLessEqFn :
            case Etype::eGreaterFn :
            case Etype::eGreaterEqFn :
                {
                    std::shared_ptr<Function>  objPtr =
                            std::dynamic_pointer_cast<Function>(it.second);
                    std::vector<std::string> const  friendCName =
                            objPtr->getFriendClassName();
                    if (friendCName.size() == 1 && friendCName[0] == m_className) {
                        res += objPtr->friendDeclaration(tabStr);
                    }
                }
                break;
            case Etype::eFunctions :
            case Etype::eStaticFunctions :
            case Etype::eConstexprFunctions :
            case Etype::eTplFunctions :
            case Etype::eTplStaticFunctions :
            case Etype::eTplConstexprFunctions :
                {
                    std::shared_ptr<Functions>  objPtr =
                            std::dynamic_pointer_cast<Functions>(it.second);
                    std::vector<std::shared_ptr<Function>>  olist = objPtr->getObjList();
                    for (auto const &  it: olist) {
                        std::vector<std::string>  friendCName =
                                it->getFriendClassName();
                        auto  item = std::find(friendCName.begin(), friendCName.end(),
                                m_className);
                        if (item != friendCName.end()) {
                            res += objPtr->friendDeclaration(tabStr);
                        }
                    }
                }
                break;
            case Etype::eClass :
                {
                    std::shared_ptr<MyClass>  objPtr =
                            std::dynamic_pointer_cast<MyClass>(it.second);
                    std::vector<std::string>  friendCName =
                            objPtr->getFriendClassName();
                    auto  item = std::find(friendCName.begin(), friendCName.end(),
                            m_className);
                    if (item != friendCName.end()) {
                        res += objPtr->friendDeclaration(tabStr);
                    }
                }
                break;
            default :
                break;
            }
        }
    }

    return res;
}

std::string
MyClass::class_tplStringNotDefVal(const size_t  index /* = 0 */) const
{
    std::string  res;

    if (m_template) {
        res += "template <";
        for (size_t  i = 0; i < m_classTparam.size(); ++i) {
            res += m_classTparam[i].getTypename() + " " + m_classTparam[i].getTName();
            if (index > 0) {
                res += std::to_string(index);
            }
            if (m_classTparam[i].getDefalutValue().size() > 0) {
                res += " /* = " + m_classTparam[i].getDefalutValue() + " */";
            }
            if (i != m_classTparam.size() - 1) {
                res += ", ";
            }
        }
        res += ">\n";
    }

    return res;
}

void
MyClass::classToInternal(MyClass *  myClass,
                         bool const  isInternal)
{
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *
            objList = myClass->getEObjectPtr();
    if (isInternal) {
        for (auto &  it: *objList) {
            EObject *  ptr = it.second.get();
            if (Function *  fnPtr = dynamic_cast<Function *>(ptr)) {
                fnPtr->setInternal(true);
            } else if (Functions *  ptrFns = dynamic_cast<Functions *>(ptr)) {
                std::vector<std::shared_ptr<Function>> &
                        fns = ptrFns->getFunctionRef();
                for (auto &  thisFn: fns) {
                    thisFn->setInternal(true);
                }
            } else if (MyClass *  clsPtr = dynamic_cast<MyClass *>(ptr)) {
                classToInternal(clsPtr, true);
            }
        }
    } else {
        for (auto &  it: *objList) {
            EObject *  ptr = it.second.get();
            if (Function *  fnPtr = dynamic_cast<Function *>(ptr)) {
                fnPtr->setInternal(false);
            } else if (Functions *  ptrFns = dynamic_cast<Functions *>(ptr)) {
                std::vector<std::shared_ptr<Function>> &
                        fns = ptrFns->getFunctionRef();
                for (auto &  thisFn: fns) {
                    thisFn->setInternal(false);
                }
            } else if (MyClass *  clsPtr = dynamic_cast<MyClass *>(ptr)) {
                classToInternal(clsPtr, false);
            }
        }
    }
}

std::vector<size_t>
MyClass::getStringErr() const
{
    return m_stringErr;
}

Module *
MyClass::getParentModulePtr() const
{
    return m_parentModulePtr;
}

void
MyClass::setParentModulePtr(Module *  value)
{
    m_parentModulePtr = value;
}

std::vector<std::pair<Etype, std::shared_ptr<EObject>>>
MyClass::getEobjList() const
{
    return m_eobjList;
}

std::vector<Field>
MyClass::getField() const
{
    return m_field;
}

std::vector<size_t>
MyClass::getStyleField() const
{
    return m_styleField;
}

void
MyClass::setStyleField(const std::vector<size_t> &  value)
{
    std::vector<size_t>  idfd;
    const size_t  fdsize = m_field.size();
    for (size_t  i: value) {
        auto  rep = std::find(idfd.begin(), idfd.end(), i);
        if (rep == idfd.end() && i < fdsize) {
            idfd.push_back(i);
        }
    }
    if (idfd.size() < fdsize) {
        for (size_t  i = 0; i < fdsize; ++i) {
            auto  rep = std::find(idfd.begin(), idfd.end(), i);
            if (rep == idfd.end()) {
                idfd.push_back(i);
            }
        }
    }
    m_styleField = std::move(idfd);
}

std::vector<size_t>
MyClass::getIDField() const
{
    return m_IDField;
}

void
MyClass::setIDField(const std::vector<size_t> &  value)
{
    std::vector<size_t>  idfd;
    const size_t  fdsize = m_field.size();
    for (size_t  i: value) {
        auto  rep = std::find(idfd.begin(), idfd.end(), i);
        if (rep == idfd.end() && i < fdsize) {
            idfd.push_back(i);
        }
    }
    m_IDField = std::move(idfd);
}

std::vector<size_t>
MyClass::getSerzField() const
{
    return m_serzField;
}

void
MyClass::setSerzField(const std::vector<size_t> &  value)
{
    std::vector<size_t>  idfd;
    const size_t  fdsize = m_field.size();
    for (size_t  i: value) {
        auto  rep = std::find(idfd.begin(), idfd.end(), i);
        if (rep == idfd.end() && i < fdsize) {
            idfd.push_back(i);
        }
    }
    m_serzField = std::move(idfd);
}

std::string
MyClass::getClassName() const
{
    return m_className;
}

void
MyClass::setClassName(const std::string &  value)
{
    std::string const  oldName = m_className;

    m_className = xu::trim(value);
    if (!xu::checkReg(m_className)) {
        m_className = "MyClass1";
    }
    m_className[0] = xu::toupperS(m_className[0]);
    setTreeLabel("C   " + m_className);

    if (m_updateFilename && m_parentModulePtr) {
        m_parentModulePtr->setFilename(m_className);
    }

    for (auto &  fnObj: m_eobjList) {
        switch (fnObj.first) {
        case Etype::eConstructors :
        case Etype::eTplConstructors :
            std::dynamic_pointer_cast<Functions>(fnObj.second)->
                    setParentClassPtr(this);
            break;
        case Etype::eDefaultConstructorFn :
        case Etype::eCopyConstructorFn :
        case Etype::eMoveConstructorFn :
        case Etype::eDestructorFn :
            std::dynamic_pointer_cast<Function>(fnObj.second)->
                    setParentClassPtr(this);
            std::dynamic_pointer_cast<Function>(fnObj.second)->
                    setParam({});
            break;
        case Etype::eVirtualEqFn :
        case Etype::eVirtualLessFn :
        case Etype::eInSwapFn :
        case Etype::eVirtualExchangeFn :
            std::dynamic_pointer_cast<Function>(fnObj.second)->
                    setParam({});
            break;
        case Etype::eCopyOperatorEqFn :
        case Etype::eMoveOperatorEqFn :
            std::dynamic_pointer_cast<Function>(fnObj.second)->
                    setParam({});
            std::dynamic_pointer_cast<Function>(fnObj.second)->
                    setReturnType("");
            break;
        default :
            break;
        }
    }

    if (m_parentModulePtr) {
        std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  fns =
                m_parentModulePtr->getEObjectListRef();
        for (auto &  it: fns) {
            switch (it.first) {
            case Etype::eFunctions :
            case Etype::eStaticFunctions :
                {
                    std::vector<std::shared_ptr<Function>> &  friends =
                            std::dynamic_pointer_cast<Functions>(
                            it.second)->getFunctionRef();
                    for (auto &  thisFn: friends) {
                        std::vector<std::string>  frs = thisFn->getFriendClassName();
                        for (auto &  fName:  frs) {
                            if (fName == oldName)  fName = m_className;
                        }
                        thisFn->setFriendClassName(frs);
                    }
                }
                break;
            case Etype::eEqFn :
                {
                    EqFn *  fnPtr = static_cast<EqFn *>(it.second.get());
                    if (fnPtr->getParentClassPtr() == this) {
                        fnPtr->setClassName(m_className);
                    }
                }
                break;
            case Etype::eNotEqFn :
                {
                    NotEqFn *  fnPtr = static_cast<NotEqFn *>(it.second.get());
                    if (fnPtr->getParentClassPtr() == this) {
                        fnPtr->setClassName(m_className);
                    }
                }
                break;
            case Etype::eLessFn :
                {
                    LessFn *  fnPtr = static_cast<LessFn *>(it.second.get());
                    if (fnPtr->getParentClassPtr() == this) {
                        fnPtr->setClassName(m_className);
                    }
                }
                break;
            case Etype::eLessEqFn :
                {
                    LessEqFn *  fnPtr = static_cast<LessEqFn *>(it.second.get());
                    if (fnPtr->getParentClassPtr() == this) {
                        fnPtr->setClassName(m_className);
                    }
                }
                break;
            case Etype::eGreaterFn :
                {
                    GreaterFn *  fnPtr = static_cast<GreaterFn *>(it.second.get());
                    if (fnPtr->getParentClassPtr() == this) {
                        fnPtr->setClassName(m_className);
                    }
                }
                break;
            case Etype::eGreaterEqFn :
                {
                    GreaterEqFn *  fnPtr = static_cast<GreaterEqFn *>(
                            it.second.get());
                    if (fnPtr->getParentClassPtr() == this) {
                        fnPtr->setClassName(m_className);
                    }
                }
                break;
            case Etype::eExtSwapFn :
                {
                    ExtSwapFn *  fnPtr = static_cast<ExtSwapFn *>(it.second.get());
                    if (fnPtr->getParentClassPtr() == this) {
                        fnPtr->setClassName(m_className);
                    }
                }
                break;
            case Etype::eExtFromStringFn :
                {
                    ExtFromStringFn *  fnPtr = static_cast<ExtFromStringFn *>(
                            it.second.get());
                    if (fnPtr->getParentClassPtr() == this) {
                        fnPtr->setClassName(m_className);
                    }
                }
                break;
            default :
                break;
            }
        }
    }
}

std::string
MyClass::getReplaceClassName() const
{
    return m_replaceClassName;
}

void
MyClass::setReplaceClassName(const std::string &  value)
{
    m_replaceClassName = value;
    xu::procCode(m_replaceClassName);
}

void
MyClass::setReplaceClassName(std::string &&  value)
{
    m_replaceClassName = std::move(value);
    xu::procCode(m_replaceClassName);
}

std::string
MyClass::getDocment() const
{
    return m_docment;
}

void
MyClass::setDocment(const std::string &  value)
{
    m_docment = value;
}

void
MyClass::setDocment(std::string &&  value)
{
    m_docment = std::move(value);
}

std::string
MyClass::getTestCode() const
{
    return m_testCode;
}

void
MyClass::setTestCode(const std::string &  value)
{
    m_testCode = value;
    xu::procCode(m_testCode);
}

void
MyClass::setTestCode(std::string &&  value)
{
    m_testCode = std::move(value);
    xu::procCode(m_testCode);
}

ClassType
MyClass::getClasstype() const
{
    return m_classtype;
}

void
MyClass::setClasstype(const ClassType  value)
{
    ClassType const  oldVal = m_classtype;
    if (oldVal == value)  return;

    m_classtype = value;
    if (m_classtype == ClassType::cppFinal) {
        m_finalClass = true;
    } else if (m_classtype == ClassType::cppBase) {
        m_finalClass = false;
    }
}

int
MyClass::getAlignByte() const
{
    return m_alignByte;
}

void
MyClass::setAlignByte(const int  value)
{
    if (value == 4 || value == 8 || value == 16 || value == 32 ||
            value == 64 || value == 128) {
        m_alignByte = value;
    } else {
        m_alignByte = 0;
    }
}

std::string
MyClass::getBaseClassPrarm() const
{
    return m_baseClassPrarm;
}

void
MyClass::setBaseClassPrarm(const std::string &  value)
{
    m_baseClassPrarm = xu::trim(value);
    if (!xu::checkReg(m_baseClassPrarm)) {
        m_baseClassPrarm = "";
    }
}

std::pair<std::string, bool>
MyClass::getBaseClassFirst() const
{
    return m_baseClassFirst;
}

void
MyClass::setBaseClassFirst(const std::pair<std::string, bool> &  value)
{
    m_baseClassFirst = value;
    std::get<0>(m_baseClassFirst) = xu::trim(std::get<0>(m_baseClassFirst));
    if (!checkReg(std::get<0>(m_baseClassFirst))) {
        m_baseClassFirst.first = "";
    }
}

std::vector<std::tuple<std::string, Purview, bool>>
MyClass::getMulInhClass() const
{
    return m_mulInhClass;
}

InheritID
MyClass::getInheritID() const
{
    return m_inheritID;
}

void
MyClass::setInheritID(const InheritID  value)
{
    m_inheritID = value;
}

std::vector<Tpl>
MyClass::getClassTparam() const
{
    return m_classTparam;
}

void
MyClass::setClassTparam(const std::vector<Tpl> &  value)
{
    m_classTparam = value;
}

void
MyClass::setClassTparam(std::vector<Tpl> &&  value)
{
    m_classTparam = std::move(value);
}

std::string
MyClass::getAttribute() const
{
    return m_attribute;
}

void
MyClass::setAttribute(const std::string &  value)
{
    m_attribute = value;
}

void
MyClass::setAttribute(std::string &&  value)
{
    m_attribute = std::move(value);
}

std::vector<std::string>
MyClass::getFriendClassName() const
{
    return m_friendClassName;
}

void
MyClass::setFriendClassName(const std::vector<std::string> &  value)
{
    m_friendClassName = value;
}

void
MyClass::setFriendClassName(std::vector<std::string> &&  value)
{
    m_friendClassName = std::move(value);
}

std::string
MyClass::getHBeginBefore() const
{
    return m_hBeginBefore;
}

void
MyClass::setHBeginBefore(const std::string &  value)
{
    m_hBeginBefore = value;
    xu::procCode(m_hBeginBefore);
}

void
MyClass::setHBeginBefore(std::string &&  value)
{
    m_hBeginBefore = std::move(value);
    xu::procCode(m_hBeginBefore);
}

std::string
MyClass::getHBeginBehind() const
{
    return m_hBeginBehind;
}

void
MyClass::setHBeginBehind(const std::string &  value)
{
    m_hBeginBehind = value;
    xu::procCode(m_hBeginBehind);
}

void
MyClass::setHBeginBehind(std::string &&  value)
{
    m_hBeginBehind = std::move(value);
    xu::procCode(m_hBeginBehind);
}

std::string
MyClass::getHEndBefore() const
{
    return m_hEndBefore;
}

void
MyClass::setHEndBefore(const std::string &  value)
{
    m_hEndBefore = value;
    xu::procCode(m_hEndBefore);
}

void
MyClass::setHEndBefore(std::string &&  value)
{
    m_hEndBefore = std::move(value);
    xu::procCode(m_hEndBefore);
}

std::string
MyClass::getHEndBehind() const
{
    return m_hEndBehind;
}

void
MyClass::setHEndBehind(const std::string &  value)
{
    m_hEndBehind = value;
    xu::procCode(m_hEndBehind);
}

void
MyClass::setHEndBehind(std::string &&  value)
{
    m_hEndBehind = std::move(value);
    xu::procCode(m_hEndBehind);
}

std::string
MyClass::getBeforeDcl() const
{
    return m_beforeDcl;
}

void
MyClass::setBeforeDcl(const std::string &  value)
{
    m_beforeDcl = value;
    xu::procCode(m_beforeDcl);
}

void
MyClass::setBeforeDcl(std::string &&  value)
{
    m_beforeDcl = std::move(value);
    xu::procCode(m_beforeDcl);
}

std::string
MyClass::getBehindDcl() const
{
    return m_behindDcl;
}

void
MyClass::setBehindDcl(const std::string &  value)
{
    m_behindDcl = value;
    xu::procCode(m_behindDcl);
}

void
MyClass::setBehindDcl(std::string &&  value)
{
    m_behindDcl = std::move(value);
    xu::procCode(m_behindDcl);
}

bool
MyClass::isUpdateToString() const
{
    return m_updateToString;
}

void
MyClass::setUpdateToString(const bool  value)
{
    m_updateToString = value;
}

bool
MyClass::isFinalClass() const
{
    return m_finalClass;
}

void
MyClass::setFinalClass(const bool  value)
{
    if (m_classtype == ClassType::cppFinal) {
        m_finalClass = true;
    } else if (m_classtype == ClassType::cppBase) {
        m_finalClass = false;
    } else {
        m_finalClass = value;
    }
}

bool
MyClass::isTemplate() const
{
    return m_template;
}

void
MyClass::setTemplate(const bool  value)
{
    m_template = value;
}

bool
MyClass::isUpdateFilename() const
{
    return m_updateFilename;
}

void
MyClass::setUpdateFilename(const bool  value)
{
    m_updateFilename = value;
    if (m_updateFilename && m_parentModulePtr) {
        m_parentModulePtr->setFilename(m_className);
    }
}

bool
MyClass::isSetterReturnThis() const
{
    return m_setterReturnThis;
}

void
MyClass::setSetterReturnThis(const bool  value)
{
    m_setterReturnThis = value;
    for (Field &  fd: m_field) {
        auto  fns = fd.getActionFn();
        fd.setActionFn(fns);
    }
}

bool
MyClass::isImpl() const
{
    return m_impl;
}

void
MyClass::setImpl(const bool  value)
{
    m_impl = value;
}

bool
MyClass::hasLessFunction() const
{
    return m_lessFunction;
}

void
MyClass::setLessFunction(const bool  value)
{
    m_lessFunction = value;
}

bool
MyClass::hasEqFunction() const
{
    return m_eqFunction;
}

void
MyClass::setEqFunction(const bool  value)
{
    m_eqFunction = value;
}

bool
MyClass::hasSwapFunction() const
{
    return m_swapFunction;
}

void
MyClass::setSwapFunction(const bool  value)
{
    m_swapFunction = value;
}

bool
MyClass::hasToStringFunction() const
{
    return m_toStringFunction;
}

void
MyClass::setToStringFunction(const bool  value)
{
    m_toStringFunction = value;
}

bool
MyClass::isInternal() const
{
    return m_internal;
}

void
MyClass::setInternal(const bool  value)
{
    m_internal = value;
    classToInternal(this, m_internal);
}

bool
MyClass::isIndPublicLabel() const
{
    return m_indPublicLabel;
}

void
MyClass::setIndPublicLabel(const bool  value)
{
    m_indPublicLabel = value;
}

bool
MyClass::hasDefCtor() const
{
    return m_defCtor;
}

void
MyClass::setDefCtor(const bool  value)
{
    m_defCtor = value;
}

bool
MyClass::hasCopyCtor() const
{
    return m_copyCtor;
}

void
MyClass::setCopyCtor(const bool  value)
{
    m_copyCtor = value;
}

bool
MyClass::hasMoveCtor() const
{
    return m_moveCtor;
}

void
MyClass::setMoveCtor(const bool  value)
{
    m_moveCtor = value;
}

bool
MyClass::hasDtor() const
{
    return m_dtor;
}

void
MyClass::setDtor(const bool  value)
{
    m_dtor = value;
}

bool
MyClass::hasCopyOpEq() const
{
    return m_copyOpEq;
}

void
MyClass::setCopyOpEq(const bool  value)
{
    m_copyOpEq = value;
}

bool
MyClass::hasMoveOpEq() const
{
    return m_moveOpEq;
}

void
MyClass::setMoveOpEq(const bool  value)
{
    m_moveOpEq = value;
}

bool
MyClass::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const MyClass &  rhs = dynamic_cast<const MyClass &>(value);

        result = this->EObject::equal(value);
        if (!result) return result;

        result = ( m_className == rhs.m_className );
        if (!result) return result;

        result = ( m_field == rhs.m_field );
        if (!result) return result;

        result = ( m_classtype == rhs.m_classtype );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
MyClass::less(const EObject &  value) const
{
    if (this->EObject::less(value)) return true;
    if (!(this->EObject::equal(value))) return false;

    try {
        const MyClass &  rhs = dynamic_cast<const MyClass &>(value);

        if (m_className < rhs.m_className) return true;
        if (rhs.m_className < m_className) return false;

        if (m_field < rhs.m_field) return true;
        if (rhs.m_field < m_field) return false;

        if (m_classtype < rhs.m_classtype) return true;
        if (rhs.m_classtype < m_classtype) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
MyClass::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_eobjList));
    xu::append(res, xu::toString(m_field));
    xu::append(res, xu::toString(m_styleField));
    xu::append(res, xu::toString(m_IDField));
    xu::append(res, xu::toString(m_serzField));
    xu::append(res, xu::toString(m_className));
    xu::append(res, xu::toString(m_replaceClassName));
    xu::append(res, xu::toString(m_docment));
    xu::append(res, xu::toString(m_testCode));
    xu::append(res, xu::toString(m_classtype));
    xu::append(res, xu::toString(m_alignByte));
    xu::append(res, xu::toString(m_baseClassPrarm));
    xu::append(res, xu::toString(m_baseClassFirst));
    xu::append(res, xu::toString(m_mulInhClass));
    xu::append(res, xu::toString(m_inheritID));
    xu::append(res, xu::toString(m_classTparam));
    xu::append(res, xu::toString(m_attribute));
    xu::append(res, xu::toString(m_friendClassName));
    xu::append(res, xu::toString(m_hBeginBefore));
    xu::append(res, xu::toString(m_hBeginBehind));
    xu::append(res, xu::toString(m_hEndBefore));
    xu::append(res, xu::toString(m_hEndBehind));
    xu::append(res, xu::toString(m_beforeDcl));
    xu::append(res, xu::toString(m_behindDcl));
    {
        std::string  boolBit("\0\0\0");

        if (m_updateToString)    boolBit[0] |= 0b00'000'001;
        if (m_finalClass)        boolBit[0] |= 0b00'000'010;
        if (m_template)          boolBit[0] |= 0b00'000'100;
        if (m_updateFilename)    boolBit[0] |= 0b00'001'000;
        if (m_setterReturnThis)  boolBit[0] |= 0b00'010'000;
        if (m_impl)              boolBit[0] |= 0b00'100'000;
        if (m_lessFunction)      boolBit[0] |= 0b01'000'000;

        if (m_eqFunction)        boolBit[1] |= 0b00'000'001;
        if (m_swapFunction)      boolBit[1] |= 0b00'000'010;
        if (m_toStringFunction)  boolBit[1] |= 0b00'000'100;
        if (m_internal)          boolBit[1] |= 0b00'001'000;
        if (m_indPublicLabel)    boolBit[1] |= 0b00'010'000;
        if (m_defCtor)           boolBit[1] |= 0b00'100'000;
        if (m_copyCtor)          boolBit[1] |= 0b01'000'000;

        if (m_moveCtor)          boolBit[2] |= 0b00'000'001;
        if (m_dtor)              boolBit[2] |= 0b00'000'010;
        if (m_copyOpEq)          boolBit[2] |= 0b00'000'100;
        if (m_moveOpEq)          boolBit[2] |= 0b00'001'000;

        xu::append(res, xu::toString(boolBit));
    }

    return res;
}

bool
MyClass::deserialize(const char *  data,
                     const size_t  size)
{
    MyClass  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 24) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_eobjList, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_field, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_styleField, vi[3]))  err.push_back({3});
        if (!xu::fromString(me.m_IDField, vi[4]))  err.push_back({4});
        if (!xu::fromString(me.m_serzField, vi[5]))  err.push_back({5});
        if (!xu::fromString(me.m_className, vi[6]))  err.push_back({6});
        if (!xu::fromString(me.m_replaceClassName, vi[7]))  err.push_back({7});
        if (!xu::fromString(me.m_docment, vi[8]))  err.push_back({8});
        if (!xu::fromString(me.m_testCode, vi[9]))  err.push_back({9});
        if (!xu::fromString(me.m_classtype, vi[10]))  err.push_back({10});
        if (!xu::fromString(me.m_alignByte, vi[11]))  err.push_back({11});
        if (!xu::fromString(me.m_baseClassPrarm, vi[12]))  err.push_back({12});
        if (!xu::fromString(me.m_baseClassFirst, vi[13]))  err.push_back({13});
        if (!xu::fromString(me.m_mulInhClass, vi[14]))  err.push_back({14});
        if (!xu::fromString(me.m_inheritID, vi[15]))  err.push_back({15});
        if (!xu::fromString(me.m_classTparam, vi[16]))  err.push_back({16});
        if (!xu::fromString(me.m_attribute, vi[17]))  err.push_back({17});
        if (!xu::fromString(me.m_friendClassName, vi[18]))  err.push_back({18});
        if (!xu::fromString(me.m_hBeginBefore, vi[19]))  err.push_back({19});
        if (!xu::fromString(me.m_hBeginBehind, vi[20]))  err.push_back({20});
        if (!xu::fromString(me.m_hEndBefore, vi[21]))  err.push_back({21});
        if (!xu::fromString(me.m_hEndBehind, vi[22]))  err.push_back({22});
        if (!xu::fromString(me.m_beforeDcl, vi[23]))  err.push_back({23});
        if (!xu::fromString(me.m_behindDcl, vi[24]))  err.push_back({24});
    }
    bool  result = false;

    if (vi.size() == 25) {
        err.push_back({25});
        m_stringErr = std::move(err);
        return result;
    } else {
        std::string  boolBit;
        if (xu::fromString(boolBit, vi[25]) && boolBit.size() == 3) {
            me.m_updateToString =   boolBit[0] & 0b00'000'001;
            me.m_finalClass =       boolBit[0] & 0b00'000'010;
            me.m_template =         boolBit[0] & 0b00'000'100;
            me.m_updateFilename =   boolBit[0] & 0b00'001'000;
            me.m_setterReturnThis = boolBit[0] & 0b00'010'000;
            me.m_impl =             boolBit[0] & 0b00'100'000;
            me.m_lessFunction =     boolBit[0] & 0b01'000'000;

            me.m_eqFunction =       boolBit[1] & 0b00'000'001;
            me.m_swapFunction =     boolBit[1] & 0b00'000'010;
            me.m_toStringFunction = boolBit[1] & 0b00'000'100;
            me.m_internal =         boolBit[1] & 0b00'001'000;
            me.m_indPublicLabel =   boolBit[1] & 0b00'010'000;
            me.m_defCtor =          boolBit[1] & 0b00'100'000;
            me.m_copyCtor =         boolBit[1] & 0b01'000'000;

            me.m_moveCtor =         boolBit[2] & 0b00'000'001;
            me.m_dtor =             boolBit[2] & 0b00'000'010;
            me.m_copyOpEq =         boolBit[2] & 0b00'000'100;
            me.m_moveOpEq =         boolBit[2] & 0b00'001'000;
        } else {
            err.push_back({25});
        }
    }

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
MyClass::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        MyClass &  rhs = dynamic_cast<MyClass &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_stringErr, rhs.m_stringErr);
        swap(m_parentModulePtr, rhs.m_parentModulePtr);
        swap(m_eobjList, rhs.m_eobjList);
        swap(m_field, rhs.m_field);
        swap(m_styleField, rhs.m_styleField);
        swap(m_IDField, rhs.m_IDField);
        swap(m_serzField, rhs.m_serzField);
        swap(m_className, rhs.m_className);
        swap(m_replaceClassName, rhs.m_replaceClassName);
        swap(m_docment, rhs.m_docment);
        swap(m_testCode, rhs.m_testCode);
        swap(m_classtype, rhs.m_classtype);
        swap(m_alignByte, rhs.m_alignByte);
        swap(m_baseClassPrarm, rhs.m_baseClassPrarm);
        swap(m_baseClassFirst, rhs.m_baseClassFirst);
        swap(m_mulInhClass, rhs.m_mulInhClass);
        swap(m_inheritID, rhs.m_inheritID);
        swap(m_classTparam, rhs.m_classTparam);
        swap(m_attribute, rhs.m_attribute);
        swap(m_friendClassName, rhs.m_friendClassName);
        swap(m_hBeginBefore, rhs.m_hBeginBefore);
        swap(m_hBeginBehind, rhs.m_hBeginBehind);
        swap(m_hEndBefore, rhs.m_hEndBefore);
        swap(m_hEndBehind, rhs.m_hEndBehind);
        swap(m_beforeDcl, rhs.m_beforeDcl);
        swap(m_behindDcl, rhs.m_behindDcl);
        swap(m_updateToString, rhs.m_updateToString);
        swap(m_finalClass, rhs.m_finalClass);
        swap(m_template, rhs.m_template);
        swap(m_updateFilename, rhs.m_updateFilename);
        swap(m_setterReturnThis, rhs.m_setterReturnThis);
        swap(m_impl, rhs.m_impl);
        swap(m_lessFunction, rhs.m_lessFunction);
        swap(m_eqFunction, rhs.m_eqFunction);
        swap(m_swapFunction, rhs.m_swapFunction);
        swap(m_toStringFunction, rhs.m_toStringFunction);
        swap(m_internal, rhs.m_internal);
        swap(m_indPublicLabel, rhs.m_indPublicLabel);
        swap(m_defCtor, rhs.m_defCtor);
        swap(m_copyCtor, rhs.m_copyCtor);
        swap(m_moveCtor, rhs.m_moveCtor);
        swap(m_dtor, rhs.m_dtor);
        swap(m_copyOpEq, rhs.m_copyOpEq);
        swap(m_moveOpEq, rhs.m_moveOpEq);

        result = true;
    }
    return result;
}

}
