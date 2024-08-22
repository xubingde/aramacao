#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "field.h"
#include "copyoperatoreqfn.h"
#include "eobject.h"
#include "myclass.h"
#include "parameter.h"

namespace xu {

CopyOperatorEqFn::CopyOperatorEqFn():
        Function()
{
    init();
}

CopyOperatorEqFn::CopyOperatorEqFn(const CopyOperatorEqFn &  other):
        Function(other)
{
}

CopyOperatorEqFn::CopyOperatorEqFn(CopyOperatorEqFn &&  other) noexcept:
        Function(std::move(other))
{
}

CopyOperatorEqFn::CopyOperatorEqFn(MyClass *  parent):
        Function(parent)
{
    init();
}

CopyOperatorEqFn::~CopyOperatorEqFn() noexcept
{
}

CopyOperatorEqFn &
CopyOperatorEqFn::operator=(const CopyOperatorEqFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

CopyOperatorEqFn &
CopyOperatorEqFn::operator=(CopyOperatorEqFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

std::string
CopyOperatorEqFn::autoCode() const
{
    std::string  autoCode;
    std::string const  tab1(getDefTab());
    std::string const  tab2(getDefTab() + getDefTab());
    std::string const  other(getOther());

    MyClass const *  parentPtr = getParentClassPtr();
    if (parentPtr == nullptr)  return autoCode;
    std::vector<Field> const  vecField = parentPtr->getField();

    autoCode += tab1 + "if (this == &" + other + ") return *this;\n";
    if (parentPtr->getClasstype() == ClassType::cppInherit) {
        autoCode += "\n";
        autoCode += tab1 + "this->" + parentPtr->getBaseClassFirst().first +
                "::operator=(" + other + ");\n";

        std::vector<std::tuple<std::string, Purview, bool>> const &  mulClass =
                parentPtr->getMulInhClass();
        for (const auto &  it: mulClass) {
            autoCode += tab1 + "this->" + std::get<0>(it) + "::operator=(" +
                    other + ");\n";
        }
        autoCode += "\n";
    } else {
        if (vecField.size() > 0) {
            autoCode += "\n";
        }
    }

    bool  spacePtr = false;
    const size_t  size = vecField.size();
    size_t  cnt = 0;
    for (const auto &  it: vecField) {
        if (it.isPointer()) {
            if (spacePtr) {
                autoCode += "\n";
            }
            autoCode += tab1 + "delete " + it.getPrivateName() + ";\n";
            autoCode += tab1 + "if (" + other + "." + it.getPrivateName() +
                    " == nullptr) {\n";
            autoCode += tab2 + it.getPrivateName() + " = nullptr;\n";
            autoCode += tab1 + "} else {\n";
            autoCode += tab2 + it.getPrivateName() + " = new " +
                    it.getTypeName() + " { *" + other + "." +
                    it.getPrivateName() + " };\n";
            autoCode += tab1 + "}\n";
            if (cnt != size - 1) {
                autoCode += "\n";
            }
            spacePtr = false;
        } else {
            autoCode += tab1 + it.getPrivateName() + " = " + other +
                    "." + it.getPrivateName() + ";\n";
            spacePtr = true;
        }
        ++cnt;
    }
    autoCode += "\n";
    autoCode += tab1 + "return *this;\n";

    return autoCode;

}

void
CopyOperatorEqFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("    Copy Operator=");
}

void
CopyOperatorEqFn::setReturnType(std::string const &)
{
    MyClass *  parentClass = getParentClassPtr();
    if (parentClass) {
        std::string const  className = parentClass->getClassName();
        Function::setReturnType(className + " &");
    }
}

void
CopyOperatorEqFn::setReturnType(std::string &&  value)
{
    CopyOperatorEqFn::setReturnType(value);
}

void
CopyOperatorEqFn::setParam(std::vector<Parameter> const &)
{
    MyClass *  parentClass = getParentClassPtr();
    if (parentClass) {
        std::vector<Parameter>  params;
        Parameter  par1;
        par1.setParameterName(getOther());
        par1.setType(parentClass->getClassName() + " const &");
        params.push_back(std::move(par1));
        Function::setParam(std::move(params));
    }
}

void
CopyOperatorEqFn::setParam(std::vector<Parameter> &&  value)
{
    CopyOperatorEqFn::setParam(value);
}

void
CopyOperatorEqFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    setReturnType("");
    setParam({});
}

void
CopyOperatorEqFn::init()
{
    setBaseType(Etype::eCopyOperatorEqFn);

    setClassFunction(true);
    setAutoSource(true);
    CopyOperatorEqFn::setFunctionName("operator=");
    CopyOperatorEqFn::setReturnType("");
    CopyOperatorEqFn::setParam({});
}

bool
CopyOperatorEqFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
CopyOperatorEqFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
CopyOperatorEqFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
CopyOperatorEqFn::deserialize(const char *  data,
                              const size_t  size)
{
    CopyOperatorEqFn  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 0) {
        if (!me.Function::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
CopyOperatorEqFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        CopyOperatorEqFn &  rhs = dynamic_cast<CopyOperatorEqFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
