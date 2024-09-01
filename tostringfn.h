#pragma once

#ifndef XU_TOSTRINGFN_H_
#define XU_TOSTRINGFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class ToStringFn;

class MyClass;
class EObject;


class ToStringFn : public Function
{

public:

    ToStringFn();
    ToStringFn(const ToStringFn &  other);
    ToStringFn(ToStringFn &&  other) noexcept;
    ToStringFn(MyClass *  parent);
    virtual ~ToStringFn() noexcept;

    ToStringFn &  operator=(const ToStringFn &  other);
    ToStringFn &  operator=(ToStringFn &&  other) noexcept;

    virtual void  setFunctionName(std::string const &  value) override;
    virtual std::string  autoCode() const override;
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
