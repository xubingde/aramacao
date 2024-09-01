#include <algorithm>
#include <map>
#include <cstring>
#include <typeinfo>
#include "publictype.h"
#include "function.h"
#include "icode.h"
#include "fmt.h"
#include "myclass.h"
#include "functions.h"

namespace xu {

Function::Function():
        EObject(),
        m_stringErr(),
        m_parentClassPtr(nullptr),
        m_functionName("new__fn"),
        m_docment(),
        m_testCode(),
        m_mCode(),
        m_insertMCode(),
        m_strike(),
        m_newCode(),
        m_returnType("void"),
        m_hReturnTypeBehind(),
        m_hReturnTypeBehind2(),
        m_returnTypeDoc(),
        m_param(),
        m_tparam(),
        m_inhValueFirst(),
        m_inhValueBaseClass(),
        m_defValueCtor(),
        m_attribute(),
        m_hBefore(),
        m_hBehind(),
        m_cppBefore(),
        m_cppBehind(),
        m_friendClassName(),
        m_classFunction(false),
        m_constructor(false),
        m_autoSource(false),
        m_template(false),
        m_inline(false),
        m_constexpr(false),
        m_static(false),
        m_explicit(false),
        m_virtual(false),
        m_sourceinH(false),
        m_enabled(true),
        m_const(false),
        m_noexcept(false),
        m_override(false),
        m_final(false),
        m_eqDefault(false),
        m_eqDelete(false),
        m_ref(false),
        m_refRef(false),
        m_pureVirtual(false),
        m_internal(false),
        m_decSpaceLine(false)
{
    init();
}

Function::Function(const Function &  other):
        EObject(other),
        m_stringErr(other.m_stringErr),
        m_parentClassPtr(other.m_parentClassPtr),
        m_functionName(other.m_functionName),
        m_docment(other.m_docment),
        m_testCode(other.m_testCode),
        m_mCode(other.m_mCode),
        m_insertMCode(other.m_insertMCode),
        m_strike(other.m_strike),
        m_newCode(other.m_newCode),
        m_returnType(other.m_returnType),
        m_hReturnTypeBehind(other.m_hReturnTypeBehind),
        m_hReturnTypeBehind2(other.m_hReturnTypeBehind2),
        m_returnTypeDoc(other.m_returnTypeDoc),
        m_param(other.m_param),
        m_tparam(other.m_tparam),
        m_inhValueFirst(other.m_inhValueFirst),
        m_inhValueBaseClass(other.m_inhValueBaseClass),
        m_defValueCtor(other.m_defValueCtor),
        m_attribute(other.m_attribute),
        m_hBefore(other.m_hBefore),
        m_hBehind(other.m_hBehind),
        m_cppBefore(other.m_cppBefore),
        m_cppBehind(other.m_cppBehind),
        m_friendClassName(other.m_friendClassName),
        m_classFunction(other.m_classFunction),
        m_constructor(other.m_constructor),
        m_autoSource(other.m_autoSource),
        m_template(other.m_template),
        m_inline(other.m_inline),
        m_constexpr(other.m_constexpr),
        m_static(other.m_static),
        m_explicit(other.m_explicit),
        m_virtual(other.m_virtual),
        m_sourceinH(other.m_sourceinH),
        m_enabled(other.m_enabled),
        m_const(other.m_const),
        m_noexcept(other.m_noexcept),
        m_override(other.m_override),
        m_final(other.m_final),
        m_eqDefault(other.m_eqDefault),
        m_eqDelete(other.m_eqDelete),
        m_ref(other.m_ref),
        m_refRef(other.m_refRef),
        m_pureVirtual(other.m_pureVirtual),
        m_internal(other.m_internal),
        m_decSpaceLine(other.m_decSpaceLine)
{
}

Function::Function(Function &&  other) noexcept:
        EObject(std::move(other)),
        m_stringErr(std::move(other.m_stringErr)),
        m_parentClassPtr(std::move(other.m_parentClassPtr)),
        m_functionName(std::move(other.m_functionName)),
        m_docment(std::move(other.m_docment)),
        m_testCode(std::move(other.m_testCode)),
        m_mCode(std::move(other.m_mCode)),
        m_insertMCode(std::move(other.m_insertMCode)),
        m_strike(std::move(other.m_strike)),
        m_newCode(std::move(other.m_newCode)),
        m_returnType(std::move(other.m_returnType)),
        m_hReturnTypeBehind(std::move(other.m_hReturnTypeBehind)),
        m_hReturnTypeBehind2(std::move(other.m_hReturnTypeBehind2)),
        m_returnTypeDoc(std::move(other.m_returnTypeDoc)),
        m_param(std::move(other.m_param)),
        m_tparam(std::move(other.m_tparam)),
        m_inhValueFirst(std::move(other.m_inhValueFirst)),
        m_inhValueBaseClass(std::move(other.m_inhValueBaseClass)),
        m_defValueCtor(std::move(other.m_defValueCtor)),
        m_attribute(std::move(other.m_attribute)),
        m_hBefore(std::move(other.m_hBefore)),
        m_hBehind(std::move(other.m_hBehind)),
        m_cppBefore(std::move(other.m_cppBefore)),
        m_cppBehind(std::move(other.m_cppBehind)),
        m_friendClassName(std::move(other.m_friendClassName)),
        m_classFunction(std::move(other.m_classFunction)),
        m_constructor(std::move(other.m_constructor)),
        m_autoSource(std::move(other.m_autoSource)),
        m_template(std::move(other.m_template)),
        m_inline(std::move(other.m_inline)),
        m_constexpr(std::move(other.m_constexpr)),
        m_static(std::move(other.m_static)),
        m_explicit(std::move(other.m_explicit)),
        m_virtual(std::move(other.m_virtual)),
        m_sourceinH(std::move(other.m_sourceinH)),
        m_enabled(std::move(other.m_enabled)),
        m_const(std::move(other.m_const)),
        m_noexcept(std::move(other.m_noexcept)),
        m_override(std::move(other.m_override)),
        m_final(std::move(other.m_final)),
        m_eqDefault(std::move(other.m_eqDefault)),
        m_eqDelete(std::move(other.m_eqDelete)),
        m_ref(std::move(other.m_ref)),
        m_refRef(std::move(other.m_refRef)),
        m_pureVirtual(std::move(other.m_pureVirtual)),
        m_internal(std::move(other.m_internal)),
        m_decSpaceLine(std::move(other.m_decSpaceLine))
{
}

Function::Function(MyClass *  parent):
        EObject(),
        m_stringErr(),
        m_parentClassPtr(parent),
        m_functionName(),
        m_docment(),
        m_testCode(),
        m_mCode(),
        m_insertMCode(),
        m_strike(),
        m_newCode(),
        m_returnType(),
        m_hReturnTypeBehind(),
        m_hReturnTypeBehind2(),
        m_returnTypeDoc(),
        m_param(),
        m_tparam(),
        m_inhValueFirst(),
        m_inhValueBaseClass(),
        m_defValueCtor(),
        m_attribute(),
        m_hBefore(),
        m_hBehind(),
        m_cppBefore(),
        m_cppBehind(),
        m_friendClassName(),
        m_classFunction(),
        m_constructor(false),
        m_autoSource(false),
        m_template(false),
        m_inline(false),
        m_constexpr(false),
        m_static(false),
        m_explicit(false),
        m_virtual(false),
        m_sourceinH(false),
        m_enabled(true),
        m_const(false),
        m_noexcept(false),
        m_override(false),
        m_final(false),
        m_eqDefault(false),
        m_eqDelete(false),
        m_ref(false),
        m_refRef(false),
        m_pureVirtual(false),
        m_internal(false),
        m_decSpaceLine()
{
    init();
}

Function::~Function() noexcept
{
}

Function &
Function::operator=(const Function &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_stringErr = other.m_stringErr;
    m_parentClassPtr = other.m_parentClassPtr;
    m_functionName = other.m_functionName;
    m_docment = other.m_docment;
    m_testCode = other.m_testCode;
    m_mCode = other.m_mCode;
    m_insertMCode = other.m_insertMCode;
    m_strike = other.m_strike;
    m_newCode = other.m_newCode;
    m_returnType = other.m_returnType;
    m_hReturnTypeBehind = other.m_hReturnTypeBehind;
    m_hReturnTypeBehind2 = other.m_hReturnTypeBehind2;
    m_returnTypeDoc = other.m_returnTypeDoc;
    m_param = other.m_param;
    m_tparam = other.m_tparam;
    m_inhValueFirst = other.m_inhValueFirst;
    m_inhValueBaseClass = other.m_inhValueBaseClass;
    m_defValueCtor = other.m_defValueCtor;
    m_attribute = other.m_attribute;
    m_hBefore = other.m_hBefore;
    m_hBehind = other.m_hBehind;
    m_cppBefore = other.m_cppBefore;
    m_cppBehind = other.m_cppBehind;
    m_friendClassName = other.m_friendClassName;
    m_classFunction = other.m_classFunction;
    m_constructor = other.m_constructor;
    m_autoSource = other.m_autoSource;
    m_template = other.m_template;
    m_inline = other.m_inline;
    m_constexpr = other.m_constexpr;
    m_static = other.m_static;
    m_explicit = other.m_explicit;
    m_virtual = other.m_virtual;
    m_sourceinH = other.m_sourceinH;
    m_enabled = other.m_enabled;
    m_const = other.m_const;
    m_noexcept = other.m_noexcept;
    m_override = other.m_override;
    m_final = other.m_final;
    m_eqDefault = other.m_eqDefault;
    m_eqDelete = other.m_eqDelete;
    m_ref = other.m_ref;
    m_refRef = other.m_refRef;
    m_pureVirtual = other.m_pureVirtual;
    m_internal = other.m_internal;
    m_decSpaceLine = other.m_decSpaceLine;

    return *this;
}

Function &
Function::operator=(Function &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_stringErr = std::move(other.m_stringErr);
    m_parentClassPtr = std::move(other.m_parentClassPtr);
    m_functionName = std::move(other.m_functionName);
    m_docment = std::move(other.m_docment);
    m_testCode = std::move(other.m_testCode);
    m_mCode = std::move(other.m_mCode);
    m_insertMCode = std::move(other.m_insertMCode);
    m_strike = std::move(other.m_strike);
    m_newCode = std::move(other.m_newCode);
    m_returnType = std::move(other.m_returnType);
    m_hReturnTypeBehind = std::move(other.m_hReturnTypeBehind);
    m_hReturnTypeBehind2 = std::move(other.m_hReturnTypeBehind2);
    m_returnTypeDoc = std::move(other.m_returnTypeDoc);
    m_param = std::move(other.m_param);
    m_tparam = std::move(other.m_tparam);
    m_inhValueFirst = std::move(other.m_inhValueFirst);
    m_inhValueBaseClass = std::move(other.m_inhValueBaseClass);
    m_defValueCtor = std::move(other.m_defValueCtor);
    m_attribute = std::move(other.m_attribute);
    m_hBefore = std::move(other.m_hBefore);
    m_hBehind = std::move(other.m_hBehind);
    m_cppBefore = std::move(other.m_cppBefore);
    m_cppBehind = std::move(other.m_cppBehind);
    m_friendClassName = std::move(other.m_friendClassName);
    m_classFunction = std::move(other.m_classFunction);
    m_constructor = std::move(other.m_constructor);
    m_autoSource = std::move(other.m_autoSource);
    m_template = std::move(other.m_template);
    m_inline = std::move(other.m_inline);
    m_constexpr = std::move(other.m_constexpr);
    m_static = std::move(other.m_static);
    m_explicit = std::move(other.m_explicit);
    m_virtual = std::move(other.m_virtual);
    m_sourceinH = std::move(other.m_sourceinH);
    m_enabled = std::move(other.m_enabled);
    m_const = std::move(other.m_const);
    m_noexcept = std::move(other.m_noexcept);
    m_override = std::move(other.m_override);
    m_final = std::move(other.m_final);
    m_eqDefault = std::move(other.m_eqDefault);
    m_eqDelete = std::move(other.m_eqDelete);
    m_ref = std::move(other.m_ref);
    m_refRef = std::move(other.m_refRef);
    m_pureVirtual = std::move(other.m_pureVirtual);
    m_internal = std::move(other.m_internal);
    m_decSpaceLine = std::move(other.m_decSpaceLine);

    return *this;
}

std::string
Function::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    if (m_internal) {
        res += "\n";
        res += definition(tabStr);
    } else {
        res = declaration(tabStr);
    }

