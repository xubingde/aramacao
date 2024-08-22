#pragma once

#ifndef XU_TPL_H_
#define XU_TPL_H_

#include <string>

namespace xu {

class Tpl;

bool  operator==(const Tpl &  lhs, const Tpl &  rhs);
bool  operator!=(const Tpl &  lhs, const Tpl &  rhs);
void  swap(Tpl &  lhs, Tpl &  rhs) noexcept;
bool  operator<(const Tpl &  lhs, const Tpl &  rhs);
bool  operator<=(const Tpl &  lhs, const Tpl &  rhs);
bool  operator>(const Tpl &  lhs, const Tpl &  rhs);
bool  operator>=(const Tpl &  lhs, const Tpl &  rhs);
bool  fromString(Tpl &  value, const char *  data, const size_t  size);

class Tpl final
{
friend bool  operator==(const Tpl &  lhs, const Tpl &  rhs);
friend bool  operator!=(const Tpl &  lhs, const Tpl &  rhs);
friend bool  operator<(const Tpl &  lhs, const Tpl &  rhs);
friend bool  operator<=(const Tpl &  lhs, const Tpl &  rhs);
friend bool  operator>(const Tpl &  lhs, const Tpl &  rhs);
friend bool  operator>=(const Tpl &  lhs, const Tpl &  rhs);

public:

    Tpl();
    Tpl(const Tpl &  other);
    Tpl(Tpl &&  other) noexcept;
    ~Tpl() noexcept;

    Tpl &  operator=(const Tpl &  other);
    Tpl &  operator=(Tpl &&  other) noexcept;

    std::string  toString() const;
    bool  fromString(const char *  data, const size_t  size);
    void  swap(Tpl &  value) noexcept;

    std::string  getTypename() const;
    void  setTypename(const std::string &  value);

    std::string  getTName() const;
    void  setTName(const std::string &  value);

    std::string  getDocment() const;
    void  setDocment(const std::string &  value);
    void  setDocment(std::string &&  value);

    std::string  getDefalutValue() const;
    void  setDefalutValue(const std::string &  value);

    std::string  getFriendTypeName() const;
    void  setFriendTypeName(const std::string &  value);

private:

    std::string     m_typename;
    std::string     m_TName;
    std::string     m_docment;
    std::string     m_defalutValue;
    std::string     m_friendTypeName;
};

}

#endif
