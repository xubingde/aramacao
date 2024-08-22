#pragma once

#ifndef XU_EXTFROMSTRINGFN_H_
#define XU_EXTFROMSTRINGFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class ExtFromStringFn;

class MyClass;
class EObject;
class Parameter;

class ExtFromStringFn : public Function
{

public:

    ExtFromStringFn();
    ExtFromStringFn(const ExtFromStringFn &  other);
    ExtFromStringFn(ExtFromStringFn &&  other) noexcept;
    ExtFromStringFn(std::string const &  classname, MyClass *  parent);
    virtual ~ExtFromStringFn() noexcept;

    ExtFromStringFn &  operator=(const ExtFromStringFn &  other);
    ExtFromStringFn &  operator=(ExtFromStringFn &&  other) noexcept;

    virtual void  setFunctionName(std::string const &  value) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;
    virtual void  setParentClassPtr(MyClass *  value) override;

    std::string  getClassName() const;
    virtual void  setClassName(const std::string &  value);
    virtual void  setClassName(std::string &&  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    void  init();

    std::string     m_className;
};

}

#endif
