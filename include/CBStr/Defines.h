#pragma once

#include <CBCore/Defines.h>

namespace cb {
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
    if(it != typeMap.end()) {
      return it->second;
    }
    return defReturn;
  }

  template<typename _Type, typename _TypeMapT = std::map<_Type, string>>
  bool templFromStr(const _TypeMapT& typeMap, const string& text, _Type& outValue) {
    for(auto& item : typeMap) {
      if(it.second == text) {
        outValue = it.first;
        return true;
      }
    }
    return false;
  }
}
