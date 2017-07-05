#include "stdafx.h"
#include "../StringEx.h"

namespace cb {

  size_t  count(const string& text, const string& what) {
    auto result = 0u;
    auto pos = text.find(what, 0);
    while(pos != string::npos) {
      pos = text.find(what, pos + 1);
      result++;
    }
    return result;
  }

  string substrpos(const string& text, const size_t pos, const size_t endpos) {
    if(pos == string::npos || pos >= text.length()) {
      return string();
    }
    if(endpos == string::npos) {
      return text.substr(pos);
    }
    return text.substr(pos, endpos - pos);
  }

  bool subcmp(const string& text, const string& what, const size_t pos) {
    return text.compare(pos, what.length(), what) == 0;
  }

  bool subcmp(const string& text, const strvector& list, const size_t pos) {
    for(auto& item : list) {
      if(subcmp(text, item, pos)) {
        return true;
      }
    }
    return false;
  }

  bool rsubcmp(const string & text, const string & what, const size_t roffset) {
    if(roffset + 1 > text.length()) {
      return false;
    }
    return subcmp(text, what, text.length() - roffset - 1);
  }

  bool subrcmp(const string & text, const string & what, const size_t offset) {
    if(offset < what.length())
      return false;
    return text.compare(offset - what.length(), what.length(), what) == 0;
  }

  string replace(const string& text, const string& what, const string& with) {
    if(what.empty() || text.empty()) {
      return text;
    }

    auto result = string();
    auto pos = 0u;
    while(pos != string::npos) {
      auto next_pos = text.find(what, pos);
      result += substrpos(text, pos, next_pos);

      if(next_pos != string::npos) {
        result += with;
        next_pos += what.length();
      }
      pos = next_pos;
    }
    return result;
  }

  string replace(const string & text, const strmap & list, const bool flip) {
    auto result = text;
    for(auto& item : list) {
      if(!flip) {
        result = replace(result, item.first, item.second);
      }
      else {
        result = replace(result, item.second, item.first);
      }
    }
    return result;
  }

  string join(const strvector& list, const string& glue) {
    auto result = string();
    auto it = list.begin(); 

    while(it != list.end()) {
      result += *it;

      it++;
      if(it != list.end()) {
        result += glue;
      }
    }

    return result;
  }

  strvector split(const string& text, const string& knife, const bool skipEmpty) {
    auto result = strvector();
    if(knife.empty()) {
      for(auto& item : text) {
        result.push_back(string(1, item));
      }
      return result;
    }

    auto pos = 0u;
    while(pos != string::npos) {
      auto next_pos = text.find(knife, pos);
      auto item = substrpos(text, pos, next_pos);
      if(!(item.empty() && skipEmpty)) {
        result.push_back(item);
      }
      if(next_pos != string::npos) {
        next_pos += knife.length();
      }
      pos = next_pos;
    }
    return result;
  }

  string varReplace(const string& format, const strvector& list) {
    if(format.empty()) {
      return string();
    }
    if(list.empty()) {
      return format;
    }

    auto result = format;
    for(auto i = 0u; i < list.size(); i++) {
      auto var = L"{" + toStr(i) + L"}";
      result = replace(result, var, list[i]);
    }

    return result;
  }

  size_t strlastpos(const string & text, const size_t roffset) {
    if(text.empty()) {
      return string::npos;
    }
    if(roffset + 1 > text.length()) {

    }
    return text.length() - 1 - roffset;
  }

  string repeat(const string & text, const size_t times) {
    if(times == 0)
      return string();
    if(times == 1)
      return text;

    auto result = string();
    for(auto i = 0u; i < times; i++) {
      result += text;
    }
    return result;
  }
}
