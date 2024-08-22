#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "eqfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

EqFn::EqFn():
        Function(),
        m_className()
{
    init();
}

EqFn::EqFn(const EqFn &  other):
        Function(other),
        m_className(other.m_className)
{
}

EqFn::EqFn(EqFn &&  other) noexcept:
        Function(std::move(other)),
        m_className(std::move(other.m_className))
{
}

EqFn::EqFn(std::string const &  classname,
           MyClass *  parent):
        Function(parent),
        m_className(classname)
{
    init();
}

EqFn::~EqFn() noexcept
{
}

EqFn &
EqFn::operator=(const EqFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    m_className = other.m_className;

    return *this;
}

EqFn &
EqFn::operator=(EqFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    m_className = std::move(other.m_className);

    return *this;
}

void
EqFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
EqFn::setParam(std::vector<Parameter> const &)
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
EqFn::setParam(std::vector<Parameter> &&  value)
{
    EqFn::setParam(value);
}

void
EqFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    if (value)  setClassName(value->getClassName());
}

std::string
EqFn::autoCode() const
{
    std::string  res;
    std::string const  tab1(getDefTab());

    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        ClassType  ct = parentPtr->getClasstype();
        if (ct == ClassType::cppFinal) {
            res = parentPtr->toFCodeEq();
        } else if (ct == ClassType::cppBase) {
            std::string const  lhs = getLhs();
            std::string const  rhs = getRhs();
            res += tab1 + "if (&" + lhs + " == &" + rhs + ") return true;\n";
            res += tab1 + "return " + lhs + ".equal(" + rhs + ") && " +
                    rhs + ".equal(" + lhs + ");\n";
        }
    }

    return res;
}

void
EqFn::init()
{
    setBaseType(Etype::eEqFn);

    setAutoSource(true);
    EqFn::setFunctionName("operator==");
    setReturnType("bool");
    EqFn::setParam({});
    EqFn::setParentClassPtr(getParentClassPtr());
    setFriendClassName({m_className});
}

std::string
EqFn::getClassName() const
{
    return m_className;
}

void
EqFn::setClassName(const std::string &  value)
{
    m_className = value;
    setFriendClassName({m_className});
    setParam({});
}

void
EqFn::setClassName(std::string &&  value)
{
    m_className = std::move(value);
    setFriendClassName({m_className});
    EqFn::setParam({});
}

bool
EqFn::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const EqFn &  rhs = dynamic_cast<const EqFn &>(value);

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
EqFn::less(const EObject &  value) const
{
    if (this->Function::less(value)) return true;
    if (!(this->Function::equal(value))) return false;

    try {
        const EqFn &  rhs = dynamic_cast<const EqFn &>(value);

        if (m_className < rhs.m_className) return true;
        if (rhs.m_className < m_className) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
EqFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    xu::append(res, xu::toString(m_className));

    return res;
}

bool
EqFn::deserialize(const char *  data,
                  const size_t  size)
{
    EqFn  me;
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
EqFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        EqFn &  rhs = dynamic_cast<EqFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;
        swap(m_className, rhs.m_className);

        result = true;
    }
    return result;
}

}
