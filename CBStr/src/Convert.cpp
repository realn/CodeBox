#include "stdafx.h"

#include "../StringEx.h"

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
  return ss.good();
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
}
