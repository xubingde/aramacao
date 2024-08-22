#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "lesseqfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

LessEqFn::LessEqFn():
        Function(),
        m_className()
{
    init();
}

LessEqFn::LessEqFn(const LessEqFn &  other):
        Function(other),
        m_className(other.m_className)
{
}

LessEqFn::LessEqFn(LessEqFn &&  other) noexcept:
        Function(std::move(other)),
        m_className(std::move(other.m_className))
{
}

LessEqFn::LessEqFn(std::string const &  classname,
                   MyClass *  parent):
        Function(parent),
        m_className(classname)
{
    init();
}

LessEqFn::~LessEqFn() noexcept
{
}

LessEqFn &
LessEqFn::operator=(const LessEqFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    m_className = other.m_className;

    return *this;
}

LessEqFn &
LessEqFn::operator=(LessEqFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    m_className = std::move(other.m_className);

    return *this;
}

void
LessEqFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
LessEqFn::setParam(std::vector<Parameter> const &)
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
LessEqFn::setParam(std::vector<Parameter> &&  value)
{
    LessEqFn::setParam(value);
}

void
LessEqFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    if (value)  setClassName(value->getClassName());
}

void
LessEqFn::init()
{
    setBaseType(Etype::eLessEqFn);

    LessEqFn::setFunctionName("operator<=");
    setReturnType("bool");
    setMCode(getDefTab() + "return !(" + getLhs() + " > " + getRhs() + ");\n");
    LessEqFn::setParam({});
    LessEqFn::setParentClassPtr(getParentClassPtr());
    setFriendClassName({m_className});
}

std::string
LessEqFn::getClassName() const
{
    return m_className;
}

void
LessEqFn::setClassName(const std::string &  value)
{
    m_className = value;
    setFriendClassName({m_className});
    LessEqFn::setParam({});
}

void
LessEqFn::setClassName(std::string &&  value)
{
    m_className = std::move(value);
    setFriendClassName({m_className});
    LessEqFn::setParam({});
}

bool
LessEqFn::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const LessEqFn &  rhs = dynamic_cast<const LessEqFn &>(value);

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
LessEqFn::less(const EObject &  value) const
{
    if (this->Function::less(value)) return true;
    if (!(this->Function::equal(value))) return false;

    try {
        const LessEqFn &  rhs = dynamic_cast<const LessEqFn &>(value);

        if (m_className < rhs.m_className) return true;
        if (rhs.m_className < m_className) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
LessEqFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    xu::append(res, xu::toString(m_className));

    return res;
}

bool
LessEqFn::deserialize(const char *  data,
                      const size_t  size)
{
    LessEqFn  me;
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
LessEqFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        LessEqFn &  rhs = dynamic_cast<LessEqFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;
        swap(m_className, rhs.m_className);

        result = true;
    }
    return result;
}

}
