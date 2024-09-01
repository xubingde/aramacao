#pragma once

#ifndef XU_EXTSWAPFN_H_
#define XU_EXTSWAPFN_H_

#include <string>
#include <vector>
#include "function.h"

namespace xu {

class ExtSwapFn;

class MyClass;
class EObject;
class Parameter;

class ExtSwapFn : public Function
{

public:

    ExtSwapFn();
    ExtSwapFn(const ExtSwapFn &  other);
    ExtSwapFn(ExtSwapFn &&  other) noexcept;
    ExtSwapFn(std::string const &  classname, MyClass *  parent);
    virtual ~ExtSwapFn() noexcept;

    ExtSwapFn &  operator=(const ExtSwapFn &  other);
    ExtSwapFn &  operator=(ExtSwapFn &&  other) noexcept;

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