    return res;
}

std::string
Function::toCppBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    if (!m_internal) {
        res += "\n";
        res += definition(tabStr);
    }

    return res;
}

std::string
Function::declaration(std::string const &  tabStr /* = std::string() */) const
{
    return friendDecl(tabStr, false);
}

std::string
Function::friendDeclaration(std::string const &  tabStr /* = std::string() */) const
{
    return friendDecl(tabStr, true);
}

std::string
Function::definition(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;
    const std::string  tab1(getDefTab());
    const std::string  tab2(getDefTab() + getDefTab());

    if (!m_enabled)  return res;
    if (m_pureVirtual)  return res;

    res += m_cppBefore;

    if (m_attribute.size() > 0) {
        res += tabStr;
        if (m_internal)  res += tab1;
        res += m_attribute + "\n";
    }

    bool  isMyClassTpl = false;
    std::vector<Tpl>  myClassTplPrarm;
    if (m_parentClassPtr && m_classFunction) {
        isMyClassTpl = m_parentClassPtr->isTemplate();
        myClassTplPrarm = m_parentClassPtr->getClassTparam();
    }
    if (isMyClassTpl && !m_internal) {
        res += tabStr;
        res += "template <";
        for (size_t  i = 0; i < myClassTplPrarm.size(); ++i) {
            res += myClassTplPrarm[i].getTypename();
            if (myClassTplPrarm[i].getTName().size() > 0) {
                if (myClassTplPrarm[i].getTypename().size() > 0) {
                    res += " ";
                }
                res += myClassTplPrarm[i].getTName();
            }

            if (myClassTplPrarm[i].getDefalutValue().size() > 0) {
                res += " /* = " + myClassTplPrarm[i].getDefalutValue() + " */";
            }
            if (i != myClassTplPrarm.size() - 1) {
                res += ", ";
            }
        }
        res += ">\n";
    }

    if (m_template) {
        res += tabStr;
        if (m_internal)  res += tab1;
        res += "template <";
        for (size_t  i = 0; i < m_tparam.size(); ++i) {
            res += m_tparam[i].getTypename();
            if (m_tparam[i].getTName().size() > 0) {
                if (m_tparam[i].getTypename().size() > 0) {
                    res += " ";
                }
                res += m_tparam[i].getTName();
            }

            if (m_tparam[i].getDefalutValue().size() > 0) {
                res += " /* = " + m_tparam[i].getDefalutValue() + " */";
            }
            if (i != m_tparam.size() - 1) {
                res += ", ";
            }
        }
        res += "> ";
    }

    if (m_inline)               res += "inline ";
    if (m_constexpr)            res += "constexpr ";
    if (res.size() > 0)         res[res.size() - 1] = '\n';

    bool  isAutoType = false;
    if (!m_constructor && m_returnType.size() > 0) {
        res += tabStr;
        if (m_internal)  res += tab1;

        if (m_returnType.size() > 1 && m_returnType[0] == '-' && m_returnType[1] == '>') {
            isAutoType = true;
        }
        if (isAutoType) {
            res += "auto";
        } else {
            res += m_returnType;
        }
        if (m_hReturnTypeBehind2.size() > 0) {
            res += " " + m_hReturnTypeBehind2;
        }
        res += "\n";
    }

    size_t  spaceCnt;
    if (m_classFunction) {
        std::string  myClassName;
        if (m_parentClassPtr)  myClassName = m_parentClassPtr->getClassName();

        res += tabStr;
        if (m_internal) {
            res += tab1;
        } else {
            res += myClassName;
        }

        size_t  dotSize = 0;
        if (isMyClassTpl && !m_internal) {
            for (size_t  i = 0; i < myClassTplPrarm.size(); ++i) {
                res += myClassTplPrarm[i].getTName();

                bool  dot3 = false;
                std::string  tnameTmp = myClassTplPrarm[i].getTypename();
                if (tnameTmp.size() > 3) {
                    const auto  ret = tnameTmp.compare(tnameTmp.size() - 3, 3, "...");
                    if (ret == 0)  dot3 = true;
                }
                if (dot3) {
                    res += "...";
                    dotSize += 3;
                }
                if (i != myClassTplPrarm.size() - 1)  res += ", ";
            }
            res += ">";
        }
        if (!m_internal) {
            res += "::";
        }

        if (isMyClassTpl) {
            std::string  spStr;
            for (size_t  i = 0; i < myClassTplPrarm.size(); ++i) {
                spStr += myClassTplPrarm[i].getTName();
                if (i != myClassTplPrarm.size() - 1) {
                    spStr += ", ";
                }
            }
            if (m_internal) {
                spaceCnt = tabStr.size() + spStr.size() + tab1.size() +
                        m_functionName.size() + 5 + dotSize;
            } else {
                spaceCnt = tabStr.size() + spStr.size() + myClassName.size() +
                        m_functionName.size() + 5 + dotSize;
            }
        } else {
            if (m_internal) {
                spaceCnt = tabStr.size() + tab1.size() + m_functionName.size() + 3;
            } else {
                spaceCnt = tabStr.size() + myClassName.size() + m_functionName.size() + 3;
            }
        }
    } else {
        spaceCnt = tabStr.size() + m_functionName.size() + 1;
        res += tabStr;
    }
    res += m_functionName + "(";

    {
        const std::string  tab_space(spaceCnt, '\x20');
        const size_t  size { m_param.size() };
        for (size_t  i = 0; i < size; ++i) {
            res += m_param[i].getType();
            if (m_param[i].getParameterName().size() > 0) {
                if (m_param[i].getType().size() > 0) {
                    res += "  ";
                }
                res += m_param[i].getParameterName();
            }

            if (m_param[i].getDefalutValue().size() > 0) {
                res += " /* = " + m_param[i].getDefalutValue() + " */";
            }
            if (i != size - 1) {
                res += ",\n" + tab_space + tabStr;
            }
        }
    }
    res += ")";

    if (m_constructor) {
        if (m_noexcept)  res += " noexcept";

        ClassType  ct = ClassType::cppFinal;
        std::vector<Field>  vecField;
        if (m_parentClassPtr) {
            ct = m_parentClassPtr->getClasstype();
            vecField = m_parentClassPtr->getField();
        }
        size_t const  fieldSize = vecField.size();

        if (fieldSize > 0 || ct == ClassType::cppInherit) {
            res += ":\n";
        }
        if (ct == ClassType::cppInherit) {
            res += tabStr + tab2 + m_parentClassPtr->getBaseClassFirst().first
                    + "(" + m_inhValueFirst + ")";
            const std::string  mInh = multipleInh();
            if (mInh.size() > 0) {
                res += ",\n" + mInh;
            }
            if (fieldSize > 0)  res += ",\n";
        }
        if (fieldSize > 0) {
            for (size_t  i = 0; i < fieldSize; ++i) {
                res += tabStr + tab2 + vecField[i].getPrivateName() +
                        "(" + m_defValueCtor[i] + ")";
                if (i != fieldSize - 1) {
                    res += ",\n";
                }
            }
        }
    } else {
        if (m_const)                res += " const";
        if (m_noexcept)             res += " noexcept";
        if (m_final)                res += " final";
        if (m_ref)                  res += " &";
        if (m_refRef)               res += " &&";
    }
    if (isAutoType) {
        res += " " + m_returnType;
    }

    res += "\n" + tabStr;
    if (m_internal)  res += tab1;
    res += "{\n";

    if (m_autoSource) {
        res += updateAutoCode(tabStr);
    } else {
        res += updateMCode(m_mCode, tabStr, true);
    }

    if (res[res.size() - 1] != '\n') {
        res += "\n";
    }

    res += tabStr;
    if (m_internal)  res += tab1;
    res += "}\n";
    res += m_cppBehind;

    return res;
}

