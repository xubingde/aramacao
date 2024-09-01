#pragma once

#ifndef XU_GREATEREQFN_H_
#define XU_GREATEREQFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class GreaterEqFn;

class MyClass;
class EObject;
class Parameter;

class GreaterEqFn : public Function
{

public:

    GreaterEqFn();
    GreaterEqFn(const GreaterEqFn &  other);
    GreaterEqFn(GreaterEqFn &&  other) noexcept;
    GreaterEqFn(std::string const &  classname, MyClass *  parent);
    virtual ~GreaterEqFn() noexcept;

    GreaterEqFn &  operator=(const GreaterEqFn &  other);
    GreaterEqFn &  operator=(GreaterEqFn &&  other) noexcept;

    virtual void  setFunctionName(std::string const &  value) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;
    virtual void  setParentClassPtr(MyClass *  value) override;
    virtual void  init() override;

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

    std::string     m_className;
};

}

#endif
