#pragma once

#ifndef XU_TPLSTATICFUNCTIONS_H_
#define XU_TPLSTATICFUNCTIONS_H_

#include <string>
#include <vector>
#include "tplfunctions.h"

namespace xu {

class TplStaticFunctions;

class MyClass;
class EObject;
class Function;

class TplStaticFunctions : public TplFunctions
{

public:

    TplStaticFunctions(const TplStaticFunctions &  other);
    TplStaticFunctions(TplStaticFunctions &&  other) noexcept;
    TplStaticFunctions(MyClass *  parent = nullptr);
    virtual ~TplStaticFunctions() noexcept;

    TplStaticFunctions &  operator=(const TplStaticFunctions &  other);
    TplStaticFunctions &  operator=(TplStaticFunctions &&  other) noexcept;

    virtual void  procFunction(Function &  fn) override;

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
