#pragma once

#ifndef XU_FMT_H_
#define XU_FMT_H_

#include <string>
#include <string_view>
#include <vector>
#include <initializer_list>
#include <map>

namespace xu {

std::string  trim(const std::string &  value, const std::string &  ch = std::string(" "));
std::string  trim(const char *  data, const size_t  size, const std::string &  ch = std::string(" "));
std::string  toHex(const char *  data, const size_t  size);
bool  checkReg(const std::string &  value);
bool  checkReg(const char *  data, const size_t  size);
std::vector<std::string>  split(const std::string &  value, const std::string &  delim);
std::vector<std::string>  split(const char *  data, const size_t  size, const std::string &  delim);
std::vector<std::string_view>  splitLine(const std::string &  value);
std::vector<std::string_view>  splitLine(const char *  data, const size_t  size);
bool  isPrmType(const std::string &  typestr, std::string *  label = nullptr);
void  procCode(std::string &  sourceCode);
int  isalnumS(int  ch);
int  isalphaS(int  ch);
int  islowerS(int  ch);
int  isupperS(int  ch);
int  isdigitS(int  ch);
int  isxdigitS(int  ch);
int  iscntrlS(int  ch);
int  isgraphS(int  ch);
int  isspaceS(int  ch);
int  isblankS(int  ch);
int  isprintS(int  ch);
int  ispunctS(int  ch);
int  tolowerS(int  ch);
int  toupperS(int  ch);

template <typename T>
bool  moveVec_0(std::vector<T> &  vec, size_t &  from, size_t &  to);
template <typename T>
bool  moveVec_1(std::vector<T> &  vec, size_t &  from, size_t &  to);

template <typename T> inline
bool
moveVec_0(std::vector<T> &  vec,
          size_t &  from,
          size_t &  to)
{
    size_t const  size = vec.size();
    if (size < 2)  return false;

    if (to >= size)  to = size - 1;
    if ( from >= size || from == to) {
        return false;
    }

    auto  fnv = vec[from];
    vec.erase(vec.begin() + from);
    vec.insert(vec.begin() + to, std::move(fnv));

    return true;
}

template <typename T> inline
bool
moveVec_1(std::vector<T> &  vec,
          size_t &  from,
          size_t &  to)
{
    size_t const  size = vec.size();
    if (size < 2)  return false;

    if (to > size)  to = size;
    if (to == 0)  to = 1;
    if (from == 0 || from > size || from == to) {
        return false;
    }

    from--;
    to--;
    auto  fnv = vec[from];
    vec.erase(vec.begin() + from);
    vec.insert(vec.begin() + to, std::move(fnv));

    return true;
}

}

#endif
