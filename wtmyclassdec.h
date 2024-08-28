#pragma once

#ifndef XU_WTMYCLASSDEC_H_
#define XU_WTMYCLASSDEC_H_

#include <QLineEdit>
#include <QStandardItem>
#include "wtbase.h"
#include "myclassdec.h"
#include "codeeditor.h"

namespace xu {

class WtMyClassDec;

class MyClass;

class WtMyClassDec : public WtBase
{

    Q_OBJECT

public:

    WtMyClassDec(QWidget *  parent = nullptr);
    virtual ~WtMyClassDec() noexcept;

    void  beforeCode_textChanged();
    void  behindCode_textChanged();
    void  classNameEdit_editingFinished();

    MyClassDec *  getObjPtr() const;
    void  setObjPtr(MyClassDec *  value);

    QStandardItem *  getItemPtr() const;
    void  setItemPtr(QStandardItem *  value);

protected:

private:

    void  updatePtr();

    MyClassDec *    m_objPtr;
    QStandardItem *     m_itemPtr;
    CodeEditor *    m_beforeCode;
    CodeEditor *    m_behindCode;
    QLineEdit *     m_classNameEdit;
};

}

#endif
