#pragma once

#ifndef XU_WTPROTECTEDLABEL_H_
#define XU_WTPROTECTEDLABEL_H_

#include "wtbase.h"
#include "protectedlabel.h"
#include "codeeditor.h"

namespace xu {

class WtProtectedLabel;

class WtProtectedLabel : public WtBase
{

    Q_OBJECT

public:

    WtProtectedLabel(QWidget *  parent = nullptr);
    virtual ~WtProtectedLabel() noexcept;

    void  beforeCode_textChanged();
    void  behindCode_textChanged();

    ProtectedLabel *  getObjPtr() const;
    void  setObjPtr(ProtectedLabel *  value);

protected:

private:

    ProtectedLabel *    m_objPtr;
    CodeEditor *    m_beforeCode;
    CodeEditor *    m_behindCode;
};

}

#endif
