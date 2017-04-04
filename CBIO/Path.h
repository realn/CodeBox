#ifndef __CB_IO_PATH_H__
#define __CB_IO_PATH_H__

#include "Defines.h"

namespace cb {
  extern const size_t filenameextpos(const string& filename);
  extern const string filenameext(const string& filename);
  extern const string makefilename(const string& name, const string& ext);

  extern const string clearpath(const string& path);

  extern const size_t pathnamepos(const string& path);
  extern const string pathname(const string& path);
  extern const string pathbase(const string& path);
  extern const string makepath(const string& path1, const string& path2);
}

#endif // !__CB_IO_PATH_H__

