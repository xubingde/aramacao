#pragma once

#ifndef XU_WTCTORFN_H_
#define XU_WTCTORFN_H_

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QFrame>
#include "wtbase.h"
#include "codeeditor.h"
#include "function.h"

namespace xu {

class WtCtorFn;

class WtCtorFn : public WtBase
{

    Q_OBJECT

public:

    WtCtorFn(QWidget *  parent = nullptr);
    virtual ~WtCtorFn() noexcept;

    void  baseClassDefVal_editingFinished();
    void  attribute_editingFinished();
    void  beforBehindPb_clicked();
    void  codeEdit_textChanged();
    void  parameterItemConnect();
    void  param_AddNew_triggered();
    void  param_InsertNew_triggered();
    void  param_Delete_triggered();
    void  param_CopyToNew_triggered();
    void  param_Up_triggered();
    void  param_Down_triggered();
    void  param_MoveToRow_triggered();
    void  param_BeforBehind_triggered();
    void  param_itemDelegate_closeEditor();
    void  isEnabled_stateChanged(int  status);
    void  isInline_stateChanged(int  status);
    void  isExplicit_stateChanged(int  status);
    void  isNoexcept_stateChanged(int  status);
    void  fieldVal_itemDelegate_closeEditor();
    void  baseClassVal_itemDelegate_closeEditor();

    Function *  getObjPtr() const;
    void  setObjPtr(Function *  value);

protected:

private:

    void  repParameterItem();
    void  repFieldValItem();
    void  repBaseClassValItem();
    bool  nameCheckDuplication(std::string const &  fnName);

    Function *      m_objPtr;
    QLineEdit *     m_baseClassDefVal;
    QLineEdit *     m_attribute;
    QPushButton *   m_beforBehindPb;
    CodeEditor *    m_codeEdit;
    QTableView *    m_parameterView;
    QStandardItemModel *    m_parameterModel;
    QTableView *    m_fieldValView;
    QStandardItemModel *    m_fieldValModel;
    QTableView *    m_baseClassValView;
    QStandardItemModel *    m_baseClassValModel;
    QCheckBox *     m_isEnabled;
    QCheckBox *     m_isInline;
    QCheckBox *     m_isExplicit;
    QCheckBox *     m_isNoexcept;
};

}

#endif
