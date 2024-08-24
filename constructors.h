#pragma once

#ifndef XU_CONSTRUCTORS_H_
#define XU_CONSTRUCTORS_H_

#include <string>
#include <vector>
#include "functions.h"

namespace xu {

class Constructors;

class MyClass;
class EObject;
class Function;

class Constructors : public Functions
{

public:

    Constructors(const Constructors &  other);
    Constructors(Constructors &&  other) noexcept;
    Constructors(MyClass *  parent = nullptr);
    virtual ~Constructors() noexcept;

    Constructors &  operator=(const Constructors &  other);
    Constructors &  operator=(Constructors &&  other) noexcept;

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
