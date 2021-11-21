#include "stdafx.h"
#include "utf8.h"

#include <sstream>

#include <CBCore/StringConvert.h>
#include <CBCore/StringFunctions.h>

namespace cb {
  using namespace std::string_literals;

  auto const STR_BOOL_TRUE = L"true"s;
  auto const STR_BOOL_FALSE = L"false"s;

  auto const STR_BOOL_TRUE_CAP = L"True"s;
  auto const STR_BOOL_FALSE_CAP = L"False"s;

  auto const STR_BOOL_TRUE_HIGH = L"TRUE";
  auto const STR_BOOL_FALSE_HIGH = L"FALSE";

  auto const STR_FORMAT_BRACE_LEFT = L"{"s;
  auto const STR_FORMAT_BRACE_RIGHT = L"}"s;

  string toStr(string const& val) {
    return val;
  }

  string toStr(bool const& val) {
    return val ? STR_BOOL_TRUE : STR_BOOL_FALSE;
  }

  bool fromStr(string const& text, string& outVal) {
    outVal = text;
    return true;
  }

  bool fromStr(string const& text, bool& outVal) {
    if (text == STR_BOOL_TRUE || text == STR_BOOL_TRUE_CAP || text == STR_BOOL_TRUE_HIGH) {
      outVal = true;
      return true;
    }
    if (text == STR_BOOL_FALSE || text == STR_BOOL_FALSE_CAP || text == STR_BOOL_FALSE_HIGH) {
      outVal = false;
      return true;
    }
    return false;
  }


  utf8string toUtf8(string const& text) {
    auto result = utf8string();
    utf8::utf16to8(text.begin(), text.end(), std::back_inserter(result));
    return result;
  }

  string fromUtf8(utf8string const& text) {
    auto result = string();
    utf8::utf8to16(text.begin(), text.end(), std::back_inserter(result));
    return result;
  }

  size_t utf8len(utf8string const& text) {
    return utf8::distance(text.begin(), text.end());
  }

  string varReplace(string const& format, strvector const& list) {
    if (format.empty()) {
      return string();
    }
    if (list.empty()) {
      return format;
    }

    auto result = format;
    for (auto i = 0u; i < list.size(); i++) {
      auto var = STR_FORMAT_BRACE_LEFT + toStr(i) + STR_FORMAT_BRACE_RIGHT;
      result = replace(result, var, list[i]);
    }

    return result;
  }
}
