#pragma once

#ifndef XU_WTBASICBLOCK_H_
#define XU_WTBASICBLOCK_H_

#include "wtbase.h"
#include "basicblock.h"
#include "codeeditor.h"

namespace xu {

class WtBasicBlock;

class WtBasicBlock : public WtBase
{

    Q_OBJECT

public:

    WtBasicBlock(QWidget *  parent = nullptr);
    virtual ~WtBasicBlock() noexcept;

    void  codeEditor_textChanged();

    BasicBlock *  getObjPtr() const;
    void  setObjPtr(BasicBlock *  value);

protected:

private:

    BasicBlock *    m_objPtr;
    CodeEditor *    m_codeEditor;
};

}

#endif
