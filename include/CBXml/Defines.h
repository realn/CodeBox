#ifndef __CB_XML_DEFINES_H__
#define __CB_XML_DEFINES_H__

#include <string>
#include <vector>
#include <map>
#include <iostream>

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
  using strmap = std::map<string, string>;

  using istream = std::wistream;
  using ostream = std::wostream;
}

#endif // !__CB_XML_DEFINES_H__
