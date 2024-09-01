#pragma once

#ifndef XU_ACTSETCONSTVALUEFN_H_
#define XU_ACTSETCONSTVALUEFN_H_

#include <string>
#include <vector>
#include "actfn.h"

namespace xu {

class ActSetConstValueFn;

class MyClass;
class Field;
class EObject;
class Parameter;

class ActSetConstValueFn : public ActFn
{

public:

    ActSetConstValueFn();
    ActSetConstValueFn(const ActSetConstValueFn &  other);
    ActSetConstValueFn(ActSetConstValueFn &&  other) noexcept;
    ActSetConstValueFn(MyClass *  parentClass, Field *  parentField);
    virtual ~ActSetConstValueFn() noexcept;

    ActSetConstValueFn &  operator=(const ActSetConstValueFn &  other);
    ActSetConstValueFn &  operator=(ActSetConstValueFn &&  other) noexcept;

    virtual std::string  autoCode() const override;
    virtual void  setReturnType(std::string const &) override;
    virtual void  setReturnType(std::string &&  value) override;
    virtual void  setFunctionName(std::string const &) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;
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
