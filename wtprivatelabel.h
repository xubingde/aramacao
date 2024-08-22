#pragma once

#ifndef XU_WTPRIVATELABEL_H_
#define XU_WTPRIVATELABEL_H_

#include "wtbase.h"
#include "privatelabel.h"
#include "codeeditor.h"

namespace xu {

class WtPrivateLabel;

class WtPrivateLabel : public WtBase
{

    Q_OBJECT

public:

    WtPrivateLabel(QWidget *  parent = nullptr);
    virtual ~WtPrivateLabel() noexcept;

    void  beforeCode_textChanged();
    void  behindCode_textChanged();

    PrivateLabel *  getObjPtr() const;
    void  setObjPtr(PrivateLabel *  value);

protected:

private:

    PrivateLabel *      m_objPtr;
    CodeEditor *    m_beforeCode;
    CodeEditor *    m_behindCode;
};

}

#endif
