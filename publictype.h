#pragma once

#ifndef XU_PUBLICTYPE_H_
#define XU_PUBLICTYPE_H_

#include <string>
#include <string_view>
#include <vector>
#include <utility>
#include <memory>

namespace xu {

enum class StyleType {
    dark = 0,
    light = 1,
    defaultStyle = 99
};

StyleType  getGuiStyle();
void  setGuiStyle(const StyleType  value);
std::string  getDefTab();
void  setDefTab(std::string const &  value);
std::string  getOther();
void  setOther(std::string const &  value);
std::string  getSig();
void  setSig(std::string const &  value);
std::string  getRhs();
void  setRhs(std::string const &  value);
std::string  getLhs();
void  setLhs(std::string const &  value);

static StyleType &  primGuiStyle();
static std::string &  primDefTab();
static std::string &  primOther();
static std::string &  primSig();
static std::string &  primRhs();
static std::string &  primLhs();

}

#endif
