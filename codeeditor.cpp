#include <typeinfo>
#include <algorithm>
#include <QApplication>
#include <QPainter>
#include <QTextBlock>
#include <QTextCursor>
#include <QAbstractItemView>
#include <QScrollBar>
#include "codeeditor.h"
#include "publictype.h"

namespace xu {

CodeEditor::CodeEditor(QWidget *  parent /* = nullptr */):
        QPlainTextEdit(parent),
        m_lineNumberArea(nullptr),
        m_completer(nullptr),
        m_previousChar(0)
{
    m_lineNumberArea = new LineNumberArea(this);

    connect(this, &CodeEditor::blockCountChanged,
            this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest,
            this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged,
            this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth();
    highlightCurrentLine();
}

CodeEditor::~CodeEditor() noexcept
{
}

void
CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *  event)
{
    QPainter  painter(m_lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);
    painter.setPen(Qt::black);

    QTextBlock  block = firstVisibleBlock();
    int  blockNumber = block.blockNumber();
    int  top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int  bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString  number = QString::number(blockNumber);
            painter.drawText(0, top, m_lineNumberArea->width() - 5,
                             fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

int
CodeEditor::lineNumberAreaWidth()
{
    int  digits = 1;
    int  max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    int  space = 10 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void
CodeEditor::resizeEvent(QResizeEvent *  event)
{
    QPlainTextEdit::resizeEvent(event);

    QRect  cr = contentsRect();
    m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(),
            lineNumberAreaWidth(), cr.height()));
}

void
CodeEditor::focusInEvent(QFocusEvent *  event)
{
    if (m_completer) {
        m_completer->setWidget(this);
    }
    QPlainTextEdit::focusInEvent(event);
}

void
CodeEditor::keyPressEvent(QKeyEvent *  event)
{
    if (m_completer && m_completer->popup()->isVisible()) {
        switch (event->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            event->ignore();
            return;
        default:
            break;
        }

        const bool  isShortcut = (event->modifiers().testFlag(Qt::ControlModifier) &&
                                  event->key() == Qt::Key_E);
        if (!m_completer || !isShortcut)  QPlainTextEdit::keyPressEvent(event);

        const bool  ctrlOrShift = event->modifiers().testFlag(Qt::ControlModifier) ||
                event->modifiers().testFlag(Qt::ShiftModifier);
        if (!m_completer || (ctrlOrShift && event->text().isEmpty()))  return;

        static QString  eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-=");
        const bool  hasModifier = (event->modifiers() != Qt::NoModifier) && !ctrlOrShift;
        QString  completionPrefix = textUnderCursor();

        if (!isShortcut && (hasModifier || event->text().isEmpty() ||
                            completionPrefix.length() < 3 ||
                            eow.contains(event->text().right(1)))) {
            m_completer->popup()->hide();
            return;
        }

        if (completionPrefix != m_completer->completionPrefix()) {
            m_completer->setCompletionPrefix(completionPrefix);
            m_completer->popup()->setCurrentIndex(
                        m_completer->completionModel()->index(0, 0));
        }
        QRect  cr = cursorRect();
        cr.setWidth(m_completer->popup()->sizeHintForColumn(0)
                 + m_completer->popup()->verticalScrollBar()->sizeHint().width());
        m_completer->complete(cr);

        m_previousChar = 0;
    } else {
        keyPressEventProc(event);
    }
}

void
CodeEditor::keyPressEventProc(QKeyEvent *  event)
{
    switch (event->key()) {
    case Qt::Key_Tab :
        {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, QString("    "));
            QPlainTextEdit::keyPressEvent(&e1);
            m_previousChar = 0;
        }
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return :
        {
            QTextCursor  tc = textCursor();
            int  currBlockIdx = tc.positionInBlock();
            std::string  currText = tc.block().text().toStdString();
            auto  it = std::find_if(currText.begin(), currText.end(),
                    [](const char ch)->bool {
                if (ch != ' ') {
                    return true;
                } else {
                    return false;
                }
            });
            const auto  step = std::distance(currText.begin(), it);
            const std::string  spaceBegin(step, ' ');

            if (tc.atBlockStart()) {
                QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
                QPlainTextEdit::keyPressEvent(&e1);
            } else if (currText.size() > currBlockIdx &&
                       currText[currBlockIdx - 1] == '{' &&
                       currText[currBlockIdx] == '}') {
                QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
                QPlainTextEdit::keyPressEvent(&e1);
                QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier,
                              QString::fromStdString(spaceBegin));
                QPlainTextEdit::keyPressEvent(&e2);
                QKeyEvent  e3(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
                QPlainTextEdit::keyPressEvent(&e3);
                QKeyEvent  e4(QEvent::KeyPress, Qt::Key_End, Qt::NoModifier);
                QPlainTextEdit::keyPressEvent(&e4);
                QKeyEvent  e5(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
                QPlainTextEdit::keyPressEvent(&e5);
                QKeyEvent  e6(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier,
                              QString(QString::fromStdString(spaceBegin) +
                              QString(4, QChar(' '))));
                QPlainTextEdit::keyPressEvent(&e6);
            } else if (currText.size() == currBlockIdx &&
                    currText[currBlockIdx - 1] == '{') {
                QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
                QPlainTextEdit::keyPressEvent(&e1);
                QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier,
                              QString(QString::fromStdString(spaceBegin) +
                              QString(4, QChar(' '))));
                QPlainTextEdit::keyPressEvent(&e2);
            } else if (it != currText.end() && currText.size() == currBlockIdx) {
                QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
                QPlainTextEdit::keyPressEvent(&e1);
                QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier,
                              QString::fromStdString(spaceBegin));
                QPlainTextEdit::keyPressEvent(&e2);
            } else if (currText == spaceBegin) {
                QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Home, Qt::NoModifier);
                QPlainTextEdit::keyPressEvent(&e1);
                QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
                QPlainTextEdit::keyPressEvent(&e2);
                QKeyEvent  e3(QEvent::KeyPress, Qt::Key_End, Qt::NoModifier);
                QPlainTextEdit::keyPressEvent(&e3);
            } else {
                QPlainTextEdit::keyPressEvent(event);
            }
            m_previousChar = 0;
        }
        break;
    case Qt::Key_Backspace :
        {
            QTextCursor  tc = textCursor();
            int  currBlockIdx = tc.positionInBlock();
            std::string  currText = tc.block().text().toStdString();

            if (currText.size() > 3 && currBlockIdx > 3 &&
                    currText.substr(currBlockIdx - 4, 4) == std::string(4, ' ')) {
                QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
                QPlainTextEdit::keyPressEvent(&e1);
                QPlainTextEdit::keyPressEvent(&e1);
                QPlainTextEdit::keyPressEvent(&e1);
                QPlainTextEdit::keyPressEvent(&e1);
            } else {
                QPlainTextEdit::keyPressEvent(event);
            }
            m_previousChar = 0;
        }
        break;
    case Qt::Key_BraceLeft :
        {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, QString("{}"));
            QPlainTextEdit::keyPressEvent(&e1);
            QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e2);
            m_previousChar = static_cast<int>(Qt::Key_BraceLeft);
        }
        break;
    case Qt::Key_BraceRight :
        if (m_previousChar == static_cast<int>(Qt::Key_BraceLeft)) {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e1);
        } else {
            QPlainTextEdit::keyPressEvent(event);
        }
        m_previousChar = 0;
        break;
    case Qt::Key_ParenLeft :
        {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, QString("()"));
            QPlainTextEdit::keyPressEvent(&e1);
            QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e2);
            m_previousChar = static_cast<int>(Qt::Key_ParenLeft);
        }
        break;
    case Qt::Key_ParenRight :
        if (m_previousChar == static_cast<int>(Qt::Key_ParenLeft)) {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e1);
        } else {
            QPlainTextEdit::keyPressEvent(event);
        }
        m_previousChar = 0;
        break;
    case Qt::Key_BracketLeft :
        {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, QString("[]"));
            QPlainTextEdit::keyPressEvent(&e1);
            QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e2);
            m_previousChar = static_cast<int>(Qt::Key_BracketLeft);
        }
        break;
    case Qt::Key_BracketRight :
        if (m_previousChar == static_cast<int>(Qt::Key_BracketLeft)) {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e1);
        } else {
            QPlainTextEdit::keyPressEvent(event);
        }
        m_previousChar = 0;
        break;
    case Qt::Key_QuoteDbl :
        if (m_previousChar == static_cast<int>(Qt::Key_QuoteDbl)) {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e1);
            m_previousChar = 0;
        } else {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, QString("\"\""));
            QPlainTextEdit::keyPressEvent(&e1);
            QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e2);
            m_previousChar = static_cast<int>(Qt::Key_QuoteDbl);
        }
        break;
    case Qt::Key_Apostrophe :
        if (m_previousChar == static_cast<int>(Qt::Key_Apostrophe)) {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e1);
            m_previousChar = 0;
        } else {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, QString("\'\'"));
            QPlainTextEdit::keyPressEvent(&e1);
            QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e2);
            m_previousChar = static_cast<int>(Qt::Key_Apostrophe);
        }
        break;
    case Qt::Key_Less :
        if (m_previousChar == static_cast<int>(Qt::Key_Less)) {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e1);
            QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, QString("<"));
            QPlainTextEdit::keyPressEvent(&e2);
            m_previousChar = 0;
        } else {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, QString("<>"));
            QPlainTextEdit::keyPressEvent(&e1);
            QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e2);
            m_previousChar = static_cast<int>(Qt::Key_Less);
        }
        break;
    case Qt::Key_Greater :
        if (m_previousChar == static_cast<int>(Qt::Key_Less)) {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e1);
        } else {
            QPlainTextEdit::keyPressEvent(event);
        }
        m_previousChar = 0;
        break;
    case Qt::Key_Space :
        if (m_previousChar == static_cast<int>(Qt::Key_Less)) {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e1);
            QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, QString(" "));
            QPlainTextEdit::keyPressEvent(&e2);
        } else {
            QPlainTextEdit::keyPressEvent(event);
        }
        m_previousChar = 0;
        break;
    case Qt::Key_Equal :
        if (m_previousChar == static_cast<int>(Qt::Key_Less)) {
            QKeyEvent  e1(QEvent::KeyPress, Qt::Key_Delete, Qt::NoModifier);
            QPlainTextEdit::keyPressEvent(&e1);
            QKeyEvent  e2(QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, QString("="));
            QPlainTextEdit::keyPressEvent(&e2);
        } else {
            QPlainTextEdit::keyPressEvent(event);
        }
        m_previousChar = 0;
        break;
    default:
        QPlainTextEdit::keyPressEvent(event);
        m_previousChar = 0;
        break;
    }
}

