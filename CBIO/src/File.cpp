#include "stdafx.h"
#include "../File.h"

#include <CBStr/StringEx.h>

namespace cb {
  const bool fileexists(const string & filepath) {
    ifstream file(filepath, std::ios::in);
    return file.is_open();
  }
  const std::streamsize filesize(const string & filepath) {
    ifstream file(filepath, std::ios::in);
    return filesize(file);
  }

  const std::streamsize filesize(ifstream & stream) {
    std::streampos pos = stream.tellg();
    stream.seekg(0, std::ios::end);
    std::streampos result = stream.tellg();
    stream.seekg(pos, std::ios::beg);
    return result;
  }

  const std::streamsize filesize(ofstream & stream) {
    std::streampos pos = stream.tellp();
    stream.seekp(0, std::ios::end);
    std::streampos result = stream.tellp();
    stream.seekp(pos, std::ios::beg);
    return result;
  }

  const bytevector readfile(const string & filepath) {
    ifstream file(filepath, std::ios::binary | std::ios::in);
    if(file.is_open())
      return bytevector();
    return readfile(file);
  }

  const bool readfile(const string & filepath, bytevector & outdata) {
    ifstream file(filepath, std::ios::binary | std::ios::in);
    if(!file.is_open())
      return false;
    return readfile(file, outdata);
  }

  const bytevector readfile(ifstream & stream) {
    bytevector result;
    if(!readfile(stream, result)) {
      return bytevector();
    }
    return result;
  }

  const bool readfile(ifstream & stream, bytevector & outdata) {
    std::streamsize size = filesize(stream);
    outdata.resize((size_t)size);
    byte* ptr = vectorcastptr<byte>(outdata);
    stream.read(ptr, size);
    return !stream.fail();
  }

  const bool writefile(const string & filepath, const bytevector & data) {
    ofstream file(filepath, std::ios::binary | std::ios::trunc | std::ios::out);
    if(!file.is_open()) {
      return false;
    }
    return writefile(file, data);
  }

  const bool writefile(ofstream & stream, const bytevector & data) {
    if(data.size() == 0)
      return false;
    const byte* ptr = vectorcastptr<byte>(data);
    stream.write(ptr, data.size());
    return !stream.fail();
  }

  const string readtextfileutf8(const string & filepath) {
    ifstream file(filepath, std::ios::in | std::ios::binary);
    if(!file.is_open())
      return string();
    return readtextfileutf8(file);
  }

  const string readtextfileutf8(ifstream & file) {
    std::streamsize size = filesize(file);
    if(size == 0)
      return string();

    charvector data;
    data.resize((size_t)size);
    byte* ptr = vectorcastptr<byte>(data);
    file.read(ptr, size);

    return fromUtf8(data);
  }

  const string readtextfileutf16(const string & filepath) {
    ifstream file(filepath, std::ios::in | std::ios::binary);
    if(!file.is_open())
      return string();
    return readtextfileutf16(file);
  }

  const string readtextfileutf16(ifstream & file) {
    std::streamsize size = filesize(file);
    if(size == 0)
      return string();

    string result;
    result.resize((size_t)size / sizeof(string::value_type));
    byte* ptr = byteptr(result[0]);
    file.read(ptr, size);

    return result;
  }

  const bool writetextfileutf8(const string & filepath, const string & text) {
    ofstream file(filepath, std::ios::out | std::ios::trunc | std::ios::binary);
    if(!file.is_open())
      return false;
    return writetextfileutf8(file, text);
  }

  const bool writetextfileutf8(ofstream & file, const string & text) {
    charvector data = toUtf8(text);
    const byte* ptr = vectorcastptr<byte>(data);
    file.write(ptr, data.size());
    return !file.fail();
  }

  const bool writetextfileutf16(const string & filepath, const string & text) {
    ofstream file(filepath, std::ios::out | std::ios::trunc | std::ios::binary);
    if(!file.is_open())
      return false;
    return writetextfileutf16(file, text);
  }

  const bool writetextfileutf16(ofstream & file, const string & text) {
    const byte* ptr = byteptr(text.c_str());
    file.write(ptr, text.length() * sizeof(string::value_type));
    return !file.fail();
  }
}

