#pragma once

#ifndef XU_TPLCONSTEXPRFUNCTIONS_H_
#define XU_TPLCONSTEXPRFUNCTIONS_H_

#include <string>
#include <vector>
#include "tplfunctions.h"

namespace xu {

class TplConstexprFunctions;

class MyClass;
class EObject;
class Function;

class TplConstexprFunctions : public TplFunctions
{

public:

    TplConstexprFunctions(const TplConstexprFunctions &  other);
    TplConstexprFunctions(TplConstexprFunctions &&  other) noexcept;
    TplConstexprFunctions(MyClass *  parent = nullptr);
    virtual ~TplConstexprFunctions() noexcept;

    TplConstexprFunctions &  operator=(const TplConstexprFunctions &  other);
    TplConstexprFunctions &  operator=(TplConstexprFunctions &&  other) noexcept;

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
