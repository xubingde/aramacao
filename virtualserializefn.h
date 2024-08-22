#pragma once

#ifndef XU_VIRTUALSERIALIZEFN_H_
#define XU_VIRTUALSERIALIZEFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class VirtualSerializeFn;

class MyClass;
class EObject;

class VirtualSerializeFn : public Function
{

public:

    VirtualSerializeFn();
    VirtualSerializeFn(const VirtualSerializeFn &  other);
    VirtualSerializeFn(VirtualSerializeFn &&  other) noexcept;
    VirtualSerializeFn(MyClass *  parent);
    virtual ~VirtualSerializeFn() noexcept;

    VirtualSerializeFn &  operator=(const VirtualSerializeFn &  other);
    VirtualSerializeFn &  operator=(VirtualSerializeFn &&  other) noexcept;

    virtual void  setFunctionName(std::string const &  value) override;
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
