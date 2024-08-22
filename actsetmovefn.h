#pragma once

#ifndef XU_ACTSETMOVEFN_H_
#define XU_ACTSETMOVEFN_H_

#include <string>
#include <vector>
#include "actfn.h"

namespace xu {

class ActSetMoveFn;

class MyClass;
class Field;
class EObject;
class Parameter;

class ActSetMoveFn : public ActFn
{

public:

    ActSetMoveFn();
    ActSetMoveFn(const ActSetMoveFn &  other);
    ActSetMoveFn(ActSetMoveFn &&  other) noexcept;
    ActSetMoveFn(MyClass *  parentClass, Field *  parentField);
    virtual ~ActSetMoveFn() noexcept;

    ActSetMoveFn &  operator=(const ActSetMoveFn &  other);
    ActSetMoveFn &  operator=(ActSetMoveFn &&  other) noexcept;

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
