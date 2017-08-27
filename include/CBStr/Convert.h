#pragma once

#include "Defines.h"

namespace cb {
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

  extern utf8string toUtf8(string const& text);

  extern string fromUtf8(utf8string const& text);

  extern size_t utf8len(utf8string const& text);


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
    auto list = strvector();
    return detail::format(fmt, list, args...);
  }
}
