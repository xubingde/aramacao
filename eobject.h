#pragma once

#ifndef XU_EOBJECT_H_
#define XU_EOBJECT_H_

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <utility>

namespace xu {

enum class Action {
    get = 0,
    setCopy = 1,
    setMove = 2,
    setConstValue = 3,
    setMutValue = 4,
    is = 5,
    has = 6,
    none = 9999
};

enum class Purview {
    purPublic,
    purProtected,
    purPrivate
};

enum class ClassType {
    cppFinal,
    cppBase,
    cppInherit
};

enum class InheritID {
    baseId,
    inheritId,
    borthId
};

enum class CopyCtorWay {
    yes,
    no,
    isDefault,
    isDelete
};

enum class MoveCtorWay {
    yes,
    no,
    isDelete
};

enum class Etype {
    eObject = 0,
    eBasicBlock = 1,
    eFunction = 2,
    eFunctions = 3,
    eStaticFunctions = 4,
    eConstexprFunctions = 5,
    eTplFunctions = 6,
    eTplStaticFunctions = 7,
    eTplConstexprFunctions = 8,
    eClass = 9,
    eClassDeclaration = 10,
    eEnum = 11,
    eStruct = 12,
    eStructDeclaration = 13,
    eTypedef = 14,
    eConstructors = 15,
    eTplConstructors = 16,
    eLabel = 17,
    ePublicLabel = 18,
    eProtectedLabel = 19,
    ePrivateLabel = 20,
    eDefaultConstructorFn = 25,
    eCopyConstructorFn = 26,
    eMoveConstructorFn = 27,
    eDestructorFn = 28,
    eCopyOperatorEqFn = 29,
    eMoveOperatorEqFn = 30,
    eActFn = 38,
    eActGetFn = 39,
    eActSetCopyFn = 40,
    eActSetMoveFn = 41,
    eActSetConstValueFn = 42,
    eActSetMutValueFn = 43,
    eActIsFn = 44,
    eActHasFn = 45,
    eEqFn = 55,
    eNotEqFn = 56,
    eVirtualEqFn = 57,
    eLessFn = 58,
    eLessEqFn = 59,
    eVirtualLessFn = 60,
    eGreaterFn = 61,
    eGreaterEqFn = 62,
    eExtSwapFn = 63,
    eInSwapFn = 64,
    eVirtualExchangeFn = 65,
    eToStringFn = 66,
    eVirtualSerializeFn = 67,
    eExtFromStringFn = 68,
    eInFromStringFn = 69,
    eDeserializeFn = 70,
    eModule = 100,
    eProject = 101
};

class EObject;

class ActFn;
class Field;

std::string  toString(std::vector<std::pair<Etype, std::shared_ptr<EObject>>> const &  value);
bool  fromString(std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  res, std::string const &  value);
bool  fromString(std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  res, std::string_view const &  value);
bool  fromString(std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  res, char const *  data, size_t const  size);
std::string  toString(std::vector<std::pair<Action, std::shared_ptr<ActFn>>> const &  value);
bool  fromString(std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  res, std::string const &  value);
bool  fromString(std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  res, std::string_view const &  value);
bool  fromString(std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  res, char const *  data, size_t const  size);
std::string  toString(std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>> const &  value);
bool  fromString(std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>> &  res, std::string const &  value);
bool  fromString(std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>> &  res, std::string_view const &  value);
bool  fromString(std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>> &  res, char const *  data, size_t const  size);
std::string  toString(std::vector<std::shared_ptr<Field>> const &  value);
bool  fromString(std::vector<std::shared_ptr<Field>> &  res, std::string const &  value);
bool  fromString(std::vector<std::shared_ptr<Field>> &  res, std::string_view const &  value);
bool  fromString(std::vector<std::shared_ptr<Field>> &  res, char const *  data, size_t const  size);
std::string  toActionString(Action const  act);
Action  fromActionString(std::string const &  val);

bool  operator==(const EObject &  lhs, const EObject &  rhs);
bool  operator!=(const EObject &  lhs, const EObject &  rhs);
bool  swap(EObject &  lhs, EObject &  rhs) noexcept;
bool  operator<(const EObject &  lhs, const EObject &  rhs);
bool  operator<=(const EObject &  lhs, const EObject &  rhs);
bool  operator>(const EObject &  lhs, const EObject &  rhs);
bool  operator>=(const EObject &  lhs, const EObject &  rhs);
bool  fromString(EObject &  value, const char *  data, const size_t  size);

class EObject
{
friend bool  operator==(const EObject &  lhs, const EObject &  rhs);
friend bool  operator!=(const EObject &  lhs, const EObject &  rhs);
friend bool  operator<(const EObject &  lhs, const EObject &  rhs);
friend bool  operator<=(const EObject &  lhs, const EObject &  rhs);
friend bool  operator>(const EObject &  lhs, const EObject &  rhs);
friend bool  operator>=(const EObject &  lhs, const EObject &  rhs);

public:

    EObject();
    EObject(const EObject &  other);
    EObject(EObject &&  other) noexcept;
    virtual ~EObject() noexcept;

    EObject &  operator=(const EObject &  other);
    EObject &  operator=(EObject &&  other) noexcept;

    std::string  toString() const;
    bool  fromString(const char *  data, const size_t  size);
    bool  swap(EObject &  value) noexcept;

    virtual std::string  toHBlock(std::string const &  tabStr = std::string()) const;
    virtual std::string  toCppBlock(std::string const &  tabStr = std::string()) const;
    virtual std::string  declaration(std::string const &  tabStr = std::string()) const;
    virtual std::string  friendDeclaration(std::string const &  tabStr = std::string()) const;

    std::string  getTreeLabel() const;

    Etype  getBaseType() const;

    int  getId() const;
    void  setId(const int  value);

protected:

    void  setTreeLabel(std::string const &  value);
    void  setTreeLabel(std::string &&  value);
    void  setBaseType(Etype const  value);

    virtual bool  equal(const EObject &  value) const;
    virtual bool  less(const EObject &  value) const;
    virtual bool  exchange(EObject &  value) noexcept;
    virtual std::string  serialize() const;
    virtual bool  deserialize(const char *  data, const size_t  size);

private:

    std::string     m_treeLabel;
    Etype           m_baseType;
    int             m_id;
};

}

#endif
