#include "stdafx.h"
#include <CBStr/StringEx.h>
#include "utf8.h"

#include <sstream>

namespace cb {
  using namespace std::string_literals;

  auto const STR_BOOL_TRUE = L"true"s;
  auto const STR_BOOL_FALSE = L"false"s;
  
  auto const STR_BOOL_TRUE_CAP = L"True"s;
  auto const STR_BOOL_FALSE_CAP = L"False"s;

  string toStr(string const& val) {
    return val;
  }

  string toStr(bool const & val) {
    return val ? STR_BOOL_TRUE : STR_BOOL_FALSE;
  }

  bool fromStr(string const& text, string& outVal) {
    outVal = text;
    return true;
  }

  bool fromStr(string const & text, bool & outVal) {
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


  charvector toUtf8(string const & text, bool const addZero) {
    auto result = charvector();
    utf8::utf16to8(text.begin(), text.end(), std::back_inserter(result));
    if(addZero) {
      result.push_back(0);
    }
    return result;
  }

  string fromUtf8(charvector const & text) {
    auto result = string();
    utf8::utf8to16(text.begin(), text.end(), std::back_inserter(result));
    if(!result.empty() && *result.rbegin() == 0) {
      result.pop_back();
    }
    return result;
  }

  size_t utf8len(charvector const & text) {
    return utf8::distance(text.begin(), text.end());
  }

  const char * utf8ptr(charvector const & text) {
    if(text.empty()) {
      return nullptr;
    }
    return text.data();
  }

  charvector utf8vec(const char * szText) {
    auto len = std::strlen(szText);
    return charvector(szText, szText + len);
  }
}
