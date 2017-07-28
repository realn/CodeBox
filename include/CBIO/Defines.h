#ifndef __CB_IO_DEFINES_H__
#define __CB_IO_DEFINES_H__

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

namespace cb {
  using string = std::wstring;

  using byte = unsigned char;
  using bytevector = std::vector<byte>;
  using charvector = std::vector<char>;

  using ostream = std::wostream;
  using istream = std::wistream;

  using fstream = std::basic_fstream<byte>;
  using ifstream = std::basic_ifstream<byte>;
  using ofstream = std::basic_ofstream<byte>;
}

#endif // !__CB_IO_DEFINES_H__

