#pragma once

#ifndef XU_WTTPLCTORFN_H_
#define XU_WTTPLCTORFN_H_

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

class WtTplCtorFn;

class WtTplCtorFn : public WtBase
{

    Q_OBJECT

public:

    WtTplCtorFn(QWidget *  parent = nullptr);
    virtual ~WtTplCtorFn() noexcept;

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
    void  isExplicit_stateChanged(int  status);
    void  isNoexcept_stateChanged(int  status);
    void  fieldVal_itemDelegate_closeEditor();
    void  baseClassVal_itemDelegate_closeEditor();
    void  paramTplItemConnect();
    void  paramTpl_AddNew_triggered();
    void  paramTpl_InsertNew_triggered();
    void  paramTpl_Delete_triggered();
    void  paramTpl_CopyToNew_triggered();
    void  paramTpl_Up_triggered();
    void  paramTpl_Down_triggered();
    void  paramTpl_MoveToRow_triggered();
    void  paramTpl_itemDelegate_closeEditor();

    Function *  getObjPtr() const;
    void  setObjPtr(Function *  value);

protected:

private:

    void  repParamTplItem();
    void  repParameterItem();
    void  repFieldValItem();
    void  repBaseClassValItem();
    bool  nameCheckDuplication(std::string const &  fnName);

    Function *      m_objPtr;
    QLineEdit *     m_baseClassDefVal;
    QLineEdit *     m_attribute;
    QPushButton *   m_beforBehindPb;
    CodeEditor *    m_codeEdit;
    QTableView *    m_paramTplView;
    QStandardItemModel *    m_paramTplModel;
    QTableView *    m_parameterView;
    QStandardItemModel *    m_parameterModel;
    QTableView *    m_fieldValView;
    QStandardItemModel *    m_fieldValModel;
    QTableView *    m_baseClassValView;
    QStandardItemModel *    m_baseClassValModel;
    QCheckBox *     m_isEnabled;
    QCheckBox *     m_isExplicit;
    QCheckBox *     m_isNoexcept;
};

}

#endif
