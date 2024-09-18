#include <cstring>
#include <typeinfo>
#include "eobject.h"
#include "icode.h"
#include "fmt.h"
#include "actfn.h"
#include "actgetfn.h"
#include "actsetcopyfn.h"
#include "actsetmovefn.h"
#include "actsetconstvaluefn.h"
#include "actsetmutvaluefn.h"
#include "actisfn.h"
#include "acthasfn.h"
#include "basicblock.h"
#include "function.h"
#include "functions.h"
#include "staticfunctions.h"
#include "constexprfunctions.h"
#include "tplfunctions.h"
#include "tplstaticfunctions.h"
#include "tplconstexprfunctions.h"
#include "myclass.h"
#include "myclassdec.h"
#include "myenum.h"
#include "mystruct.h"
#include "mystructdec.h"
#include "mytypedef.h"
#include "constructors.h"
#include "tplconstructors.h"
#include "label.h"
#include "publiclabel.h"
#include "protectedlabel.h"
#include "privatelabel.h"
#include "defaultconstructorfn.h"
#include "copyconstructorfn.h"
#include "moveconstructorfn.h"
#include "destructorfn.h"
#include "copyoperatoreqfn.h"
#include "moveoperatoreqfn.h"
#include "eqfn.h"
#include "noteqfn.h"
#include "virtualeqfn.h"
#include "lessfn.h"
#include "lesseqfn.h"
#include "virtuallessfn.h"
#include "greaterfn.h"
#include "greatereqfn.h"
#include "extswapfn.h"
#include "inswapfn.h"
#include "virtualexchangefn.h"
#include "tostringfn.h"
#include "virtualserializefn.h"
#include "extfromstringfn.h"
#include "infromstringfn.h"
#include "deserializefn.h"
#include "module.h"
#include "project.h"

