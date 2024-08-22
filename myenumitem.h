#pragma once

#ifndef XU_MYENUMITEM_H_
#define XU_MYENUMITEM_H_

#include <string>

namespace xu {

class MyEnumItem;

bool  operator==(const MyEnumItem &  lhs, const MyEnumItem &  rhs);
bool  operator!=(const MyEnumItem &  lhs, const MyEnumItem &  rhs);
void  swap(MyEnumItem &  lhs, MyEnumItem &  rhs) noexcept;
bool  operator<(const MyEnumItem &  lhs, const MyEnumItem &  rhs);
bool  operator<=(const MyEnumItem &  lhs, const MyEnumItem &  rhs);
bool  operator>(const MyEnumItem &  lhs, const MyEnumItem &  rhs);
bool  operator>=(const MyEnumItem &  lhs, const MyEnumItem &  rhs);
bool  fromString(MyEnumItem &  value, const char *  data, const size_t  size);

class MyEnumItem final
{
friend bool  operator==(const MyEnumItem &  lhs, const MyEnumItem &  rhs);
friend bool  operator!=(const MyEnumItem &  lhs, const MyEnumItem &  rhs);
friend bool  operator<(const MyEnumItem &  lhs, const MyEnumItem &  rhs);
friend bool  operator<=(const MyEnumItem &  lhs, const MyEnumItem &  rhs);
friend bool  operator>(const MyEnumItem &  lhs, const MyEnumItem &  rhs);
friend bool  operator>=(const MyEnumItem &  lhs, const MyEnumItem &  rhs);

public:

    MyEnumItem();
    MyEnumItem(const MyEnumItem &  other);
    MyEnumItem(MyEnumItem &&  other) noexcept;
    ~MyEnumItem() noexcept;

    MyEnumItem &  operator=(const MyEnumItem &  other);
    MyEnumItem &  operator=(MyEnumItem &&  other) noexcept;

    std::string  toString() const;
    bool  fromString(const char *  data, const size_t  size);
    void  swap(MyEnumItem &  value) noexcept;

    std::string  toHBlock(bool const  hasComma, std::string const &  parentTab = std::string(), std::string const &  tabStr = std::string("    ")) const;

    std::string  getName() const;
    void  setName(const std::string &  value);

    std::string  getDefalutValue() const;
    void  setDefalutValue(const std::string &  value);

    std::string  getDocment() const;
    void  setDocment(const std::string &  value);
    void  setDocment(std::string &&  value);

    std::string  getBefore() const;
    void  setBefore(const std::string &  value);
    void  setBefore(std::string &&  value);

    std::string  getBehind() const;
    void  setBehind(const std::string &  value);
    void  setBehind(std::string &&  value);

private:

    std::string     m_name;
    std::string     m_defalutValue;
    std::string     m_docment;
    std::string     m_before;
    std::string     m_behind;
};

}

#endif
