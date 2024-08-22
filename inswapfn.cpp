#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "inswapfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

InSwapFn::InSwapFn():
        Function()
{
    init();
}

InSwapFn::InSwapFn(const InSwapFn &  other):
        Function(other)
{
}

InSwapFn::InSwapFn(InSwapFn &&  other) noexcept:
        Function(std::move(other))
{
}

InSwapFn::InSwapFn(MyClass *  parent):
        Function(parent)
{
    init();
}

InSwapFn::~InSwapFn() noexcept
{
}

InSwapFn &
InSwapFn::operator=(const InSwapFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

InSwapFn &
InSwapFn::operator=(InSwapFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

void
InSwapFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
InSwapFn::setParam(std::vector<Parameter> const &)
{
    MyClass *  parentPtr = getParentClassPtr();
    std::string  classname;
    if (parentPtr) {
        classname = parentPtr->getClassName();
    }
    std::vector<Parameter>  params;
    Parameter  par1;
    par1.setParameterName(getSig());
    par1.setType(classname + " &");
    params.push_back(std::move(par1));
    Function::setParam(std::move(params));
}

void
InSwapFn::setParam(std::vector<Parameter> &&  value)
{
    InSwapFn::setParam(value);
}

void
InSwapFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    InSwapFn::setParam({});
}

std::string
InSwapFn::autoCode() const
{
    std::string  res;
    std::string const  tab1(getDefTab());

    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        ClassType  ct = parentPtr->getClasstype();
        if (ct == ClassType::cppFinal) {
            res = parentPtr->toFCodeSwap();
        } else if (ct == ClassType::cppBase) {
            res += tab1 + "if (this == &" + getSig() + ") return true;\n";
            res += tab1 + "return this->exchange(" + getSig() + ");\n";
        }
    }

    return res;
}

void
InSwapFn::init()
{
    setBaseType(Etype::eInSwapFn);

    setClassFunction(true);
    setAutoSource(true);
    setNoexcept(true);
    InSwapFn::setFunctionName("swap");
    setReturnType("bool");
    InSwapFn::setParam({});
}

bool
InSwapFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
InSwapFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
InSwapFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
InSwapFn::deserialize(const char *  data,
                      const size_t  size)
{
    InSwapFn  me;
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
InSwapFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        InSwapFn &  rhs = dynamic_cast<InSwapFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
