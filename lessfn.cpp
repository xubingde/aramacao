#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "eqfn.h"
#include "lessfn.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

LessFn::LessFn():
        Function(),
        m_className()
{
    init();
}

LessFn::LessFn(const LessFn &  other):
        Function(other),
        m_className(other.m_className)
{
}

LessFn::LessFn(LessFn &&  other) noexcept:
        Function(std::move(other)),
        m_className(std::move(other.m_className))
{
}

LessFn::LessFn(std::string const &  classname,
               MyClass *  parent):
        Function(parent),
        m_className(classname)
{
    init();
}

LessFn::~LessFn() noexcept
{
}

LessFn &
LessFn::operator=(const LessFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    m_className = other.m_className;

    return *this;
}

LessFn &
LessFn::operator=(LessFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    m_className = std::move(other.m_className);

    return *this;
}

void
LessFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("FT  " + getFunctionName());
}

void
LessFn::setParam(std::vector<Parameter> const &)
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
LessFn::setParam(std::vector<Parameter> &&  value)
{
    LessFn::setParam(value);
}

void
LessFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    if (value)  setClassName(value->getClassName());
}

std::string
LessFn::autoCode() const
{
    std::string  res;
    std::string const  tab1(getDefTab());

    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        ClassType  ct = parentPtr->getClasstype();
        if (ct == ClassType::cppFinal) {
            res = parentPtr->toFCodeLess();
        } else if (ct == ClassType::cppBase) {
            std::string const  lhs = getLhs();
            std::string const  rhs = getRhs();
            res += tab1 + "if (&" + lhs + " == &" + rhs + ")  return false;\n";
            res += tab1 + "return " + lhs + ".less(" + rhs + ") && !(" +
                    rhs + ".less(" + lhs + ") && " + lhs + " != " + rhs + ");\n";
        }
    }

    return res;
}

void
LessFn::init()
{
    setBaseType(Etype::eLessFn);

    setAutoSource(true);
    LessFn::setFunctionName("operator<");
    setReturnType("bool");
    LessFn::setParam({});
    LessFn::setParentClassPtr(getParentClassPtr());
    setFriendClassName({m_className});
}

std::string
LessFn::getClassName() const
{
    return m_className;
}

void
LessFn::setClassName(const std::string &  value)
{
    m_className = value;
    setFriendClassName({m_className});
    LessFn::setParam({});
}

void
LessFn::setClassName(std::string &&  value)
{
    m_className = std::move(value);
    setFriendClassName({m_className});
    LessFn::setParam({});
}

bool
LessFn::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const LessFn &  rhs = dynamic_cast<const LessFn &>(value);

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
LessFn::less(const EObject &  value) const
{
    if (this->Function::less(value)) return true;
    if (!(this->Function::equal(value))) return false;

    try {
        const LessFn &  rhs = dynamic_cast<const LessFn &>(value);

        if (m_className < rhs.m_className) return true;
        if (rhs.m_className < m_className) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
LessFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    xu::append(res, xu::toString(m_className));

    return res;
}

bool
LessFn::deserialize(const char *  data,
                    const size_t  size)
{
    LessFn  me;
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
LessFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        LessFn &  rhs = dynamic_cast<LessFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;
        swap(m_className, rhs.m_className);

        result = true;
    }
    return result;
}

}
