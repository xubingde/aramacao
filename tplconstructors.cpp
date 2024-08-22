#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "tplconstructors.h"
#include "function.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

TplConstructors::TplConstructors(const TplConstructors &  other):
        Functions(other)
{
}

TplConstructors::TplConstructors(TplConstructors &&  other) noexcept:
        Functions(std::move(other))
{
}

TplConstructors::TplConstructors(MyClass *  parent /* = nullptr */):
        Functions(parent)
{
    setTreeLabel("G   Template Constructors");
    setBaseType(Etype::eTplConstructors);
}

TplConstructors::~TplConstructors() noexcept
{
}

TplConstructors &
TplConstructors::operator=(const TplConstructors &  other)
{
    if (this == &other) return *this;

    this->Functions::operator=(other);

    return *this;
}

TplConstructors &
TplConstructors::operator=(TplConstructors &&  other) noexcept
{
    if (this == &other) return *this;

    this->Functions::operator=(std::move(other));

    return *this;
}

void
TplConstructors::procFunction(Function &  fn)
{
    fn.setClassFunction(true);
    fn.setParentClassPtr(getParentClassPtr());

    fn.setConstructor(true);
    fn.setStrike({});
    fn.setNewCode({});
    fn.setStatic(false);
    fn.setConstexpr(false);
    fn.setTemplate(true);
    fn.setAutoSource(false);
    fn.setVirtual(false);
    fn.setOverride(false);
    fn.setFinal(false);
    fn.setConst(false);
    fn.setPureVirtual(false);
    fn.setRef(false);
    fn.setRefRef(false);
    fn.setInline(true);
    fn.setSourceinH(true);
    fn.setReturnType("");
    fn.setFunctionName("");
}

bool
TplConstructors::equal(const EObject &  value) const
{
    return this->Functions::equal(value);
}

bool
TplConstructors::less(const EObject &  value) const
{
    return this->Functions::less(value);
}

std::string
TplConstructors::serialize() const
{
    std::string  res;

    xu::append(res, this->Functions::serialize());

    return res;
}

bool
TplConstructors::deserialize(const char *  data,
                             const size_t  size)
{
    TplConstructors  me;
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
TplConstructors::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        TplConstructors &  rhs = dynamic_cast<TplConstructors &>(value);
        this->Functions::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
