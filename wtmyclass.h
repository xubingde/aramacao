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
#include "comboboxdelegate.h"

namespace xu {

class WtMyClass;

class EqFn;
class NotEqFn;
class VirtualEqFn;
class LessFn;
class LessEqFn;
class VirtualLessFn;
class GreaterFn;
class GreaterEqFn;
class ExtSwapFn;
class InSwapFn;
class VirtualExchangeFn;
class ToStringFn;
class VirtualSerializeFn;
class ExtFromStringFn;
class InFromStringFn;
class DeserializeFn;

void  setItemProperty(QStandardItem *  item, Etype const  etp, std::shared_ptr<EObject>  objPtr);

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
    void  replaceClassName_editingFinished();
    void  isFinalClass_stateChanged(int const  status);
    void  isTemplate_stateChanged(int const  status);
    void  isSetterReturnThis_stateChanged(int const  status);
    void  isUpdateFilename_stateChanged(int const  status);
    void  isImpl_stateChanged(int const  status);
    void  isInternal_stateChanged(int const  status);
    void  isIndPublicLabel_stateChanged(int const  status);
    void  hasDefCtor_stateChanged(int const  status);
    void  hasCopyCtor_stateChanged(int const  status);
    void  hasMoveCtor_stateChanged(int const  status);
    void  hasDtor_stateChanged(int const  status);
    void  hasCopyOpEq_stateChanged(int const  status);
    void  hasMoveOpEq_stateChanged(int const  status);
    void  finalClass_toggled(bool const  isChecked);
    void  baseClass_toggled(bool const  isChecked);
    void  inheritClass_toggled(bool const  isChecked);
    void  mulInhClassConnect();
    void  mulInhClass_Add_triggered();
    void  mulInhClass_Delete_triggered();
    void  mulInhClass_Up_triggered();
    void  mulInhClass_Down_triggered();
    void  mulInhClass_MoveTo_triggered();
    void  mulInhClass_itemDelegate_closeEditor();
    void  mulInhClass_itemDgtForCol_closeEditor();
    void  templateConnect();
    void  template_Add_triggered();
    void  template_Delete_triggered();
    void  template_Up_triggered();
    void  template_Down_triggered();
    void  template_MoveTo_triggered();
    void  template_itemDelegate_closeEditor();
    void  friendClassConnect();
    void  friendClass_Add_triggered();
    void  friendClass_Delete_triggered();
    void  friendClass_Up_triggered();
    void  friendClass_Down_triggered();
    void  friendClass_MoveTo_triggered();
    void  friendClass_itemDelegate_closeEditor();
    void  baseClassPrarm_editingFinished();
    void  classNameInherit_editingFinished();
    void  inheritIsVirtual_stateChanged(int const  status);
    void  baseId_toggled(bool const  isChecked);
    void  borthId_toggled(bool const  isChecked);
    void  inheritId_toggled(bool const  isChecked);
    void  hasEqFunction_stateChanged(int const  status);
    void  hasLessFunction_stateChanged(int const  status);
    void  hasSwapFunction_stateChanged(int const  status);
    void  hasToStringFunction_stateChanged(int const  status);
    void  fieldIdIsToString_stateChanged(int const  status);
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
    void  fieldIdRegularConnect();
    void  fieldIdRegular_Up_triggered();
    void  fieldIdRegular_Down_triggered();
    void  fieldIdRegular_MoveTo_triggered();
    void  fieldIdConnect();
    void  fieldId_Add_triggered();
    void  fieldId_Delete_triggered();
    void  fieldId_Up_triggered();
    void  fieldId_Down_triggered();
    void  fieldId_MoveTo_triggered();
    void  fieldIdToStringConnect();
    void  fieldIdToString_Add_triggered();
    void  fieldIdToString_Delete_triggered();
    void  fieldIdToString_Up_triggered();
    void  fieldIdToString_Down_triggered();
    void  fieldIdToString_MoveTo_triggered();
    void  fieldActionConnect();
    void  fieldAction_selectChanged();
    void  fieldAction_AddActionFalse_triggered();
    void  fieldAction_AddAction(bool const  isInline);
    void  fieldAction_DeleteAction_triggered();
    void  fieldAction_InsBeforBehind_triggered();
    void  fieldActionAutoCodeConnect();
    void  fieldActionDelIdxConnect();
    void  fieldActionInsertIdxConnect();
    void  fdActAttribute_editingFinished();
    void  fdActInline_stateChanged(int const  status);
    void  fdActNoexcept_stateChanged(int const  status);
    void  fdActVirtual_stateChanged(int const  status);
    void  fdActOverride_stateChanged(int const  status);
    void  fdActFinal_stateChanged(int const  status);
    void  fdActInsertCode_textChanged();
    void  repDefCtor();
    void  repCopyCtor();
    void  repMoveCtor();
    void  repDtor();
    void  repCopyOpEq();
    void  repMoveOpEq();
    void  repInheritIsVirtual();
    void  repIsFinalClass();

