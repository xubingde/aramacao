#pragma once

#ifndef XU_LABEL_H_
#define XU_LABEL_H_

#include <string>
#include "eobject.h"

namespace xu {

class Label;

class Label : public EObject
{

public:

    Label();
    Label(const Label &  other);
    Label(Label &&  other) noexcept;
    virtual ~Label() noexcept;

    Label &  operator=(const Label &  other);
    Label &  operator=(Label &&  other) noexcept;

    virtual std::string  toHBlock(std::string const &  tabStr = std::string()) const override;

    std::string  getLabelValue() const;
    virtual void  setLabelValue(const std::string &  value);

    std::string  getBefore() const;
    virtual void  setBefore(const std::string &  value);
    virtual void  setBefore(std::string &&  value);

    std::string  getBehind() const;
    virtual void  setBehind(const std::string &  value);
    virtual void  setBehind(std::string &&  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    std::string     m_labelValue;
    std::string     m_before;
    std::string     m_behind;
};

}

#endif
