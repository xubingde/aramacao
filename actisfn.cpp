#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "actfn.h"
#include "field.h"
#include "actisfn.h"
#include "myclass.h"
#include "function.h"

namespace xu {

ActIsFn::ActIsFn():
        ActFn()
{
    init();
}

ActIsFn::ActIsFn(const ActIsFn &  other):
        ActFn(other)
{
}

ActIsFn::ActIsFn(ActIsFn &&  other) noexcept:
        ActFn(std::move(other))
{
}

ActIsFn::ActIsFn(MyClass *  parentClass,
                 Field *  parentField):
        ActFn(parentClass, parentField)
{
    init();
}

ActIsFn::~ActIsFn() noexcept
{
}

ActIsFn &
ActIsFn::operator=(const ActIsFn &  other)
{
    if (this == &other) return *this;

    this->ActFn::operator=(other);

    return *this;
}

ActIsFn &
ActIsFn::operator=(ActIsFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->ActFn::operator=(std::move(other));

    return *this;
}

std::string
ActIsFn::autoCode() const
{
    std::string  res;
    std::string const  tab1(getDefTab());
    Field *  parentField = getParentFieldPtr();

    if (parentField) {
        res += tab1 + "return " + parentField->getPrivateName() + ";\n";
    }
    return res;
}

void
ActIsFn::setReturnType(std::string const &)
{
    ActFn::setReturnType("bool");
}

void
ActIsFn::setReturnType(std::string &&  value)
{
    ActIsFn::setReturnType(value);
}

void
ActIsFn::setFunctionName(std::string const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        std::string  fdName = parentField->getFieldName();
        if (fdName.size() > 0)  fdName[0] = xu::toupperS(fdName[0]);
        ActFn::setFunctionName("is" + fdName);
    }
}

void
ActIsFn::setParam(std::vector<Parameter> const &)
{
    ActFn::setParam({});
}

void
ActIsFn::setParam(std::vector<Parameter> &&  value)
{
    ActIsFn::setParam(value);
}

void
ActIsFn::init()
{
    setBaseType(Etype::eActIsFn);

    setClassFunction(true);
    setAutoSource(true);
    setConst(true);
    setAction(Action::is);
    setParentFieldPtr(getParentFieldPtr());
}

bool
ActIsFn::equal(const EObject &  value) const
{
    return this->ActFn::equal(value);
}

bool
ActIsFn::less(const EObject &  value) const
{
    return this->ActFn::less(value);
}

std::string
ActIsFn::serialize() const
{
    std::string  res;

    xu::append(res, this->ActFn::serialize());

    return res;
}

bool
ActIsFn::deserialize(const char *  data,
                     const size_t  size)
{
    ActIsFn  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 0) {
        if (!me.ActFn::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
ActIsFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ActIsFn &  rhs = dynamic_cast<ActIsFn &>(value);
        this->ActFn::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
