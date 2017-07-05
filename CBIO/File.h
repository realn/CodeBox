#ifndef __CB_IO_FILE_H__
#define __CB_IO_FILE_H__

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

  extern bool fileexists(const string& filepath);
  extern std::streamsize filesize(const string& filepath);  
  
  extern bytevector readfile(const string& filepath);
  extern bool readfile(const string& filepath, bytevector& outdata);

  extern bytevector readfile(ifstream& stream);
  extern bool readfile(ifstream& stream, bytevector& outdata);

  extern bool writefile(const string& filepath, const bytevector& data);
  extern bool writefile(ofstream& stream, const bytevector& data);

  extern string readtextfileutf8(const string& filepath);
  extern string readtextfileutf8(std::ifstream& stream);
  extern string readtextfileutf16(const string& filepath);
  extern string readtextfileutf16(std::wifstream& stream);

  extern bool writetextfileutf8(const string& filepath, const string& text);
  extern bool writetextfileutf8(std::ofstream& file, const string& text);
  extern bool writetextfileutf16(const string& filepath, const string& text);
  extern bool writetextfileutf16(std::wofstream& file, const string& text);
}

#endif // !__CB_IO_FILE_H__

