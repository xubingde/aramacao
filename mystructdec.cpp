#include <cstring>
#include <typeinfo>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "mystructdec.h"
#include "mystruct.h"

namespace xu {

MyStructDec::MyStructDec():
        EObject(),
        m_structName("Struct1"),
        m_parentStructPtr(nullptr)
{
    setTreeLabel("SD  " + m_structName);
    setBaseType(Etype::eStructDeclaration);
}

MyStructDec::MyStructDec(const MyStructDec &  other):
        EObject(other),
        m_structName(other.m_structName),
        m_parentStructPtr(other.m_parentStructPtr)
{
}

MyStructDec::MyStructDec(MyStructDec &&  other) noexcept:
        EObject(std::move(other)),
        m_structName(std::move(other.m_structName)),
        m_parentStructPtr(std::move(other.m_parentStructPtr))
{
    other.m_parentStructPtr = nullptr;
}

MyStructDec::~MyStructDec() noexcept
{
}

MyStructDec &
MyStructDec::operator=(const MyStructDec &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_structName = other.m_structName;
    m_parentStructPtr = other.m_parentStructPtr;

    return *this;
}

MyStructDec &
MyStructDec::operator=(MyStructDec &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_structName = std::move(other.m_structName);
    m_parentStructPtr = std::move(other.m_parentStructPtr);

    other.m_parentStructPtr = nullptr;

    return *this;
}

std::string
MyStructDec::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    if (m_parentStructPtr) {
        res += m_parentStructPtr->getBeforeDcl();
        res += tabStr + "struct ";
        if (m_parentStructPtr->getAttribute().size() > 0) {
            res += m_parentStructPtr->getAttribute() + " ";
        }
        res += m_parentStructPtr->getName() + ";\n";
        res += m_parentStructPtr->getBehindDcl();
    } else {
        res += tabStr + "struct " + m_structName + ";\n";
    }

    return res;
}

std::string
MyStructDec::getStructName() const
{
    return m_structName;
}

void
MyStructDec::setStructName(const std::string &  value)
{
    m_structName = xu::trim(value);
    if (!xu::checkReg(m_structName)) {
        m_structName = "Struct1";
    }
    m_structName[0] = xu::toupperS(m_structName[0]);

    setTreeLabel("SD  " + m_structName);
}

MyStruct *
MyStructDec::getParentStructPtr() const
{
    return m_parentStructPtr;
}

void
MyStructDec::setParentStructPtr(MyStruct *  value)
{
    m_parentStructPtr = value;
    if (m_parentStructPtr) {
        m_structName = m_parentStructPtr->getName();
        setTreeLabel("SD  " + m_structName);
    }
}

bool
MyStructDec::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const MyStructDec &  rhs = dynamic_cast<const MyStructDec &>(value);

        result = this->EObject::equal(value);
        if (!result) return result;

        result = ( m_structName == rhs.m_structName );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
MyStructDec::less(const EObject &  value) const
{
    if (this->EObject::less(value)) return true;
    if (!(this->EObject::equal(value))) return false;

    try {
        const MyStructDec &  rhs = dynamic_cast<const MyStructDec &>(value);

        if (m_structName < rhs.m_structName) return true;
        if (rhs.m_structName < m_structName) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
MyStructDec::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_structName));

    return res;
}

bool
MyStructDec::deserialize(const char *  data,
                         const size_t  size)
{
    MyStructDec  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 1) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_structName, vi[1]))  err.push_back({1});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }
    m_parentStructPtr = nullptr;

    return result;
}

bool
MyStructDec::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        MyStructDec &  rhs = dynamic_cast<MyStructDec &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_structName, rhs.m_structName);
        swap(m_parentStructPtr, rhs.m_parentStructPtr);

        result = true;
    }
    return result;
}

}
