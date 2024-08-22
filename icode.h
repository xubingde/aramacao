#pragma once

#ifndef XU_ICODE_H_
#define XU_ICODE_H_

#include <string>
#include <cstdint>
#include <string_view>
#include <vector>
#include <map>
#include <set>
#include <array>
#include <list>
#include <utility>
#include <tuple>
#include <ctime>
#include <chrono>
#include <type_traits>
#include <memory>

namespace xu {

class Icode;

template <typename, template <typename...> class>
struct is_specialization: std::false_type {};

template <template <typename...> class Template, typename... Args>
struct is_specialization<Template<Args...>, Template>: std::true_type {};

void  append(std::string &  pkg, const std::string &  value);
void  append(std::string &  pkg, const std::string_view &  value);
void  append(std::string &  pkg, const char *  data, const size_t  size);
std::vector<std::string_view>  viewIcode(const std::string &  value) noexcept;
std::vector<std::string_view>  viewIcode(const std::string_view &  value) noexcept;
std::vector<std::string_view>  viewIcode(const char *  data, const size_t  size) noexcept;
std::pair<size_t, size_t>  extHead(const char *  data, const size_t  size) noexcept;
std::string  makeHead(const size_t  size);
bool  fromString(bool &  res, const std::string &  value);
bool  fromString(bool &  res, const std::string_view &  value);
bool  fromString(bool &  res, const char *  data, const size_t  size);
bool  fromString(char &  res, const std::string &  value);
bool  fromString(char &  res, const std::string_view &  value);
bool  fromString(char &  res, const char *  data, const size_t  size);
bool  fromString(signed char &  res, const std::string &  value);
bool  fromString(signed char &  res, const std::string_view &  value);
bool  fromString(signed char &  res, const char *  data, const size_t  size);
bool  fromString(unsigned char &  res, const std::string &  value);
bool  fromString(unsigned char &  res, const std::string_view &  value);
bool  fromString(unsigned char &  res, const char *  data, const size_t  size);
bool  fromString(long long &  res, const std::string &  value);
bool  fromString(long long &  res, const std::string_view &  value);
bool  fromString(long long &  res, const char *  data, const size_t  size);
bool  fromString(unsigned long long &  res, const std::string &  value);
bool  fromString(unsigned long long &  res, const std::string_view &  value);
bool  fromString(unsigned long long &  res, const char *  data, const size_t  size);
bool  fromString(short &  res, const std::string &  value);
bool  fromString(short &  res, const std::string_view &  value);
bool  fromString(short &  res, const char *  data, const size_t  size);
bool  fromString(unsigned short &  res, const std::string &  value);
bool  fromString(unsigned short &  res, const std::string_view &  value);
bool  fromString(unsigned short &  res, const char *  data, const size_t  size);
bool  fromString(int &  res, const std::string &  value);
bool  fromString(int &  res, const std::string_view &  value);
bool  fromString(int &  res, const char *  data, const size_t  size);
bool  fromString(unsigned int &  res, const std::string &  value);
bool  fromString(unsigned int &  res, const std::string_view &  value);
bool  fromString(unsigned int &  res, const char *  data, const size_t  size);
bool  fromString(long &  res, const std::string &  value);
bool  fromString(long &  res, const std::string_view &  value);
bool  fromString(long &  res, const char *  data, const size_t  size);
bool  fromString(unsigned long &  res, const std::string &  value);
bool  fromString(unsigned long &  res, const std::string_view &  value);
bool  fromString(unsigned long &  res, const char *  data, const size_t  size);
bool  fromString(std::chrono::time_point<std::chrono::system_clock> &  res, const std::string &  value);
bool  fromString(std::chrono::time_point<std::chrono::system_clock> &  res, const std::string_view &  value);
bool  fromString(std::chrono::time_point<std::chrono::system_clock> &  res, const char *  data, const size_t  size);
bool  fromString(float &  res, const std::string &  value);
bool  fromString(float &  res, const std::string_view &  value);
bool  fromString(float &  res, const char *  data, const size_t  size);
bool  fromString(double &  res, const std::string &  value);
bool  fromString(double &  res, const std::string_view &  value);
bool  fromString(double &  res, const char *  data, const size_t  size);
bool  fromString(long double &  res, const std::string &  value);
bool  fromString(long double &  res, const std::string_view &  value);
bool  fromString(long double &  res, const char *  data, const size_t  size);
bool  fromString(std::string &  res, const std::string &  value);
bool  fromString(std::string &  res, const std::string_view &  value);
bool  fromString(std::string &  res, const char *  data, const size_t  size);
std::string  toJsonString(const std::string &  value);
std::string  fromJsonString(const std::string &  value);
std::string  toString(const std::string &  value);
std::string  toString(const char *  data, const size_t  size);
std::string  toString(const bool  value);
std::string  toString(const char  value);
std::string  toString(const signed char  value);
std::string  toString(const unsigned char  value);
std::string  toString(const short  value);
std::string  toString(const unsigned short  value);
std::string  toString(const int  value);
std::string  toString(const unsigned int  value);
std::string  toString(const long  value);
std::string  toString(const unsigned long  value);
std::string  toString(const long long  value);
std::string  toString(const unsigned long long  value);
std::string  toString(const std::chrono::time_point<std::chrono::system_clock> &  value);
std::string  toString(const float  value);
std::string  toString(const double  value);
std::string  toString(const long double  value);
bool  isLittle() noexcept;

template <typename T, typename U>
bool  fromString(std::pair<T, U> &  res, const std::string &  value);
template <typename T, typename U>
bool  fromString(std::pair<T, U> &  res, const std::string_view &  value);
template <typename T, typename U>
bool  fromString(std::pair<T, U> &  res, const char *  data, const size_t  size);
template <typename T, typename U>
bool  fromString(std::map<T, U> &  res, const std::string &  value);
template <typename T, typename U>
bool  fromString(std::map<T, U> &  res, const std::string_view &  value);
template <typename T, typename U>
bool  fromString(std::map<T, U> &  res, const char *  data, const size_t  size);
template <typename T>
bool  fromString(std::vector<T> &  res, const std::string &  value);
template <typename T>
bool  fromString(std::vector<T> &  res, const std::string_view &  value);
template <typename T>
bool  fromString(std::vector<T> &  res, const char *  data, const size_t  size);
template <typename T>
bool  fromString(std::list<T> &  res, const std::string &  value);
template <typename T>
bool  fromString(std::list<T> &  res, const std::string_view &  value);
template <typename T>
bool  fromString(std::list<T> &  res, const char *  data, const size_t  size);
template <typename T>
bool  fromString(std::set<T> &  res, const std::string &  value);
template <typename T>
bool  fromString(std::set<T> &  res, const std::string_view &  value);
template <typename T>
bool  fromString(std::set<T> &  res, const char *  data, const size_t  size);
template <typename T>
bool  fromString(T &  res, const std::string &  value);
template <typename T>
bool  fromString(T &  res, const std::string_view &  value);
template <typename T>
bool  fromString(T &  res, const char *  data, const size_t  size);
template <typename T, typename U>
std::string  toString(const std::pair<T, U> &  value);
template <typename T, typename U>
std::string  toString(const std::map<T, U> &  value);
template <typename T>
std::string  toString(const std::vector<T> &  value);
template <typename T>
std::string  toString(const std::list<T> &  value);
template <typename T>
std::string  toString(const std::set<T> &  value);
template <typename T>
std::string  toString(const T &  value);

template <size_t N>
constexpr void  append(std::string &  pkg, const char (&r)[N]);
template <typename Tuple, size_t... Is>
constexpr bool  from_for_each_tp(Tuple &  t, const std::vector<std::string_view> &  vi, std::index_sequence<Is...>);
template <typename Tuple, size_t... Is>
constexpr void  for_each_tp(std::string &  res, const Tuple &  t, std::index_sequence<Is...>);

bool  operator==(const Icode &  lhs, const Icode &  rhs);
bool  operator!=(const Icode &  lhs, const Icode &  rhs);

class Icode final
{
friend bool  operator==(const Icode &  lhs, const Icode &  rhs);
friend bool  operator!=(const Icode &  lhs, const Icode &  rhs);
friend void  append(std::string &  pkg, const std::string &  value);
friend void  append(std::string &  pkg, const std::string_view &  value);
friend void  append(std::string &  pkg, const char *  data, const size_t  size);
friend std::vector<std::string_view>  viewIcode(const std::string &  value) noexcept;
friend std::vector<std::string_view>  viewIcode(const std::string_view &  value) noexcept;
friend std::vector<std::string_view>  viewIcode(const char *  data, const size_t  size) noexcept;
friend std::pair<size_t, size_t>  extHead(const char *  data, const size_t  size) noexcept;
friend std::string  makeHead(const size_t  size);
friend bool  fromString(long long &  res, const char *  data, const size_t  size);
friend bool  fromString(unsigned long long &  res, const char *  data, const size_t  size);
friend bool  fromString(float &  res, const char *  data, const size_t  size);
friend bool  fromString(double &  res, const char *  data, const size_t  size);
friend bool  fromString(long double &  res, const char *  data, const size_t  size);
friend std::string  toString(const short  value);
friend std::string  toString(const unsigned short  value);
friend std::string  toString(const int  value);
friend std::string  toString(const unsigned int  value);
friend std::string  toString(const long  value);
friend std::string  toString(const unsigned long  value);
friend std::string  toString(const long long  value);
friend std::string  toString(const unsigned long long  value);
friend std::string  toString(const std::chrono::time_point<std::chrono::system_clock> &  value);
friend std::string  toString(const float  value);
friend std::string  toString(const double  value);
friend std::string  toString(const long double  value);

