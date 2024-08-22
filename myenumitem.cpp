#include <cstring>
#include "myenumitem.h"
#include "fmt.h"
#include "icode.h"

namespace xu {

MyEnumItem::MyEnumItem():
        m_name(),
        m_defalutValue(),
        m_docment(),
        m_before(),
        m_behind()
{
}

MyEnumItem::MyEnumItem(const MyEnumItem &  other):
        m_name(other.m_name),
        m_defalutValue(other.m_defalutValue),
        m_docment(other.m_docment),
        m_before(other.m_before),
        m_behind(other.m_behind)
{
}

MyEnumItem::MyEnumItem(MyEnumItem &&  other) noexcept:
        m_name(std::move(other.m_name)),
        m_defalutValue(std::move(other.m_defalutValue)),
        m_docment(std::move(other.m_docment)),
        m_before(std::move(other.m_before)),
        m_behind(std::move(other.m_behind))
{
}

MyEnumItem::~MyEnumItem() noexcept
{
}

MyEnumItem &
MyEnumItem::operator=(const MyEnumItem &  other)
{
    if (this == &other) return *this;

    m_name = other.m_name;
    m_defalutValue = other.m_defalutValue;
    m_docment = other.m_docment;
    m_before = other.m_before;
    m_behind = other.m_behind;

    return *this;
}

MyEnumItem &
MyEnumItem::operator=(MyEnumItem &&  other) noexcept
{
    if (this == &other) return *this;

    m_name = std::move(other.m_name);
    m_defalutValue = std::move(other.m_defalutValue);
    m_docment = std::move(other.m_docment);
    m_before = std::move(other.m_before);
    m_behind = std::move(other.m_behind);

    return *this;
}

std::string
MyEnumItem::toHBlock(bool const  hasComma,
                     std::string const &  parentTab /* = std::string() */,
                     std::string const &  tabStr /* = std::string("    ") */) const
{
    std::string  res = m_before;

    res += parentTab + tabStr + m_name;
    if (m_defalutValue.size() > 0) {
        res += " = " + m_defalutValue;
    }
    if (hasComma) {
        res += ",";
    }
    res += "\n";
    res += m_behind;

    return res;
}

std::string
MyEnumItem::getName() const
{
    return m_name;
}

void
MyEnumItem::setName(const std::string &  value)
{
    m_name = xu::trim(value);
    if (!xu::checkReg(m_name)) {
        m_name = "item1";
    }
}

std::string
MyEnumItem::getDefalutValue() const
{
    return m_defalutValue;
}

void
MyEnumItem::setDefalutValue(const std::string &  value)
{
    m_defalutValue = xu::trim(value);
}

std::string
MyEnumItem::getDocment() const
{
    return m_docment;
}

void
MyEnumItem::setDocment(const std::string &  value)
{
    m_docment = value;
}

void
MyEnumItem::setDocment(std::string &&  value)
{
    m_docment = std::move(value);
}

std::string
MyEnumItem::getBefore() const
{
    return m_before;
}

void
MyEnumItem::setBefore(const std::string &  value)
{
    m_before = value;
    xu::procCode(m_before);
}

void
MyEnumItem::setBefore(std::string &&  value)
{
    m_before = std::move(value);
    xu::procCode(m_before);
}

std::string
MyEnumItem::getBehind() const
{
    return m_behind;
}

void
MyEnumItem::setBehind(const std::string &  value)
{
    m_behind = value;
    xu::procCode(m_behind);
}

void
MyEnumItem::setBehind(std::string &&  value)
{
    m_behind = std::move(value);
    xu::procCode(m_behind);
}

bool
operator==(const MyEnumItem &  lhs,
           const MyEnumItem &  rhs)
{
    if (&lhs == &rhs) return true;
    bool  result = false;

    result = ( lhs.m_name == rhs.m_name );
    if (!result) return result;

    result = ( lhs.m_defalutValue == rhs.m_defalutValue );
    if (!result) return result;

    result = ( lhs.m_docment == rhs.m_docment );
    if (!result) return result;

    result = ( lhs.m_before == rhs.m_before );
    if (!result) return result;

    result = ( lhs.m_behind == rhs.m_behind );
    if (!result) return result;

    return result;
}

bool
operator!=(const MyEnumItem &  lhs,
           const MyEnumItem &  rhs)
{
    return !(lhs == rhs);
}

bool
operator<(const MyEnumItem &  lhs,
          const MyEnumItem &  rhs)
{
    if (&lhs == &rhs) return false;

    if (lhs.m_name < rhs.m_name) return true;
    if (rhs.m_name < lhs.m_name) return false;

    if (lhs.m_defalutValue < rhs.m_defalutValue) return true;
    if (rhs.m_defalutValue < lhs.m_defalutValue) return false;

    if (lhs.m_docment < rhs.m_docment) return true;
    if (rhs.m_docment < lhs.m_docment) return false;

    if (lhs.m_before < rhs.m_before) return true;
    if (rhs.m_before < lhs.m_before) return false;

    if (lhs.m_behind < rhs.m_behind) return true;
    if (rhs.m_behind < lhs.m_behind) return false;

    return false;
}

bool
operator<=(const MyEnumItem &  lhs,
           const MyEnumItem &  rhs)
{
    return !(lhs > rhs);
}

bool
operator>(const MyEnumItem &  lhs,
          const MyEnumItem &  rhs)
{
    return rhs < lhs;
}

bool
operator>=(const MyEnumItem &  lhs,
           const MyEnumItem &  rhs)
{
    return !(lhs < rhs);
}

std::string
MyEnumItem::toString() const
{
    std::string  res;

    xu::append(res, xu::toString(m_name));
    xu::append(res, xu::toString(m_defalutValue));
    xu::append(res, xu::toString(m_docment));
    xu::append(res, xu::toString(m_before));
    xu::append(res, xu::toString(m_behind));

    return res;
}

bool
MyEnumItem::fromString(const char *  data,
                       const size_t  size)
{
    MyEnumItem  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 4) {
        if (!xu::fromString(me.m_name, vi[0]))  err.push_back({0});
        if (!xu::fromString(me.m_defalutValue, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_docment, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_before, vi[3]))  err.push_back({3});
        if (!xu::fromString(me.m_behind, vi[4]))  err.push_back({4});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
fromString(MyEnumItem &  value,
           const char *  data,
           const size_t  size)
{
    return value.fromString(data, size);
}

void
swap(MyEnumItem &  lhs,
     MyEnumItem &  rhs) noexcept
{
    lhs.swap(rhs);
}

void
MyEnumItem::swap(MyEnumItem &  value) noexcept
{
    if (this == &value) return;
    using std::swap;
    swap(m_name, value.m_name);
    swap(m_defalutValue, value.m_defalutValue);
    swap(m_docment, value.m_docment);
    swap(m_before, value.m_before);
    swap(m_behind, value.m_behind);
}

}
