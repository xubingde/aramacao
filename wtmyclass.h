#pragma once

#ifndef XU_WTMYCLASS_H_
#define XU_WTMYCLASS_H_

#include <QLineEdit>
#include <QTabWidget>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QCheckBox>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QStandardItemModel>
#include "wtbase.h"
#include "codeeditor.h"
#include "myclass.h"

namespace xu {

class WtMyClass;

class WtMyClass : public WtBase
{

    Q_OBJECT

public:

    WtMyClass(QWidget *  parent = nullptr);
    virtual ~WtMyClass() noexcept;

    void  className_editingFinished();
    void  attribute_editingFinished();
    void  alignas_editingFinished();
    void  beforBehindPb_clicked();
    void  docmentEdit_textChanged();
    void  fieldConnect();
    void  field_AddItem_triggered();
    void  field_InsertNew_triggered();
    void  field_Delete_triggered();
    void  field_CopyToNew_triggered();
    void  field_Up_triggered();
    void  field_Down_triggered();
    void  field_MoveToRow_triggered();
    void  field_BeforBehind_triggered();
    void  field_itemDelegate_closeEditor();
    void  field_selectChanged();
    void  field_attribute_editingFinished();
    void  field_array_editingFinished();
    void  field_alignas_editingFinished();
    void  field_docment_textChanged();
    void  field_isMutable_stateChanged(int const  status);

    MyClass *  getObjPtr() const;
    void  setObjPtr(MyClass *  value);

protected:

private:

    void  init_obj();
    void  connect_obj();
    void  display_obj();
    void  fillData();
    void  repField();
    bool  nameCheckDuplication(std::string const &  fnName);

    MyClass *       m_objPtr;
    QLineEdit *     m_className;
    QLineEdit *     m_attribute;
    QLineEdit *     m_alignas;
    QPushButton *   m_beforBehindPb;
    QTabWidget *    m_mainTab;
    QTextEdit *     m_docmentClass;
    QCheckBox *     m_isFinalClass;
    QCheckBox *     m_isSetterReturnThis;
    QCheckBox *     m_isTemplate;
    QButtonGroup *      m_classTypeGroup;
    QRadioButton *      m_finalClass;
    QRadioButton *      m_baseClass;
    QRadioButton *      m_inheritClass;
    QTableView *    m_templateView;
    QStandardItemModel *    m_templateModel;
    QLineEdit *     m_classNameInherit;
    QCheckBox *     m_inheritIsVirtual;
    QButtonGroup *      m_inheritIdGroup;
    QRadioButton *      m_baseId;
    QRadioButton *      m_borthId;
    QRadioButton *      m_inheritId;
    QTableView *    m_mulInhClassView;
    QStandardItemModel *    m_mulInhClassModel;
    QTableView *    m_fieldView;
    QStandardItemModel *    m_fieldModel;
    QTextEdit *     m_fieldDocment;
    QLineEdit *     m_fieldAlignas;
    QLineEdit *     m_fieldAttribute;
    QLineEdit *     m_fieldArray;
    QCheckBox *     m_fieldIsMutable;
    QTableView *    m_fieldIdRegularView;
    QStandardItemModel *    m_fieldIdRegularModel;
    QTableView *    m_fieldIdView;
    QStandardItemModel *    m_fieldIdModel;
    QTableView *    m_fieldIdToStringView;
    QStandardItemModel *    m_fieldIdToStringModel;
    QCheckBox *     m_fieldIdIsToString;
    QTreeView *     m_fieldActionView;
    QStandardItemModel *    m_fieldActionModel;
    CodeEditor *    m_fieldActionAutoCode;
    QTextEdit *     m_fieldActionDoc;
    QLineEdit *     m_fieldActionAttribute;
    QCheckBox *     m_fieldActionInline;
    QCheckBox *     m_fieldActionNoexcept;
    QCheckBox *     m_fieldActionVirtual;
    QCheckBox *     m_fieldActionOverride;
    QCheckBox *     m_fieldActionFinal;
    QTableView *    m_fieldActionDelIdxView;
    QStandardItemModel *    m_fieldActionDelIdxModel;
    QTableView *    m_fieldActionInsertIdxView;
    QStandardItemModel *    m_fieldActionInsertIdxModel;
    CodeEditor *    m_fieldActionInsertCode;
};

}

#endif
