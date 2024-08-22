#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "actfn.h"
#include "field.h"
#include "actgetfn.h"
#include "myclass.h"
#include "function.h"

namespace xu {

ActGetFn::ActGetFn():
        ActFn()
{
    init();
}

ActGetFn::ActGetFn(const ActGetFn &  other):
        ActFn(other)
{
}

ActGetFn::ActGetFn(ActGetFn &&  other) noexcept:
        ActFn(std::move(other))
{
}

ActGetFn::ActGetFn(MyClass *  parentClass,
                   Field *  parentField):
        ActFn(parentClass, parentField)
{
    init();
}

ActGetFn::~ActGetFn() noexcept
{
}

ActGetFn &
ActGetFn::operator=(const ActGetFn &  other)
{
    if (this == &other) return *this;

    this->ActFn::operator=(other);

    return *this;
}

ActGetFn &
ActGetFn::operator=(ActGetFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->ActFn::operator=(std::move(other));

    return *this;
}

std::string
ActGetFn::autoCode() const
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
ActGetFn::setReturnType(std::string const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        if (parentField->isPointer()) {
            ActFn::setReturnType(parentField->getTypeName() + " *");
        } else {
            ActFn::setReturnType(parentField->getTypeName());
        }
    }
}

void
ActGetFn::setReturnType(std::string &&  value)
{
    ActGetFn::setReturnType(value);
}

void
ActGetFn::setFunctionName(std::string const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        std::string  fdName = parentField->getFieldName();
        if (fdName.size() > 0)  fdName[0] = xu::toupperS(fdName[0]);
        ActFn::setFunctionName("get" + fdName);
    }
}

void
ActGetFn::setParam(std::vector<Parameter> const &)
{
    Function::setParam({});
}

void
ActGetFn::setParam(std::vector<Parameter> &&)
{
    Function::setParam({});
}

void
ActGetFn::init()
{
    EObject::setBaseType(Etype::eActGetFn);

    setClassFunction(true);
    setAutoSource(true);
    setConst(true);
    setAction(Action::get);
    setParentFieldPtr(getParentFieldPtr());
}

bool
ActGetFn::equal(const EObject &  value) const
{
    return this->ActFn::equal(value);
}

bool
ActGetFn::less(const EObject &  value) const
{
    return this->ActFn::less(value);
}

std::string
ActGetFn::serialize() const
{
    std::string  res;

    xu::append(res, this->ActFn::serialize());

    return res;
}

bool
ActGetFn::deserialize(const char *  data,
                      const size_t  size)
{
    ActGetFn  me;
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
ActGetFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ActGetFn &  rhs = dynamic_cast<ActGetFn &>(value);
        this->ActFn::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
