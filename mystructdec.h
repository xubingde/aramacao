#pragma once

#ifndef XU_MYSTRUCTDEC_H_
#define XU_MYSTRUCTDEC_H_

#include <string>
#include <utility>
#include <tuple>
#include <vector>
#include "eobject.h"

namespace xu {

class MyStructDec;

class MyStruct;

class MyStructDec : public EObject
{

public:

    MyStructDec();
    MyStructDec(const MyStructDec &  other);
    MyStructDec(MyStructDec &&  other) noexcept;
    virtual ~MyStructDec() noexcept;

    MyStructDec &  operator=(const MyStructDec &  other);
    MyStructDec &  operator=(MyStructDec &&  other) noexcept;

    virtual std::string  toHBlock(std::string const &  tabStr = std::string()) const override;

    MyStruct *  getParentStructPtr() const;
    virtual void  setParentStructPtr(MyStruct *  value);

    std::string  getStructName() const;
    virtual void  setStructName(const std::string &  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    MyStruct *      m_parentStructPtr;
    std::string     m_structName;
};

}

#endif
