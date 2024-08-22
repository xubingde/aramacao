#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "infromstringfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

InFromStringFn::InFromStringFn():
        Function()
{
    init();
}

InFromStringFn::InFromStringFn(const InFromStringFn &  other):
        Function(other)
{
}

InFromStringFn::InFromStringFn(InFromStringFn &&  other) noexcept:
        Function(std::move(other))
{
}

InFromStringFn::InFromStringFn(MyClass *  parent):
        Function(parent)
{
    init();
}

InFromStringFn::~InFromStringFn() noexcept
{
}

InFromStringFn &
InFromStringFn::operator=(const InFromStringFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

InFromStringFn &
InFromStringFn::operator=(InFromStringFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

void
InFromStringFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

std::string
InFromStringFn::autoCode() const
{
    std::string  res;
    std::string const  tab1(getDefTab());

    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        ClassType  ct = parentPtr->getClasstype();
        if (ct == ClassType::cppFinal) {
            res = parentPtr->toFCodeFromString();
        } else if (ct == ClassType::cppBase) {
            res = tab1 + "return deserialize(data, size);\n";
        }
    }

    return res;
}

void
InFromStringFn::init()
{
    setBaseType(Etype::eInFromStringFn);

    setClassFunction(true);
    setAutoSource(true);
    InFromStringFn::setFunctionName("fromString");
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
}

bool
InFromStringFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
InFromStringFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
InFromStringFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
InFromStringFn::deserialize(const char *  data,
                            const size_t  size)
{
    InFromStringFn  me;
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
InFromStringFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        InFromStringFn &  rhs = dynamic_cast<InFromStringFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
