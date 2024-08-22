#pragma once

#ifndef XU_FUNCTIONS_H_
#define XU_FUNCTIONS_H_

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include "function.h"
#include "eobject.h"

namespace xu {

class Functions;

class MyClass;

std::string  toString(std::vector<std::shared_ptr<Function>> const &  value);
bool  fromString(std::vector<std::shared_ptr<Function>> &  res, std::string const &  value);
bool  fromString(std::vector<std::shared_ptr<Function>> &  res, std::string_view const &  value);
bool  fromString(std::vector<std::shared_ptr<Function>> &  res, char const *  data, size_t const  size);

class Functions : public EObject
{

public:

    Functions(const Functions &  other);
    Functions(Functions &&  other) noexcept;
    Functions(MyClass *  parent = nullptr);
    virtual ~Functions() noexcept;

    Functions &  operator=(const Functions &  other);
    Functions &  operator=(Functions &&  other) noexcept;

    virtual std::string  toHBlock(std::string const & = std::string()) const override;
    virtual std::string  toCppBlock(std::string const &  tabStr = std::string()) const override;
    virtual std::string  declaration(std::string const &  tabStr = std::string()) const override;
    std::vector<std::shared_ptr<Function>> &  getFunctionRef();
    std::vector<std::shared_ptr<Function>> *  getFunctionPtr();
    void  enterClass(MyClass *  classPtr);
    void  leaveClass();
    bool  getFunction(Function &  result, const size_t  index) const;
    bool  takeFunction(Function &  result, const size_t  index);
    std::shared_ptr<Function>  appendFunction(const Function &  value);
    bool  updateFunction(const Function &  fn, const size_t  index);
    void  insertFunction(const Function &  fn, size_t  index);
    bool  deleteFunction(const size_t  index);
    bool  swapFunction(const size_t  indexLhs, const size_t  indexRhs);
    bool  moveFunction(size_t &  indexFrom, size_t &  indexTo);
    void  clearFunction();

    std::vector<std::shared_ptr<Function>>  getObjList() const;
    virtual void  setObjList(const std::vector<std::shared_ptr<Function>> &  value);

    MyClass *  getParentClassPtr() const;
    virtual void  setParentClassPtr(MyClass *  value);

protected:

    virtual void  procFunction(Function &  fn);

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    std::vector<std::shared_ptr<Function>>      m_objList;
    MyClass *       m_parentClassPtr;
};

}

#endif
