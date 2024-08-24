#pragma once

#ifndef XU_MODULE_H_
#define XU_MODULE_H_

#include <string>
#include <vector>
#include <memory>
#include "includeitem.h"
#include "namespaceitem.h"
#include "eobject.h"

namespace xu {

class Module;

class Module : public EObject
{

public:

    enum class Extension {
        cpp,
        c,
        cc,
        cxx
    };

    Module();
    Module(const Module &  other);
    Module(Module &&  other) noexcept;
    virtual ~Module() noexcept;

    Module &  operator=(const Module &  other);
    Module &  operator=(Module &&  other) noexcept;

    std::string  toHCode() const;
    std::string  toCppCode() const;
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>> &  getEObjectListRef();
    std::vector<std::pair<Etype, std::shared_ptr<EObject>>> *  getEObjectListPtr();
    bool  appendEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value);
    bool  appendEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value);
    bool  updateEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value, size_t const  index);
    bool  updateEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value, size_t const  index);
    bool  insertEobjList(std::pair<Etype, std::shared_ptr<EObject>> const &  value, size_t  index);
    bool  insertEobjList(std::pair<Etype, std::shared_ptr<EObject>> &&  value, size_t  index);
    bool  deleteEobjList(size_t const  index);
    bool  takeEobjList(std::pair<Etype, std::shared_ptr<EObject>> &  result, size_t const  index);
    bool  swapEobjList(size_t const  indexLhs, size_t const  indexRhs);
    bool  moveEobjList(size_t &  indexFrom, size_t &  indexTo);

    std::vector<std::pair<Etype, std::shared_ptr<EObject>>>  getEobjList() const;

    std::string  getFilename() const;
    void  setFilename(const std::string &  value);
    void  setFilename(std::string &&  value);

    std::string  getCppGlobalCode() const;
    void  setCppGlobalCode(const std::string &  value);
    void  setCppGlobalCode(std::string &&  value);

    std::string  getCppEndCode() const;
    void  setCppEndCode(const std::string &  value);
    void  setCppEndCode(std::string &&  value);

    std::string  getHStart() const;
    void  setHStart(const std::string &  value);
    void  setHStart(std::string &&  value);

    std::string  getTestCode() const;
    void  setTestCode(const std::string &  value);
    void  setTestCode(std::string &&  value);

    std::vector<IncludeItem>  getHInclude() const;
    void  setHInclude(const std::vector<IncludeItem> &  value);
    void  setHInclude(std::vector<IncludeItem> &&  value);

    std::vector<IncludeItem>  getCppInclude() const;
    void  setCppInclude(const std::vector<IncludeItem> &  value);
    void  setCppInclude(std::vector<IncludeItem> &&  value);

    std::vector<NamespaceItem>  getNamespace() const;
    void  setNamespace(const std::vector<NamespaceItem> &  value);
    void  setNamespace(std::vector<NamespaceItem> &&  value);

    Extension  getExtension() const;
    void  setExtension(const Extension  value);

    bool  isUpdate() const;

    bool  isHeaderOnly() const;
    void  setHeaderOnly(const bool  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    void  refreshPtr();
    bool  checkEobject(std::pair<Etype, std::shared_ptr<EObject>> const &  value) const;
    std::string  begin_ifndef() const;
    std::string  end_ifndef() const;
    std::string  h_include() const;
    std::string  cpp_include() const;
    std::string  begin_namespaceH() const;
    std::string  begin_namespaceCpp() const;
    std::string  end_namespaceH() const;
    std::string  end_namespaceCpp() const;

    std::vector<std::pair<Etype, std::shared_ptr<EObject>>>  m_eobjList;
    std::string     m_filename;
    std::string     m_cppGlobalCode;
    std::string     m_cppEndCode;
    std::string     m_hStart;
    std::string     m_testCode;
    std::vector<IncludeItem>    m_hInclude;
    std::vector<IncludeItem>    m_cppInclude;
    std::vector<NamespaceItem>      m_namespace;
    Extension       m_extension;
    bool            m_update;
    bool            m_headerOnly;
};

}

#endif
