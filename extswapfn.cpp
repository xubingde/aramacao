#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "extswapfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

ExtSwapFn::ExtSwapFn():
        Function(),
        m_className()
{
    init();
}

ExtSwapFn::ExtSwapFn(const ExtSwapFn &  other):
        Function(other),
        m_className(other.m_className)
{
}

ExtSwapFn::ExtSwapFn(ExtSwapFn &&  other) noexcept:
        Function(std::move(other)),
        m_className(std::move(other.m_className))
{
}

ExtSwapFn::ExtSwapFn(std::string const &  classname,
                     MyClass *  parent):
        Function(parent),
        m_className(classname)
{
    init();
}

ExtSwapFn::~ExtSwapFn() noexcept
{
}

ExtSwapFn &
ExtSwapFn::operator=(const ExtSwapFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    m_className = other.m_className;

    return *this;
}

ExtSwapFn &
ExtSwapFn::operator=(ExtSwapFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    m_className = std::move(other.m_className);

    return *this;
}

void
ExtSwapFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
ExtSwapFn::setParam(std::vector<Parameter> const &)
{
    std::vector<Parameter>  params;
    Parameter  par1, par2;
    par1.setParameterName(getLhs());
    par1.setType(m_className + " &");
    par2.setParameterName(getRhs());
    par2.setType(m_className + " &");
    params.push_back(std::move(par1));
    params.push_back(std::move(par2));
    Function::setParam(std::move(params));
}

void
ExtSwapFn::setParam(std::vector<Parameter> &&  value)
{
    ExtSwapFn::setParam(value);
}

void
ExtSwapFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    if (value)  setClassName(value->getClassName());
}

std::string
ExtSwapFn::autoCode() const
{
    std::string  res;
    std::string const  tab1(getDefTab());

    res += tab1 + "if (&" + getLhs() + " == &" + getRhs() + ") return true;\n";
    res += tab1 + "return " + getLhs() + ".swap(" + getRhs() + ");\n";
    return res;
}

void
ExtSwapFn::init()
{
    setBaseType(Etype::eExtSwapFn);

    setAutoSource(true);
    setNoexcept(true);
    ExtSwapFn::setFunctionName("swap");
    setReturnType("bool");

    ExtSwapFn::setParam({});
}

std::string
ExtSwapFn::getClassName() const
{
    return m_className;
}

void
ExtSwapFn::setClassName(const std::string &  value)
{
    m_className = value;
    ExtSwapFn::setParam({});
}

void
ExtSwapFn::setClassName(std::string &&  value)
{
    m_className = std::move(value);
    ExtSwapFn::setParam({});
}

bool
ExtSwapFn::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const ExtSwapFn &  rhs = dynamic_cast<const ExtSwapFn &>(value);

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
ExtSwapFn::less(const EObject &  value) const
{
    if (this->Function::less(value)) return true;
    if (!(this->Function::equal(value))) return false;

    try {
        const ExtSwapFn &  rhs = dynamic_cast<const ExtSwapFn &>(value);

        if (m_className < rhs.m_className) return true;
        if (rhs.m_className < m_className) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
ExtSwapFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    xu::append(res, xu::toString(m_className));

    return res;
}

bool
ExtSwapFn::deserialize(const char *  data,
                       const size_t  size)
{
    ExtSwapFn  me;
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
ExtSwapFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ExtSwapFn &  rhs = dynamic_cast<ExtSwapFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;
        swap(m_className, rhs.m_className);

        result = true;
    }
    return result;
}

}
