#pragma once

#ifndef XU_VIRTUALLESSFN_H_
#define XU_VIRTUALLESSFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class VirtualLessFn;

class MyClass;
class EObject;
class Parameter;

class VirtualLessFn : public Function
{

public:

    VirtualLessFn();
    VirtualLessFn(const VirtualLessFn &  other);
    VirtualLessFn(VirtualLessFn &&  other) noexcept;
    VirtualLessFn(MyClass *  parent);
    virtual ~VirtualLessFn() noexcept;

    VirtualLessFn &  operator=(const VirtualLessFn &  other);
    VirtualLessFn &  operator=(VirtualLessFn &&  other) noexcept;

    virtual void  setFunctionName(std::string const &  value) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;
    virtual void  setParentClassPtr(MyClass *  value) override;
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
