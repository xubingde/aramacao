#pragma once

#ifndef XU_ACTSETCOPYFN_H_
#define XU_ACTSETCOPYFN_H_

#include <string>
#include <vector>
#include "actfn.h"

namespace xu {

class ActSetCopyFn;

class MyClass;
class Field;
class EObject;
class Parameter;

class ActSetCopyFn : public ActFn
{

public:

    ActSetCopyFn();
    ActSetCopyFn(const ActSetCopyFn &  other);
    ActSetCopyFn(ActSetCopyFn &&  other) noexcept;
    ActSetCopyFn(MyClass *  parentClass, Field *  parentField);
    virtual ~ActSetCopyFn() noexcept;

    ActSetCopyFn &  operator=(const ActSetCopyFn &  other);
    ActSetCopyFn &  operator=(ActSetCopyFn &&  other) noexcept;

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
