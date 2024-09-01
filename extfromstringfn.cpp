#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "extfromstringfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

ExtFromStringFn::ExtFromStringFn():
        Function(),
        m_className()
{
    init();
}

ExtFromStringFn::ExtFromStringFn(const ExtFromStringFn &  other):
        Function(other),
        m_className(other.m_className)
{
}

ExtFromStringFn::ExtFromStringFn(ExtFromStringFn &&  other) noexcept:
        Function(std::move(other)),
        m_className(std::move(other.m_className))
{
}

ExtFromStringFn::ExtFromStringFn(std::string const &  classname,
                                 MyClass *  parent):
        Function(parent),
        m_className(classname)
{
    init();
}

ExtFromStringFn::~ExtFromStringFn() noexcept
{
}

ExtFromStringFn &
ExtFromStringFn::operator=(const ExtFromStringFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    m_className = other.m_className;

    return *this;
}

ExtFromStringFn &
ExtFromStringFn::operator=(ExtFromStringFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    m_className = std::move(other.m_className);

    return *this;
}

void
ExtFromStringFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
ExtFromStringFn::setParam(std::vector<Parameter> const &)
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
ExtFromStringFn::setParam(std::vector<Parameter> &&  value)
{
    ExtFromStringFn::setParam(value);
}

void
ExtFromStringFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    if (value)  setClassName(value->getClassName());
}

std::string
ExtFromStringFn::autoCode() const
{
    std::string  res;
    std::string const  tab1(getDefTab());

    res += tab1 + "return value.fromString(data, size);\n";
    return res;
}

void
ExtFromStringFn::init()
{
    setBaseType(Etype::eExtFromStringFn);

    setAutoSource(true);
    ExtFromStringFn::setFunctionName("fromString");
    setReturnType("bool");
    ExtFromStringFn::setParam({});
}

std::string
ExtFromStringFn::getClassName() const
{
    return m_className;
}

void
ExtFromStringFn::setClassName(const std::string &  value)
{
    m_className = value;
    ExtFromStringFn::setParam({});
}

void
ExtFromStringFn::setClassName(std::string &&  value)
{
    m_className = std::move(value);
    ExtFromStringFn::setParam({});
}

bool
ExtFromStringFn::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const ExtFromStringFn &  rhs = dynamic_cast<const ExtFromStringFn &>(value);

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
ExtFromStringFn::less(const EObject &  value) const
{
    if (this->Function::less(value)) return true;
    if (!(this->Function::equal(value))) return false;

    try {
        const ExtFromStringFn &  rhs = dynamic_cast<const ExtFromStringFn &>(value);

        if (m_className < rhs.m_className) return true;
        if (rhs.m_className < m_className) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
ExtFromStringFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    xu::append(res, xu::toString(m_className));

    return res;
}

bool
ExtFromStringFn::deserialize(const char *  data,
                             const size_t  size)
{
    ExtFromStringFn  me;
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
ExtFromStringFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ExtFromStringFn &  rhs = dynamic_cast<ExtFromStringFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;
        swap(m_className, rhs.m_className);

        result = true;
    }
    return result;
}

}
