#pragma once

#ifndef XU_CODEEDITOR_H_
#define XU_CODEEDITOR_H_

#include <QPlainTextEdit>
#include <QCompleter>
#include "linenumberarea.h"

namespace xu {

class CodeEditor;

class CodeEditor : public QPlainTextEdit
{

    Q_OBJECT

public:

    CodeEditor(QWidget *  parent = nullptr);
    virtual ~CodeEditor() noexcept;

    void  lineNumberAreaPaintEvent(QPaintEvent *  event);
    int  lineNumberAreaWidth();

    QCompleter *  getCompleter() const;
    void  setCompleter(QCompleter *  value);

protected:

    void  resizeEvent(QResizeEvent *  event) override;
    void  focusInEvent(QFocusEvent *  event) override;
    void  keyPressEvent(QKeyEvent *  event) override;

private:

    void  keyPressEventProc(QKeyEvent *  event);
    void  updateLineNumberAreaWidth();
    void  updateLineNumberArea(const QRect &  rect, int  dy);
    void  highlightCurrentLine();
    void  insertCompletion(const QString &  completion);
    QString  textUnderCursor() const;

    LineNumberArea *    m_lineNumberArea;
    QCompleter *    m_completer;
    int             m_previousChar;
};

}

#endif
