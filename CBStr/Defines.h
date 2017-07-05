#ifndef __CB_STRING_DEFINES_H__
#define __CB_STRING_DEFINES_H__

#include <string>
#include <sstream>
#include <vector>
#include <map>

namespace cb {
  typedef std::wstring string;
  typedef std::vector<string> strvector;
  typedef std::wstringstream stringstream;
  typedef std::map<string, string> strmap;
  typedef std::vector<char> charvector;

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
    ss >> outValue;
    return !ss.fail();
  }

  template<typename _Type, typename _TypeMapT = std::map<_Type, string>>
  const string templToStr(const _TypeMapT& typeMap,
                          const _Type& value,
                          const string& defReturn) {
    typename _TypeMapT::const_iterator it = typeMap.find(value);
    if(it != typeMap.end()) {
      return it->second;
    }
    return defReturn;
  }

  template<typename _Type, typename _TypeMapT = std::map<_Type, string>>
  const bool templFromStr(const _TypeMapT& typeMap,
                          const string& text,
                          _Type& outValue) {
    for(_TypeMapT::const_iterator it = typeMap.begin(); it != typeMap.end(); it++) {
      if(it->second == text) {
        outValue = it->first;
        return true;
      }
    }
    return false;
  }
}

#endif // !__CB_STRING_DEFINES_H__
