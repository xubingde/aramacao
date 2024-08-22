#pragma once

#ifndef XU_MYTYPEDEF_H_
#define XU_MYTYPEDEF_H_

#include <string>
#include <vector>
#include "eobject.h"
#include "tpl.h"

namespace xu {

class MyTypedef;

class MyTypedef : public EObject
{

public:

    MyTypedef();
    MyTypedef(const MyTypedef &  other);
    MyTypedef(MyTypedef &&  other) noexcept;
    virtual ~MyTypedef() noexcept;

    MyTypedef &  operator=(const MyTypedef &  other);
    MyTypedef &  operator=(MyTypedef &&  other) noexcept;

    virtual std::string  toHBlock(std::string const &  tabStr = std::string()) const override;

    std::string  getName() const;
    virtual void  setName(const std::string &  value);

    std::string  getType() const;
    virtual void  setType(const std::string &  value);

    std::string  getBefore() const;
    virtual void  setBefore(const std::string &  value);
    virtual void  setBefore(std::string &&  value);

    std::string  getBehind() const;
    virtual void  setBehind(const std::string &  value);
    virtual void  setBehind(std::string &&  value);

    std::string  getDocment() const;
    virtual void  setDocment(const std::string &  value);
    virtual void  setDocment(std::string &&  value);

    std::vector<Tpl>  getTemplateItem() const;
    virtual void  setTemplateItem(const std::vector<Tpl> &  value);
    virtual void  setTemplateItem(std::vector<Tpl> &&  value);

    bool  isTemplate() const;
    virtual void  setTemplate(const bool  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    std::string     m_name;
    std::string     m_type;
    std::string     m_before;
    std::string     m_behind;
    std::string     m_docment;
    std::vector<Tpl>    m_templateItem;
    bool            m_template;
};

}

#endif
