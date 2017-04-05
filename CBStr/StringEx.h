#ifndef __CB_STRING_EX_H__
#define __CB_STRING_EX_H__

#include "Defines.h"

#include <string>
#include <vector>

namespace cb {
  extern const size_t count(const string& text, const string& what);

  extern const string substrpos(const string& text, const size_t pos = 0, const size_t endpos = string::npos);

  extern const bool subcmp(const string& text, const string& what, const size_t pos = 0);

  extern const bool subcmp(const string& text, const strvector& list, const size_t pos = 0);

  extern const bool rsubcmp(const string& text, const string& what, const size_t roffset = 0);

  extern const bool subrcmp(const string& text, const string& what, const size_t offset = 0);

  extern const string replace(const string& text, const string& what, const string& with);

  extern const string replace(const string& text, const strmap& list, const bool flip = false);

  extern const string join(const strvector& list, const string& glue = string());

  extern const strvector split(const string& text, const string& knife = string(), const bool skipEmpty = false);

  extern const string varReplace(const string& format, const strvector& list);

  extern const size_t strlastpos(const string& text, const size_t roffset = 0);

  extern const string repeat(const string& text, const size_t times);


  extern const string toStr(const signed char val);

  extern const string toStr(const unsigned char val);

  extern const string toStr(const signed short val);

  extern const string toStr(const unsigned short val);

  extern const string toStr(const signed int val);

  extern const string toStr(const unsigned int val);

  extern const string toStr(const signed __int64 val);

  extern const string toStr(const unsigned __int64 val);

  extern const string toStr(const float val);

  extern const string toStr(const double val);

  extern const string toStr(const string& val);

  extern const string toStr(const bool& val);


  extern const bool fromStr(const string& text, signed char& outVal);

  extern const bool fromStr(const string& text, unsigned char& outVal);

  extern const bool fromStr(const string& text, signed short& outVal);

  extern const bool fromStr(const string& text, unsigned short& outVal);

  extern const bool fromStr(const string& text, signed int& outVal);

  extern const bool fromStr(const string& text, unsigned int& outVal);

  extern const bool fromStr(const string& text, signed __int64& outVal);

  extern const bool fromStr(const string& text, unsigned __int64& outVal);

  extern const bool fromStr(const string& text, float& outVal);

  extern const bool fromStr(const string& text, double& outVal);

  extern const bool fromStr(const string& text, string& outVal);

  extern const bool fromStr(const string& text, bool& outVal);


  extern const charvector toUtf8(const string& text);

  extern const string fromUtf8(const charvector& text);

  extern const size_t utf8len(const charvector& text);

  extern const char* utf8ptr(const charvector& text);

  template<typename _T0>
  const string format(const string& fmt, const _T0& arg0) {
    strvector list = {toStr(arg0)};
    return varReplace(fmt, list);
  }

  template<typename _T0, typename _T1>
  const string format(const string& fmt, const _T0& arg0, const _T1& arg1) {
    strvector list = {toStr(arg0), toStr(arg1)};
    return varReplace(fmt, list);
  }

  template<typename _T0, typename _T1, typename _T2>
  const string format(const string& fmt, const _T0& arg0, const _T1& arg1, const _T2& arg2) {
    strvector list = {toStr(arg0), toStr(arg1), toStr(arg2)};
    return varReplace(fmt, list);
  }

  template<typename _T0, typename _T1, typename _T2, typename _T3>
  const string format(const string& fmt, const _T0& arg0, const _T1& arg1, const _T2& arg2, const _T3& arg3) {
    strvector list = {toStr(arg0), toStr(arg1), toStr(arg2), toStr(arg3)};
    return varReplace(fmt, list);
  }

  template<typename _T0, typename _T1, typename _T2, typename _T3, typename _T4>
  const string format(const string& fmt, const _T0& arg0, const _T1& arg1, const _T2& arg2, const _T3& arg3, const _T4& arg4) {
    strvector list = {toStr(arg0), toStr(arg1), toStr(arg2), toStr(arg3), toStr(arg4)};
    return varReplace(fmt, list);
  }

  template<typename _T0, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5>
  const string format(const string& fmt, const _T0& arg0, const _T1& arg1, const _T2& arg2, const _T3& arg3, const _T4& arg4, const _T5& arg5) {
    strvector list = {toStr(arg0), toStr(arg1), toStr(arg2), toStr(arg3), toStr(arg4), toStr(arg5)};
    return varReplace(fmt, list);
  }

  template<typename _T0, typename _T1, typename _T2, typename _T3, typename _T4, typename _T5, typename _T6>
  const string format(const string& fmt, const _T0& arg0, const _T1& arg1, const _T2& arg2, const _T3& arg3, const _T4& arg4, const _T5& arg5, const _T6& arg6) {
    strvector list = {toStr(arg0), toStr(arg1), toStr(arg2), toStr(arg3), toStr(arg4), toStr(arg5), toStr(arg6)};
    return varReplace(fmt, list);
  }
}

#endif // !__CB_STRING_EX_H__
