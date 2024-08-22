#pragma once

#ifndef XU_BASICBLOCK_H_
#define XU_BASICBLOCK_H_

#include <string>
#include "eobject.h"

namespace xu {

class BasicBlock;

class BasicBlock : public EObject
{

public:

    BasicBlock();
    BasicBlock(const BasicBlock &  other);
    BasicBlock(BasicBlock &&  other) noexcept;
    virtual ~BasicBlock() noexcept;

    BasicBlock &  operator=(const BasicBlock &  other);
    BasicBlock &  operator=(BasicBlock &&  other) noexcept;

    virtual std::string  toHBlock(std::string const &  tabStr = std::string()) const override;

    std::string  getSourceCode() const;
    virtual void  setSourceCode(const std::string &  value);
    virtual void  setSourceCode(std::string &&  value);

protected:

    virtual bool  equal(const EObject &  value) const override;
    virtual bool  less(const EObject &  value) const override;
    virtual bool  exchange(EObject &  value) noexcept override;
    virtual std::string  serialize() const override;
    virtual bool  deserialize(const char *  data, const size_t  size) override;

private:

    std::string     m_sourceCode;
};

}

#endif
