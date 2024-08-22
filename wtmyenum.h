#pragma once

#ifndef XU_WTMYENUM_H_
#define XU_WTMYENUM_H_

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include "wtbase.h"
#include "myenum.h"

namespace xu {

class WtMyEnum;

class WtMyEnum : public WtBase
{

    Q_OBJECT

public:

    WtMyEnum(QWidget *  parent = nullptr);
    virtual ~WtMyEnum() noexcept;

    void  enumName_editingFinished();
    void  enumType_editingFinished();
    void  beforBehindPb_clicked();
    void  docmentEdit_textChanged();
    void  enumItemConnect();
    void  enum_AddItem_triggered();
    void  enum_InsertNew_triggered();
    void  enum_Delete_triggered();
    void  enum_CopyToNew_triggered();
    void  enum_Up_triggered();
    void  enum_Down_triggered();
    void  enum_MoveToRow_triggered();
    void  enum_BeforBehind_triggered();
    void  enum_itemDelegate_closeEditor();

    MyEnum *  getObjPtr() const;
    void  setObjPtr(MyEnum *  value);

    QStandardItem *  getItemPtr() const;
    void  setItemPtr(QStandardItem *  value);

protected:

private:

    void  repEnumItem();
    bool  nameCheckDuplication(std::string const &  fnName);

    MyEnum *        m_objPtr;
    QStandardItem *     m_itemPtr;
    QLineEdit *     m_enumName;
    QLineEdit *     m_enumType;
    QPushButton *   m_beforBehindPb;
    QTextEdit *     m_docmentEdit;
    QTableView *    m_enumItemView;
    QStandardItemModel *    m_enumItemModel;
};

}

#endif
