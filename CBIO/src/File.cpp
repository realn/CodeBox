#include "stdafx.h"
#include "../File.h"

#include <CBStr/StringEx.h>

namespace cb {
  bool fileexists(const string & filepath) {
    auto file = ifstream(filepath, std::ios::in);
    return file.is_open();
  }

  std::streamsize filesize(const string & filepath) {
    auto file = ifstream(filepath, std::ios::in);
    return filesize(file);
  }

  bytevector readfile(const string & filepath) {
    auto file = ifstream(filepath, std::ios::binary | std::ios::in);
    if(!file.is_open())
      return bytevector();
    return readfile(file);
  }

  bool readfile(const string & filepath, bytevector & outdata) {
    auto file = ifstream(filepath, std::ios::binary | std::ios::in);
    if(!file.is_open())
      return false;
    return readfile(file, outdata);
  }

  bytevector readfile(ifstream & stream) {
    bytevector result;
    if(!readfile(stream, result)) {
      return bytevector();
    }
    return result;
  }

  bool readfile(ifstream & stream, bytevector & outdata) {
    auto size = filesize(stream);
    outdata.resize(bytevector::size_type(size));
    stream.read(outdata.data(), size);
    return !stream.fail();
  }

  bool writefile(const string & filepath, const bytevector & data) {
    auto file = ofstream(filepath, std::ios::binary | std::ios::trunc | std::ios::out);
    if(!file.is_open()) {
      return false;
    }
    return writefile(file, data);
  }

  bool writefile(ofstream & stream, const bytevector & data) {
    if(data.size() == 0)
      return false;
    stream.write(data.data(), data.size());
    return !stream.fail();
  }

  string readtextfileutf8(const string & filepath) {
    auto file = std::ifstream(filepath, std::ios::in | std::ios::binary);
    if(!file.is_open())
      return string();
    return readtextfileutf8(file);
  }

  string readtextfileutf8(std::ifstream & file) {
    auto size = filesize(file);
    if(size == 0)
      return string();

    auto data = charvector(charvector::size_type(size));
    file.read(data.data(), size);

    return fromUtf8(data);
  }

  string readtextfileutf16(const string & filepath) {
    auto file = std::wifstream(filepath, std::ios::in | std::ios::binary);
    if(!file.is_open())
      return string();
    return readtextfileutf16(file);
  }

  string readtextfileutf16(std::wifstream & file) {
    auto size = filesize(file);
    if(size == 0)
      return string();

    auto result = string(string::size_type(size), L'\0');
    file.read(&result[0], size);

    return result;
  }

  bool writetextfileutf8(const string & filepath, const string & text) {
    auto file = std::ofstream(filepath, std::ios::out | std::ios::trunc | std::ios::binary);
    if(!file.is_open())
      return false;
    return writetextfileutf8(file, text);
  }

  bool writetextfileutf8(std::ofstream & file, const string & text) {
    auto data = toUtf8(text);
    file.write(data.data(), data.size());
    return !file.fail();
  }

  bool writetextfileutf16(const string & filepath, const string & text) {
    auto file = std::wofstream(filepath, std::ios::out | std::ios::trunc | std::ios::binary);
    if(!file.is_open())
      return false;
    return writetextfileutf16(file, text);
  }

  bool writetextfileutf16(std::wofstream & file, const string & text) {
    file.write(text.data(), text.size());
    return !file.fail();
  }
}

