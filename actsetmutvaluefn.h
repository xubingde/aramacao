#pragma once

#ifndef XU_ACTSETMUTVALUEFN_H_
#define XU_ACTSETMUTVALUEFN_H_

#include <string>
#include <vector>
#include "actfn.h"

namespace xu {

class ActSetMutValueFn;

class MyClass;
class Field;
class EObject;
class Parameter;

class ActSetMutValueFn : public ActFn
{

public:

    ActSetMutValueFn();
    ActSetMutValueFn(const ActSetMutValueFn &  other);
    ActSetMutValueFn(ActSetMutValueFn &&  other) noexcept;
    ActSetMutValueFn(MyClass *  parentClass, Field *  parentField);
    virtual ~ActSetMutValueFn() noexcept;

    ActSetMutValueFn &  operator=(const ActSetMutValueFn &  other);
    ActSetMutValueFn &  operator=(ActSetMutValueFn &&  other) noexcept;

    virtual std::string  autoCode() const override;
    virtual void  setReturnType(std::string const &) override;
    virtual void  setReturnType(std::string &&  value) override;
    virtual void  setFunctionName(std::string const &) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    void  init();
};

}

#endif
