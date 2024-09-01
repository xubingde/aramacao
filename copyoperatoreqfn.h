#pragma once

#ifndef XU_COPYOPERATOREQFN_H_
#define XU_COPYOPERATOREQFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class CopyOperatorEqFn;

class MyClass;
class EObject;
class Parameter;

class CopyOperatorEqFn : public Function
{

public:

    CopyOperatorEqFn();
    CopyOperatorEqFn(const CopyOperatorEqFn &  other);
    CopyOperatorEqFn(CopyOperatorEqFn &&  other) noexcept;
    CopyOperatorEqFn(MyClass *  parent);
    virtual ~CopyOperatorEqFn() noexcept;

    CopyOperatorEqFn &  operator=(const CopyOperatorEqFn &  other);
    CopyOperatorEqFn &  operator=(CopyOperatorEqFn &&  other) noexcept;

    virtual std::string  autoCode() const override;
    virtual void  setFunctionName(std::string const &  value) override;
    virtual void  setReturnType(std::string const &) override;
    virtual void  setReturnType(std::string &&  value) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;
    virtual void  setParentClassPtr(MyClass *  value) override;
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
