#pragma once

#ifndef XU_WTFN_H_
#define XU_WTFN_H_

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QListView>
#include <QTableView>
#include <QStandardItemModel>
#include <QFrame>
#include "wtbase.h"
#include "codeeditor.h"
#include "function.h"

namespace xu {

class WtFn;

class WtFn : public WtBase
{

    Q_OBJECT

public:

    WtFn(QWidget *  parent = nullptr);
    virtual ~WtFn() noexcept;

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
    void  isInline_stateChanged(int  status);
    void  isConst_stateChanged(int  status);
    void  isExplicit_stateChanged(int  status);
    void  isPureVirtual_stateChanged(int  status);
    void  isVirtual_stateChanged(int  status);
    void  isOverride_stateChanged(int  status);
    void  isFinal_stateChanged(int  status);
    void  isNoexcept_stateChanged(int  status);
    void  friendClassConnect();
    void  friendClass_Add_triggered();
    void  friendClass_InsertNew_triggered();
    void  friendClass_Delete_triggered();
    void  friendClass_Up_triggered();
    void  friendClass_Down_triggered();
    void  friendClass_MoveToRow_triggered();
    void  friendClass_itemDelegate_closeEditor();

    Function *  getObjPtr() const;
    void  setObjPtr(Function *  value);

protected:

private:

    void  repParameterItem();
    void  repFriendItem();
    bool  nameCheckDuplication(std::string const &  fnName);
    void  setVisible();

    Function *      m_objPtr;
    QLineEdit *     m_functionName;
    QLineEdit *     m_returnType;
    QLineEdit *     m_attribute;
    QPushButton *   m_beforBehindPb;
    CodeEditor *    m_codeEdit;
    QTableView *    m_parameterView;
    QStandardItemModel *    m_parameterModel;
    QListView *     m_friendClassView;
    QStandardItemModel *    m_friendClassModel;
    QLabel *        m_friendLabel;
    QFrame *        m_hideWindow;
    QCheckBox *     m_isEnabled;
    QCheckBox *     m_isInline;
    QCheckBox *     m_isConst;
    QCheckBox *     m_isExplicit;
    QCheckBox *     m_isPureVirtual;
    QCheckBox *     m_isVirtual;
    QCheckBox *     m_isOverride;
    QCheckBox *     m_isFinal;
    QCheckBox *     m_isNoexcept;
};

}

#endif
