#include "stdafx.h"

#include "../StringEx.h"
#include "utf8.h"

#include <sstream>

template <typename _T>
const std::wstring templToString(const _T val) {
  std::wstringstream ss;
  ss << val;
  return ss.str();
}

template<typename _T>
const bool templFromString(const std::wstring& text, _T& outVal) {
  std::wstringstream ss;
  ss << text;
  ss >> outVal;
  return !ss.fail();
}

namespace cb {
  const string toStr(const signed char val) {
    return templToString(val);
  }

  const string toStr(const unsigned char val) {
    return templToString(val);
  }

  const string toStr(const signed short val) {
    return templToString(val);
  }

  const string toStr(const unsigned short val) {
    return templToString(val);
  }

  const string toStr(const signed int val) {
    return templToString(val);
  }

  const string toStr(const unsigned int val) {
    return templToString(val);
  }

  const string toStr(const signed __int64 val) {
    return templToString(val);
  }

  const string toStr(const unsigned __int64 val) {
    return templToString(val);
  }

  const string toStr(const float val) {
    return templToString(val);
  }

  const string toStr(const double val) {
    return templToString(val);
  }

  const string toStr(const string& val) {
    return val;
  }

  const string toStr(const bool & val) {
    return val ? L"true" : L"false";
  }



  const bool fromStr(const string& text, signed char& outVal) {
    signed int val;
    if(templFromString(text, val)) {
      outVal = val;
    }
    return false;
  }

  const bool fromStr(const string& text, unsigned char& outVal) {
    unsigned int val;
    if(templFromString(text, val)) {
      outVal = val;
    }
    return false;
  }

  const bool fromStr(const string& text, signed short& outVal) {
    return templFromString(text, outVal);
  }

  const bool fromStr(const string& text, unsigned short& outVal) {
    return templFromString(text, outVal);
  }

  const bool fromStr(const string& text, signed int& outVal) {
    return templFromString(text, outVal);
  }

  const bool fromStr(const string& text, unsigned int& outVal) {
    return templFromString(text, outVal);
  }

  const bool fromStr(const string& text, signed __int64& outVal) {
    return templFromString(text, outVal);
  }

  const bool fromStr(const string& text, unsigned __int64& outVal) {
    return templFromString(text, outVal);
  }

  const bool fromStr(const string& text, float& outVal) {
    return templFromString(text, outVal);
  }

  const bool fromStr(const string& text, double& outVal) {
    return templFromString(text, outVal);
  }

  const bool fromStr(const string& text, string& outVal) {
    outVal = text;
    return true;
  }

  const bool fromStr(const string & text, bool & outVal) {
    if(text == L"True" || text == L"true") {
      outVal = true;
      return true;
    }
    if(text == L"False" || text == L"false") {
      outVal = false;
      return true;
    }
    return false;
  }


  const charvector toUtf8(const string & text) {
    charvector result;
    utf8::utf16to8(text.begin(), text.end(), std::back_inserter(result));
    return result;
  }

  const string fromUtf8(const charvector & text) {
    string result;
    utf8::utf8to16(text.begin(), text.end(), std::back_inserter(result));
    return result;
  }

  const size_t utf8len(const charvector & text) {
    return utf8::distance(text.begin(), text.end());
  }

  const char * utf8ptr(const charvector & text) {
    if(text.empty()) {
      return nullptr;
    }
    return &text[0];
  }

  const charvector utf8vec(const char * szText) {
    charvector result;
    size_t i = 0;
    while(szText[i] != 0) {
      result.push_back(szText[i]);
      i++;
    }
    return result;
  }
}
