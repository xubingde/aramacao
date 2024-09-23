#pragma once

#ifndef XU_MYCLASS_H_
#define XU_MYCLASS_H_

#include <string>
#include <string_view>
#include <utility>
#include <memory>
#include <tuple>
#include <map>
#include <set>
#include <vector>
#include "eobject.h"
#include "tpl.h"
#include "field.h"

namespace xu {

class MyClass;

class Module;

class MyClass : public EObject
{

public:

    MyClass();
    MyClass(const MyClass &  other);
    MyClass(MyClass &&  other) noexcept;
    virtual ~MyClass() noexcept;

    MyClass &  operator=(const MyClass &  other);
    MyClass &  operator=(MyClass &&  other) noexcept;

    std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  getEObjectRef();
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  getEObjectPtr();
    std::vector<std::shared_ptr<Field>> &  getFieldRef();
    virtual std::string  toHBlock(std::string const &  tabStr = std::string()) const override;
    virtual std::string  toCppBlock(std::string const & = std::string()) const override;
    virtual std::string  declaration(std::string const &  tabStr = std::string()) const override;
    virtual std::string  friendDeclaration(std::string const &  tabStr = std::string()) const override;
    std::string  definition(std::string const &  tabStr = std::string()) const;
    std::string  toFCodeEq() const;
    std::string  toFCodeLess() const;
    std::string  toFCodeSwap() const;
    std::string  toFCodeToString() const;
    std::string  toFCodeFromString() const;
    virtual void  appendField(Field const &  value);
    virtual void  appendField(Field &&  value);
    virtual bool  updateField(Field const &  value, size_t const  index);
    virtual bool  updateField(Field &&  value, size_t const  index);
    virtual void  insertField(Field const &  value, size_t  index);
    virtual void  insertField(Field &&  value, size_t  index);
    virtual bool  deleteField(size_t const  index);
    virtual bool  takeField(Field &  result, size_t const  index);
    virtual bool  swapField(size_t const  idxLhs, size_t const  idxRhs);
    virtual bool  moveField(size_t &  idxFrom, size_t &  idxTo);
    virtual void  clearField();
    virtual void  appendMulInhClass(std::tuple<std::string, Purview, bool> const &  value);
    virtual void  appendMulInhClass(std::tuple<std::string, Purview, bool> &&  value);
    virtual bool  updateMulInhClass(std::tuple<std::string, Purview, bool> const &  value, size_t const  index);
    virtual bool  updateMulInhClass(std::tuple<std::string, Purview, bool> &&  value, size_t const  index);
    virtual void  insertMulInhClass(std::tuple<std::string, Purview, bool> const &  value, size_t  index);
    virtual void  insertMulInhClass(std::tuple<std::string, Purview, bool> &&  value, size_t  index);
    virtual bool  deleteMulInhClass(size_t const  index);
    virtual bool  takeMulInhClass(std::tuple<std::string, Purview, bool> &  result, size_t const  index);
    virtual bool  swapMulInhClass(size_t const  indexLhs, size_t const  indexRhs);
    virtual bool  moveMulInhClass(size_t &  indexFrom, size_t &  indexTo);
    virtual void  clearMulInhClass();
    virtual bool  appendEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value);
    virtual bool  appendEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value);
    virtual bool  updateEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value, size_t const  index);
    virtual bool  updateEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value, size_t const  index);
    virtual bool  insertEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value, size_t  index);
    virtual bool  insertEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value, size_t  index);
    virtual bool  deleteEobjList(size_t const  index);
    virtual bool  takeEobjList(std::pair<Etype, std::shared_ptr<EObject>> &  result, size_t const  index);
    virtual bool  swapEobjList(size_t const  indexLhs, size_t const  indexRhs);
    virtual bool  moveEobjList(size_t &  indexFrom, size_t &  indexTo);

    std::vector<size_t>  getStringErr() const;

    Module *  getParentModulePtr() const;
    virtual void  setParentModulePtr(Module *  value);

    std::vector<std::pair<Etype, std::shared_ptr<EObject>>>  getEobjList() const;

    std::vector<std::shared_ptr<Field>>  getField() const;

    std::vector<size_t>  getStyleField() const;
    virtual void  setStyleField(const std::vector<size_t> &  value);

    std::vector<size_t>  getIDField() const;
    virtual void  setIDField(const std::vector<size_t> &  value);

    std::vector<size_t>  getSerzField() const;
    virtual void  setSerzField(const std::vector<size_t> &  value);

    std::string  getClassName() const;
    virtual void  setClassName(const std::string &  value);

    std::string  getReplaceClassName() const;
    virtual void  setReplaceClassName(const std::string &  value);
    virtual void  setReplaceClassName(std::string &&  value);

    std::string  getDocment() const;
    virtual void  setDocment(const std::string &  value);
    virtual void  setDocment(std::string &&  value);

    std::string  getTestCode() const;
    virtual void  setTestCode(const std::string &  value);
    virtual void  setTestCode(std::string &&  value);

    ClassType  getClasstype() const;
    virtual void  setClasstype(const ClassType  value);

    int  getAlignByte() const;
    virtual void  setAlignByte(const int  value);

    std::string  getBaseClassPrarm() const;
    virtual void  setBaseClassPrarm(const std::string &  value);

    std::pair<std::string, bool>  getBaseClassFirst() const;
    virtual void  setBaseClassFirst(const std::pair<std::string, bool> &  value);

    std::vector<std::tuple<std::string, Purview, bool>>  getMulInhClass() const;

    InheritID  getInheritID() const;
    virtual void  setInheritID(const InheritID  value);

    std::vector<Tpl>  getClassTparam() const;
    virtual void  setClassTparam(const std::vector<Tpl> &  value);
    virtual void  setClassTparam(std::vector<Tpl> &&  value);

    std::string  getAttribute() const;
    virtual void  setAttribute(const std::string &  value);
    virtual void  setAttribute(std::string &&  value);

    std::vector<std::string>  getFriendClassName() const;
    virtual void  setFriendClassName(const std::vector<std::string> &  value);
    virtual void  setFriendClassName(std::vector<std::string> &&  value);

    std::string  getHBeginBefore() const;
    virtual void  setHBeginBefore(const std::string &  value);
    virtual void  setHBeginBefore(std::string &&  value);

    std::string  getHBeginBehind() const;
    virtual void  setHBeginBehind(const std::string &  value);
    virtual void  setHBeginBehind(std::string &&  value);

    std::string  getHEndBefore() const;
    virtual void  setHEndBefore(const std::string &  value);
    virtual void  setHEndBefore(std::string &&  value);

    std::string  getHEndBehind() const;
    virtual void  setHEndBehind(const std::string &  value);
    virtual void  setHEndBehind(std::string &&  value);

    std::string  getBeforeDcl() const;
    virtual void  setBeforeDcl(const std::string &  value);
    virtual void  setBeforeDcl(std::string &&  value);

    std::string  getBehindDcl() const;
    virtual void  setBehindDcl(const std::string &  value);
    virtual void  setBehindDcl(std::string &&  value);

    bool  isUpdateToString() const;
    virtual void  setUpdateToString(const bool  value);

    bool  isFinalClass() const;
    virtual void  setFinalClass(const bool  value);

    bool  isTemplate() const;
    virtual void  setTemplate(const bool  value);

    bool  isUpdateFilename() const;
    virtual void  setUpdateFilename(const bool  value);

    bool  isSetterReturnThis() const;
    virtual void  setSetterReturnThis(const bool  value);

    bool  isImpl() const;
    virtual void  setImpl(const bool  value);

    bool  hasLessFunction() const;
    virtual void  setLessFunction(const bool  value);

    bool  hasEqFunction() const;
    virtual void  setEqFunction(const bool  value);

    bool  hasSwapFunction() const;
    virtual void  setSwapFunction(const bool  value);

    bool  hasToStringFunction() const;
    virtual void  setToStringFunction(const bool  value);

    bool  isInternal() const;
    virtual void  setInternal(const bool  value);

    bool  isIndPublicLabel() const;
    virtual void  setIndPublicLabel(const bool  value);

    bool  hasDefCtor() const;
    virtual void  setDefCtor(const bool  value);

    bool  hasCopyCtor() const;
    virtual void  setCopyCtor(const bool  value);

    bool  hasMoveCtor() const;
    virtual void  setMoveCtor(const bool  value);

    bool  hasDtor() const;
    virtual void  setDtor(const bool  value);

    bool  hasCopyOpEq() const;
    virtual void  setCopyOpEq(const bool  value);

    bool  hasMoveOpEq() const;
    virtual void  setMoveOpEq(const bool  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    std::string  toFCodeEqIndex(Field const &  fd, std::string const &  tab, std::string const &  lhsName, std::string const &  rhsName) const;
    std::string  toFCodeLessIndex(Field const &  fd, std::string const &  tab, std::string const &  lhsName, std::string const &  rhsName) const;
    std::string  toFCodeToStringIndex(Field const &  fd) const;
    std::string  toFCodeFromStringIndex(Field const &  fd, size_t const  vi_index) const;
    void  updateBaseClassName();
    void  appendFieldIndex();
    void  updateFieldIndex(size_t const  index);
    void  insertFieldIndex(size_t const  index);
    void  deleteFieldIndex(size_t const  index);
    void  appendMulInhClassIndex();
    void  insertMulInhClassIndex(size_t const  index);
    void  deleteMulInhClassIndex(size_t const  index);
    bool  checkEobject(std::pair<Etype, std::shared_ptr<EObject>> const &  value) const;
    bool  checkDeleteEobject(size_t const  index) const;
    std::string  class_field_toHBlock(std::string const &  tabStr = std::string()) const;
    std::string  class_field_FnDcl(bool const  isPubLabel = true, std::string const &  tabStr = std::string()) const;
    std::string  class_begin(std::string const &  tabStr = std::string()) const;
    std::string  class_end(std::string const &  tabStr = std::string()) const;
    std::string  class_friend(std::string const &  tabStr = std::string()) const;
    std::string  class_tplStringNotDefVal(const size_t  index = 0) const;
    void  classToInternal(MyClass *  myClass, bool const  isInternal);
    void  copyEobjList();
    void  moveEobjList();
    void  copyField();
    void  moveField();

    std::vector<size_t>     m_stringErr;
    Module *        m_parentModulePtr;
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>>  m_eobjList;
    std::vector<std::shared_ptr<Field>>     m_field;
    std::vector<size_t>     m_styleField;
    std::vector<size_t>     m_IDField;
    std::vector<size_t>     m_serzField;
    std::string     m_className;
    std::string     m_replaceClassName;
    std::string     m_docment;
    std::string     m_testCode;
    ClassType       m_classtype;
    int             m_alignByte;
    std::string     m_baseClassPrarm;
    std::pair<std::string, bool>    m_baseClassFirst;
    std::vector<std::tuple<std::string, Purview, bool>>     m_mulInhClass;
    InheritID       m_inheritID;
    std::vector<Tpl>    m_classTparam;
    std::string     m_attribute;
    std::vector<std::string>    m_friendClassName;
    std::string     m_hBeginBefore;
    std::string     m_hBeginBehind;
    std::string     m_hEndBefore;
    std::string     m_hEndBehind;
    std::string     m_beforeDcl;
    std::string     m_behindDcl;
    bool            m_updateToString;
    bool            m_finalClass;
    bool            m_template;
    bool            m_updateFilename;
    bool            m_setterReturnThis;
    bool            m_impl;
    bool            m_lessFunction;
    bool            m_eqFunction;
    bool            m_swapFunction;
    bool            m_toStringFunction;
    bool            m_internal;
    bool            m_indPublicLabel;
    bool            m_defCtor;
    bool            m_copyCtor;
    bool            m_moveCtor;
    bool            m_dtor;
    bool            m_copyOpEq;
    bool            m_moveOpEq;
};

}

#endif
