#ifndef __CB_IO_FILE_H__
#define __CB_IO_FILE_H__

#include "Defines.h"

namespace cb {
  extern const bool fileexists(const string& filepath);
  extern const std::streamsize filesize(const string& filepath);
  extern const std::streamsize filesize(ifstream& stream);
  extern const std::streamsize filesize(ofstream& stream);

  extern const bytevector readfile(const string& filepath);
  extern const bool readfile(const string& filepath, bytevector& outdata);

  extern const bytevector readfile(ifstream& stream);
  extern const bool readfile(ifstream& stream, bytevector& outdata);

  extern const bool writefile(const string& filepath, const bytevector& data);
  extern const bool writefile(ofstream& stream, const bytevector& data);

  extern const string readtextfileutf8(const string& filepath);
  extern const string readtextfileutf8(ifstream& stream);
  extern const string readtextfileutf16(const string& filepath);
  extern const string readtextfileutf16(ifstream& stream);

  extern const bool writetextfileutf8(const string& filepath, const string& text);
  extern const bool writetextfileutf8(ofstream& file, const string& text);
  extern const bool writetextfileutf16(const string& filepath, const string& text);
  extern const bool writetextfileutf16(ofstream& file, const string& text);
}

#endif // !__CB_IO_FILE_H__

