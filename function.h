#pragma once

#ifndef XU_FUNCTION_H_
#define XU_FUNCTION_H_

#include <string>
#include <string_view>
#include <tuple>
#include <vector>
#include <set>
#include <utility>
#include "eobject.h"
#include "parameter.h"
#include "tpl.h"

namespace xu {

class Function;

class MyClass;

class Function : public EObject
{

public:

    Function();
    Function(const Function &  other);
    Function(Function &&  other) noexcept;
    Function(MyClass *  parent);
    virtual ~Function() noexcept;

    Function &  operator=(const Function &  other);
    Function &  operator=(Function &&  other) noexcept;

    virtual std::string  toHBlock(std::string const &  tabStr = std::string()) const override;
    virtual std::string  toCppBlock(std::string const &  tabStr = std::string()) const override;
    virtual std::string  declaration(std::string const &  tabStr = std::string()) const override;
    virtual std::string  friendDeclaration(std::string const &  tabStr = std::string()) const override;
    std::string  definition(std::string const &  tabStr = std::string()) const;
    std::string  declLabel() const;
    std::string  updateAutoCode(std::string const &  tabStr = std::string()) const;
    std::string  updateMCode(std::string const &  code, std::string const &  tabStr = std::string(), bool const  hasInsertObj = false) const;
    virtual std::string  autoCode() const;

    std::vector<size_t>  getStringErr() const;

    MyClass *  getParentClassPtr() const;
    virtual void  setParentClassPtr(MyClass *  value);

    std::string  getFunctionName() const;
    virtual void  setFunctionName(const std::string &  value);

    std::string  getDocment() const;
    virtual void  setDocment(const std::string &  value);
    virtual void  setDocment(std::string &&  value);

    std::string  getTestCode() const;
    virtual void  setTestCode(const std::string &  value);
    virtual void  setTestCode(std::string &&  value);

    std::string  getMCode() const;
    virtual void  setMCode(const std::string &  value);
    virtual void  setMCode(std::string &&  value);

    std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>>  getInsertMCode() const;
    void  setInsertMCode(const std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>> &  value);

    std::vector<size_t>  getStrike() const;
    virtual void  setStrike(const std::vector<size_t> &  value);

    std::vector<std::pair<size_t, std::string>>  getNewCode() const;
    virtual void  setNewCode(const std::vector<std::pair<size_t, std::string>> &  value);

    std::string  getReturnType() const;
    virtual void  setReturnType(const std::string &  value);
    virtual void  setReturnType(std::string &&  value);

    std::string  getHReturnTypeBehind() const;
    virtual void  setHReturnTypeBehind(const std::string &  value);

    std::string  getHReturnTypeBehind2() const;
    virtual void  setHReturnTypeBehind2(const std::string &  value);

    std::string  getReturnTypeDoc() const;
    virtual void  setReturnTypeDoc(const std::string &  value);
    virtual void  setReturnTypeDoc(std::string &&  value);

    std::vector<Parameter>  getParam() const;
    virtual void  setParam(const std::vector<Parameter> &  value);
    virtual void  setParam(std::vector<Parameter> &&  value);

    std::vector<Tpl>  getTparam() const;
    virtual void  setTparam(const std::vector<Tpl> &  value);
    virtual void  setTparam(std::vector<Tpl> &&  value);

    std::string  getInhValueFirst() const;
    virtual void  setInhValueFirst(const std::string &  value);
    virtual void  setInhValueFirst(std::string &&  value);

    std::vector<std::string>  getInhValueBaseClass() const;
    virtual void  setInhValueBaseClass(const std::vector<std::string> &  value);

    std::vector<std::string>  getDefValueCtor() const;
    virtual void  setDefValueCtor(const std::vector<std::string> &  value);

    std::string  getAttribute() const;
    virtual void  setAttribute(const std::string &  value);
    virtual void  setAttribute(std::string &&  value);

    std::string  getHBefore() const;
    virtual void  setHBefore(const std::string &  value);
    virtual void  setHBefore(std::string &&  value);

