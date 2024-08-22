#include <cstring>
#include <typeinfo>
#include "label.h"
#include "icode.h"
#include "fmt.h"

namespace xu {

Label::Label():
        EObject(),
        m_labelValue(),
        m_before(),
        m_behind()
{
    setTreeLabel("L   " + m_labelValue);
    setBaseType(Etype::eLabel);
}

Label::Label(const Label &  other):
        EObject(other),
        m_labelValue(other.m_labelValue),
        m_before(other.m_before),
        m_behind(other.m_behind)
{
}

Label::Label(Label &&  other) noexcept:
        EObject(std::move(other)),
        m_labelValue(std::move(other.m_labelValue)),
        m_before(std::move(other.m_before)),
        m_behind(std::move(other.m_behind))
{
}

Label::~Label() noexcept
{
}

Label &
Label::operator=(const Label &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_labelValue = other.m_labelValue;
    m_before = other.m_before;
    m_behind = other.m_behind;

    return *this;
}

Label &
Label::operator=(Label &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_labelValue = std::move(other.m_labelValue);
    m_before = std::move(other.m_before);
    m_behind = std::move(other.m_behind);

    return *this;
}

std::string
Label::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res = "\n" + m_before;

    res += tabStr + m_labelValue;
    size_t const  size = res.size();
    if (size > 0 && res[size - 1] != ':') {
        res += ":";
    }
    if (res.size() > 0)  res += "\n";
    res += m_behind;

    return res;
}

std::string
Label::getLabelValue() const
{
    return m_labelValue;
}

void
Label::setLabelValue(const std::string &  value)
{
    m_labelValue = xu::trim(value);
    std::string  treelabel("L   " + m_labelValue);

    size_t const  size = treelabel.size();
    if (treelabel[size - 1] != ':') {
        treelabel.push_back(':');
    }
    setTreeLabel(std::move(treelabel));

}

std::string
Label::getBefore() const
{
    return m_before;
}

void
Label::setBefore(const std::string &  value)
{
    m_before = value;
    xu::procCode(m_before);
}

void
Label::setBefore(std::string &&  value)
{
    m_before = std::move(value);
    xu::procCode(m_before);
}

std::string
Label::getBehind() const
{
    return m_behind;
}

void
Label::setBehind(const std::string &  value)
{
    m_behind = value;
    xu::procCode(m_behind);
}

void
Label::setBehind(std::string &&  value)
{
    m_behind = std::move(value);
    xu::procCode(m_behind);
}

bool
Label::equal(const EObject &  value) const
{
    return this->EObject::equal(value);
}

bool
Label::less(const EObject &  value) const
{
    return this->EObject::less(value);
}

std::string
Label::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_labelValue));
    xu::append(res, xu::toString(m_before));
    xu::append(res, xu::toString(m_behind));

    return res;
}

bool
Label::deserialize(const char *  data,
                   const size_t  size)
{
    Label  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 3) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_labelValue, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_before, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_behind, vi[3]))  err.push_back({3});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
Label::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        Label &  rhs = dynamic_cast<Label &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_labelValue, rhs.m_labelValue);
        swap(m_before, rhs.m_before);
        swap(m_behind, rhs.m_behind);

        result = true;
    }
    return result;
}

}
