#pragma once

#ifndef XU_STATICFUNCTIONS_H_
#define XU_STATICFUNCTIONS_H_

#include <string>
#include <vector>
#include "functions.h"

namespace xu {

class StaticFunctions;

class MyClass;
class EObject;
class Function;

class StaticFunctions : public Functions
{

public:

    StaticFunctions(const StaticFunctions &  other);
    StaticFunctions(StaticFunctions &&  other) noexcept;
    StaticFunctions(MyClass *  parent = nullptr);
    virtual ~StaticFunctions() noexcept;

    StaticFunctions &  operator=(const StaticFunctions &  other);
    StaticFunctions &  operator=(StaticFunctions &&  other) noexcept;

protected:

    virtual void  procFunction(Function &  fn) override;

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:
};

}

#endif
