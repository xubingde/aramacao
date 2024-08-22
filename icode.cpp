#include <algorithm>
#include <cstring>
#include "icode.h"

namespace xu {

void
append(std::string &  pkg,
       const std::string &  value)
{
    append(pkg, value.data(), value.size());
}

void
append(std::string &  pkg,
       const std::string_view &  value)
{
    append(pkg, value.data(), value.size());
}

void
append(std::string &  pkg,
       const char *  data,
       const size_t  size)
{
    if (data == nullptr || size == 0) {
        pkg.append(makeHead(0));
    } else {
        pkg.append(makeHead(size));
        pkg.append(data, size);
    }
}

std::vector<std::string_view>
viewIcode(const std::string &  value) noexcept
{
    return viewIcode(value.data(), value.size());
}

std::vector<std::string_view>
viewIcode(const std::string_view &  value) noexcept
{
    return viewIcode(value.data(), value.size());
}

std::vector<std::string_view>
viewIcode(const char *  data,
          const size_t  size) noexcept
{
    std::vector<std::string_view> res;
    if (!(size == 0 || data == nullptr)) {
        Icode::viewSection(data, size, res);
    }
    return res;
}

std::pair<size_t, size_t>
extHead(const char *  data,
        const size_t  size) noexcept
{
    std::pair<size_t, size_t>  res { 0, 0 };
    if (data == nullptr || size == 0) {
        return res;
    }

    const char  head_char = *data;
    switch (head_char) {
        case Icode::cs_MAX2:
            if (size > 2) {
                std::get<0>(res) = 3;
                std::get<1>(res) = Icode::stou16(data + 1);
            }
            break;
        case Icode::cs_MAX4:
            if (size > 4) {
                std::get<0>(res) = 5;
                std::get<1>(res) = Icode::stou32(data + 1);
            }
            break;
        case Icode::cs_MAX8:
            if (size > 8) {
                std::get<0>(res) = 9;
                std::get<1>(res) = Icode::stou64(data + 1);
            }
            break;
        default:
            std::get<0>(res) = 1;
            std::get<1>(res) = static_cast<unsigned char>(head_char);
            break;
    }
    return res;
}

std::string
makeHead(const size_t  size)
{
    std::string  res;
    if (size <= Icode::cs_MAX_SIZE) {
        res.push_back(static_cast<unsigned char>(size));
    } else if (size <= UINT16_MAX) {
        res.push_back(Icode::cs_MAX2);
        res.append(Icode::u16tos(static_cast<uint16_t>(size)));
    } else if (size <= UINT32_MAX) {
        res.push_back(Icode::cs_MAX4);
        res.append(Icode::u32tos(static_cast<uint32_t>(size)));
    } else {
        res.push_back(Icode::cs_MAX8);
        res.append(Icode::u64tos(size));
    }
    return res;
}

bool
fromString(bool &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(bool &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(bool &  res,
           const char *  data,
           const size_t  size)
{
    if (size > 1) {
        return false;
    } else {
        if (data == nullptr || size == 0) {
            res = false;
        } else {
            res = static_cast<bool>(*data);
        }
        return true;
    }
}

bool
fromString(char &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(char &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(char &  res,
           const char *  data,
           const size_t  size)
{
    if (size > 1) {
        return false;
    } else {
        if (data == nullptr || size == 0) {
            res = '\0';
        } else {
            res = *data;
        }
        return true;
    }
}

bool
fromString(signed char &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(signed char &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(signed char &  res,
           const char *  data,
           const size_t  size)
{
    char  ch;
    if (fromString(ch, data, size)) {
        res = static_cast<signed char>(ch);
        return true;
    } else {
        return false;
    }
}

bool
fromString(unsigned char &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(unsigned char &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(unsigned char &  res,
           const char *  data,
           const size_t  size)
{
    char  ch;
    if (fromString(ch, data, size)) {
        res = static_cast<unsigned char>(ch);
        return true;
    } else {
        return false;
    }
}

bool
fromString(long long &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(long long &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(long long &  res,
           const char *  data,
           const size_t  size)
{
    if (size > sizeof(long long) + 1) {
        return false;
    } else {
        if (size == 0 || data == nullptr) {
            res = 0;
        } else {
            const unsigned char  chPtr = *data;
            if (size == 1) {
                res = chPtr;
            } else {
                res = Icode::cpy_int(data + 1, size - 1);
                if (chPtr == Icode::cs_SERZ_T_NINT) {
                    res = -res;
                }
            }
        }
        return true;
    }
}

bool
fromString(unsigned long long &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(unsigned long long &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(unsigned long long &  res,
           const char *  data,
           const size_t  size)
{
    if (size > sizeof(unsigned long long)) {
        return false;
    } else {
        if (size == 0 || data == nullptr) {
            res = 0;
        } else {
            res = Icode::cpy_int(data, size);
        }
        return true;
    }
}

bool
fromString(short &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(short &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(short &  res,
           const char *  data,
           const size_t  size)
{
    long long  value;
    if (fromString(value, data, size)) {
        const short  tmp = static_cast<short>(value);
        if (value == tmp) {
            res = tmp;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool
fromString(unsigned short &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(unsigned short &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(unsigned short &  res,
           const char *  data,
           const size_t  size)
{
    unsigned long long  value;
    if (fromString(value, data, size)) {
        const unsigned short  tmp = static_cast<unsigned short>(value);
        if (value == tmp) {
            res = tmp;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool
fromString(int &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(int &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(int &  res,
           const char *  data,
           const size_t  size)
{
    long long  value;
    if (fromString(value, data, size)) {
        const int  tmp = static_cast<int>(value);
        if (value == tmp) {
            res = tmp;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool
fromString(unsigned int &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(unsigned int &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(unsigned int &  res,
           const char *  data,
           const size_t  size)
{
    unsigned long long  value;
    if (fromString(value, data, size)) {
        const unsigned int  tmp = static_cast<unsigned int>(value);
        if (value == tmp) {
            res = tmp;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool
fromString(long &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(long &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(long &  res,
           const char *  data,
           const size_t  size)
{
    long long  value;
    if (fromString(value, data, size)) {
        const long  tmp = static_cast<long>(value);
        if (value == tmp) {
            res = tmp;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool
fromString(unsigned long &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(unsigned long &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(unsigned long &  res,
           const char *  data,
           const size_t  size)
{
    unsigned long long  value;
    if (fromString(value, data, size)) {
        const unsigned long  tmp = static_cast<unsigned long>(value);
        if (value == tmp) {
            res = tmp;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool
fromString(std::chrono::time_point<std::chrono::system_clock> &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::chrono::time_point<std::chrono::system_clock> &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(std::chrono::time_point<std::chrono::system_clock> &  res,
           const char *  data,
           const size_t  size)
{
    long long  value;
    if (fromString(value, data, size)) {
        const time_t  tmp = static_cast<time_t>(value);
        if (value == tmp) {
            res = std::chrono::system_clock::from_time_t(tmp);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool
fromString(float &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(float &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(float &  res,
           const char *  data,
           const size_t  size)
{
    if (size > sizeof(float)) {
        return false;
    } else {
        if (size == 0 || data == nullptr) {
            res = 0;
        } else {
            union {
                float  fl;
                char  ch[sizeof(float)];
            } brick;
            brick.fl = 0;

            const size_t  fld_size = sizeof(float);
            char *  begin = std::begin(brick.ch);
            Icode::cpy_df(begin, fld_size, data, size);
            res = brick.fl;
        }
        return true;
    }
}

bool
fromString(double &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(double &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(double &  res,
           const char *  data,
           const size_t  size)
{
    if (size > sizeof(double)) {
        return false;
    } else {
        if (size == 0 || data == nullptr) {
            res = 0;
        } else {
            union {
                double  df;
                char  ch[sizeof(double)];
            } brick;
            brick.df = 0;

            const size_t  df_size = sizeof(double);
            char *  begin = std::begin(brick.ch);
            Icode::cpy_df(begin, df_size, data, size);
            res = brick.df;
        }
        return true;
    }
}

bool
fromString(long double &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(long double &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

bool
fromString(long double &  res,
           const char *  data,
           const size_t  size)
{
    if (size > sizeof(long double)) {
        return false;
    } else {
        if (size == 0 || data == nullptr) {
            res = 0;
        } else {
            union {
                long double  ldf;
                char  ch[sizeof(long double)];
            } brick;
            brick.ldf = 0;

            const size_t  ldf_size = sizeof(long double);
            char *  begin = std::begin(brick.ch);
            Icode::cpy_df(begin, ldf_size, data, size);
            res = brick.ldf;
        }
        return true;
    }
}

bool
fromString(std::string &  res,
           const std::string &  value)
{
    res = value;
    return true;
}

bool
fromString(std::string &  res,
           const std::string_view &  value)
{
    res = value;
    return true;
}

bool
fromString(std::string &  res,
           const char *  data,
           const size_t  size)
{
    if (data == nullptr && size > 0) {
        return false;
    } else {
        res = std::string(data, size);
        return true;
    }
}

std::string
toJsonString(const std::string &  value)
{
    std::string  str;
    for (const auto &  ch: value) {
        switch (ch) {
            case '\"':
                str.push_back('\\');
                str.push_back('\"');
                break;
            case '\\':
                str.push_back('\\');
                str.push_back('\\');
                break;
            case '/':
                str.push_back('\\');
                str.push_back('/');
                break;
            case '\b':
                str.push_back('\\');
                str.push_back('b');
                break;
            case '\f':
                str.push_back('\\');
                str.push_back('f');
                break;
            case '\n':
                str.push_back('\\');
                str.push_back('n');
                break;
            case '\r':
                str.push_back('\\');
                str.push_back('r');
                break;
            case '\t':
                str.push_back('\\');
                str.push_back('t');
                break;
            default:
                str.push_back(ch);
                break;
        }
    }
    return str;
}

std::string
fromJsonString(const std::string &  value)
{
    std::string  str;
    bool  flag = false;
    for (const auto &  ch: value) {
        if (!flag) {
            if (ch == '\\') {
                flag = true;
            } else {
                str.push_back(ch);
            }
            continue;
        }

        if (flag) {
            switch (ch) {
                case '\"':
                    str.push_back('\"');
                    break;
                case '\\':
                    str.push_back('\\');
                    break;
                case '/':
                    str.push_back('/');
                    break;
                case 'b':
                    str.push_back('\b');
                    break;
                case 'f':
                    str.push_back('\f');
                    break;
                case 'n':
                    str.push_back('\n');
                    break;
                case 'r':
                    str.push_back('\r');
                    break;
                case 't':
                    str.push_back('\t');
                    break;
            }
            flag = false;
        }
    }

    return str;
}

std::string
toString(const std::string &  value)
{
    return value;
}

std::string
toString(const char *  data,
         const size_t  size)
{
    return std::string(data, size);
}

std::string
toString(const bool  value)
{
    std::string  result;
    if (value) {
        result.push_back('\1');
    }
    return result;
}

std::string
toString(const char  value)
{
    std::string  res { value };
    if (value == '\0') {
        res.pop_back();
    }
    return res;
}

std::string
toString(const signed char  value)
{
    std::string  res { static_cast<char>(value) };
    if (value == 0) {
        res.pop_back();
    }
    return res;
}

std::string
toString(const unsigned char  value)
{
    std::string  res { static_cast<char>(value) };
    if (value == 0) {
        res.pop_back();
    }
    return res;
}

std::string
toString(const short  value)
{
    const long long  nint = value;
    return Icode::to_s(nint);
}

std::string
toString(const unsigned short  value)
{
    const unsigned long long  pint = value;
    return Icode::to_s(pint);
}

std::string
toString(const int  value)
{
    const long long  nint = value;
    return Icode::to_s(nint);
}

std::string
toString(const unsigned int  value)
{
    const unsigned long long  pint = value;
    return Icode::to_s(pint);
}

std::string
toString(const long  value)
{
    const long long  nint = value;
    return Icode::to_s(nint);
}

std::string
toString(const unsigned long  value)
{
    const unsigned long long  pint = value;
    return Icode::to_s(pint);
}

std::string
toString(const long long  value)
{
    return Icode::to_s(value);
}

std::string
toString(const unsigned long long  value)
{
    return Icode::to_s(value);
}

std::string
toString(const std::chrono::time_point<std::chrono::system_clock> &  value)
{
    const time_t  myTime = std::chrono::system_clock::to_time_t(value);
    return toString(myTime);
}

std::string
toString(const float  value)
{
    std::string  res;
    if (value == 0) {
        return res;
    }
    union {
        float  fl;
        char  ch[sizeof(float)];
    } brick;
    brick.fl = value;

    const char *  begin = std::begin(brick.ch);
    const size_t  size = sizeof(float);
    res = Icode::d_to_s(begin, size);
    return res;
}

std::string
toString(const double  value)
{
    std::string  res;
    if (value == 0) {
        return res;
    }
    union {
        double  df;
        char  ch[sizeof(double)];
    } brick;
    brick.df = value;

    const char *  begin = std::begin(brick.ch);
    const size_t  size = sizeof(double);
    res = Icode::d_to_s(begin, size);
    return res;
}

std::string
toString(const long double  value)
{
    std::string  res;
    if (value == 0) {
        return res;
    }
    union {
        long double  ld;
        char  ch[sizeof(long double)];
    } brick;
    brick.ld = value;

    const char *  begin = std::begin(brick.ch);
    const size_t  size = sizeof(long double);
    res = Icode::d_to_s(begin, size);
    return res;
}

bool
isLittle() noexcept
{
    static int const  ch = 1;
    return static_cast<bool>(*reinterpret_cast<char const *>(&ch));
}

Icode::~Icode() noexcept
{
}

std::string
Icode::u16tos(const uint16_t  value)
{
    std::string  res;
    union {
        char  ch[2];
        uint16_t  u16;
    };

    u16 = value;
    if (isLittle()) {
        for (int  i = 0; i < 2; ++i) {
            res.push_back(ch[1 - i]);
        }
    } else {
        res.append(ch, 2);
    }
    return res;
}

std::string
Icode::u32tos(const uint32_t  value)
{
    std::string  res;
    union {
        char  ch[4];
        uint32_t  u32;
    };

    u32 = value;
    if (isLittle()) {
        for (int  i = 0; i < 4; ++i) {
            res.push_back(ch[3 - i]);
        }
    } else {
        res.append(ch, 4);
    }
    return res;
}

std::string
Icode::u64tos(const uint64_t  value)
{
    std::string  res;
    union {
        char  ch[8];
        uint64_t  u64;
    };

    u64 = value;
    if (isLittle()) {
        for (int  i = 0; i < 8; ++i) {
            res.push_back(ch[7 - i]);
        }
    } else {
        res.append(ch, 8);
    }
    return res;
}

uint16_t
Icode::stou16(const char *  data) noexcept
{
    union {
        char  ch[2];
        uint16_t  u16;
    };
    if (isLittle()) {
        for (int  i = 0; i < 2; ++i) {
            ch[i] = data[1 - i];
        }
    } else {
        memcpy(ch, data, 2);
    }
    return u16;
}

uint32_t
Icode::stou32(const char *  data) noexcept
{
    union {
        char  ch[4];
        uint32_t  u32;
    };
    if (isLittle()) {
        for (int  i = 0; i < 4; ++i) {
            ch[i] = data[3 - i];
        }
    } else {
        memcpy(ch, data, 4);
    }
    return u32;
}

uint64_t
Icode::stou64(const char *  data) noexcept
{
    union {
        char  ch[8];
        uint64_t  u64;
    };
    if (isLittle()) {
        for (int  i = 0; i < 8; ++i) {
            ch[i] = data[7 - i];
        }
    } else {
        memcpy(ch, data, 8);
    }
    return u64;
}

void
Icode::viewSection(const char *  data,
                   size_t  size,
                   std::vector<std::string_view> &  res) noexcept
{
    if (size == 0) {
        return;
    }

    const char  head_char = *data;
    size_t  tail, headlen;
    switch (head_char) {
        case cs_MAX2:
            headlen = 3;
            if (size < headlen) {
                res.clear();
                return;
            }
            tail = stou16(data + 1) + 3ull;
            break;
        case cs_MAX4:
            headlen = 5;
            if (size < headlen) {
                res.clear();
                return;
            }
            tail = stou32(data + 1) + 5ull;
            break;
        case cs_MAX8:
            headlen = 9;
            if (size < headlen) {
                res.clear();
                return;
            }
            tail = stou64(data + 1) + 9ull;
            break;
        default:
            headlen = 1;
            tail = static_cast<unsigned char>(head_char) + 1ull;
            break;
    }
    if (size < tail) {
        res.clear();
        return;
    } else {
        res.emplace_back(data + headlen, tail - headlen);
    }

    data += tail;
    size -= tail;
    viewSection(data, size, res);
}

std::string
Icode::to_s(const unsigned long long &  value)
{
    std::string  result;
    if (value == 0) {
        return result;
    }
    pint_to_s(result, value);
    return result;
}

std::string
Icode::to_s(const long long &  value)
{
    std::string  result;
    if (value == 0) {
        return result;
    }

    unsigned long long  ull_value;
    if (value < 0) {
        result.push_back(cs_SERZ_T_NINT);
        ull_value = -value;
        pint_to_s(result, ull_value);
    } else {
        ull_value = value;
        unsigned char  ch;
        if (ull_value <= 255 ) {
            ch = static_cast<unsigned char>(ull_value);
            result.push_back(ch);
        } else {
            result.push_back(cs_SERZ_T_PINT);
            pint_to_s(result, ull_value);
        }
    }
    return result;
}

void
Icode::pint_to_s(std::string &  data,
                 const unsigned long long &  value)
{
    union {
        unsigned long long  ull;
        char  ch[sizeof(unsigned long long)];
    } brick;
    brick.ull = value;

    auto  begin = std::begin(brick.ch);
    auto  end = std::end(brick.ch);
    if (isLittle()) {
        --begin;
        --end;
        for (; begin != end; --end) {
            if (*end != 0)
                break;
        }
        ++begin;
        ++end;
        for (; begin != end; ++begin) {
            data.push_back(*begin);
        }
    } else {
        for (; begin != end; ++begin) {
            if (*begin != 0)
                break;
        }
        --begin;
        --end;
        for (; begin != end; --end) {
            data.push_back(*end);
        }
    }
}

unsigned long long
Icode::cpy_int(const char *  data,
               size_t  size) noexcept
{
    union {
        unsigned long long  ull;
        char  ch[sizeof(unsigned long long)];
    } brick;
    brick.ull = 0;
    const size_t  total = sizeof(unsigned long long);
    if (size > total)
        size = total;

    const char *  data_end = data + size;
    if (isLittle()) {
        auto  begin = std::begin(brick.ch);
        for (; data != data_end; ++data) {
            *begin++ = *data;
        }
    } else {
        auto  end = std::end(brick.ch);
        --end;
        for (; data != data_end; ++data) {
            *end-- = *data;
        }
    }
    return brick.ull;
}

std::string
Icode::d_to_s(const char *  data,
              const size_t  size)
{
    std::string  result;
    const char *  end = data + size;
    if (isLittle()) {
        for (; data != end; ++data) {
            if (*data != 0)
                break;
        }
        --data;
        --end;
        for (; data != end; --end) {
            result.push_back(*end);
        }
    } else {
        --data;
        --end;
        for (; data != end; --end) {
            if (*end != 0)
                break;
        }
        ++data;
        ++end;
        for (; data != end; ++data) {
            result.push_back(*data);
        }
    }
    return result;
}

void
Icode::cpy_df(char *  dest,
              const size_t  dest_size,
              const char *  src,
              const size_t  src_size) noexcept
{
    size_t  safe_size = src_size;
    if (src_size > dest_size)  safe_size = dest_size;

    char *  dest_end = dest + dest_size;
    const char *  src_end = src + safe_size;

    if (isLittle()) {
        --dest_end;
        for (; src != src_end; ++src) {
            *dest_end-- = *src;
        }
    } else {
        for (; src != src_end; ++src) {
            *dest++ = *src;
        }
    }
}

bool
operator==(const Icode &  lhs,
           const Icode &  rhs)
{
    if (&lhs == &rhs) return true;
    bool  result = false;

    return result;
}

bool
operator!=(const Icode &  lhs,
           const Icode &  rhs)
{
    return !(lhs == rhs);
}

}
