#include "itemstack.h"

namespace xu {

ItemStack::ItemStack():
        m_vecPtr(nullptr),
        m_selfItem(nullptr),
        m_parentItem(nullptr),
        m_selfIndex(),
        m_parentIndex(),
        m_selfRow(),
        m_parentRow()
{
}

ItemStack::ItemStack(const ItemStack &  other):
        m_vecPtr(other.m_vecPtr),
        m_selfItem(other.m_selfItem),
        m_parentItem(other.m_parentItem),
        m_selfIndex(other.m_selfIndex),
        m_parentIndex(other.m_parentIndex),
        m_selfRow(other.m_selfRow),
        m_parentRow(other.m_parentRow)
{
}

ItemStack::ItemStack(ItemStack &&  other) noexcept:
        m_vecPtr(std::move(other.m_vecPtr)),
        m_selfItem(std::move(other.m_selfItem)),
        m_parentItem(std::move(other.m_parentItem)),
        m_selfIndex(std::move(other.m_selfIndex)),
        m_parentIndex(std::move(other.m_parentIndex)),
        m_selfRow(std::move(other.m_selfRow)),
        m_parentRow(std::move(other.m_parentRow))
{
}

ItemStack::~ItemStack() noexcept
{
}

ItemStack &
ItemStack::operator=(const ItemStack &  other)
{
    if (this == &other) return *this;

    m_vecPtr = other.m_vecPtr;
    m_selfItem = other.m_selfItem;
    m_parentItem = other.m_parentItem;
    m_selfIndex = other.m_selfIndex;
    m_parentIndex = other.m_parentIndex;
    m_selfRow = other.m_selfRow;
    m_parentRow = other.m_parentRow;

    return *this;
}

ItemStack &
ItemStack::operator=(ItemStack &&  other) noexcept
{
    if (this == &other) return *this;

    m_vecPtr = std::move(other.m_vecPtr);
    m_selfItem = std::move(other.m_selfItem);
    m_parentItem = std::move(other.m_parentItem);
    m_selfIndex = std::move(other.m_selfIndex);
    m_parentIndex = std::move(other.m_parentIndex);
    m_selfRow = std::move(other.m_selfRow);
    m_parentRow = std::move(other.m_parentRow);

    return *this;
}

void *
ItemStack::getVecPtr() const
{
    return m_vecPtr;
}

void
ItemStack::setVecPtr(void *  value)
{
    m_vecPtr = value;
}

QStandardItem *
ItemStack::getSelfItem() const
{
    return m_selfItem;
}

void
ItemStack::setSelfItem(QStandardItem *  value)
{
    m_selfItem = value;
}

QStandardItem *
ItemStack::getParentItem() const
{
    return m_parentItem;
}

void
ItemStack::setParentItem(QStandardItem *  value)
{
    m_parentItem = value;
}

QModelIndex
ItemStack::getSelfIndex() const
{
    return m_selfIndex;
}

void
ItemStack::setSelfIndex(const QModelIndex &  value)
{
    m_selfIndex = value;
}

QModelIndex
ItemStack::getParentIndex() const
{
    return m_parentIndex;
}

void
ItemStack::setParentIndex(const QModelIndex &  value)
{
    m_parentIndex = value;
}

int
ItemStack::getSelfRow() const
{
    return m_selfRow;
}

void
ItemStack::setSelfRow(const int  value)
{
    m_selfRow = value;
}

int
ItemStack::getParentRow() const
{
    return m_parentRow;
}

void
ItemStack::setParentRow(const int  value)
{
    m_parentRow = value;
}

}
