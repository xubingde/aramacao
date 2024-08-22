#pragma once

#ifndef XU_WTPUBLICLABEL_H_
#define XU_WTPUBLICLABEL_H_

#include "wtbase.h"
#include "publiclabel.h"
#include "codeeditor.h"

namespace xu {

class WtPublicLabel;

class WtPublicLabel : public WtBase
{

    Q_OBJECT

public:

    WtPublicLabel(QWidget *  parent = nullptr);
    virtual ~WtPublicLabel() noexcept;

    void  beforeCode_textChanged();
    void  behindCode_textChanged();

    PublicLabel *  getObjPtr() const;
    void  setObjPtr(PublicLabel *  value);

protected:

private:

    PublicLabel *   m_objPtr;
    CodeEditor *    m_beforeCode;
    CodeEditor *    m_behindCode;
};

}

#endif
