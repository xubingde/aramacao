#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cctype>
#include <memory>
#include "fmt.h"

namespace xu {

std::string
trim(const std::string &  value,
     const std::string &  ch /* = std::string(" ") */)
{
    return trim(value.data(), value.size(), ch);
}

std::string
trim(const char *  data,
     const size_t  size,
     const std::string &  ch /* = std::string(" ") */)
{
    std::string  res;
    if (data == nullptr || size == 0) {
        return res;
    }
    if (ch.empty()) {
        res.append(data, size);
        return res;
    }

    const char *  end = data + size;
    bool  eq = false;
    for (; data < end; ++data) {
        for (const char &  val: ch) {
            if (*data == val) {
                eq = true;
                break;
            }
        }
        if (eq) {
            eq = false;
            continue;
        } else {
            break;
        }
    }
    if (data == end) {
        return res;
    }

    eq = false;
    while (data < end) {
        --end;
        for (const char &  val: ch) {
            if (*end == val) {
                eq = true;
                break;
            }
        }
        if (eq) {
            eq = false;
            continue;
        } else {
            break;
        }
    }
    ++end;
    res = std::string(data, end - data);

    return res;
}

std::string
toHex(const char *  data,
      const size_t  size)
{
    const char  hex_chars[] = "0123456789abcdef";
    std::string  res;
    for (size_t  i = 0; i < size; ++i) {
        res += hex_chars[ (static_cast<unsigned char>(data[i]) >> 4) & 0x0f ];
        res += hex_chars[ static_cast<unsigned char>(data[i]) & 0x0f ];
    }
    return res;
}

bool
checkReg(const std::string &  value)
{
    return checkReg(value.data(), value.size());
}

bool
checkReg(const char *  data,
         const size_t  size)
{
    if (data == nullptr || size == 0) {
        return false;
    }
    for (size_t  i = 0; i < size; ++i) {
        if (i == 0) {
            if (!static_cast<bool>(isalphaS(*data))) return false;
        } else {
            if (!(static_cast<bool>(isalnumS(*(data + i))) || *(data + i) == '_' )){
                return false;
            }
        }
    }
    return true;
}

std::vector<std::string>
split(const std::string &  value,
      const std::string &  delim)
{
    return split(value.data(), value.size(), delim);
}

std::vector<std::string>
split(const char *  data,
      const size_t  size,
      const std::string &  delim)
{
    std::vector<std::string>  res;
    if (data == nullptr) {
        return res;
    }
    if (size == 0 || delim.empty()) {
        res.emplace_back(data, size);
        return res;
    }

    const char *  databegin = data;
    const char *  end = data + size;
    const char *  dmend = delim.data() + delim.size();
    bool  eq = false;
    for (const char *  val = data; val < end; ++val) {
        for (const char *  dmval = delim.data(); dmval < dmend; ++dmval) {
            if (*val == *dmval) {
                eq = true;
                break;
            }
        }
        if (eq) {
            const size_t  tmpsize = val - databegin;
            if (tmpsize > 0) {
                res.emplace_back(databegin, tmpsize);
            }
            databegin = val + 1;
            eq = false;
        }
    }
    if (databegin != end) {
        res.emplace_back(databegin, (end - databegin));
    }

    return res;
}

std::vector<std::string_view>
splitLine(const std::string &  value)
{
    return splitLine(value.data(), value.size());
}

std::vector<std::string_view>
splitLine(const char *  data,
          const size_t  size)
{
    std::vector<std::string_view>  vecLine;
    if (data == nullptr || size == 0)  return vecLine;

    const char *  pData = data;
    size_t  pSize = 0;

    for (size_t  i = 0; i < size; ++i) {
        if (*data == '\r') {
            std::string_view const  sv(pData, pSize);
            vecLine.push_back(sv);
            pData = data + 1;
            pSize = 0;
        } else if (*data == '\n') {
            if (i == 0) {
                std::string_view const  sv(pData, pSize);
                vecLine.push_back(sv);
                pData = data + 1;
                pSize = 0;
            } else {
                if (*(data - 1) == '\r') {
                    pData = data + 1;
                } else {
                    std::string_view const  sv(pData, pSize);
                    vecLine.push_back(sv);
                    pData = data + 1;
                    pSize = 0;
                }
            }
        } else {
            pSize++;
            if (i == size - 1) {
                std::string_view const  sv(pData, pSize);
                vecLine.push_back(sv);
            }
        }
        data++;
    }

    return vecLine;
}

bool
isPrmType(const std::string &  typestr,
          std::string *  label /* = nullptr */)
{
    auto  bool_ptr =
        std::make_shared<std::string>(std::string("bool"));
    auto  char_ptr =
        std::make_shared<std::string>(std::string("char"));
    auto  signed_char_ptr =
        std::make_shared<std::string>(std::string("signed char"));
    auto  unsigned_char_ptr =
        std::make_shared<std::string>(std::string("unsigned char"));
    auto  short_ptr =
        std::make_shared<std::string>(std::string("short"));
    auto  unsigned_short_ptr =
        std::make_shared<std::string>(std::string("unsigned short"));
    auto  int_ptr =
        std::make_shared<std::string>(std::string("int"));
    auto  unsigned_ptr =
        std::make_shared<std::string>(std::string("unsigned"));
    auto  long_ptr =
        std::make_shared<std::string>(std::string("long"));
    auto  unsigned_long_ptr =
        std::make_shared<std::string>(std::string("unsigned long"));
    auto  long_long_ptr =
        std::make_shared<std::string>(std::string("long long"));
    auto  unsigned_long_long_ptr =
        std::make_shared<std::string>(std::string("unsigned long long"));
    auto  float_ptr =
        std::make_shared<std::string>(std::string("float"));
    auto  double_ptr =
        std::make_shared<std::string>(std::string("double"));
    auto  long_double_ptr =
        std::make_shared<std::string>(std::string("long double"));
    auto  wchar_t_ptr =
        std::make_shared<std::string>(std::string("wchar_t"));
    auto  char16_t_ptr =
        std::make_shared<std::string>(std::string("char16_t"));
    auto  char32_t_ptr =
        std::make_shared<std::string>(std::string("char32_t"));
    auto  size_t_ptr =
        std::make_shared<std::string>(std::string("size_t"));
    auto  ptrdiff_t_ptr =
        std::make_shared<std::string>(std::string("ptrdiff_t"));
    auto  time_t_ptr =
        std::make_shared<std::string>(std::string("time_t"));
    auto  int8_t_ptr =
        std::make_shared<std::string>(std::string("int8_t"));
    auto  int16_t_ptr =
        std::make_shared<std::string>(std::string("int16_t"));
    auto  int32_t_ptr =
        std::make_shared<std::string>(std::string("int32_t"));
    auto  int64_t_ptr =
        std::make_shared<std::string>(std::string("int64_t"));
    auto  int_fast8_t_ptr =
        std::make_shared<std::string>(std::string("int_fast8_t"));
    auto  int_fast16_t_ptr =
        std::make_shared<std::string>(std::string("int_fast16_t"));
    auto  int_fast32_t_ptr =
        std::make_shared<std::string>(std::string("int_fast32_t"));
    auto  int_fast64_t_ptr =
        std::make_shared<std::string>(std::string("int_fast64_t"));
    auto  int_least8_t_ptr =
        std::make_shared<std::string>(std::string("int_least8_t"));
    auto  int_least16_t_ptr =
        std::make_shared<std::string>(std::string("int_least16_t"));
    auto  int_least32_t_ptr =
        std::make_shared<std::string>(std::string("int_least32_t"));
    auto  int_least64_t_ptr =
        std::make_shared<std::string>(std::string("int_least64_t"));
    auto  intmax_t_ptr =
        std::make_shared<std::string>(std::string("intmax_t"));
    auto  intptr_t_ptr =
        std::make_shared<std::string>(std::string("intptr_t"));
    auto  uint8_t_ptr =
        std::make_shared<std::string>(std::string("uint8_t"));
    auto  uint16_t_ptr =
        std::make_shared<std::string>(std::string("uint16_t"));
    auto  uint32_t_ptr =
        std::make_shared<std::string>(std::string("uint32_t"));
    auto  uint64_t_ptr =
        std::make_shared<std::string>(std::string("uint64_t"));
    auto  uint_fast8_t_ptr =
        std::make_shared<std::string>(std::string("uint_fast8_t"));
    auto  uint_fast16_t_ptr =
        std::make_shared<std::string>(std::string("uint_fast16_t"));
    auto  uint_fast32_t_ptr =
        std::make_shared<std::string>(std::string("uint_fast32_t"));
    auto  uint_fast64_t_ptr =
        std::make_shared<std::string>(std::string("uint_fast64_t"));
    auto  uint_least8_t_ptr =
        std::make_shared<std::string>(std::string("uint_least8_t"));
    auto  uint_least16_t_ptr =
        std::make_shared<std::string>(std::string("uint_least16_t"));
    auto  uint_least32_t_ptr =
        std::make_shared<std::string>(std::string("uint_least32_t"));
    auto  uint_least64_t_ptr =
        std::make_shared<std::string>(std::string("uint_least64_t"));
    auto  uintmax_t_ptr =
        std::make_shared<std::string>(std::string("uintmax_t"));
    auto  uintptr_t_ptr =
        std::make_shared<std::string>(std::string("uintptr_t"));

    using cchild_ty = std::multimap<std::string, std::shared_ptr<std::string>>;
    using child_t = std::vector<std::vector<cchild_ty>>;
    std::map<size_t, child_t>  prmtypes;
    cchild_ty  mms;
    std::vector<cchild_ty>  mid_mms;
    std::vector<std::vector<cchild_ty>>  child_mms;

    mms.emplace("bool", bool_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("char", char_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("short", short_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int", int_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("signed", int_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("unsigned", unsigned_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("long", long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("float", float_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("double", double_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("wchar_t", wchar_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("char16_t", char16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("char32_t", char32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("size_t", size_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::size_t", size_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("ptrdiff_t", ptrdiff_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::ptrdiff_t", ptrdiff_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("time_t", time_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::time_t", time_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int8_t", int8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int8_t", int8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int16_t", int16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int16_t", int16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int32_t", int32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int32_t", int32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int64_t", int64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int64_t", int64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int_fast8_t", int_fast8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int_fast8_t", int_fast8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int_fast16_t", int_fast16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int_fast16_t", int_fast16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int_fast32_t", int_fast32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int_fast32_t", int_fast32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int_fast64_t", int_fast64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int_fast64_t", int_fast64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int_least8_t", int_least8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int_least8_t", int_least8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int_least16_t", int_least16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int_least16_t", int_least16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int_least32_t", int_least32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int_least32_t", int_least32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("int_least64_t", int_least64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::int_least64_t", int_least64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("intmax_t", intmax_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::intmax_t", intmax_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("intptr_t", intptr_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::intptr_t", intptr_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint8_t", uint8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint8_t", uint8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint16_t", uint16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint16_t", uint16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint32_t", uint32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint32_t", uint32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint64_t", uint64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint64_t", uint64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint_fast8_t", uint_fast8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint_fast8_t", uint_fast8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint_fast16_t", uint_fast16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint_fast16_t", uint_fast16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint_fast32_t", uint_fast32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint_fast32_t", uint_fast32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint_fast64_t", uint_fast64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint_fast64_t", uint_fast64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint_least8_t", uint_least8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint_least8_t", uint_least8_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint_least16_t", uint_least16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint_least16_t", uint_least16_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint_least32_t", uint_least32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint_least32_t", uint_least32_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uint_least64_t", uint_least64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uint_least64_t", uint_least64_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uintmax_t", uintmax_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uintmax_t", uintmax_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("uintptr_t", uintptr_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("std::uintptr_t", uintptr_t_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    prmtypes[1] = child_mms;
    child_mms.clear();

    mms.emplace("signed", signed_char_ptr);
    mms.emplace("char", signed_char_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("unsigned", unsigned_char_ptr);
    mms.emplace("char", unsigned_char_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("signed", short_ptr);
    mms.emplace("short", short_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("short", short_ptr);
    mms.emplace("int", short_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("unsigned", unsigned_short_ptr);
    mms.emplace("short", unsigned_short_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("signed", int_ptr);
    mms.emplace("int", int_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("unsigned", unsigned_ptr);
    mms.emplace("int", unsigned_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("long", long_ptr);
    mms.emplace("int", long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("signed", long_ptr);
    mms.emplace("long", long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("unsigned", unsigned_long_ptr);
    mms.emplace("long", unsigned_long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("long", long_long_ptr);
    mms.emplace("long", long_long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("long", long_double_ptr);
    mms.emplace("double", long_double_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    prmtypes[2] = child_mms;
    child_mms.clear();

    mms.emplace("signed", short_ptr);
    mms.emplace("short", short_ptr);
    mms.emplace("int", short_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("unsigned", unsigned_short_ptr);
    mms.emplace("short", unsigned_short_ptr);
    mms.emplace("int", unsigned_short_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("signed", long_ptr);
    mms.emplace("long", long_ptr);
    mms.emplace("int", long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("unsigned", unsigned_long_ptr);
    mms.emplace("long", unsigned_long_ptr);
    mms.emplace("int", unsigned_long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("signed", long_long_ptr);
    mms.emplace("long", long_long_ptr);
    mms.emplace("long", long_long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("long", long_long_ptr);
    mms.emplace("long", long_long_ptr);
    mms.emplace("int", long_long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("unsigned", unsigned_long_long_ptr);
    mms.emplace("long", unsigned_long_long_ptr);
    mms.emplace("long", unsigned_long_long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    prmtypes[3] = child_mms;
    child_mms.clear();

    mms.emplace("signed", long_long_ptr);
    mms.emplace("long", long_long_ptr);
    mms.emplace("long", long_long_ptr);
    mms.emplace("int", long_long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    mms.emplace("unsigned", unsigned_long_long_ptr);
    mms.emplace("long", unsigned_long_long_ptr);
    mms.emplace("long", unsigned_long_long_ptr);
    mms.emplace("int", unsigned_long_long_ptr);
    mid_mms.push_back(mms);
    child_mms.push_back(mid_mms);
    mms.clear();
    mid_mms.clear();

    prmtypes[4] = child_mms;
    child_mms.clear();

    auto  in_type = split(typestr, " ");
    std::sort(in_type.begin(), in_type.end());
    const size_t  size = in_type.size();
    if (size == 0 || size > 4) {
        return false;
    }
    auto  vp = prmtypes.find(size);
    if (vp == prmtypes.end()) {
        return false;
    }
    auto &  se = vp->second;

    if (size == 1) {
        for (auto &  vcx: se) {
            auto  vip = vcx[0].find(in_type[0]);
            if (vip != vcx[0].end()) {
                if (label != nullptr) {
                    *label = *(vip->second);
                }
                return true;
            }
        }
        return false;
    }

    if (size > 1) {
        std::string  in_tmp_str;
        for (auto &  tmp: in_type) {
            in_tmp_str += tmp;
        }
        for (auto &  vcx: se) {
            std::string  com_str;
            for (auto &  mpd: vcx) {
                for (auto &  paty: mpd) {
                    com_str += paty.first;
                }
            }
            if (in_tmp_str == com_str) {
                auto  vip = vcx[0].find(in_type[0]);
                if (label != nullptr) {
                    *label = *(vip->second);
                }
                return true;
            }
        }
        return false;
    }

    return false;
}

void
procCode(std::string &  sourceCode)
{
    if (sourceCode.size() > 0 ) {
        while (true) {
            auto  it = std::find(sourceCode.begin(), sourceCode.end(), '\t');
            if (it == sourceCode.end())  break;
            sourceCode.replace(it, it + 1, 4, ' ');
        }
        if (sourceCode[sourceCode.size() - 1] == '\n' ||
                sourceCode[sourceCode.size() - 1] == '\r') {
            ;
        } else {
            sourceCode += "\n";
        }
    }
}

int
isalnumS(int  ch)
{
    return static_cast<char>(std::isalnum(static_cast<unsigned char>(ch)));
}

int
isalphaS(int  ch)
{
    return static_cast<char>(std::isalpha(static_cast<unsigned char>(ch)));
}

int
islowerS(int  ch)
{
    return static_cast<char>(std::islower(static_cast<unsigned char>(ch)));
}

int
isupperS(int  ch)
{
    return static_cast<char>(std::isupper(static_cast<unsigned char>(ch)));
}

int
isdigitS(int  ch)
{
    return static_cast<char>(std::isdigit(static_cast<unsigned char>(ch)));
}

int
isxdigitS(int  ch)
{
    return static_cast<char>(std::isxdigit(static_cast<unsigned char>(ch)));
}

int
iscntrlS(int  ch)
{
    return static_cast<char>(std::iscntrl(static_cast<unsigned char>(ch)));
}

int
isgraphS(int  ch)
{
    return static_cast<char>(std::isgraph(static_cast<unsigned char>(ch)));
}

int
isspaceS(int  ch)
{
    return static_cast<char>(std::isspace(static_cast<unsigned char>(ch)));
}

int
isblankS(int  ch)
{
    return static_cast<char>(std::isblank(static_cast<unsigned char>(ch)));
}

int
isprintS(int  ch)
{
    return static_cast<char>(std::isprint(static_cast<unsigned char>(ch)));
}

int
ispunctS(int  ch)
{
    return static_cast<char>(std::ispunct(static_cast<unsigned char>(ch)));
}

int
tolowerS(int  ch)
{
    return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
}

int
toupperS(int  ch)
{
    return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
}

}
