#ifndef __CB_XML_DEFINES_H__
#define __CB_XML_DEFINES_H__

#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace cb {
  using string = std::wstring;
  using strvector = std::vector<string>;
  using strmap = std::map<string, string>;

  using istream = std::wistream;
  using ostream = std::wostream;
}

#endif // !__CB_XML_DEFINES_H__
