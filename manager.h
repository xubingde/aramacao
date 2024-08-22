#pragma once

#ifndef XU_MANAGER_H_
#define XU_MANAGER_H_

#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <memory>
#include "project.h"

namespace xu {

class Manager;

std::string  toString(std::vector<std::shared_ptr<Project>> const &  value);
bool  fromString(std::vector<std::shared_ptr<Project>> &  res, std::string const &  value);
bool  fromString(std::vector<std::shared_ptr<Project>> &  res, std::string_view const &  value);
bool  fromString(std::vector<std::shared_ptr<Project>> &  res, char const *  data, size_t const  size);

bool  operator==(const Manager &  lhs, const Manager &  rhs);
bool  operator!=(const Manager &  lhs, const Manager &  rhs);
void  swap(Manager &  lhs, Manager &  rhs) noexcept;
bool  operator<(const Manager &  lhs, const Manager &  rhs);
bool  operator<=(const Manager &  lhs, const Manager &  rhs);
bool  operator>(const Manager &  lhs, const Manager &  rhs);
bool  operator>=(const Manager &  lhs, const Manager &  rhs);
bool  fromString(Manager &  value, const char *  data, const size_t  size);

class Manager final
{
friend bool  operator==(const Manager &  lhs, const Manager &  rhs);
friend bool  operator!=(const Manager &  lhs, const Manager &  rhs);
friend bool  operator<(const Manager &  lhs, const Manager &  rhs);
friend bool  operator<=(const Manager &  lhs, const Manager &  rhs);
friend bool  operator>(const Manager &  lhs, const Manager &  rhs);
friend bool  operator>=(const Manager &  lhs, const Manager &  rhs);

public:

    Manager();
    Manager(const Manager &  other);
    Manager(Manager &&  other) noexcept;
    ~Manager() noexcept;

    Manager &  operator=(const Manager &  other);
    Manager &  operator=(Manager &&  other) noexcept;

    std::string  toString() const;
    bool  fromString(const char *  data, const size_t  size);
    void  swap(Manager &  value) noexcept;

    std::vector<std::shared_ptr<Project>> &  getProjectListRef();
    Project &  getProjectRef(size_t  index);
    bool  getProject(Project &  result, size_t const  index);
    void  appendEobjList(Project const &  value);
    void  appendEobjList(Project &&  value);
    bool  updateEobjList(Project const &  value, size_t const  index);
    bool  updateEobjList(Project &&  value, size_t const  index);
    void  insertEobjList(Project const &  value, size_t  index);
    void  insertEobjList(Project &&  value, size_t  index);
    bool  deleteEobjList(size_t const  index);
    bool  takeEobjList(Project &  result, size_t const  index);
    bool  swapEobjList(size_t const  indexLhs, size_t const  indexRhs);
    bool  moveEobjList(size_t &  indexFrom, size_t &  indexTo);
    void  clearEobjList();

    std::vector<std::shared_ptr<Project>>  getEobjList() const;
    void  setEobjList(const std::vector<std::shared_ptr<Project>> &  value);
    void  setEobjList(std::vector<std::shared_ptr<Project>> &&  value);

    int  getId() const;
    void  setId(const int  value);

private:

    std::vector<std::shared_ptr<Project>>   m_eobjList;
    int             m_id;
};

}

#endif
