#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "virtuallessfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

VirtualLessFn::VirtualLessFn():
        Function()
{
    init();
}

VirtualLessFn::VirtualLessFn(const VirtualLessFn &  other):
        Function(other)
{
}

VirtualLessFn::VirtualLessFn(VirtualLessFn &&  other) noexcept:
        Function(std::move(other))
{
}

VirtualLessFn::VirtualLessFn(MyClass *  parent):
        Function(parent)
{
    init();
}

VirtualLessFn::~VirtualLessFn() noexcept
{
}

VirtualLessFn &
VirtualLessFn::operator=(const VirtualLessFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

VirtualLessFn &
VirtualLessFn::operator=(VirtualLessFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

void
VirtualLessFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
VirtualLessFn::setParam(std::vector<Parameter> const &)
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
VirtualLessFn::setParam(std::vector<Parameter> &&  value)
{
    VirtualLessFn::setParam(value);
}

void
VirtualLessFn::setParentClassPtr(MyClass *  value)
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
VirtualLessFn::autoCode() const
{
    std::string  res;

    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr)  res = parentPtr->toFCodeLess();

    return res;
}

void
VirtualLessFn::init()
{
    setBaseType(Etype::eVirtualLessFn);

    setClassFunction(true);
    setAutoSource(true);
    setVirtual(true);
    setConst(true);
    VirtualLessFn::setFunctionName("less");
    setReturnType("bool");
    VirtualLessFn::setParam({});

    MyClass *  parent = getParentClassPtr();
    if (parent) {
        ClassType  ct = parent->getClasstype();
        if (ct == ClassType::cppInherit)  setOverride(true);
    }
}

bool
VirtualLessFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
VirtualLessFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
VirtualLessFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
VirtualLessFn::deserialize(const char *  data,
                           const size_t  size)
{
    VirtualLessFn  me;
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
VirtualLessFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        VirtualLessFn &  rhs = dynamic_cast<VirtualLessFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
