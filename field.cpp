#include <cstring>
#include <typeinfo>
#include <set>
#include <map>
#include "field.h"
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "function.h"
#include "actfn.h"
#include "actgetfn.h"
#include "actisfn.h"
#include "acthasfn.h"
#include "actsetcopyfn.h"
#include "actsetmovefn.h"
#include "actsetmutvaluefn.h"
#include "actsetconstvaluefn.h"

namespace xu {

Field::Field():
        m_stringErr(),
        m_fieldName("new__state"),
        m_docment(),
        m_typeName("std::string"),
        m_defValue(),
        m_array(),
        m_attribute(),
        m_before(),
        m_behind(),
        m_actionFn(),
        m_alignByte(0),
        m_mutable(false),
        m_pointer(false)
{
}

Field::Field(const Field &  other):
        m_stringErr(other.m_stringErr),
        m_fieldName(other.m_fieldName),
        m_docment(other.m_docment),
        m_typeName(other.m_typeName),
        m_defValue(other.m_defValue),
        m_array(other.m_array),
        m_attribute(other.m_attribute),
        m_before(other.m_before),
        m_behind(other.m_behind),
        m_actionFn(other.m_actionFn),
        m_alignByte(other.m_alignByte),
        m_mutable(other.m_mutable),
        m_pointer(other.m_pointer)
{
    copyActionFn();
}

Field::Field(Field &&  other) noexcept:
        m_stringErr(std::move(other.m_stringErr)),
        m_fieldName(std::move(other.m_fieldName)),
        m_docment(std::move(other.m_docment)),
        m_typeName(std::move(other.m_typeName)),
        m_defValue(std::move(other.m_defValue)),
        m_array(std::move(other.m_array)),
        m_attribute(std::move(other.m_attribute)),
        m_before(std::move(other.m_before)),
        m_behind(std::move(other.m_behind)),
        m_actionFn(std::move(other.m_actionFn)),
        m_alignByte(std::move(other.m_alignByte)),
        m_mutable(std::move(other.m_mutable)),
        m_pointer(std::move(other.m_pointer))
{
    moveActionFn();
}

Field::~Field() noexcept
{
}

Field &
Field::operator=(const Field &  other)
{
    if (this == &other) return *this;

    m_stringErr = other.m_stringErr;
    m_fieldName = other.m_fieldName;
    m_docment = other.m_docment;
    m_typeName = other.m_typeName;
    m_defValue = other.m_defValue;
    m_array = other.m_array;
    m_attribute = other.m_attribute;
    m_before = other.m_before;
    m_behind = other.m_behind;
    m_actionFn = other.m_actionFn;
    m_alignByte = other.m_alignByte;
    m_mutable = other.m_mutable;
    m_pointer = other.m_pointer;

    copyActionFn();

    return *this;
}

Field &
Field::operator=(Field &&  other) noexcept
{
    if (this == &other) return *this;

    m_stringErr = std::move(other.m_stringErr);
    m_fieldName = std::move(other.m_fieldName);
    m_docment = std::move(other.m_docment);
    m_typeName = std::move(other.m_typeName);
    m_defValue = std::move(other.m_defValue);
    m_array = std::move(other.m_array);
    m_attribute = std::move(other.m_attribute);
    m_before = std::move(other.m_before);
    m_behind = std::move(other.m_behind);
    m_actionFn = std::move(other.m_actionFn);
    m_alignByte = std::move(other.m_alignByte);
    m_mutable = std::move(other.m_mutable);
    m_pointer = std::move(other.m_pointer);

    moveActionFn();

    return *this;
}

std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &
Field::getActionFnRef()
{
    return m_actionFn;
}

void
Field::updateActionPtr()
{
    for (auto &  fn:  m_actionFn) {
        fn.second->setParentFieldPtr(this);
    }
}

std::string
Field::toHBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;
    std::string const  tab1(getDefTab());

    res += m_before;
    if (m_attribute.size() > 0) {
        res += tabStr + tab1 + m_attribute + "\n";
    }

    std::string  lineStr = tabStr + tab1;
    if (m_alignByte > 0) {
        lineStr += "alignas(" + std::to_string(m_alignByte) + ") ";
    }
    if (m_mutable) {
        lineStr += "mutable ";
    }
    lineStr += m_typeName;
    if (m_pointer) {
        lineStr += " *";
    }
    lineStr += "  ";

