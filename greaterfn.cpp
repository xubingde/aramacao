#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "greaterfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

GreaterFn::GreaterFn():
        Function(),
        m_className()
{
    init();
}

GreaterFn::GreaterFn(const GreaterFn &  other):
        Function(other),
        m_className(other.m_className)
{
}

GreaterFn::GreaterFn(GreaterFn &&  other) noexcept:
        Function(std::move(other)),
        m_className(std::move(other.m_className))
{
}

GreaterFn::GreaterFn(std::string const &  classname,
                     MyClass *  parent):
        Function(parent),
        m_className(classname)
{
    init();
}

GreaterFn::~GreaterFn() noexcept
{
}

GreaterFn &
GreaterFn::operator=(const GreaterFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    m_className = other.m_className;

    return *this;
}

GreaterFn &
GreaterFn::operator=(GreaterFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    m_className = std::move(other.m_className);

    return *this;
}

void
GreaterFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
GreaterFn::setParam(std::vector<Parameter> const &)
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
GreaterFn::setParam(std::vector<Parameter> &&  value)
{
    GreaterFn::setParam(value);
}

void
GreaterFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    if (value)  setClassName(value->getClassName());
}

void
GreaterFn::init()
{
    setBaseType(Etype::eGreaterFn);

    GreaterFn::setFunctionName("operator>");
    setReturnType("bool");
    setMCode(getDefTab() + "return " + getRhs() + " < " + getLhs() + ";\n");
    GreaterFn::setParam({});
    GreaterFn::setParentClassPtr(getParentClassPtr());
    setFriendClassName({m_className});
}

std::string
GreaterFn::getClassName() const
{
    return m_className;
}

void
GreaterFn::setClassName(const std::string &  value)
{
    m_className = value;
    setFriendClassName({m_className});
    GreaterFn::setParam({});
}

void
GreaterFn::setClassName(std::string &&  value)
{
    m_className = std::move(value);
    setFriendClassName({m_className});
    GreaterFn::setParam({});
}

bool
GreaterFn::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const GreaterFn &  rhs = dynamic_cast<const GreaterFn &>(value);

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
GreaterFn::less(const EObject &  value) const
{
    if (this->Function::less(value)) return true;
    if (!(this->Function::equal(value))) return false;

    try {
        const GreaterFn &  rhs = dynamic_cast<const GreaterFn &>(value);

        if (m_className < rhs.m_className) return true;
        if (rhs.m_className < m_className) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
GreaterFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    xu::append(res, xu::toString(m_className));

    return res;
}

bool
GreaterFn::deserialize(const char *  data,
                       const size_t  size)
{
    GreaterFn  me;
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
GreaterFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        GreaterFn &  rhs = dynamic_cast<GreaterFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;
        swap(m_className, rhs.m_className);

        result = true;
    }
    return result;
}

}
