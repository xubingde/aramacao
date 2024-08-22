#pragma once

#ifndef XU_PARAMETER_H_
#define XU_PARAMETER_H_

#include <string>

namespace xu {

class Parameter;

bool  operator==(const Parameter &  lhs, const Parameter &  rhs);
bool  operator!=(const Parameter &  lhs, const Parameter &  rhs);
void  swap(Parameter &  lhs, Parameter &  rhs) noexcept;
bool  operator<(const Parameter &  lhs, const Parameter &  rhs);
bool  operator<=(const Parameter &  lhs, const Parameter &  rhs);
bool  operator>(const Parameter &  lhs, const Parameter &  rhs);
bool  operator>=(const Parameter &  lhs, const Parameter &  rhs);
bool  fromString(Parameter &  value, const char *  data, const size_t  size);

class Parameter final
{
friend bool  operator==(const Parameter &  lhs, const Parameter &  rhs);
friend bool  operator!=(const Parameter &  lhs, const Parameter &  rhs);
friend bool  operator<(const Parameter &  lhs, const Parameter &  rhs);
friend bool  operator<=(const Parameter &  lhs, const Parameter &  rhs);
friend bool  operator>(const Parameter &  lhs, const Parameter &  rhs);
friend bool  operator>=(const Parameter &  lhs, const Parameter &  rhs);

public:

    Parameter();
    Parameter(const Parameter &  other);
    Parameter(Parameter &&  other) noexcept;
    ~Parameter() noexcept;

    Parameter &  operator=(const Parameter &  other);
    Parameter &  operator=(Parameter &&  other) noexcept;

    std::string  toString() const;
    bool  fromString(const char *  data, const size_t  size);
    void  swap(Parameter &  value) noexcept;

    std::string  getType() const;
    void  setType(const std::string &  value);

    std::string  getParameterName() const;
    void  setParameterName(const std::string &  value);

    std::string  getDefalutValue() const;
    void  setDefalutValue(const std::string &  value);

    std::string  getDocment() const;
    void  setDocment(const std::string &  value);
    void  setDocment(std::string &&  value);

private:

    std::string     m_type;
    std::string     m_parameterName;
    std::string     m_defalutValue;
    std::string     m_docment;
};

}

#endif