    MyClass *  getObjPtr() const;
    void  setObjPtr(MyClass *  value);

protected:

private:

    void  init_obj();
    void  connect_obj();
    void  display_obj();
    void  fillData();
    void  repField();
    void  repFieldIdRegular();
    void  repFieldId();
    void  repFieldIdToString();
    void  repFieldAction();
    void  updateActionTitle(size_t const  fieldIdx);
    void  updateActionChildren(size_t const  fieldIdx);
    void  repFieldActionDelIdx();
    void  repFieldActionInsertIdx();
    void  currFieldActionInsertIdx(int const  idx = INT_MAX);
    void  repMulInhClass();
    void  repTemplateClass();
    void  repFriendClass();
    bool  nameCheckDuplication(std::string const &  fnName);
    void  setEqFn(bool const  status);
    void  setEqFnAdd(EqFn &&  fnEq, NotEqFn &&  fnNotEq, VirtualEqFn &&  fnVirtualEq);
    void  setLessFn(bool const  status);
    void  setLessFnAdd(LessFn &&  fnLess, LessEqFn &&  fnLessEq, GreaterFn &&  fnGreater, GreaterEqFn &&  fnGreaterEq, VirtualLessFn &&  fnVirtualLess);
    void  setSwapFn(bool const  status);
    void  setSwapFnAdd(ExtSwapFn &&  fnExtSwap, InSwapFn &&  fnInSwap, VirtualExchangeFn &&  fnVirtualExchange);
    void  setToStringFn(bool const  status);
    void  setToStringFnAdd(ToStringFn &&  fnToString, VirtualSerializeFn &&  fnVirtualSerialize, ExtFromStringFn &&  fnExtFromString, InFromStringFn &&  fnInFromString, DeserializeFn &&  fnDeserialize);

    MyClass *       m_objPtr;
    QLineEdit *     m_className;
    QLineEdit *     m_attribute;
    QLineEdit *     m_alignas;
    QPushButton *   m_beforBehindPb;
    QTabWidget *    m_mainTab;
    QTextEdit *     m_docmentClass;
    QLineEdit *     m_replaceClassName;
    QCheckBox *     m_isFinalClass;
    QCheckBox *     m_isSetterReturnThis;
    QCheckBox *     m_isTemplate;
    QCheckBox *     m_isUpdateFilename;
    QCheckBox *     m_isImpl;
    QCheckBox *     m_isInternal;
    QCheckBox *     m_isIndPublicLabel;
    QCheckBox *     m_hasDefCtor;
    QCheckBox *     m_hasCopyCtor;
    QCheckBox *     m_hasMoveCtor;
    QCheckBox *     m_hasDtor;
    QCheckBox *     m_hasCopyOpEq;
    QCheckBox *     m_hasMoveOpEq;
    QButtonGroup *      m_classTypeGroup;
    QRadioButton *      m_finalClass;
    QRadioButton *      m_baseClass;
    QRadioButton *      m_inheritClass;
    QLineEdit *     m_baseClassPrarm;
    QTableView *    m_templateView;
    QStandardItemModel *    m_templateModel;
    QTableView *    m_friendClassView;
    QStandardItemModel *    m_friendClassModel;
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
    QCheckBox *     m_hasLessFunction;
    QCheckBox *     m_hasEqFunction;
    QCheckBox *     m_hasSwapFunction;
    QCheckBox *     m_hasToStringFunction;
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
    CodeEditor *    m_dotH;
    CodeEditor *    m_dotCpp;
};

}

#endif
