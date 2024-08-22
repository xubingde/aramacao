#include <cstring>
#include <typeinfo>
#include <vector>
#include <string_view>
#include "icode.h"
#include "fmt.h"
#include "basicblock.h"

namespace xu {

BasicBlock::BasicBlock():
        EObject(),
        m_sourceCode()
{
    setTreeLabel("B   BasicBlock");
    setBaseType(Etype::eBasicBlock);
}

BasicBlock::BasicBlock(const BasicBlock &  other):
        EObject(other),
        m_sourceCode(other.m_sourceCode)
{
}

BasicBlock::BasicBlock(BasicBlock &&  other) noexcept:
        EObject(std::move(other)),
        m_sourceCode(std::move(other.m_sourceCode))
{
}

BasicBlock::~BasicBlock() noexcept
{
}

BasicBlock &
BasicBlock::operator=(const BasicBlock &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_sourceCode = other.m_sourceCode;

    return *this;
}

BasicBlock &
BasicBlock::operator=(BasicBlock &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_sourceCode = std::move(other.m_sourceCode);

    return *this;
}

std::string
BasicBlock::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    if (tabStr.size() == 0) {
        res = m_sourceCode;
    } else {
        std::vector<std::string_view>  vecLine = xu::splitLine(m_sourceCode);
        for (const auto &  it: vecLine) {
            if (it.size() > 0) {
                res += tabStr + std::string(it) + "\n";
            } else {
                res += "\n";
            }
        }
    }

    return res;
}

std::string
BasicBlock::getSourceCode() const
{
    return m_sourceCode;
}

void
BasicBlock::setSourceCode(const std::string &  value)
{
    m_sourceCode = value;
    xu::procCode(m_sourceCode);
}

void
BasicBlock::setSourceCode(std::string &&  value)
{
    m_sourceCode = std::move(value);
    xu::procCode(m_sourceCode);
}

bool
BasicBlock::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const BasicBlock &  rhs = dynamic_cast<const BasicBlock &>(value);

        result = this->EObject::equal(value);
        if (!result) return result;

        result = ( m_sourceCode == rhs.m_sourceCode );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
BasicBlock::less(const EObject &  value) const
{
    if (this->EObject::less(value)) return true;
    if (!(this->EObject::equal(value))) return false;

    try {
        const BasicBlock &  rhs = dynamic_cast<const BasicBlock &>(value);

        if (m_sourceCode < rhs.m_sourceCode) return true;
        if (rhs.m_sourceCode < m_sourceCode) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
BasicBlock::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_sourceCode));

    return res;
}

bool
BasicBlock::deserialize(const char *  data,
                        const size_t  size)
{
    BasicBlock  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 1) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_sourceCode, vi[1]))  err.push_back({1});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
BasicBlock::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        BasicBlock &  rhs = dynamic_cast<BasicBlock &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_sourceCode, rhs.m_sourceCode);

        result = true;
    }
    return result;
}

}
