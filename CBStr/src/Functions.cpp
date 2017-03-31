#include "stdafx.h"

#include "../StringEx.h"

namespace cb {

  const size_t  count(const string& text, const string& what) {
    size_t result = 0;
    size_t pos = text.find(what, 0);
    while(pos != string::npos) {
      result++;
      pos = text.find(what, pos + 1);
    }
    return result;
  }

  const string substrpos(const string& text, const size_t pos, const size_t endpos) {
    if(pos == string::npos || pos >= text.length()) {
      return string();
    }
    if(endpos == string::npos) {
      return text.substr(pos);
    }
    return text.substr(pos, endpos - pos);
  }

  const bool subcmp(const string& text, const string& what, const size_t pos) {
    return text.compare(pos, what.length(), what) == 0;
  }

  const bool subcmp(const string& text, const strvector& list, const size_t pos) {
    for(strvector::const_iterator it = list.begin(); it != list.end(); it++) {
      if(subcmp(text, *it, pos)) {
        return true;
      }
    }
    return false;
  }

  const bool rsubcmp(const string & text, const string & what, const size_t roffset) {
    if(roffset + 1 > text.length()) {
      return false;
    }
    return subcmp(text, what, text.length() - roffset - 1);
  }

  const bool subrcmp(const string & text, const string & what, const size_t offset) {
    if(offset < what.length())
      return false;
    return text.compare(offset - what.length(), what.length(), what) == 0;
  }

  const string replace(const string& text, const string& what, const string& with) {
    if(what.empty() || text.empty()) {
      return text;
    }

    string result;
    size_t pos = 0;
    while(pos != string::npos) {
      size_t next_pos = text.find(what, pos);
      result += substrpos(text, pos, next_pos);

      if(next_pos != string::npos) {
        result += with;
        next_pos += what.length();
      }
      pos = next_pos;
    }

    return result;
  }

  const string replace(const string & text, const strmap & list, const bool flip) {
    string result = text;
    for(strmap::const_iterator it = list.begin(); it != list.end(); it++) {
      if(!flip) {
        result = replace(result, it->first, it->second);
      }
      else {
        result = replace(result, it->second, it->first);
      }
    }
    return result;
  }

  const string join(const strvector& list, const string& glue) {
    string result;
    strvector::const_iterator it = list.begin(); 

    while(it != list.end()) {
      result += *it;

      it++;
      if(it != list.end()) {
        result += glue;
      }
    }

    return result;
  }

  const strvector split(const string& text, const string& knife, const bool skipEmpty) {
    strvector result;

    if(knife.empty()) {
      for(size_t i = 0; i < text.length(); i++) {
        result.push_back(text.substr(i, 1));
      }
      return result;
    }

    size_t pos = 0;
    while(pos != string::npos) {
      size_t next_pos = text.find(knife, pos);
      string item = substrpos(text, pos, next_pos);
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

  const string varReplace(const string& format, const strvector& list) {
    if(format.empty()) {
      return string();
    }
    if(list.empty()) {
      return format;
    }

    string result = format;
    for(size_t i = 0; i < list.size(); i++) {
      string var = L"{" + toStr(i) + L"}";
      result = replace(result, var, list[i]);
    }

    return result;
  }

  const size_t strlastpos(const string & text, const size_t roffset) {
    if(text.empty()) {
      return string::npos;
    }
    if(roffset + 1 > text.length()) {

    }
    return text.length() - 1 - roffset;
  }
  const string repeat(const string & text, const size_t times) {
    if(times == 0)
      return string();
    if(times == 1)
      return text;

    string result;
    for(size_t i = 0; i < times; i++) {
      result += text;
    }

    return result;
  }
}
