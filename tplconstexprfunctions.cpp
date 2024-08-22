#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "tplconstexprfunctions.h"
#include "function.h"
#include "eobject.h"
#include "myclass.h"
#include "functions.h"

namespace xu {

TplConstexprFunctions::TplConstexprFunctions(const TplConstexprFunctions &  other):
        TplFunctions(other)
{
}

TplConstexprFunctions::TplConstexprFunctions(TplConstexprFunctions &&  other) noexcept:
        TplFunctions(std::move(other))
{
}

TplConstexprFunctions::TplConstexprFunctions(MyClass *  parent /* = nullptr */):
        TplFunctions(parent)
{
    setTreeLabel("G   Template Constexpr Functions");
    setBaseType(Etype::eTplConstexprFunctions);
}

TplConstexprFunctions::~TplConstexprFunctions() noexcept
{
}

TplConstexprFunctions &
TplConstexprFunctions::operator=(const TplConstexprFunctions &  other)
{
    if (this == &other) return *this;

    this->TplFunctions::operator=(other);

    return *this;
}

TplConstexprFunctions &
TplConstexprFunctions::operator=(TplConstexprFunctions &&  other) noexcept
{
    if (this == &other) return *this;

    this->TplFunctions::operator=(std::move(other));

    return *this;
}

void
TplConstexprFunctions::procFunction(Function &  fn)
{
    TplFunctions::procFunction(fn);
    fn.setConstexpr(true);
}

bool
TplConstexprFunctions::equal(const EObject &  value) const
{
    return this->TplFunctions::equal(value);
}

bool
TplConstexprFunctions::less(const EObject &  value) const
{
    return this->TplFunctions::less(value);
}

std::string
TplConstexprFunctions::serialize() const
{
    std::string  res;

    xu::append(res, this->TplFunctions::serialize());

    return res;
}

bool
TplConstexprFunctions::deserialize(const char *  data,
                                   const size_t  size)
{
    TplConstexprFunctions  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 0) {
        if (!me.TplFunctions::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
TplConstexprFunctions::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        TplConstexprFunctions &  rhs = dynamic_cast<TplConstexprFunctions &>(value);
        this->TplFunctions::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
