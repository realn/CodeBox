#ifndef __CB_XML_DEFINES_H__
#define __CB_XML_DEFINES_H__

#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace cb {
  typedef std::wstring string;
  typedef std::vector<string> strvector;
  typedef std::map<string, string> strmap;

  typedef std::wistream istream;
  typedef std::wostream ostream;
}

#endif // !__CB_XML_DEFINES_H__
