#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "noteqfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

NotEqFn::NotEqFn():
        Function(),
        m_className()
{
    init();
}

NotEqFn::NotEqFn(const NotEqFn &  other):
        Function(other),
        m_className(other.m_className)
{
}

NotEqFn::NotEqFn(NotEqFn &&  other) noexcept:
        Function(std::move(other)),
        m_className(std::move(other.m_className))
{
}

NotEqFn::NotEqFn(std::string const &  classname,
                 MyClass *  parent):
        Function(parent),
        m_className(classname)
{
    init();
}

NotEqFn::~NotEqFn() noexcept
{
}

NotEqFn &
NotEqFn::operator=(const NotEqFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    m_className = other.m_className;

    return *this;
}

NotEqFn &
NotEqFn::operator=(NotEqFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    m_className = std::move(other.m_className);

    return *this;
}

void
NotEqFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
NotEqFn::setParam(std::vector<Parameter> const &)
{
    std::vector<Parameter>  params;
    Parameter  par1, par2;
    par1.setParameterName(getLhs());
    par1.setType(m_className + " const &");
    par2.setParameterName(getRhs());
    par2.setType(m_className + " const &");
    params.push_back(std::move(par1));
    params.push_back(std::move(par2));
    Function::setParam(std::move(params));
}

void
NotEqFn::setParam(std::vector<Parameter> &&  value)
{
    NotEqFn::setParam(value);
}

void
NotEqFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    if (value)  setClassName(value->getClassName());
}

std::string
NotEqFn::autoCode() const
{
    std::string  res;
    std::string const  tab1(getDefTab());

    res += tab1 + "return !(" + getLhs() + " == " + getRhs() + ");\n";
    return res;
}

void
NotEqFn::init()
{
    setBaseType(Etype::eNotEqFn);

    setAutoSource(true);
    NotEqFn::setFunctionName("operator!=");
    setReturnType("bool");
    NotEqFn::setParam({});
    NotEqFn::setParentClassPtr(getParentClassPtr());
    setFriendClassName({m_className});
}

std::string
NotEqFn::getClassName() const
{
    return m_className;
}

void
NotEqFn::setClassName(const std::string &  value)
{
    m_className = value;
    setFriendClassName({m_className});
    NotEqFn::setParam({});
}

void
NotEqFn::setClassName(std::string &&  value)
{
    m_className = std::move(value);
    setFriendClassName({m_className});
    NotEqFn::setParam({});
}

bool
NotEqFn::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const NotEqFn &  rhs = dynamic_cast<const NotEqFn &>(value);

        result = this->Function::equal(value);
        if (!result) return result;

        result = ( m_className == rhs.m_className );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
NotEqFn::less(const EObject &  value) const
{
    if (this->Function::less(value)) return true;
    if (!(this->Function::equal(value))) return false;

    try {
        const NotEqFn &  rhs = dynamic_cast<const NotEqFn &>(value);

        if (m_className < rhs.m_className) return true;
        if (rhs.m_className < m_className) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
NotEqFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    xu::append(res, xu::toString(m_className));

    return res;
}

bool
NotEqFn::deserialize(const char *  data,
                     const size_t  size)
{
    NotEqFn  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 1) {
        if (!me.Function::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_className, vi[1]))  err.push_back({1});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
NotEqFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        NotEqFn &  rhs = dynamic_cast<NotEqFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;
        swap(m_className, rhs.m_className);

        result = true;
    }
    return result;
}

}
