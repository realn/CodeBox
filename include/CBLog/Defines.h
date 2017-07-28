#ifndef __CB_LOG_DEFINES_H__
#define __CB_LOG_DEFINES_H__

#include <string>
#include <ostream>
#include <sstream>
#include <vector>

namespace cb {
  using string = std::wstring;
  using strvector = std::vector<string>;
  using ostream = std::wostream;
  using stringstream = std::wstringstream;
}

#endif // !__CB_LOG_DEFINES_H__
