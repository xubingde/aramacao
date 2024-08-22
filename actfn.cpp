#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "actfn.h"
#include "field.h"
#include "function.h"
#include "myclass.h"

namespace xu {

ActFn::ActFn():
        Function(),
        m_action(),
        m_parentFieldPtr(nullptr)
{
    init();
}

ActFn::ActFn(const ActFn &  other):
        Function(other),
        m_action(other.m_action),
        m_parentFieldPtr(other.m_parentFieldPtr)
{
}

ActFn::ActFn(ActFn &&  other) noexcept:
        Function(std::move(other)),
        m_action(std::move(other.m_action)),
        m_parentFieldPtr(std::move(other.m_parentFieldPtr))
{
}

ActFn::ActFn(MyClass *  parentClass,
             Field *  parentField):
        Function(parentClass),
        m_action(Action::none),
        m_parentFieldPtr(parentField)
{
    init();
}

ActFn::~ActFn() noexcept
{
}

ActFn &
ActFn::operator=(const ActFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    m_action = other.m_action;
    m_parentFieldPtr = other.m_parentFieldPtr;

    return *this;
}

ActFn &
ActFn::operator=(ActFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    m_action = std::move(other.m_action);
    m_parentFieldPtr = std::move(other.m_parentFieldPtr);

    return *this;
}

std::string
ActFn::autoCode() const
{
    return std::string();
}

void
ActFn::setReturnType(std::string const &  value)
{
    Function::setReturnType(value);
}

void
ActFn::setReturnType(std::string &&  value)
{
    Function::setReturnType(std::move(value));
}

void
ActFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
}

void
ActFn::setParam(std::vector<Parameter> const &  value)
{
    Function::setParam(value);
}

void
ActFn::setParam(std::vector<Parameter> &&  value)
{
    Function::setParam(std::move(value));
}

void
ActFn::init()
{
    std::string const  fnName = getFunctionName();
    setTreeLabel("F   " + fnName);
    setBaseType(Etype::eActFn);

    setClassFunction(true);
    setAutoSource(true);
}

Action
ActFn::getAction() const
{
    return m_action;
}

void
ActFn::setAction(const Action  value)
{
    m_action = value;
}

Field *
ActFn::getParentFieldPtr() const
{
    return m_parentFieldPtr;
}

void
ActFn::setParentFieldPtr(Field *  value)
{
    m_parentFieldPtr = value;
    setReturnType("");
    setFunctionName("");
    setParam({});
}

bool
ActFn::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const ActFn &  rhs = dynamic_cast<const ActFn &>(value);

        result = this->Function::equal(value);
        if (!result) return result;

        result = ( m_action == rhs.m_action );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
ActFn::less(const EObject &  value) const
{
    if (this->Function::less(value)) return true;
    if (!(this->Function::equal(value))) return false;

    try {
        const ActFn &  rhs = dynamic_cast<const ActFn &>(value);

        if (m_action < rhs.m_action) return true;
        if (rhs.m_action < m_action) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
ActFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    xu::append(res, xu::toString(m_action));

    return res;
}

bool
ActFn::deserialize(const char *  data,
                   const size_t  size)
{
    ActFn  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 1) {
        if (!me.Function::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_action, vi[1]))  err.push_back({1});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
ActFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ActFn &  rhs = dynamic_cast<ActFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;
        swap(m_action, rhs.m_action);
        swap(m_parentFieldPtr, rhs.m_parentFieldPtr);

        result = true;
    }
    return result;
}

}
