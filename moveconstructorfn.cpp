#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "field.h"
#include "moveconstructorfn.h"
#include "eobject.h"
#include "myclass.h"
#include "parameter.h"

namespace xu {

MoveConstructorFn::MoveConstructorFn():
        Function()
{
    init();
}

MoveConstructorFn::MoveConstructorFn(const MoveConstructorFn &  other):
        Function(other)
{
}

MoveConstructorFn::MoveConstructorFn(MoveConstructorFn &&  other) noexcept:
        Function(std::move(other))
{
}

MoveConstructorFn::MoveConstructorFn(MyClass *  parent):
        Function(parent)
{
}

MoveConstructorFn::~MoveConstructorFn() noexcept
{
}

MoveConstructorFn &
MoveConstructorFn::operator=(const MoveConstructorFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

MoveConstructorFn &
MoveConstructorFn::operator=(MoveConstructorFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

std::string
MoveConstructorFn::autoCode() const
{
    std::string  autoCode;
    const std::string  tab1(getDefTab());

    MyClass const *  parentPtr = getParentClassPtr();
    if (parentPtr == nullptr)  return autoCode;
    std::vector<Field> const  vecField = parentPtr->getField();

    for (const auto &  fd: vecField) {
        if (fd.isPointer()) {
            autoCode += tab1 + "other." + fd.getPrivateName() + " = nullptr;\n";
        }
    }

    return autoCode;
}

void
MoveConstructorFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("A   Move Constructor");
}

void
MoveConstructorFn::setParam(std::vector<Parameter> const &)
{
    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        std::string const  className = parentPtr->getClassName();
        std::vector<Parameter>  params;
        Parameter  par1;
        par1.setParameterName("other");
        par1.setType(className + " &&");
        params.push_back(std::move(par1));
        Function::setParam(std::move(params));
    }
}

void
MoveConstructorFn::setParam(std::vector<Parameter> &&  value)
{
    MoveConstructorFn::setParam(value);
}

void
MoveConstructorFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    setTreeLabel("A   Move Constructor");
    updateDefualtValue();
}

void
MoveConstructorFn::init()
{
    setTreeLabel("A   Move Constructor");
    setBaseType(Etype::eMoveConstructorFn);

    setClassFunction(true);
    setConstructor(true);
    setAutoSource(true);
    setNoexcept(true);
    MoveConstructorFn::setFunctionName("");
    MoveConstructorFn::setParam({});
    updateDefualtValue();
}

void
MoveConstructorFn::updateDefualtValue()
{
    std::vector<Field>  vecField;
    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        vecField = parentPtr->getField();
    }
    std::vector<std::string>  defVal;
    for (const auto &  fd: vecField) {
        defVal.push_back("std::move(other." + fd.getPrivateName() + ")");
    }
    setDefValueCtor(defVal);

    if (parentPtr && parentPtr->getClasstype() == ClassType::cppInherit) {
        size_t const  size = parentPtr->getMulInhClass().size();
        std::vector<std::string>  valueBaseClass(size, "std::move(other)");
        setInhValueBaseClass(valueBaseClass);
    }
}

bool
MoveConstructorFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
MoveConstructorFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
MoveConstructorFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
MoveConstructorFn::deserialize(const char *  data,
                               const size_t  size)
{
    MoveConstructorFn  me;
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
MoveConstructorFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        MoveConstructorFn &  rhs = dynamic_cast<MoveConstructorFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
