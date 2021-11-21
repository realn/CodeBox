#pragma once

#include "Defines.h"

namespace cb {
  // string convertion

  template<typename _Type>
  string toStr(const _Type& value) {
    auto ss = stringstream();
    ss << value;
    return ss.str();
  }

  template<typename _Type>
  bool fromStr(const string& text, _Type& outValue) {
    auto ss = stringstream();
    ss << text;
    ss >> std::noskipws >> outValue;
    return !ss.fail();
  }

  template<typename _Type, typename _TypeMapT = std::map<_Type, string>>
  string templToStr(const _TypeMapT& typeMap, const _Type& value, const string& defReturn) {
    auto it = typeMap.find(value);
    if (it != typeMap.end()) {
      return it->second;
    }
    return defReturn;
  }

  template<typename _Type, typename _TypeMapT = std::map<_Type, string>>
  bool templFromStr(const _TypeMapT& typeMap, const string& text, _Type& outValue) {
    for (auto& item : typeMap) {
      if (item.second == text) {
        outValue = item.first;
        return true;
      }
    }
    return false;
  }

  string toStr(string const& val);

  string toStr(bool const& val);

  bool fromStr(string const& text, string& outVal);

  bool fromStr(string const& text, bool& outVal);

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

  utf8string toUtf8(string const& text);

  string fromUtf8(utf8string const& text);

  size_t utf8len(utf8string const& text);

  string varReplace(string const& format, const strvector& list);

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
