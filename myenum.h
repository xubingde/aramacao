#pragma once

#ifndef XU_MYENUM_H_
#define XU_MYENUM_H_

#include <string>
#include <tuple>
#include <vector>
#include "eobject.h"
#include "myenumitem.h"

namespace xu {

class MyEnum;

class MyEnum : public EObject
{

public:

    MyEnum();
    MyEnum(const MyEnum &  other);
    MyEnum(MyEnum &&  other) noexcept;
    virtual ~MyEnum() noexcept;

    MyEnum &  operator=(const MyEnum &  other);
    MyEnum &  operator=(MyEnum &&  other) noexcept;

    virtual std::string  toHBlock(std::string const &  parentTab = std::string()) const override;

    std::string  getName() const;
    virtual void  setName(const std::string &  value);

    std::string  getDocment() const;
    virtual void  setDocment(const std::string &  value);
    virtual void  setDocment(std::string &&  value);

    std::string  getType() const;
    virtual void  setType(const std::string &  value);

    std::string  getBefore() const;
    virtual void  setBefore(const std::string &  value);
    virtual void  setBefore(std::string &&  value);

    std::string  getBehind() const;
    virtual void  setBehind(const std::string &  value);
    virtual void  setBehind(std::string &&  value);

    std::vector<MyEnumItem>  getItem() const;
    virtual void  setItem(const std::vector<MyEnumItem> &  value);
    void  setItem(std::vector<MyEnumItem> &&  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    std::string     m_name;
    std::string     m_docment;
    std::string     m_type;
    std::string     m_before;
    std::string     m_behind;
    std::vector<MyEnumItem>     m_item;
};

}

#endif
