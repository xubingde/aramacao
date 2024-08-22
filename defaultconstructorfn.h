#pragma once

#ifndef XU_DEFAULTCONSTRUCTORFN_H_
#define XU_DEFAULTCONSTRUCTORFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class DefaultConstructorFn;

class Myclass;
class EObject;

class DefaultConstructorFn : public Function
{

public:

    DefaultConstructorFn();
    DefaultConstructorFn(const DefaultConstructorFn &  other);
    DefaultConstructorFn(DefaultConstructorFn &&  other) noexcept;
    DefaultConstructorFn(MyClass *  parent);
    virtual ~DefaultConstructorFn() noexcept;

    DefaultConstructorFn &  operator=(const DefaultConstructorFn &  other);
    DefaultConstructorFn &  operator=(DefaultConstructorFn &&  other) noexcept;

    virtual std::string  autoCode() const override;
    virtual void  setFunctionName(std::string const &  value) override;
    virtual void  setParentClassPtr(MyClass *  value) override;

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    void  updateDefualtValue();
    void  init();
};

}

#endif