    constexpr static char cs_MAX2 = '\xFF';
    constexpr static char cs_MAX4 = '\xFE';
    constexpr static char cs_MAX8 = '\xFD';
    constexpr static unsigned char cs_MAX_SIZE = '\xFC';

    constexpr static unsigned char cs_SERZ_T_PINT = 255;
    constexpr static unsigned char cs_SERZ_T_NINT = 254;

public:

    Icode() = delete;
    Icode(const Icode &  other) = delete;
    ~Icode() noexcept;

    Icode &  operator=(const Icode &  other) = delete;

private:

    static std::string  u16tos(const uint16_t  value);
    static std::string  u32tos(const uint32_t  value);
    static std::string  u64tos(const uint64_t  value);
    static uint16_t  stou16(const char *  data) noexcept;
    static uint32_t  stou32(const char *  data) noexcept;
    static uint64_t  stou64(const char *  data) noexcept;
    static void  viewSection(const char *  data, size_t  size, std::vector<std::string_view> &  res) noexcept;
    static std::string  to_s(const unsigned long long &  value);
    static std::string  to_s(const long long &  value);
    static void  pint_to_s(std::string &  data, const unsigned long long &  value);
    static unsigned long long  cpy_int(const char *  data, size_t  size) noexcept;
    static std::string  d_to_s(const char *  data, const size_t  size);
    static void  cpy_df(char *  dest, const size_t  dest_size, const char *  src, const size_t  src_size) noexcept;
};

template <typename T, typename U> inline
bool
fromString(std::pair<T, U> &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T, typename U> inline
bool
fromString(std::pair<T, U> &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T, typename U> inline
bool
fromString(std::pair<T, U> &  res,
           const char *  data,
           const size_t  size)
{
    auto  vi { xu::viewIcode(data, size) };
    if (vi.size() == 2) {
        std::pair<T, U>  pa;
        if (    xu::fromString(pa.first, vi[0]) &&
                xu::fromString(pa.second, vi[1]) ) {
            res = std::move(pa);
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

template <typename T, typename U> inline
bool
fromString(std::map<T, U> &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T, typename U> inline
bool
fromString(std::map<T, U> &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T, typename U> inline
bool
fromString(std::map<T, U> &  res,
           const char *  data,
           const size_t  size)
{
    std::map<T, U>  resTmp;
    auto  vi { xu::viewIcode(data, size) };
    const size_t  viSize = vi.size();
    for (size_t  i = 0; i < viSize; ++i) {
        auto  v2vi = xu::viewIcode(vi[i]);
        std::pair<T, U>  pa;
        if (v2vi.size() == 2) {
            if (    fromString(pa.first, v2vi[0]) &&
                    fromString(pa.second, v2vi[1]) ) {
                resTmp.insert(std::move(pa));
            } else {
                return false;
            }
        }
    }
    res = std::move(resTmp);
    return true;
}

template <typename T> inline
bool
fromString(std::vector<T> &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T> inline
bool
fromString(std::vector<T> &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T> inline
bool
fromString(std::vector<T> &  res,
           const char *  data,
           const size_t  size)
{
    std::vector<T>  resTmp;
    auto  vi { xu::viewIcode(data, size) };
    const size_t  viSize = vi.size();
    for (size_t  i = 0; i < viSize; ++i) {
        T  item;
        if (fromString(item, vi[i])) {
            resTmp.push_back(std::move(item));
        } else {
            return false;
        }
    }
    res = std::move(resTmp);
    return true;
}

template <typename T> inline
bool
fromString(std::list<T> &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T> inline
bool
fromString(std::list<T> &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T> inline
bool
fromString(std::list<T> &  res,
           const char *  data,
           const size_t  size)
{
    std::list<T>  resTmp;
    auto  vi { xu::viewIcode(data, size) };
    const size_t  viSize = vi.size();
    for (size_t  i = 0; i < viSize; ++i) {
        T  item;
        if (fromString(item, vi[i])) {
            resTmp.push_back(std::move(item));
        } else {
            return false;
        }
    }
    res = std::move(resTmp);
    return true;
}

template <typename T> inline
bool
fromString(std::set<T> &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T> inline
bool
fromString(std::set<T> &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T> inline
bool
fromString(std::set<T> &  res,
           const char *  data,
           const size_t  size)
{
    std::set<T>  resTmp;
    auto  vi { xu::viewIcode(data, size) };
    const size_t  viSize = vi.size();
    for (size_t  i = 0; i < viSize; ++i) {
        T  item;
        if (fromString(item, vi[i])) {
            resTmp.insert(std::move(item));
        } else {
            return false;
        }
    }
    res = std::move(resTmp);
    return true;
}

template <typename T> inline
bool
fromString(T &  res,
           const std::string &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T> inline
bool
fromString(T &  res,
           const std::string_view &  value)
{
    return fromString(res, value.data(), value.size());
}

template <typename T> inline
bool
fromString(T &  res,
           const char *  data,
           const size_t  size)
{
    if constexpr (std::is_enum<T>::value) {
        std::underlying_type_t<T>  resTmp;
        if (fromString(resTmp, data, size)) {
            res = static_cast<T>(resTmp);
            return true;
        } else {
            return false;
        }
    } else if constexpr (is_specialization<T, std::tuple>::value) {
        T  resTmp;
        auto  vi { xu::viewIcode(data, size) };
        const size_t  viSize = vi.size();
        constexpr size_t  tpSize = std::tuple_size<T>();
        if (viSize == tpSize) {
            const bool  flag = from_for_each_tp(resTmp, vi,
                    std::make_index_sequence<std::tuple_size_v<T>>());
            if (flag) {
                res = std::move(resTmp);
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return res.fromString(data, size);
    }
}

template <typename T, typename U> inline
std::string
toString(const std::pair<T, U> &  value)
{
    std::string  res;
    xu::append(res, xu::toString(value.first));
    xu::append(res, xu::toString(value.second));
    return res;
}

template <typename T, typename U> inline
std::string
toString(const std::map<T, U> &  value)
{
    std::string  res;
    for (const auto &  item : value) {
        xu::append(res, xu::toString(item));
    }
    return res;
}

template <typename T> inline
std::string
toString(const std::vector<T> &  value)
{
    std::string  res;
    const size_t  size = value.size();
    for (size_t  i = 0; i < size; ++i) {
        xu::append(res, xu::toString(value[i]));
    }
    return res;
}

template <typename T> inline
std::string
toString(const std::list<T> &  value)
{
    std::string  res;
    for (const auto &  item : value) {
        xu::append(res, xu::toString(item));
    }
    return res;
}

template <typename T> inline
std::string
toString(const std::set<T> &  value)
{
    std::string  res;
    for (const auto &  item : value) {
        xu::append(res, xu::toString(item));
    }
    return res;
}

template <typename T> inline
std::string
toString(const T &  value)
{
    std::string  res;

    if constexpr (std::is_enum<T>::value) {
        res = xu::toString(static_cast<typename std::underlying_type<T>::type>(value));
    } else if constexpr (is_specialization<T, std::tuple>::value) {
        for_each_tp(res, value, std::make_index_sequence<std::tuple_size_v<T>>());
    } else {
        res = value.toString();
    }

    return res;
}

template <size_t N> inline constexpr
void
append(std::string &  pkg,
       const char (&r)[N])
{
    static_assert(N != 0, "Icode append error: 0 length arrays.");
    if (*(r + N - 1) == '\0') {
        append(pkg, r, N - 1);
    } else {
        append(pkg, r, N);
    }
}

template <typename Tuple, size_t... Is> inline constexpr
bool
from_for_each_tp(Tuple &  t,
                 const std::vector<std::string_view> &  vi,
                 std::index_sequence<Is...>)
{
    return (xu::fromString(std::get<Is>(t), vi[Is]) && ...);
}

template <typename Tuple, size_t... Is> inline constexpr
void
for_each_tp(std::string &  res,
            const Tuple &  t,
            std::index_sequence<Is...>)
{
    (xu::append(res, xu::toString(std::get<Is>(t))), ...);
}

}

#endif
