#include <cstring>
#include <typeinfo>
#include "icode.h"
#include "fmt.h"
#include "protectedlabel.h"

namespace xu {

ProtectedLabel::ProtectedLabel():
        EObject(),
        m_before(),
        m_behind()
{
    setTreeLabel("L   protected:");
    setBaseType(Etype::eProtectedLabel);
}

ProtectedLabel::ProtectedLabel(const ProtectedLabel &  other):
        EObject(other),
        m_before(other.m_before),
        m_behind(other.m_behind)
{
}

ProtectedLabel::ProtectedLabel(ProtectedLabel &&  other) noexcept:
        EObject(std::move(other)),
        m_before(std::move(other.m_before)),
        m_behind(std::move(other.m_behind))
{
}

ProtectedLabel::~ProtectedLabel() noexcept
{
}

ProtectedLabel &
ProtectedLabel::operator=(const ProtectedLabel &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_before = other.m_before;
    m_behind = other.m_behind;

    return *this;
}

ProtectedLabel &
ProtectedLabel::operator=(ProtectedLabel &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_before = std::move(other.m_before);
    m_behind = std::move(other.m_behind);

    return *this;
}

std::string
ProtectedLabel::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res = "\n" + m_before;

    res += tabStr + "protected:\n" + m_behind;
    return res;
}

std::string
ProtectedLabel::getBefore() const
{
    return m_before;
}

void
ProtectedLabel::setBefore(const std::string &  value)
{
    m_before = value;
    xu::procCode(m_before);
}

void
ProtectedLabel::setBefore(std::string &&  value)
{
    m_before = std::move(value);
    xu::procCode(m_before);
}

std::string
ProtectedLabel::getBehind() const
{
    return m_behind;
}

void
ProtectedLabel::setBehind(const std::string &  value)
{
    m_behind = value;
    xu::procCode(m_behind);
}

void
ProtectedLabel::setBehind(std::string &&  value)
{
    m_behind = std::move(value);
    xu::procCode(m_behind);
}

bool
ProtectedLabel::equal(const EObject &  value) const
{
    return this->EObject::equal(value);
}

bool
ProtectedLabel::less(const EObject &  value) const
{
    return this->EObject::less(value);
}

std::string
ProtectedLabel::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_before));
    xu::append(res, xu::toString(m_behind));

    return res;
}

bool
ProtectedLabel::deserialize(const char *  data,
                            const size_t  size)
{
    ProtectedLabel  me;
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
ProtectedLabel::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ProtectedLabel &  rhs = dynamic_cast<ProtectedLabel &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_before, rhs.m_before);
        swap(m_behind, rhs.m_behind);

        result = true;
    }
    return result;
}

}