    size_t  devSize = 20;
    size_t const  maxSize = 61;
    size_t const  fdSize = lineStr.size();
    while (devSize < maxSize) {
        if (fdSize < devSize) {
            lineStr.insert(lineStr.end(), devSize - fdSize, '\x20');;
            break;
        }
        devSize += 4;
    }

    lineStr += getPrivateName();
    if (m_array.size() > 0) {
        lineStr += "[" + m_array + "]";
    }
    if (m_defValue.size() > 0) {
        lineStr += " = " + m_defValue;
    }
    lineStr += ";\n";

    res += lineStr + m_behind;

    return res;
}

std::string
Field::toBlockStruct(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;
    std::string const  tab1(getDefTab());

    res += m_before;
    if (m_attribute.size() > 0) {
        res += tabStr + tab1 + m_attribute + "\n";
    }

    std::string  lineStr = tabStr + tab1;
    if (m_alignByte > 0) {
        lineStr += "alignas(" + std::to_string(m_alignByte) + ") ";
    }
    if (m_mutable) {
        lineStr += "mutable ";
    }
    lineStr += m_typeName;
    if (m_pointer) {
        lineStr += " *";
    }
    lineStr += "  ";

    size_t  devSize = 20;
    size_t const  maxSize = 61;
    size_t const  fdSize = lineStr.size();
    while (devSize < maxSize) {
        if (fdSize < devSize) {
            lineStr.insert(lineStr.end(), devSize - fdSize, '\x20');;
            break;
        }
        devSize += 4;
    }

    lineStr += m_fieldName;
    if (m_array.size() > 0) {
        lineStr += "[" + m_array + "]";
    }
    if (m_defValue.size() > 0) {
        lineStr += " = " + m_defValue;
    }
    lineStr += ";\n";

    res += lineStr + m_behind;

    return res;
}

std::string
Field::cppCodeGeneral(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    for (auto const &  it: m_actionFn) {
        auto const &  fnPtr = std::dynamic_pointer_cast<Function>(it.second);
        res += "\n";
        res += fnPtr->toCppBlock(tabStr);
    }

    return res;
}

std::string
Field::hCodeDcl(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;

    for (auto const &  it: m_actionFn) {
        auto const &  fnPtr = std::dynamic_pointer_cast<Function>(it.second);
        res += tabStr + fnPtr->declaration();
    }

    return res;
}

std::string
Field::getPrivateName() const
{
    return std::string("m_" + m_fieldName);
}

std::string
Field::getCtorDefValue() const
{
    std::string  res = m_defValue;

    if (m_pointer) {
        res = "nullptr";
    }

    return res;
}

void
Field::copyActionFn()
{
    for (auto &  actFn: m_actionFn) {
        std::shared_ptr<ActFn>  actPtr;
        switch (actFn.first) {
        case Action::get :
            actPtr = std::make_shared<ActGetFn>(
                    *std::dynamic_pointer_cast<ActGetFn>(actFn.second));
            break;
        case Action::setCopy :
            actPtr = std::make_shared<ActSetCopyFn>(
                    *std::dynamic_pointer_cast<ActSetCopyFn>(actFn.second));
            break;
        case Action::setMove :
            actPtr = std::make_shared<ActSetMoveFn>(
                    *std::dynamic_pointer_cast<ActSetMoveFn>(actFn.second));
            break;
        case Action::setConstValue :
            actPtr = std::make_shared<ActSetConstValueFn>(
                    *std::dynamic_pointer_cast<ActSetConstValueFn>(actFn.second));
            break;
        case Action::setMutValue :
            actPtr = std::make_shared<ActSetMutValueFn>(
                    *std::dynamic_pointer_cast<ActSetMutValueFn>(actFn.second));
            break;
        case Action::is :
            actPtr = std::make_shared<ActIsFn>(
                    *std::dynamic_pointer_cast<ActIsFn>(actFn.second));
            break;
        case Action::has :
            actPtr = std::make_shared<ActHasFn>(
                    *std::dynamic_pointer_cast<ActHasFn>(actFn.second));
            break;
        case Action::none :
            actPtr = std::make_shared<ActFn>(
                    *std::dynamic_pointer_cast<ActFn>(actFn.second));
            break;
        }
        actFn.second = actPtr;
        actFn.second->setParentFieldPtr(this);
    }
}

