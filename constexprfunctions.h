#pragma once

#ifndef XU_CONSTEXPRFUNCTIONS_H_
#define XU_CONSTEXPRFUNCTIONS_H_

#include <string>
#include <vector>
#include "functions.h"

namespace xu {

class ConstexprFunctions;

class MyClass;
class EObject;
class Function;

class ConstexprFunctions : public Functions
{

public:

    ConstexprFunctions(const ConstexprFunctions &  other);
    ConstexprFunctions(ConstexprFunctions &&  other) noexcept;
    ConstexprFunctions(MyClass *  parent = nullptr);
    virtual ~ConstexprFunctions() noexcept;

    ConstexprFunctions &  operator=(const ConstexprFunctions &  other);
    ConstexprFunctions &  operator=(ConstexprFunctions &&  other) noexcept;

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