    std::string  getHBehind() const;
    virtual void  setHBehind(const std::string &  value);
    virtual void  setHBehind(std::string &&  value);

    std::string  getCppBefore() const;
    virtual void  setCppBefore(const std::string &  value);
    virtual void  setCppBefore(std::string &&  value);

    std::string  getCppBehind() const;
    virtual void  setCppBehind(const std::string &  value);
    virtual void  setCppBehind(std::string &&  value);

    std::vector<std::string>  getFriendClassName() const;
    virtual void  setFriendClassName(const std::vector<std::string> &  value);

    bool  isClassFunction() const;
    virtual void  setClassFunction(const bool  value);

    bool  isConstructor() const;
    virtual void  setConstructor(const bool  value);

    bool  isAutoSource() const;
    virtual void  setAutoSource(const bool  value);

    bool  isTemplate() const;
    virtual void  setTemplate(const bool  value);

    bool  isInline() const;
    virtual void  setInline(const bool  value);

    bool  isConstexpr() const;
    virtual void  setConstexpr(const bool  value);

    bool  isStatic() const;
    virtual void  setStatic(const bool  value);

    bool  isExplicit() const;
    virtual void  setExplicit(const bool  value);

    bool  isVirtual() const;
    virtual void  setVirtual(const bool  value);

    bool  isSourceinH() const;
    virtual void  setSourceinH(const bool  value);

    bool  isEnabled() const;
    virtual void  setEnabled(const bool  value);

    bool  isConst() const;
    virtual void  setConst(const bool  value);

    bool  isNoexcept() const;
    virtual void  setNoexcept(const bool  value);

    bool  isOverride() const;
    virtual void  setOverride(const bool  value);

    bool  isFinal() const;
    virtual void  setFinal(const bool  value);

    bool  isEqDefault() const;
    virtual void  setEqDefault(const bool  value);

    bool  isEqDelete() const;
    virtual void  setEqDelete(const bool  value);

    bool  isRef() const;
    virtual void  setRef(const bool  value);

    bool  isRefRef() const;
    virtual void  setRefRef(const bool  value);

    bool  isPureVirtual() const;
    virtual void  setPureVirtual(const bool  value);

    bool  isInternal() const;
    virtual void  setInternal(const bool  value);

    bool  isDecSpaceLine() const;
    virtual void  setDecSpaceLine(const bool  value);

protected:

    std::string  friendDecl(std::string const &  tabStr, bool const  isFriendFn) const;

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    std::string  multipleInh() const;
    void  init();

    std::vector<size_t>     m_stringErr;
    MyClass *       m_parentClassPtr;
    std::string     m_functionName;
    std::string     m_docment;
    std::string     m_testCode;
    std::string     m_mCode;
    std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>>  m_insertMCode;
    std::vector<size_t>     m_strike;
    std::vector<std::pair<size_t, std::string>>     m_newCode;
    std::string     m_returnType;
    std::string     m_hReturnTypeBehind;
    std::string     m_hReturnTypeBehind2;
    std::string     m_returnTypeDoc;
    std::vector<Parameter>      m_param;
    std::vector<Tpl>    m_tparam;
    std::string     m_inhValueFirst;
    std::vector<std::string>    m_inhValueBaseClass;
    std::vector<std::string>    m_defValueCtor;
    std::string     m_attribute;
    std::string     m_hBefore;
    std::string     m_hBehind;
    std::string     m_cppBefore;
    std::string     m_cppBehind;
    std::vector<std::string>    m_friendClassName;
    bool            m_classFunction;
    bool            m_constructor;
    bool            m_autoSource;
    bool            m_template;
    bool            m_inline;
    bool            m_constexpr;
    bool            m_static;
    bool            m_explicit;
    bool            m_virtual;
    bool            m_sourceinH;
    bool            m_enabled;
    bool            m_const;
    bool            m_noexcept;
    bool            m_override;
    bool            m_final;
    bool            m_eqDefault;
    bool            m_eqDelete;
    bool            m_ref;
    bool            m_refRef;
    bool            m_pureVirtual;
    bool            m_internal;
    bool            m_decSpaceLine;
};

}

#endif
