#pragma once

#ifndef XU_COMBOBOXDELEGATE_H_
#define XU_COMBOBOXDELEGATE_H_

#include <QStyledItemDelegate>
#include <QObject>
#include <QComboBox>
#include <QItemDelegate>
#include <QStyleOption>
#include <QMouseEvent>
#include <QPainter>

namespace xu {

class ComboBoxDelegate;

class ComboBoxDelegate : public QStyledItemDelegate
{

    Q_OBJECT

public:

    ComboBoxDelegate(const ComboBoxDelegate &  other) = default;
    ComboBoxDelegate(QObject *  parent = nullptr);
    virtual ~ComboBoxDelegate() noexcept;

    ComboBoxDelegate &  operator=(const ComboBoxDelegate &  other) = default;

    QWidget *  createEditor(QWidget *  parent, const QStyleOptionViewItem &, const QModelIndex &) const override;
    void  setEditorData(QWidget *  editor, const QModelIndex &  index) const override;
    void  setModelData(QWidget *  editor, QAbstractItemModel *  model, const QModelIndex &  index) const override;

protected:

private:

    void  commitAndCloseEditor();
};

}

#endif
