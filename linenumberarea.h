#pragma once

#ifndef XU_LINENUMBERAREA_H_
#define XU_LINENUMBERAREA_H_

#include <QWidget>

namespace xu {

class LineNumberArea;

class LineNumberArea : public QWidget
{

    Q_OBJECT

public:

    LineNumberArea(QWidget *  editor);
    virtual ~LineNumberArea() noexcept;

    QSize  sizeHint() const override;

protected:

    void  paintEvent(QPaintEvent *  event) override;

private:

    QWidget *       m_codeEditor;
};

}

#endif
