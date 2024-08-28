#pragma once

#ifndef XU_WTMYSTRUCT_H_
#define XU_WTMYSTRUCT_H_

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include "wtbase.h"
#include "mystruct.h"

namespace xu {

class WtMyStruct;

class WtMyStruct : public WtBase
{

    Q_OBJECT

public:

    WtMyStruct(QWidget *  parent = nullptr);
    virtual ~WtMyStruct() noexcept;

    void  structName_editingFinished();
    void  attribute_editingFinished();
    void  alignas_editingFinished();
    void  beforBehindPb_clicked();
    void  docmentEdit_textChanged();
    void  structItemConnect();
    void  structItem_AddItem_triggered();
    void  structItem_InsertNew_triggered();
    void  structItem_Delete_triggered();
    void  structItem_CopyToNew_triggered();
    void  structItem_Up_triggered();
    void  structItem_Down_triggered();
    void  structItem_MoveToRow_triggered();
    void  structItem_BeforBehind_triggered();
    void  structItem_itemDelegate_closeEditor();

    MyStruct *  getObjPtr() const;
    void  setObjPtr(MyStruct *  value);

protected:

private:

    void  repStructItem();
    bool  nameCheckDuplication(std::string const &  fnName);

    MyStruct *      m_objPtr;
    QLineEdit *     m_structName;
    QLineEdit *     m_attribute;
    QLineEdit *     m_alignas;
    QPushButton *   m_beforBehindPb;
    QTextEdit *     m_docmentEdit;
    QTableView *    m_structItemView;
    QStandardItemModel *    m_structItemModel;
};

}

#endif
