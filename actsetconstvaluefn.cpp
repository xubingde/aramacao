#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "actfn.h"
#include "field.h"
#include "actsetconstvaluefn.h"
#include "myclass.h"
#include "function.h"

namespace xu {

ActSetConstValueFn::ActSetConstValueFn():
        ActFn()
{
    init();
}

ActSetConstValueFn::ActSetConstValueFn(const ActSetConstValueFn &  other):
        ActFn(other)
{
}

ActSetConstValueFn::ActSetConstValueFn(ActSetConstValueFn &&  other) noexcept:
        ActFn(std::move(other))
{
}

ActSetConstValueFn::ActSetConstValueFn(MyClass *  parentClass,
                                       Field *  parentField):
        ActFn(parentClass, parentField)
{
    init();
}

ActSetConstValueFn::~ActSetConstValueFn() noexcept
{
}

ActSetConstValueFn &
ActSetConstValueFn::operator=(const ActSetConstValueFn &  other)
{
    if (this == &other) return *this;

    this->ActFn::operator=(other);

    return *this;
}

ActSetConstValueFn &
ActSetConstValueFn::operator=(ActSetConstValueFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->ActFn::operator=(std::move(other));

    return *this;
}

std::string
ActSetConstValueFn::autoCode() const
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
ActSetConstValueFn::setReturnType(std::string const &)
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
ActSetConstValueFn::setReturnType(std::string &&  value)
{
    ActSetConstValueFn::setReturnType(value);
}

void
ActSetConstValueFn::setFunctionName(std::string const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        std::string  fdName = parentField->getFieldName();
        if (fdName.size() > 0)  fdName[0] = xu::toupperS(fdName[0]);
        ActFn::setFunctionName("set" + fdName);
    }
}

void
ActSetConstValueFn::setParam(std::vector<Parameter> const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        std::vector<Parameter>  params;
        Parameter  par1;
        par1.setParameterName(getSig());
        par1.setType(parentField->getTypeName() + " const");
        params.push_back(std::move(par1));
        ActFn::setParam(std::move(params));
    }
}

void
ActSetConstValueFn::setParam(std::vector<Parameter> &&  value)
{
    ActSetConstValueFn::setParam(value);
}

void
ActSetConstValueFn::init()
{
    setBaseType(Etype::eActSetConstValueFn);

    setClassFunction(true);
    setAutoSource(true);
    setAction(Action::setConstValue);
    setParentFieldPtr(getParentFieldPtr());
}

bool
ActSetConstValueFn::equal(const EObject &  value) const
{
    return this->ActFn::equal(value);
}

bool
ActSetConstValueFn::less(const EObject &  value) const
{
    return this->ActFn::less(value);
}

std::string
ActSetConstValueFn::serialize() const
{
    std::string  res;

    xu::append(res, this->ActFn::serialize());

    return res;
}

bool
ActSetConstValueFn::deserialize(const char *  data,
                                const size_t  size)
{
    ActSetConstValueFn  me;
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
ActSetConstValueFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ActSetConstValueFn &  rhs = dynamic_cast<ActSetConstValueFn &>(value);
        this->ActFn::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
