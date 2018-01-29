#ifndef __CB_IO_PATH_H__
#define __CB_IO_PATH_H__

#include "Defines.h"

namespace cb {
  extern size_t filenameextpos(string const& filename);
  extern string filenameext(string const& filename);
  extern string filenamebase(string const& filename);
  extern string makefilename(string const& name, string const& ext);

  extern string clearpath(string const& path);

  extern size_t pathnamepos(string const& path);
  extern string pathname(string const& path);
  extern string pathbase(string const& path);
  extern string makepath(string const& path1, string const& path2);
}

#endif // !__CB_IO_PATH_H__

