#pragma once

#ifndef XU_DESERIALIZEFN_H_
#define XU_DESERIALIZEFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class DeserializeFn;

class MyClass;
class EObject;

class DeserializeFn : public Function
{

public:

    DeserializeFn();
    DeserializeFn(const DeserializeFn &  other);
    DeserializeFn(DeserializeFn &&  other) noexcept;
    DeserializeFn(MyClass *  parent);
    virtual ~DeserializeFn() noexcept;

    DeserializeFn &  operator=(const DeserializeFn &  other);
    DeserializeFn &  operator=(DeserializeFn &&  other) noexcept;

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
