#pragma once

#ifndef XU_VIRTUALEQFN_H_
#define XU_VIRTUALEQFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class VirtualEqFn;

class MyClass;
class EObject;
class Parameter;

class VirtualEqFn : public Function
{

public:

    VirtualEqFn();
    VirtualEqFn(const VirtualEqFn &  other);
    VirtualEqFn(VirtualEqFn &&  other) noexcept;
    VirtualEqFn(MyClass *  parent);
    virtual ~VirtualEqFn() noexcept;

    VirtualEqFn &  operator=(const VirtualEqFn &  other);
    VirtualEqFn &  operator=(VirtualEqFn &&  other) noexcept;

    virtual void  setFunctionName(std::string const &  value) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;
    virtual void  setParentClassPtr(MyClass *  value) override;
    virtual std::string  autoCode() const override;

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
