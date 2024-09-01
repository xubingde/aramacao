#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "myclass.h"
#include "eobject.h"
#include "publictype.h"
#include "field.h"
#include "defaultconstructorfn.h"

namespace xu {

DefaultConstructorFn::DefaultConstructorFn():
        Function()
{
    init();
}

DefaultConstructorFn::DefaultConstructorFn(const DefaultConstructorFn &  other):
        Function(other)
{
}

DefaultConstructorFn::DefaultConstructorFn(DefaultConstructorFn &&  other) noexcept:
        Function(std::move(other))
{
}

DefaultConstructorFn::DefaultConstructorFn(MyClass *  parent):
        Function(parent)
{
    init();
}

DefaultConstructorFn::~DefaultConstructorFn() noexcept
{
}

DefaultConstructorFn &
DefaultConstructorFn::operator=(const DefaultConstructorFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

DefaultConstructorFn &
DefaultConstructorFn::operator=(DefaultConstructorFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

std::string
DefaultConstructorFn::autoCode() const
{
    std::string  autoCode;
    const std::string  tab1(getDefTab());

    MyClass const *  parentPtr = getParentClassPtr();
    if (parentPtr == nullptr)  return autoCode;
    std::vector<Field> const  vecField = parentPtr->getField();

    for (const auto &  fd: vecField) {
        if (fd.isPointer()) {
            const std::string  defv = fd.getDefValue();
            if (!(defv == "nullptr" || defv.size() == 0)) {
                autoCode += tab1 + fd.getPrivateName() + " = new " +
                        fd.getTypeName() + "(" + defv + ");\n";
            }
        }
    }

    return autoCode;
}

void
DefaultConstructorFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("A   Default Constructor");
}

void
DefaultConstructorFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    setTreeLabel("A   Default Constructor");
    updateDefualtValue();
}

void
DefaultConstructorFn::init()
{
    setTreeLabel("A   Default Constructor");
    setBaseType(Etype::eDefaultConstructorFn);

    setClassFunction(true);
    setConstructor(true);
    setAutoSource(true);
    DefaultConstructorFn::setFunctionName("");
    updateDefualtValue();
}

void
DefaultConstructorFn::updateDefualtValue()
{
    std::vector<Field>  vecField;
    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        vecField = parentPtr->getField();
    }
    std::vector<std::string>  defVal;
    for (const auto &  fd: vecField) {
        defVal.push_back(fd.getCtorDefValue());
    }
    setDefValueCtor(defVal);

    if (parentPtr && parentPtr->getClasstype() == ClassType::cppInherit) {
        size_t const  size = parentPtr->getMulInhClass().size();
        std::vector<std::string>  valueBaseClass(size, "");
        setInhValueBaseClass(valueBaseClass);
    }
}

bool
DefaultConstructorFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
DefaultConstructorFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
DefaultConstructorFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
DefaultConstructorFn::deserialize(const char *  data,
                                  const size_t  size)
{
    DefaultConstructorFn  me;
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
DefaultConstructorFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        DefaultConstructorFn &  rhs = dynamic_cast<DefaultConstructorFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
