#pragma once

#ifndef XU_EQFN_H_
#define XU_EQFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class EqFn;

class MyClass;
class EObject;
class Parameter;

class EqFn : public Function
{

public:

    EqFn();
    EqFn(const EqFn &  other);
    EqFn(EqFn &&  other) noexcept;
    EqFn(std::string const &  classname, MyClass *  parent);
    virtual ~EqFn() noexcept;

    EqFn &  operator=(const EqFn &  other);
    EqFn &  operator=(EqFn &&  other) noexcept;

    virtual void  setFunctionName(std::string const &  value) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;
    virtual void  setParentClassPtr(MyClass *  value) override;
    virtual std::string  autoCode() const override;

    std::string  getClassName() const;
    virtual void  setClassName(const std::string &  value);
    virtual void  setClassName(std::string &&  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    void  init();

    std::string     m_className;
};

}

#endif
