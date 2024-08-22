#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "actfn.h"
#include "field.h"
#include "acthasfn.h"
#include "myclass.h"
#include "function.h"

namespace xu {

ActHasFn::ActHasFn():
        ActFn()
{
    init();
}

ActHasFn::ActHasFn(const ActHasFn &  other):
        ActFn(other)
{
}

ActHasFn::ActHasFn(ActHasFn &&  other) noexcept:
        ActFn(std::move(other))
{
}

ActHasFn::ActHasFn(MyClass *  parentClass,
                   Field *  parentField):
        ActFn(parentClass, parentField)
{
    init();
}

ActHasFn::~ActHasFn() noexcept
{
}

ActHasFn &
ActHasFn::operator=(const ActHasFn &  other)
{
    if (this == &other) return *this;

    this->ActFn::operator=(other);

    return *this;
}

ActHasFn &
ActHasFn::operator=(ActHasFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->ActFn::operator=(std::move(other));

    return *this;
}

std::string
ActHasFn::autoCode() const
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
ActHasFn::setReturnType(std::string const &)
{
    ActFn::setReturnType("bool");
}

void
ActHasFn::setReturnType(std::string &&  value)
{
    ActHasFn::setReturnType(value);
}

void
ActHasFn::setFunctionName(std::string const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        std::string  fdName = parentField->getFieldName();
        if (fdName.size() > 0)  fdName[0] = xu::toupperS(fdName[0]);
        ActFn::setFunctionName("has" + fdName);
    }
}

void
ActHasFn::setParam(std::vector<Parameter> const &)
{
    ActFn::setParam({});
}

void
ActHasFn::setParam(std::vector<Parameter> &&  value)
{
    ActHasFn::setParam(value);
}

void
ActHasFn::init()
{
    setBaseType(Etype::eActHasFn);

    setClassFunction(true);
    setAutoSource(true);
    setConst(true);
    setAction(Action::has);
    setParentFieldPtr(getParentFieldPtr());
}

bool
ActHasFn::equal(const EObject &  value) const
{
    return this->ActFn::equal(value);
}

bool
ActHasFn::less(const EObject &  value) const
{
    return this->ActFn::less(value);
}

std::string
ActHasFn::serialize() const
{
    std::string  res;

    xu::append(res, this->ActFn::serialize());

    return res;
}

bool
ActHasFn::deserialize(const char *  data,
                      const size_t  size)
{
    ActHasFn  me;
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
ActHasFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ActHasFn &  rhs = dynamic_cast<ActHasFn &>(value);
        this->ActFn::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
