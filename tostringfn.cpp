#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "tostringfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

ToStringFn::ToStringFn():
        Function()
{
    init();
}

ToStringFn::ToStringFn(const ToStringFn &  other):
        Function(other)
{
}

ToStringFn::ToStringFn(ToStringFn &&  other) noexcept:
        Function(std::move(other))
{
}

ToStringFn::ToStringFn(MyClass *  parent):
        Function(parent)
{
    init();
}

ToStringFn::~ToStringFn() noexcept
{
}

ToStringFn &
ToStringFn::operator=(const ToStringFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

ToStringFn &
ToStringFn::operator=(ToStringFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

void
ToStringFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

std::string
ToStringFn::autoCode() const
{
    std::string  res;
    std::string const  tab1(getDefTab());

    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        ClassType  ct = parentPtr->getClasstype();
        if (ct == ClassType::cppFinal) {
            res = parentPtr->toFCodeToString();
        } else {
            res = tab1 + "return serialize();\n";
        }
    }

    return res;
}

void
ToStringFn::init()
{
    setBaseType(Etype::eToStringFn);

    setClassFunction(true);
    setAutoSource(true);
    setConst(true);
    ToStringFn::setFunctionName("toString");
    setReturnType("std::string");
}

bool
ToStringFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
ToStringFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
ToStringFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
ToStringFn::deserialize(const char *  data,
                        const size_t  size)
{
    ToStringFn  me;
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
ToStringFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ToStringFn &  rhs = dynamic_cast<ToStringFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
