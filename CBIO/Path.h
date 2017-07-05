#ifndef __CB_IO_PATH_H__
#define __CB_IO_PATH_H__

#include "Defines.h"

namespace cb {
  extern size_t filenameextpos(const string& filename);
  extern string filenameext(const string& filename);
  extern string makefilename(const string& name, const string& ext);

  extern string clearpath(const string& path);

  extern size_t pathnamepos(const string& path);
  extern string pathname(const string& path);
  extern string pathbase(const string& path);
  extern string makepath(const string& path1, const string& path2);
}

#endif // !__CB_IO_PATH_H__

