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

  extern bool fileexists(string const& filepath);
  extern std::streamsize filesize(string const& filepath);  
  
  extern bytevector readfile(string const& filepath);
  extern bool readfile(string const& filepath, bytevector& outdata);

  extern bytevector readfile(ifstream& stream);
  extern bool readfile(ifstream& stream, bytevector& outdata);

  extern bool writefile(string const& filepath, bytevector const& data);
  extern bool writefile(ofstream& stream, bytevector const& data);

  extern string readtextfileutf8(string const& filepath);
  extern string readtextfileutf8(std::ifstream& stream);
  extern string readtextfileutf16(string const& filepath);
  extern string readtextfileutf16(std::wifstream& stream);

  extern bool writetextfileutf8(string const& filepath, string const& text);
  extern bool writetextfileutf8(std::ofstream& file, string const& text);
  extern bool writetextfileutf16(string const& filepath, string const& text);
  extern bool writetextfileutf16(std::wofstream& file, string const& text);
}