std::string
Function::declLabel() const
{
    std::string  res;

    if (m_template) {
        res += "template <";
        for (size_t  i = 0; i < m_tparam.size(); ++i) {
            res += m_tparam[i].getTypename();
            if (m_tparam[i].getTName().size() > 0) {
                if (m_tparam[i].getTypename().size() > 0) {
                    res += " ";
                }
                res += m_tparam[i].getTName();
            }

            if (m_tparam[i].getDefalutValue().size() > 0) {
                res += " = " + m_tparam[i].getDefalutValue();
            }
            if (i != m_tparam.size() - 1) {
                res += ", ";
            }
        }
        res += ">\n";
    }

    if (m_constexpr)            res += "constexpr ";
    if (m_static)               res += "static ";
    if (m_explicit)             res += "explicit ";
    if (m_virtual)              res += "virtual ";

    bool  isAutoType = false;
    if (m_returnType.size() > 0) {
        if (m_returnType.size() > 1 && m_returnType[0] == '-' && m_returnType[1] == '>') {
            isAutoType = true;
        }
        if (isAutoType) {
            res += "auto ";
        } else {
            res += m_returnType + " ";
        }
        if (m_hReturnTypeBehind.size() > 0) {
            res += m_hReturnTypeBehind + " ";
        }
        if (m_hReturnTypeBehind2.size() > 0) {
            res += m_hReturnTypeBehind2 + " ";
        }
        res += " ";
    }
    res += m_functionName + "(";

    const size_t  size { m_param.size() };
    for (size_t  i = 0; i < size; ++i) {
        res += m_param[i].getType();
        if (m_param[i].getParameterName().size() > 0) {
            if (m_param[i].getType().size() > 0) {
                res += "  ";
            }
            res += m_param[i].getParameterName();
        }

        if (m_param[i].getDefalutValue().size() > 0) {
            res += " = " + m_param[i].getDefalutValue();
        }
        if (i != size - 1) {
            res += ", ";
        }
    }

    res += ")";
    if (m_const)                res += " const";
    if (m_noexcept)             res += " noexcept";
    if (m_override)             res += " override";
    if (m_final)                res += " final";
    if (m_ref)                  res += " &";
    if (m_refRef)               res += " &&";
    if (m_eqDefault)            res += " = default";
    if (m_eqDelete)             res += " = delete";
    if (m_pureVirtual)          res += " = 0";

    if (isAutoType) {
        res += " " + m_returnType;
    }
    res += ";";

    return res;
}

