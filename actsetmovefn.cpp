#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "actfn.h"
#include "field.h"
#include "actsetmovefn.h"
#include "myclass.h"
#include "function.h"

namespace xu {

ActSetMoveFn::ActSetMoveFn():
        ActFn()
{
    init();
}

ActSetMoveFn::ActSetMoveFn(const ActSetMoveFn &  other):
        ActFn(other)
{
}

ActSetMoveFn::ActSetMoveFn(ActSetMoveFn &&  other) noexcept:
        ActFn(std::move(other))
{
}

ActSetMoveFn::ActSetMoveFn(MyClass *  parentClass,
                           Field *  parentField):
        ActFn(parentClass, parentField)
{
    init();
}

ActSetMoveFn::~ActSetMoveFn() noexcept
{
}

ActSetMoveFn &
ActSetMoveFn::operator=(const ActSetMoveFn &  other)
{
    if (this == &other) return *this;

    this->ActFn::operator=(other);

    return *this;
}

ActSetMoveFn &
ActSetMoveFn::operator=(ActSetMoveFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->ActFn::operator=(std::move(other));

    return *this;
}

std::string
ActSetMoveFn::autoCode() const
{
    std::string  res;
    std::string const  tab1(getDefTab());
    MyClass *  parentClass = getParentClassPtr();
    Field *  parentField = getParentFieldPtr();

    if (parentClass && parentField) {
        if (parentField->isPointer()) {
            res += tab1 + "delete " + parentField->getPrivateName() + ";\n";
            res += tab1 + parentField->getPrivateName() + " = new " +
                    parentField->getTypeName() + " { std::move(" + getSig() + ") };\n";
        } else {
            res += tab1 + parentField->getPrivateName() + " = std::move(" +
                    getSig() + ");\n";
        }
        if (parentClass->isSetterReturnThis()) {
            res += tab1 + "return *this;\n";
        }
    }
    return res;
}

void
ActSetMoveFn::setReturnType(std::string const &)
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
ActSetMoveFn::setReturnType(std::string &&  value)
{
    ActSetMoveFn::setReturnType(value);
}

void
ActSetMoveFn::setFunctionName(std::string const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        std::string  fdName = parentField->getFieldName();
        if (fdName.size() > 0)  fdName[0] = xu::toupperS(fdName[0]);
        ActFn::setFunctionName("set" + fdName);
    }
}

void
ActSetMoveFn::setParam(std::vector<Parameter> const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        std::vector<Parameter>  params;
        Parameter  par1;
        par1.setParameterName(getSig());
        par1.setType(parentField->getTypeName() + " &&");
        params.push_back(std::move(par1));
        ActFn::setParam(std::move(params));
    }
}

void
ActSetMoveFn::setParam(std::vector<Parameter> &&  value)
{
    ActSetMoveFn::setParam(value);
}

void
ActSetMoveFn::init()
{
    setBaseType(Etype::eActSetMoveFn);

    setClassFunction(true);
    setAutoSource(true);
    setAction(Action::setMove);
    setParentFieldPtr(getParentFieldPtr());
}

bool
ActSetMoveFn::equal(const EObject &  value) const
{
    return this->ActFn::equal(value);
}

bool
ActSetMoveFn::less(const EObject &  value) const
{
    return this->ActFn::less(value);
}

std::string
ActSetMoveFn::serialize() const
{
    std::string  res;

    xu::append(res, this->ActFn::serialize());

    return res;
}

bool
ActSetMoveFn::deserialize(const char *  data,
                          const size_t  size)
{
    ActSetMoveFn  me;
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
ActSetMoveFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ActSetMoveFn &  rhs = dynamic_cast<ActSetMoveFn &>(value);
        this->ActFn::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
