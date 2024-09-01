#pragma once

#ifndef XU_INFROMSTRINGFN_H_
#define XU_INFROMSTRINGFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class InFromStringFn;

class MyClass;
class EObject;

class InFromStringFn : public Function
{

public:

    InFromStringFn();
    InFromStringFn(const InFromStringFn &  other);
    InFromStringFn(InFromStringFn &&  other) noexcept;
    InFromStringFn(MyClass *  parent);
    virtual ~InFromStringFn() noexcept;

    InFromStringFn &  operator=(const InFromStringFn &  other);
    InFromStringFn &  operator=(InFromStringFn &&  other) noexcept;

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
