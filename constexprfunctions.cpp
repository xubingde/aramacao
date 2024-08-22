#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "constexprfunctions.h"
#include "function.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

ConstexprFunctions::ConstexprFunctions(const ConstexprFunctions &  other):
        Functions(other)
{
}

ConstexprFunctions::ConstexprFunctions(ConstexprFunctions &&  other) noexcept:
        Functions(std::move(other))
{
}

ConstexprFunctions::ConstexprFunctions(MyClass *  parent /* = nullptr */):
        Functions(parent)
{
    setTreeLabel("G   Constexpr Functions");
    setBaseType(Etype::eConstexprFunctions);
}

ConstexprFunctions::~ConstexprFunctions() noexcept
{
}

ConstexprFunctions &
ConstexprFunctions::operator=(const ConstexprFunctions &  other)
{
    if (this == &other) return *this;

    this->Functions::operator=(other);

    return *this;
}

ConstexprFunctions &
ConstexprFunctions::operator=(ConstexprFunctions &&  other) noexcept
{
    if (this == &other) return *this;

    this->Functions::operator=(std::move(other));

    return *this;
}

void
ConstexprFunctions::procFunction(Function &  fn)
{
    Functions::procFunction(fn);
    fn.setConstexpr(true);
    fn.setInline(true);
    fn.setSourceinH(true);
}

bool
ConstexprFunctions::equal(const EObject &  value) const
{
    return this->Functions::equal(value);
}

bool
ConstexprFunctions::less(const EObject &  value) const
{
    return this->Functions::less(value);
}

std::string
ConstexprFunctions::serialize() const
{
    std::string  res;

    xu::append(res, this->Functions::serialize());

    return res;
}

bool
ConstexprFunctions::deserialize(const char *  data,
                                const size_t  size)
{
    ConstexprFunctions  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 0) {
        if (!me.Functions::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
ConstexprFunctions::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        ConstexprFunctions &  rhs = dynamic_cast<ConstexprFunctions &>(value);
        this->Functions::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
