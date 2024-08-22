#include <typeinfo>
#include <cstring>
#include "highlighter.h"
#include "publictype.h"

namespace xu {

Highlighter::Highlighter(QTextDocument *  parent /* = nullptr */):
        QSyntaxHighlighter(parent),
        m_highLightingRules(),
        m_commentStartExpression(),
        m_commentEndExpression(),
        m_keywordFormat(),
        m_cppTypeFormat(),
        m_classFormatQt(),
        m_singleLineCommentFormat(),
        m_multiLineCommentFormat(),
        m_quotationFormat(),
        m_apostropheFormat(),
        m_functionFormat(),
        m_stdFormat(),
        m_mLineFormat(),
        m_digitFormat()
{
    StyleType  guiStyle = xu::getGuiStyle();
    if (guiStyle == StyleType::dark) {
        m_classFormatQt.setForeground(QColor(0xff, 0x6b, 0xf8));
        m_quotationFormat.setForeground(QColor(0xd6, 0x95, 0x45));
        m_apostropheFormat.setForeground(QColor(0xd6, 0x95, 0x45));
        m_functionFormat.setForeground(QColor(0xff, 0xb1, 0x52));
        m_keywordFormat.setForeground(QColor(0x45, 0xc6, 0xd6));
        m_cppTypeFormat.setForeground(QColor(0x9b, 0xa5, 0xff));
        m_stdFormat.setForeground(QColor(0x61, 0xc4, 0xf9));
        m_mLineFormat.setForeground(QColor(0xff, 0x80, 0x80));
        m_singleLineCommentFormat.setForeground(QColor(0x69, 0xc5, 0x00));
        m_multiLineCommentFormat.setForeground(QColor(0x69, 0xc5, 0x00));
        m_digitFormat.setForeground(QColor(0xff, 0x4d, 0x00));
    } else {
        m_classFormatQt.setForeground(QColor(0xa6, 0x46, 0xa3));
        m_quotationFormat.setForeground(Qt::red);
        m_apostropheFormat.setForeground(Qt::red);
        m_functionFormat.setForeground(QColor(0x95, 0x64, 0x30));
        m_keywordFormat.setForeground(QColor(0x00, 0x00, 0x9c));
        m_cppTypeFormat.setForeground(Qt::blue);
        m_stdFormat.setForeground(QColor(0x00, 0x00, 0x7f));
        m_mLineFormat.setForeground(QColor(0x9e, 0x00, 0x00));
        m_singleLineCommentFormat.setForeground(Qt::darkGreen);
        m_multiLineCommentFormat.setForeground(Qt::darkGreen);
        m_digitFormat.setForeground(QColor(0x98, 0x30, 0x00));
    }

    HighLightingRule  rule;

    rule.pattern = QRegularExpression("\\b[0-9]+\\b");
    rule.format = m_digitFormat;
    m_highLightingRules.append(rule);

    QStringList  digitPatterns;
    digitPatterns   << "\\bINT8_MIN\\b" << "\\bINT16_MIN\\b"
                    << "\\bINT32_MIN\\b" << "\\bINT64_MIN\\b"
                    << "\\bINT8_MAX\\b" << "\\bINT16_MAX\\b"
                    << "\\bINT32_MAX\\b" << "\\bINT64_MAX\\b"
                    << "\\bUINT8_MIN\\b" << "\\bUINT16_MIN\\b"
                    << "\\bUINT32_MIN\\b" << "\\bUINT64_MIN\\b"
                    << "\\bUINT8_MAX\\b" << "\\bUINT16_MAX\\b"
                    << "\\bUINT32_MAX\\b" << "\\bUINT64_MAX\\b"
                    << "\\bINT_FAST8_MIN\\b" << "\\bINT_FAST16_MIN\\b"
                    << "\\bINT_FAST32_MIN\\b" << "\\bINT_FAST64_MIN\\b"
                    << "\\bINT_FAST8_MAX\\b" << "\\bINT_FAST16_MAX\\b"
                    << "\\bINT_FAST32_MAX\\b" << "\\bINT_FAST64_MAX\\b"
                    << "\\bUINT_FAST8_MIN\\b" << "\\bUINT_FAST16_MIN\\b"
                    << "\\bUINT_FAST32_MIN\\b" << "\\bUINT_FAST64_MIN\\b"
                    << "\\bUINT_FAST8_MAX\\b" << "\\bUINT_FAST16_MAX\\b"
                    << "\\bUINT_FAST32_MAX\\b" << "\\bUINT_FAST64_MAX\\b"
                    << "\\bINT_LEAST8_MIN\\b" << "\\bINT_LEAST16_MIN\\b"
                    << "\\bINT_LEAST32_MIN\\b" << "\\bINT_LEAST64_MIN\\b"
                    << "\\bINT_LEAST8_MAX\\b" << "\\bINT_LEAST16_MAX\\b"
                    << "\\bINT_LEAST32_MAX\\b" << "\\bINT_LEAST64_MAX\\b"
                    << "\\bUINT_LEAST8_MIN\\b" << "\\bUINT_LEAST16_MIN\\b"
                    << "\\bUINT_LEAST32_MIN\\b" << "\\bUINT_LEAST64_MIN\\b"
                    << "\\bUINT_LEAST8_MAX\\b" << "\\bUINT_LEAST16_MAX\\b"
                    << "\\bUINT_LEAST32_MAX\\b" << "\\bUINT_LEAST64_MAX\\b"
                    << "\\bSIZE_MAX\\b" << "\\bWCHAR_MAX\\b" << "\\bWCHAR_MIN\\b"
                    << "\\bINT_MAX\\b" << "\\bINT_MIN\\b"
                    << "\\btrue\\b" << "\\bfalse\\b" << "\\bnullptr\\b"
                    << "\\bthis\\b";
    foreach (const QString &  pattern, digitPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = m_digitFormat;
        m_highLightingRules.append(rule);
    }

    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = m_functionFormat;
    m_highLightingRules.append(rule);

    rule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
    rule.format = m_classFormatQt;
    m_highLightingRules.append(rule);

    rule.pattern = QRegularExpression("\\bm_[A-Za-z0-9_]+\\b");
    rule.format = m_mLineFormat;
    m_highLightingRules.append(rule);

    QStringList  cppTypePatterns;
    cppTypePatterns << "\\bchar\\b" << "\\bdouble\\b" << "\\bfloat\\b"
                    << "\\bint\\b" << "\\blong\\b" << "\\bmax_align_t\\b"
                    << "\\bshort\\b" << "\\bsigned\\b"
                    << "\\bunsigned\\b" << "\\bvoid\\b" << "\\bbool\\b"
                    << "\\bsize_t\\b" << "\\bwchar_t\\b"
                    << "\\bchar8_t\\b" << "\\bchar16_t\\b" << "\\bchar32_t\\b"
                    << "\\bnullptr_t\\b" << "\\bptrdiff_t\\b"
                    << "\\bint8_t\\b" << "\\bint16_t\\b" << "\\bint32_t\\b"
                    << "\\bint64_t\\b" << "\\bint_fast8_t\\b" << "\\bint_fast16_t\\b"
                    << "\\bint_fast32_t\\b" << "\\bint_fast64_t\\b"
                    << "\\bint_least8_t\\b" << "\\bint_least16_t\\b"
                    << "\\bint_least32_t\\b" << "\\bint_least64_t\\b"
                    << "\\buint8_t\\b" << "\\buint16_t\\b" << "\\buint32_t\\b"
                    << "\\buint64_t\\b" << "\\buint_fast8_t\\b" << "\\buint_fast16_t\\b"
                    << "\\buint_fast32_t\\b" << "\\buint_fast64_t\\b"
                    << "\\buint_least8_t\\b" << "\\buint_least16_t\\b"
                    << "\\buint_least32_t\\b" << "\\buint_least64_t\\b"
                    << "\\bauto\\b" << "\\bdecltype\\b";
    foreach (const QString &  pattern, cppTypePatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = m_cppTypeFormat;
        m_highLightingRules.append(rule);
    }

    QStringList  keywordPatterns;
    keywordPatterns << "\\bclass\\b" << "\\bconst\\b"
                    << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b"
                    << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bsignals\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bvirtual\\b"
                    << "\\bvolatile\\b"
                    << "\\breturn\\b" << "\\busing\\b"
                    << "\\bsizeof\\b"
                    << "\\bextern\\b" << "\\bfinal\\b" << "\\boverride\\b"
                    << "\\bregister\\b" << "\\bthread_local\\b" << "\\bvolatile\\b"
                    << "\\bconstexpr\\b" << "\\bif\\b"
                    << "\\bwhile\\b" << "\\bfor\\b" << "\\bcase\\b" << "\\bswitch\\b"
                    << "\\bstatic_cast\\b" << "\\bconst_cast\\b" << "\\bthrow\\b"
                    << "\\breinterpret_cast\\b" << "\\bdynamic_cast\\b"
                    << "\\bcatch\\b" << "\\belse\\b" << "\\bbreak\\b" << "\\bnew\\b"
                    << "\\bdefault\\b" << "\\bdelete\\b" << "\\continueb\\b"
                    << "\\bgoto\\b" << "\\btry\\b"
                    << "\\bnoexcept\\b" << "\\bsizeof\\b" << "\\bcontinue\\b"
                    << "\\bstd::move\\b" << "\\basm\\b" << "\\bdo\\b"
                    << "\\bexport\\b" << "\\bmutable\\b" << "\\bstd::forward\\b"
                    << "\\balignas\\b" << "\\balignof\\b" << "\\band\\b"
                    << "\\band_eq\\b" << "\\bbitand\\b" << "\\bbitor\\b"
                    << "\\bcompl\\b" << "\\bconcept\\b" << "\\bconsteval\\b"
                    << "\\bconstinit\\b" << "\\bco_await\\b" << "\\bco_return\\b"
                    << "\\bco_yield\\b" << "\\bnot\\b" << "\\bnot_eq\\b" << "\\bor\\b"
                    << "\\bor_eq\\b" << "\\brequires\\b" << "\\bstatic_assert\\b"
                    << "\\btypeid\\b" << "\\bxor\\b" << "\\bxor_eq\\b";
    foreach (const QString &  pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = m_keywordFormat;
        m_highLightingRules.append(rule);
    }

    QStringList  stdPatterns;
    stdPatterns << "\\bstd::\\b";
    foreach (const QString &  pattern, stdPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = m_stdFormat;
        m_highLightingRules.append(rule);
    }


    m_commentStartExpression = QRegularExpression("/\\*");
    m_commentEndExpression = QRegularExpression("\\*/");
}

Highlighter::~Highlighter() noexcept
{
}

void
Highlighter::highlightBlock(const QString &  text)
{
    {
        const size_t  size = text.size();
        for (int  i = 0; i < size; ++i) {
            if (text[i] == '&' && (i + 1) < size && text[i + 1] == '&') {
                setFormat(i, 2, m_keywordFormat);
            } else if (text[i] == '|' && (i + 1) < size && text[i + 1] == '|') {
                setFormat(i, 2, m_keywordFormat);
            } else if (text[i] == ':') {
                if (!((i + 1 < size && text[i + 1] == ':') ||
                        (i != 0 && text[i - 1] == ':'))) {
                    setFormat(i, 1, m_keywordFormat);
                }
            } else if (text[i] == '\?') {
                if (!((i + 1 < size && text[i + 1] == '\?') ||
                        (i != 0 && text[i - 1] == '\?'))) {
                    setFormat(i, 1, m_keywordFormat);
                }
            }
        }
    }
    foreach (const HighLightingRule &  rule, m_highLightingRules) {
        QRegularExpressionMatchIterator  matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch  match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    bool  isInQuotation = false;
    bool  isInApostrophe = false;
    bool  isInMulComment = false;
    if (previousBlockState() == 1)  isInMulComment = true;
    {
        int  quotationStart = 0;
        int  apostropheStart = 0;
        int  inMuiStart = 0;

        int  countQut = 0;
        int  countApo = 0;
        int  countMui = 0;
        const size_t  size = text.size();

        for (int  i = 0; i < size; ++i) {
            if (text[i] == '/') {
                if (isInMulComment && (i != 0) && (text[i - 1] == '*')) {
                    countMui++;
                    setFormat(inMuiStart, countMui, m_multiLineCommentFormat);
                    inMuiStart = 0;
                    countMui = 0;
                    isInMulComment = false;
                } else if (isInMulComment && size == 1) {
                    setFormat(0, 1, m_multiLineCommentFormat);
                } else if (isInMulComment && i == (size - 1)) {
                    countMui++;
                    setFormat(inMuiStart, countMui, m_multiLineCommentFormat);
                } else if (isInMulComment) {
                    countMui++;
                } else if (isInQuotation || isInApostrophe) {
                    if (isInQuotation)  countQut++;
                    if (isInApostrophe)  countApo++;
                } else if ((i + 1) < size && text[i + 1] == '/') {
                    setFormat(i, static_cast<int>(size - i), m_singleLineCommentFormat);
                    break;
                } else if ((i + 1) < size && text[i + 1] == '*') {
                    isInMulComment = true;
                    inMuiStart = i;
                    countMui = 2;
                    i++;
                    if (size == i + 1) {
                        setFormat(inMuiStart, countMui, m_multiLineCommentFormat);
                    }
                }
            } else if (text[i] == '\"') {
                if (isInMulComment) {
                    countMui++;
                    if (i == (size - 1)) {
                        setFormat(inMuiStart, countMui, m_multiLineCommentFormat);
                    }
                    continue;
                }
                if (isInApostrophe) {
                    countApo++;
                    continue;
                }
                if (i != 0) {
                    size_t  vIdx = 0;
                    for (int  k = i - 1; k != 0; --k) {
                        if (text[k] == '\\') {
                            vIdx++;
                        } else {
                            break;
                        }
                    }
                    if (vIdx % 2 == 0) {
                        isInQuotation = !isInQuotation;
                        if (!isInQuotation) {
                            countQut++;
                            setFormat(quotationStart, countQut, m_quotationFormat);
                            countQut = 0;
                        } else {
                            quotationStart = i;
                            countQut = 1;
                        }
                    } else {
                        if (isInQuotation)  countQut++;
                    }
                } else {
                    quotationStart = 0;
                    countQut = 1;
                    isInQuotation = !isInQuotation;
                }

            } else if (text[i] == '\'') {
                if (isInMulComment) {
                    countMui++;
                    if (i == (size - 1)) {
                        setFormat(inMuiStart, countMui, m_multiLineCommentFormat);
                    }
                    continue;
                }
                if (isInQuotation) {
                    countQut++;
                    continue;
                }
                if (i == 0) {
                    apostropheStart = i;
                    countApo++;
                    isInApostrophe = !isInApostrophe;
                } else {
                    size_t  vIdx = 0;
                    for (int  k = i - 1; k != 0; --k) {
                        if (text[k] == '\\') {
                            vIdx++;
                        } else {
                            break;
                        }
                    }
                    if (vIdx % 2 == 0) {
                        isInApostrophe = !isInApostrophe;
                        if (!isInApostrophe) {
                            countApo++;
                            setFormat(apostropheStart, countApo, m_quotationFormat);
                            countApo = 0;
                        } else {
                            apostropheStart = i;
                            countApo = 1;
                        }
                    } else {
                        if (isInApostrophe)  countApo++;
                    }
                }
            } else {
                if (isInMulComment && i == (size - 1)) {
                    countMui++;
                    setFormat(inMuiStart, countMui, m_multiLineCommentFormat);
                    continue;
                }
                if (isInMulComment) {
                    countMui++;
                    continue;
                }
                if (isInQuotation)  countQut++;
                if (isInApostrophe)  countApo++;
            }
        }
    }
    if (isInMulComment) {
        setCurrentBlockState(1);
    } else {
        setCurrentBlockState(-1);
    }
}

}
