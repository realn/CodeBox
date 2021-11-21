#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
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
  using utf8string = std::string;

  using strvector = std::vector<string>;
  using strmap = std::map<string, string>;

  using byte = unsigned char;
  using bytevector = std::vector<byte>;

  using ostream = std::wostream;
  using istream = std::wistream;

  using fstream = std::basic_fstream<byte>;
  using ifstream = std::basic_ifstream<byte>;
  using ofstream = std::basic_ofstream<byte>;
  using stringstream = std::wstringstream;

  template<typename _KeyType, typename _ValueType>
  std::vector<_ValueType> mapvalues(std::map<_KeyType, _ValueType> const& obj) {
    auto result = std::vector<_ValueType>();
    for (auto& item : obj) {
      result.push_back(item.second);
    }
    return result;
  }

  template<typename _KeyType, typename _ValueType>
  std::vector<_KeyType> mapkeys(std::map<_KeyType, _ValueType> const& obj) {
    auto result = std::vector<_KeyType>();
    for (auto& item : obj) {
      result.push_back(item.first);
    }
    return result;
  }

  template<typename _KeyType, typename _ValueType>
  std::map<_ValueType, _KeyType> mapflip(std::map<_KeyType, _ValueType> const& obj) {
    auto result = std::map<_ValueType, _KeyType>();
    for (auto& item : obj) {
      result.insert({ item.second, item.first });
    }
    return result;
  }
}
