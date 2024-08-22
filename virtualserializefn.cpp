#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "virtualserializefn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

VirtualSerializeFn::VirtualSerializeFn():
        Function()
{
    init();
}

VirtualSerializeFn::VirtualSerializeFn(const VirtualSerializeFn &  other):
        Function(other)
{
}

VirtualSerializeFn::VirtualSerializeFn(VirtualSerializeFn &&  other) noexcept:
        Function(std::move(other))
{
}

VirtualSerializeFn::VirtualSerializeFn(MyClass *  parent):
        Function(parent)
{
    init();
}

VirtualSerializeFn::~VirtualSerializeFn() noexcept
{
}

VirtualSerializeFn &
VirtualSerializeFn::operator=(const VirtualSerializeFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

VirtualSerializeFn &
VirtualSerializeFn::operator=(VirtualSerializeFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

void
VirtualSerializeFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
VirtualSerializeFn::setParentClassPtr(MyClass *  value)
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
VirtualSerializeFn::autoCode() const
{
    std::string  res;

    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr)  res = parentPtr->toFCodeToString();

    return res;
}

void
VirtualSerializeFn::init()
{
    setBaseType(Etype::eVirtualSerializeFn);

    setClassFunction(true);
    setAutoSource(true);
    setVirtual(true);
    setConst(true);
    VirtualSerializeFn::setFunctionName("serialize");
    setReturnType("std::string");

    MyClass *  parent = getParentClassPtr();
    if (parent) {
        ClassType  ct = parent->getClasstype();
        if (ct == ClassType::cppInherit)  setOverride(true);
    }
}

bool
VirtualSerializeFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
VirtualSerializeFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
VirtualSerializeFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
VirtualSerializeFn::deserialize(const char *  data,
                                const size_t  size)
{
    VirtualSerializeFn  me;
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
VirtualSerializeFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        VirtualSerializeFn &  rhs = dynamic_cast<VirtualSerializeFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