std::string
Function::updateAutoCode(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;
    std::string const  aCode = autoCode();

    std::vector<std::tuple<size_t, std::string_view, size_t, bool, bool>>  codeV;
    std::vector<std::string_view>  vecLine = splitLine(aCode);
    size_t const  vecSize = vecLine.size();
    for (size_t  i = 0; i < vecSize; ++i) {
        std::tuple<size_t, std::string_view, size_t, bool, bool>  it;
        std::get<0>(it) = i;
        std::get<1>(it) = vecLine[i];
        std::get<3>(it) = false;
        std::get<4>(it) = true;
        codeV.push_back(std::move(it));
    }

    size_t const  codeSize = codeV.size();
    for (size_t  i = 0; i < m_strike.size(); ++i) {
        if (m_strike[i] < codeSize) {
            std::get<4>(codeV[m_strike[i]]) = false;
        } else {
            break;
        }
    }
    for (size_t  i = 0; i < m_newCode.size(); ++i) {
        if (m_newCode[i].first < codeSize) {
            std::get<2>(codeV[m_newCode[i].first]) = i;
            std::get<3>(codeV[m_newCode[i].first]) = true;
        } else {
            break;
        }
    }

    for (const auto &  it: codeV) {
        if (std::get<3>(it)) {
            res += m_newCode[std::get<2>(it)].second;
            if (res.size() > 0 && res[res.size() - 1] != '\n') {
                res += '\n';
            }
        }
        if (std::get<4>(it)) {
            res += std::get<1>(it);
            res += '\n';
        }
    }
    for (const auto &  it: m_newCode) {
        if (it.first >= codeSize) {
            res += it.second;
            if (res.size() > 0 && res[res.size() - 1] != '\n') {
                res += '\n';
            }
        }
    }
    std::string  result = updateMCode(res, tabStr, false);

    return result;
}

std::string
Function::updateMCode(std::string const &  code,
                      std::string const &  tabStr /* = std::string() */,
                      bool const  hasInsertObj /* = false */) const
{
    std::string  res;

    if (tabStr.size() == 0) {
        res = code;
    } else {
        std::vector<std::string_view>  vecLine = xu::splitLine(code);

        size_t const  size = vecLine.size();
        for (size_t  i = 0; i < size; ++i) {
            if (hasInsertObj) {
                auto  insertIt = std::find_if(m_insertMCode.begin(), m_insertMCode.end(),
                        [i](std::tuple<size_t, Etype, std::shared_ptr<EObject>> const &  val)
                        ->bool {
                            if (std::get<0>(val) == i) {
                                return true;
                            } else {
                                return false;
                            }
                        });
                if (insertIt != m_insertMCode.end()) {
                    res += "\n";
                    res += tabStr + std::get<2>(*insertIt)->toHBlock(xu::getDefTab());
                }
            }

            if (vecLine[i].size() > 0) {
                res += tabStr + std::string(vecLine[i]) + "\n";
            } else {
                res += "\n";
            }
        }
    }

    return res;
}

std::string
Function::autoCode() const
{
    std::string  res;
    return res;
}

void
Function::init()
{
    setTreeLabel("F   " + m_functionName);
    setBaseType(Etype::eFunction);
}

std::string
Function::friendDecl(std::string const &  tabStr,
                     bool const  isFriendFn) const
{
    std::string  res;
    const std::string  tab1(getDefTab());

    if (!m_enabled)  return res;

    if (isFriendFn) {
        res += tabStr + "friend ";
    } else {
        if (m_decSpaceLine) {
            res += "\n";
        }
        res += m_hBefore + tabStr;
    }

    if (!isFriendFn && m_attribute.size() > 0) {
        if (m_classFunction)  res += tab1;
        res += m_attribute + "\n";
    }

    if (m_classFunction)  res += tab1;

    if (m_template) {
        res += "template <";
        for (size_t  i = 0; i < m_tparam.size(); ++i) {
            res += m_tparam[i].getTypename();

            if (isFriendFn && m_tparam[i].getFriendTypeName().size() > 0) {
                if (m_tparam[i].getTypename().size() > 0) {
                    res += " ";
                }
                res += m_tparam[i].getFriendTypeName();
            } else if (m_tparam[i].getTName().size() > 0) {
                if (m_tparam[i].getTypename().size() > 0) {
                    res += " ";
                }
                res += m_tparam[i].getTName();
            }

            if (m_tparam[i].getDefalutValue().size() > 0) {
                if (isFriendFn) {
                    res += " /* = " + m_tparam[i].getDefalutValue() + " */";
                } else {
                    res += " = " + m_tparam[i].getDefalutValue();
                }
            }
            if (i != m_tparam.size() - 1) {
                res += ", ";
            }
        }
        res += ">\n";
        if (m_classFunction) {
            res += tab1;
        }
    }

    if (m_constexpr)            res += "constexpr ";
    if (m_static)               res += "static ";
    if (m_explicit)             res += "explicit ";
    if (m_virtual)              res += "virtual ";

    bool  isAutoType = false;
    if (m_returnType.size() > 0) {
        if (m_returnType.size() > 1 && m_returnType[0] == '-' && m_returnType[1] == '>') {
            isAutoType = true;
        }
        if (isAutoType) {
            res += "auto ";
        } else {
            res += m_returnType + " ";
        }
        if (m_hReturnTypeBehind.size() > 0) {
            res += m_hReturnTypeBehind + " ";
        }
        if (m_hReturnTypeBehind2.size() > 0) {
            res += m_hReturnTypeBehind2 + " ";
        }
        res += " ";
    }
    res += m_functionName + "(";

    const size_t  size { m_param.size() };
    for (size_t  i = 0; i < size; ++i) {
        res += m_param[i].getType();
        if (m_param[i].getParameterName().size() > 0) {
            if (m_param[i].getType().size() > 0) {
                res += "  ";
            }
            res += m_param[i].getParameterName();
        }

        if (m_param[i].getDefalutValue().size() > 0) {
            res += " = " + m_param[i].getDefalutValue();
        }
        if (i != size - 1) {
            res += ", ";
        }
    }

    res += ")";
    if (m_const)                res += " const";
    if (m_noexcept)             res += " noexcept";
    if (m_override)             res += " override";
    if (m_final)                res += " final";
    if (m_ref)                  res += " &";
    if (m_refRef)               res += " &&";
    if (m_eqDefault)            res += " = default";
    if (m_eqDelete)             res += " = delete";
    if (m_pureVirtual)          res += " = 0";

    if (isAutoType) {
        res += " " + m_returnType;
    }

    res += ";\n";
    if (!isFriendFn) {
        res += m_hBehind;
    }

    return res;
}

