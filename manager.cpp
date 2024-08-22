#include <cstring>
#include <tuple>
#include "manager.h"
#include "icode.h"
#include "fmt.h"
#include "publictype.h"

namespace xu {

std::string
toString(std::vector<std::shared_ptr<Project>> const &  value)
{
    std::string  res;
    for (auto const &  it: value) {
        xu::append(res, it->toString());
    }
    return res;
}

bool
fromString(std::vector<std::shared_ptr<Project>> &  res,
           std::string const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::shared_ptr<Project>> &  res,
           std::string_view const &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::vector<std::shared_ptr<Project>> &  res,
           char const *  data,
           size_t const  size)
{
    std::vector<std::shared_ptr<Project>>  resTmp;
    auto  vi = xu::viewIcode(data, size);
    size_t const  viSize = vi.size();
    for (size_t  i = 0; i < viSize; ++i) {
        Project  prj;
        if (!xu::fromString(prj, vi[i]))  return false;
        std::shared_ptr<Project>  objPtr = std::make_shared<Project>(std::move(prj));
        resTmp.push_back(objPtr);
    }
    res = std::move(resTmp);
    return true;
}

Manager::Manager():
        m_eobjList(),
        m_id(0)
{
}

Manager::Manager(const Manager &  other):
        m_eobjList(other.m_eobjList),
        m_id(other.m_id)
{
}

Manager::Manager(Manager &&  other) noexcept:
        m_eobjList(std::move(other.m_eobjList)),
        m_id(std::move(other.m_id))
{
}

Manager::~Manager() noexcept
{
}

Manager &
Manager::operator=(const Manager &  other)
{
    if (this == &other) return *this;

    m_eobjList = other.m_eobjList;
    m_id = other.m_id;

    return *this;
}

Manager &
Manager::operator=(Manager &&  other) noexcept
{
    if (this == &other) return *this;

    m_eobjList = std::move(other.m_eobjList);
    m_id = std::move(other.m_id);

    return *this;
}

std::vector<std::shared_ptr<Project>> &
Manager::getProjectListRef()
{
    return m_eobjList;
}

Project &
Manager::getProjectRef(size_t  index)
{
    if (index > m_eobjList.size()) {
        index = m_eobjList.size();
    }
    return *m_eobjList[index];
}

bool
Manager::getProject(Project &  result,
                    size_t const  index)
{
    if (index < m_eobjList.size()) {
        result = *m_eobjList[index];
        return true;
    }
    return false;
}

void
Manager::appendEobjList(Project const &  value)
{
    std::shared_ptr<Project>  obj = std::make_shared<Project>(value);
    m_eobjList.push_back(obj);
}

void
Manager::appendEobjList(Project &&  value)
{
    std::shared_ptr<Project>  obj = std::make_shared<Project>(std::move(value));
    m_eobjList.push_back(obj);
}

bool
Manager::updateEobjList(Project const &  value,
                        size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size()) {
        std::shared_ptr<Project>  obj = std::make_shared<Project>(value);
        m_eobjList[index] = obj;
        res = true;
    }
    return res;
}

bool
Manager::updateEobjList(Project &&  value,
                        size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size()) {
        std::shared_ptr<Project>  obj = std::make_shared<Project>(std::move(value));
        m_eobjList[index] = obj;
        res = true;
    }
    return res;
}

void
Manager::insertEobjList(Project const &  value,
                        size_t  index)
{
    if (index > m_eobjList.size()) {
        index = m_eobjList.size();
    }
    std::shared_ptr<Project>  obj = std::make_shared<Project>(value);
    m_eobjList.insert(m_eobjList.begin() + index, obj);
}

void
Manager::insertEobjList(Project &&  value,
                        size_t  index)
{
    if (index > m_eobjList.size()) {
        index = m_eobjList.size();
    }
    std::shared_ptr<Project>  obj = std::make_shared<Project>(std::move(value));
    m_eobjList.insert(m_eobjList.begin() + index, obj);
}

bool
Manager::deleteEobjList(size_t const  index)
{
    bool  res = false;

    if (index < m_eobjList.size()) {
        m_eobjList.erase(m_eobjList.begin() + index);
        res = true;
    }

    return res;
}

bool
Manager::takeEobjList(Project &  result,
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
Manager::swapEobjList(size_t const  indexLhs,
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
Manager::moveEobjList(size_t &  indexFrom,
                      size_t &  indexTo)
{
    if (xu::moveVec_1(m_eobjList, indexFrom, indexTo)) {
        return true;
    }
    return false;
}

void
Manager::clearEobjList()
{
    m_eobjList.clear();
}

std::vector<std::shared_ptr<Project>>
Manager::getEobjList() const
{
    return m_eobjList;
}

void
Manager::setEobjList(const std::vector<std::shared_ptr<Project>> &  value)
{
    m_eobjList = value;
}

void
Manager::setEobjList(std::vector<std::shared_ptr<Project>> &&  value)
{
    m_eobjList = std::move(value);
}

int
Manager::getId() const
{
    return m_id;
}

void
Manager::setId(const int  value)
{
    m_id = value;
}

bool
operator==(const Manager &  lhs,
           const Manager &  rhs)
{
    if (&lhs == &rhs) return true;
    bool  result = false;

    result = ( lhs.m_eobjList == rhs.m_eobjList );
    if (!result) return result;

    result = ( lhs.m_id == rhs.m_id );
    if (!result) return result;

    return result;
}

bool
operator!=(const Manager &  lhs,
           const Manager &  rhs)
{
    return !(lhs == rhs);
}

bool
operator<(const Manager &  lhs,
          const Manager &  rhs)
{
    if (&lhs == &rhs) return false;

    if (lhs.m_eobjList < rhs.m_eobjList) return true;
    if (rhs.m_eobjList < lhs.m_eobjList) return false;

    if (lhs.m_id < rhs.m_id) return true;
    if (rhs.m_id < lhs.m_id) return false;

    return false;
}

bool
operator<=(const Manager &  lhs,
           const Manager &  rhs)
{
    return !(lhs > rhs);
}

bool
operator>(const Manager &  lhs,
          const Manager &  rhs)
{
    return rhs < lhs;
}

bool
operator>=(const Manager &  lhs,
           const Manager &  rhs)
{
    return !(lhs < rhs);
}

std::string
Manager::toString() const
{
    std::string  res;

    xu::append(res, xu::toString(m_eobjList));
    xu::append(res, xu::toString(m_id));

    return res;
}

bool
Manager::fromString(const char *  data,
                    const size_t  size)
{
    Manager  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 1) {
        if (!xu::fromString(me.m_eobjList, vi[0]))  err.push_back({0});
        if (!xu::fromString(me.m_id, vi[1]))  err.push_back({1});
    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
fromString(Manager &  value,
           const char *  data,
           const size_t  size)
{
    return value.fromString(data, size);
}

void
swap(Manager &  lhs,
     Manager &  rhs) noexcept
{
    lhs.swap(rhs);
}

void
Manager::swap(Manager &  value) noexcept
{
    if (this == &value) return;
    using std::swap;
    swap(m_eobjList, value.m_eobjList);
    swap(m_id, value.m_id);
}

}
