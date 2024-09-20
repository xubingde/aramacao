#pragma once

#ifndef XU_MYSTRUCT_H_
#define XU_MYSTRUCT_H_

#include <string>
#include <utility>
#include <tuple>
#include <vector>
#include <memory>
#include "eobject.h"
#include "field.h"

namespace xu {

class MyStruct;

class MyStruct : public EObject
{

public:

    MyStruct();
    MyStruct(const MyStruct &  other);
    MyStruct(MyStruct &&  other) noexcept;
    virtual ~MyStruct() noexcept;

    MyStruct &  operator=(const MyStruct &  other);
    MyStruct &  operator=(MyStruct &&  other) noexcept;

    virtual std::string  toHBlock(std::string const &  tabStr = std::string()) const override;

    std::string  getName() const;
    virtual void  setName(const std::string &  value);

    std::string  getDocment() const;
    virtual void  setDocment(const std::string &  value);
    virtual void  setDocment(std::string &&  value);

    std::string  getAttribute() const;
    virtual void  setAttribute(const std::string &  value);
    virtual void  setAttribute(std::string &&  value);

    std::string  getBefore() const;
    virtual void  setBefore(const std::string &  value);
    virtual void  setBefore(std::string &&  value);

    std::string  getBehind() const;
    virtual void  setBehind(const std::string &  value);
    virtual void  setBehind(std::string &&  value);

    std::string  getBeforeDcl() const;
    virtual void  setBeforeDcl(const std::string &  value);
    virtual void  setBeforeDcl(std::string &&  value);

    std::string  getBehindDcl() const;
    virtual void  setBehindDcl(const std::string &  value);
    virtual void  setBehindDcl(std::string &&  value);

    std::vector<std::shared_ptr<Field>>  getField() const;
    virtual void  setField(const std::vector<std::shared_ptr<Field>> &  value);
    virtual void  setField(std::vector<std::shared_ptr<Field>> &&  value);

    int  getAlignas() const;
    virtual void  setAlignas(const int  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    void  copyField();

    std::string     m_name;
    std::string     m_docment;
    std::string     m_attribute;
    std::string     m_before;
    std::string     m_behind;
    std::string     m_beforeDcl;
    std::string     m_behindDcl;
    std::vector<std::shared_ptr<Field>>     m_field;
    int             m_alignas;
};

}

#endif
