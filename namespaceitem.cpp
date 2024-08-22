#include <cstring>
#include <typeinfo>
#include "namespaceitem.h"
#include "icode.h"
#include "fmt.h"

namespace xu {

NamespaceItem::NamespaceItem():
        m_namespaceValue(),
        m_hBeginBefor(),
        m_hBeginBehind(),
        m_hEndBefor(),
        m_hEndBehind(),
        m_cppBeginBefor(),
        m_cppBeginBehind(),
        m_cppEndBefor(),
        m_cppEndBehind()
{
}

NamespaceItem::NamespaceItem(const NamespaceItem &  other):
        m_namespaceValue(other.m_namespaceValue),
        m_hBeginBefor(other.m_hBeginBefor),
        m_hBeginBehind(other.m_hBeginBehind),
        m_hEndBefor(other.m_hEndBefor),
        m_hEndBehind(other.m_hEndBehind),
        m_cppBeginBefor(other.m_cppBeginBefor),
        m_cppBeginBehind(other.m_cppBeginBehind),
        m_cppEndBefor(other.m_cppEndBefor),
        m_cppEndBehind(other.m_cppEndBehind)
{
}

NamespaceItem::NamespaceItem(NamespaceItem &&  other) noexcept:
        m_namespaceValue(std::move(other.m_namespaceValue)),
        m_hBeginBefor(std::move(other.m_hBeginBefor)),
        m_hBeginBehind(std::move(other.m_hBeginBehind)),
        m_hEndBefor(std::move(other.m_hEndBefor)),
        m_hEndBehind(std::move(other.m_hEndBehind)),
        m_cppBeginBefor(std::move(other.m_cppBeginBefor)),
        m_cppBeginBehind(std::move(other.m_cppBeginBehind)),
        m_cppEndBefor(std::move(other.m_cppEndBefor)),
        m_cppEndBehind(std::move(other.m_cppEndBehind))
{
}

NamespaceItem::~NamespaceItem() noexcept
{
}

NamespaceItem &
NamespaceItem::operator=(const NamespaceItem &  other)
{
    if (this == &other) return *this;

    m_namespaceValue = other.m_namespaceValue;
    m_hBeginBefor = other.m_hBeginBefor;
    m_hBeginBehind = other.m_hBeginBehind;
    m_hEndBefor = other.m_hEndBefor;
    m_hEndBehind = other.m_hEndBehind;
    m_cppBeginBefor = other.m_cppBeginBefor;
    m_cppBeginBehind = other.m_cppBeginBehind;
    m_cppEndBefor = other.m_cppEndBefor;
    m_cppEndBehind = other.m_cppEndBehind;

    return *this;
}

NamespaceItem &
NamespaceItem::operator=(NamespaceItem &&  other) noexcept
{
    if (this == &other) return *this;

    m_namespaceValue = std::move(other.m_namespaceValue);
    m_hBeginBefor = std::move(other.m_hBeginBefor);
    m_hBeginBehind = std::move(other.m_hBeginBehind);
    m_hEndBefor = std::move(other.m_hEndBefor);
    m_hEndBehind = std::move(other.m_hEndBehind);
    m_cppBeginBefor = std::move(other.m_cppBeginBefor);
    m_cppBeginBehind = std::move(other.m_cppBeginBehind);
    m_cppEndBefor = std::move(other.m_cppEndBefor);
    m_cppEndBehind = std::move(other.m_cppEndBehind);

    return *this;
}

std::string
NamespaceItem::hCodeStart() const
{
    std::string  res(m_hBeginBefor + "namespace " +
                     m_namespaceValue + " {\n" + m_hBeginBehind);
    return res;
}

std::string
NamespaceItem::hCodeEnd() const
{
    std::string  res(m_hEndBefor + "}   // " + m_namespaceValue + "\n" + m_hEndBehind);
    return res;
}

std::string
NamespaceItem::cppCodeStart() const
{
    std::string  res(m_cppBeginBefor + "namespace " +
                     m_namespaceValue + " {\n" + m_cppBeginBehind);
    return res;
}

std::string
NamespaceItem::cppCodeEnd() const
{
    std::string  res(m_cppEndBefor + "}   // " + m_namespaceValue + "\n" + m_cppEndBehind);
    return res;
}

std::string
NamespaceItem::getNamespaceValue() const
{
    return m_namespaceValue;
}

void
NamespaceItem::setNamespaceValue(const std::string &  value)
{
    m_namespaceValue = value;
    if (!xu::checkReg(m_namespaceValue)) {
        m_namespaceValue = "xu";
    }
}

void
NamespaceItem::setNamespaceValue(std::string &&  value)
{
    m_namespaceValue = std::move(value);
    if (!xu::checkReg(m_namespaceValue)) {
        m_namespaceValue = "xu";
    }
}

std::string
NamespaceItem::getHBeginBefor() const
{
    return m_hBeginBefor;
}

void
NamespaceItem::setHBeginBefor(const std::string &  value)
{
    m_hBeginBefor = value;
    xu::procCode(m_hBeginBefor);
}

void
NamespaceItem::setHBeginBefor(std::string &&  value)
{
    m_hBeginBefor = std::move(value);
    xu::procCode(m_hBeginBefor);
}

std::string
NamespaceItem::getHBeginBehind() const
{
    return m_hBeginBehind;
}

void
NamespaceItem::setHBeginBehind(const std::string &  value)
{
    m_hBeginBehind = value;
    xu::procCode(m_hBeginBehind);
}

void
NamespaceItem::setHBeginBehind(std::string &&  value)
{
    m_hBeginBehind = std::move(value);
    xu::procCode(m_hBeginBehind);
}

std::string
NamespaceItem::getHEndBefor() const
{
    return m_hEndBefor;
}

void
NamespaceItem::setHEndBefor(const std::string &  value)
{
    m_hEndBefor = value;
    xu::procCode(m_hEndBefor);
}

void
NamespaceItem::setHEndBefor(std::string &&  value)
{
    m_hEndBefor = std::move(value);
    xu::procCode(m_hEndBefor);
}

std::string
NamespaceItem::getHEndBehind() const
{
    return m_hEndBehind;
}

void
NamespaceItem::setHEndBehind(const std::string &  value)
{
    m_hEndBehind = value;
    xu::procCode(m_hEndBehind);
}

void
NamespaceItem::setHEndBehind(std::string &&  value)
{
    m_hEndBehind = std::move(value);
    xu::procCode(m_hEndBehind);
}

std::string
NamespaceItem::getCppBeginBefor() const
{
    return m_cppBeginBefor;
}

void
NamespaceItem::setCppBeginBefor(const std::string &  value)
{
    m_cppBeginBefor = value;
    xu::procCode(m_cppBeginBefor);
}

void
NamespaceItem::setCppBeginBefor(std::string &&  value)
{
    m_cppBeginBefor = std::move(value);
    xu::procCode(m_cppBeginBefor);
}

std::string
NamespaceItem::getCppBeginBehind() const
{
    return m_cppBeginBehind;
}

void
NamespaceItem::setCppBeginBehind(const std::string &  value)
{
    m_cppBeginBehind = value;
    xu::procCode(m_cppBeginBehind);
}

void
NamespaceItem::setCppBeginBehind(std::string &&  value)
{
    m_cppBeginBehind = std::move(value);
    xu::procCode(m_cppBeginBehind);
}

std::string
NamespaceItem::getCppEndBefor() const
{
    return m_cppEndBefor;
}

void
NamespaceItem::setCppEndBefor(const std::string &  value)
{
    m_cppEndBefor = value;
    xu::procCode(m_cppEndBefor);
}

void
NamespaceItem::setCppEndBefor(std::string &&  value)
{
    m_cppEndBefor = std::move(value);
    xu::procCode(m_cppEndBefor);
}

std::string
NamespaceItem::getCppEndBehind() const
{
    return m_cppEndBehind;
}

void
NamespaceItem::setCppEndBehind(const std::string &  value)
{
    m_cppEndBehind = value;
    xu::procCode(m_cppEndBehind);
}

void
NamespaceItem::setCppEndBehind(std::string &&  value)
{
    m_cppEndBehind = std::move(value);
    xu::procCode(m_cppEndBehind);
}

bool
operator==(const NamespaceItem &  lhs,
           const NamespaceItem &  rhs)
{
    if (&lhs == &rhs) return true;
    bool  result = false;

    result = ( lhs.m_namespaceValue == rhs.m_namespaceValue );
    if (!result) return result;

    result = ( lhs.m_hBeginBefor == rhs.m_hBeginBefor );
    if (!result) return result;

    result = ( lhs.m_hBeginBehind == rhs.m_hBeginBehind );
    if (!result) return result;

    result = ( lhs.m_hEndBefor == rhs.m_hEndBefor );
    if (!result) return result;

    result = ( lhs.m_hEndBehind == rhs.m_hEndBehind );
    if (!result) return result;

    result = ( lhs.m_cppBeginBefor == rhs.m_cppBeginBefor );
    if (!result) return result;

    result = ( lhs.m_cppBeginBehind == rhs.m_cppBeginBehind );
    if (!result) return result;

    result = ( lhs.m_cppEndBefor == rhs.m_cppEndBefor );
    if (!result) return result;

    result = ( lhs.m_cppEndBehind == rhs.m_cppEndBehind );
    if (!result) return result;

    return result;
}

bool
operator!=(const NamespaceItem &  lhs,
           const NamespaceItem &  rhs)
{
    return !(lhs == rhs);
}

bool
operator<(const NamespaceItem &  lhs,
          const NamespaceItem &  rhs)
{
    if (&lhs == &rhs) return false;

    if (lhs.m_namespaceValue < rhs.m_namespaceValue) return true;
    if (rhs.m_namespaceValue < lhs.m_namespaceValue) return false;

    if (lhs.m_hBeginBefor < rhs.m_hBeginBefor) return true;
    if (rhs.m_hBeginBefor < lhs.m_hBeginBefor) return false;

    if (lhs.m_hBeginBehind < rhs.m_hBeginBehind) return true;
    if (rhs.m_hBeginBehind < lhs.m_hBeginBehind) return false;

    if (lhs.m_hEndBefor < rhs.m_hEndBefor) return true;
    if (rhs.m_hEndBefor < lhs.m_hEndBefor) return false;

    if (lhs.m_hEndBehind < rhs.m_hEndBehind) return true;
    if (rhs.m_hEndBehind < lhs.m_hEndBehind) return false;

    if (lhs.m_cppBeginBefor < rhs.m_cppBeginBefor) return true;
    if (rhs.m_cppBeginBefor < lhs.m_cppBeginBefor) return false;

    if (lhs.m_cppBeginBehind < rhs.m_cppBeginBehind) return true;
    if (rhs.m_cppBeginBehind < lhs.m_cppBeginBehind) return false;

    if (lhs.m_cppEndBefor < rhs.m_cppEndBefor) return true;
    if (rhs.m_cppEndBefor < lhs.m_cppEndBefor) return false;

    if (lhs.m_cppEndBehind < rhs.m_cppEndBehind) return true;
    if (rhs.m_cppEndBehind < lhs.m_cppEndBehind) return false;

    return false;
}

bool
operator<=(const NamespaceItem &  lhs,
           const NamespaceItem &  rhs)
{
    return !(lhs > rhs);
}

bool
operator>(const NamespaceItem &  lhs,
          const NamespaceItem &  rhs)
{
    return rhs < lhs;
}

bool
operator>=(const NamespaceItem &  lhs,
           const NamespaceItem &  rhs)
{
    return !(lhs < rhs);
}

std::string
NamespaceItem::toString() const
{
    std::string  res;

    xu::append(res, xu::toString(m_namespaceValue));
    xu::append(res, xu::toString(m_hBeginBefor));
    xu::append(res, xu::toString(m_hBeginBehind));
    xu::append(res, xu::toString(m_hEndBefor));
    xu::append(res, xu::toString(m_hEndBehind));
    xu::append(res, xu::toString(m_cppBeginBefor));
    xu::append(res, xu::toString(m_cppBeginBehind));
    xu::append(res, xu::toString(m_cppEndBefor));
    xu::append(res, xu::toString(m_cppEndBehind));

    return res;
}

bool
NamespaceItem::fromString(const char *  data,
                          const size_t  size)
{
    NamespaceItem  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 8) {
        if (!xu::fromString(me.m_namespaceValue, vi[0]))  err.push_back({0});
        if (!xu::fromString(me.m_hBeginBefor, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_hBeginBehind, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_hEndBefor, vi[3]))  err.push_back({3});
        if (!xu::fromString(me.m_hEndBehind, vi[4]))  err.push_back({4});
        if (!xu::fromString(me.m_cppBeginBefor, vi[5]))  err.push_back({5});
        if (!xu::fromString(me.m_cppBeginBehind, vi[6]))  err.push_back({6});
        if (!xu::fromString(me.m_cppEndBefor, vi[7]))  err.push_back({7});
        if (!xu::fromString(me.m_cppEndBehind, vi[8]))  err.push_back({8});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
fromString(NamespaceItem &  value,
           const char *  data,
           const size_t  size)
{
    return value.fromString(data, size);
}

void
swap(NamespaceItem &  lhs,
     NamespaceItem &  rhs) noexcept
{
    lhs.swap(rhs);
}

void
NamespaceItem::swap(NamespaceItem &  value) noexcept
{
    if (this == &value) return;
    using std::swap;
    swap(m_namespaceValue, value.m_namespaceValue);
    swap(m_hBeginBefor, value.m_hBeginBefor);
    swap(m_hBeginBehind, value.m_hBeginBehind);
    swap(m_hEndBefor, value.m_hEndBefor);
    swap(m_hEndBehind, value.m_hEndBehind);
    swap(m_cppBeginBefor, value.m_cppBeginBefor);
    swap(m_cppBeginBehind, value.m_cppBeginBehind);
    swap(m_cppEndBefor, value.m_cppEndBefor);
    swap(m_cppEndBehind, value.m_cppEndBehind);
}

}
