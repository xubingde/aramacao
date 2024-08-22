#pragma once

#ifndef XU_TPLFUNCTIONS_H_
#define XU_TPLFUNCTIONS_H_

#include <string>
#include <vector>
#include "functions.h"

namespace xu {

class TplFunctions;

class MyClass;
class EObject;
class Function;

class TplFunctions : public Functions
{

public:

    TplFunctions(const TplFunctions &  other);
    TplFunctions(TplFunctions &&  other) noexcept;
    TplFunctions(MyClass *  parent = nullptr);
    virtual ~TplFunctions() noexcept;

    TplFunctions &  operator=(const TplFunctions &  other);
    TplFunctions &  operator=(TplFunctions &&  other) noexcept;

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
