#pragma once

#ifndef XU_WTLABEL_H_
#define XU_WTLABEL_H_

#include <QLineEdit>
#include <QStandardItem>
#include "wtbase.h"
#include "label.h"
#include "codeeditor.h"

namespace xu {

class WtLabel;

class WtLabel : public WtBase
{

    Q_OBJECT

public:

    WtLabel(QWidget *  parent = nullptr);
    virtual ~WtLabel() noexcept;

    void  beforeCode_textChanged();
    void  behindCode_textChanged();
    void  labelValueEdit_editingFinished();

    Label *  getObjPtr() const;
    void  setObjPtr(Label *  value);

protected:

private:

    Label *         m_objPtr;
    CodeEditor *    m_beforeCode;
    CodeEditor *    m_behindCode;
    QLineEdit *     m_labelValueEdit;
};

}

#endif
