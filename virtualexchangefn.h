#pragma once

#ifndef XU_VIRTUALEXCHANGEFN_H_
#define XU_VIRTUALEXCHANGEFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class VirtualExchangeFn;

class MyClass;
class EObject;
class Parameter;

class VirtualExchangeFn : public Function
{

public:

    VirtualExchangeFn();
    VirtualExchangeFn(const VirtualExchangeFn &  other);
    VirtualExchangeFn(VirtualExchangeFn &&  other) noexcept;
    VirtualExchangeFn(MyClass *  parent);
    virtual ~VirtualExchangeFn() noexcept;

    VirtualExchangeFn &  operator=(const VirtualExchangeFn &  other);
    VirtualExchangeFn &  operator=(VirtualExchangeFn &&  other) noexcept;

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
