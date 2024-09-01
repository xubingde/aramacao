#pragma once

#ifndef XU_NOTEQFN_H_
#define XU_NOTEQFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class NotEqFn;

class MyClass;
class EObject;
class Parameter;

class NotEqFn : public Function
{

public:

    NotEqFn();
    NotEqFn(const NotEqFn &  other);
    NotEqFn(NotEqFn &&  other) noexcept;
    NotEqFn(std::string const &  classname, MyClass *  parent);
    virtual ~NotEqFn() noexcept;

    NotEqFn &  operator=(const NotEqFn &  other);
    NotEqFn &  operator=(NotEqFn &&  other) noexcept;

    virtual void  setFunctionName(std::string const &  value) override;
    virtual void  setParam(std::vector<Parameter> const &) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;
    virtual void  setParentClassPtr(MyClass *  value) override;
    virtual std::string  autoCode() const override;
    virtual void  init() override;

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

    std::string     m_className;
};

}

#endif
