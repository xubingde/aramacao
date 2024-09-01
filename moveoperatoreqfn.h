#pragma once

#ifndef XU_MOVEOPERATOREQFN_H_
#define XU_MOVEOPERATOREQFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class MoveOperatorEqFn;

class MyClass;
class EObject;
class Parameter;

class MoveOperatorEqFn : public Function
{

public:

    MoveOperatorEqFn();
    MoveOperatorEqFn(const MoveOperatorEqFn &  other);
    MoveOperatorEqFn(MoveOperatorEqFn &&  other) noexcept;
    MoveOperatorEqFn(MyClass *  parent);
    virtual ~MoveOperatorEqFn() noexcept;

    MoveOperatorEqFn &  operator=(const MoveOperatorEqFn &  other);
    MoveOperatorEqFn &  operator=(MoveOperatorEqFn &&  other) noexcept;

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
