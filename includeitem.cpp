#include <cstring>
#include <typeinfo>
#include "includeitem.h"
#include "icode.h"
#include "fmt.h"

namespace xu {

IncludeItem::IncludeItem():
        m_includeValue("<string>"),
        m_before(),
        m_behind()
{
}

IncludeItem::IncludeItem(const IncludeItem &  other):
        m_includeValue(other.m_includeValue),
        m_before(other.m_before),
        m_behind(other.m_behind)
{
}

IncludeItem::IncludeItem(IncludeItem &&  other) noexcept:
        m_includeValue(std::move(other.m_includeValue)),
        m_before(std::move(other.m_before)),
        m_behind(std::move(other.m_behind))
{
}

IncludeItem::~IncludeItem() noexcept
{
}

IncludeItem &
IncludeItem::operator=(const IncludeItem &  other)
{
    if (this == &other) return *this;

    m_includeValue = other.m_includeValue;
    m_before = other.m_before;
    m_behind = other.m_behind;

    return *this;
}

IncludeItem &
IncludeItem::operator=(IncludeItem &&  other) noexcept
{
    if (this == &other) return *this;

    m_includeValue = std::move(other.m_includeValue);
    m_before = std::move(other.m_before);
    m_behind = std::move(other.m_behind);

    return *this;
}

std::string
IncludeItem::toHCode() const
{
    std::string  res(m_before + "#include " + m_includeValue + "\n" + m_behind);
    return res;
}

void
IncludeItem::procIncludeValue(std::string &  value)
{
    size_t const  size = value.size();
    if (size > 1) {
        if (!(value[0] == '<' || value[0] == '\"')) {
            value.insert(value.begin(), '\"');
        }
        if (value[size - 1] == '>' || value[size - 1] == '\"') {
            value.push_back('\"');
        }
    }
}

std::string
IncludeItem::getIncludeValue() const
{
    return m_includeValue;
}

void
IncludeItem::setIncludeValue(const std::string &  value)
{
    m_includeValue = value;
    xu::trim(m_includeValue);
    procIncludeValue(m_includeValue);
}

void
IncludeItem::setIncludeValue(std::string &&  value)
{
    m_includeValue = std::move(value);
    xu::trim(m_includeValue);
    procIncludeValue(m_includeValue);
}

std::string
IncludeItem::getBefore() const
{
    return m_before;
}

void
IncludeItem::setBefore(const std::string &  value)
{
    m_before = value;
    xu::procCode(m_before);
}

void
IncludeItem::setBefore(std::string &&  value)
{
    m_before = std::move(value);
    xu::procCode(m_before);
}

std::string
IncludeItem::getBehind() const
{
    return m_behind;
}

void
IncludeItem::setBehind(const std::string &  value)
{
    m_behind = value;
    xu::procCode(m_behind);
}

void
IncludeItem::setBehind(std::string &&  value)
{
    m_behind = std::move(value);
    xu::procCode(m_behind);
}

bool
operator==(const IncludeItem &  lhs,
           const IncludeItem &  rhs)
{
    if (&lhs == &rhs) return true;
    bool  result = false;

    result = ( lhs.m_includeValue == rhs.m_includeValue );
    if (!result) return result;

    result = ( lhs.m_before == rhs.m_before );
    if (!result) return result;

    result = ( lhs.m_behind == rhs.m_behind );
    if (!result) return result;

    return result;
}

bool
operator!=(const IncludeItem &  lhs,
           const IncludeItem &  rhs)
{
    return !(lhs == rhs);
}

bool
operator<(const IncludeItem &  lhs,
          const IncludeItem &  rhs)
{
    if (&lhs == &rhs) return false;

    if (lhs.m_includeValue < rhs.m_includeValue) return true;
    if (rhs.m_includeValue < lhs.m_includeValue) return false;

    if (lhs.m_before < rhs.m_before) return true;
    if (rhs.m_before < lhs.m_before) return false;

    if (lhs.m_behind < rhs.m_behind) return true;
    if (rhs.m_behind < lhs.m_behind) return false;

    return false;
}

bool
operator<=(const IncludeItem &  lhs,
           const IncludeItem &  rhs)
{
    return !(lhs > rhs);
}

bool
operator>(const IncludeItem &  lhs,
          const IncludeItem &  rhs)
{
    return rhs < lhs;
}

bool
operator>=(const IncludeItem &  lhs,
           const IncludeItem &  rhs)
{
    return !(lhs < rhs);
}

std::string
IncludeItem::toString() const
{
    std::string  res;

    xu::append(res, xu::toString(m_includeValue));
    xu::append(res, xu::toString(m_before));
    xu::append(res, xu::toString(m_behind));

    return res;
}

bool
IncludeItem::fromString(const char *  data,
                        const size_t  size)
{
    IncludeItem  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 2) {
        if (!xu::fromString(me.m_includeValue, vi[0]))  err.push_back({0});
        if (!xu::fromString(me.m_before, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_behind, vi[2]))  err.push_back({2});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
fromString(IncludeItem &  value,
           const char *  data,
           const size_t  size)
{
    return value.fromString(data, size);
}

void
swap(IncludeItem &  lhs,
     IncludeItem &  rhs) noexcept
{
    lhs.swap(rhs);
}

void
IncludeItem::swap(IncludeItem &  value) noexcept
{
    if (this == &value) return;
    using std::swap;
    swap(m_includeValue, value.m_includeValue);
    swap(m_before, value.m_before);
    swap(m_behind, value.m_behind);
}

}
