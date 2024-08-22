#include <cstring>
#include "tpl.h"
#include "fmt.h"
#include "icode.h"

namespace xu {

Tpl::Tpl():
        m_typename("typename"),
        m_TName(),
        m_docment(),
        m_defalutValue(),
        m_friendTypeName()
{
}

Tpl::Tpl(const Tpl &  other):
        m_typename(other.m_typename),
        m_TName(other.m_TName),
        m_docment(other.m_docment),
        m_defalutValue(other.m_defalutValue),
        m_friendTypeName(other.m_friendTypeName)
{
}

Tpl::Tpl(Tpl &&  other) noexcept:
        m_typename(std::move(other.m_typename)),
        m_TName(std::move(other.m_TName)),
        m_docment(std::move(other.m_docment)),
        m_defalutValue(std::move(other.m_defalutValue)),
        m_friendTypeName(std::move(other.m_friendTypeName))
{
}

Tpl::~Tpl() noexcept
{
}

Tpl &
Tpl::operator=(const Tpl &  other)
{
    if (this == &other) return *this;

    m_typename = other.m_typename;
    m_TName = other.m_TName;
    m_docment = other.m_docment;
    m_defalutValue = other.m_defalutValue;
    m_friendTypeName = other.m_friendTypeName;

    return *this;
}

Tpl &
Tpl::operator=(Tpl &&  other) noexcept
{
    if (this == &other) return *this;

    m_typename = std::move(other.m_typename);
    m_TName = std::move(other.m_TName);
    m_docment = std::move(other.m_docment);
    m_defalutValue = std::move(other.m_defalutValue);
    m_friendTypeName = std::move(other.m_friendTypeName);

    return *this;
}

std::string
Tpl::getTypename() const
{
    return m_typename;
}

void
Tpl::setTypename(const std::string &  value)
{
    m_typename = xu::trim(value);
    if (m_typename.size() == 0) {
        m_typename = "typename";
    }
}

std::string
Tpl::getTName() const
{
    return m_TName;
}

void
Tpl::setTName(const std::string &  value)
{
    m_TName = xu::trim(value);
}

std::string
Tpl::getDocment() const
{
    return m_docment;
}

void
Tpl::setDocment(const std::string &  value)
{
    m_docment = value;
}

void
Tpl::setDocment(std::string &&  value)
{
    m_docment = std::move(value);
}

std::string
Tpl::getDefalutValue() const
{
    return m_defalutValue;
}

void
Tpl::setDefalutValue(const std::string &  value)
{
    m_defalutValue = xu::trim(value);
}

std::string
Tpl::getFriendTypeName() const
{
    return m_friendTypeName;
}

void
Tpl::setFriendTypeName(const std::string &  value)
{
    m_friendTypeName = xu::trim(value);
}

bool
operator==(const Tpl &  lhs,
           const Tpl &  rhs)
{
    if (&lhs == &rhs) return true;
    bool  result = false;

    result = ( lhs.m_typename == rhs.m_typename );
    if (!result) return result;

    result = ( lhs.m_TName == rhs.m_TName );
    if (!result) return result;

    result = ( lhs.m_docment == rhs.m_docment );
    if (!result) return result;

    result = ( lhs.m_defalutValue == rhs.m_defalutValue );
    if (!result) return result;

    result = ( lhs.m_friendTypeName == rhs.m_friendTypeName );
    if (!result) return result;

    return result;
}

bool
operator!=(const Tpl &  lhs,
           const Tpl &  rhs)
{
    return !(lhs == rhs);
}

bool
operator<(const Tpl &  lhs,
          const Tpl &  rhs)
{
    if (&lhs == &rhs) return false;

    if (lhs.m_typename < rhs.m_typename) return true;
    if (rhs.m_typename < lhs.m_typename) return false;

    if (lhs.m_TName < rhs.m_TName) return true;
    if (rhs.m_TName < lhs.m_TName) return false;

    if (lhs.m_docment < rhs.m_docment) return true;
    if (rhs.m_docment < lhs.m_docment) return false;

    if (lhs.m_defalutValue < rhs.m_defalutValue) return true;
    if (rhs.m_defalutValue < lhs.m_defalutValue) return false;

    if (lhs.m_friendTypeName < rhs.m_friendTypeName) return true;
    if (rhs.m_friendTypeName < lhs.m_friendTypeName) return false;

    return false;
}

bool
operator<=(const Tpl &  lhs,
           const Tpl &  rhs)
{
    return !(lhs > rhs);
}

bool
operator>(const Tpl &  lhs,
          const Tpl &  rhs)
{
    return rhs < lhs;
}

bool
operator>=(const Tpl &  lhs,
           const Tpl &  rhs)
{
    return !(lhs < rhs);
}

std::string
Tpl::toString() const
{
    std::string  res;

    xu::append(res, xu::toString(m_typename));
    xu::append(res, xu::toString(m_TName));
    xu::append(res, xu::toString(m_docment));
    xu::append(res, xu::toString(m_defalutValue));
    xu::append(res, xu::toString(m_friendTypeName));

    return res;
}

bool
Tpl::fromString(const char *  data,
                const size_t  size)
{
    Tpl  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 4) {
        if (!xu::fromString(me.m_typename, vi[0]))  err.push_back({0});
        if (!xu::fromString(me.m_TName, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_docment, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_defalutValue, vi[3]))  err.push_back({3});
        if (!xu::fromString(me.m_friendTypeName, vi[4]))  err.push_back({4});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
fromString(Tpl &  value,
           const char *  data,
           const size_t  size)
{
    return value.fromString(data, size);
}

void
swap(Tpl &  lhs,
     Tpl &  rhs) noexcept
{
    lhs.swap(rhs);
}

void
Tpl::swap(Tpl &  value) noexcept
{
    if (this == &value) return;
    using std::swap;
    swap(m_typename, value.m_typename);
    swap(m_TName, value.m_TName);
    swap(m_docment, value.m_docment);
    swap(m_defalutValue, value.m_defalutValue);
    swap(m_friendTypeName, value.m_friendTypeName);
}

}
