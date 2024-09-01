#pragma once

#ifndef XU_ACTGETFN_H_
#define XU_ACTGETFN_H_

#include <string>
#include <vector>
#include "actfn.h"

namespace xu {

class ActGetFn;

class MyClass;
class Field;
class EObject;
class Parameter;

class ActGetFn : public ActFn
{

public:

    ActGetFn();
    ActGetFn(const ActGetFn &  other);
    ActGetFn(ActGetFn &&  other) noexcept;
    ActGetFn(MyClass *  parentClass, Field *  parentField);
    virtual ~ActGetFn() noexcept;

    ActGetFn &  operator=(const ActGetFn &  other);
    ActGetFn &  operator=(ActGetFn &&  other) noexcept;

    virtual std::string  autoCode() const override;
    virtual void  setReturnType(std::string const &) override;
    virtual void  setReturnType(std::string &&  value) override;
    virtual void  setFunctionName(std::string const &) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&) override;
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
