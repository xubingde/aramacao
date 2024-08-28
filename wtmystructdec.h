#pragma once

#ifndef XU_WTMYSTRUCTDEC_H_
#define XU_WTMYSTRUCTDEC_H_

#include <QLineEdit>
#include <QStandardItem>
#include "wtbase.h"
#include "mystructdec.h"
#include "codeeditor.h"

namespace xu {

class WtMyStructDec;

class MyStruct;

class WtMyStructDec : public WtBase
{

    Q_OBJECT

public:

    WtMyStructDec(QWidget *  parent = nullptr);
    virtual ~WtMyStructDec() noexcept;

    void  beforeCode_textChanged();
    void  behindCode_textChanged();
    void  structNameEdit_editingFinished();

    MyStructDec *  getObjPtr() const;
    void  setObjPtr(MyStructDec *  value);

protected:

private:

    void  updatePtr();

    MyStructDec *   m_objPtr;
    CodeEditor *    m_beforeCode;
    CodeEditor *    m_behindCode;
    QLineEdit *     m_structNameEdit;
};

}

#endif
