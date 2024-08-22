#pragma once

#ifndef XU_TPLCONSTRUCTORS_H_
#define XU_TPLCONSTRUCTORS_H_

#include <string>
#include <vector>
#include "functions.h"

namespace xu {

class TplConstructors;

class MyClass;
class EObject;
class Function;

class TplConstructors : public Functions
{

public:

    TplConstructors(const TplConstructors &  other);
    TplConstructors(TplConstructors &&  other) noexcept;
    TplConstructors(MyClass *  parent = nullptr);
    virtual ~TplConstructors() noexcept;

    TplConstructors &  operator=(const TplConstructors &  other);
    TplConstructors &  operator=(TplConstructors &&  other) noexcept;

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
