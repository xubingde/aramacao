#pragma once

#ifndef XU_ACTISFN_H_
#define XU_ACTISFN_H_

#include <string>
#include <vector>
#include "actfn.h"

namespace xu {

class ActIsFn;

class MyClass;
class Field;
class EObject;
class Parameter;

class ActIsFn : public ActFn
{

public:

    ActIsFn();
    ActIsFn(const ActIsFn &  other);
    ActIsFn(ActIsFn &&  other) noexcept;
    ActIsFn(MyClass *  parentClass, Field *  parentField);
    virtual ~ActIsFn() noexcept;

    ActIsFn &  operator=(const ActIsFn &  other);
    ActIsFn &  operator=(ActIsFn &&  other) noexcept;

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