void
Field::moveActionFn()
{
    for (auto &  actFn: m_actionFn) {
        actFn.second->setParentFieldPtr(this);
    }
}

std::vector<size_t>
Field::getStringErr() const
{
    return m_stringErr;
}

std::string
Field::getFieldName() const
{
    return m_fieldName;
}

void
Field::setFieldName(const std::string &  value)
{
    m_fieldName = xu::trim(value);
}

std::string
Field::getDocment() const
{
    return m_docment;
}

void
Field::setDocment(const std::string &  value)
{
    m_docment = value;
}

void
Field::setDocment(std::string &&  value)
{
    m_docment = std::move(value);
}

std::string
Field::getTypeName() const
{
    return m_typeName;
}

void
Field::setTypeName(const std::string &  value)
{
    m_typeName = value;
}

void
Field::setTypeName(std::string &&  value)
{
    m_typeName = std::move(value);
}

std::string
Field::getDefValue() const
{
    return m_defValue;
}

void
Field::setDefValue(const std::string &  value)
{
    m_defValue = value;
}

void
Field::setDefValue(std::string &&  value)
{
    m_defValue = std::move(value);
}

std::string
Field::getArray() const
{
    return m_array;
}

void
Field::setArray(const std::string &  value)
{
    m_array = xu::trim(value);
}

std::string
Field::getAttribute() const
{
    return m_attribute;
}

void
Field::setAttribute(const std::string &  value)
{
    m_attribute = value;
}

void
Field::setAttribute(std::string &&  value)
{
    m_attribute = std::move(value);
}

std::string
Field::getBefore() const
{
    return m_before;
}

void
Field::setBefore(const std::string &  value)
{
    m_before = value;
    xu::procCode(m_before);
}

void
Field::setBefore(std::string &&  value)
{
    m_before = std::move(value);
    xu::procCode(m_before);
}

std::string
Field::getBehind() const
{
    return m_behind;
}

void
Field::setBehind(const std::string &  value)
{
    m_behind = value;
    xu::procCode(m_behind);
}

void
Field::setBehind(std::string &&  value)
{
    m_behind = std::move(value);
    xu::procCode(m_behind);
}

std::vector<std::pair<Action, std::shared_ptr<ActFn>>>
Field::getActionFn() const
{
    return m_actionFn;
}

