#include "stdafx.h"
#include "../StringEx.h"
#include "utf8.h"

#include <sstream>

namespace cb {
  using namespace std::string_literals;

  const auto STR_BOOL_TRUE = L"true"s;
  const auto STR_BOOL_FALSE = L"false"s;
  
  const auto STR_BOOL_TRUE_CAP = L"True"s;
  const auto STR_BOOL_FALSE_CAP = L"False"s;

  template<>
  string toStr<string>(const string& val) {
    return val;
  }

  template<>
  string toStr<bool>(const bool & val) {
    return val ? STR_BOOL_TRUE : STR_BOOL_FALSE;
  }

  template<>
  bool fromStr<string>(const string& text, string& outVal) {
    outVal = text;
    return true;
  }

  template<>
  bool fromStr<bool>(const string & text, bool & outVal) {
    if(text == STR_BOOL_TRUE || text == STR_BOOL_TRUE_CAP) {
      outVal = true;
      return true;
    }
    if(text == STR_BOOL_FALSE || text == STR_BOOL_FALSE_CAP) {
      outVal = false;
      return true;
    }
    return false;
  }


  charvector toUtf8(const string & text) {
    auto result = charvector();
    utf8::utf16to8(text.begin(), text.end(), std::back_inserter(result));
    return result;
  }

  string fromUtf8(const charvector & text) {
    auto result = string();
    utf8::utf8to16(text.begin(), text.end(), std::back_inserter(result));
    return result;
  }

  size_t utf8len(const charvector & text) {
    return utf8::distance(text.begin(), text.end());
  }

  const char * utf8ptr(const charvector & text) {
    if(text.empty()) {
      return nullptr;
    }
    return &text[0];
  }

  charvector utf8vec(const char * szText) {
    auto len = 0u;
    while(szText[len] != 0) len++;
    return charvector(szText, szText + len);
  }
}
