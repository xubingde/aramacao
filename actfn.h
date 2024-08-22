#pragma once

#ifndef XU_ACTFN_H_
#define XU_ACTFN_H_

#include <string>
#include <vector>
#include "function.h"
#include "eobject.h"

namespace xu {

class ActFn;

class MyClass;
class Field;
class EObject;
class Parameter;

class ActFn : public Function
{

public:

    ActFn();
    ActFn(const ActFn &  other);
    ActFn(ActFn &&  other) noexcept;
    ActFn(MyClass *  parentClass, Field *  parentField);
    virtual ~ActFn() noexcept;

    ActFn &  operator=(const ActFn &  other);
    ActFn &  operator=(ActFn &&  other) noexcept;

    virtual std::string  autoCode() const override;
    virtual void  setReturnType(std::string const &  value) override;
    virtual void  setReturnType(std::string &&  value) override;
    virtual void  setFunctionName(std::string const &  value) override;
    virtual void  setParam(std::vector<Parameter> const &  value) override;
    virtual void  setParam(std::vector<Parameter> &&  value) override;

    Action  getAction() const;
    virtual void  setAction(const Action  value);

    Field *  getParentFieldPtr() const;
    virtual void  setParentFieldPtr(Field *  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    void  init();

    Action          m_action;
    Field *         m_parentFieldPtr;
};

}

#endif
