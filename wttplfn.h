#pragma once

#ifndef XU_WTTPLFN_H_
#define XU_WTTPLFN_H_

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QListView>
#include <QTableView>
#include <QStandardItemModel>
#include "wtbase.h"
#include "codeeditor.h"
#include "function.h"

namespace xu {

class WtTplFn;

class WtTplFn : public WtBase
{

    Q_OBJECT

public:

    WtTplFn(QWidget *  parent = nullptr);
    virtual ~WtTplFn() noexcept;

    void  functionName_editingFinished();
    void  returnType_editingFinished();
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
    void  isConst_stateChanged(int  status);
    void  isNoexcept_stateChanged(int  status);
    void  friendClassConnect();
    void  friendClass_Add_triggered();
    void  friendClass_InsertNew_triggered();
    void  friendClass_Delete_triggered();
    void  friendClass_Up_triggered();
    void  friendClass_Down_triggered();
    void  friendClass_MoveToRow_triggered();
    void  friendClass_itemDelegate_closeEditor();
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

    QStandardItem *  getItemPtr() const;
    void  setItemPtr(QStandardItem *  value);

protected:

private:

    void  repParamTplItem();
    void  repParameterItem();
    void  repFriendItem();
    bool  nameCheckDuplication(std::string const &  fnName);
    void  setVisible();

    Function *      m_objPtr;
    QStandardItem *     m_itemPtr;
    QLineEdit *     m_functionName;
    QLineEdit *     m_returnType;
    QLineEdit *     m_attribute;
    QPushButton *   m_beforBehindPb;
    CodeEditor *    m_codeEdit;
    QTableView *    m_paramTplView;
    QStandardItemModel *    m_paramTplModel;
    QTableView *    m_parameterView;
    QStandardItemModel *    m_parameterModel;
    QListView *     m_friendClassView;
    QStandardItemModel *    m_friendClassModel;
    QLabel *        m_friendLabel;
    QCheckBox *     m_isEnabled;
    QCheckBox *     m_isConst;
    QCheckBox *     m_isNoexcept;
};

}

#endif
