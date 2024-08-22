#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "deserializefn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

DeserializeFn::DeserializeFn():
        Function()
{
    init();
}

DeserializeFn::DeserializeFn(const DeserializeFn &  other):
        Function(other)
{
}

DeserializeFn::DeserializeFn(DeserializeFn &&  other) noexcept:
        Function(std::move(other))
{
}

DeserializeFn::DeserializeFn(MyClass *  parent):
        Function(parent)
{
    init();
}

DeserializeFn::~DeserializeFn() noexcept
{
}

DeserializeFn &
DeserializeFn::operator=(const DeserializeFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

DeserializeFn &
DeserializeFn::operator=(DeserializeFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

void
DeserializeFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
DeserializeFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);

    if (value) {
        ClassType  ct = value->getClasstype();
        if (ct == ClassType::cppInherit) {
            setOverride(true);
        } else {
            setOverride(false);
        }
    }
}

std::string
DeserializeFn::autoCode() const
{
    std::string  res;

    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr)  res = parentPtr->toFCodeFromString();

    return res;
}

void
DeserializeFn::init()
{
    setBaseType(Etype::eDeserializeFn);

    setClassFunction(true);
    setAutoSource(true);
    setVirtual(true);
    DeserializeFn::setFunctionName("deserialize");
    setReturnType("bool");

    std::vector<Parameter>  params;
    Parameter  par1, par2;
    par1.setParameterName("data");
    par1.setType("char const *");
    par2.setParameterName("size");
    par2.setType("size_t const");
    params.push_back(std::move(par1));
    params.push_back(std::move(par2));
    Function::setParam(std::move(params));

    MyClass *  parent = getParentClassPtr();
    if (parent) {
        ClassType  ct = parent->getClasstype();
        if (ct == ClassType::cppInherit)  setOverride(true);
    }
}

bool
DeserializeFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
DeserializeFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
DeserializeFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
DeserializeFn::deserialize(const char *  data,
                           const size_t  size)
{
    DeserializeFn  me;
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
DeserializeFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        DeserializeFn &  rhs = dynamic_cast<DeserializeFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
