#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "staticfunctions.h"
#include "function.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

StaticFunctions::StaticFunctions(const StaticFunctions &  other):
        Functions(other)
{
}

StaticFunctions::StaticFunctions(StaticFunctions &&  other) noexcept:
        Functions(std::move(other))
{
}

StaticFunctions::StaticFunctions(MyClass *  parent /* = nullptr */):
        Functions(parent)
{
    setTreeLabel("G   Static Functions");
    setBaseType(Etype::eStaticFunctions);
}

StaticFunctions::~StaticFunctions() noexcept
{
}

StaticFunctions &
StaticFunctions::operator=(const StaticFunctions &  other)
{
    if (this == &other) return *this;

    this->Functions::operator=(other);

    return *this;
}

StaticFunctions &
StaticFunctions::operator=(StaticFunctions &&  other) noexcept
{
    if (this == &other) return *this;

    this->Functions::operator=(std::move(other));

    return *this;
}

void
StaticFunctions::procFunction(Function &  fn)
{
    Functions::procFunction(fn);
    fn.setStatic(true);
}

bool
StaticFunctions::equal(const EObject &  value) const
{
    return this->Functions::equal(value);
}

bool
StaticFunctions::less(const EObject &  value) const
{
    return this->Functions::less(value);
}

std::string
StaticFunctions::serialize() const
{
    std::string  res;

    xu::append(res, this->Functions::serialize());

    return res;
}

bool
StaticFunctions::deserialize(const char *  data,
                             const size_t  size)
{
    StaticFunctions  me;
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
StaticFunctions::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        StaticFunctions &  rhs = dynamic_cast<StaticFunctions &>(value);
        this->Functions::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
