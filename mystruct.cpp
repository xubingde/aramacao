#include <cstring>
#include <typeinfo>
#include "mystruct.h"
#include "icode.h"
#include "fmt.h"
#include "publictype.h"

namespace xu {

MyStruct::MyStruct():
        EObject(),
        m_name("Struct1"),
        m_docment(),
        m_attribute(),
        m_before(),
        m_behind(),
        m_beforeDcl(),
        m_behindDcl(),
        m_field(),
        m_alignas(0)
{
    setTreeLabel("S   " + m_name);
    setBaseType(Etype::eStruct);
}

MyStruct::MyStruct(const MyStruct &  other):
        EObject(other),
        m_name(other.m_name),
        m_docment(other.m_docment),
        m_attribute(other.m_attribute),
        m_before(other.m_before),
        m_behind(other.m_behind),
        m_beforeDcl(other.m_beforeDcl),
        m_behindDcl(other.m_behindDcl),
        m_field(other.m_field),
        m_alignas(other.m_alignas)
{
}

MyStruct::MyStruct(MyStruct &&  other) noexcept:
        EObject(std::move(other)),
        m_name(std::move(other.m_name)),
        m_docment(std::move(other.m_docment)),
        m_attribute(std::move(other.m_attribute)),
        m_before(std::move(other.m_before)),
        m_behind(std::move(other.m_behind)),
        m_beforeDcl(std::move(other.m_beforeDcl)),
        m_behindDcl(std::move(other.m_behindDcl)),
        m_field(std::move(other.m_field)),
        m_alignas(std::move(other.m_alignas))
{
}

MyStruct::~MyStruct() noexcept
{
}

MyStruct &
MyStruct::operator=(const MyStruct &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_name = other.m_name;
    m_docment = other.m_docment;
    m_attribute = other.m_attribute;
    m_before = other.m_before;
    m_behind = other.m_behind;
    m_beforeDcl = other.m_beforeDcl;
    m_behindDcl = other.m_behindDcl;
    m_field = other.m_field;
    m_alignas = other.m_alignas;

    return *this;
}

MyStruct &
MyStruct::operator=(MyStruct &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_name = std::move(other.m_name);
    m_docment = std::move(other.m_docment);
    m_attribute = std::move(other.m_attribute);
    m_before = std::move(other.m_before);
    m_behind = std::move(other.m_behind);
    m_beforeDcl = std::move(other.m_beforeDcl);
    m_behindDcl = std::move(other.m_behindDcl);
    m_field = std::move(other.m_field);
    m_alignas = std::move(other.m_alignas);

    return *this;
}

std::string
MyStruct::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res("\n");

    res += m_before;
    res += tabStr + "struct ";
    if (m_attribute.size() > 0) {
        res += m_attribute + " ";
    }
    if (m_alignas > 0) {
        res += "alignas(" + std::to_string(m_alignas) + ") ";
    }
    res += m_name + " {\n";

    size_t const  size = m_field.size();
    for (size_t  i = 0; i < size; ++i) {
        res += m_field[i].toBlockStruct(tabStr);
    }
    res += tabStr + "};\n" + m_behind;

    return res;
}

std::string
MyStruct::getName() const
{
    return m_name;
}

void
MyStruct::setName(const std::string &  value)
{
    m_name = xu::trim(value);
    if (!xu::checkReg(m_name)) {
        m_name = "Struct1";
    }
    m_name[0] = xu::toupperS(m_name[0]);
    setTreeLabel("S   " + m_name);
}

std::string
MyStruct::getDocment() const
{
    return m_docment;
}

void
MyStruct::setDocment(const std::string &  value)
{
    m_docment = value;
}

void
MyStruct::setDocment(std::string &&  value)
{
    m_docment = std::move(value);
}

std::string
MyStruct::getAttribute() const
{
    return m_attribute;
}

void
MyStruct::setAttribute(const std::string &  value)
{
    m_attribute = value;
}

void
MyStruct::setAttribute(std::string &&  value)
{
    m_attribute = std::move(value);
}

std::string
MyStruct::getBefore() const
{
    return m_before;
}

void
MyStruct::setBefore(const std::string &  value)
{
    m_before = value;
    xu::procCode(m_before);
}

void
MyStruct::setBefore(std::string &&  value)
{
    m_before = std::move(value);
    xu::procCode(m_before);
}

std::string
MyStruct::getBehind() const
{
    return m_behind;
}

void
MyStruct::setBehind(const std::string &  value)
{
    m_behind = value;
    xu::procCode(m_behind);
}

void
MyStruct::setBehind(std::string &&  value)
{
    m_behind = std::move(value);
    xu::procCode(m_behind);
}

std::string
MyStruct::getBeforeDcl() const
{
    return m_beforeDcl;
}

void
MyStruct::setBeforeDcl(const std::string &  value)
{
    m_beforeDcl = value;
    xu::procCode(m_beforeDcl);
}

void
MyStruct::setBeforeDcl(std::string &&  value)
{
    m_beforeDcl = std::move(value);
    xu::procCode(m_beforeDcl);
}

std::string
MyStruct::getBehindDcl() const
{
    return m_behindDcl;
}

