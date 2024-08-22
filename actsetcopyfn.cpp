#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "actfn.h"
#include "field.h"
#include "actsetcopyfn.h"
#include "myclass.h"
#include "function.h"

namespace xu {

ActSetCopyFn::ActSetCopyFn():
        ActFn()
{
    init();
}

ActSetCopyFn::ActSetCopyFn(const ActSetCopyFn &  other):
        ActFn(other)
{
}

ActSetCopyFn::ActSetCopyFn(ActSetCopyFn &&  other) noexcept:
        ActFn(std::move(other))
{
}

ActSetCopyFn::ActSetCopyFn(MyClass *  parentClass,
                           Field *  parentField):
        ActFn(parentClass, parentField)
{
    init();
}

ActSetCopyFn::~ActSetCopyFn() noexcept
{
}

ActSetCopyFn &
ActSetCopyFn::operator=(const ActSetCopyFn &  other)
{
    if (this == &other) return *this;

    this->ActFn::operator=(other);

    return *this;
}

ActSetCopyFn &
ActSetCopyFn::operator=(ActSetCopyFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->ActFn::operator=(std::move(other));

    return *this;
}

std::string
ActSetCopyFn::autoCode() const
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
ActSetCopyFn::setReturnType(std::string const &)
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
ActSetCopyFn::setReturnType(std::string &&  value)
{
    ActSetCopyFn::setReturnType(value);
}

void
ActSetCopyFn::setFunctionName(std::string const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        std::string  fdName = parentField->getFieldName();
        if (fdName.size() > 0)  fdName[0] = xu::toupperS(fdName[0]);
        ActFn::setFunctionName("set" + fdName);
    }
}

void
ActSetCopyFn::setParam(std::vector<Parameter> const &)
{
    Field *  parentField = getParentFieldPtr();
    if (parentField) {
        std::vector<Parameter>  params;
        Parameter  par1;
        par1.setParameterName(getSig());
        par1.setType(parentField->getTypeName() + " const &");
        params.push_back(std::move(par1));
        ActFn::setParam(std::move(params));
    }
}

void
ActSetCopyFn::setParam(std::vector<Parameter> &&  value)
{
    ActSetCopyFn::setParam(value);
}

void
ActSetCopyFn::init()
{
    setBaseType(Etype::eActSetCopyFn);

    setClassFunction(true);
    setAutoSource(true);
    setAction(Action::setCopy);
    setParentFieldPtr(getParentFieldPtr());
}

bool
ActSetCopyFn::equal(const EObject &  value) const
{
    return this->ActFn::equal(value);
}

bool
ActSetCopyFn::less(const EObject &  value) const
{
    return this->ActFn::less(value);
}

std::string
ActSetCopyFn::serialize() const
{
    std::string  res;

    xu::append(res, this->ActFn::serialize());

    return res;
}

bool
ActSetCopyFn::deserialize(const char *  data,
                          const size_t  size)
{
    ActSetCopyFn  me;
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
ActSetCopyFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ActSetCopyFn &  rhs = dynamic_cast<ActSetCopyFn &>(value);
        this->ActFn::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
