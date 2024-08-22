#pragma once

#ifndef XU_ITEMSTACK_H_
#define XU_ITEMSTACK_H_

#include <QStandardItem>
#include <QModelIndex>
#include "eobject.h"

namespace xu {

class ItemStack;

class alignas(8) ItemStack final
{

public:

    ItemStack();
    ItemStack(const ItemStack &  other);
    ItemStack(ItemStack &&  other) noexcept;
    ~ItemStack() noexcept;

    ItemStack &  operator=(const ItemStack &  other);
    ItemStack &  operator=(ItemStack &&  other) noexcept;

    void *  getVecPtr() const;
    void  setVecPtr(void *  value);

    QStandardItem *  getSelfItem() const;
    void  setSelfItem(QStandardItem *  value);

    QStandardItem *  getParentItem() const;
    void  setParentItem(QStandardItem *  value);

    QModelIndex  getSelfIndex() const;
    void  setSelfIndex(const QModelIndex &  value);

    QModelIndex  getParentIndex() const;
    void  setParentIndex(const QModelIndex &  value);

    int  getSelfRow() const;
    void  setSelfRow(const int  value);

    int  getParentRow() const;
    void  setParentRow(const int  value);

private:

    void *          m_vecPtr;
    QStandardItem *     m_selfItem;
    QStandardItem *     m_parentItem;
    QModelIndex     m_selfIndex;
    QModelIndex     m_parentIndex;
    alignas(8) int      m_selfRow;
    int             m_parentRow;
};

}

#endif
