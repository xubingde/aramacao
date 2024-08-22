#pragma once

#ifndef XU_INCLUDEITEM_H_
#define XU_INCLUDEITEM_H_

#include <string>

namespace xu {

class IncludeItem;

bool  operator==(const IncludeItem &  lhs, const IncludeItem &  rhs);
bool  operator!=(const IncludeItem &  lhs, const IncludeItem &  rhs);
void  swap(IncludeItem &  lhs, IncludeItem &  rhs) noexcept;
bool  operator<(const IncludeItem &  lhs, const IncludeItem &  rhs);
bool  operator<=(const IncludeItem &  lhs, const IncludeItem &  rhs);
bool  operator>(const IncludeItem &  lhs, const IncludeItem &  rhs);
bool  operator>=(const IncludeItem &  lhs, const IncludeItem &  rhs);
bool  fromString(IncludeItem &  value, const char *  data, const size_t  size);

class IncludeItem final
{
friend bool  operator==(const IncludeItem &  lhs, const IncludeItem &  rhs);
friend bool  operator!=(const IncludeItem &  lhs, const IncludeItem &  rhs);
friend bool  operator<(const IncludeItem &  lhs, const IncludeItem &  rhs);
friend bool  operator<=(const IncludeItem &  lhs, const IncludeItem &  rhs);
friend bool  operator>(const IncludeItem &  lhs, const IncludeItem &  rhs);
friend bool  operator>=(const IncludeItem &  lhs, const IncludeItem &  rhs);

public:

    IncludeItem();
    IncludeItem(const IncludeItem &  other);
    IncludeItem(IncludeItem &&  other) noexcept;
    ~IncludeItem() noexcept;

    IncludeItem &  operator=(const IncludeItem &  other);
    IncludeItem &  operator=(IncludeItem &&  other) noexcept;

    std::string  toString() const;
    bool  fromString(const char *  data, const size_t  size);
    void  swap(IncludeItem &  value) noexcept;

    std::string  toHCode() const;

    std::string  getIncludeValue() const;
    void  setIncludeValue(const std::string &  value);
    void  setIncludeValue(std::string &&  value);

    std::string  getBefore() const;
    void  setBefore(const std::string &  value);
    void  setBefore(std::string &&  value);

    std::string  getBehind() const;
    void  setBehind(const std::string &  value);
    void  setBehind(std::string &&  value);

private:

    static void  procIncludeValue(std::string &  value);

    std::string     m_includeValue;
    std::string     m_before;
    std::string     m_behind;
};

}

#endif
