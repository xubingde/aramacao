#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "constructors.h"
#include "function.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

Constructors::Constructors(const Constructors &  other):
        Functions(other)
{
}

Constructors::Constructors(Constructors &&  other) noexcept:
        Functions(std::move(other))
{
}

Constructors::Constructors(MyClass *  parent /* = nullptr */):
        Functions(parent)
{
    setTreeLabel("G   Constructors");
    setBaseType(Etype::eConstructors);
}

Constructors::~Constructors() noexcept
{
}

Constructors &
Constructors::operator=(const Constructors &  other)
{
    if (this == &other) return *this;

    this->Functions::operator=(other);

    return *this;
}

Constructors &
Constructors::operator=(Constructors &&  other) noexcept
{
    if (this == &other) return *this;

    this->Functions::operator=(std::move(other));

    return *this;
}

void
Constructors::procFunction(Function &  fn)
{
    fn.setClassFunction(true);
    fn.setParentClassPtr(getParentClassPtr());

    fn.setConstructor(true);
    fn.setStrike({});
    fn.setNewCode({});
    fn.setStatic(false);
    fn.setConstexpr(false);
    fn.setTemplate(false);
    fn.setAutoSource(false);
    fn.setTparam({});
    fn.setVirtual(false);
    fn.setOverride(false);
    fn.setFinal(false);
    fn.setConst(false);
    fn.setPureVirtual(false);
    fn.setRef(false);
    fn.setRefRef(false);
    fn.setReturnType("");
    fn.setFunctionName("");
}

bool
Constructors::equal(const EObject &  value) const
{
    return this->Functions::equal(value);
}

bool
Constructors::less(const EObject &  value) const
{
    return this->Functions::less(value);
}

std::string
Constructors::serialize() const
{
    std::string  res;

    xu::append(res, this->Functions::serialize());

    return res;
}

bool
Constructors::deserialize(const char *  data,
                          const size_t  size)
{
    Constructors  me;
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
Constructors::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        Constructors &  rhs = dynamic_cast<Constructors &>(value);
        this->Functions::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
