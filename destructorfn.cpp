#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "publictype.h"
#include "field.h"
#include "destructorfn.h"
#include "myclass.h"
#include "eobject.h"

namespace xu {

DestructorFn::DestructorFn():
        Function()
{
    init();
}

DestructorFn::DestructorFn(const DestructorFn &  other):
        Function(other)
{
}

DestructorFn::DestructorFn(DestructorFn &&  other) noexcept:
        Function(std::move(other))
{
}

DestructorFn::DestructorFn(MyClass *  parent):
        Function(parent)
{
    init();
}

DestructorFn::~DestructorFn() noexcept
{
}

DestructorFn &
DestructorFn::operator=(const DestructorFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

DestructorFn &
DestructorFn::operator=(DestructorFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

std::string
DestructorFn::autoCode() const
{
    std::string  autoCode;
    const std::string  tab1(getDefTab());

    MyClass const *  parentPtr = getParentClassPtr();
    if (parentPtr == nullptr)  return autoCode;
    std::vector<Field> const  vecField = parentPtr->getField();

    for (auto  it = vecField.rbegin(); it != vecField.rend(); ++it) {
        if (it->isPointer()) {
            autoCode += tab1 + "delete " + it->getPrivateName() + ";\n";
        }
    }

    return autoCode;
}

void
DestructorFn::setFunctionName(std::string const &)
{
    std::string  fnName = "~";
    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        fnName = "~" + parentPtr->getClassName();
    }

    Function::setFunctionName(fnName);
    setTreeLabel("A   ~Destructor");
}

void
DestructorFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    setTreeLabel("A   ~Destructor");
    updateDefualtValue();

}

void
DestructorFn::updateDefualtValue()
{
    ClassType  ct = ClassType::cppFinal;
    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        ct = parentPtr->getClasstype();
    }

    if (ct == ClassType::cppFinal) {
        Function::setVirtual(false);
    } else {
        Function::setVirtual(true);
    }
}

void
DestructorFn::init()
{
    setTreeLabel("A   ~Destructor");
    setBaseType(Etype::eDestructorFn);

    setClassFunction(true);
    setAutoSource(true);
    setNoexcept(true);
    DestructorFn::setFunctionName("");
    updateDefualtValue();
}

bool
DestructorFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
DestructorFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
DestructorFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
DestructorFn::deserialize(const char *  data,
                          const size_t  size)
{
    DestructorFn  me;
    std::vector<size_t>  err;
    const auto  vi { xu::viewIcode(data, size) };

    if (vi.size() > 0) {
        if (!me.Function::deserialize(vi[0].data(), vi[0].size()))  err.push_back({0});

    }
    bool  result = false;

    if (err.size() == 0) {
        *this = std::move(me);
        result = true;
    }

    return result;
}

bool
DestructorFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        DestructorFn &  rhs = dynamic_cast<DestructorFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
