#pragma once

#ifndef XU_FOURBEFOREBEHIND_H_
#define XU_FOURBEFOREBEHIND_H_

#include <QDialog>
#include <string>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "codeeditor.h"

namespace xu {

class FourBeforeBehind;

class FourBeforeBehind : public QDialog
{

    Q_OBJECT

public:

    FourBeforeBehind(const std::string &  title, const QString &  beforeFirstLabel, const QString &  behindFirstLabel, std::string &  beforeFirst, std::string &  behindFirst, const QString &  beforeSecondLabel, const QString &  behindSecondLabel, std::string &  beforeSecond, std::string &  behindSecond, QWidget *  parent = nullptr);
    virtual ~FourBeforeBehind() noexcept;

    void  beforeFirstEdit_textChanged();
    void  behindFirstEdit_textChanged();
    void  beforeSecondEdit_textChanged();
    void  behindSecondEdit_textChanged();

protected:

private:

    QLabel *        m_titleLabel;
    std::string &   m_beforeFirst;
    std::string &   m_behindFirst;
    CodeEditor *    m_beforeFirstEdit;
    CodeEditor *    m_behindFirstEdit;
    std::string &   m_beforeSecond;
    std::string &   m_behindSecond;
    CodeEditor *    m_beforeSecondEdit;
    CodeEditor *    m_behindSecondEdit;
    QDialogButtonBox *      m_buttonBox;
};

}

#endif
