#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "virtualexchangefn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

VirtualExchangeFn::VirtualExchangeFn():
        Function()
{
    init();
}

VirtualExchangeFn::VirtualExchangeFn(const VirtualExchangeFn &  other):
        Function(other)
{
}

VirtualExchangeFn::VirtualExchangeFn(VirtualExchangeFn &&  other) noexcept:
        Function(std::move(other))
{
}

VirtualExchangeFn::VirtualExchangeFn(MyClass *  parent):
        Function(parent)
{
    init();
}

VirtualExchangeFn::~VirtualExchangeFn() noexcept
{
}

VirtualExchangeFn &
VirtualExchangeFn::operator=(const VirtualExchangeFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

VirtualExchangeFn &
VirtualExchangeFn::operator=(VirtualExchangeFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

void
VirtualExchangeFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
VirtualExchangeFn::setParam(std::vector<Parameter> const &)
{
    MyClass *  parentPtr = getParentClassPtr();
    std::string  classname;
    if (parentPtr) {
        classname = parentPtr->getClassName();
        if (parentPtr->getBaseClassPrarm().size() > 0) {
            classname = parentPtr->getBaseClassPrarm();
        }
    }
    std::vector<Parameter>  params;
    Parameter  par1;
    par1.setParameterName(getSig());
    par1.setType(classname + " &");
    params.push_back(std::move(par1));
    Function::setParam(std::move(params));
}

void
VirtualExchangeFn::setParam(std::vector<Parameter> &&  value)
{
    VirtualExchangeFn::setParam(value);
}

void
VirtualExchangeFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);

    VirtualExchangeFn::setParam({});
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
VirtualExchangeFn::autoCode() const
{
    std::string  res;

    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr)  res = parentPtr->toFCodeSwap();

    return res;
}

void
VirtualExchangeFn::init()
{
    setBaseType(Etype::eVirtualExchangeFn);

    setClassFunction(true);
    setAutoSource(true);
    setVirtual(true);
    setNoexcept(true);
    VirtualExchangeFn::setFunctionName("exchange");
    setReturnType("bool");
    VirtualExchangeFn::setParam({});

    MyClass *  parent = getParentClassPtr();
    if (parent) {
        ClassType  ct = parent->getClasstype();
        if (ct == ClassType::cppInherit)  setOverride(true);
    }
}

bool
VirtualExchangeFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
VirtualExchangeFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
VirtualExchangeFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
VirtualExchangeFn::deserialize(const char *  data,
                               const size_t  size)
{
    VirtualExchangeFn  me;
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
VirtualExchangeFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        VirtualExchangeFn &  rhs = dynamic_cast<VirtualExchangeFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
