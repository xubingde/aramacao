#pragma once

#ifndef XU_NAMESPACEITEM_H_
#define XU_NAMESPACEITEM_H_

#include <string>

namespace xu {

class NamespaceItem;

bool  operator==(const NamespaceItem &  lhs, const NamespaceItem &  rhs);
bool  operator!=(const NamespaceItem &  lhs, const NamespaceItem &  rhs);
void  swap(NamespaceItem &  lhs, NamespaceItem &  rhs) noexcept;
bool  operator<(const NamespaceItem &  lhs, const NamespaceItem &  rhs);
bool  operator<=(const NamespaceItem &  lhs, const NamespaceItem &  rhs);
bool  operator>(const NamespaceItem &  lhs, const NamespaceItem &  rhs);
bool  operator>=(const NamespaceItem &  lhs, const NamespaceItem &  rhs);
bool  fromString(NamespaceItem &  value, const char *  data, const size_t  size);

class NamespaceItem final
{
friend bool  operator==(const NamespaceItem &  lhs, const NamespaceItem &  rhs);
friend bool  operator!=(const NamespaceItem &  lhs, const NamespaceItem &  rhs);
friend bool  operator<(const NamespaceItem &  lhs, const NamespaceItem &  rhs);
friend bool  operator<=(const NamespaceItem &  lhs, const NamespaceItem &  rhs);
friend bool  operator>(const NamespaceItem &  lhs, const NamespaceItem &  rhs);
friend bool  operator>=(const NamespaceItem &  lhs, const NamespaceItem &  rhs);

public:

    NamespaceItem();
    NamespaceItem(const NamespaceItem &  other);
    NamespaceItem(NamespaceItem &&  other) noexcept;
    ~NamespaceItem() noexcept;

    NamespaceItem &  operator=(const NamespaceItem &  other);
    NamespaceItem &  operator=(NamespaceItem &&  other) noexcept;

    std::string  toString() const;
    bool  fromString(const char *  data, const size_t  size);
    void  swap(NamespaceItem &  value) noexcept;

    std::string  hCodeStart() const;
    std::string  hCodeEnd() const;
    std::string  cppCodeStart() const;
    std::string  cppCodeEnd() const;

    std::string  getNamespaceValue() const;
    void  setNamespaceValue(const std::string &  value);
    void  setNamespaceValue(std::string &&  value);

    std::string  getHBeginBefor() const;
    void  setHBeginBefor(const std::string &  value);
    void  setHBeginBefor(std::string &&  value);

    std::string  getHBeginBehind() const;
    void  setHBeginBehind(const std::string &  value);
    void  setHBeginBehind(std::string &&  value);

    std::string  getHEndBefor() const;
    void  setHEndBefor(const std::string &  value);
    void  setHEndBefor(std::string &&  value);

    std::string  getHEndBehind() const;
    void  setHEndBehind(const std::string &  value);
    void  setHEndBehind(std::string &&  value);

    std::string  getCppBeginBefor() const;
    void  setCppBeginBefor(const std::string &  value);
    void  setCppBeginBefor(std::string &&  value);

    std::string  getCppBeginBehind() const;
    void  setCppBeginBehind(const std::string &  value);
    void  setCppBeginBehind(std::string &&  value);

    std::string  getCppEndBefor() const;
    void  setCppEndBefor(const std::string &  value);
    void  setCppEndBefor(std::string &&  value);

    std::string  getCppEndBehind() const;
    void  setCppEndBehind(const std::string &  value);
    void  setCppEndBehind(std::string &&  value);

private:

    std::string     m_namespaceValue;
    std::string     m_hBeginBefor;
    std::string     m_hBeginBehind;
    std::string     m_hEndBefor;
    std::string     m_hEndBehind;
    std::string     m_cppBeginBefor;
    std::string     m_cppBeginBehind;
    std::string     m_cppEndBefor;
    std::string     m_cppEndBehind;
};

}

#endif
