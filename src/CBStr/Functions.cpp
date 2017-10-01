#include "stdafx.h"
#include <CBStr/Functions.h>

namespace cb {
  // string checking

  size_t  count(string const & text, string const & what) {
    auto result = 0u;
    auto pos = text.find(what, 0);
    while(pos != string::npos) {
      result++;
      pos = text.find(what, pos + what.length());
    }
    return result;
  }

  bool subcmp(string const& text, string const& what, size_t const pos) {
    return text.compare(pos, what.length(), what) == 0;
  }

  bool subcmp(string const& text, strvector const& list, size_t const pos) {
    for(auto& item : list) {
      if(subcmp(text, item, pos)) {
        return true;
      }
    }
    return false;
  }

  bool rsubcmp(string const & text, string const & what, size_t const roffset) {
    if(roffset > text.length()) {
      return false;
    }
    return subcmp(text, what, text.length() - roffset);
  }

  bool subrcmp(string const & text, string const & what, size_t const offset) {
    if(offset < what.length())
      return false;
    return text.compare(offset - what.length(), what.length(), what) == 0;
  }

  strvector::const_iterator subfind(string const & text, strvector const & list, size_t const pos) {
    for(auto it = list.begin(); it != list.end(); it++) {
      if(subcmp(text, *it, pos)) {
        return it;
      }
    }
    return list.end();
  }

  // string manipulation

  string substrpos(string const& text, size_t const pos, size_t const endpos) {
    if(pos == string::npos || pos >= text.length()) {
      return string();
    }
    if(endpos == string::npos) {
      return text.substr(pos);
    }
    return text.substr(pos, endpos - pos);
  }

  string replace(string const& text, string const& what, string const& with) {
    if(what.empty() || text.empty()) {
      return text;
    }
    auto result = string();
    auto pos = size_t(0u);
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

  string replace(string const & text, const strmap & list) {
    auto result = text;
    for(auto& item : list) {
      result = replace(result, item.first, item.second);
    }
    return result;
  }

  string replace_by_char(string const & text, string const & what, string const & with) {
    auto result = string();
    auto i = size_t(0); 
    while(i < text.length()) {
      if(subcmp(text, what, i)) {
        result += with;
        i += what.length();
      }
      else {
        result += text[i];
        i++;
      }
    }
    return result;
  }

  string replace_by_char(string const & text, strmap const & list) {
    auto result = string();
    auto keys = mapkeys(list);
    auto i = size_t(0);
    while(i < text.length()) {
      auto it = subfind(text, keys, i);
      if(it != keys.end()) {
        auto mapit = list.find(*it);

        result += mapit->second;
        i += mapit->first.length();
      }
      else {
        result += text[i];
        i++;
      }
    }
    return result;
  }

  string join(strvector const& list, string const& glue) {
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

  strvector split(string const& text, string const& knife, bool const skipEmpty) {
    auto result = strvector();
    if(knife.empty()) {
      for(auto& item : text) {
        result.push_back(string(1, item));
      }
      return result;
    }

    auto pos = size_t(0u);
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

  string varReplace(string const& format, strvector const& list) {
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

  size_t strposrev(string const & text, size_t const roffset) {
    if(text.empty() || roffset + 1 > text.length()) {
      return string::npos;
    }
    return text.length() - (1 + roffset);
  }

  bool ends_with(string const & text, string const & with) {
    if(with.length() > text.length()) {
      return false;
    }
    return text.compare(text.length() - with.length(), with.length(), with) == 0;
  }

  string repeat(string const & text, size_t const times) {
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
