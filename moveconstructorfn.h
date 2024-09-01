#pragma once

#ifndef XU_MOVECONSTRUCTORFN_H_
#define XU_MOVECONSTRUCTORFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class MoveConstructorFn;

class MyClass;
class EObject;
class Parameter;

class MoveConstructorFn : public Function
{

public:

    MoveConstructorFn();
    MoveConstructorFn(const MoveConstructorFn &  other);
    MoveConstructorFn(MoveConstructorFn &&  other) noexcept;
    MoveConstructorFn(MyClass *  parent);
    virtual ~MoveConstructorFn() noexcept;

    MoveConstructorFn &  operator=(const MoveConstructorFn &  other);
    MoveConstructorFn &  operator=(MoveConstructorFn &&  other) noexcept;

    virtual std::string  autoCode() const override;
    virtual void  setFunctionName(std::string const &  value) override;
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

    void  updateDefualtValue();
};

}

#endif
