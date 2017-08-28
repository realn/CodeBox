#ifndef __CB_STRING_DEFINES_H__
#define __CB_STRING_DEFINES_H__

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

namespace cb {
  using s8 = signed char;
  using s16 = signed short;
  using s32 = signed int;
  using s64 = signed __int64;

  using u8 = unsigned char;
  using u16 = unsigned short;
  using u32 = unsigned int;
  using u64 = unsigned __int64;

  using string = std::wstring;

  using strvector = std::vector<string>;
  using stringstream = std::wstringstream;
  using strmap = std::map<string, string>;
  using utf8string = std::string;

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

  template<typename _LambdaT>
  class OnScopeExit {
  private:
    _LambdaT mLambda;
  public:
    OnScopeExit(_LambdaT onScope) : mLambda(onScope) {}
    ~OnScopeExit() { mLambda(); }
  };

  template<typename _LambdaT>
  OnScopeExit<_LambdaT> finalize(_LambdaT onScopeExit) {
    return OnScopeExit<_LambdaT>(onScopeExit);
  }

  template<typename _KeyType, typename _ValueType>
  std::vector<_KeyType> mapkeys(std::map<_KeyType, _ValueType> const& obj) {
    auto result = std::vector<_KeyType>();
    for(auto& item : obj) {
      result.push_back(item.first);
    }
    return result;
  }

  template<typename _KeyType, typename _ValueType>
  std::vector<_ValueType> mapvalues(std::map<_KeyType, _ValueType> const& obj) {
    auto result = std::vector<_ValueType>();
    for(auto& item : obj) {
      result.push_back(item.second);
    }
    return result;
  }

  template<typename _KeyType, typename _ValueType>
  std::map<_ValueType, _KeyType> mapflip(std::map<_KeyType, _ValueType> const& obj) {
    auto result = std::map<_ValueType, _KeyType>();
    for(auto& item : obj) {
      result.insert({item.second, item.first});
    }
    return result;
  }
}

#endif // !__CB_STRING_DEFINES_H__
