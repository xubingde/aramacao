#pragma once

#ifndef XU_TWOBEFOREBEHIND_H_
#define XU_TWOBEFOREBEHIND_H_

#include <QDialog>
#include <string>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "codeeditor.h"

namespace xu {

class TwoBeforeBehind;

class TwoBeforeBehind : public QDialog
{

    Q_OBJECT

public:

    TwoBeforeBehind(const std::string &  title, const QString &  beforeLabel, const QString &  behindLabel, std::string &  beforeString, std::string &  behindString, QWidget *  parent = nullptr);
    virtual ~TwoBeforeBehind() noexcept;

    void  beforeEdit_textChanged();
    void  behindEdit_textChanged();

protected:

private:

    QLabel *        m_titleLabel;
    std::string &   m_beforeString;
    std::string &   m_behindString;
    CodeEditor *    m_beforeEdit;
    CodeEditor *    m_behindEdit;
    QDialogButtonBox *      m_buttonBox;
};

}

#endif