void
MyStruct::setBehindDcl(const std::string &  value)
{
    m_behindDcl = value;
    xu::procCode(m_behindDcl);
}

void
MyStruct::setBehindDcl(std::string &&  value)
{
    m_behindDcl = std::move(value);
    xu::procCode(m_behindDcl);
}

std::vector<Field>
MyStruct::getField() const
{
    return m_field;
}

void
MyStruct::setField(const std::vector<Field> &  value)
{
    m_field = value;
    for (auto &  fd: m_field) {
        if (fd.getFieldName() == "") {
            fd.setFieldName("Field1");
        }
        fd.setActionFn({});
    }
}

void
MyStruct::setField(std::vector<Field> &&  value)
{
    m_field = std::move(value);
    for (auto &  fd: m_field) {
        if (fd.getFieldName() == "") {
            fd.setFieldName("Field1");
        }
        fd.setActionFn({});
    }
}

int
MyStruct::getAlignas() const
{
    return m_alignas;
}

void
MyStruct::setAlignas(const int  value)
{
    m_alignas = value;
    if (m_alignas == 4 || m_alignas == 8 || m_alignas == 16 || m_alignas == 32 ||
            m_alignas == 64 || m_alignas == 128) {
        ;
    } else {
        m_alignas = 0;
    }
}

bool
MyStruct::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const MyStruct &  rhs = dynamic_cast<const MyStruct &>(value);

        result = this->EObject::equal(value);
        if (!result) return result;

        result = ( m_name == rhs.m_name );
        if (!result) return result;

        result = ( m_docment == rhs.m_docment );
        if (!result) return result;

        result = ( m_attribute == rhs.m_attribute );
        if (!result) return result;

        result = ( m_before == rhs.m_before );
        if (!result) return result;

        result = ( m_behind == rhs.m_behind );
        if (!result) return result;

        result = ( m_field == rhs.m_field );
        if (!result) return result;

        result = ( m_alignas == rhs.m_alignas );
        if (!result) return result;

        result = ( m_beforeDcl == rhs.m_beforeDcl );
        if (!result) return result;

        result = ( m_behindDcl == rhs.m_behindDcl );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
MyStruct::less(const EObject &  value) const
{
    if (this->EObject::less(value)) return true;
    if (!(this->EObject::equal(value))) return false;

    try {
        const MyStruct &  rhs = dynamic_cast<const MyStruct &>(value);

        if (m_name < rhs.m_name) return true;
        if (rhs.m_name < m_name) return false;

        if (m_docment < rhs.m_docment) return true;
        if (rhs.m_docment < m_docment) return false;

        if (m_attribute < rhs.m_attribute) return true;
        if (rhs.m_attribute < m_attribute) return false;

        if (m_before < rhs.m_before) return true;
        if (rhs.m_before < m_before) return false;

        if (m_behind < rhs.m_behind) return true;
        if (rhs.m_behind < m_behind) return false;

        if (m_field < rhs.m_field) return true;
        if (rhs.m_field < m_field) return false;

        if (m_alignas < rhs.m_alignas) return true;
        if (rhs.m_alignas < m_alignas) return false;

        if (m_beforeDcl < rhs.m_beforeDcl) return true;
        if (rhs.m_beforeDcl < m_beforeDcl) return false;

        if (m_behindDcl < rhs.m_behindDcl) return true;
        if (rhs.m_behindDcl < m_behindDcl) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
MyStruct::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_name));
    xu::append(res, xu::toString(m_docment));
    xu::append(res, xu::toString(m_attribute));
    xu::append(res, xu::toString(m_before));
    xu::append(res, xu::toString(m_behind));
    xu::append(res, xu::toString(m_field));
    xu::append(res, xu::toString(m_alignas));
    xu::append(res, xu::toString(m_beforeDcl));
    xu::append(res, xu::toString(m_behindDcl));

    return res;
}

bool
MyStruct::deserialize(const char *  data,
                      const size_t  size)
{
    MyStruct  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 9) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_name, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_docment, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_attribute, vi[3]))  err.push_back({3});
        if (!xu::fromString(me.m_before, vi[4]))  err.push_back({4});
        if (!xu::fromString(me.m_behind, vi[5]))  err.push_back({5});
        if (!xu::fromString(me.m_field, vi[6]))  err.push_back({6});
        if (!xu::fromString(me.m_alignas, vi[7]))  err.push_back({7});
        if (!xu::fromString(me.m_beforeDcl, vi[8]))  err.push_back({8});
        if (!xu::fromString(me.m_behindDcl, vi[9]))  err.push_back({9});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
MyStruct::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        MyStruct &  rhs = dynamic_cast<MyStruct &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_name, rhs.m_name);
        swap(m_docment, rhs.m_docment);
        swap(m_attribute, rhs.m_attribute);
        swap(m_before, rhs.m_before);
        swap(m_behind, rhs.m_behind);
        swap(m_beforeDcl, rhs.m_beforeDcl);
        swap(m_behindDcl, rhs.m_behindDcl);
        swap(m_field, rhs.m_field);
        swap(m_alignas, rhs.m_alignas);

        result = true;
    }
    return result;
}

}