void
CodeEditor::updateLineNumberAreaWidth()
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void
CodeEditor::updateLineNumberArea(const QRect &  rect,
                                 int  dy)
{
    if (dy) {
        m_lineNumberArea->scroll(0, dy);
    } else {
        m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());
    }

    if (rect.contains(viewport()->rect())) {
        updateLineNumberAreaWidth();
    }
}

void
CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection>  extraSelections;
    QTextEdit::ExtraSelection         selection;
    QColor                            lineColor;
    StyleType  stype = xu::getGuiStyle();

    if (stype == StyleType::dark) {
        lineColor = QColor(Qt::darkCyan).lighter(50);
    } else {
        lineColor = QColor(Qt::yellow).lighter(160);
    }

    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);

    setExtraSelections(extraSelections);
}

void
CodeEditor::insertCompletion(const QString &  completion)
{
    if (m_completer->widget() != this) {
        return;
    }

    QTextCursor  tc = textCursor();
    int  extra = completion.length() - m_completer->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

QString
CodeEditor::textUnderCursor() const
{
    QTextCursor  tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

QCompleter *
CodeEditor::getCompleter() const
{
    return m_completer;
}

void
CodeEditor::setCompleter(QCompleter *  value)
{
    if (m_completer) {
        m_completer->disconnect(this);
    }

    m_completer = value;

    if (!m_completer) {
        return;
    }

    m_completer->setWidget(this);
    m_completer->setCompletionMode(QCompleter::PopupCompletion);
    m_completer->setCaseSensitivity(Qt::CaseInsensitive);
    connect(m_completer, QOverload<const QString &>::of(&QCompleter::activated),
            this, &CodeEditor::insertCompletion);
}

}
