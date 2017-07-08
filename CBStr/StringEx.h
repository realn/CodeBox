#ifndef __CB_STRING_EX_H__
#define __CB_STRING_EX_H__

#include "Defines.h"

#include <string>
#include <sstream>
#include <vector>

namespace cb {
  // string checking
  extern size_t count(string const & text, string const & what);

  extern bool subcmp(string const& text, string const& what, size_t const pos = 0);

  extern bool subcmp(string const& text, const strvector& list, size_t const pos = 0);

  extern bool rsubcmp(string const& text, string const& what, size_t const roffset = 0);

  extern bool subrcmp(string const& text, string const& what, size_t const offset = 0);

  extern size_t strposrev(string const& text, size_t const roffset = 0);


  // string manipulation

  extern string substrpos(string const& text, size_t const pos = 0, size_t const endpos = string::npos);

  extern string replace(string const& text, string const& what, string const& with);

  extern string replace(string const& text, const strmap& list, bool const flip = false);

  extern string join(const strvector& list, string const& glue = string());

  extern strvector split(string const& text, string const& knife = string(), bool const skipEmpty = false);

  extern string varReplace(string const& format, const strvector& list);

  extern string repeat(string const& text, size_t const times);


  // string convertion

  extern string toStr(string const& val);

  extern string toStr(bool const& val);

  extern bool fromStr(string const& text, string& outVal);

  extern bool fromStr(string const& text, bool& outVal);

  template<>
  inline string toStr<string>(string const& val) {
    return toStr(val);
  }

  template<>
  inline string toStr<bool>(bool const& val) {
    return toStr(val);
  }

  template<>
  inline bool fromStr<string>(string const& text, string& outVal) {
    return fromStr(text, outVal);
  }

  template<>
  inline bool fromStr<bool>(string const& text, bool& outVal) {
    return fromStr(text, outVal);
  }

  extern charvector toUtf8(string const& text);

  extern string fromUtf8(charvector const& text);

  extern size_t utf8len(charvector const& text);

  extern const char* utf8ptr(charvector const& text);

  extern charvector utf8vec(const char* szText);


  // string formating

  namespace detail {
    template<typename _Type, typename ..._Args>
    string format(string const& fmt, strvector& list, _Type const& arg0, _Args... args) {
      list.push_back(toStr(arg0));
      return format(fmt, list, args...);
    }

    template<typename _Type>
    string format(string const& fmt, strvector& list, _Type const& arg0) {
      list.push_back(toStr(arg0));
      return varReplace(fmt, list);
    }
  }

  template<typename ..._Args>
  string format(string const& fmt, _Args... args) {
    return detail::format(fmt, strvector(), args...);
  }
}

#endif // !__CB_STRING_EX_H__
