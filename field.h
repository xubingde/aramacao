#pragma once

#ifndef XU_FIELD_H_
#define XU_FIELD_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include "eobject.h"

namespace xu {

class Field;

class ActFn;

bool  operator==(const Field &  lhs, const Field &  rhs);
bool  operator!=(const Field &  lhs, const Field &  rhs);
void  swap(Field &  lhs, Field &  rhs) noexcept;
bool  operator<(const Field &  lhs, const Field &  rhs);
bool  operator<=(const Field &  lhs, const Field &  rhs);
bool  operator>(const Field &  lhs, const Field &  rhs);
bool  operator>=(const Field &  lhs, const Field &  rhs);
bool  fromString(Field &  value, const char *  data, const size_t  size);

class Field final
{
friend bool  operator==(const Field &  lhs, const Field &  rhs);
friend bool  operator!=(const Field &  lhs, const Field &  rhs);
friend bool  operator<(const Field &  lhs, const Field &  rhs);
friend bool  operator<=(const Field &  lhs, const Field &  rhs);
friend bool  operator>(const Field &  lhs, const Field &  rhs);
friend bool  operator>=(const Field &  lhs, const Field &  rhs);

public:

    Field();
    Field(const Field &  other);
    Field(Field &&  other) noexcept;
    ~Field() noexcept;

    Field &  operator=(const Field &  other);
    Field &  operator=(Field &&  other) noexcept;

    std::string  toString() const;
    bool  fromString(const char *  data, const size_t  size);
    void  swap(Field &  value) noexcept;

    std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  getActionFnRef();
    void  updateActionPtr();
    std::string  toHBlock(std::string const &  tabStr = std::string()) const;
    std::string  toBlockStruct(std::string const &  tabStr = std::string()) const;
    std::string  cppCodeGeneral(std::string const &  tabStr = std::string()) const;
    std::string  hCodeDcl(std::string const &  tabStr = std::string()) const;
    std::string  getPrivateName() const;
    std::string  getCtorDefValue() const;

    std::vector<size_t>  getStringErr() const;

    std::string  getFieldName() const;
    void  setFieldName(const std::string &  value);

    std::string  getDocment() const;
    void  setDocment(const std::string &  value);
    void  setDocment(std::string &&  value);

    std::string  getTypeName() const;
    void  setTypeName(const std::string &  value);
    void  setTypeName(std::string &&  value);

    std::string  getDefValue() const;
    void  setDefValue(const std::string &  value);
    void  setDefValue(std::string &&  value);

    std::string  getArray() const;
    void  setArray(const std::string &  value);

    std::string  getAttribute() const;
    void  setAttribute(const std::string &  value);
    void  setAttribute(std::string &&  value);

    std::string  getBefore() const;
    void  setBefore(const std::string &  value);
    void  setBefore(std::string &&  value);

    std::string  getBehind() const;
    void  setBehind(const std::string &  value);
    void  setBehind(std::string &&  value);

    std::vector<std::pair<Action, std::shared_ptr<ActFn>>>  getActionFn() const;
    void  setActionFn(const std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  value);

    int  getAlignByte() const;
    void  setAlignByte(const int  value);

    bool  isMutable() const;
    void  setMutable(const bool  value);

    bool  isPointer() const;
    void  setPointer(const bool  value);

private:

    std::vector<size_t>     m_stringErr;
    std::string     m_fieldName;
    std::string     m_docment;
    std::string     m_typeName;
    std::string     m_defValue;
    std::string     m_array;
    std::string     m_attribute;
    std::string     m_before;
    std::string     m_behind;
    std::vector<std::pair<Action, std::shared_ptr<ActFn>>>  m_actionFn;
    int             m_alignByte;
    bool            m_mutable;
    bool            m_pointer;
};

}

#endif