std::string
Function::multipleInh() const
{
    std::string  res;
    const std::string tab2(getDefTab() + getDefTab());

    if (!m_parentClassPtr || !m_classFunction)  return res;

    ClassType const  ct = m_parentClassPtr->getClasstype();
    if (ct != ClassType::cppInherit)  return res;

    std::vector<std::tuple<std::string, Purview, bool>> const
            mulClass = m_parentClassPtr->getMulInhClass();
    size_t const  size = mulClass.size();
    for (size_t  i = 0; i < size; ++i) {
        res += tab2 + std::get<0>(mulClass[i]) + "(" + m_inhValueBaseClass[i] + ")";
        if (i < size - 1) {
            res += ",\n";
        }
    }

    return res;
}

std::vector<size_t>
Function::getStringErr() const
{
    return m_stringErr;
}

MyClass *
Function::getParentClassPtr() const
{
    return m_parentClassPtr;
}

void
Function::setParentClassPtr(MyClass *  value)
{
    m_parentClassPtr = value;
    if (m_parentClassPtr)  setFunctionName(m_functionName);
}

std::string
Function::getFunctionName() const
{
    return m_functionName;
}

void
Function::setFunctionName(const std::string &  value)
{
    if (m_constructor) {
        setConstructor(m_constructor);
    } else {
        m_functionName = xu::trim(value);
        setTreeLabel("F   " + m_functionName);
    }
}

std::string
Function::getDocment() const
{
    return m_docment;
}

void
Function::setDocment(const std::string &  value)
{
    m_docment = value;
}

void
Function::setDocment(std::string &&  value)
{
    m_docment = std::move(value);
}

std::string
Function::getTestCode() const
{
    return m_testCode;
}

void
Function::setTestCode(const std::string &  value)
{
    m_testCode = value;
    xu::procCode(m_testCode);
}

void
Function::setTestCode(std::string &&  value)
{
    m_testCode = std::move(value);
    xu::procCode(m_testCode);
}

std::string
Function::getMCode() const
{
    return m_mCode;
}

void
Function::setMCode(const std::string &  value)
{
    m_mCode = value;
    xu::procCode(m_mCode);
}

void
Function::setMCode(std::string &&  value)
{
    m_mCode = std::move(value);
    xu::procCode(m_mCode);
}

std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>>
Function::getInsertMCode() const
{
    return m_insertMCode;
}

void
Function::setInsertMCode(const std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>> &  value)
{
    m_insertMCode.clear();
    for (auto const &  [line, ety, objPtr] : value) {
        if (ety != objPtr->getBaseType())  continue;

        std::tuple<size_t, Etype, std::shared_ptr<EObject>>  obj(line, ety, objPtr);
        switch (ety) {
        case Etype::eClass :
            {
                std::shared_ptr<MyClass>  myClassPtr =
                        std::dynamic_pointer_cast<MyClass>(std::get<2>(obj));
                std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &
                        olist = myClassPtr->getEObjectRef();
                for (auto &  fns: olist) {
                    switch (fns.first) {
                    case Etype::eFunctions :
                    case Etype::eStaticFunctions :
                    case Etype::eConstexprFunctions :
                    case Etype::eTplFunctions :
                    case Etype::eTplStaticFunctions :
                    case Etype::eTplConstexprFunctions :
                    case Etype::eConstructors :
                    case Etype::eTplConstructors :
                        {
                            std::shared_ptr<Functions>  fnObjs =
                                    std::dynamic_pointer_cast<Functions>(fns.second);
                            std::vector<std::shared_ptr<Function>> &  fnRef =
                                    fnObjs->getFunctionRef();
                            for (auto &  item: fnRef) {
                                item->setInternal(true);
                            }
                        }
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
                        std::dynamic_pointer_cast<Function>(fns.second)
                                ->setInternal(true);
                        break;
                    default :
                        break;
                    }
                }
            }
            break;

        case Etype::eClassDeclaration :
        case Etype::eEnum :
        case Etype::eStruct :
        case Etype::eStructDeclaration :
        case Etype::eTypedef :
            break;
        default :
            continue;
            break;
        }
        m_insertMCode.push_back(obj);
    }

    std::sort(m_insertMCode.begin(), m_insertMCode.end(),
            [](std::tuple<size_t, Etype, std::shared_ptr<EObject>> &  val1,
            std::tuple<size_t, Etype, std::shared_ptr<EObject>> &  val2)
            ->bool {
                return std::get<0>(val1) < std::get<0>(val2);
            });
    auto  delIt = std::unique(m_insertMCode.begin(), m_insertMCode.end(),
            [](std::tuple<size_t, Etype, std::shared_ptr<EObject>> &  val1,
            std::tuple<size_t, Etype, std::shared_ptr<EObject>> &  val2)
            ->bool {
                if (std::get<0>(val1) == std::get<0>(val2)) {
                    return true;
                } else {
                    return false;
                }
            });
    m_insertMCode.erase(delIt, m_insertMCode.end());
}

std::vector<size_t>
Function::getStrike() const
{
    return m_strike;
}

void
Function::setStrike(const std::vector<size_t> &  value)
{
    m_strike.clear();

    std::set<size_t>  st;
    for (size_t  i: value) {
        st.insert(i);
    }
    for (auto &  it: st) {
        m_strike.push_back(it);
    }
}

std::vector<std::pair<size_t, std::string>>
Function::getNewCode() const
{
    return m_newCode;
}

void
Function::setNewCode(const std::vector<std::pair<size_t, std::string>> &  value)
{
    m_newCode.clear();

    std::map<size_t, std::string>  mc;
    for (auto &  it: value) {
        mc.insert(it);
    }
    for (auto &  it: mc) {
        xu::procCode(it.second);
        m_newCode.push_back(it);
    }
}

std::string
Function::getReturnType() const
{
    return m_returnType;
}

