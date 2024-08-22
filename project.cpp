#include <cstring>
#include <typeinfo>
#include "project.h"
#include "icode.h"
#include "fmt.h"
#include "publictype.h"

namespace xu {

std::string
toString(std::vector<std::shared_ptr<Module>> const &  value)
{
    std::string  res;
    for (auto const &  it: value) {
        xu::append(res, it->toString());
    }
    return res;
}

bool
fromString(std::vector<std::shared_ptr<Module>> &  res,
           std::string const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::shared_ptr<Module>> &  res,
           std::string_view const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::shared_ptr<Module>> &  res,
           char const *  data,
           size_t const  size)
{
    std::vector<std::shared_ptr<Module>>  resTmp;
    auto  vi = xu::viewIcode(data, size);
    size_t const  viSize = vi.size();
    for (size_t  i = 0; i < viSize; ++i) {
        Module  md;
        if (!xu::fromString(md, vi[i]))  return false;
        std::shared_ptr<Module>  objPtr = std::make_shared<Module>(std::move(md));
        resTmp.push_back(objPtr);
    }
    res = std::move(resTmp);
    return true;
}

Project::Project():
        EObject(),
        m_eobjList(),
        m_projectName(),
        m_docment()
{
    setTreeLabel("P   " + m_projectName);
    setBaseType(Etype::eProject);
}

Project::Project(const Project &  other):
        EObject(other),
        m_eobjList(other.m_eobjList),
        m_projectName(other.m_projectName),
        m_docment(other.m_docment)
{
}

Project::Project(Project &&  other) noexcept:
        EObject(std::move(other)),
        m_eobjList(std::move(other.m_eobjList)),
        m_projectName(std::move(other.m_projectName)),
        m_docment(std::move(other.m_docment))
{
}

Project::~Project() noexcept
{
}

Project &
Project::operator=(const Project &  other)
{
    if (this == &other) return *this;

    this->EObject::operator=(other);

    m_eobjList = other.m_eobjList;
    m_projectName = other.m_projectName;
    m_docment = other.m_docment;

    return *this;
}

Project &
Project::operator=(Project &&  other) noexcept
{
    if (this == &other) return *this;

    this->EObject::operator=(std::move(other));

    m_eobjList = std::move(other.m_eobjList);
    m_projectName = std::move(other.m_projectName);
    m_docment = std::move(other.m_docment);

    return *this;
}

std::vector<std::shared_ptr<Module>> &
Project::getModuleListRef()
{
    return m_eobjList;
}

Module &
Project::getModuleRef(size_t  index)
{
    if (index > m_eobjList.size()) {
        index = m_eobjList.size();
    }
    return *m_eobjList[index];
}

bool
Project::getModule(Module &  result,
                   size_t const  index)
{
    if (index < m_eobjList.size()) {
        result = *m_eobjList[index];
        return true;
    }
    return false;
}

void
Project::appendEobjList(Module const &  value)
{
    std::shared_ptr<Module>  obj = std::make_shared<Module>(value);
    m_eobjList.push_back(obj);
}

void
Project::appendEobjList(Module &&  value)
{
    std::shared_ptr<Module>  obj = std::make_shared<Module>(std::move(value));
    m_eobjList.push_back(obj);
}

bool
Project::updateEobjList(Module const &  value,
                        size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size()) {
        std::shared_ptr<Module>  obj = std::make_shared<Module>(value);
        m_eobjList[index] = obj;
        res = true;
    }
    return res;
}

bool
Project::updateEobjList(Module &&  value,
                        size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size()) {
        std::shared_ptr<Module>  obj = std::make_shared<Module>(std::move(value));
        m_eobjList[index] = obj;
        res = true;
    }
    return res;
}

void
Project::insertEobjList(Module const &  value,
                        size_t  index)
{
    if (index > m_eobjList.size()) {
        index = m_eobjList.size();
    }
    std::shared_ptr<Module>  obj = std::make_shared<Module>(value);
    m_eobjList.insert(m_eobjList.begin() + index, obj);
}

void
Project::insertEobjList(Module &&  value,
                        size_t  index)
{
    if (index > m_eobjList.size()) {
        index = m_eobjList.size();
    }
    std::shared_ptr<Module>  obj = std::make_shared<Module>(std::move(value));
    m_eobjList.insert(m_eobjList.begin() + index, obj);
}