void
Field::setActionFn(const std::vector<std::pair<Action, std::shared_ptr<ActFn>>> &  value)
{
    m_actionFn.clear();
    for (auto const &  it: value) {
        auto  itpos = std::find_if(m_actionFn.begin(), m_actionFn.end(),
                [act = it.first]
                (std::pair<Action, std::shared_ptr<ActFn>> const &  fn)
                ->bool {
                    if (fn.first == act) {
                        return true;
                    } else {
                        return false;
                    }
                });
        if (itpos != m_actionFn.end()) {
            continue;
        }

        std::pair<Action, std::shared_ptr<ActFn>>  fdAct;
        fdAct.first = it.first;
        switch (it.first) {
        case Action::get :
            fdAct.second = std::dynamic_pointer_cast<ActFn>(
                    std::make_shared<ActGetFn>(nullptr, this));
            break;
        case Action::setCopy :
            fdAct.second = std::dynamic_pointer_cast<ActFn>(
                    std::make_shared<ActSetCopyFn>(nullptr, this));
            break;
        case Action::setMove :
            fdAct.second = std::dynamic_pointer_cast<ActFn>(
                    std::make_shared<ActSetMoveFn>(nullptr, this));
            break;
        case Action::setConstValue :
            fdAct.second = std::dynamic_pointer_cast<ActFn>(
                    std::make_shared<ActSetConstValueFn>(nullptr, this));
            break;
        case Action::setMutValue :
            fdAct.second = std::dynamic_pointer_cast<ActFn>(
                    std::make_shared<ActSetMutValueFn>(nullptr, this));
            break;
        case Action::is :
            fdAct.second = std::dynamic_pointer_cast<ActFn>(
                    std::make_shared<ActIsFn>(nullptr, this));
            break;
        case Action::has :
            fdAct.second = std::dynamic_pointer_cast<ActFn>(
                    std::make_shared<ActHasFn>(nullptr, this));
            break;
        case Action::none :
            break;
        }
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setParentClassPtr(std::dynamic_pointer_cast<Function>
                (it.second)->getParentClassPtr());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setDocment(std::dynamic_pointer_cast<Function>
                (it.second)->getDocment());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setTestCode(std::dynamic_pointer_cast<Function>
                (it.second)->getTestCode());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setStrike(std::dynamic_pointer_cast<Function>
                (it.second)->getStrike());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setNewCode(std::dynamic_pointer_cast<Function>
                (it.second)->getNewCode());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setHReturnTypeBehind(std::dynamic_pointer_cast<Function>
                (it.second)->getHReturnTypeBehind());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setHReturnTypeBehind2(std::dynamic_pointer_cast<Function>
                (it.second)->getHReturnTypeBehind2());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setReturnTypeDoc(std::dynamic_pointer_cast<Function>
                (it.second)->getReturnTypeDoc());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setAttribute(std::dynamic_pointer_cast<Function>
                (it.second)->getAttribute());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setHBefore(std::dynamic_pointer_cast<Function>
                (it.second)->getHBefore());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setHBehind(std::dynamic_pointer_cast<Function>
                (it.second)->getHBehind());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setCppBefore(std::dynamic_pointer_cast<Function>
                (it.second)->getCppBefore());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setCppBehind(std::dynamic_pointer_cast<Function>
                (it.second)->getCppBehind());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setNoexcept(std::dynamic_pointer_cast<Function>
                (it.second)->isNoexcept());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setInline(std::dynamic_pointer_cast<Function>
                (it.second)->isInline());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setVirtual(std::dynamic_pointer_cast<Function>
                (it.second)->isVirtual());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setOverride(std::dynamic_pointer_cast<Function>
                (it.second)->isOverride());
        std::dynamic_pointer_cast<Function>(fdAct.second)->
                setFinal(std::dynamic_pointer_cast<Function>
                (it.second)->isFinal());

        m_actionFn.push_back(std::move(fdAct));
    }
}

int
Field::getAlignByte() const
{
    return m_alignByte;
}

void
Field::setAlignByte(const int  value)
{
    if (value == 4 || value == 8 || value == 16 || value == 32 ||
            value == 64 || value == 128) {
        m_alignByte = value;
    } else {
        m_alignByte = 0;
    }
}

bool
Field::isMutable() const
{
    return m_mutable;
}

void
Field::setMutable(const bool  value)
{
    m_mutable = value;
}

bool
Field::isPointer() const
{
    return m_pointer;
}

void
Field::setPointer(const bool  value)
{
    m_pointer = value;
}

bool
operator==(const Field &  lhs,
           const Field &  rhs)
{
    if (&lhs == &rhs) return true;
    bool  result = false;

    result = ( lhs.m_fieldName == rhs.m_fieldName );
    if (!result) return result;

    result = ( lhs.m_typeName == rhs.m_typeName );
    if (!result) return result;

    result = ( lhs.m_defValue == rhs.m_defValue );
    if (!result) return result;

    result = ( lhs.m_array == rhs.m_array );
    if (!result) return result;

    result = ( lhs.m_attribute == rhs.m_attribute );
    if (!result) return result;

    result = ( lhs.m_before == rhs.m_before );
    if (!result) return result;

    result = ( lhs.m_behind == rhs.m_behind );
    if (!result) return result;

    result = ( lhs.m_alignByte == rhs.m_alignByte );
    if (!result) return result;

    result = ( lhs.m_mutable == rhs.m_mutable );
    if (!result) return result;

    result = ( lhs.m_pointer == rhs.m_pointer );
    if (!result) return result;

    return result;
}

bool
operator!=(const Field &  lhs,
           const Field &  rhs)
{
    return !(lhs == rhs);
}

