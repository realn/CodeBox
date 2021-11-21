#pragma once

#include "Defines.h"

namespace cb {
  template<typename _Type>
  std::streamsize filesize(std::basic_ifstream<_Type>& stream) {
    auto pos = stream.tellg();
    stream.seekg(0, std::ios::end);
    auto result = stream.tellg();
    stream.seekg(pos, std::ios::beg);
    return result;
  }
  template<typename _Type>
  std::streamsize filesize(std::basic_ofstream<_Type>& stream) {
    auto pos = stream.tellp();
    stream.seekp(0, std::ios::end);
    auto result = stream.tellp();
    stream.seekp(pos, std::ios::beg);
    return result;
  }

  bool fileexists(string const& filepath);
  std::streamsize filesize(string const& filepath);

  bytevector readfile(string const& filepath);
  bool readfile(string const& filepath, bytevector& outdata);

  bytevector readfile(ifstream& stream);
  bool readfile(ifstream& stream, bytevector& outdata);

  bool writefile(string const& filepath, bytevector const& data);
  bool writefile(ofstream& stream, bytevector const& data);

  string readtextfileutf8(string const& filepath);
  string readtextfileutf8(std::ifstream& stream);
  string readtextfileutf16(string const& filepath);
  string readtextfileutf16(std::wifstream& stream);

  bool writetextfileutf8(string const& filepath, string const& text);
  bool writetextfileutf8(std::ofstream& file, string const& text);
  bool writetextfileutf16(string const& filepath, string const& text);
  bool writetextfileutf16(std::wofstream& file, string const& text);
}
