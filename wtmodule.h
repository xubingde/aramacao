#pragma once

#ifndef XU_WTMODULE_H_
#define XU_WTMODULE_H_

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
#include "module.h"
#include "comboboxdelegate.h"

namespace xu {

class WtModule;

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

class WtModule : public WtBase
{

    Q_OBJECT

public:

    WtModule(QWidget *  parent = nullptr);
    virtual ~WtModule() noexcept;

    void  filename_editingFinished();
    void  hStart_editingFinished();
    void  extension_currentIndexChanged(int  index);
    void  isHeaderOnly_stateChanged(int  state);
    void  mainTab_tabBarClicked(int const  index);
    void  docment_textChanged();
    void  cppGlobalCode_textChanged();
    void  cppEndCode_textChanged();
    void  namespaceConnect();
    void  namespace_Add_triggered();
    void  namespace_InsertNew_triggered();
    void  namespace_Delete_triggered();
    void  namespace_Up_triggered();
    void  namespace_Down_triggered();
    void  namespace_MoveTo_triggered();
    void  namespace_HBeforBehind_triggered();
    void  namespace_CppBeforBehind_triggered();
    void  namespace_itemDelegate_closeEditor();
    void  hIncludeConnect();
    void  hinclude_Add_triggered();
    void  hinclude_InsertNew_triggered();
    void  hinclude_Delete_triggered();
    void  hinclude_Up_triggered();
    void  hinclude_Down_triggered();
    void  hinclude_MoveToRow_triggered();
    void  hinclude_BeforBehind_triggered();
    void  hinclude_MoveToCpp_triggered();
    void  hinclude_itemDelegate_closeEditor();
    void  cppIncludeConnect();
    void  cppinclude_Add_triggered();
    void  cppinclude_InsertNew_triggered();
    void  cppinclude_Delete_triggered();
    void  cppinclude_Up_triggered();
    void  cppinclude_Down_triggered();
    void  cppinclude_MoveToRow_triggered();
    void  cppinclude_MoveToH_triggered();
    void  cppinclude_BeforBehind_triggered();
    void  cppinclude_itemDelegate_closeEditor();
    void  dotHConnect();
    void  dotH_Previous_triggered();
    void  dotH_Update_triggered();
    void  dotCppConnect();
    void  dotCpp_Previous_triggered();
    void  dotCpp_Update_triggered();

    Module *  getObjPtr() const;
    void  setObjPtr(Module *  value);

protected:

private:

    void  init_obj();
    void  connect_obj();
    void  display_obj();
    void  fillData();
    void  repNamespace();
    void  repHInclude();
    void  repCppInclude();

    Module *        m_objPtr;
    QLineEdit *     m_filename;
    QLineEdit *     m_hStart;
    QComboBox *     m_extension;
    QCheckBox *     m_isHeaderOnly;
    QTabWidget *    m_mainTab;
    QTextEdit *     m_docment;
    QTableView *    m_namespaceView;
    QStandardItemModel *    m_namespaceModel;
    QTableView *    m_hIncludeView;
    QStandardItemModel *    m_hIncludeModel;
    QTableView *    m_cppIncludeView;
    QStandardItemModel *    m_cppIncludeModel;
    CodeEditor *    m_cppGlobalCode;
    CodeEditor *    m_cppEndCode;
    CodeEditor *    m_dotH;
    CodeEditor *    m_dotCpp;
};

}

#endif
