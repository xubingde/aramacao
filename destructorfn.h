#pragma once

#ifndef XU_DESTRUCTORFN_H_
#define XU_DESTRUCTORFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class DestructorFn;

class MyClass;
class EObject;

class DestructorFn : public Function
{

public:

    DestructorFn();
    DestructorFn(const DestructorFn &  other);
    DestructorFn(DestructorFn &&  other) noexcept;
    DestructorFn(MyClass *  parent);
    virtual ~DestructorFn() noexcept;

    DestructorFn &  operator=(const DestructorFn &  other);
    DestructorFn &  operator=(DestructorFn &&  other) noexcept;

    virtual std::string  autoCode() const override;
    virtual void  setFunctionName(std::string const &) override;
    virtual void  setParentClassPtr(MyClass *  value) override;

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    void  updateDefualtValue();
    void  init();
};

}

#endif
