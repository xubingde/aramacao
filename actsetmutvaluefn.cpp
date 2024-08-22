#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "actfn.h"
#include "field.h"
#include "actsetmutvaluefn.h"
#include "myclass.h"
#include "function.h"

namespace xu {

ActSetMutValueFn::ActSetMutValueFn():
        ActFn()
{
    init();
}

ActSetMutValueFn::ActSetMutValueFn(const ActSetMutValueFn &  other):
        ActFn(other)
{
}

ActSetMutValueFn::ActSetMutValueFn(ActSetMutValueFn &&  other) noexcept:
        ActFn(std::move(other))
{
}

ActSetMutValueFn::ActSetMutValueFn(MyClass *  parentClass,
                                   Field *  parentField):
        ActFn(parentClass, parentField)
{
    init();
}

ActSetMutValueFn::~ActSetMutValueFn() noexcept
{
}

ActSetMutValueFn &
ActSetMutValueFn::operator=(const ActSetMutValueFn &  other)
{
    if (this == &other) return *this;

    this->ActFn::operator=(other);

    return *this;
}

ActSetMutValueFn &
ActSetMutValueFn::operator=(ActSetMutValueFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->ActFn::operator=(std::move(other));

    return *this;
}

std::string
ActSetMutValueFn::autoCode() const
{
    std::string  res;
    std::string const  tab1(getDefTab());
    MyClass *  parentClass = getParentClassPtr();
    Field *  parentField = getParentFieldPtr();

    if (parentClass && parentField) {
        if (parentField->isPointer()) {
            res += tab1 + "delete " + parentField->getPrivateName() + ";\n";
            res += tab1 + parentField->getPrivateName() + " = new " +
                    parentField->getTypeName() + " { " + getSig() + " };\n";
        } else {
            res += tab1 + parentField->getPrivateName() + " = " + getSig() + ";\n";
        }
        if (parentClass->isSetterReturnThis()) {
            res += tab1 + "return *this;\n";
        }
    }
    return res;
}

void
ActSetMutValueFn::setReturnType(std::string const &)
{
    MyClass *  parentClass = getParentClassPtr();
    if (parentClass) {
        std::string const  className = parentClass->getClassName();
        if (parentClass->isSetterReturnThis()) {
            ActFn::setReturnType(className + " &");
        } else {
            ActFn::setReturnType("void");
        }
    }
}

void
ActSetMutValueFn::setReturnType(std::string &&  value)
{
    ActSetMutValueFn::setReturnType(value);
}

void
ActSetMutValueFn::setFunctionName(std::string const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        std::string  fdName = parentField->getFieldName();
        if (fdName.size() > 0)  fdName[0] = xu::toupperS(fdName[0]);
        ActFn::setFunctionName("set" + fdName);
    }
}

void
ActSetMutValueFn::setParam(std::vector<Parameter> const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        std::vector<Parameter>  params;
        Parameter  par1;
        par1.setParameterName(getSig());
        par1.setType(parentField->getTypeName());
        params.push_back(std::move(par1));
        ActFn::setParam(std::move(params));
    }
}

void
ActSetMutValueFn::setParam(std::vector<Parameter> &&  value)
{
    ActSetMutValueFn::setParam(value);
}

void
ActSetMutValueFn::init()
{
    setBaseType(Etype::eActSetMutValueFn);

    setClassFunction(true);
    setAutoSource(true);
    setAction(Action::setMutValue);
    setParentFieldPtr(getParentFieldPtr());
}

bool
ActSetMutValueFn::equal(const EObject &  value) const
{
    return this->ActFn::equal(value);
}

bool
ActSetMutValueFn::less(const EObject &  value) const
{
    return this->ActFn::less(value);
}

std::string
ActSetMutValueFn::serialize() const
{
    std::string  res;

    xu::append(res, this->ActFn::serialize());

    return res;
}

bool
ActSetMutValueFn::deserialize(const char *  data,
                              const size_t  size)
{
    ActSetMutValueFn  me;
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
ActSetMutValueFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ActSetMutValueFn &  rhs = dynamic_cast<ActSetMutValueFn &>(value);
        this->ActFn::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
