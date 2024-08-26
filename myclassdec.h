#pragma once

#ifndef XU_MYCLASSDEC_H_
#define XU_MYCLASSDEC_H_

#include <string>
#include <utility>
#include <tuple>
#include <vector>
#include "eobject.h"

namespace xu {

class MyClassDec;

class MyClass;

class MyClassDec : public EObject
{

public:

    MyClassDec();
    MyClassDec(const MyClassDec &  other);
    MyClassDec(MyClassDec &&  other) noexcept;
    virtual ~MyClassDec() noexcept;

    MyClassDec &  operator=(const MyClassDec &  other);
    MyClassDec &  operator=(MyClassDec &&  other) noexcept;

    virtual std::string  toHBlock(std::string const &  tabStr = std::string()) const override;

    MyClass *  getParentClassPtr() const;
    void  setParentClassPtr(MyClass *  value);

    std::string  getClassName() const;
    void  setClassName(const std::string &  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    MyClass *       m_parentClassPtr;
    std::string     m_className;
};

}

#endif
