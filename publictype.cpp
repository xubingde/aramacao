#include <cstring>
#include <typeinfo>
#include "publictype.h"

namespace xu {

StyleType
getGuiStyle()
{
    return primGuiStyle();
}

void
setGuiStyle(const StyleType  value)
{
    StyleType &  style = primGuiStyle();
    style = value;
}

std::string
getDefTab()
{
    return primDefTab();
}

void
setDefTab(std::string const &  value)
{
    std::string &  tabStr = primDefTab();
    tabStr = value;
}

std::string
getOther()
{
    return primOther();
}

void
setOther(std::string const &  value)
{
    std::string &  res = primOther();
    res = value;
}

std::string
getSig()
{
    return primSig();
}

void
setSig(std::string const &  value)
{
    std::string &  res = primSig();
    res = value;
}

std::string
getRhs()
{
    return primRhs();
}

void
setRhs(std::string const &  value)
{
    std::string &  res = primRhs();
    res = value;
}

std::string
getLhs()
{
    return primLhs();
}

void
setLhs(std::string const &  value)
{
    std::string &  res = primRhs();
    res = value;
}

StyleType &
primGuiStyle()
{
    static thread_local StyleType  guiStyle { StyleType::dark };
    return guiStyle;
}

std::string &
primDefTab()
{
    static thread_local std::string  tabStr("    ");
    return tabStr;
}

std::string &
primOther()
{
    static thread_local std::string  other("other");
    return other;
}

std::string &
primSig()
{
    static thread_local std::string  sig("value");
    return sig;
}

std::string &
primRhs()
{
    static thread_local std::string  right("rhs");
    return right;
}

std::string &
primLhs()
{
    static thread_local std::string  left("lhs");
    return left;
}

}
