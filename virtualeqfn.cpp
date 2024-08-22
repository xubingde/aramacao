#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "virtualeqfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

VirtualEqFn::VirtualEqFn():
        Function()
{
    init();
}

VirtualEqFn::VirtualEqFn(const VirtualEqFn &  other):
        Function(other)
{
}

VirtualEqFn::VirtualEqFn(VirtualEqFn &&  other) noexcept:
        Function(std::move(other))
{
}

VirtualEqFn::VirtualEqFn(MyClass *  parent):
        Function(parent)
{
    init();
}

VirtualEqFn::~VirtualEqFn() noexcept
{
}

VirtualEqFn &
VirtualEqFn::operator=(const VirtualEqFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

VirtualEqFn &
VirtualEqFn::operator=(VirtualEqFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

void
VirtualEqFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
VirtualEqFn::setParam(std::vector<Parameter> const &)
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
    par1.setType(classname + " const &");
    params.push_back(std::move(par1));
    Function::setParam(std::move(params));
}

void
VirtualEqFn::setParam(std::vector<Parameter> &&  value)
{
    VirtualEqFn::setParam(value);
}

void
VirtualEqFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);

    setParam({});
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
VirtualEqFn::autoCode() const
{
    std::string  res;

    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr)  res = parentPtr->toFCodeEq();

    return res;
}

void
VirtualEqFn::init()
{
    setBaseType(Etype::eVirtualEqFn);

    setClassFunction(true);
    setAutoSource(true);
    setVirtual(true);
    setConst(true);
    VirtualEqFn::setFunctionName("equal");
    setReturnType("bool");
    VirtualEqFn::setParam({});

    MyClass *  parent = getParentClassPtr();
    if (parent) {
        ClassType  ct = parent->getClasstype();
        if (ct == ClassType::cppInherit)  setOverride(true);
    }
}

bool
VirtualEqFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
VirtualEqFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
VirtualEqFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
VirtualEqFn::deserialize(const char *  data,
                         const size_t  size)
{
    VirtualEqFn  me;
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
VirtualEqFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        VirtualEqFn &  rhs = dynamic_cast<VirtualEqFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
