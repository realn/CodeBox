#include "stdafx.h"
#include <CBCore/File.h>
#include <CBCore/StringConvert.h>

namespace cb {
  bool fileexists(string const& filepath) {
    auto file = ifstream(filepath, std::ios::in);
    return file.is_open();
  }

  std::streamsize filesize(string const& filepath) {
    auto file = ifstream(filepath, std::ios::in);
    return filesize(file);
  }

  bytevector readfile(string const& filepath) {
    auto file = ifstream(filepath, std::ios::binary | std::ios::in);
    if (!file.is_open())
      return bytevector();
    return readfile(file);
  }

  bool readfile(string const& filepath, bytevector& outdata) {
    auto file = ifstream(filepath, std::ios::binary | std::ios::in);
    if (!file.is_open())
      return false;
    return readfile(file, outdata);
  }

  bytevector readfile(ifstream& stream) {
    bytevector result;
    if (!readfile(stream, result)) {
      return bytevector();
    }
    return result;
  }

  bool readfile(ifstream& stream, bytevector& outdata) {
    auto size = filesize(stream);
    outdata.resize(bytevector::size_type(size));
    stream.read(outdata.data(), size);
    return !stream.fail();
  }

  bool writefile(string const& filepath, bytevector const& data) {
    auto file = ofstream(filepath, std::ios::binary | std::ios::trunc | std::ios::out);
    if (!file.is_open()) {
      return false;
    }
    return writefile(file, data);
  }

  bool writefile(ofstream& stream, bytevector const& data) {
    if (data.size() == 0)
      return false;
    stream.write(data.data(), data.size());
    return !stream.fail();
  }

  string readtextfileutf8(string const& filepath) {
    auto file = std::ifstream(filepath, std::ios::in | std::ios::binary);
    if (!file.is_open())
      return string();
    return readtextfileutf8(file);
  }

  string readtextfileutf8(std::ifstream& file) {
    auto size = filesize(file);
    if (size == 0)
      return string();

    auto data = utf8string(static_cast<size_t>(size), 0);
    file.read(&data[0], size);

    return fromUtf8(data);
  }

  string readtextfileutf16(string const& filepath) {
    auto file = std::wifstream(filepath, std::ios::in | std::ios::binary);
    if (!file.is_open())
      return string();
    return readtextfileutf16(file);
  }

  string readtextfileutf16(std::wifstream& file) {
    auto size = filesize(file);
    if (size == 0)
      return string();

    auto result = string(string::size_type(size), L'\0');
    file.read(&result[0], size);

    return result;
  }

  bool writetextfileutf8(string const& filepath, string const& text) {
    auto file = std::ofstream(filepath, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!file.is_open())
      return false;
    return writetextfileutf8(file, text);
  }

  bool writetextfileutf8(std::ofstream& file, string const& text) {
    auto data = toUtf8(text);
    file.write(data.data(), data.size());
    return !file.fail();
  }

  bool writetextfileutf16(string const& filepath, string const& text) {
    auto file = std::wofstream(filepath, std::ios::out | std::ios::trunc | std::ios::binary);
    if (!file.is_open())
      return false;
    return writetextfileutf16(file, text);
  }

  bool writetextfileutf16(std::wofstream& file, string const& text) {
    file.write(text.data(), text.size());
    return !file.fail();
  }
}