namespace xu {

std::string
toString(std::vector<std::pair<Etype, std::shared_ptr<EObject>>> const &  value)
{
    std::string  res;
    for (auto const &  it: value) {
        std::string  resTmp;
        xu::append(resTmp, xu::toString(it.first));
        xu::append(resTmp, xu::toString(*it.second));
        xu::append(res, resTmp);
    }
    return res;
}

bool
fromString(std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  res,
           std::string const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  res,
           std::string_view const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  res,
           char const *  data,
           size_t const  size)
{
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>>  resTmp;
    auto  vi = xu::viewIcode(data, size);
    size_t const  viSize = vi.size();
    for (size_t  i = 0; i < viSize; ++i) {
        auto  vi2 = xu::viewIcode(vi[i]);
        if (vi2.size() == 2) {
            std::pair<Etype, std::shared_ptr<EObject>>  aItem;
            if (!xu::fromString(aItem.first, vi2[0]))  return false;

            switch (aItem.first) {
            case Etype::eObject :
                {
                    EObject  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<EObject>  objPtr =
                            std::make_shared<EObject>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eBasicBlock :
                {
                    BasicBlock  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<BasicBlock>  objPtr =
                            std::make_shared<BasicBlock>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eFunction :
                {
                    Function  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<Function>  objPtr =
                            std::make_shared<Function>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eFunctions :
                {
                    Functions  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<Functions>  objPtr =
                            std::make_shared<Functions>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eStaticFunctions :
                {
                    StaticFunctions  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<StaticFunctions>  objPtr =
                            std::make_shared<StaticFunctions>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eConstexprFunctions :
                {
                    ConstexprFunctions  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ConstexprFunctions>  objPtr =
                            std::make_shared<ConstexprFunctions>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eTplFunctions :
                {
                    TplFunctions  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<TplFunctions>  objPtr =
                            std::make_shared<TplFunctions>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eTplStaticFunctions :
                {
                    TplStaticFunctions  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<TplStaticFunctions>  objPtr =
                            std::make_shared<TplStaticFunctions>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eTplConstexprFunctions :
                {
                    TplConstexprFunctions  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<TplConstexprFunctions>  objPtr =
                            std::make_shared<TplConstexprFunctions>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eClass :
                {
                    MyClass  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<MyClass>  objPtr =
                            std::make_shared<MyClass>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eClassDeclaration :
                {
                    MyClassDec  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<MyClassDec>  objPtr =
                            std::make_shared<MyClassDec>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eEnum :
                {
                    MyEnum  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<MyEnum>  objPtr =
                            std::make_shared<MyEnum>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eStruct :
                {
                    MyStruct  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<MyStruct>  objPtr =
                            std::make_shared<MyStruct>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eStructDeclaration :
                {
                    MyStructDec  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<MyStructDec>  objPtr =
                            std::make_shared<MyStructDec>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eTypedef :
                {
                    MyTypedef  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<MyTypedef>  objPtr =
                            std::make_shared<MyTypedef>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eConstructors :
                {
                    Constructors  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<Constructors>  objPtr =
                            std::make_shared<Constructors>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eTplConstructors :
                {
                    TplConstructors  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<TplConstructors>  objPtr =
                            std::make_shared<TplConstructors>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eLabel :
                {
                    Label  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<Label>  objPtr =
                            std::make_shared<Label>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::ePublicLabel :
                {
                    PublicLabel  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<PublicLabel>  objPtr =
                            std::make_shared<PublicLabel>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eProtectedLabel :
                {
                    ProtectedLabel  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ProtectedLabel>  objPtr =
                            std::make_shared<ProtectedLabel>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::ePrivateLabel :
                {
                    PrivateLabel  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<PrivateLabel>  objPtr =
                            std::make_shared<PrivateLabel>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eDefaultConstructorFn :
                {
                    DefaultConstructorFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<DefaultConstructorFn>  objPtr =
                            std::make_shared<DefaultConstructorFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eCopyConstructorFn :
                {
                    CopyConstructorFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<CopyConstructorFn>  objPtr =
                            std::make_shared<CopyConstructorFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eMoveConstructorFn :
                {
                    MoveConstructorFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<MoveConstructorFn>  objPtr =
                            std::make_shared<MoveConstructorFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eDestructorFn :
                {
                    DestructorFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<DestructorFn>  objPtr =
                            std::make_shared<DestructorFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eCopyOperatorEqFn :
                {
                    CopyOperatorEqFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<CopyOperatorEqFn>  objPtr =
                            std::make_shared<CopyOperatorEqFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eMoveOperatorEqFn :
                {
                    MoveOperatorEqFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<MoveOperatorEqFn>  objPtr =
                            std::make_shared<MoveOperatorEqFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActFn :
                {
                    ActFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ActFn>  objPtr =
                            std::make_shared<ActFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActGetFn :
                {
                    ActGetFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ActGetFn>  objPtr =
                            std::make_shared<ActGetFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActSetCopyFn :
                {
                    ActSetCopyFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ActSetCopyFn>  objPtr =
                            std::make_shared<ActSetCopyFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActSetMoveFn :
                {
                    ActSetMoveFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ActSetMoveFn>  objPtr =
                            std::make_shared<ActSetMoveFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActSetConstValueFn :
                {
                    ActSetConstValueFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ActSetConstValueFn>  objPtr =
                            std::make_shared<ActSetConstValueFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActSetMutValueFn :
                {
                    ActSetMutValueFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ActSetMutValueFn>  objPtr =
                            std::make_shared<ActSetMutValueFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActIsFn :
                {
                    ActIsFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ActIsFn>  objPtr =
                            std::make_shared<ActIsFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActHasFn :
                {
                    ActHasFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ActHasFn>  objPtr =
                            std::make_shared<ActHasFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eEqFn :
                {
                    EqFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<EqFn>  objPtr =
                            std::make_shared<EqFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eNotEqFn :
                {
                    NotEqFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<NotEqFn>  objPtr =
                            std::make_shared<NotEqFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eVirtualEqFn :
                {
                    VirtualEqFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<VirtualEqFn>  objPtr =
                            std::make_shared<VirtualEqFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eLessFn :
                {
                    LessFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<LessFn>  objPtr =
                            std::make_shared<LessFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eLessEqFn :
                {
                    LessEqFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<LessEqFn>  objPtr =
                            std::make_shared<LessEqFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eVirtualLessFn :
                {
                    VirtualLessFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<VirtualLessFn>  objPtr =
                            std::make_shared<VirtualLessFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eGreaterFn :
                {
                    GreaterFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<GreaterFn>  objPtr =
                            std::make_shared<GreaterFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eGreaterEqFn :
                {
                    GreaterEqFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<GreaterEqFn>  objPtr =
                            std::make_shared<GreaterEqFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eExtSwapFn :
                {
                    ExtSwapFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ExtSwapFn>  objPtr =
                            std::make_shared<ExtSwapFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eInSwapFn :
                {
                    InSwapFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<InSwapFn>  objPtr =
                            std::make_shared<InSwapFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eVirtualExchangeFn :
                {
                    VirtualExchangeFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<VirtualExchangeFn>  objPtr =
                            std::make_shared<VirtualExchangeFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eToStringFn :
                {
                    ToStringFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ToStringFn>  objPtr =
                            std::make_shared<ToStringFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eVirtualSerializeFn :
                {
                    VirtualSerializeFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<VirtualSerializeFn>  objPtr =
                            std::make_shared<VirtualSerializeFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eExtFromStringFn :
                {
                    ExtFromStringFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<ExtFromStringFn>  objPtr =
                            std::make_shared<ExtFromStringFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eInFromStringFn :
                {
                    InFromStringFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<InFromStringFn>  objPtr =
                            std::make_shared<InFromStringFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eDeserializeFn :
                {
                    DeserializeFn  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<DeserializeFn>  objPtr =
                            std::make_shared<DeserializeFn>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eModule :
                {
                    Module  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<Module>  objPtr =
                            std::make_shared<Module>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eProject :
                {
                    Project  obj;
                    if (!xu::fromString(obj, vi2[1]))  return false;
                    std::shared_ptr<Project>  objPtr =
                            std::make_shared<Project>(std::move(obj));
                    aItem.second = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            }
            resTmp.push_back(std::move(aItem));
        } else {
            return false;
        }
    }
    res = std::move(resTmp);
    return true;
}

std::string
toString(std::vector<std::pair<Action, std::shared_ptr<ActFn>>> const &  value)
{
    std::string  res;
    for (auto const &  it: value) {
        std::string  resTmp;
        xu::append(resTmp, xu::toString(it.first));
        xu::append(resTmp, xu::toString(*it.second));
        xu::append(res, resTmp);
    }
    return res;
}

bool
fromString(std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  res,
           std::string const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  res,
           std::string_view const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  res,
           char const *  data,
           size_t const  size)
{
    std::vector<std::pair<Action, std::shared_ptr<ActFn>>>  resTmp;
    auto  vi = xu::viewIcode(data, size);
    size_t const  viSize = vi.size();
    for (size_t  i = 0; i < viSize; ++i) {
        auto  vi2 = xu::viewIcode(vi[i]);
        if (vi2.size() == 2) {
            std::pair<Action, std::shared_ptr<ActFn>>  aItem;
            if (!xu::fromString(aItem.first, vi2[0]))  return false;

            switch (aItem.first) {
            case Action::get :
                {
                    ActGetFn  fn(nullptr, nullptr);
                    if (!xu::fromString(fn, vi2[1]))  return false;
                    std::shared_ptr<ActGetFn>  fnPtr =
                            std::make_shared<ActGetFn>(std::move(fn));
                    aItem.second = std::dynamic_pointer_cast<ActFn>(fnPtr);
                }
                break;
            case Action::setCopy :
                {
                    ActSetCopyFn  fn(nullptr, nullptr);
                    if (!xu::fromString(fn, vi2[1]))  return false;
                    std::shared_ptr<ActSetCopyFn>  fnPtr =
                            std::make_shared<ActSetCopyFn>(std::move(fn));
                    aItem.second = std::dynamic_pointer_cast<ActFn>(fnPtr);
                }
                break;
            case Action::setMove :
                {
                    ActSetMoveFn  fn(nullptr, nullptr);
                    if (!xu::fromString(fn, vi2[1]))  return false;
                    std::shared_ptr<ActSetMoveFn>  fnPtr =
                            std::make_shared<ActSetMoveFn>(std::move(fn));
                    aItem.second = std::dynamic_pointer_cast<ActFn>(fnPtr);
                }
                break;
            case Action::setConstValue :
                {
                    ActSetConstValueFn  fn(nullptr, nullptr);
                    if (!xu::fromString(fn, vi2[1]))  return false;
                    std::shared_ptr<ActSetConstValueFn>  fnPtr =
                            std::make_shared<ActSetConstValueFn>(std::move(fn));
                    aItem.second = std::dynamic_pointer_cast<ActFn>(fnPtr);
                }
                break;
            case Action::setMutValue :
                {
                    ActSetMutValueFn  fn(nullptr, nullptr);
                    if (!xu::fromString(fn, vi2[1]))  return false;
                    std::shared_ptr<ActSetMutValueFn>  fnPtr =
                            std::make_shared<ActSetMutValueFn>(std::move(fn));
                    aItem.second = std::dynamic_pointer_cast<ActFn>(fnPtr);
                }
                break;
            case Action::is :
                {
                    ActIsFn  fn(nullptr, nullptr);
                    if (!xu::fromString(fn, vi2[1]))  return false;
                    std::shared_ptr<ActIsFn>  fnPtr =
                            std::make_shared<ActIsFn>(std::move(fn));
                    aItem.second = std::dynamic_pointer_cast<ActFn>(fnPtr);
                }
                break;
            case Action::has :
                {
                    ActHasFn  fn(nullptr, nullptr);
                    if (!xu::fromString(fn, vi2[1]))  return false;
                    std::shared_ptr<ActHasFn>  fnPtr =
                            std::make_shared<ActHasFn>(std::move(fn));
                    aItem.second = std::dynamic_pointer_cast<ActFn>(fnPtr);
                }
                break;
            case Action::none :
                break;
            }
            resTmp.push_back(std::move(aItem));
        } else {
            return false;
        }
    }
    res = std::move(resTmp);
    return true;
}

std::string
toString(std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>> const &  value)
{
    std::string  res;
    for (auto const &  it: value) {
        std::string  resTmp;
        xu::append(resTmp, xu::toString(std::get<0>(it)));
        xu::append(resTmp, xu::toString(std::get<1>(it)));
        xu::append(resTmp, xu::toString(*std::get<2>(it)));
        xu::append(res, resTmp);
    }
    return res;
}

bool
fromString(std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>> &  res,
           std::string const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>> &  res,
           std::string_view const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>> &  res,
           char const *  data,
           size_t const  size)
{
    std::vector<std::tuple<size_t, Etype, std::shared_ptr<EObject>>>  resTmp;
    auto  vi = xu::viewIcode(data, size);
    size_t const  viSize = vi.size();
    for (size_t  i = 0; i < viSize; ++i) {
        auto  vi2 = xu::viewIcode(vi[i]);
        if (vi2.size() == 3) {
            std::tuple<size_t, Etype, std::shared_ptr<EObject>>  aItem;
            if (!xu::fromString(std::get<0>(aItem), vi2[0]))  return false;
            if (!xu::fromString(std::get<1>(aItem), vi2[1]))  return false;

            switch (std::get<1>(aItem)) {
            case Etype::eObject :
                {
                    EObject  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<EObject>  objPtr =
                            std::make_shared<EObject>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eBasicBlock :
                {
                    BasicBlock  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<BasicBlock>  objPtr =
                            std::make_shared<BasicBlock>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eFunction :
                {
                    Function  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<Function>  objPtr =
                            std::make_shared<Function>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eFunctions :
                {
                    Functions  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<Functions>  objPtr =
                            std::make_shared<Functions>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eStaticFunctions :
                {
                    StaticFunctions  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<StaticFunctions>  objPtr =
                            std::make_shared<StaticFunctions>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eConstexprFunctions :
                {
                    ConstexprFunctions  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ConstexprFunctions>  objPtr =
                            std::make_shared<ConstexprFunctions>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eTplFunctions :
                {
                    TplFunctions  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<TplFunctions>  objPtr =
                            std::make_shared<TplFunctions>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eTplStaticFunctions :
                {
                    TplStaticFunctions  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<TplStaticFunctions>  objPtr =
                            std::make_shared<TplStaticFunctions>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eTplConstexprFunctions :
                {
                    TplConstexprFunctions  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<TplConstexprFunctions>  objPtr =
                            std::make_shared<TplConstexprFunctions>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eClass :
                {
                    MyClass  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<MyClass>  objPtr =
                            std::make_shared<MyClass>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eClassDeclaration :
                {
                    MyClassDec  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<MyClassDec>  objPtr =
                            std::make_shared<MyClassDec>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eEnum :
                {
                    MyEnum  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<MyEnum>  objPtr =
                            std::make_shared<MyEnum>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eStruct :
                {
                    MyStruct  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<MyStruct>  objPtr =
                            std::make_shared<MyStruct>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eStructDeclaration :
                {
                    MyStructDec  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<MyStructDec>  objPtr =
                            std::make_shared<MyStructDec>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eTypedef :
                {
                    MyTypedef  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<MyTypedef>  objPtr =
                            std::make_shared<MyTypedef>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eConstructors :
                {
                    Constructors  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<Constructors>  objPtr =
                            std::make_shared<Constructors>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eTplConstructors :
                {
                    TplConstructors  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<TplConstructors>  objPtr =
                            std::make_shared<TplConstructors>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eLabel :
                {
                    Label  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<Label>  objPtr =
                            std::make_shared<Label>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::ePublicLabel :
                {
                    PublicLabel  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<PublicLabel>  objPtr =
                            std::make_shared<PublicLabel>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eProtectedLabel :
                {
                    ProtectedLabel  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ProtectedLabel>  objPtr =
                            std::make_shared<ProtectedLabel>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::ePrivateLabel :
                {
                    PrivateLabel  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<PrivateLabel>  objPtr =
                            std::make_shared<PrivateLabel>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eDefaultConstructorFn :
                {
                    DefaultConstructorFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<DefaultConstructorFn>  objPtr =
                            std::make_shared<DefaultConstructorFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eCopyConstructorFn :
                {
                    CopyConstructorFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<CopyConstructorFn>  objPtr =
                            std::make_shared<CopyConstructorFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eMoveConstructorFn :
                {
                    MoveConstructorFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<MoveConstructorFn>  objPtr =
                            std::make_shared<MoveConstructorFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eDestructorFn :
                {
                    DestructorFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<DestructorFn>  objPtr =
                            std::make_shared<DestructorFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eCopyOperatorEqFn :
                {
                    CopyOperatorEqFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<CopyOperatorEqFn>  objPtr =
                            std::make_shared<CopyOperatorEqFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eMoveOperatorEqFn :
                {
                    MoveOperatorEqFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<MoveOperatorEqFn>  objPtr =
                            std::make_shared<MoveOperatorEqFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActFn :
                {
                    ActFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ActFn>  objPtr =
                            std::make_shared<ActFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActGetFn :
                {
                    ActGetFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ActGetFn>  objPtr =
                            std::make_shared<ActGetFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActSetCopyFn :
                {
                    ActSetCopyFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ActSetCopyFn>  objPtr =
                            std::make_shared<ActSetCopyFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActSetMoveFn :
                {
                    ActSetMoveFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ActSetMoveFn>  objPtr =
                            std::make_shared<ActSetMoveFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActSetConstValueFn :
                {
                    ActSetConstValueFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ActSetConstValueFn>  objPtr =
                            std::make_shared<ActSetConstValueFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActSetMutValueFn :
                {
                    ActSetMutValueFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ActSetMutValueFn>  objPtr =
                            std::make_shared<ActSetMutValueFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActIsFn :
                {
                    ActIsFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ActIsFn>  objPtr =
                            std::make_shared<ActIsFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eActHasFn :
                {
                    ActHasFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ActHasFn>  objPtr =
                            std::make_shared<ActHasFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eEqFn :
                {
                    EqFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<EqFn>  objPtr =
                            std::make_shared<EqFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eNotEqFn :
                {
                    NotEqFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<NotEqFn>  objPtr =
                            std::make_shared<NotEqFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eVirtualEqFn :
                {
                    VirtualEqFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<VirtualEqFn>  objPtr =
                            std::make_shared<VirtualEqFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eLessFn :
                {
                    LessFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<LessFn>  objPtr =
                            std::make_shared<LessFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eLessEqFn :
                {
                    LessEqFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<LessEqFn>  objPtr =
                            std::make_shared<LessEqFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eVirtualLessFn :
                {
                    VirtualLessFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<VirtualLessFn>  objPtr =
                            std::make_shared<VirtualLessFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eGreaterFn :
                {
                    GreaterFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<GreaterFn>  objPtr =
                            std::make_shared<GreaterFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eGreaterEqFn :
                {
                    GreaterEqFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<GreaterEqFn>  objPtr =
                            std::make_shared<GreaterEqFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eExtSwapFn :
                {
                    ExtSwapFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ExtSwapFn>  objPtr =
                            std::make_shared<ExtSwapFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eInSwapFn :
                {
                    InSwapFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<InSwapFn>  objPtr =
                            std::make_shared<InSwapFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eVirtualExchangeFn :
                {
                    VirtualExchangeFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<VirtualExchangeFn>  objPtr =
                            std::make_shared<VirtualExchangeFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eToStringFn :
                {
                    ToStringFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ToStringFn>  objPtr =
                            std::make_shared<ToStringFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eVirtualSerializeFn :
                {
                    VirtualSerializeFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<VirtualSerializeFn>  objPtr =
                            std::make_shared<VirtualSerializeFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eExtFromStringFn :
                {
                    ExtFromStringFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<ExtFromStringFn>  objPtr =
                            std::make_shared<ExtFromStringFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eInFromStringFn :
                {
                    InFromStringFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<InFromStringFn>  objPtr =
                            std::make_shared<InFromStringFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eDeserializeFn :
                {
                    DeserializeFn  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<DeserializeFn>  objPtr =
                            std::make_shared<DeserializeFn>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eModule :
                {
                    Module  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<Module>  objPtr =
                            std::make_shared<Module>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            case Etype::eProject :
                {
                    Project  obj;
                    if (!xu::fromString(obj, vi2[2]))  return false;
                    std::shared_ptr<Project>  objPtr =
                            std::make_shared<Project>(std::move(obj));
                    std::get<2>(aItem) = std::dynamic_pointer_cast<EObject>(objPtr);
                }
                break;
            }
            resTmp.push_back(std::move(aItem));
        } else {
            return false;
        }
    }
    res = std::move(resTmp);
    return true;
}

std::string
toActionString(Action const  act)
{
    std::string  res;
    switch (act) {
    case Action::get :
        res = "get";
        break;
    case Action::setCopy :
        res = "setCopy";
        break;
    case Action::setMove :
        res = "setMove";
        break;
    case Action::setConstValue :
        res = "setConstValue";
        break;
    case Action::setMutValue :
        res = "setMutValue";
        break;
    case Action::is :
        res = "is";
        break;
    case Action::has :
        res = "has";
        break;
    case Action::none :
        res = "none";
        break;
    }
    return res;
}

Action
fromActionString(std::string const &  val)
{
    Action  act = Action::none;
    if (val == "get") {
        act = Action::get;
    } else if (val == "setCopy") {
        act = Action::setCopy;
    } else if (val == "setMove") {
        act = Action::setMove;
    } else if (val == "setConstValue") {
        act = Action::setConstValue;
    } else if (val == "setMutValue") {
        act = Action::setMutValue;
    } else if (val == "is") {
        act = Action::is;
    } else if (val == "has") {
        act = Action::has;
    } else {
        act = Action::none;
    }
    return act;
}

EObject::EObject():
        m_treeLabel(),
        m_baseType(Etype::eObject),
        m_id(0)
{
}

EObject::EObject(const EObject &  other):
        m_treeLabel(other.m_treeLabel),
        m_baseType(other.m_baseType),
        m_id(other.m_id)
{
}

EObject::EObject(EObject &&  other) noexcept:
        m_treeLabel(std::move(other.m_treeLabel)),
        m_baseType(std::move(other.m_baseType)),
        m_id(std::move(other.m_id))
{
}

EObject::~EObject() noexcept
{
}

EObject &
EObject::operator=(const EObject &  other)
{
    if (this == &other) return *this;

    m_treeLabel = other.m_treeLabel;
    m_baseType = other.m_baseType;
    m_id = other.m_id;

    return *this;
}

EObject &
EObject::operator=(EObject &&  other) noexcept
{
    if (this == &other) return *this;

    m_treeLabel = std::move(other.m_treeLabel);
    m_baseType = std::move(other.m_baseType);
    m_id = std::move(other.m_id);

    return *this;
}

std::string
EObject::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    return tabStr;
}

std::string
EObject::toCppBlock(std::string const &  tabStr /* = std::string() */) const
{
    return tabStr;
}

std::string
EObject::declaration(std::string const &  tabStr /* = std::string() */) const
{
    return tabStr;
}

std::string
EObject::friendDeclaration(std::string const &  tabStr /* = std::string() */) const
{
    return tabStr;
}

void
EObject::setTreeLabel(std::string const &  value)
{
    m_treeLabel = value;
}

void
EObject::setTreeLabel(std::string &&  value)
{
    m_treeLabel = std::move(value);
}

void
EObject::setBaseType(Etype const  value)
{
    m_baseType = value;
}

std::string
EObject::getTreeLabel() const
{
    return m_treeLabel;
}

Etype
EObject::getBaseType() const
{
    return m_baseType;
}

int
EObject::getId() const
{
    return m_id;
}

void
EObject::setId(const int  value)
{
    m_id = value;
}

bool
operator==(const EObject &  lhs,
           const EObject &  rhs)
{
    if (&lhs == &rhs) return true;
    return lhs.equal(rhs) && rhs.equal(lhs);
}

bool
operator!=(const EObject &  lhs,
           const EObject &  rhs)
{
    return !(lhs == rhs);
}

bool
EObject::equal(const EObject &  value) const
{
    bool  result = false;

    result = ( m_id == value.m_id );
    if (!result) return result;

    result = ( m_treeLabel == value.m_treeLabel );
    if (!result) return result;

    result = ( m_baseType == value.m_baseType );
    if (!result) return result;

    return result;
}

bool
operator<(const EObject &  lhs,
          const EObject &  rhs)
{
    if (&lhs == &rhs) return false;
    return lhs.less(rhs) && !(rhs.less(lhs) && lhs != rhs);
}

bool
operator<=(const EObject &  lhs,
           const EObject &  rhs)
{
    return !(lhs > rhs);
}

bool
EObject::less(const EObject &  value) const
{
    if (m_id < value.m_id) return true;
    if (value.m_id < m_id) return false;

    if (m_treeLabel < value.m_treeLabel) return true;
    if (value.m_treeLabel < m_treeLabel) return false;

    if (m_baseType < value.m_baseType) return true;
    if (value.m_baseType < m_baseType) return false;

    return false;
}

bool
operator>(const EObject &  lhs,
          const EObject &  rhs)
{
    return rhs < lhs;
}

bool
operator>=(const EObject &  lhs,
           const EObject &  rhs)
{
    return !(lhs < rhs);
}

std::string
EObject::toString() const
{
    return serialize();
}

std::string
EObject::serialize() const
{
    std::string  res;

    xu::append(res, xu::toString(m_treeLabel));
    xu::append(res, xu::toString(m_baseType));
    xu::append(res, xu::toString(m_id));

    return res;
}

bool
EObject::deserialize(const char *  data,
                     const size_t  size)
{
    EObject  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 2) {
        if (!xu::fromString(me.m_treeLabel, vi[0]))  err.push_back({0});
        if (!xu::fromString(me.m_baseType, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_id, vi[2]))  err.push_back({2});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
EObject::fromString(const char *  data,
                    const size_t  size)
{
    return deserialize(data, size);
}

bool
fromString(EObject &  value,
           const char *  data,
           const size_t  size)
{
    return value.fromString(data, size);
}

bool
swap(EObject &  lhs,
     EObject &  rhs) noexcept
{
    if (&lhs == &rhs) return false;
    return lhs.swap(rhs);
}

bool
EObject::swap(EObject &  value) noexcept
{
    if (this == &value) return true;
    return this->exchange(value);
}

bool
EObject::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        using std::swap;
        swap(m_treeLabel, value.m_treeLabel);
        swap(m_baseType, value.m_baseType);
        swap(m_id, value.m_id);

        result = true;
    }
    return result;
}

}
