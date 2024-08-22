#include <cstring>
#include <typeinfo>
#include "myenum.h"
#include "icode.h"
#include "fmt.h"
#include "publictype.h"

namespace xu {

MyEnum::MyEnum():
        EObject(),
        m_name("E1"),
        m_docment(),
        m_type(),
        m_before(),
        m_behind(),
        m_item()
{
    setTreeLabel("E   " + m_name);
    setBaseType(Etype::eEnum);
}

MyEnum::MyEnum(const MyEnum &  other):
        EObject(other),
        m_name(other.m_name),
        m_docment(other.m_docment),
        m_type(other.m_type),
        m_before(other.m_before),
        m_behind(other.m_behind),
        m_item(other.m_item)
{
}

MyEnum::MyEnum(MyEnum &&  other) noexcept:
        EObject(std::move(other)),
        m_name(std::move(other.m_name)),
        m_docment(std::move(other.m_docment)),
        m_type(std::move(other.m_type)),
        m_before(std::move(other.m_before)),
        m_behind(std::move(other.m_behind)),
        m_item(std::move(other.m_item))
{
}

MyEnum::~MyEnum() noexcept
{
}

MyEnum &
MyEnum::operator=(const MyEnum &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_name = other.m_name;
    m_docment = other.m_docment;
    m_type = other.m_type;
    m_before = other.m_before;
    m_behind = other.m_behind;
    m_item = other.m_item;

    return *this;
}

MyEnum &
MyEnum::operator=(MyEnum &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_name = std::move(other.m_name);
    m_docment = std::move(other.m_docment);
    m_type = std::move(other.m_type);
    m_before = std::move(other.m_before);
    m_behind = std::move(other.m_behind);
    m_item = std::move(other.m_item);

    return *this;
}

std::string
MyEnum::toHBlock(std::string const &  parentTab /* = std::string() */) const
{
    std::string  res = "\n" + m_before;
    std::string const  tabStr(getDefTab());

    res += parentTab + "enum class " + m_name;
    if (m_type.size() > 0) {
        res += ": " + m_type;
    }
    res += " {\n";

    size_t const  size = m_item.size();
    for (size_t  i = 0; i < size; ++i) {
        if (i != size - 1) {
            res += m_item[i].toHBlock(true, parentTab, tabStr);
        } else {
            res += m_item[i].toHBlock(false, parentTab, tabStr);
        }
    }
    res += parentTab + "};\n";
    res += m_behind;

    return res;
}

std::string
MyEnum::getName() const
{
    return m_name;
}

void
MyEnum::setName(const std::string &  value)
{
    m_name = xu::trim(value);
    if (!xu::checkReg(m_name)) {
        m_name = "E1";
    }
    setTreeLabel("E   " + m_name);
}

std::string
MyEnum::getDocment() const
{
    return m_docment;
}

void
MyEnum::setDocment(const std::string &  value)
{
    m_docment = value;
}

void
MyEnum::setDocment(std::string &&  value)
{
    m_docment = std::move(value);
}

std::string
MyEnum::getType() const
{
    return m_type;
}

void
MyEnum::setType(const std::string &  value)
{
    m_type = xu::trim(value);
}

std::string
MyEnum::getBefore() const
{
    return m_before;
}

void
MyEnum::setBefore(const std::string &  value)
{
    m_before = value;
    xu::procCode(m_before);
}

void
MyEnum::setBefore(std::string &&  value)
{
    m_before = std::move(value);
    xu::procCode(m_before);
}

std::string
MyEnum::getBehind() const
{
    return m_behind;
}

void
MyEnum::setBehind(const std::string &  value)
{
    m_behind = value;
    xu::procCode(m_behind);
}

void
MyEnum::setBehind(std::string &&  value)
{
    m_behind = std::move(value);
    xu::procCode(m_behind);
}

std::vector<MyEnumItem>
MyEnum::getItem() const
{
    return m_item;
}

void
MyEnum::setItem(const std::vector<MyEnumItem> &  value)
{
    m_item = value;
}

void
MyEnum::setItem(std::vector<MyEnumItem> &&  value)
{
    m_item = std::move(value);
}

bool
MyEnum::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const MyEnum &  rhs = dynamic_cast<const MyEnum &>(value);

        result = this->EObject::equal(value);
        if (!result) return result;

        result = ( m_name == rhs.m_name );
        if (!result) return result;

        result = ( m_type == rhs.m_type );
        if (!result) return result;

        result = ( m_item == rhs.m_item );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
MyEnum::less(const EObject &  value) const
{
    if (this->EObject::less(value)) return true;
    if (!(this->EObject::equal(value))) return false;

    try {
        const MyEnum &  rhs = dynamic_cast<const MyEnum &>(value);

        if (m_name < rhs.m_name) return true;
        if (rhs.m_name < m_name) return false;

        if (m_type < rhs.m_type) return true;
        if (rhs.m_type < m_type) return false;

        if (m_item < rhs.m_item) return true;
        if (rhs.m_item < m_item) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
MyEnum::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_name));
    xu::append(res, xu::toString(m_docment));
    xu::append(res, xu::toString(m_type));
    xu::append(res, xu::toString(m_before));
    xu::append(res, xu::toString(m_behind));
    xu::append(res, xu::toString(m_item));

    return res;
}

bool
MyEnum::deserialize(const char *  data,
                    const size_t  size)
{
    MyEnum  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 6) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_name, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_docment, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_type, vi[3]))  err.push_back({3});
        if (!xu::fromString(me.m_before, vi[4]))  err.push_back({4});
        if (!xu::fromString(me.m_behind, vi[5]))  err.push_back({5});
        if (!xu::fromString(me.m_item, vi[6]))  err.push_back({6});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
MyEnum::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        MyEnum &  rhs = dynamic_cast<MyEnum &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_name, rhs.m_name);
        swap(m_docment, rhs.m_docment);
        swap(m_type, rhs.m_type);
        swap(m_before, rhs.m_before);
        swap(m_behind, rhs.m_behind);
        swap(m_item, rhs.m_item);

        result = true;
    }
    return result;
}

}
