#ifndef __CB_STRING_DEFINES_H__
#define __CB_STRING_DEFINES_H__

#include <string>
#include <sstream>
#include <vector>
#include <map>

namespace cb {
  typedef std::wstring string;
  typedef std::vector<string> strvector;
  typedef std::wstringstream strstream;
  typedef std::map<string, string> strmap;
  typedef std::vector<char> charvector;
}

#endif // !__CB_STRING_DEFINES_H__