void
Function::setReturnType(const std::string &  value)
{
    if (m_constructor) {
        m_returnType = "";
    } else {
        m_returnType = value;
    }
}

void
Function::setReturnType(std::string &&  value)
{
    if (m_constructor) {
        m_returnType = "";
    } else {
        m_returnType = std::move(value);
    }
}

std::string
Function::getHReturnTypeBehind() const
{
    return m_hReturnTypeBehind;
}

void
Function::setHReturnTypeBehind(const std::string &  value)
{
    m_hReturnTypeBehind = xu::trim(value);
}

std::string
Function::getHReturnTypeBehind2() const
{
    return m_hReturnTypeBehind2;
}

void
Function::setHReturnTypeBehind2(const std::string &  value)
{
    m_hReturnTypeBehind2 = xu::trim(value);
}

std::string
Function::getReturnTypeDoc() const
{
    return m_returnTypeDoc;
}

void
Function::setReturnTypeDoc(const std::string &  value)
{
    m_returnTypeDoc = value;
}

void
Function::setReturnTypeDoc(std::string &&  value)
{
    m_returnTypeDoc = std::move(value);
}

std::vector<Parameter>
Function::getParam() const
{
    return m_param;
}

void
Function::setParam(const std::vector<Parameter> &  value)
{
    m_param = value;
}

void
Function::setParam(std::vector<Parameter> &&  value)
{
    m_param = std::move(value);
}

std::vector<Tpl>
Function::getTparam() const
{
    return m_tparam;
}

void
Function::setTparam(const std::vector<Tpl> &  value)
{
    m_tparam = value;
}

void
Function::setTparam(std::vector<Tpl> &&  value)
{
    m_tparam = std::move(value);
}

std::string
Function::getInhValueFirst() const
{
    return m_inhValueFirst;
}

void
Function::setInhValueFirst(const std::string &  value)
{
    m_inhValueFirst = value;
}

void
Function::setInhValueFirst(std::string &&  value)
{
    m_inhValueFirst = std::move(value);
}

std::vector<std::string>
Function::getInhValueBaseClass() const
{
    return m_inhValueBaseClass;
}

void
Function::setInhValueBaseClass(const std::vector<std::string> &  value)
{
    m_inhValueBaseClass.clear();
    for (auto const &  it: value) {
        std::string  bv = xu::trim(it);
        m_inhValueBaseClass.push_back(std::move(bv));
    }
}

std::vector<std::string>
Function::getDefValueCtor() const
{
    return m_defValueCtor;
}

void
Function::setDefValueCtor(const std::vector<std::string> &  value)
{
    m_defValueCtor.clear();
    for (auto const &  it: value) {
        std::string  defv = xu::trim(it);
        m_defValueCtor.push_back(std::move(defv));
    }
}

std::string
Function::getAttribute() const
{
    return m_attribute;
}

void
Function::setAttribute(const std::string &  value)
{
    m_attribute = value;
}

void
Function::setAttribute(std::string &&  value)
{
    m_attribute = std::move(value);
}

std::string
Function::getHBefore() const
{
    return m_hBefore;
}

void
Function::setHBefore(const std::string &  value)
{
    m_hBefore = value;
    xu::procCode(m_hBefore);
}

void
Function::setHBefore(std::string &&  value)
{
    m_hBefore = std::move(value);
    xu::procCode(m_hBefore);
}

std::string
Function::getHBehind() const
{
    return m_hBehind;
}

void
Function::setHBehind(const std::string &  value)
{
    m_hBehind = value;
    xu::procCode(m_hBehind);
}

void
Function::setHBehind(std::string &&  value)
{
    m_hBehind = std::move(value);
    xu::procCode(m_hBehind);
}

std::string
Function::getCppBefore() const
{
    return m_cppBefore;
}

void
Function::setCppBefore(const std::string &  value)
{
    m_cppBefore = value;
    xu::procCode(m_cppBefore);
}

void
Function::setCppBefore(std::string &&  value)
{
    m_cppBefore = std::move(value);
    xu::procCode(m_cppBefore);
}

std::string
Function::getCppBehind() const
{
    return m_cppBehind;
}

void
Function::setCppBehind(const std::string &  value)
{
    m_cppBehind = value;
    xu::procCode(m_cppBehind);
}

void
Function::setCppBehind(std::string &&  value)
{
    m_cppBehind = std::move(value);
    xu::procCode(m_cppBehind);
}

std::vector<std::string>
Function::getFriendClassName() const
{
    return m_friendClassName;
}

void
Function::setFriendClassName(const std::vector<std::string> &  value)
{
    m_friendClassName = value;
    for (auto &  it: m_friendClassName) {
        it = xu::trim(it);
    }
}

bool
Function::isClassFunction() const
{
    return m_classFunction;
}

void
Function::setClassFunction(const bool  value)
{
    m_classFunction = value;
    if (!m_classFunction) {
        setConstructor(false);
        setVirtual(false);
        setConst(false);
        setOverride(false);
        setFinal(false);
        setEqDefault(false);
        setEqDelete(false);
        setRef(false);
        setRefRef(false);
        setPureVirtual(false);
    }
}

bool
Function::isConstructor() const
{
    return m_constructor;
}

void
Function::setConstructor(const bool  value)
{
    m_constructor = value;
    if (!m_classFunction)  m_constructor = false;
    if (m_constructor) {
        m_functionName = "";
        m_returnType = "";
        if (m_parentClassPtr) {
            m_functionName = m_parentClassPtr->getClassName();
        }
        setTreeLabel("F   Constructor");
    } else {
        setTreeLabel("F   " + m_functionName);
    }
}

bool
Function::isAutoSource() const
{
    return m_autoSource;
}

void
Function::setAutoSource(const bool  value)
{
    m_autoSource = value;
}

bool
Function::isTemplate() const
{
    return m_template;
}

void
Function::setTemplate(const bool  value)
{
    m_template = value;
}

bool
Function::isInline() const
{
    return m_inline;
}

void
Function::setInline(const bool  value)
{
    m_inline = value;
}

bool
Function::isConstexpr() const
{
    return m_constexpr;
}

void
Function::setConstexpr(const bool  value)
{
    m_constexpr = value;
}

bool
Function::isStatic() const
{
    return m_static;
}

void
Function::setStatic(const bool  value)
{
    m_static = value;
    if (m_static) {
        m_const = false;
    }
}

bool
Function::isExplicit() const
{
    return m_explicit;
}

void
Function::setExplicit(const bool  value)
{
    m_explicit = value;
    if (m_explicit) {
        auto const  stu = m_functionName.find("operator");
        if (!(m_constructor || !(stu == std::string::npos))) {
            m_explicit = false;
        }
    }
}

bool
Function::isVirtual() const
{
    return m_virtual;
}

void
Function::setVirtual(const bool  value)
{
    m_virtual = value;
    if (!m_classFunction)  m_virtual = false;
}

bool
Function::isSourceinH() const
{
    return m_sourceinH;
}

void
Function::setSourceinH(const bool  value)
{
    m_sourceinH = value;
    if (m_sourceinH) {
        m_inline = true;
    }
}

bool
Function::isEnabled() const
{
    return m_enabled;
}