bool
operator<(const Field &  lhs,
          const Field &  rhs)
{
    if (&lhs == &rhs) return false;

    if (lhs.m_fieldName < rhs.m_fieldName) return true;
    if (rhs.m_fieldName < lhs.m_fieldName) return false;

    if (lhs.m_typeName < rhs.m_typeName) return true;
    if (rhs.m_typeName < lhs.m_typeName) return false;

    if (lhs.m_defValue < rhs.m_defValue) return true;
    if (rhs.m_defValue < lhs.m_defValue) return false;

    if (lhs.m_array < rhs.m_array) return true;
    if (rhs.m_array < lhs.m_array) return false;

    if (lhs.m_attribute < rhs.m_attribute) return true;
    if (rhs.m_attribute < lhs.m_attribute) return false;

    if (lhs.m_before < rhs.m_before) return true;
    if (rhs.m_before < lhs.m_before) return false;

    if (lhs.m_behind < rhs.m_behind) return true;
    if (rhs.m_behind < lhs.m_behind) return false;

    if (lhs.m_alignByte < rhs.m_alignByte) return true;
    if (rhs.m_alignByte < lhs.m_alignByte) return false;

    if (lhs.m_mutable < rhs.m_mutable) return true;
    if (rhs.m_mutable < lhs.m_mutable) return false;

    if (lhs.m_pointer < rhs.m_pointer) return true;
    if (rhs.m_pointer < lhs.m_pointer) return false;

    return false;
}

bool
operator<=(const Field &  lhs,
           const Field &  rhs)
{
    return !(lhs > rhs);
}

bool
operator>(const Field &  lhs,
          const Field &  rhs)
{
    return rhs < lhs;
}

bool
operator>=(const Field &  lhs,
           const Field &  rhs)
{
    return !(lhs < rhs);
}

std::string
Field::toString() const
{
    std::string  res;

    xu::append(res, xu::toString(m_fieldName));
    xu::append(res, xu::toString(m_docment));
    xu::append(res, xu::toString(m_typeName));
    xu::append(res, xu::toString(m_defValue));
    xu::append(res, xu::toString(m_array));
    xu::append(res, xu::toString(m_attribute));
    xu::append(res, xu::toString(m_before));
    xu::append(res, xu::toString(m_behind));
    xu::append(res, xu::toString(m_alignByte));
    xu::append(res, xu::toString(m_mutable));
    xu::append(res, xu::toString(m_pointer));
    xu::append(res, xu::toString(m_actionFn));

    return res;
}

bool
Field::fromString(const char *  data,
                  const size_t  size)
{
    Field  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 11) {
        if (!xu::fromString(me.m_fieldName, vi[0]))  err.push_back({0});
        if (!xu::fromString(me.m_docment, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_typeName, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_defValue, vi[3]))  err.push_back({3});
        if (!xu::fromString(me.m_array, vi[4]))  err.push_back({4});
        if (!xu::fromString(me.m_attribute, vi[5]))  err.push_back({5});
        if (!xu::fromString(me.m_before, vi[6]))  err.push_back({6});
        if (!xu::fromString(me.m_behind, vi[7]))  err.push_back({7});
        if (!xu::fromString(me.m_alignByte, vi[8]))  err.push_back({8});
        if (!xu::fromString(me.m_mutable, vi[9]))  err.push_back({9});
        if (!xu::fromString(me.m_pointer, vi[10]))  err.push_back({10});
        if (!xu::fromString(me.m_actionFn, vi[11]))  err.push_back({11});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
        updateActionPtr();
    }
    m_stringErr = std::move(err);

    return result;
}

bool
fromString(Field &  value,
           const char *  data,
           const size_t  size)
{
    return value.fromString(data, size);
}

void
swap(Field &  lhs,
     Field &  rhs) noexcept
{
    lhs.swap(rhs);
}

void
Field::swap(Field &  value) noexcept
{
    if (this == &value) return;
    using std::swap;
    swap(m_stringErr, value.m_stringErr);
    swap(m_fieldName, value.m_fieldName);
    swap(m_docment, value.m_docment);
    swap(m_typeName, value.m_typeName);
    swap(m_defValue, value.m_defValue);
    swap(m_array, value.m_array);
    swap(m_attribute, value.m_attribute);
    swap(m_before, value.m_before);
    swap(m_behind, value.m_behind);
    swap(m_actionFn, value.m_actionFn);
    swap(m_alignByte, value.m_alignByte);
    swap(m_mutable, value.m_mutable);
    swap(m_pointer, value.m_pointer);
}

}
