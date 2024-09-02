#pragma once

#ifndef XU_PROJECT_H_
#define XU_PROJECT_H_

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include "module.h"
#include "eobject.h"

namespace xu {

class Project;

std::string  toString(std::vector<std::shared_ptr<Module>> const &  value);
bool  fromString(std::vector<std::shared_ptr<Module>> &  res, std::string const &  value);
bool  fromString(std::vector<std::shared_ptr<Module>> &  res, std::string_view const &  value);
bool  fromString(std::vector<std::shared_ptr<Module>> &  res, char const *  data, size_t const  size);

class Project : public EObject
{

public:

    Project();
    Project(const Project &  other);
    Project(Project &&  other) noexcept;
    virtual ~Project() noexcept;

    Project &  operator=(const Project &  other);
    Project &  operator=(Project &&  other) noexcept;

    std::vector<std::shared_ptr<Module>> &  getModuleListRef();
    Module &  getModuleRef(size_t  index);
    bool  getModule(Module &  result, size_t const  index);
    void  appendEobjList(Module const &  value);
    void  appendEobjList(Module &&  value);
    bool  updateEobjList(Module const &  value, size_t const  index);
    bool  updateEobjList(Module &&  value, size_t const  index);
    void  insertEobjList(Module const &  value, size_t  index);
    void  insertEobjList(Module &&  value, size_t  index);
    bool  deleteEobjList(size_t const  index);
    bool  takeEobjList(Module &  result, size_t const  index);
    bool  swapEobjList(size_t const  indexLhs, size_t const  indexRhs);
    bool  moveEobjList(size_t &  indexFrom, size_t &  indexTo);

    std::vector<std::shared_ptr<Module>>  getEobjList() const;
    void  setEobjList(const std::vector<std::shared_ptr<Module>> &  value);
    void  setEobjList(std::vector<std::shared_ptr<Module>> &&  value);

    std::string  getProjectName() const;
    void  setProjectName(const std::string &  value);
    void  setProjectName(std::string &&  value);

    std::string  getDocment() const;
    void  setDocment(const std::string &  value);
    void  setDocment(std::string &&  value);

    std::string  getDir() const;
    void  setDir(const std::string &  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    std::vector<std::shared_ptr<Module>>    m_eobjList;
    std::string     m_projectName;
    std::string     m_docment;
    std::string     m_dir;
};

}

#endif