void
Function::setEnabled(const bool  value)
{
    m_enabled = value;
}

bool
Function::isConst() const
{
    return m_const;
}

void
Function::setConst(const bool  value)
{
    m_const = value;
    if (!m_classFunction)  m_const = false;
    if (m_const) {
        m_static = false;
    }
}

bool
Function::isNoexcept() const
{
    return m_noexcept;
}

void
Function::setNoexcept(const bool  value)
{
    m_noexcept = value;
}

bool
Function::isOverride() const
{
    return m_override;
}

void
Function::setOverride(const bool  value)
{
    m_override = value;
    if (!m_classFunction)  m_override = false;
}

bool
Function::isFinal() const
{
    return m_final;
}

void
Function::setFinal(const bool  value)
{
    m_final = value;
    if (!m_classFunction)  m_final = false;
}

bool
Function::isEqDefault() const
{
    return m_eqDefault;
}

void
Function::setEqDefault(const bool  value)
{
    m_eqDefault = value;
    if (!m_classFunction)  m_eqDefault = false;
}

bool
Function::isEqDelete() const
{
    return m_eqDelete;
}

void
Function::setEqDelete(const bool  value)
{
    m_eqDelete = value;
    if (!m_classFunction)  m_eqDelete = false;
}

bool
Function::isRef() const
{
    return m_ref;
}

void
Function::setRef(const bool  value)
{
    m_ref = value;
    if (!m_classFunction)  m_ref = false;
    if (m_ref) {
        m_refRef = false;
    }
}

bool
Function::isRefRef() const
{
    return m_refRef;
}

void
Function::setRefRef(const bool  value)
{
    m_refRef = value;
    if (!m_classFunction)  m_refRef = false;
    if (m_refRef) {
        m_ref = false;
    }
}

bool
Function::isPureVirtual() const
{
    return m_pureVirtual;
}

void
Function::setPureVirtual(const bool  value)
{
    m_pureVirtual = value;
    if (!m_classFunction)  m_pureVirtual = false;
    if (m_pureVirtual) {
        m_virtual = true;
        m_override = false;
    }
}

bool
Function::isInternal() const
{
    return m_internal;
}

void
Function::setInternal(const bool  value)
{
    m_internal = value;
}

bool
Function::isDecSpaceLine() const
{
    return m_decSpaceLine;
}

void
Function::setDecSpaceLine(const bool  value)
{
    m_decSpaceLine = value;
}

bool
Function::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const Function &  rhs = dynamic_cast<const Function &>(value);

        result = this->EObject::equal(value);
        if (!result) return result;

        result = ( m_functionName == rhs.m_functionName );
        if (!result) return result;

        result = ( m_const == rhs.m_const );
        if (!result) return result;

        result = ( m_noexcept == rhs.m_noexcept );
        if (!result) return result;

        result = ( m_testCode == rhs.m_testCode );
        if (!result) return result;

        result = ( m_mCode == rhs.m_mCode );
        if (!result) return result;

        result = ( m_strike == rhs.m_strike );
        if (!result) return result;

        result = ( m_param == rhs.m_param );
        if (!result) return result;

        result = ( m_tparam == rhs.m_tparam );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
Function::less(const EObject &  value) const
{
    if (this->EObject::less(value)) return true;
    if (!(this->EObject::equal(value))) return false;

    try {
        const Function &  rhs = dynamic_cast<const Function &>(value);

        if (m_functionName < rhs.m_functionName) return true;
        if (rhs.m_functionName < m_functionName) return false;

        if (m_const < rhs.m_const) return true;
        if (rhs.m_const < m_const) return false;

        if (m_noexcept < rhs.m_noexcept) return true;
        if (rhs.m_noexcept < m_noexcept) return false;

        if (m_testCode < rhs.m_testCode) return true;
        if (rhs.m_testCode < m_testCode) return false;

        if (m_mCode < rhs.m_mCode) return true;
        if (rhs.m_mCode < m_mCode) return false;

        if (m_strike < rhs.m_strike) return true;
        if (rhs.m_strike < m_strike) return false;

        if (m_param < rhs.m_param) return true;
        if (rhs.m_param < m_param) return false;

        if (m_tparam < rhs.m_tparam) return true;
        if (rhs.m_tparam < m_tparam) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
Function::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_functionName));
    xu::append(res, xu::toString(m_docment));
    xu::append(res, xu::toString(m_testCode));
    xu::append(res, xu::toString(m_mCode));
    xu::append(res, xu::toString(m_insertMCode));
    xu::append(res, xu::toString(m_strike));
    xu::append(res, xu::toString(m_newCode));
    xu::append(res, xu::toString(m_returnType));
    xu::append(res, xu::toString(m_hReturnTypeBehind));
    xu::append(res, xu::toString(m_hReturnTypeBehind2));
    xu::append(res, xu::toString(m_returnTypeDoc));
    xu::append(res, xu::toString(m_param));
    xu::append(res, xu::toString(m_tparam));
    xu::append(res, xu::toString(m_inhValueFirst));
    xu::append(res, xu::toString(m_inhValueBaseClass));
    xu::append(res, xu::toString(m_defValueCtor));
    xu::append(res, xu::toString(m_attribute));
    xu::append(res, xu::toString(m_hBefore));
    xu::append(res, xu::toString(m_hBehind));
    xu::append(res, xu::toString(m_cppBefore));
    xu::append(res, xu::toString(m_cppBehind));
    xu::append(res, xu::toString(m_friendClassName));
    {
        std::string  boolBit("\0\0\0\0");

        if (m_classFunction)  boolBit[0] |= 0b00'000'001;
        if (m_constructor)    boolBit[0] |= 0b00'000'010;
        if (m_autoSource)     boolBit[0] |= 0b00'000'100;
        if (m_template)       boolBit[0] |= 0b00'001'000;
        if (m_inline)         boolBit[0] |= 0b00'010'000;
        if (m_constexpr)      boolBit[0] |= 0b00'100'000;
        if (m_static)         boolBit[0] |= 0b01'000'000;

        if (m_explicit)       boolBit[1] |= 0b00'000'001;
        if (m_virtual)        boolBit[1] |= 0b00'000'010;
        if (m_sourceinH)      boolBit[1] |= 0b00'000'100;
        if (m_enabled)        boolBit[1] |= 0b00'001'000;
        if (m_const)          boolBit[1] |= 0b00'010'000;
        if (m_noexcept)       boolBit[1] |= 0b00'100'000;
        if (m_override)       boolBit[1] |= 0b01'000'000;

        if (m_final)          boolBit[2] |= 0b00'000'001;
        if (m_eqDefault)      boolBit[2] |= 0b00'000'010;
        if (m_eqDelete)       boolBit[2] |= 0b00'000'100;
        if (m_ref)            boolBit[2] |= 0b00'001'000;
        if (m_refRef)         boolBit[2] |= 0b00'010'000;
        if (m_pureVirtual)    boolBit[2] |= 0b00'100'000;
        if (m_internal)       boolBit[2] |= 0b01'000'000;

        if (m_decSpaceLine)   boolBit[3] |= 0b00'000'001;

        xu::append(res, xu::toString(boolBit));
    }

    return res;
}

