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

std::string
deleteSingleLineComment(std::string const &  code)
{
    std::string  res;

    std::vector<std::pair<std::string_view, bool>>  vce;
    const char *  pData = nullptr;
    size_t  pSize = 0;
    const char *  data = code.data();
    if (code.size() > 0) {
        pData = data;
    }

    for (size_t  i = 0; i < code.size(); ++i) {
        data++;
        std::pair<std::string_view, bool>  it;
        it.second = true;
        if (code[i] == '\r') {
            it.first = std::string_view(pData, pSize);
            vce.push_back(it);
            pData = data;
            pSize = 0;
        } else if (code[i] == '\n') {
            if (i == 0) {
                it.first = std::string_view(pData, pSize);
                vce.push_back(it);
                pData = data;
            } else {
                if (code[i - 1] == '\r') {
                    pData = data;
                } else {
                    it.first = std::string_view(pData, pSize);
                    vce.push_back(it);
                    pData = data;
                    pSize = 0;
                }
            }
        } else {
            pSize++;
        }
    }

    bool  isInMulComment = false;
    for (auto &  it: vce) {
        const size_t  size = it.first.size();
        if (size == 0) {
            continue;
        }
        bool  isInQuotation = false;
        bool  isAllSpace = true;
        size_t  endSpaceSize = 0;

        for (size_t  i = 0; i < size; ++i) {
            if (it.first[i] == '/') {
                if (!isInMulComment && !isInQuotation &&
                        (i + 1) < size && it.first[i + 1] == '/') {
                    if (isAllSpace) {
                        it.second = false;
                    } else {
                        it.first.remove_suffix(size - i + endSpaceSize);
                    }
                    break;
                } else if (!isInMulComment && !isInQuotation &&
                        (i + 1) < size && it.first[i + 1] == '*') {
                    isInMulComment = true;
                    isAllSpace = false;
                    endSpaceSize = 0;
                    i++;
                } else {
                    isAllSpace = false;
                    endSpaceSize = 0;
                }
            } else if (it.first[i] == '*' && isInMulComment &&
                    (i + 1) < size && it.first[i + 1] == '/') {
                isInMulComment = false;
                isAllSpace = false;
                endSpaceSize = 0;
                i++;
            } else if (it.first[i] == ' ') {
                endSpaceSize++;
                if ((i + 1) == size) {
                    it.first.remove_suffix(endSpaceSize);
                }
            } else if (it.first[i] == '\"' && !isInMulComment) {
                if (i != 0) {
                    size_t  vIdx = 0;
                    for (size_t  k = i - 1; k != 0; --k) {
                        if (it.first[k] == '\\') {
                            vIdx++;
                        } else {
                            break;
                        }
                    }
                    if (vIdx % 2 == 0) {
                        isInQuotation = !isInQuotation;
                    }
                } else {
                    isInQuotation = !isInQuotation;
                }
                endSpaceSize = 0;
                isAllSpace = false;
            } else {
                isAllSpace = false;
                endSpaceSize = 0;
            }
        }
    }

    for (auto &  it: vce) {
        if (it.second) {
            res += it.first;
            res += "\n";
        }
    }
    return res;
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
