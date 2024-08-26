#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "field.h"
#include "moveoperatoreqfn.h"
#include "eobject.h"
#include "myclass.h"
#include "parameter.h"

namespace xu {

MoveOperatorEqFn::MoveOperatorEqFn():
        Function()
{
    init();
}

MoveOperatorEqFn::MoveOperatorEqFn(const MoveOperatorEqFn &  other):
        Function(other)
{
}

MoveOperatorEqFn::MoveOperatorEqFn(MoveOperatorEqFn &&  other) noexcept:
        Function(std::move(other))
{
}

MoveOperatorEqFn::MoveOperatorEqFn(MyClass *  parent):
        Function(parent)
{
    init();
}

MoveOperatorEqFn::~MoveOperatorEqFn() noexcept
{
}

MoveOperatorEqFn &
MoveOperatorEqFn::operator=(const MoveOperatorEqFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

MoveOperatorEqFn &
MoveOperatorEqFn::operator=(MoveOperatorEqFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

std::string
MoveOperatorEqFn::autoCode() const
{
    std::string  autoCode;
    std::string const  tab1(getDefTab());
    std::string const  other(getOther());

    MyClass const *  parentPtr = getParentClassPtr();
    if (parentPtr == nullptr)  return autoCode;
    std::vector<Field> const  vecField = parentPtr->getField();

    autoCode += tab1 + "if (this == &" + other + ") return *this;\n";
    if (parentPtr->getClasstype() == ClassType::cppInherit) {
        autoCode += "\n";
        autoCode += tab1 + "this->" + parentPtr->getBaseClassFirst().first +
                "::operator=(std::move(" + other + "));\n";

        std::vector<std::tuple<std::string, Purview, bool>> const &  mulClass =
                parentPtr->getMulInhClass();
        for (const auto &  it: mulClass) {
            autoCode += tab1 + "this->" + std::get<0>(it) +
                    "::operator=(std::move(" + other + "));\n";
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
            autoCode += tab1 + it.getPrivateName() + " = " + other + "." +
                    it.getPrivateName() + ";\n";
            autoCode += tab1 + other + "." + it.getPrivateName() +
                    " = nullptr;\n";
            if (cnt != size - 1) {
                autoCode += "\n";
            }
            spacePtr = false;
        } else {
            autoCode += tab1 + it.getPrivateName() + " = std::move(" +
                    other + "." + it.getPrivateName() + ");\n";
            spacePtr = true;
        }
        ++cnt;
    }
    autoCode += "\n";
    autoCode += tab1 + "return *this;\n";

    return autoCode;

}

void
MoveOperatorEqFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("A   Move Operator=");
}

void
MoveOperatorEqFn::setReturnType(std::string const &)
{
    MyClass *  parentClass = getParentClassPtr();
    if (parentClass) {
        std::string const  className = parentClass->getClassName();
        Function::setReturnType(className + " &");
    }
}

void
MoveOperatorEqFn::setReturnType(std::string &&  value)
{
    MoveOperatorEqFn::setReturnType(value);
}

void
MoveOperatorEqFn::setParam(std::vector<Parameter> const &)
{
    MyClass *  parentClass = getParentClassPtr();
    if (parentClass) {
        std::vector<Parameter>  params;
        Parameter  par1;
        par1.setParameterName(getOther());
        par1.setType(parentClass->getClassName() + " &&");
        params.push_back(std::move(par1));
        Function::setParam(std::move(params));
    }
}

void
MoveOperatorEqFn::setParam(std::vector<Parameter> &&  value)
{
    MoveOperatorEqFn::setParam(value);
}

void
MoveOperatorEqFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    setReturnType("");
    setParam({});
}

void
MoveOperatorEqFn::init()
{
    setBaseType(Etype::eMoveOperatorEqFn);

    setClassFunction(true);
    setAutoSource(true);
    MoveOperatorEqFn::setFunctionName("operator=");
    MoveOperatorEqFn::setReturnType("");
    MoveOperatorEqFn::setParam({});
}

bool
MoveOperatorEqFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
MoveOperatorEqFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
MoveOperatorEqFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
MoveOperatorEqFn::deserialize(const char *  data,
                              const size_t  size)
{
    MoveOperatorEqFn  me;
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
MoveOperatorEqFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        MoveOperatorEqFn &  rhs = dynamic_cast<MoveOperatorEqFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