bool
Function::deserialize(const char *  data,
                      const size_t  size)
{
    Function  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 22) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_functionName, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_docment, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_testCode, vi[3]))  err.push_back({3});
        if (!xu::fromString(me.m_mCode, vi[4]))  err.push_back({4});
        if (!xu::fromString(me.m_insertMCode, vi[5]))  err.push_back({5});
        if (!xu::fromString(me.m_strike, vi[6]))  err.push_back({6});
        if (!xu::fromString(me.m_newCode, vi[7]))  err.push_back({7});
        if (!xu::fromString(me.m_returnType, vi[8]))  err.push_back({8});
        if (!xu::fromString(me.m_hReturnTypeBehind, vi[9]))  err.push_back({9});
        if (!xu::fromString(me.m_hReturnTypeBehind2, vi[10]))  err.push_back({10});
        if (!xu::fromString(me.m_returnTypeDoc, vi[11]))  err.push_back({11});
        if (!xu::fromString(me.m_param, vi[12]))  err.push_back({12});
        if (!xu::fromString(me.m_tparam, vi[13]))  err.push_back({13});
        if (!xu::fromString(me.m_inhValueFirst, vi[14]))  err.push_back({14});
        if (!xu::fromString(me.m_inhValueBaseClass, vi[15]))  err.push_back({15});
        if (!xu::fromString(me.m_defValueCtor, vi[16]))  err.push_back({16});
        if (!xu::fromString(me.m_attribute, vi[17]))  err.push_back({17});
        if (!xu::fromString(me.m_hBefore, vi[18]))  err.push_back({18});
        if (!xu::fromString(me.m_hBehind, vi[19]))  err.push_back({19});
        if (!xu::fromString(me.m_cppBefore, vi[20]))  err.push_back({20});
        if (!xu::fromString(me.m_cppBehind, vi[21]))  err.push_back({21});
        if (!xu::fromString(me.m_friendClassName, vi[22]))  err.push_back({22});
    }
    bool  result = false;

    if (vi.size() == 23) {
        err.push_back({23});
        m_stringErr = std::move(err);
        return result;
    } else {
        std::string  boolBit;
        if (xu::fromString(boolBit, vi[23]) && boolBit.size() == 4) {
            me.m_classFunction = boolBit[0] & 0b00'000'001;
            me.m_constructor =   boolBit[0] & 0b00'000'010;
            me.m_autoSource =    boolBit[0] & 0b00'000'100;
            me.m_template =      boolBit[0] & 0b00'001'000;
            me.m_inline =        boolBit[0] & 0b00'010'000;
            me.m_constexpr =     boolBit[0] & 0b00'100'000;
            me.m_static =        boolBit[0] & 0b01'000'000;

            me.m_explicit =      boolBit[1] & 0b00'000'001;
            me.m_virtual =       boolBit[1] & 0b00'000'010;
            me.m_sourceinH =     boolBit[1] & 0b00'000'100;
            me.m_enabled =       boolBit[1] & 0b00'001'000;
            me.m_const =         boolBit[1] & 0b00'010'000;
            me.m_noexcept =      boolBit[1] & 0b00'100'000;
            me.m_override =      boolBit[1] & 0b01'000'000;

            me.m_final =         boolBit[2] & 0b00'000'001;
            me.m_eqDefault =     boolBit[2] & 0b00'000'010;
            me.m_eqDelete =      boolBit[2] & 0b00'000'100;
            me.m_ref =           boolBit[2] & 0b00'001'000;
            me.m_refRef =        boolBit[2] & 0b00'010'000;
            me.m_pureVirtual =   boolBit[2] & 0b00'100'000;
            me.m_internal =      boolBit[2] & 0b01'000'000;

            me.m_decSpaceLine =  boolBit[3] & 0b00'000'001;
        } else {
            err.push_back({23});
        }
    }

    if (err.size() == 0) {
        Function  cs;
        cs.setStrike(me.getStrike());
        cs.setNewCode(me.getNewCode());
        if (    cs.getStrike() != me.getStrike() ||
                cs.getNewCode() != me.getNewCode() ) {
            m_stringErr = std::move(err);
            return result;
        }

        *this = std::move(me);
        result = true;
    }
    m_stringErr = std::move(err);

    return result;
}

bool
Function::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        Function &  rhs = dynamic_cast<Function &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_stringErr, rhs.m_stringErr);
        swap(m_parentClassPtr, rhs.m_parentClassPtr);
        swap(m_functionName, rhs.m_functionName);
        swap(m_docment, rhs.m_docment);
        swap(m_testCode, rhs.m_testCode);
        swap(m_mCode, rhs.m_mCode);
        swap(m_insertMCode, rhs.m_insertMCode);
        swap(m_strike, rhs.m_strike);
        swap(m_newCode, rhs.m_newCode);
        swap(m_returnType, rhs.m_returnType);
        swap(m_hReturnTypeBehind, rhs.m_hReturnTypeBehind);
        swap(m_hReturnTypeBehind2, rhs.m_hReturnTypeBehind2);
        swap(m_returnTypeDoc, rhs.m_returnTypeDoc);
        swap(m_param, rhs.m_param);
        swap(m_tparam, rhs.m_tparam);
        swap(m_inhValueFirst, rhs.m_inhValueFirst);
        swap(m_inhValueBaseClass, rhs.m_inhValueBaseClass);
        swap(m_defValueCtor, rhs.m_defValueCtor);
        swap(m_attribute, rhs.m_attribute);
        swap(m_hBefore, rhs.m_hBefore);
        swap(m_hBehind, rhs.m_hBehind);
        swap(m_cppBefore, rhs.m_cppBefore);
        swap(m_cppBehind, rhs.m_cppBehind);
        swap(m_friendClassName, rhs.m_friendClassName);
        swap(m_classFunction, rhs.m_classFunction);
        swap(m_constructor, rhs.m_constructor);
        swap(m_autoSource, rhs.m_autoSource);
        swap(m_template, rhs.m_template);
        swap(m_inline, rhs.m_inline);
        swap(m_constexpr, rhs.m_constexpr);
        swap(m_static, rhs.m_static);
        swap(m_explicit, rhs.m_explicit);
        swap(m_virtual, rhs.m_virtual);
        swap(m_sourceinH, rhs.m_sourceinH);
        swap(m_enabled, rhs.m_enabled);
        swap(m_const, rhs.m_const);
        swap(m_noexcept, rhs.m_noexcept);
        swap(m_override, rhs.m_override);
        swap(m_final, rhs.m_final);
        swap(m_eqDefault, rhs.m_eqDefault);
        swap(m_eqDelete, rhs.m_eqDelete);
        swap(m_ref, rhs.m_ref);
        swap(m_refRef, rhs.m_refRef);
        swap(m_pureVirtual, rhs.m_pureVirtual);
        swap(m_internal, rhs.m_internal);
        swap(m_decSpaceLine, rhs.m_decSpaceLine);

        result = true;
    }
    return result;
}

}
