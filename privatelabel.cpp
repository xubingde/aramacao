#include <cstring>
#include <typeinfo>
#include "icode.h"
#include "fmt.h"
#include "privatelabel.h"

namespace xu {

PrivateLabel::PrivateLabel():
        EObject(),
        m_before(),
        m_behind()
{
    setTreeLabel("L   private:");
    setBaseType(Etype::ePrivateLabel);
}

PrivateLabel::PrivateLabel(const PrivateLabel &  other):
        EObject(other),
        m_before(other.m_before),
        m_behind(other.m_behind)
{
}

PrivateLabel::PrivateLabel(PrivateLabel &&  other) noexcept:
        EObject(std::move(other)),
        m_before(std::move(other.m_before)),
        m_behind(std::move(other.m_behind))
{
}

PrivateLabel::~PrivateLabel() noexcept
{
}

PrivateLabel &
PrivateLabel::operator=(const PrivateLabel &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_before = other.m_before;
    m_behind = other.m_behind;

    return *this;
}

PrivateLabel &
PrivateLabel::operator=(PrivateLabel &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_before = std::move(other.m_before);
    m_behind = std::move(other.m_behind);

    return *this;
}

std::string
PrivateLabel::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res = "\n" + m_before;

    res += tabStr + "private:\n" + m_behind;
    return res;
}

std::string
PrivateLabel::getBefore() const
{
    return m_before;
}

void
PrivateLabel::setBefore(const std::string &  value)
{
    m_before = value;
    xu::procCode(m_before);
}

void
PrivateLabel::setBefore(std::string &&  value)
{
    m_before = std::move(value);
    xu::procCode(m_before);
}

std::string
PrivateLabel::getBehind() const
{
    return m_behind;
}

void
PrivateLabel::setBehind(const std::string &  value)
{
    m_behind = value;
    xu::procCode(m_behind);
}

void
PrivateLabel::setBehind(std::string &&  value)
{
    m_behind = std::move(value);
    xu::procCode(m_behind);
}

bool
PrivateLabel::equal(const EObject &  value) const
{
    return this->EObject::equal(value);
}

bool
PrivateLabel::less(const EObject &  value) const
{
    return this->EObject::less(value);
}

std::string
PrivateLabel::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_before));
    xu::append(res, xu::toString(m_behind));

    return res;
}

bool
PrivateLabel::deserialize(const char *  data,
                          const size_t  size)
{
    PrivateLabel  me;
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
PrivateLabel::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        PrivateLabel &  rhs = dynamic_cast<PrivateLabel &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_before, rhs.m_before);
        swap(m_behind, rhs.m_behind);

        result = true;
    }
    return result;
}

}
