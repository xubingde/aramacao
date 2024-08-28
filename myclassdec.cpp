#include <cstring>
#include <typeinfo>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "myclassdec.h"
#include "tpl.h"
#include "myclass.h"
#include "module.h"

namespace xu {

MyClassDec::MyClassDec():
        EObject(),
        m_parentClassPtr(nullptr),
        m_className("MyClass1")
{
    setTreeLabel("CD  " + m_className);
    setBaseType(Etype::eClassDeclaration);
}

MyClassDec::MyClassDec(const MyClassDec &  other):
        EObject(other),
        m_parentClassPtr(other.m_parentClassPtr),
        m_className(other.m_className)
{
}

MyClassDec::MyClassDec(MyClassDec &&  other) noexcept:
        EObject(std::move(other)),
        m_parentClassPtr(std::move(other.m_parentClassPtr)),
        m_className(std::move(other.m_className))
{
    other.m_parentClassPtr = nullptr;
}

MyClassDec::~MyClassDec() noexcept
{
}

MyClassDec &
MyClassDec::operator=(const MyClassDec &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_parentClassPtr = other.m_parentClassPtr;
    m_className = other.m_className;

    return *this;
}

MyClassDec &
MyClassDec::operator=(MyClassDec &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_parentClassPtr = std::move(other.m_parentClassPtr);
    m_className = std::move(other.m_className);

    other.m_parentClassPtr = nullptr;

    return *this;
}

std::string
MyClassDec::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    if (m_parentClassPtr) {
        res += m_parentClassPtr->getBeforeDcl();

        if (m_parentClassPtr->isTemplate()) {
            res += tabStr + "template <";
            std::vector<Tpl> const  tplParam = m_parentClassPtr->getClassTparam();
            size_t const  ctpSize = tplParam.size();
            for (size_t  i = 0; i < ctpSize; ++i) {
                res += tplParam[i].getTypename() + " " + tplParam[i].getTName();
                if (tplParam[i].getDefalutValue().size() > 0) {
                    res += " = " + tplParam[i].getDefalutValue();
                }
                if (i != tplParam.size() - 1) {
                    res += ", ";
                }
            }
            res += ">\n";
        }

        res += tabStr + "class ";
        if (m_parentClassPtr->getAttribute().size() > 0) {
            res += m_parentClassPtr->getAttribute() + " ";
        }
        res += m_parentClassPtr->getClassName() + ";\n";
        res += m_parentClassPtr->getBehindDcl();
    } else {
        res += tabStr + "class " + m_className + ";\n";
    }

    return res;
}

MyClass *
MyClassDec::getParentClassPtr() const
{
    return m_parentClassPtr;
}

void
MyClassDec::setParentClassPtr(MyClass *  value)
{
    m_parentClassPtr = value;
}

std::string
MyClassDec::getClassName() const
{
    return m_className;
}

void
MyClassDec::setClassName(const std::string &  value)
{
    m_className = xu::trim(value);
    if (!xu::checkReg(m_className)) {
        m_className = "MyClass1";
    }
    m_className[0] = xu::toupperS(m_className[0]);
    setTreeLabel("CD  " + m_className);
}

bool
MyClassDec::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const MyClassDec &  rhs = dynamic_cast<const MyClassDec &>(value);

        result = this->EObject::equal(value);
        if (!result) return result;

        result = ( m_className == rhs.m_className );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
MyClassDec::less(const EObject &  value) const
{
    if (this->EObject::less(value)) return true;
    if (!(this->EObject::equal(value))) return false;

    try {
        const MyClassDec &  rhs = dynamic_cast<const MyClassDec &>(value);

        if (m_className < rhs.m_className) return true;
        if (rhs.m_className < m_className) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
MyClassDec::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_className));

    return res;
}

bool
MyClassDec::deserialize(const char *  data,
                        const size_t  size)
{
    MyClassDec  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 1) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_className, vi[1]))  err.push_back({1});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
        m_parentClassPtr = nullptr;
    }

    return result;
}

bool
MyClassDec::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        MyClassDec &  rhs = dynamic_cast<MyClassDec &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_parentClassPtr, rhs.m_parentClassPtr);
        swap(m_className, rhs.m_className);

        result = true;
    }
    return result;
}

}
