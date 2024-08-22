#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "tplstaticfunctions.h"
#include "function.h"
#include "eobject.h"
#include "myclass.h"
#include "functions.h"

namespace xu {

TplStaticFunctions::TplStaticFunctions(const TplStaticFunctions &  other):
        TplFunctions(other)
{
}

TplStaticFunctions::TplStaticFunctions(TplStaticFunctions &&  other) noexcept:
        TplFunctions(std::move(other))
{
}

TplStaticFunctions::TplStaticFunctions(MyClass *  parent /* = nullptr */):
        TplFunctions(parent)
{
    setTreeLabel("G   Template Static Functions");
    setBaseType(Etype::eTplStaticFunctions);
}

TplStaticFunctions::~TplStaticFunctions() noexcept
{
}

TplStaticFunctions &
TplStaticFunctions::operator=(const TplStaticFunctions &  other)
{
    if (this == &other) return *this;

    this->TplFunctions::operator=(other);

    return *this;
}

TplStaticFunctions &
TplStaticFunctions::operator=(TplStaticFunctions &&  other) noexcept
{
    if (this == &other) return *this;

    this->TplFunctions::operator=(std::move(other));

    return *this;
}

void
TplStaticFunctions::procFunction(Function &  fn)
{
    TplFunctions::procFunction(fn);
    fn.setStatic(true);
}

bool
TplStaticFunctions::equal(const EObject &  value) const
{
    return this->TplFunctions::equal(value);
}

bool
TplStaticFunctions::less(const EObject &  value) const
{
    return this->TplFunctions::less(value);
}

std::string
TplStaticFunctions::serialize() const
{
    std::string  res;

    xu::append(res, this->TplFunctions::serialize());

    return res;
}

bool
TplStaticFunctions::deserialize(const char *  data,
                                const size_t  size)
{
    TplStaticFunctions  me;
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
TplStaticFunctions::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        TplStaticFunctions &  rhs = dynamic_cast<TplStaticFunctions &>(value);
        this->TplFunctions::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
