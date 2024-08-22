#include <typeinfo>
#include "wtbase.h"

namespace xu {

WtBase::WtBase(QWidget *  parent /* = nullptr */):
        QAbstractScrollArea(parent)
{
}

WtBase::~WtBase() noexcept
{
}

}
