#ifndef __CB_STRING_EX_H__
#define __CB_STRING_EX_H__

#include "Defines.h"

#include <string>
#include <sstream>
#include <vector>

namespace cb {
  // string checking
  extern size_t count(const string& text, const string& what);

  extern bool subcmp(const string& text, const string& what, const size_t pos = 0);

  extern bool subcmp(const string& text, const strvector& list, const size_t pos = 0);

  extern bool rsubcmp(const string& text, const string& what, const size_t roffset = 0);

  extern bool subrcmp(const string& text, const string& what, const size_t offset = 0);

  extern size_t strposrev(const string& text, const size_t roffset = 0);


  // string manipulation

  extern string substrpos(const string& text, const size_t pos = 0, const size_t endpos = string::npos);

  extern string replace(const string& text, const string& what, const string& with);

  extern string replace(const string& text, const strmap& list, const bool flip = false);

  extern string join(const strvector& list, const string& glue = string());

  extern strvector split(const string& text, const string& knife = string(), const bool skipEmpty = false);

  extern string varReplace(const string& format, const strvector& list);

  extern string repeat(const string& text, const size_t times);


  // string convertion

  template<>
  extern string toStr<string>(const string& val);

  template<>
  extern string toStr<bool>(const bool& val);

  template<>
  extern bool fromStr<string>(const string& text, string& outVal);

  template<>
  extern bool fromStr<bool>(const string& text, bool& outVal);

  extern charvector toUtf8(const string& text);

  extern string fromUtf8(const charvector& text);

  extern size_t utf8len(const charvector& text);

  extern const char* utf8ptr(const charvector& text);

  extern charvector utf8vec(const char* szText);


  // string formating

  namespace detail {
    template<typename _Type, typename ..._Args>
    string format(const string& fmt, strvector& list, const _Type& arg0, const _Args... args) {
      list.push_back(toStr(arg0));
      return format(fmt, list, args...);
    }

    template<typename _Type>
    string format(const string& fmt, strvector& list, const _Type& arg0) {
      list.push_back(toStr(arg0));
      return varReplace(fmt, list);
    }
  }

  template<typename ..._Args>
  string format(const string& fmt, const _Args... args) {
    return detail::format(fmt, strvector(), args...);
  }
}

#endif // !__CB_STRING_EX_H__
