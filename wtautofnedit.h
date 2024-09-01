#pragma once

#ifndef XU_WTAUTOFNEDIT_H_
#define XU_WTAUTOFNEDIT_H_

#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QLabel>
#include "wtbase.h"
#include "function.h"
#include "codeeditor.h"

namespace xu {

class WtAutoFnEdit;

class WtAutoFnEdit : public WtBase
{

    Q_OBJECT

public:

    WtAutoFnEdit(QWidget *  parent = nullptr);
    virtual ~WtAutoFnEdit() noexcept;

    void  insertCode_textChanged();
    void  isDefault_stateChanged(int  status);
    void  isDelete_stateChanged(int  status);
    void  attribute_editingFinished();
    void  beforBehindPb_clicked();
    void  displayCodeConnect();
    void  displayCode_Previous_triggered();
    void  displayCode_Update_triggered();
    void  deleteIndexConnect();
    void  deleteIndex_Add_triggered();
    void  deleteIndex_Delete_triggered();
    void  insertIndexConnect();
    void  insertIndex_Add_triggered();
    void  insertIndex_Delete_triggered();
    void  insertIndex_Modify_triggered();
    void  insertIndex_RowChanged();

    Function *  getObjPtr() const;
    void  setObjPtr(Function *  value);

protected:

private:

    void  repDeleteIndex();
    void  repInsertIndex();
    void  currInsert(int const  idx = INT_MAX);
    void  setVisible();

    Function *      m_objPtr;
    QLabel *        m_functionDecLabel;
    QCheckBox *     m_isDefault;
    QCheckBox *     m_isDelete;
    QLineEdit *     m_attribute;
    QPushButton *   m_beforBehindPb;
    CodeEditor *    m_displayCode;
    CodeEditor *    m_insertCode;
    QTableView *    m_deleteIndexView;
    QStandardItemModel *    m_deleteIndexModel;
    QTableView *    m_insertIndexView;
    QStandardItemModel *    m_insertIndexModel;
};

}

#endif
