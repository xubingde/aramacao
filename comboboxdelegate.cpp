#include <cstring>
#include <typeinfo>
#include <QComboBox>
#include <QPainter>
#include "comboboxdelegate.h"

namespace xu {

ComboBoxDelegate::ComboBoxDelegate(QObject *  parent /* = nullptr */):
        QStyledItemDelegate(parent)
{
}

ComboBoxDelegate::~ComboBoxDelegate() noexcept
{
}

QWidget *
ComboBoxDelegate::createEditor(QWidget *  parent,
                               const QStyleOptionViewItem &,
                               const QModelIndex &) const
{
    QComboBox *  editor = new QComboBox(parent);
    editor->addItem(QString::fromLocal8Bit("public"));
    editor->addItem(QString::fromLocal8Bit("protected"));
    editor->addItem(QString::fromLocal8Bit("private"));
    editor->setCurrentIndex(0);

    connect(editor,  QOverload<int>::of(&QComboBox::activated),
            this, &ComboBoxDelegate::commitAndCloseEditor);

    return editor;
}

void
ComboBoxDelegate::setEditorData(QWidget *  editor,
                                const QModelIndex &  index) const
{
    QComboBox *  cb = qobject_cast<QComboBox *>(editor);

    const QString  currentText = index.data(Qt::EditRole).toString();
    const int  cbIndex = cb->findText(currentText);
    if (cbIndex >= 0) {
        cb->setCurrentIndex(cbIndex);
    }
}

void
ComboBoxDelegate::setModelData(QWidget *  editor,
                               QAbstractItemModel *  model,
                               const QModelIndex &  index) const
{
    QComboBox *  cb = qobject_cast<QComboBox *>(editor);
    model->setData(index, cb->currentText(), Qt::EditRole);
}

void
ComboBoxDelegate::commitAndCloseEditor()
{
    QComboBox *  editor = qobject_cast<QComboBox *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

}
