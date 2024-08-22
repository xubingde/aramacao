#pragma once

#ifndef XU_COPYCONSTRUCTORFN_H_
#define XU_COPYCONSTRUCTORFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class CopyConstructorFn;

class MyClass;
class EObject;
class Parameter;

class CopyConstructorFn : public Function
{

public:

    CopyConstructorFn();
    CopyConstructorFn(const CopyConstructorFn &  other);
    CopyConstructorFn(CopyConstructorFn &&  other) noexcept;
    CopyConstructorFn(MyClass *  parent);
    virtual ~CopyConstructorFn() noexcept;

    CopyConstructorFn &  operator=(const CopyConstructorFn &  other);
    CopyConstructorFn &  operator=(CopyConstructorFn &&  other) noexcept;

    virtual std::string  autoCode() const override;
    virtual void  setFunctionName(std::string const &  value) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;
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
