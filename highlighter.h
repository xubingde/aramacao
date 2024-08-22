#pragma once

#ifndef XU_HIGHLIGHTER_H_
#define XU_HIGHLIGHTER_H_

#include <QTextDocument>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QVector>

namespace xu {

class Highlighter;

class Highlighter : public QSyntaxHighlighter
{

    Q_OBJECT

public:

    struct HighLightingRule;

    struct HighLightingRule {
        QRegularExpression      pattern;
        QTextCharFormat     format;
    };

    Highlighter(QTextDocument *  parent = nullptr);
    virtual ~Highlighter() noexcept;

protected:

    void  highlightBlock(const QString &  text) override;

private:

    QVector<HighLightingRule>   m_highLightingRules;
    QRegularExpression      m_commentStartExpression;
    QRegularExpression      m_commentEndExpression;
    QTextCharFormat     m_keywordFormat;
    QTextCharFormat     m_cppTypeFormat;
    QTextCharFormat     m_classFormatQt;
    QTextCharFormat     m_singleLineCommentFormat;
    QTextCharFormat     m_multiLineCommentFormat;
    QTextCharFormat     m_quotationFormat;
    QTextCharFormat     m_apostropheFormat;
    QTextCharFormat     m_functionFormat;
    QTextCharFormat     m_stdFormat;
    QTextCharFormat     m_mLineFormat;
    QTextCharFormat     m_digitFormat;
};

}

#endif