bool
Project::deleteEobjList(size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size()) {
        m_eobjList.erase(m_eobjList.begin() + index);
        res = true;
    }

    return res;
}

bool
Project::takeEobjList(Module &  result,
                      size_t const  index)
{
    if (index < m_eobjList.size()) {
        result = *m_eobjList[index];
        m_eobjList.erase(m_eobjList.begin() + index);
        return true;
    }
    return false;
}

bool
Project::swapEobjList(size_t const  indexLhs,
                      size_t const  indexRhs)
{
    if (indexLhs < m_eobjList.size() && indexRhs < m_eobjList.size() && indexLhs != indexRhs) {
        std::swap(m_eobjList[indexLhs], m_eobjList[indexRhs]);
        return true;
    } else {
        return false;
    }
}

bool
Project::moveEobjList(size_t &  indexFrom,
                      size_t &  indexTo)
{
    if (xu::moveVec_1(m_eobjList, indexFrom, indexTo)) {
        return true;
    }
    return false;
}

std::vector<std::shared_ptr<Module>>
Project::getEobjList() const
{
    return m_eobjList;
}

void
Project::setEobjList(const std::vector<std::shared_ptr<Module>> &  value)
{
    m_eobjList = value;
}

inline
void
Project::setEobjList(std::vector<std::shared_ptr<Module>> &&  value)
{
    m_eobjList = std::move(value);
}

std::string
Project::getProjectName() const
{
    return m_projectName;
}

void
Project::setProjectName(const std::string &  value)
{
    m_projectName = value;
    setTreeLabel("P   " + m_projectName);
}

void
Project::setProjectName(std::string &&  value)
{
    m_projectName = std::move(value);
    setTreeLabel("P   " + m_projectName);
}

std::string
Project::getDocment() const
{
    return m_docment;
}

void
Project::setDocment(const std::string &  value)
{
    m_docment = value;
}

void
Project::setDocment(std::string &&  value)
{
    m_docment = std::move(value);
}

bool
Project::equal(const EObject &  value) const
{
    bool  result = false;
    try {
        const Project &  rhs = dynamic_cast<const Project &>(value);

        result = this->EObject::equal(value);
        if (!result) return result;

        result = ( m_eobjList == rhs.m_eobjList );
        if (!result) return result;

        result = ( m_projectName == rhs.m_projectName );
        if (!result) return result;

        result = ( m_docment == rhs.m_docment );
        if (!result) return result;

    } catch (const std::bad_cast &) {
        ;
    }
    return result;
}

bool
Project::less(const EObject &  value) const
{
    if (this->EObject::less(value)) return true;
    if (!(this->EObject::equal(value))) return false;

    try {
        const Project &  rhs = dynamic_cast<const Project &>(value);

        if (m_eobjList < rhs.m_eobjList) return true;
        if (rhs.m_eobjList < m_eobjList) return false;

        if (m_projectName < rhs.m_projectName) return true;
        if (rhs.m_projectName < m_projectName) return false;

        if (m_docment < rhs.m_docment) return true;
        if (rhs.m_docment < m_docment) return false;

    } catch (const std::bad_cast &) {
        ;
    }
    return false;
}

std::string
Project::serialize() const
{
    std::string  res;

    xu::append(res, this->EObject::serialize());

    xu::append(res, xu::toString(m_eobjList));
    xu::append(res, xu::toString(m_projectName));
    xu::append(res, xu::toString(m_docment));

    return res;
}

bool
Project::deserialize(const char *  data,
                     const size_t  size)
{
    Project  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 3) {
        if (!me.EObject::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

        if (!xu::fromString(me.m_eobjList, vi[1]))  err.push_back({1});
        if (!xu::fromString(me.m_projectName, vi[2]))  err.push_back({2});
        if (!xu::fromString(me.m_docment, vi[3]))  err.push_back({3});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
Project::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        Project &  rhs = dynamic_cast<Project &>(value);
        this->EObject::exchange(rhs);

        using std::swap;
        swap(m_eobjList, rhs.m_eobjList);
        swap(m_projectName, rhs.m_projectName);
        swap(m_docment, rhs.m_docment);

        result = true;
    }
    return result;
}

}
