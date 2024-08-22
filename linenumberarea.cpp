#include <typeinfo>
#include "linenumberarea.h"
#include "codeeditor.h"

namespace xu {

LineNumberArea::LineNumberArea(QWidget *  editor):
        QWidget(editor),
        m_codeEditor(editor)
{
}

LineNumberArea::~LineNumberArea() noexcept
{
}

QSize
LineNumberArea::sizeHint() const
{
    return QSize(dynamic_cast<CodeEditor *>(m_codeEditor)->lineNumberAreaWidth(), 0);
}

void
LineNumberArea::paintEvent(QPaintEvent *  event)
{
    dynamic_cast<CodeEditor *>(m_codeEditor)->lineNumberAreaPaintEvent(event);
}

}
