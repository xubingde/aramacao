#include <typeinfo>
#include <cstring>
#include "icode.h"
#include "fmt.h"
#include "eobject.h"
#include "myclass.h"
#include "publictype.h"
#include "field.h"
#include "copyconstructorfn.h"
#include "parameter.h"

namespace xu {

CopyConstructorFn::CopyConstructorFn():
        Function()
{
    init();
}

CopyConstructorFn::CopyConstructorFn(const CopyConstructorFn &  other):
        Function(other)
{
}

CopyConstructorFn::CopyConstructorFn(CopyConstructorFn &&  other) noexcept:
        Function(std::move(other))
{
}

CopyConstructorFn::CopyConstructorFn(MyClass *  parent):
        Function(parent)
{
    init();
}

CopyConstructorFn::~CopyConstructorFn() noexcept
{
}

CopyConstructorFn &
CopyConstructorFn::operator=(const CopyConstructorFn &  other)
{
    if (this == &other) return *this;

    this->Function::operator=(other);

    return *this;
}

CopyConstructorFn &
CopyConstructorFn::operator=(CopyConstructorFn &&  other) noexcept
{
    if (this == &other) return *this;

    this->Function::operator=(std::move(other));

    return *this;
}

std::string
CopyConstructorFn::autoCode() const
{
    std::string  autoCode;
    const std::string  tab1(getDefTab());
    const std::string  tab2(getDefTab() + getDefTab());

    MyClass const *  parentPtr = getParentClassPtr();
    if (parentPtr == nullptr)  return autoCode;
    std::vector<Field> const  vecField = parentPtr->getField();

    for (const auto &  fd: vecField) {
        if (fd.isPointer()) {
            autoCode += tab1 + "if (other." + fd.getPrivateName() + " != nullptr) {\n";
            autoCode += tab2 + fd.getPrivateName() + " = new " +
                    fd.getTypeName() + " { *other." + fd.getPrivateName() + " };\n";
            autoCode += tab1 + "}\n";
        }
    }

    return autoCode;
}

void
CopyConstructorFn::setFunctionName(std::string const &  value)
{
    Function::setFunctionName(value);
    setTreeLabel("A   Copy Constructor");
}

void
CopyConstructorFn::setParam(std::vector<Parameter> const &)
{
    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        std::string const  className = parentPtr->getClassName();
        std::vector<Parameter>  params;
        Parameter  par1;
        par1.setParameterName("other");
        par1.setType(className + "const &");
        params.push_back(std::move(par1));
        Function::setParam(std::move(params));
    }
}

void
CopyConstructorFn::setParam(std::vector<Parameter> &&  value)
{
    CopyConstructorFn::setParam(value);
}

void
CopyConstructorFn::setParentClassPtr(MyClass *  value)
{
    Function::setParentClassPtr(value);
    setTreeLabel("A   Copy Constructor");
    updateDefualtValue();
}

void
CopyConstructorFn::updateDefualtValue()
{
    std::vector<Field>  vecField;
    MyClass *  parentPtr = getParentClassPtr();
    if (parentPtr) {
        vecField = parentPtr->getField();
    }
    std::vector<std::string>  defVal;
    for (const auto &  fd: vecField) {
        defVal.push_back("other." + fd.getPrivateName());
    }
    setDefValueCtor(defVal);

    if (parentPtr && parentPtr->getClasstype() == ClassType::cppInherit) {
        size_t const  size = parentPtr->getMulInhClass().size();
        std::vector<std::string>  valueBaseClass(size, "other");
        setInhValueBaseClass(valueBaseClass);
    }
}

void
CopyConstructorFn::init()
{
    setTreeLabel("A   Copy Constructor");
    setBaseType(Etype::eCopyConstructorFn);

    setClassFunction(true);
    setConstructor(true);
    setAutoSource(true);
    CopyConstructorFn::setFunctionName("");
    CopyConstructorFn::setParam({});
    updateDefualtValue();
}

bool
CopyConstructorFn::equal(const EObject &  value) const
{
    return this->Function::equal(value);
}

bool
CopyConstructorFn::less(const EObject &  value) const
{
    return this->Function::less(value);
}

std::string
CopyConstructorFn::serialize() const
{
    std::string  res;

    xu::append(res, this->Function::serialize());

    return res;
}

bool
CopyConstructorFn::deserialize(const char *  data,
                               const size_t  size)
{
    CopyConstructorFn  me;
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
CopyConstructorFn::exchange(EObject &  value) noexcept
{
    bool  result = false;
    if (typeid(*this) == typeid(value)) {
        CopyConstructorFn &  rhs = dynamic_cast<CopyConstructorFn &>(value);
        this->Function::exchange(rhs);

        using std::swap;

        result = true;
    }
    return result;
}

}
