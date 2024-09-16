#include <cstring>
#include <typeinfo>
#include "publiclabel.h"
#include "icode.h"
#include "fmt.h"

namespace xu {

PublicLabel::PublicLabel():
        EObject(),
        m_before(),
        m_behind()
{
    setTreeLabel("L   public :");
    setBaseType(Etype::ePublicLabel);
}

PublicLabel::PublicLabel(const PublicLabel &  other):
        EObject(other),
        m_before(other.m_before),
        m_behind(other.m_behind)
{
}

PublicLabel::PublicLabel(PublicLabel &&  other) noexcept:
        EObject(std::move(other)),
        m_before(std::move(other.m_before)),
        m_behind(std::move(other.m_behind))
{
}

PublicLabel::~PublicLabel() noexcept
{
}

PublicLabel &
PublicLabel::operator=(const PublicLabel &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_before = other.m_before;
    m_behind = other.m_behind;

    return *this;
}

PublicLabel &
PublicLabel::operator=(PublicLabel &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_before = std::move(other.m_before);
    m_behind = std::move(other.m_behind);

    return *this;
}

std::string
PublicLabel::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res = "\n" + m_before;

    res += tabStr + "public :\n" + m_behind;
    return res;
}

std::string
PublicLabel::getBefore() const
{
    return m_before;
}

void
PublicLabel::setBefore(const std::string &  value)
{
    m_before = value;
    xu::procCode(m_before);
}

void
PublicLabel::setBefore(std::string &&  value)
{
    m_before = std::move(value);
    xu::procCode(m_before);
}

std::string
PublicLabel::getBehind() const
{
    return m_behind;
}

void
PublicLabel::setBehind(const std::string &  value)
{
    m_behind = value;
    xu::procCode(m_behind);
}

void
PublicLabel::setBehind(std::string &&  value)
{
    m_behind = std::move(value);
    xu::procCode(m_behind);
}

bool
PublicLabel::equal(const EObject &  value) const
{
    return this->EObject::equal(value);
}

bool
PublicLabel::less(const EObject &  value) const
{
    return this->EObject::less(value);
}

std::string
PublicLabel::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_before));
    xu::append(res, xu::toString(m_behind));

    return res;
}

bool
PublicLabel::deserialize(const char *  data,
                         const size_t  size)
{
    PublicLabel  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 2) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

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
PublicLabel::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        PublicLabel &  rhs = dynamic_cast<PublicLabel &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_before, rhs.m_before);
        swap(m_behind, rhs.m_behind);

        result = true;
    }
    return result;
}

}
