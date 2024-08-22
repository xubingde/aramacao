#include <cstring>
#include <typeinfo>
#include "mytypedef.h"
#include "icode.h"
#include "fmt.h"

namespace xu {

MyTypedef::MyTypedef():
        EObject(),
        m_name(),
        m_type(),
        m_before(),
        m_behind(),
        m_docment(),
        m_templateItem(),
        m_template(false)
{
    setTreeLabel("T   " + m_name);
    setBaseType(Etype::eTypedef);
}

MyTypedef::MyTypedef(const MyTypedef &  other):
        EObject(other),
        m_name(other.m_name),
        m_type(other.m_type),
        m_before(other.m_before),
        m_behind(other.m_behind),
        m_docment(other.m_docment),
        m_templateItem(other.m_templateItem),
        m_template(other.m_template)
{
}

MyTypedef::MyTypedef(MyTypedef &&  other) noexcept:
        EObject(std::move(other)),
        m_name(std::move(other.m_name)),
        m_type(std::move(other.m_type)),
        m_before(std::move(other.m_before)),
        m_behind(std::move(other.m_behind)),
        m_docment(std::move(other.m_docment)),
        m_templateItem(std::move(other.m_templateItem)),
        m_template(std::move(other.m_template))
{
}

MyTypedef::~MyTypedef() noexcept
{
}

MyTypedef &
MyTypedef::operator=(const MyTypedef &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_name = other.m_name;
    m_type = other.m_type;
    m_before = other.m_before;
    m_behind = other.m_behind;
    m_docment = other.m_docment;
    m_templateItem = other.m_templateItem;
    m_template = other.m_template;

    return *this;
}

MyTypedef &
MyTypedef::operator=(MyTypedef &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_name = std::move(other.m_name);
    m_type = std::move(other.m_type);
    m_before = std::move(other.m_before);
    m_behind = std::move(other.m_behind);
    m_docment = std::move(other.m_docment);
    m_templateItem = std::move(other.m_templateItem);
    m_template = std::move(other.m_template);

    return *this;
}

std::string
MyTypedef::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res = m_before;

    if (m_template) {
        res += tabStr + "template <";
        for (size_t  i = 0; i < m_templateItem.size(); ++i) {
            res += m_templateItem[i].getTypename() + " " + m_templateItem[i].getTName();
            if (m_templateItem[i].getDefalutValue().size() > 0) {
                res += " = " + m_templateItem[i].getDefalutValue();
            }
            if (i != m_templateItem.size() - 1) {
                res += ", ";
            }
        }
        res += ">\n";
    }

    res += tabStr + "using  " + m_name + " = " + m_type + ";\n";
    res += m_behind;
    return res;
}

std::string
MyTypedef::getName() const
{
    return m_name;
}

void
MyTypedef::setName(const std::string &  value)
{
    m_name = xu::trim(value);
    if (!xu::checkReg(m_name)) {
        m_name = "";
    }
    setTreeLabel("T   " + m_name);
}

std::string
MyTypedef::getType() const
{
    return m_type;
}

void
MyTypedef::setType(const std::string &  value)
{
    m_type = xu::trim(value);
}

std::string
MyTypedef::getBefore() const
{
    return m_before;
}

void
MyTypedef::setBefore(const std::string &  value)
{
    m_before = value;
    xu::procCode(m_before);
}

void
MyTypedef::setBefore(std::string &&  value)
{
    m_before = std::move(value);
    xu::procCode(m_before);
}

std::string
MyTypedef::getBehind() const
{
    return m_behind;
}

void
MyTypedef::setBehind(const std::string &  value)
{
    m_behind = value;
    xu::procCode(m_behind);
}

void
MyTypedef::setBehind(std::string &&  value)
{
    m_behind = std::move(value);
    xu::procCode(m_behind);
}

std::string
MyTypedef::getDocment() const
{
    return m_docment;
}

void
MyTypedef::setDocment(const std::string &  value)
{
    m_docment = value;
}

void
MyTypedef::setDocment(std::string &&  value)
{
    m_docment = std::move(value);
}

std::vector<Tpl>
MyTypedef::getTemplateItem() const
{
    return m_templateItem;
}

void
MyTypedef::setTemplateItem(const std::vector<Tpl> &  value)
{
    m_templateItem = value;
}

void
MyTypedef::setTemplateItem(std::vector<Tpl> &&  value)
{
    m_templateItem = std::move(value);
}

bool
MyTypedef::isTemplate() const
{
    return m_template;
}

void
MyTypedef::setTemplate(const bool  value)
{
    m_template = value;
}

bool
MyTypedef::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const MyTypedef &  rhs = dynamic_cast<const MyTypedef &>(value);

        result = this->EObject::equal(value);
        if (!result) return result;

        result = ( m_name == rhs.m_name );
        if (!result) return result;

        result = ( m_type == rhs.m_type );
        if (!result) return result;

        result = ( m_before == rhs.m_before );
        if (!result) return result;

        result = ( m_behind == rhs.m_behind );
        if (!result) return result;

        result = ( m_docment == rhs.m_docment );
        if (!result) return result;

        result = ( m_templateItem == rhs.m_templateItem );
        if (!result) return result;

        result = ( m_template == rhs.m_template );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
MyTypedef::less(const EObject &  value) const
{
    if (this->EObject::less(value)) return true;
    if (!(this->EObject::equal(value))) return false;

    try {
        const MyTypedef &  rhs = dynamic_cast<const MyTypedef &>(value);

        if (m_name < rhs.m_name) return true;
        if (rhs.m_name < m_name) return false;

        if (m_type < rhs.m_type) return true;
        if (rhs.m_type < m_type) return false;

        if (m_before < rhs.m_before) return true;
        if (rhs.m_before < m_before) return false;

        if (m_behind < rhs.m_behind) return true;
        if (rhs.m_behind < m_behind) return false;

        if (m_docment < rhs.m_docment) return true;
        if (rhs.m_docment < m_docment) return false;

        if (m_templateItem < rhs.m_templateItem) return true;
        if (rhs.m_templateItem < m_templateItem) return false;

        if (m_template < rhs.m_template) return true;
        if (rhs.m_template < m_template) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
MyTypedef::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_name));
    xu::append(res, xu::toString(m_type));
    xu::append(res, xu::toString(m_before));
    xu::append(res, xu::toString(m_behind));
    xu::append(res, xu::toString(m_docment));
    xu::append(res, xu::toString(m_templateItem));
    xu::append(res, xu::toString(m_template));

    return res;
}

bool
MyTypedef::deserialize(const char *  data,
                       const size_t  size)
{
    MyTypedef  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 7) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_name, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_type, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_before, vi[3]))  err.push_back({3});
        if (!xu::fromString(me.m_behind, vi[4]))  err.push_back({4});
        if (!xu::fromString(me.m_docment, vi[5]))  err.push_back({5});
        if (!xu::fromString(me.m_templateItem, vi[6]))  err.push_back({6});
        if (!xu::fromString(me.m_template, vi[7]))  err.push_back({7});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
MyTypedef::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        MyTypedef &  rhs = dynamic_cast<MyTypedef &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_name, rhs.m_name);
        swap(m_type, rhs.m_type);
        swap(m_before, rhs.m_before);
        swap(m_behind, rhs.m_behind);
        swap(m_docment, rhs.m_docment);
        swap(m_templateItem, rhs.m_templateItem);
        swap(m_template, rhs.m_template);

        result = true;
    }
    return result;
}

}
