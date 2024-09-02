#pragma once

#ifndef XU_WTPROJECT_H_
#define XU_WTPROJECT_H_

#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QStandardItem>
#include "wtbase.h"
#include "project.h"

namespace xu {

class WtProject;

class WtProject : public WtBase
{

    Q_OBJECT

public:

    WtProject(QWidget *  parent = nullptr);
    virtual ~WtProject() noexcept;

    void  projectName_editingFinished();
    void  projectDir_editingFinished();
    void  docmentEdit_textChanged();

    Project *  getObjPtr() const;
    void  setObjPtr(Project *  value);

protected:

private:

    Project *       m_objPtr;
    QLineEdit *     m_projectName;
    QLineEdit *     m_projectDir;
    QTextEdit *     m_docmentEdit;
};

}

#endif
