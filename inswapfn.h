#pragma once

#ifndef XU_INSWAPFN_H_
#define XU_INSWAPFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class InSwapFn;

class MyClass;
class EObject;
class Parameter;

class InSwapFn : public Function
{

public:

    InSwapFn();
    InSwapFn(const InSwapFn &  other);
    InSwapFn(InSwapFn &&  other) noexcept;
    InSwapFn(MyClass *  parent);
    virtual ~InSwapFn() noexcept;

    InSwapFn &  operator=(const InSwapFn &  other);
    InSwapFn &  operator=(InSwapFn &&  other) noexcept;

    virtual void  setFunctionName(std::string const &  value) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;
    virtual void  setParentClassPtr(MyClass *  value) override;
    virtual std::string  autoCode() const override;
    virtual void  init() override;

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:
};

}

#endif
