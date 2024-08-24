#include <cstring>
#include "parameter.h"
#include "fmt.h"
#include "icode.h"

namespace xu {

Parameter::Parameter():
        m_type("int"),
        m_parameterName("value"),
        m_defalutValue(),
        m_docment()
{
}

Parameter::Parameter(const Parameter &  other):
        m_type(other.m_type),
        m_parameterName(other.m_parameterName),
        m_defalutValue(other.m_defalutValue),
        m_docment(other.m_docment)
{
}

Parameter::Parameter(Parameter &&  other) noexcept:
        m_type(std::move(other.m_type)),
        m_parameterName(std::move(other.m_parameterName)),
        m_defalutValue(std::move(other.m_defalutValue)),
        m_docment(std::move(other.m_docment))
{
}

Parameter::~Parameter() noexcept
{
}

Parameter &
Parameter::operator=(const Parameter &  other)
{
    if (this == &other) return *this;

    m_type = other.m_type;
    m_parameterName = other.m_parameterName;
    m_defalutValue = other.m_defalutValue;
    m_docment = other.m_docment;

    return *this;
}

Parameter &
Parameter::operator=(Parameter &&  other) noexcept
{
    if (this == &other) return *this;

    m_type = std::move(other.m_type);
    m_parameterName = std::move(other.m_parameterName);
    m_defalutValue = std::move(other.m_defalutValue);
    m_docment = std::move(other.m_docment);

    return *this;
}

std::string
Parameter::getType() const
{
    return m_type;
}

void
Parameter::setType(const std::string &  value)
{
    m_type = xu::trim(value);
}

std::string
Parameter::getParameterName() const
{
    return m_parameterName;
}

void
Parameter::setParameterName(const std::string &  value)
{
    m_parameterName = xu::trim(value);
}

std::string
Parameter::getDefalutValue() const
{
    return m_defalutValue;
}

void
Parameter::setDefalutValue(const std::string &  value)
{
    m_defalutValue = xu::trim(value);
}

std::string
Parameter::getDocment() const
{
    return m_docment;
}

void
Parameter::setDocment(const std::string &  value)
{
    m_docment = value;
}

void
Parameter::setDocment(std::string &&  value)
{
    m_docment = std::move(value);
}

bool
operator==(const Parameter &  lhs,
           const Parameter &  rhs)
{
    if (&lhs == &rhs) return true;
    bool  result = false;

    result = ( lhs.m_type == rhs.m_type );
    if (!result) return result;

    result = ( lhs.m_parameterName == rhs.m_parameterName );
    if (!result) return result;

    result = ( lhs.m_defalutValue == rhs.m_defalutValue );
    if (!result) return result;

    result = ( lhs.m_docment == rhs.m_docment );
    if (!result) return result;

    return result;
}

bool
operator!=(const Parameter &  lhs,
           const Parameter &  rhs)
{
    return !(lhs == rhs);
}

bool
operator<(const Parameter &  lhs,
          const Parameter &  rhs)
{
    if (&lhs == &rhs) return false;

    if (lhs.m_type < rhs.m_type) return true;
    if (rhs.m_type < lhs.m_type) return false;

    if (lhs.m_parameterName < rhs.m_parameterName) return true;
    if (rhs.m_parameterName < lhs.m_parameterName) return false;

    if (lhs.m_defalutValue < rhs.m_defalutValue) return true;
    if (rhs.m_defalutValue < lhs.m_defalutValue) return false;

    if (lhs.m_docment < rhs.m_docment) return true;
    if (rhs.m_docment < lhs.m_docment) return false;

    return false;
}

bool
operator<=(const Parameter &  lhs,
           const Parameter &  rhs)
{
    return !(lhs > rhs);
}

bool
operator>(const Parameter &  lhs,
          const Parameter &  rhs)
{
    return rhs < lhs;
}

bool
operator>=(const Parameter &  lhs,
           const Parameter &  rhs)
{
    return !(lhs < rhs);
}

std::string
Parameter::toString() const
{
    std::string  res;

    xu::append(res, xu::toString(m_type));
    xu::append(res, xu::toString(m_parameterName));
    xu::append(res, xu::toString(m_defalutValue));
    xu::append(res, xu::toString(m_docment));

    return res;
}

bool
Parameter::fromString(const char *  data,
                      const size_t  size)
{
    Parameter  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 3) {
        if (!xu::fromString(me.m_type, vi[0]))  err.push_back({0});
        if (!xu::fromString(me.m_parameterName, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_defalutValue, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_docment, vi[3]))  err.push_back({3});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
fromString(Parameter &  value,
           const char *  data,
           const size_t  size)
{
    return value.fromString(data, size);
}

void
swap(Parameter &  lhs,
     Parameter &  rhs) noexcept
{
    lhs.swap(rhs);
}

void
Parameter::swap(Parameter &  value) noexcept
{
    if (this == &value) return;
    using std::swap;
    swap(m_type, value.m_type);
    swap(m_parameterName, value.m_parameterName);
    swap(m_defalutValue, value.m_defalutValue);
    swap(m_docment, value.m_docment);
}

}
