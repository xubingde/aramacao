#include <typeinfo>
#include "wtbase.h"

namespace xu {

WtBase::WtBase(QWidget *  parent /* = nullptr */):
        QAbstractScrollArea(parent),
        m_itemPtr()
{
}

WtBase::~WtBase() noexcept
{
}

QStandardItem *
WtBase::getItemPtr() const
{
    return m_itemPtr;
}

void
WtBase::setItemPtr(QStandardItem *  value)
{
    m_itemPtr = value;
}

}
