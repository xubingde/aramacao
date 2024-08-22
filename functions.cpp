#include <typeinfo>
#include <cstring>
#include "functions.h"
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "myclass.h"

namespace xu {

std::string
toString(std::vector<std::shared_ptr<Function>> const &  value)
{
    std::string  res;
    for (auto const &  it: value) {
        xu::append(res, it->toString());
    }
    return res;
}

bool
fromString(std::vector<std::shared_ptr<Function>> &  res,
           std::string const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::shared_ptr<Function>> &  res,
           std::string_view const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::shared_ptr<Function>> &  res,
           char const *  data,
           size_t const  size)
{
    std::vector<std::shared_ptr<Function>>  resTmp;
    auto  vi = xu::viewIcode(data, size);
    size_t const  viSize = vi.size();
    for (size_t  i = 0; i < viSize; ++i) {
        Function  fn;
        if (!xu::fromString(fn, vi[i]))  return false;
        std::shared_ptr<Function>  objPtr = std::make_shared<Function>(std::move(fn));
        resTmp.push_back(objPtr);
    }
    res = std::move(resTmp);
    return true;
}

Functions::Functions(const Functions &  other):
        EObject(other),
        m_objList(other.m_objList),
        m_parentClassPtr(other.m_parentClassPtr)
{
}

Functions::Functions(Functions &&  other) noexcept:
        EObject(std::move(other)),
        m_objList(std::move(other.m_objList)),
        m_parentClassPtr(std::move(other.m_parentClassPtr))
{
}

Functions::Functions(MyClass *  parent /* = nullptr */):
        EObject(),
        m_objList(),
        m_parentClassPtr(parent)
{
    setTreeLabel("G   Functions");
    setBaseType(Etype::eFunctions);
}

Functions::~Functions() noexcept
{
}

Functions &
Functions::operator=(const Functions &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_objList = other.m_objList;
    m_parentClassPtr = other.m_parentClassPtr;

    return *this;
}

Functions &
Functions::operator=(Functions &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_objList = std::move(other.m_objList);
    m_parentClassPtr = std::move(other.m_parentClassPtr);

    return *this;
}

std::string
Functions::toHBlock(std::string const & /* = std::string() */) const
{
    std::string  res;
    std::string  tab1;

    if (m_parentClassPtr)  tab1 = xu::getDefTab();
    if (m_objList.size() > 0)  res += "\n";
    for (auto const &  it: m_objList) {
        res += it->toHBlock(tab1);
    }
    return res;
}

std::string
Functions::toCppBlock(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;
    for (auto const &  it: m_objList) {
        res += it->toCppBlock(tabStr);
    }
    return res;
}

std::string
Functions::declaration(std::string const &  tabStr /* = std::string() */) const
{
    std::string  res;
    for (auto const &  it: m_objList) {
        res += it->declaration(tabStr);
    }
    return res;
}

std::vector<std::shared_ptr<Function>> &
Functions::getFunctionRef()
{
    return m_objList;
}

std::vector<std::shared_ptr<Function>> *
Functions::getFunctionPtr()
{
    return &m_objList;
}

void
Functions::enterClass(MyClass *  classPtr)
{
    m_parentClassPtr = classPtr;
    for (auto &  fn: m_objList) {
        procFunction(*fn);
    }
}

void
Functions::leaveClass()
{
    m_parentClassPtr = nullptr;
    for (auto &  fn: m_objList) {
        procFunction(*fn);
    }
}

bool
Functions::getFunction(Function &  result,
                       const size_t  index) const
{
    if (index < m_objList.size()) {
        result = *m_objList[index];
        return true;
    }
    return false;
}

bool
Functions::takeFunction(Function &  result,
                        const size_t  index)
{
    if (index < m_objList.size()) {
        result = *m_objList[index];
        m_objList.erase(m_objList.begin() + index);
        return true;
    }
    return false;
}

std::shared_ptr<Function>
Functions::appendFunction(const Function &  value)
{
    Function  fn = value;
    procFunction(fn);
    std::shared_ptr<Function>  obj = std::make_shared<Function>(std::move(fn));
    m_objList.push_back(obj);

    return obj;
}

bool
Functions::updateFunction(const Function &  fn,
                          const size_t  index)
{
    if (index < m_objList.size()) {
        std::shared_ptr<Function>  obj = std::make_shared<Function>(fn);
        m_objList[index] = obj;
        procFunction(*m_objList[index]);
        return true;
    } else {
        return false;
    }
}

void
Functions::insertFunction(const Function &  fn,
                          size_t  index)
{
    if (index > m_objList.size()) {
        index = m_objList.size();
    }
    Function  value = fn;
    std::shared_ptr<Function>  obj = std::make_shared<Function>(std::move(value));
    m_objList.insert(m_objList.begin() + index, obj);
    procFunction(*m_objList[index]);
}

bool
Functions::deleteFunction(const size_t  index)
{
    if (index < m_objList.size()) {
        m_objList.erase(m_objList.begin() + index);
        return true;
    } else {
        return false;
    }
}

bool
Functions::swapFunction(const size_t  indexLhs,
                        const size_t  indexRhs)
{
    if (indexLhs < m_objList.size() && indexRhs < m_objList.size() && indexLhs != indexRhs) {
        std::swap(m_objList[indexLhs], m_objList[indexRhs]);
        return true;
    } else {
        return false;
    }
}

bool
Functions::moveFunction(size_t &  indexFrom,
                        size_t &  indexTo)
{
    return xu::moveVec_1(m_objList, indexFrom, indexTo);
}

void
Functions::clearFunction()
{
    m_objList.clear();
}

void
Functions::procFunction(Function &  fn)
{
    if (m_parentClassPtr) {
        fn.setClassFunction(true);
        fn.setParentClassPtr(m_parentClassPtr);
    } else {
        fn.setClassFunction(false);
        fn.setParentClassPtr(nullptr);
    }

    fn.setConstructor(false);
    fn.setStrike({});
    fn.setNewCode({});
    fn.setStatic(false);
    fn.setConstexpr(false);
    fn.setTemplate(false);
    fn.setAutoSource(false);
    fn.setTparam({});
    fn.setInhValueFirst("");
    fn.setInhValueBaseClass({});
    fn.setDefValueCtor({});

    if (m_parentClassPtr && m_parentClassPtr->getClasstype() == ClassType::cppFinal) {
        fn.setVirtual(false);
        fn.setOverride(false);
        fn.setFinal(false);
        fn.setPureVirtual(false);
    } else {
        fn.setVirtual(false);
        fn.setOverride(false);
        fn.setFinal(false);
        fn.setConst(false);
        fn.setEqDefault(false);
        fn.setEqDelete(false);
        fn.setRef(false);
        fn.setRefRef(false);
        fn.setPureVirtual(false);
    }
}

std::vector<std::shared_ptr<Function>>
Functions::getObjList() const
{
    return m_objList;
}

void
Functions::setObjList(const std::vector<std::shared_ptr<Function>> &  value)
{
    m_objList.clear();
    for (auto  fnPtr: value) {
        procFunction(*fnPtr);
        m_objList.push_back(fnPtr);
    }
}

MyClass *
Functions::getParentClassPtr() const
{
    return m_parentClassPtr;
}

void
Functions::setParentClassPtr(MyClass *  value)
{
    m_parentClassPtr = value;
    for (std::shared_ptr<Function> &  fn: m_objList) {
        procFunction(*fn);
    }
}

bool
Functions::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const Functions &  rhs = dynamic_cast<const Functions &>(value);

        result = this->EObject::equal(value);
        if (!result) return result;

        result = ( m_objList == rhs.m_objList );
        if (!result) return result;

        result = ( m_parentClassPtr == rhs.m_parentClassPtr );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
Functions::less(const EObject &  value) const
{
    if (this->EObject::less(value)) return true;
    if (!(this->EObject::equal(value))) return false;

    try {
        const Functions &  rhs = dynamic_cast<const Functions &>(value);

        if (m_objList < rhs.m_objList) return true;
        if (rhs.m_objList < m_objList) return false;

        if (m_parentClassPtr < rhs.m_parentClassPtr) return true;
        if (rhs.m_parentClassPtr < m_parentClassPtr) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
Functions::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_objList));

    return res;
}

bool
Functions::deserialize(const char *  data,
                       const size_t  size)
{
    Functions  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 1) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_objList, vi[1]))  err.push_back({1});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
Functions::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        Functions &  rhs = dynamic_cast<Functions &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_objList, rhs.m_objList);
        swap(m_parentClassPtr, rhs.m_parentClassPtr);

        result = true;
    }
    return result;
}

}
