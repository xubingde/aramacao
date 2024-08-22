#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "tplfunctions.h"
#include "function.h"
#include "eobject.h"
#include "myclass.h"

namespace xu {

TplFunctions::TplFunctions(const TplFunctions &  other):
        Functions(other)
{
}

TplFunctions::TplFunctions(TplFunctions &&  other) noexcept:
        Functions(std::move(other))
{
}

TplFunctions::TplFunctions(MyClass *  parent /* = nullptr */):
        Functions(parent)
{
    setTreeLabel("G   Template Functions");
    setBaseType(Etype::eTplFunctions);
}

TplFunctions::~TplFunctions() noexcept
{
}

TplFunctions &
TplFunctions::operator=(const TplFunctions &  other)
{
    if (this == &other) return *this;

    this->Functions::operator=(other);

    return *this;
}

TplFunctions &
TplFunctions::operator=(TplFunctions &&  other) noexcept
{
    if (this == &other) return *this;

    this->Functions::operator=(std::move(other));

    return *this;
}

void
TplFunctions::procFunction(Function &  fn)
{
    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        fn.setClassFunction(true);
        fn.setParentClassPtr(parentPtr);
    } else {
        fn.setClassFunction(false);
        fn.setParentClassPtr(nullptr);
    }

    fn.setConstructor(false);
    fn.setStrike({});
    fn.setNewCode({});
    fn.setStatic(false);
    fn.setConstexpr(false);
    fn.setTemplate(true);
    fn.setAutoSource(false);
    fn.setInhValueFirst("");
    fn.setInhValueBaseClass({});
    fn.setDefValueCtor({});
    fn.setInline(true);
    fn.setSourceinH(true);

    if (parentPtr && parentPtr->getClasstype() == ClassType::cppFinal) {
        fn.setVirtual(false);
        fn.setOverride(false);
        fn.setFinal(false);
        fn.setPureVirtual(false);
    } else {
        fn.setVirtual(false);
        fn.setOverride(false);
        fn.setFinal(false);
        fn.setConst(false);
        fn.setEqDefault(false);
        fn.setEqDelete(false);
        fn.setRef(false);
        fn.setRefRef(false);
        fn.setPureVirtual(false);
    }
}

bool
TplFunctions::equal(const EObject &  value) const
{
    return this->Functions::equal(value);
}

bool
TplFunctions::less(const EObject &  value) const
{
    return this->Functions::less(value);
}

std::string
TplFunctions::serialize() const
{
    std::string  res;

    xu::append(res, this->Functions::serialize());

    return res;
}

bool
TplFunctions::deserialize(const char *  data,
                          const size_t  size)
{
    TplFunctions  me;
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
TplFunctions::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        TplFunctions &  rhs = dynamic_cast<TplFunctions &>(value);
        this->Functions::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
